#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <cstdint>
#include <iostream>
#include <functional>
#include <memory>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                    IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_ret_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                              std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                              IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_unreachable_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                                      std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                      IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_trap_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                               std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                               IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_br_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                             std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                             IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_switch_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_indirectbr_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                                     std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                     IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_terminator_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".ret", analyze_ret_inst},
        {".unreachable", analyze_unreachable_inst},
        {".trap", analyze_trap_inst},
        {".br", analyze_br_inst},
        {".switch", analyze_switch_inst},
        {".indirectbr", analyze_indirectbr_inst}
    };
    auto args = inst_stmt->get_value()->get_operands();
    auto dest = process_local_dest_arg(inst_stmt);
    if(dest != nullptr){
        Utils::error(this->filename, name, "Terminator instruction " + name.value + " does not require a destination argument");
    }
    for(size_t i = 0; i < args.size(); i++){
        args[i].second = Utils::get_reduced_type(this->type_symtable,args[i].second);
        if(!Utils::type_compatible(this->var_symtable, args[i].second,args[i].first)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->get_token().value + " is not compatible with assigned type " + args[i].second->to_string());
        }
    }

    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename, this->curr_func_ret_type,this->var_symtable,name,args,inst_stmt);
    }
    else{
        std::cerr << "Unknown terminator instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_ret_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                              std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                              IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() > 1){
        Utils::error(filename, name, "Instruction .ret takes at most one argument");
    }
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"noreturn"});
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    std::optional<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> ret_value = std::nullopt;
    if(args.size() == 0){
        if(curr_func_ret_type->get_kind() != IR::TypeExprKind::VoidTypeExpr && !flag_attrs["noreturn"]){
            Utils::error(filename, name, "Instruction .ret takes no arguments only if the current function return type is void");
        }
    }
    else{
        if(args[0].second->get_kind() == IR::TypeExprKind::StrTypeExpr){
            auto [reduced_type, str_value] = Utils::reduce_str_value_and_type(var_symtable, args[0].second, args[0].first);
            if(reduced_type == nullptr){
                Utils::error(filename, name, "Unable to resolve the string type for the argument of instruction .ret.");
            }
            args[0].second = reduced_type;
        }
        if(!Utils::type_eq(curr_func_ret_type, args[0].second)){
            Utils::error(filename, name, "Instruction .ret takes an argument of the same type as the current function return type");
        }
        auto type_varient = MIR::get_type_variant_from_type(args[0].second);
        if(type_varient.has_value()){
            if(MIR::is_float_typevariant(type_varient.value())){
                auto val = Utils::extract_fastmath_attrs(filename,attributes);
                remaining_attrs = val.second;
                fast_math_attr = val.first;
            }
        }
        ret_value = std::make_pair(args[0].second, args[0].first->get_literal());
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .ret instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::RetInst>(inst_stmt, ret_value, flag_attrs["noreturn"], fast_math_attr);
}
MIR::InstPtr analyze_unreachable_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                                      std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                      IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction .unreachable takes no arguments");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .unreachable takes no attributes");
    }
    return std::make_shared<MIR::UnreachableInst>(inst_stmt);
}
MIR::InstPtr analyze_trap_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                               std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                               IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction .trap takes no arguments");
    }
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"breakpoint"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .trap instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::TrapInst>(inst_stmt, flag_attrs["breakpoint"]);
}

