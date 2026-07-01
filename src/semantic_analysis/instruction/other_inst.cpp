#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <cstdint>
#include <iostream>
#include <functional>
#include <memory>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                    IR::InstructionStmtPtr inst_stmt)>;
 
MIR::InstPtr analyze_select_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_freeze_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_va_start_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                   std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                   IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_va_end_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_va_copy_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                  std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                  IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_va_arg_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_ptrmask_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                  std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                  IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_pause_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_discrete_value_optimizer_hint(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                   std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                                   IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_range_optimizer_hint(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                          std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                          IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_nop_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                              std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                              IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_annotation_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                     std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                     IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_endbr64_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                  std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                  IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_launder_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                  std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                  IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_strip_invariant_group_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                                IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_other_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".select", analyze_select_inst},
        {".freeze", analyze_freeze_inst},
        {".ptrmask", analyze_ptrmask_inst},
        {".va_start", analyze_va_start_inst},
        {".va_end", analyze_va_end_inst},
        {".va_copy", analyze_va_copy_inst},
        {".va_arg", analyze_va_arg_inst},
        {".pause", analyze_pause_inst},
        {".nop", analyze_nop_inst},
        {".annotation", analyze_annotation_inst},
        {".endbr64", analyze_endbr64_inst},
        {".assume", analyze_discrete_value_optimizer_hint},
        {".assume_range", analyze_range_optimizer_hint},
        {".assume_not", analyze_discrete_value_optimizer_hint},
        {".assume_not_range", analyze_range_optimizer_hint},
        {".expect", analyze_discrete_value_optimizer_hint},
        {".expect_range", analyze_range_optimizer_hint},
        {".expect_not", analyze_discrete_value_optimizer_hint},
        {".expect_not_range", analyze_range_optimizer_hint},
        {".launder", analyze_launder_inst},
        {".strip_invariant_group", analyze_strip_invariant_group_inst},
    };
    auto args = inst_stmt->get_value()->get_operands();
    auto dest = process_local_dest_arg(inst_stmt);
    for(size_t i = 0; i < args.size(); i++){
        args[i].second = Utils::get_reduced_type(this->type_symtable,args[i].second);
        if(!Utils::type_compatible(this->var_symtable, args[i].second,args[i].first)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->get_token().value + " is not compatible with assigned type " + args[i].second->to_string());
        }
    }

    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,this->var_symtable,dest,name,args,inst_stmt);
    }
    else{
        std::cerr << "Unknown other instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_select_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction .select takes exactly three arguments");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .select must have a destination");
    }
    {
        if(!Utils::type_eq(args[1].second, dest->get_type())){
            Utils::error(filename, name, "Instruction .select takes an argument of the same type as the destination");
        }
        if(!Utils::type_eq(args[2].second, dest->get_type())){
            Utils::error(filename, name, "Instruction .select takes an argument of the same type as the destination");
        }
        if(!Utils::is_int(args[0].second, 1)){
            if(args[0].second->get_kind() == IR::TypeExprKind::SIMDTypeExpr){
                auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
                if(!Utils::is_int(simd_type->get_basetype(), 1)){
                    Utils::error(filename, name, "Instruction .select takes a first argument of type i1 or <i1,M> where M is the same as the second and third argument");
                }
                if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
                    Utils::error(filename, name, "Instruction .select takes a first argument of type <i1,M> which is a vector so the second and third argument must also be vectors of the same size");
                }
                auto simd_dest_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
                if(simd_dest_type->get_size() != simd_type->get_size()){
                    Utils::error(filename, name, "Instruction .select takes a first argument of type i1 or <i1,M> where M is the same as the second and third argument");
                }
            }
            else{
                Utils::error(filename, name, "Instruction .select takes a first argument of type i1 or <i1,M> where M is the same as the second and third argument");
            }
        }
    }
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(Utils::contains_float(dest->get_type())){
        auto temp = Utils::extract_fastmath_attrs(filename,attributes);
        fast_math_attr = temp.first;
        if(temp.second.size() > 0){
            Utils::error(filename, temp.second[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + temp.second[0]->to_string());
        }
    }
    else if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for select instruction: " + attributes[0]->to_string());
    }
    if(args[0].second->get_kind() == IR::TypeExprKind::SIMDTypeExpr){
        return std::make_shared<MIR::LanewiseSelectInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), fast_math_attr);
    }
    else{
        return std::make_shared<MIR::ScalarSelectInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), fast_math_attr);
    }
}
MIR::InstPtr analyze_freeze_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .freeze takes exactly one argument");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .freeze requires a destination argument");
    }
    if(!Utils::type_eq(args[0].second, dest->get_type())){
        Utils::error(filename, name, "Instruction .freeze takes an argument of the same type as the destination");
    }
    if(Utils::contains_float(dest->get_type())){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FreezeInst>(inst_stmt, dest, args[0].first->get_literal(), fast_math_attr);
    }
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for freeze instruction: " + attributes[0]->to_string());
    }
    return std::make_shared<MIR::FreezeInst>(inst_stmt, dest, args[0].first->get_literal(), std::nullopt);
}
MIR::InstPtr analyze_va_start_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                   std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                   IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .va_start takes exactly one argument");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .va_start has no destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .va_start takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .va_start takes a pointer type argument");
    }
    return std::make_shared<MIR::VastartInst>(inst_stmt, args[0].first->get_literal());
}
MIR::InstPtr analyze_va_end_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .va_end takes exactly one argument");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .va_end has no destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .va_end takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .va_end takes a pointer type argument");
    }
    return std::make_shared<MIR::VaendInst>(inst_stmt, args[0].first->get_literal());
}
MIR::InstPtr analyze_va_copy_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                  std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                  IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction .va_copy takes exactly two arguments");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .va_copy has no destination");    
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .va_copy takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .va_copy takes a pointer type argument for the first argument");
    }
    if(args[1].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .va_copy takes a pointer type argument for the second argument");
    }
    return std::make_shared<MIR::VacopyInst>(inst_stmt, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_va_arg_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .va_arg takes exactly one arguments");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .va_arg must have a destination");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .va_arg takes a pointer type argument");
    }
    if(Utils::contains_float(dest->get_type())){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::VaargInst>(inst_stmt, dest, args[0].first->get_literal(), fast_math_attr);
    }
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for va_arg instruction: " + attributes[0]->to_string());
    }
    return std::make_shared<MIR::VaargInst>(inst_stmt, dest, args[0].first->get_literal(), std::nullopt);
}
MIR::InstPtr analyze_ptrmask_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                  std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                  IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction .ptrmask takes exactly two arguments");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .ptrmask requires a destination argument");
    }
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for .ptrmask instruction: " + attributes[0]->to_string());
    }
    if(!Utils::type_eq(args[0].second, dest->get_type())){
        Utils::error(filename, name, "Instruction .ptrmask takes an argument of the same type as the destination");
    }
    auto type_varient = MIR::get_type_variant_from_type(dest->get_type());
    if(!type_varient.has_value()){
        Utils::error(filename, name, "Instruction .ptrmask takes a pointer type argument");
    }
    if(!MIR::is_ptr_typevariant(type_varient.value())){
        Utils::error(filename, name, "Instruction .ptrmask takes a pointer type argument");
    }
    if(type_varient.value() == MIR::TypeVariant::Ptr){
        if(!Utils::is_int(args[1].second, 64)){
            Utils::error(filename, name, "Instruction .ptrmask takes a second argument of type i64");
        }
        return std::make_shared<MIR::IntPtrMaskInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
    }
    else{
        auto simd_dest_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
        if(args[1].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
            Utils::error(filename, name, "Instruction .ptrmask takes a second argument of type <i64,M> where M is the same as the first argument");
        }
        auto simd_arg_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[1].second);
        if(!Utils::is_int(simd_arg_type->get_basetype(), 64)){
            Utils::error(filename, name, "Instruction .ptrmask takes a second argument of type <i64,M> where M is the same as the first argument");
        }
        if(simd_dest_type->get_size() != simd_arg_type->get_size()){
            Utils::error(filename, name, "Instruction .ptrmask takes a second argument of type <i64,M> where M is the same as the first argument");
        }
        return std::make_shared<MIR::VecIntPtrMaskInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
    }
}
MIR::InstPtr analyze_pause_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction .pause takes no arguments");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .pause has no destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .pause takes no attributes");
    }
    return std::make_shared<MIR::PauseInst>(inst_stmt);
}
MIR::InstPtr analyze_discrete_value_optimizer_hint(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                   std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                                   IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() < 2){
        Utils::error(filename, name, "Discrete value optimizer hint instruction takes at least two arguments");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Discrete value optimizer hint instruction has no destination");
    }
    auto var_name = Utils::get_var_name(args[0].first);
    if(!var_name.has_value()){
        Utils::error(filename, name, "Discrete value optimizer hint instruction takes a variable name as the first argument");
    }
    auto type_expr = args[0].second;
    std::vector<IR::LiteralExprPtr> arg_literals;
    for(size_t i = 1; i < args.size(); i++){
        if(!Utils::type_eq(type_expr, args[i].second)){
            Utils::error(filename, name, "Discrete value optimizer hint instruction takes arguments of the same type");
        }
        if(!Utils::is_constexpr(args[i].first)){
            Utils::error(filename, name, "Discrete value optimizer hint instruction takes const expression arguments");
        }
        arg_literals.push_back(args[i].first->get_literal());
    }
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(Utils::contains_float(type_expr)){
        auto val = Utils::extract_fastmath_attrs(filename,attributes);
        attributes = val.second;
        fast_math_attr = val.first;
    }
    auto [attrs_with_num_args, remaining_attrs] = Utils::extract_attrs_with_num_args<double>(filename, attributes, {"probability"});
    if(attrs_with_num_args["probability"].size() > 1){
        Utils::error(filename, name, "Attribute 'probability' for discrete value optimizer hint instruction takes at most one argument");
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for discrete value optimizer hint instruction: " + remaining_attrs[0]->to_string());
    }
    if(name.value == ".assume"){
        if(attrs_with_num_args["probability"].size() > 0){
            Utils::error(filename, name, "Attribute 'probability' is not supported for .assume instruction");
        }
        return std::make_shared<MIR::AssumeInst>(inst_stmt, var_name.value(), arg_literals, type_expr, fast_math_attr);
    }
    else if(name.value == ".assume_not"){
        if(attrs_with_num_args["probability"].size() > 0){
            Utils::error(filename, name, "Attribute 'probability' is not supported for .assume_not instruction");
        }
        return std::make_shared<MIR::AssumeNotInst>(inst_stmt, var_name.value(), arg_literals, type_expr, fast_math_attr);
    }
    else if(name.value == ".expect"){
        return std::make_shared<MIR::ExpectInst>(inst_stmt, var_name.value(), arg_literals, type_expr, 
                                                 (attrs_with_num_args["probability"].size() == 0 ? std::nullopt : std::make_optional(attrs_with_num_args["probability"][0])), 
                                                 fast_math_attr);
    }
    else if(name.value == ".expect_not"){
        return std::make_shared<MIR::ExpectNotInst>(inst_stmt, var_name.value(), arg_literals, type_expr, 
                                                    (attrs_with_num_args["probability"].size() == 0 ? std::nullopt : std::make_optional(attrs_with_num_args["probability"][0])), 
                                                    fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Unknown discrete value optimizer hint instruction: " + name.value);
    }
}
MIR::InstPtr analyze_range_optimizer_hint(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                          std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                          IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Optimizer range hint instruction takes exactly three arguments");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Optimizer range hint instruction has no destination");
    }
    auto var_name = Utils::get_var_name(args[0].first);
    if(!var_name.has_value()){
        Utils::error(filename, name, "Optimizer range hint instruction takes a variable name as the first argument");
    }
    auto type_expr = args[0].second;
    for(size_t i = 1; i < args.size(); i++){
        if(!Utils::type_eq(type_expr, args[i].second)){
            Utils::error(filename, name, "Optimizer range hint instruction takes arguments of the same type");
        }
        if(!Utils::is_constexpr(args[i].first)){
            Utils::error(filename, name, "Optimizer range hint instruction takes const expression arguments");
        }
    } 
    if(type_expr->get_kind() != IR::TypeExprKind::IntTypeExpr && type_expr->get_kind() != IR::TypeExprKind::FloatTypeExpr){
        Utils::error(filename, name, "Optimizer range hint instruction takes arguments of integer or float type");
    }
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(type_expr->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto val = Utils::extract_fastmath_attrs(filename,attributes);
        attributes = val.second;
        fast_math_attr = val.first;
    }
    auto [attrs_with_num_args, _remaining_attrs] = Utils::extract_attrs_with_num_args<double>(filename, attributes, {"probability"});
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, _remaining_attrs, {"unsigned"});
    if(fast_math_attr.has_value() && flag_attrs["unsigned"]){
        Utils::error(filename, name, "Optimizer range hint instruction cannot have both 'unsigned' and 'fast-math' attributes");
    }
    //TODO:Check if high > low. Will implement later because the size can also be an i128,i256 and so on
    if(attrs_with_num_args["probability"].size() > 1){
        Utils::error(filename, name, "Attribute 'probability' for optimizer range hint instruction takes at most one argument");
    }
    if(attrs_with_num_args["probability"].size() == 1){
        if(attrs_with_num_args["probability"][0] < 0 || attrs_with_num_args["probability"][0] > 1){
            Utils::error(filename, name, "Attribute 'probability' for optimizer range hint instruction takes a value in the range [0, 1]");
        }
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for optimizer range hint instruction: " + remaining_attrs[0]->to_string());
    }
    if(name.value == ".assume_range"){
        if(attrs_with_num_args["probability"].size() > 0){
            Utils::error(filename, name, "Attribute 'probability' is not supported for .assume_range instruction");
        }
        return std::make_shared<MIR::AssumeRangeInst>(inst_stmt, var_name.value(), args[1].first->get_literal(), args[2].first->get_literal(), type_expr, flag_attrs["unsigned"], fast_math_attr);
    }
    else if(name.value == ".assume_not_range"){
        if(attrs_with_num_args["probability"].size() > 0){
            Utils::error(filename, name, "Attribute 'probability' is not supported for .assume_not_range instruction");
        }
        return std::make_shared<MIR::AssumeNotRangeInst>(inst_stmt, var_name.value(), args[1].first->get_literal(), args[2].first->get_literal(), type_expr, flag_attrs["unsigned"], fast_math_attr);
    }
    else if(name.value == ".expect_range"){
        return std::make_shared<MIR::ExpectRangeInst>(inst_stmt, var_name.value(), args[1].first->get_literal(), args[2].first->get_literal(), type_expr, 
                                                      (attrs_with_num_args["probability"].size() == 0 ? std::nullopt : std::make_optional(attrs_with_num_args["probability"][0])), 
                                                      flag_attrs["unsigned"], fast_math_attr);
    }
    else if(name.value == ".expect_not_range"){
        return std::make_shared<MIR::ExpectNotRangeInst>(inst_stmt, var_name.value(), args[1].first->get_literal(), args[2].first->get_literal(), type_expr, 
                                                         (attrs_with_num_args["probability"].size() == 0 ? std::nullopt : std::make_optional(attrs_with_num_args["probability"][0])), 
                                                         flag_attrs["unsigned"], fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Unknown optimizer range hint instruction: " + name.value);
    }
}
MIR::InstPtr analyze_nop_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                              std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                              IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"multi_byte"});
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .nop takes exactly one argument");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .nop has no destination");
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .nop instruction: " + remaining_attrs[0]->to_string());
    }
    auto [size_expr, size_type] = args[0];
    if(!Utils::is_int(size_type,8)){
        Utils::error(filename, size_expr->get_token(), "Instruction .nop takes an integer type argument of size 8 bits");
    }
    if(!Utils::is_constexpr(size_expr)){
        Utils::error(filename, size_expr->get_token(), "Instruction .nop takes a const expression integer type argument");
    }
    auto size_value = Utils::to_numeric<std::uint8_t>(filename, size_expr, size_type, true, true);
    if(size_value < 1 || size_value > 15){
        Utils::error(filename, size_expr->get_token(), "Instruction .nop takes a const expression integer type argument in the range [1, 15]");
    }
    return std::make_shared<MIR::NopInst>(inst_stmt, size_value, flag_attrs["multi_byte"]);
}
MIR::InstPtr analyze_annotation_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                     std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                     IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .annotation takes exactly one argument");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .annotation has no destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .annotation takes no attributes");
    }
    if(!Utils::is_18_array(args[0].second)){
        Utils::error(filename, name, "Instruction .annotation takes an array of 18 elements");
    }
    auto str = Utils::reduce_str_value(args[0].first);
    if(!str.has_value()){
        Utils::error(filename, name, "Instruction .annotation takes a const expression string literal argument");
    }
    return std::make_shared<MIR::AnnotationInst>(inst_stmt, str.value());
}
MIR::InstPtr analyze_endbr64_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                  std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                  IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction .endbr64 takes no arguments");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .endbr64 has no destination");    
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .endbr64 takes no attributes");
    }
    return std::make_shared<MIR::Endbr64Inst>(inst_stmt);
}
MIR::InstPtr analyze_launder_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                  std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                  IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .launder takes exactly one argument");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .launder requires a destination argument");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .launder takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .launder takes a pointer type argument");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .launder requires a pointer type destination");
    }
    return std::make_shared<MIR::LaunderInst>(inst_stmt, dest, args[0].first->get_literal());
}
MIR::InstPtr analyze_strip_invariant_group_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .strip_invariant_group takes exactly one argument");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .strip_invariant_group requires a destination argument");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .strip_invariant_group takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .strip_invariant_group takes a pointer type argument");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .strip_invariant_group requires a pointer type destination");
    }
    return std::make_shared<MIR::StripInvariantGroupInst>(inst_stmt, dest, args[0].first->get_literal());
}
}
}