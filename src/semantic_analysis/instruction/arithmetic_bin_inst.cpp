#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/semantic_analysis.hpp"
#include <iostream>

namespace LIRA {
namespace Pass {
MIR::InstPtr SemanticAnalyzer::analyze_arithmetic_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    auto args = inst_stmt->get_value()->get_operands();
    auto _dest = inst_stmt->get_name();
    if(!_dest.has_value()){
        error(name,"Arithmetic binary instruction must have a destination i.e assign this instruction to a variable");
    }
    if(args.size() != 2){
        error(name,"Arithmetic binary instruction must have 2 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    for(auto arg:args){
        arg.second = get_reduced_type(arg.second);
        if(!type_eq(type,arg.second)){
            error(arg.first->get_token(),"Argument type " + arg.second->to_string() + " is not the same as destination type " + type->to_string());
        }
        else if(!type_compatible(type,arg.first)){
            error(arg.first->get_token(),"Argument type " + arg.second->get_token().value + " is not compatible with destination type " + type->to_string());
        }
    }
    auto type_varient = MIR::get_type_varient_from_type(type);
    if(!type_varient.has_value()){
        error(name,"Unsupported type for arithmetic binary instruction: " + type->to_string());
    }
    if((!MIR::is_int_typevarient(type_varient.value())) && (!MIR::is_float_typevarient(type_varient.value()))){
        error(name,"Only int and float types are supported for arithmetic binary instruction");
    }

    //After this stage, type varient can only be float or int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    if(name.value == ".add"){
        return analyze_add_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else if(name.value == ".sub"){
        return analyze_sub_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else if(name.value == ".mul"){
        return analyze_mul_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else if(name.value == ".div"){
        return analyze_div_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else if(name.value == ".rem"){
        return analyze_rem_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown arithmetic binary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr SemanticAnalyzer::analyze_add_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        if(remaining_attrs.size() > 0){
            error(remaining_attrs[0]->get_token(),"Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatAddInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatAddInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = extract_flag_attrs(attributes, {"nsw", "nuw"});
        if(remaining_attrs.size() > 0){
            error(remaining_attrs[0]->get_token(),"Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntAddInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"]);
        }
        else{
            return std::make_shared<MIR::VecIntAddInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"]);
        }
    }
}
MIR::InstPtr SemanticAnalyzer::analyze_sub_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        if(remaining_attrs.size() > 0){
            error(remaining_attrs[0]->get_token(),"Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatSubInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatSubInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = extract_flag_attrs(attributes, {"nsw", "nuw"});
        if(remaining_attrs.size() > 0){
            error(remaining_attrs[0]->get_token(),"Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntSubInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"]);
        }
        else{
            return std::make_shared<MIR::VecIntSubInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"]);
        }
    }
}
MIR::InstPtr SemanticAnalyzer::analyze_mul_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        if(remaining_attrs.size() > 0){
            error(remaining_attrs[0]->get_token(),"Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatMulInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatMulInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = extract_flag_attrs(attributes, {"nsw", "nuw"});
        if(remaining_attrs.size() > 0){
            error(remaining_attrs[0]->get_token(),"Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntMulInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"]);
        }
        else{
            return std::make_shared<MIR::VecIntMulInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"]);
        }
    }
}
MIR::InstPtr SemanticAnalyzer::analyze_div_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        if(remaining_attrs.size() > 0){
            error(remaining_attrs[0]->get_token(),"Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatDivInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatDivInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = extract_flag_attrs(attributes, {"exact", "unsigned"});
        if(remaining_attrs.size() > 0){
            error(remaining_attrs[0]->get_token(),"Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntDivInst>(inst_stmt,dest,lhs,rhs,flag_attrs["exact"],flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntDivInst>(inst_stmt,dest,lhs,rhs,flag_attrs["exact"],flag_attrs["unsigned"]);
        }
    }
}
MIR::InstPtr SemanticAnalyzer::analyze_rem_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        if(remaining_attrs.size() > 0){
            error(remaining_attrs[0]->get_token(),"Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatRemInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatRemInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = extract_flag_attrs(attributes, {"unsigned"});
        if(remaining_attrs.size() > 0){
            error(remaining_attrs[0]->get_token(),"Unsupported attribute for int arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntRemInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntRemInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
        }
    }
}
}
}