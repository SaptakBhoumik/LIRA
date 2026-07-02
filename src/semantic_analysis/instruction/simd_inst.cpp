#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <cstdint>
#include <iostream>
#include <functional>
#include <memory>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_shufflevector_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                        std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                        IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_ternlog_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                  std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                  IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_splat_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_step_vector_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                      std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                      IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_insert_subvector_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                           std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                           IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_extract_subvector_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                            std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                            IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_active_lane_mask_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                           std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                           IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_addsub_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_reduce_arithmetic_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_reduce_bitwise_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                             std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                             IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_horizontal_arithmetic_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                    IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_horizontal_bitwise_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                 std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                 IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_dot_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                              std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                              IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_sad_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                              std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                              IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_pack_sat_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                   std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                   IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_unpack_lo_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                    IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_unpack_hi_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                    IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_compress_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                   std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                   IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_expand_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_interleave_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                     std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                     IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_deinterleave_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                       std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                       IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_mask_to_int_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                      std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                      IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_int_to_mask_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                      std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                      IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_simd_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".shufflevector", analyze_shufflevector_inst},
        {".ternlog", analyze_ternlog_inst},
        {".splat", analyze_splat_inst},
        {".step_vector", analyze_step_vector_inst},
        {".insert_subvector", analyze_insert_subvector_inst},
        {".extract_subvector", analyze_extract_subvector_inst},
        {".active_lane_mask", analyze_active_lane_mask_inst},
        {".addsub", analyze_addsub_inst},
        {".reduce_add", analyze_reduce_arithmetic_bin_inst},
        {".reduce_mul", analyze_reduce_arithmetic_bin_inst},
        {".reduce_avg", analyze_reduce_arithmetic_bin_inst},
        {".reduce_min", analyze_reduce_arithmetic_bin_inst},
        {".reduce_max", analyze_reduce_arithmetic_bin_inst},
        {".reduce_and", analyze_reduce_bitwise_bin_inst},
        {".reduce_or", analyze_reduce_bitwise_bin_inst},
        {".reduce_xor", analyze_reduce_bitwise_bin_inst},
        {".reduce_xnor", analyze_reduce_bitwise_bin_inst},
        {".hadd", analyze_horizontal_arithmetic_bin_inst},
        {".hsub", analyze_horizontal_arithmetic_bin_inst},
        {".habsdiff", analyze_horizontal_arithmetic_bin_inst},
        {".haddsub", analyze_horizontal_arithmetic_bin_inst},
        {".hmul", analyze_horizontal_arithmetic_bin_inst},
        {".havg", analyze_horizontal_arithmetic_bin_inst},
        {".hmin", analyze_horizontal_arithmetic_bin_inst},
        {".hmax", analyze_horizontal_arithmetic_bin_inst},
        {".hand", analyze_horizontal_bitwise_bin_inst},
        {".hor", analyze_horizontal_bitwise_bin_inst},
        {".hxor", analyze_horizontal_bitwise_bin_inst},
        {".hnand", analyze_horizontal_bitwise_bin_inst},
        {".hnor", analyze_horizontal_bitwise_bin_inst},
        {".hxnor", analyze_horizontal_bitwise_bin_inst},
        {".dot", analyze_dot_inst},
        {".sad", analyze_sad_inst},
        {".pack_sat", analyze_pack_sat_inst},
        {".unpack_lo", analyze_unpack_lo_inst},
        {".unpack_hi", analyze_unpack_hi_inst},
        {".compress", analyze_compress_inst},
        {".expand", analyze_expand_inst},
        {".interleave2", analyze_interleave_inst},
        {".interleave3", analyze_interleave_inst},
        {".interleave4", analyze_interleave_inst},
        {".deinterleave2", analyze_deinterleave_inst},
        {".deinterleave3", analyze_deinterleave_inst},
        {".deinterleave4", analyze_deinterleave_inst},
        {".mask_to_int", analyze_mask_to_int_inst},
        {".int_to_mask", analyze_int_to_mask_inst},
    };
    auto args = inst_stmt->get_value()->get_operands();
    auto dest = process_local_dest_arg(inst_stmt);
    if(dest == nullptr){
        Utils::error(this->filename, name, "Instruction " + name.value + " expects a destination argument, but got none");
    }
    for(size_t i = 0; i < args.size(); i++){
        args[i].second = Utils::get_reduced_type(this->type_symtable,args[i].second);
        if(!Utils::type_compatible(this->var_symtable, args[i].second,args[i].first)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->get_token().value + " is not compatible with assigned type " + args[i].second->to_string());
        }
    }

    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,name,args,inst_stmt);
    }
    else{
        std::cerr << "Unknown simd instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_shufflevector_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                        std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                        IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction shufflevector expects 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction shufflevector expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    std::vector<std::shared_ptr<IR::SIMDTypeExpr>> simd_arg_types;
    for(size_t i = 0; i < args.size(); i++){
        if(args[i].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
            Utils::error(filename, name, "Instruction shufflevector expects the argument " + std::to_string(i) + " to be of simd type, but got " + args[i].second->to_string());
        }
        simd_arg_types.push_back(std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[i].second));
    }
    if(dest_simd_type->get_size() != simd_arg_types[2]->get_size()){
        Utils::error(filename, name, "Instruction shufflevector expects the destination simd type to have the same size as the third argument simd type, but got destination size " + std::to_string(dest_simd_type->get_size()) + " and third argument size " + std::to_string(simd_arg_types[2]->get_size()));
    }
    if(dest_simd_type->get_size() > simd_arg_types[0]->get_size() || dest_simd_type->get_size() > simd_arg_types[1]->get_size()){
        Utils::error(filename, name, "Instruction shufflevector expects the destination simd type to have size less than or equal to the first and second argument simd types, but got destination size " + std::to_string(dest_simd_type->get_size()) + ", first argument size " + std::to_string(simd_arg_types[0]->get_size()) + ", and second argument size " + std::to_string(simd_arg_types[1]->get_size()));
    }
    if(!Utils::type_eq(dest_simd_type->get_basetype(), simd_arg_types[0]->get_basetype())){
        Utils::error(filename, name, "Instruction shufflevector expects the destination simd type to have the same base type as the first argument simd type, but got destination base type " + dest_simd_type->get_basetype()->to_string() + " and first argument base type " + simd_arg_types[0]->get_basetype()->to_string());
    }
    if(!Utils::type_eq(dest_simd_type->get_basetype(), simd_arg_types[1]->get_basetype())){
        Utils::error(filename, name, "Instruction shufflevector expects the destination simd type to have the same base type as the second argument simd type, but got destination base type " + dest_simd_type->get_basetype()->to_string() + " and second argument base type " + simd_arg_types[1]->get_basetype()->to_string());
    }
    if(!Utils::is_int(simd_arg_types[2]->get_basetype(), 64)){
        Utils::error(filename, name, "Instruction shufflevector expects the third argument simd type to have base type of i64, but got " + simd_arg_types[2]->get_basetype()->to_string());
    }
    if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction shufflevector takes no attributes when the destination simd type has integer base type");
        }
        return std::make_shared<MIR::IntShuffleVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), simd_arg_types[0]->get_size(), simd_arg_types[1]->get_size());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::PtrTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction shufflevector takes no attributes when the destination simd type has pointer base type");
        }
        return std::make_shared<MIR::PtrShuffleVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), simd_arg_types[0]->get_size(), simd_arg_types[1]->get_size());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for shufflevector instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatShuffleVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), simd_arg_types[0]->get_size(), simd_arg_types[1]->get_size(), fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction shufflevector expects the destination simd type to have base type of integer, float, or pointer, but got " + dest_simd_type->get_basetype()->to_string());
    }

}
MIR::InstPtr analyze_ternlog_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                  std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                  IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 4){
        Utils::error(filename, name, "Instruction ternlog expects 4 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction ternlog expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    if(!Utils::is_int(dest_simd_type->get_basetype(), 1)){
        Utils::error(filename, name, "Instruction ternlog expects the destination simd type to have base type of i1, but got " + dest_simd_type->get_basetype()->to_string());
    }
    for(size_t i = 0; i < 3; i++){
        if(!Utils::type_eq(dest_simd_type, args[i].second)){
            Utils::error(filename, name, "Instruction ternlog expects the argument " + std::to_string(i) + " to have the same type as the destination simd type, but got argument type " + args[i].second->to_string() + " and destination type " + dest_simd_type->to_string());
        }
    }
    if(!Utils::is_int(args[3].second, 8)){
        Utils::error(filename, name, "Instruction ternlog expects the fourth argument to be of type i8, but got " + args[3].second->to_string());
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction ternlog takes no attributes");
    }
    return std::make_shared<MIR::TernLogInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), args[3].first->get_literal());
}
MIR::InstPtr analyze_splat_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction splat expects 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction splat expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    if(!Utils::type_eq(dest_simd_type->get_basetype(), args[0].second)){
        Utils::error(filename, name, "Instruction splat expects the argument to have the same base type as the destination simd type, but got argument base type " + args[0].second->to_string() + " and destination base type " + dest_simd_type->get_basetype()->to_string());
    }
    if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction splat takes no attributes when the destination simd type has integer base type");
        }
        return std::make_shared<MIR::IntSplatInst>(inst_stmt, dest, args[0].first->get_literal());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::PtrTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction splat takes no attributes when the destination simd type has pointer base type");
        }
        return std::make_shared<MIR::PtrSplatInst>(inst_stmt, dest, args[0].first->get_literal());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for splat instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatSplatInst>(inst_stmt, dest, args[0].first->get_literal(), fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction splat expects the destination simd type to have base type of integer, float, or pointer, but got " + dest_simd_type->get_basetype()->to_string());
    }
}
MIR::InstPtr analyze_step_vector_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                      std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                      IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction step_vector expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction step_vector expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    if(!Utils::type_eq(dest_simd_type->get_basetype(), args[0].second)){
        Utils::error(filename, name, "Instruction step_vector expects the first argument to have the same base type as the destination simd type, but got first argument base type " + args[0].second->to_string() + " and destination base type " + dest_simd_type->get_basetype()->to_string());
    }
    if(!Utils::type_eq(dest_simd_type->get_basetype(), args[1].second)){
        Utils::error(filename, name, "Instruction step_vector expects the second argument to have the same base type as the destination simd type, but got second argument base type " + args[1].second->to_string() + " and destination base type " + dest_simd_type->get_basetype()->to_string());
    }
    if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction step_vector takes no attributes when the destination simd type has integer base type");
        }
        return std::make_shared<MIR::IntStepVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for step_vector instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatStepVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction step_vector expects the destination simd type to have base type of integer or float, but got " + dest_simd_type->get_basetype()->to_string());
    }
}
MIR::InstPtr analyze_insert_subvector_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                           std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                           IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction insert_subvector expects 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction insert_subvector expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    if(!Utils::type_eq(dest->get_type(), args[0].second)){
        Utils::error(filename, name, "Instruction insert_subvector expects the first argument to have the same base type as the destination simd type, but got first argument base type " + args[0].second->to_string() + " and destination base type " + dest_simd_type->get_basetype()->to_string());
    }
    if(!Utils::type_eq(dest_simd_type->get_basetype(), args[1].second)){
        Utils::error(filename, name, "Instruction insert_subvector expects the second argument to have the same base type as the destination simd type, but got second argument base type " + args[1].second->to_string() + " and destination base type " + dest_simd_type->get_basetype()->to_string());
    }
    auto arg1_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[1].second);
    if(dest_simd_type->get_size() < arg1_simd_type->get_size()){
        Utils::error(filename, name, "Instruction insert_subvector expects the destination simd type to have size greater than or equal to the second argument simd type, but got destination size " + std::to_string(dest_simd_type->get_size()) + " and second argument size " + std::to_string(arg1_simd_type->get_size()));
    }
    if(!Utils::is_int(args[2].second, 64)){
        Utils::error(filename, name, "Instruction insert_subvector expects the third argument to be of type i64, but got " + args[2].second->to_string());
    }
    if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction insert_subvector takes no attributes when the destination simd type has integer base type");
        }
        return std::make_shared<MIR::IntInsertSubVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), arg1_simd_type->get_size());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::PtrTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction insert_subvector takes no attributes when the destination simd type has pointer base type");
        }
        return std::make_shared<MIR::PtrInsertSubVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), arg1_simd_type->get_size());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for insert_subvector instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatInsertSubVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), arg1_simd_type->get_size(), fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction insert_subvector expects the destination simd type to have base type of integer, float, or pointer, but got " + dest_simd_type->get_basetype()->to_string());
    }

}
MIR::InstPtr analyze_extract_subvector_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                            std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                            IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction extract_subvector expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction extract_subvector expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction extract_subvector expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    if(!Utils::type_eq(dest_simd_type->get_basetype(), arg0_simd_type->get_basetype())){
        Utils::error(filename, name, "Instruction extract_subvector expects the destination simd type to have the same base type as the first argument simd type, but got destination base type " + dest_simd_type->get_basetype()->to_string() + " and first argument base type " + arg0_simd_type->get_basetype()->to_string());
    }
    if(dest_simd_type->get_size() > arg0_simd_type->get_size()){
        Utils::error(filename, name, "Instruction extract_subvector expects the destination simd type to have size less than or equal to the first argument simd type, but got destination size " + std::to_string(dest_simd_type->get_size()) + " and first argument size "+ std::to_string(arg0_simd_type->get_size()));
    }
    if(!Utils::is_int(args[1].second, 64)){
        Utils::error(filename, name, "Instruction extract_subvector expects the second argument to be of type i64, but got " + args[1].second->to_string());
    }
    if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction extract_subvector takes no attributes when the destination simd type has integer base type");
        }
        return std::make_shared<MIR::IntExtractSubVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), arg0_simd_type->get_size());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::PtrTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction extract_subvector takes no attributes when the destination simd type has pointer base type");
        }
        return std::make_shared<MIR::PtrExtractSubVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), arg0_simd_type->get_size());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for extract_subvector instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatExtractSubVectorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), arg0_simd_type->get_size(), fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction extract_subvector expects the destination simd type to have base type of integer, float, or pointer, but got " + dest_simd_type->get_basetype()->to_string());
    }
}
MIR::InstPtr analyze_active_lane_mask_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                           std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                           IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction active_lane_mask expects 0 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction active_lane_mask expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    if(!Utils::is_int(dest_simd_type->get_basetype(), 1)){
        Utils::error(filename, name, "Instruction active_lane_mask expects the destination simd type to have base type of i1, but got " + dest_simd_type->get_basetype()->to_string());
    }
    if(!Utils::type_eq(args[0].second, args[1].second)){
        Utils::error(filename, name, "Instruction active_lane_mask expects the first and second arguments to have the same type, but got first argument type " + args[0].second->to_string() + " and second argument type " + args[1].second->to_string());
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::IntTypeExpr){
        Utils::error(filename, name, "Instruction active_lane_mask expects the first and second arguments to be of integer type, but got first argument type " + args[0].second->to_string() + " and second argument type " + args[1].second->to_string());
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"unsigned"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for active_lane_mask instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::ActiveLaneMaskInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[0].second, flag_attrs["unsigned"]);
}
MIR::InstPtr analyze_addsub_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction addsub expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction addsub expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < 2; i++){
        if(!Utils::type_eq(dest->get_type(), args[i].second)){
            Utils::error(filename, name, "Instruction addsub expects the argument " + std::to_string(i) + " to have the same type as the destination simd type, but got argument type " + args[i].second->to_string() + " and destination type " + dest->get_type()->to_string());
        }
    }
    auto typevarient = MIR::get_type_variant_from_type(dest->get_type()).value();//We know it is a vector. Vector only valid for int/float/ptr. So it must have a value in which we can classify
    if(typevarient == MIR::TypeVariant::VecInt){
        auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"nuw","nsw","unsigned","saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for addsub instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntAddSubInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["saturating"]);
    }
    else if(typevarient == MIR::TypeVariant::VecFloat){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for addsub instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatAddSubInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction addsub expects the destination simd type to have base type of integer, or float, but got " + dest->get_type()->to_string());
    }
}
MIR::InstPtr analyze_reduce_arithmetic_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_reduce_bitwise_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                             std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                             IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_horizontal_arithmetic_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                    IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_horizontal_bitwise_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                 std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                 IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_dot_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                              std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                              IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_sad_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                              std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                              IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_pack_sat_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                   std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                   IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_unpack_lo_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                    IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_unpack_hi_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                    IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_compress_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                   std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                   IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_expand_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_interleave_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                     std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                     IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_deinterleave_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                       std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                       IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
}
MIR::InstPtr analyze_mask_to_int_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                      std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                      IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction mask_to_int expects 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::IntTypeExpr){
        Utils::error(filename, name, "Instruction mask_to_int expects the destination argument to be of integer type, but got " + dest->get_type()->to_string());
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction mask_to_int expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    if(!Utils::is_int(arg0_simd_type->get_basetype(), 1)){
        Utils::error(filename, name, "Instruction mask_to_int expects the first argument simd type to have base type of i1, but got " + arg0_simd_type->get_basetype()->to_string());
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction mask_to_int takes no attributes");
    }
    return std::make_shared<MIR::MaskToIntInst>(inst_stmt, dest, args[0].first->get_literal(), args[0].second);
}
MIR::InstPtr analyze_int_to_mask_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                      std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                      IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction int_to_mask expects 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction int_to_mask expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    if(!Utils::is_int(dest_simd_type->get_basetype(), 1)){
        Utils::error(filename, name, "Instruction int_to_mask expects the destination simd type to have base type of i1, but got " + dest_simd_type->get_basetype()->to_string());
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::IntTypeExpr){
        Utils::error(filename, name, "Instruction int_to_mask expects the first argument to be of integer type, but got " + args[0].second->to_string());
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction int_to_mask takes no attributes");
    }
    return std::make_shared<MIR::IntToMaskInst>(inst_stmt, dest, args[0].first->get_literal(), args[0].second);
}
}
}