std::pair<std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>>, bool> get_label_args(std::string filename, Utils::VarSymTablePtr var_symtable, 
                                                                                           IR::TypeExprPtr label_type, IR::TypeExprPtr arg_types, IR::ExprPtr _args){
    std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> label_args;
    auto args = _args->get_literal();
    if(label_type->get_kind() != IR::TypeExprKind::LabelTypeExpr){
        Utils::error(filename, label_type->get_token(), "Expected a label type expression");
    }
    if(arg_types->get_kind() != IR::TypeExprKind::StructTypeExpr){
        Utils::error(filename, arg_types->get_token(), "Expected a struct type expression for label argument types");
    }
    if(args->get_kind() != IR::LiteralKind::StructLiteralExpr){
        Utils::error(filename, args->get_token(), "Expected a struct literal expression for label arguments");
    }
    auto label_type_expr_param = std::dynamic_pointer_cast<IR::LabelTypeExpr>(label_type)->get_params();
    auto arg_types_struct_fields = std::dynamic_pointer_cast<IR::StructTypeExpr>(arg_types)->get_fields();
    auto args_struct_fields = std::dynamic_pointer_cast<IR::StructLiteralExpr>(args)->get_fields();
    if(arg_types_struct_fields.size() != label_type_expr_param.size()){
        Utils::error(filename, arg_types->get_token(), "Number of label argument types does not match the number of label arguments");
    }
    bool contains_float_type = false;
    for(size_t i = 0; i < label_type_expr_param.size(); i++){
        auto param_type = label_type_expr_param[i];
        auto arg_type = arg_types_struct_fields[i];
        if(arg_type->get_kind() == IR::TypeExprKind::StrTypeExpr){
            auto [reduced_type, str_value] = Utils::reduce_str_value_and_type(var_symtable, arg_type, _args);
            if(reduced_type == nullptr){
                Utils::error(filename, arg_types->get_token(), "Unable to resolve the string type for the label argument type.");
            }
            arg_type = reduced_type;
        }
        if(!Utils::type_eq(param_type, arg_type)){
            Utils::error(filename, arg_type->get_token(), "Label argument type does not match the label type parameter");
        }
        auto type_varient = MIR::get_type_variant_from_type(param_type);
        if(type_varient.has_value()){
            if(MIR::is_float_typevariant(type_varient.value())){
                contains_float_type = true;
            }
        }
        label_args.push_back(std::make_pair(param_type, args_struct_fields[i]));
    }
    return std::make_pair(label_args, contains_float_type);
}
MIR::InstPtr analyze_br_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                             std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                             IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(args.size() == 2){
        auto block_name = Utils::get_var_name(args[0].first);
        if(!block_name.has_value()){
            Utils::error(filename, name, "Instruction .br takes a block name as the first argument");
        }
        auto block_arg = get_label_args(filename, var_symtable, args[0].second, args[1].second, args[1].first);
        if(block_arg.second){
            auto val = Utils::extract_fastmath_attrs(filename,attributes);
            attributes = val.second;
            fast_math_attr = val.first;
        }
        if(attributes.size() > 0){
            Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for .br instruction: " + attributes[0]->to_string());
        }
        return std::make_shared<MIR::JmpInst>(inst_stmt, block_name.value(), args[0].second, block_arg.first, fast_math_attr);
    }
    else if(args.size() == 5){
        if(!Utils::is_int(args[0].second, 1)){
            Utils::error(filename, name, "Instruction .br takes a i1 type argument as the first argument");
        }
        auto true_block_name = Utils::get_var_name(args[1].first);
        auto false_block_name = Utils::get_var_name(args[3].first);
        if(!true_block_name.has_value()){
            Utils::error(filename, name, "Instruction .br takes a block name as the second argument");
        }
        if(!false_block_name.has_value()){
            Utils::error(filename, name, "Instruction .br takes a block name as the fourth argument");
        }
        auto true_block_arg = get_label_args(filename, var_symtable, args[1].second, args[2].second, args[2].first);
        auto false_block_arg = get_label_args(filename, var_symtable, args[3].second, args[4].second, args[4].first);
        if(true_block_arg.second || false_block_arg.second){
            auto val = Utils::extract_fastmath_attrs(filename,attributes);
            attributes = val.second;
            fast_math_attr = val.first;
        }
        auto [flag_attrs,_remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unpredictable"});
        auto [attrs_with_num_args, remaining_attrs] = Utils::extract_attrs_with_num_args<std::uint64_t>(filename, attributes, {"freq"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .br instruction: " + remaining_attrs[0]->to_string());
        }
        if(attrs_with_num_args["freq"].size() > 0 && flag_attrs["unpredictable"]){
            Utils::error(filename, name, "Instruction .br cannot have both 'freq' and 'unpredictable' attributes");
        } 
        if(attrs_with_num_args["freq"].size() > 0 && attrs_with_num_args["freq"].size() != 2){
            Utils::error(filename, name, "Instruction .br takes a 'freq' attribute for each label argument");
        }
        return std::make_shared<MIR::ConditionalJmpInst>(inst_stmt, true_block_name.value(), false_block_name.value(), 
                                                         args[1].second, args[3].second, true_block_arg.first, false_block_arg.first,
                                                         args[0].first->get_literal(), attrs_with_num_args["freq"], flag_attrs["unpredictable"], fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction .br takes either 2 or 5 arguments");
    }
}
MIR::InstPtr analyze_switch_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args[0].second->get_kind() != IR::TypeExprKind::IntTypeExpr){
        Utils::error(filename, name, "Instruction .switch takes an integer type argument as the first argument");
    }
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    bool has_float_type = false;
    if((args.size()-3) % 3 != 0 || args.size() <= 3){
        Utils::error(filename, name, "Instruction .switch takes 3 + 3n arguments where n >= 1");
    }
    auto default_block_name = Utils::get_var_name(args[1].first);
    if(!default_block_name.has_value()){
        Utils::error(filename, name, "Instruction .switch takes a block name as the second argument");
    }
    auto default_block_arg = get_label_args(filename, var_symtable, args[1].second, args[2].second, args[2].first);
    std::vector<std::string> case_blocks;
    std::vector<std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>>> case_label_args; 
    std::vector<IR::LiteralExprPtr> case_values;
    std::vector<IR::TypeExprPtr> case_label_types;
    for(size_t i = 3; i < args.size(); i += 3){
        if(!Utils::type_eq(args[0].second, args[i].second)){
            Utils::error(filename, args[i].second->get_token(), "Instruction .switch takes case value of the same type as the first argument");
        }
        auto case_block_name = Utils::get_var_name(args[i+1].first);
        if(!case_block_name.has_value()){
            Utils::error(filename, args[i+1].first->get_token(), "Instruction .switch takes a block name as the second argument of each case");
        }
        auto case_block_arg = get_label_args(filename, var_symtable, args[i+1].second, args[i+2].second, args[i+2].first);
        if(case_block_arg.second){
            has_float_type = true;
        }
        case_blocks.push_back(case_block_name.value());
        case_label_args.push_back(case_block_arg.first);
        case_label_types.push_back(args[i+1].second);
        case_values.push_back(args[i].first->get_literal());
    }
    if(has_float_type){
        auto val = Utils::extract_fastmath_attrs(filename,attributes);
        attributes = val.second;
        fast_math_attr = val.first;
    }
    auto [flag_attrs,_remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unpredictable"});
    auto [attrs_with_num_args, remaining_attrs] = Utils::extract_attrs_with_num_args<std::uint64_t>(filename, attributes, {"freq"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .switch instruction: " + remaining_attrs[0]->to_string());
    }
    if(attrs_with_num_args["freq"].size() > 0 && flag_attrs["unpredictable"]){
        Utils::error(filename, name, "Instruction .switch cannot have both 'freq' and 'unpredictable' attributes");
    }
    if(attrs_with_num_args["freq"].size() > 0 && attrs_with_num_args["freq"].size() != case_blocks.size() + 1){
        Utils::error(filename, name, "Instruction .switch takes a 'freq' attribute for each label argument");
    }
    return std::make_shared<MIR::SwitchInst>(inst_stmt, args[0].first->get_literal(), args[0].second, case_blocks, case_label_types, case_label_args, case_values,
                                             default_block_name.value(), args[1].second, default_block_arg.first, 
                                             attrs_with_num_args["freq"], flag_attrs["unpredictable"], fast_math_attr);
    
}
MIR::InstPtr analyze_indirectbr_inst(std::string filename, IR::TypeExprPtr curr_func_ret_type, Utils::VarSymTablePtr var_symtable, IR::Token name,
                                     std::vector<std::pair<IR::ExprPtr, IR::TypeExprPtr>> args,
                                     IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() < 2){
        Utils::error(filename, name, "Instruction .indirectbr takes at least two arguments");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .indirectbr takes a pointer type argument as the first argument");
    }
    std::vector<std::string> label_names;
    for(size_t i = 1; i < args.size(); i++){
        if(args[i].second->get_kind() != IR::TypeExprKind::LabelTypeExpr){
            Utils::error(filename, name, "Instruction .indirectbr takes label type arguments as the second and subsequent arguments");
        }
        auto label_expr = std::dynamic_pointer_cast<IR::LabelTypeExpr>(args[i].second);
        if(label_expr->get_params().size() != 0){
            Utils::error(filename, name, "Instruction .indirectbr takes label type arguments with no parameters as the second and subsequent arguments");
        }
        auto label_name = Utils::get_var_name(args[i].first);
        if(!label_name.has_value()){
            Utils::error(filename, name, "Instruction .indirectbr takes label type arguments with a label name as the value");
        }
        label_names.push_back(label_name.value());
    }
    auto [flag_attrs,_remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unpredictable"});
    auto [attrs_with_num_args, remaining_attrs] = Utils::extract_attrs_with_num_args<std::uint64_t>(filename, attributes, {"freq"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .indirectbr instruction: " + remaining_attrs[0]->to_string());
    }
    if(attrs_with_num_args["freq"].size() > 0 && flag_attrs["unpredictable"]){
        Utils::error(filename, name, "Instruction .indirectbr cannot have both 'freq' and 'unpredictable' attributes");
    }
    if(attrs_with_num_args["freq"].size() > 0 && attrs_with_num_args["freq"].size() != label_names.size()){
        Utils::error(filename, name, "Instruction .indirectbr takes a 'freq' attribute for each label argument");
    }
    return std::make_shared<MIR::IndirectJmpInst>(inst_stmt, args[0].first->get_literal(), label_names, attrs_with_num_args["freq"], flag_attrs["unpredictable"]);
}
}
}