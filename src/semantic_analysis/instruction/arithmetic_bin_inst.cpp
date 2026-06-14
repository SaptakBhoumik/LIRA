#include "ast/ast.hpp"
#include "semantic_analysis/semantic_analysis.hpp"
#include <iostream>
#include <functional>
namespace LIRA {
namespace Pass {
using DispatchFuncType = std::function<MIR::InstPtr(std::string, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_add_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_sub_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_mul_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_div_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_rem_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_copysign_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                       MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_min_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_max_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_avg_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);

//NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".add", analyze_add_bin_inst},
        {".sub", analyze_sub_bin_inst},
        {".mul", analyze_mul_bin_inst},
        {".div", analyze_div_bin_inst},
        {".rem", analyze_rem_bin_inst},
        {".copysign", analyze_copysign_bin_inst},
        {".min", analyze_min_bin_inst},
        {".max", analyze_max_bin_inst},
        {".avg", analyze_avg_bin_inst}
};
MIR::InstPtr SemanticAnalyzer::analyze_arithmetic_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    auto args = inst_stmt->get_value()->get_operands();
    auto _dest = inst_stmt->get_name();
    if(!_dest.has_value()){
        Utils::error(this->filename, name, "Arithmetic binary instruction must have a destination i.e assign this instruction to a variable");
    }
    if(args.size() != 2){
        Utils::error(this->filename, name, "Arithmetic binary instruction must have 2 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    for(auto arg:args){
        arg.second = Utils::get_reduced_type(this->type_symtable,arg.second);
        if(!Utils::type_eq(type,arg.second)){
            Utils::error(this->filename, arg.first->get_token(), "Argument type " + arg.second->to_string() + " is not the same as destination type " + type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, type,arg.first)){
            Utils::error(this->filename, arg.first->get_token(), "Argument type " + arg.second->get_token().value + " is not compatible with destination type " + type->to_string());
        }
    }
    auto type_varient = MIR::get_type_varient_from_type(type);
    if(!type_varient.has_value()){
        Utils::error(this->filename, name, "Unsupported type for arithmetic binary instruction: " + type->to_string());
    }
    if((!MIR::is_int_typevarient(type_varient.value())) && (!MIR::is_float_typevarient(type_varient.value()))){
        Utils::error(this->filename, name, "Only int and float types are supported for arithmetic binary instruction");
    }

    //After this stage, type varient can only be float or int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown arithmetic binary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_add_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatAddInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatAddInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw", "nuw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntAddInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
        else{
            return std::make_shared<MIR::VecIntAddInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
    }
}
MIR::InstPtr analyze_sub_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatSubInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatSubInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw", "nuw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntSubInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
        else{
            return std::make_shared<MIR::VecIntSubInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
    }
}
MIR::InstPtr analyze_mul_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatMulInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatMulInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw", "nuw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntMulInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
        else{
            return std::make_shared<MIR::VecIntMulInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
    }
}
MIR::InstPtr analyze_div_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatDivInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatDivInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"exact", "unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntDivInst>(inst_stmt,dest,lhs,rhs,flag_attrs["exact"],flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntDivInst>(inst_stmt,dest,lhs,rhs,flag_attrs["exact"],flag_attrs["unsigned"]);
        }
    }
}
MIR::InstPtr analyze_rem_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatRemInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatRemInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntRemInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntRemInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
        }
    }
}
MIR::InstPtr analyze_copysign_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                        MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatCopySignInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatCopySignInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        if(attributes.size() > 0){
            Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int arithmetic binary instruction: " + attributes[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntCopySignInst>(inst_stmt,dest,lhs,rhs);
        }
        else{
            return std::make_shared<MIR::VecIntCopySignInst>(inst_stmt,dest,lhs,rhs);
        }
    }
}
MIR::InstPtr analyze_min_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,_remaining_attrs, {"unordered", "ieee754_2019"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatMinInst>(inst_stmt,dest,lhs,rhs,fast_math_attr,flag_attrs["ieee754_2019"],flag_attrs["unordered"]);
        }
        else{
            return std::make_shared<MIR::VecFloatMinInst>(inst_stmt,dest,lhs,rhs,fast_math_attr,flag_attrs["ieee754_2019"],flag_attrs["unordered"]);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntMinInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntMinInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
        }
    }
}
MIR::InstPtr analyze_max_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,_remaining_attrs, {"unordered", "ieee754_2019"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatMaxInst>(inst_stmt,dest,lhs,rhs,fast_math_attr,flag_attrs["ieee754_2019"],flag_attrs["unordered"]);
        }
        else{
            return std::make_shared<MIR::VecFloatMaxInst>(inst_stmt,dest,lhs,rhs,fast_math_attr,flag_attrs["ieee754_2019"],flag_attrs["unordered"]);
        }   
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntMaxInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntMaxInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
        }
    }
}
MIR::InstPtr analyze_avg_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatAvgInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatAvgInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }   
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nuw", "nsw","unsigned", "floor"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntAvgInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["floor"]);
        }
        else{
            return std::make_shared<MIR::VecIntAvgInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["floor"]);
        }
    }
}
}
}