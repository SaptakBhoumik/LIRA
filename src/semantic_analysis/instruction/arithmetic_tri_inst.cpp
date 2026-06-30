#include "ast/ast.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                                    IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_fma_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                  IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fms_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                  IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fnma_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                  IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fnms_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                   IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_clamp_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                    IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);


MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_arithmetic_tri_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".fma", analyze_fma_tri_inst},
        {".fms", analyze_fms_tri_inst},
        {".fnma", analyze_fnma_tri_inst},
        {".fnms", analyze_fnms_tri_inst},
        {".clamp", analyze_clamp_tri_inst}
    };
    auto args = inst_stmt->get_value()->get_operands();
    if(args.size() != 3){
        Utils::error(this->filename, name, "Arithmetic trinary instruction must have 3 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    if(dest == nullptr){
        Utils::error(this->filename, name, "Arithmetic trinary instruction must have a destination i.e assign this instruction to a variable");
    }
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    for(size_t i = 0; i < args.size(); i++){
        args[i].second = Utils::get_reduced_type(this->type_symtable,args[i].second);
        if(!Utils::type_eq(type,args[i].second)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->to_string() + " is not the same as destination type " + type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, args[i].second,args[i].first)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->get_token().value + " is not compatible with destination type " + type->to_string());
        }
    }
    auto type_variant = MIR::get_type_variant_from_type(type);
    if(!type_variant.has_value()){
        Utils::error(this->filename, name, "Unsupported type for arithmetic trinary instruction: " + type->to_string());
    }
    if((!MIR::is_int_typevariant(type_variant.value())) && (!MIR::is_float_typevariant(type_variant.value()))){
        Utils::error(this->filename, name, "Only int and float types are supported for arithmetic trinary instruction");
    }

    //After this stage, type variant can only be float or int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),args[2].first->get_literal(),type_variant.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown arithmetic trinary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}
MIR::InstPtr analyze_fma_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                  IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){

    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic trinary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatFMAInst>(inst_stmt,dest,arg1,arg2,arg3,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatFMAInst>(inst_stmt,dest,arg1,arg2,arg3,fast_math_attr);
        }
    }
    else{
         auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "nuw","nsw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic trinary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntFMAInst>(inst_stmt,dest,arg1,arg2,arg3,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
        else{
            return std::make_shared<MIR::VecIntFMAInst>(inst_stmt,dest,arg1,arg2,arg3,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
    }
}
MIR::InstPtr analyze_fms_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                  IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic trinary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatFMSInst>(inst_stmt,dest,arg1,arg2,arg3,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatFMSInst>(inst_stmt,dest,arg1,arg2,arg3,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "nuw","nsw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic trinary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntFMSInst>(inst_stmt,dest,arg1,arg2,arg3,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
        else{
            return std::make_shared<MIR::VecIntFMSInst>(inst_stmt,dest,arg1,arg2,arg3,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
    }
}
MIR::InstPtr analyze_fnma_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                  IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic trinary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatFNMAInst>(inst_stmt,dest,arg1,arg2,arg3,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatFNMAInst>(inst_stmt,dest,arg1,arg2,arg3,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "nuw","nsw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic trinary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntFNMAInst>(inst_stmt,dest,arg1,arg2,arg3,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
        else{
            return std::make_shared<MIR::VecIntFNMAInst>(inst_stmt,dest,arg1,arg2,arg3,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
    }
}
MIR::InstPtr analyze_fnms_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                   IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic trinary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatFNMSInst>(inst_stmt,dest,arg1,arg2,arg3,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatFNMSInst>(inst_stmt,dest,arg1,arg2,arg3,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "nuw","nsw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic trinary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntFNMSInst>(inst_stmt,dest,arg1,arg2,arg3,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
        else{
            return std::make_shared<MIR::VecIntFNMSInst>(inst_stmt,dest,arg1,arg2,arg3,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
    }
}
MIR::InstPtr analyze_clamp_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                    IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,_remaining_attrs, {"unordered", "ieee754_2019"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic trinary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatClampInst>(inst_stmt,dest,arg1,arg2,arg3,fast_math_attr,flag_attrs["ieee754_2019"],flag_attrs["unordered"]);
        }
        else{
            return std::make_shared<MIR::VecFloatClampInst>(inst_stmt,dest,arg1,arg2,arg3,fast_math_attr,flag_attrs["ieee754_2019"],flag_attrs["unordered"]);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic trinary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntClampInst>(inst_stmt,dest,arg1,arg2,arg3,flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntClampInst>(inst_stmt,dest,arg1,arg2,arg3,flag_attrs["unsigned"]);
        }
    }
}
}
}