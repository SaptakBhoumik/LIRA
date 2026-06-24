#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>

namespace LIRA {
namespace SemanticAnalyzer {
MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_bitwise_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    auto args = inst_stmt->get_value()->get_operands();
    auto _dest = inst_stmt->get_name();
    if(!_dest.has_value()){
        error(name,"Bitwise binary instruction must have a destination i.e assign this instruction to a variable");
    }
    if(args.size() != 2){
        error(name,"Bitwise binary instruction must have 2 arguments");
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
        error(name,"Unsupported type for bitwise binary instruction: " + type->to_string());
    }
    else if(!MIR::is_int_typevarient(type_varient.value())){
        error(name,"Only int types are supported for bitwise binary instruction");
    }

    //After this stage, type varient can only be int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    if(name.value == ".and"){
        return analyze_and_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else if(name.value == ".or"){
        return analyze_or_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else if(name.value == ".xor"){
        return analyze_xor_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else if(name.value == ".shl"){
        return analyze_shl_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else if(name.value == ".lshr"){
        return analyze_lshr_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else if(name.value == ".ashr"){
        return analyze_ashr_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type_varient.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown bitwise binary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_and_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size()>0){
        error(inst_stmt->get_token(),"Bitwise and instruction cannot have attributes");
    }
    if(type_varient == MIR::TypeVarient::Int){
        return std::make_shared<MIR::IntANDInst>(inst_stmt,dest,lhs,rhs);
    }
    else {
        return std::make_shared<MIR::VecIntANDInst>(inst_stmt,dest,lhs,rhs);
    }
}

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_or_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = extract_flag_attrs(attributes, {"disjoint"});
    if(remaining_attrs.size() > 0){
        error(remaining_attrs[0]->get_token(),"Unsupported attribute for int bitwise or instruction: " + remaining_attrs[0]->to_string());
    }
    bool disjoint = flag_attrs["disjoint"];
    if(type_varient == MIR::TypeVarient::Int){
        return std::make_shared<MIR::IntORInst>(inst_stmt,dest,lhs,rhs,disjoint);
    }
    else {
        return std::make_shared<MIR::VecIntORInst>(inst_stmt,dest,lhs,rhs,disjoint);
    }
}

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_xor_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size()>0){
        error(inst_stmt->get_token(),"Bitwise xor instruction cannot have attributes");
    }
    if(type_varient == MIR::TypeVarient::Int){
        return std::make_shared<MIR::IntXORInst>(inst_stmt,dest,lhs,rhs);
    }
    else {
        return std::make_shared<MIR::VecIntXORInst>(inst_stmt,dest,lhs,rhs);
    }
}

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_shl_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = extract_flag_attrs(attributes, {"nuw", "nsw"});
    if(remaining_attrs.size() > 0){
        error(remaining_attrs[0]->get_token(),"Unsupported attribute for int bitwise shl instruction: " + remaining_attrs[0]->to_string());
    }
    bool nuw = flag_attrs["nuw"];
    bool nsw = flag_attrs["nsw"];
    if(type_varient == MIR::TypeVarient::Int){
        return std::make_shared<MIR::IntSHLInst>(inst_stmt,dest,lhs,rhs,nuw,nsw);
    }
    else {
        return std::make_shared<MIR::VecIntSHLInst>(inst_stmt,dest,lhs,rhs,nuw,nsw);
    }
}

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_lshr_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = extract_flag_attrs(attributes, {"exact"});
    if(remaining_attrs.size() > 0){
        error(remaining_attrs[0]->get_token(),"Unsupported attribute for int bitwise lshr instruction: " + remaining_attrs[0]->to_string());
    }
    bool exact = flag_attrs["exact"];
    if(type_varient == MIR::TypeVarient::Int){
        return std::make_shared<MIR::IntLSHRInst>(inst_stmt,dest,lhs,rhs,exact);
    }
    else {
        return std::make_shared<MIR::VecIntLSHRInst>(inst_stmt,dest,lhs,rhs,exact);
    }
}

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_ashr_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::TypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = extract_flag_attrs(attributes, {"exact"});
    if(remaining_attrs.size() > 0){
        error(remaining_attrs[0]->get_token(),"Unsupported attribute for int bitwise ashr instruction: " + remaining_attrs[0]->to_string());
    }
    bool exact = flag_attrs["exact"];
    if(type_varient == MIR::TypeVarient::Int){
        return std::make_shared<MIR::IntASHRInst>(inst_stmt,dest,lhs,rhs,exact);
    }
    else {
        return std::make_shared<MIR::VecIntASHRInst>(inst_stmt,dest,lhs,rhs,exact);
    }
}
}
}