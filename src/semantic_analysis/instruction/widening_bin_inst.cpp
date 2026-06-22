#include "ast/ast.hpp"
#include "semantic_analysis/semantic_analysis.hpp"
#include <cstddef>
#include <iostream>
#include <functional>
namespace LIRA {
namespace Pass {
using DispatchFuncType = std::function<MIR::InstPtr(std::string, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    IR::TypeExprPtr input_type, MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt)>;

//NOTE:-Dont merge them into one templated function. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
MIR::InstPtr analyze_widening_add_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                           IR::TypeExprPtr input_type, MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_widening_sub_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                           IR::TypeExprPtr input_type, MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_widening_mul_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                           IR::TypeExprPtr input_type, MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr SemanticAnalyzer::analyze_widening_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
            {".widening_add", analyze_widening_add_bin_inst},
            {".widening_sub", analyze_widening_sub_bin_inst},
            {".widening_mul", analyze_widening_mul_bin_inst}
    };

    auto args = inst_stmt->get_value()->get_operands();
    auto _dest = inst_stmt->get_name();
    if(!_dest.has_value()){
        Utils::error(this->filename, name, "Binary widening instruction must have a destination i.e assign this instruction to a variable");
    }
    if(args.size() != 2){
        Utils::error(this->filename, name, "Binary widening instruction must have 2 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    ;
    for(size_t i=0;i<args.size();i++){
        args[i].second = Utils::get_reduced_type(this->type_symtable,args[i].second);
        if(!Utils::type_ge(this->filename, type, args[i].second)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->to_string() + " must be smaller than " + type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, type,args[i].first)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->get_token().value + " is not compatible with destination type " + type->to_string());
        }
    }
    if(!Utils::type_eq(args[0].second,args[1].second)){
        Utils::error(this->filename, args[1].first->get_token(), "Argument type " + args[1].second->to_string() + " is not the same as argument type " + args[0].second->to_string());
    }
    IR::TypeExprPtr input_type = args[0].second;
    auto type_varient = MIR::get_type_varient_from_type(type);
    if(!type_varient.has_value()){
        Utils::error(this->filename, name, "Unsupported type for binary widening instruction: " + type->to_string());
    }
    if((!MIR::is_int_typevarient(type_varient.value())) && (!MIR::is_float_typevarient(type_varient.value()))){
        Utils::error(this->filename, name, "Only int and float types are supported for binary widening instruction");
    }

    //After this stage, type varient can only be float or int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),input_type,type_varient.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown binary widening instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_widening_add_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                           IR::TypeExprPtr input_type, MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float widening arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::TypeVarient::Float){
            return std::make_shared<MIR::FloatWideningAddInst>(inst_stmt,dest,lhs,rhs,input_type,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatWideningAddInst>(inst_stmt,dest,lhs,rhs,input_type,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw", "nuw","unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int widening arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::TypeVarient::Int){
            return std::make_shared<MIR::IntWideningAddInst>(inst_stmt,dest,lhs,rhs,input_type,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntWideningAddInst>(inst_stmt,dest,lhs,rhs,input_type,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"]);
        }
    }
}
MIR::InstPtr analyze_widening_sub_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                           IR::TypeExprPtr input_type, MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float widening arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::TypeVarient::Float){
            return std::make_shared<MIR::FloatWideningSubInst>(inst_stmt,dest,lhs,rhs,input_type,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatWideningSubInst>(inst_stmt,dest,lhs,rhs,input_type,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw", "nuw","unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int widening arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::TypeVarient::Int){
            return std::make_shared<MIR::IntWideningSubInst>(inst_stmt,dest,lhs,rhs,input_type,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntWideningSubInst>(inst_stmt,dest,lhs,rhs,input_type,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"]);
        }
    }
}
MIR::InstPtr analyze_widening_mul_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                           IR::TypeExprPtr input_type, MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float widening arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::TypeVarient::Float){
            return std::make_shared<MIR::FloatWideningMulInst>(inst_stmt,dest,lhs,rhs,input_type,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatWideningMulInst>(inst_stmt,dest,lhs,rhs,input_type,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw", "nuw","unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int widening arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::TypeVarient::Int){
            return std::make_shared<MIR::IntWideningMulInst>(inst_stmt,dest,lhs,rhs,input_type,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntWideningMulInst>(inst_stmt,dest,lhs,rhs,input_type,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"]);
        }
    }
}
}
}