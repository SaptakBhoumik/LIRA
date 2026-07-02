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
    if(args[1].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction insert_subvector expects the second argument to be of simd type, but got " + args[1].second->to_string());
    }
    auto arg1_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[1].second);
    if(!Utils::type_eq(dest_simd_type->get_basetype(), arg1_simd_type->get_basetype())){
        Utils::error(filename, name, "Instruction insert_subvector expects the second argument to have the same base type as the destination simd type, but got second argument base type " + args[1].second->to_string() + " and destination base type " + dest_simd_type->get_basetype()->to_string());
    }
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
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction active_lane_mask expects 2 arguments, but got " + std::to_string(args.size()));
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
    if(args.size() != 1 && args.size() != 2){
        Utils::error(filename, name, "Instruction " + name.value + " expects 1 or 2 arguments, but got " + std::to_string(args.size()));
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction " + name.value + " expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    if(!Utils::type_eq(dest->get_type(), arg0_simd_type->get_basetype())){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination type to be the same as the base type of the first argument, but got destination type " + dest->get_type()->to_string() + " and first argument base type " + arg0_simd_type->get_basetype()->to_string());
    }
    IR::LiteralExprPtr mask_literal = nullptr;
    if(args.size() == 2){
        if(!Utils::is_vector_of_int(args[1].second, 1, arg0_simd_type->get_size())){
            Utils::error(filename, name, "Instruction " + name.value + " expects the second argument to be of type <i1,N> where N is the same as the first argument's size");
        }
        mask_literal = args[1].first->get_literal();
    }
    if(dest->get_type()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        if(name.value == ".reduce_min"){
            auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"unsigned"});
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for reduce_min instruction: " + remaining_attrs[0]->to_string());
            }
            return std::make_shared<MIR::IntReduceMinInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), flag_attrs["unsigned"]);
        }
        else if(name.value == ".reduce_max"){
            auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"unsigned"});
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for reduce_max instruction: " + remaining_attrs[0]->to_string());
            }
            return std::make_shared<MIR::IntReduceMaxInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), flag_attrs["unsigned"]);
        }
        else if(name.value == ".reduce_avg"){
            auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"nuw","nsw","unsigned","floor"});
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for reduce_avg instruction: " + remaining_attrs[0]->to_string());
            }
            return std::make_shared<MIR::IntReduceAvgInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["floor"]);
        }
        else if(name.value == ".reduce_add"){
            auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"nuw","nsw","unsigned","saturating"});
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for reduce_add instruction: " + remaining_attrs[0]->to_string());
            }
            return std::make_shared<MIR::IntReduceAddInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["saturating"]);
        }
        else if(name.value == ".reduce_mul"){
            auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"nuw","nsw","unsigned","saturating"});
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for reduce_mul instruction: " + remaining_attrs[0]->to_string());
            }
            return std::make_shared<MIR::IntReduceMulInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["saturating"]);
        }
        else{
            Utils::error(filename, name, "Unknown reduce arithmetic instruction: " + name.value);
        }
    }
    else if(dest->get_type()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        if(name.value == ".reduce_min" || name.value == ".reduce_max"){
            auto [fast_math_attr, remaining_attrs1] = Utils::extract_fastmath_attrs(filename, attributes);
            auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, remaining_attrs1, {"unordered","ieee754_2019"});
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for " + name.value + " instruction: " + remaining_attrs[0]->to_string());
            }
            if(name.value == ".reduce_min"){
                return std::make_shared<MIR::FloatReduceMinInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), fast_math_attr, flag_attrs["ieee754_2019"], flag_attrs["unordered"]);
            }
            else{
                return std::make_shared<MIR::FloatReduceMaxInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), fast_math_attr, flag_attrs["ieee754_2019"], flag_attrs["unordered"]);
            }
        }
        else{
            auto [fast_math_attr, remaining_attrs] = Utils::extract_fastmath_attrs(filename, attributes);
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for " + name.value + " instruction: " + remaining_attrs[0]->to_string());
            }
            if(name.value == ".reduce_add"){
                return std::make_shared<MIR::FloatReduceAddInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), fast_math_attr);
            }
            else if(name.value == ".reduce_mul"){
                return std::make_shared<MIR::FloatReduceMulInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), fast_math_attr);
            }
            else if(name.value == ".reduce_avg"){
                return std::make_shared<MIR::FloatReduceAvgInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), fast_math_attr);
            }
            else{
                Utils::error(filename, name, "Unknown reduce arithmetic instruction: " + name.value);
            }
        }
    }
    else{
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination type to be integer or float, but got " + dest->get_type()->to_string());
    }
}
MIR::InstPtr analyze_reduce_bitwise_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                             std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                             IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1 && args.size() != 2){
        Utils::error(filename, name, "Instruction " + name.value + " expects 1 or 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::IntTypeExpr){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination argument to be of integer type, but got " + dest->get_type()->to_string());
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction " + name.value + " expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    if(!Utils::type_eq(dest->get_type(), arg0_simd_type->get_basetype())){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination type to be the same as the base type of the first argument, but got destination type " + dest->get_type()->to_string() + " and first argument base type " + arg0_simd_type->get_basetype()->to_string());
    }
    IR::LiteralExprPtr mask_literal = nullptr;
    if(args.size() == 2){
        if(!Utils::is_vector_of_int(args[1].second, 1, arg0_simd_type->get_size())){
            Utils::error(filename, name, "Instruction " + name.value + " expects the second argument to be of type <i1,N> where N is the same as the first argument's size");
        }
        mask_literal = args[1].first->get_literal();
    }
    if(name.value == ".reduce_and"){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction reduce_and takes no attributes");
        }
        return std::make_shared<MIR::IntReduceAndInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size());
    }
    else if(name.value == ".reduce_or"){
        auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"disjoint"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for reduce_or instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntReduceOrInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size(), flag_attrs["disjoint"]);
    }
    else if(name.value == ".reduce_xor"){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction reduce_xor takes no attributes");
        }
        return std::make_shared<MIR::IntReduceXorInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size());
    }
    else if(name.value == ".reduce_xnor"){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction reduce_xnor takes no attributes");
        }
        return std::make_shared<MIR::IntReduceXnorInst>(inst_stmt, dest, args[0].first->get_literal(), mask_literal, arg0_simd_type->get_size());
    }
    else{
        Utils::error(filename, name, "Unknown reduce bitwise instruction: " + name.value);
    }
}
MIR::InstPtr analyze_horizontal_arithmetic_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                    IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction " + name.value + " expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    for(size_t i = 0; i < 2; i++){
        if(!Utils::type_eq(dest->get_type(), args[i].second)){
            Utils::error(filename, name, "Instruction " + name.value + " expects the argument " + std::to_string(i) + " to have the same type as the destination simd type, but got argument type " + args[i].second->to_string() + " and destination type " + dest->get_type()->to_string());
        }
    }
    if(dest_simd_type->get_size() % 2 != 0){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination simd type to have an even number of elements, but got " + std::to_string(dest_simd_type->get_size()));
    }
    auto typevarient = MIR::get_type_variant_from_type(dest->get_type()).value();
    if(typevarient == MIR::TypeVariant::VecInt){
        if(name.value == ".hmin" || name.value == ".hmax"){
            auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"unsigned"});
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for " + name.value + " instruction: " + remaining_attrs[0]->to_string());
            }
            if(name.value == ".hmin"){
                return std::make_shared<MIR::IntHorizontalMinInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["unsigned"]);
            }
            else{
                return std::make_shared<MIR::IntHorizontalMaxInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["unsigned"]);
            }
        }
        else if(name.value == ".havg"){
            auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"nuw","nsw","unsigned","floor"});
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for havg instruction: " + remaining_attrs[0]->to_string());
            }
            return std::make_shared<MIR::IntHorizontalAvgInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["floor"]);
        }
        else{
            auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"nuw","nsw","unsigned","saturating"});
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for " + name.value + " instruction: " + remaining_attrs[0]->to_string());
            }
            if(name.value == ".hadd"){
                return std::make_shared<MIR::IntHorizontalAddInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["saturating"]);
            }
            else if(name.value == ".hsub"){
                return std::make_shared<MIR::IntHorizontalSubInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["saturating"]);
            }
            else if(name.value == ".habsdiff"){
                return std::make_shared<MIR::IntHorizontalAbsDiffInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["saturating"]);
            }
            else if(name.value == ".haddsub"){
                return std::make_shared<MIR::IntHorizontalAddSubInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["saturating"]);
            }
            else if(name.value == ".hmul"){
                return std::make_shared<MIR::IntHorizontalMulInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["saturating"]);
            }
            else{
                Utils::error(filename, name, "Unknown horizontal arithmetic instruction: " + name.value);
            }
        }
    }
    else if(typevarient == MIR::TypeVariant::VecFloat){
        if(name.value == ".hmin" || name.value == ".hmax"){
            auto [fast_math_attr, remaining_attrs1] = Utils::extract_fastmath_attrs(filename, attributes);
            auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, remaining_attrs1, {"unordered","ieee754_2019"});
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for " + name.value + " instruction: " + remaining_attrs[0]->to_string());
            }
            if(name.value == ".hmin"){
                return std::make_shared<MIR::FloatHorizontalMinInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), fast_math_attr, flag_attrs["ieee754_2019"], flag_attrs["unordered"]);
            }
            else{
                return std::make_shared<MIR::FloatHorizontalMaxInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), fast_math_attr, flag_attrs["ieee754_2019"], flag_attrs["unordered"]);
            }
        }
        else{
            auto [fast_math_attr, remaining_attrs] = Utils::extract_fastmath_attrs(filename, attributes);
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for " + name.value + " instruction: " + remaining_attrs[0]->to_string());
            }
            if(name.value == ".hadd"){
                return std::make_shared<MIR::FloatHorizontalAddInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), fast_math_attr);
            }
            else if(name.value == ".hsub"){
                return std::make_shared<MIR::FloatHorizontalSubInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), fast_math_attr);
            }
            else if(name.value == ".habsdiff"){
                return std::make_shared<MIR::FloatHorizontalAbsDiffInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), fast_math_attr);
            }
            if(name.value == ".haddsub"){
                return std::make_shared<MIR::FloatHorizontalAddSubInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), fast_math_attr);
            }
            else if(name.value == ".hmul"){
                return std::make_shared<MIR::FloatHorizontalMulInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), fast_math_attr);
            }
            else if(name.value == ".havg"){
                return std::make_shared<MIR::FloatHorizontalAvgInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), fast_math_attr);
            }
            else{
                Utils::error(filename, name, "Unknown horizontal arithmetic instruction: " + name.value);
            }
        }
    }
    else{
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination simd type to have base type of integer or float, but got " + dest->get_type()->to_string());
    }
}
MIR::InstPtr analyze_horizontal_bitwise_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                 std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                 IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction " + name.value + " expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    if(dest_simd_type->get_basetype()->get_kind() != IR::TypeExprKind::IntTypeExpr){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination simd type to have base type of integer, but got " + dest_simd_type->get_basetype()->to_string());
    }
    for(size_t i = 0; i < 2; i++){
        if(!Utils::type_eq(dest->get_type(), args[i].second)){
            Utils::error(filename, name, "Instruction " + name.value + " expects the argument " + std::to_string(i) + " to have the same type as the destination simd type, but got argument type " + args[i].second->to_string() + " and destination type " + dest->get_type()->to_string());
        }
    }
    if(name.value == ".hand"){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction hand takes no attributes");
        }
        return std::make_shared<MIR::IntHorizontalAndInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
    }
    else if(name.value == ".hnand"){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction hnand takes no attributes");
        }
        return std::make_shared<MIR::IntHorizontalNandInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
    }
    else if(name.value == ".hor"){
        auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"disjoint"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for hor instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntHorizontalOrInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["disjoint"]);
    }
    else if(name.value == ".hnor"){
        auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"disjoint"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for hnor instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntHorizontalNorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["disjoint"]);
    }
    else if(name.value == ".hxor"){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction hxor takes no attributes");
        }
        return std::make_shared<MIR::IntHorizontalXorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
    }
    else if(name.value == ".hxnor"){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction hxnor takes no attributes");
        }
        return std::make_shared<MIR::IntHorizontalXnorInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
    }
    else{
        Utils::error(filename, name, "Unknown horizontal bitwise instruction: " + name.value);
    }
}
MIR::InstPtr analyze_dot_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                              std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                              IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2 && args.size() != 3){
        Utils::error(filename, name, "Instruction dot expects 2 or 3 arguments, but got " + std::to_string(args.size()));
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction dot expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    if(!Utils::type_eq(args[0].second, args[1].second)){
        Utils::error(filename, name, "Instruction dot expects the first and second arguments to have the same type, but got first argument type " + args[0].second->to_string() + " and second argument type " + args[1].second->to_string());
    }
    IR::LiteralExprPtr acc = nullptr;
    if(args.size() == 3){
        if(!Utils::type_eq(dest->get_type(), args[2].second)){
            Utils::error(filename, name, "Instruction dot expects the third argument to have the same type as the destination, but got third argument type " + args[2].second->to_string() + " and destination type " + dest->get_type()->to_string());
        }
        acc = args[2].first->get_literal();
    }
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    if(Utils::get_type_size(arg0_simd_type->get_basetype()) > Utils::get_type_size(dest->get_type())){
        Utils::error(filename, name, "Instruction dot expects the destination type to have bitwidth greater than or equal to the input vector base type bitwidth");
    }
    if(arg0_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        if(dest->get_type()->get_kind() != IR::TypeExprKind::IntTypeExpr){
            Utils::error(filename, name, "Instruction dot expects the destination type to be integer when the input vector base type is integer, but got " + dest->get_type()->to_string());
        }
        if(!Utils::type_ge(filename, dest->get_type(), arg0_simd_type->get_basetype())){
            Utils::error(filename, name, "Instruction dot expects the destination type bitwidth to be greater than or equal to the input vector base type bitwidth");
        }
        auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"unsigned","nsw","nuw","saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for dot instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntDotInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), acc, args[0].second, flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["saturating"]);
    }
    else if(arg0_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        if(dest->get_type()->get_kind() != IR::TypeExprKind::FloatTypeExpr){
            Utils::error(filename, name, "Instruction dot expects the destination type to be float when the input vector base type is float, but got " + dest->get_type()->to_string());
        }
        if(!Utils::type_ge(filename, dest->get_type(), arg0_simd_type->get_basetype())){
            Utils::error(filename, name, "Instruction dot expects the destination type bitwidth to be greater than or equal to the input vector base type bitwidth");
        }
        auto [fast_math_attr, remaining_attrs] = Utils::extract_fastmath_attrs(filename, attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for dot instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatDotInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), acc, args[0].second, fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction dot expects the input vector base type to be integer or float, but got " + arg0_simd_type->get_basetype()->to_string());
    }
}
MIR::InstPtr analyze_sad_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                              std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                              IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2 && args.size() != 3){
        Utils::error(filename, name, "Instruction sad expects 2 or 3 arguments, but got " + std::to_string(args.size()));
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction sad expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    if(!Utils::type_eq(args[0].second, args[1].second)){
        Utils::error(filename, name, "Instruction sad expects the first and second arguments to have the same type, but got first argument type " + args[0].second->to_string() + " and second argument type " + args[1].second->to_string());
    }
    IR::LiteralExprPtr acc = nullptr;
    if(args.size() == 3){
        if(!Utils::type_eq(dest->get_type(), args[2].second)){
            Utils::error(filename, name, "Instruction sad expects the third argument to have the same type as the destination, but got third argument type " + args[2].second->to_string() + " and destination type " + dest->get_type()->to_string());
        }
        acc = args[2].first->get_literal();
    }
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    if(Utils::get_type_size(arg0_simd_type->get_basetype()) > Utils::get_type_size(dest->get_type())){
        Utils::error(filename, name, "Instruction sad expects the destination type to have bitwidth greater than or equal to the input vector base type bitwidth");
    }
    if(arg0_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        if(dest->get_type()->get_kind() != IR::TypeExprKind::IntTypeExpr){
            Utils::error(filename, name, "Instruction sad expects the destination type to be integer when the input vector base type is integer, but got " + dest->get_type()->to_string());
        }
        auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"unsigned","nsw","nuw","saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for sad instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntSADInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), acc, args[0].second, flag_attrs["nuw"], flag_attrs["nsw"], flag_attrs["unsigned"], flag_attrs["saturating"]);
    }
    else if(arg0_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        if(dest->get_type()->get_kind() != IR::TypeExprKind::FloatTypeExpr){
            Utils::error(filename, name, "Instruction sad expects the destination type to be float when the input vector base type is float, but got " + dest->get_type()->to_string());
        }
        if(!Utils::type_ge(filename, dest->get_type(), arg0_simd_type->get_basetype())){
            Utils::error(filename, name, "Instruction sad expects the destination type bitwidth to be greater than or equal to the input vector base type bitwidth");
        }
        auto [fast_math_attr, remaining_attrs] = Utils::extract_fastmath_attrs(filename, attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for sad instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatSADInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), acc, args[0].second, fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction sad expects the input vector base type to be integer or float, but got " + arg0_simd_type->get_basetype()->to_string());
    }
}
MIR::InstPtr analyze_pack_sat_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                   std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                   IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction pack_sat expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction pack_sat expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction pack_sat expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    if(!Utils::type_eq(args[0].second, args[1].second)){
        Utils::error(filename, name, "Instruction pack_sat expects the first and second arguments to have the same type, but got first argument type " + args[0].second->to_string() + " and second argument type " + args[1].second->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    if(dest_simd_type->get_basetype()->get_kind() != IR::TypeExprKind::IntTypeExpr || arg0_simd_type->get_basetype()->get_kind() != IR::TypeExprKind::IntTypeExpr){
        Utils::error(filename, name, "Instruction pack_sat expects the destination and argument simd types to have base type of integer, but got destination base type " + dest_simd_type->get_basetype()->to_string() + " and argument base type " + arg0_simd_type->get_basetype()->to_string());
    }
    if(Utils::get_type_size(dest_simd_type->get_basetype()) > Utils::get_type_size(arg0_simd_type->get_basetype())){
        Utils::error(filename, name, "Instruction pack_sat expects the destination base type bitwidth to be less than equal the argument base type bitwidth");
    }
    if(dest_simd_type->get_size() != 2 * arg0_simd_type->get_size()){
        Utils::error(filename, name, "Instruction pack_sat expects the destination simd type size to be twice the argument simd type size, but got destination size " + std::to_string(dest_simd_type->get_size()) + " and argument size " + std::to_string(arg0_simd_type->get_size()));
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"unsigned"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for pack_sat instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::PackSatInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[0].second, flag_attrs["unsigned"]);
}
MIR::InstPtr analyze_unpack_lo_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                    IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction unpack_lo expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction unpack_lo expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction unpack_lo expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    if(!Utils::type_eq(args[0].second, args[1].second)){
        Utils::error(filename, name, "Instruction unpack_lo expects the first and second arguments to have the same type, but got first argument type " + args[0].second->to_string() + " and second argument type " + args[1].second->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    if(dest_simd_type->get_basetype()->get_kind() != IR::TypeExprKind::IntTypeExpr || arg0_simd_type->get_basetype()->get_kind() != IR::TypeExprKind::IntTypeExpr){
        Utils::error(filename, name, "Instruction unpack_lo expects the destination and argument simd types to have base type of integer, but got destination base type " + dest_simd_type->get_basetype()->to_string() + " and argument base type " + arg0_simd_type->get_basetype()->to_string());
    }
    if(Utils::get_type_size(dest_simd_type->get_basetype()) < Utils::get_type_size(arg0_simd_type->get_basetype())){
        Utils::error(filename, name, "Instruction unpack_lo expects the destination base type bitwidth to be greater than or equal to the argument base type bitwidth");
    }
    if(dest_simd_type->get_size() != arg0_simd_type->get_size()){
        Utils::error(filename, name, "Instruction unpack_lo expects the destination simd type size to be the same as the argument simd type size, but got destination size " + std::to_string(dest_simd_type->get_size()) + " and argument size " + std::to_string(arg0_simd_type->get_size()));
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"unsigned"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for unpack_lo instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::UnpackLoInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[0].second, flag_attrs["unsigned"]);
}
MIR::InstPtr analyze_unpack_hi_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                    IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction unpack_hi expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction unpack_hi expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction unpack_hi expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    if(!Utils::type_eq(args[0].second, args[1].second)){
        Utils::error(filename, name, "Instruction unpack_hi expects the first and second arguments to have the same type, but got first argument type " + args[0].second->to_string() + " and second argument type " + args[1].second->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    if(dest_simd_type->get_basetype()->get_kind() != IR::TypeExprKind::IntTypeExpr || arg0_simd_type->get_basetype()->get_kind() != IR::TypeExprKind::IntTypeExpr){
        Utils::error(filename, name, "Instruction unpack_hi expects the destination and argument simd types to have base type of integer, but got destination base type " + dest_simd_type->get_basetype()->to_string() + " and argument base type " + arg0_simd_type->get_basetype()->to_string());
    }
    if(Utils::get_type_size(dest_simd_type->get_basetype()) < Utils::get_type_size(arg0_simd_type->get_basetype())){
        Utils::error(filename, name, "Instruction unpack_hi expects the destination base type bitwidth to be greater than or equal to the argument base type bitwidth");
    }
    if(dest_simd_type->get_size() != arg0_simd_type->get_size()){
        Utils::error(filename, name, "Instruction unpack_hi expects the destination simd type size to be the same as the argument simd type size, but got destination size " + std::to_string(dest_simd_type->get_size()) + " and argument size " + std::to_string(arg0_simd_type->get_size()));
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"unsigned"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for unpack_hi instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::UnpackHiInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[0].second, flag_attrs["unsigned"]);
}
MIR::InstPtr analyze_compress_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                   std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                   IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction compress expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction compress expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    if(!Utils::type_eq(dest->get_type(), args[0].second)){
        Utils::error(filename, name, "Instruction compress expects the first argument to have the same type as the destination simd type, but got first argument type " + args[0].second->to_string() + " and destination type " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    if(!Utils::is_vector_of_int(args[1].second, 1, dest_simd_type->get_size())){
        Utils::error(filename, name, "Instruction compress expects the second argument to be of type <i1,N> where N is the same as the destination simd type size");
    }
    if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"poison_inactive"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for compress instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntCompressInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["poison_inactive"]);
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::PtrTypeExpr){
        auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"poison_inactive"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for compress instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::PtrCompressInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["poison_inactive"]);
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto [flag_attrs, remaining_attrs1] = Utils::extract_flag_attrs(filename, attributes, {"poison_inactive"});
        auto [fast_math_attr, remaining_attrs] = Utils::extract_fastmath_attrs(filename, remaining_attrs1);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for compress instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatCompressInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["poison_inactive"], fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction compress expects the destination simd type to have base type of integer, float, or pointer, but got " + dest_simd_type->get_basetype()->to_string());
    }
}
MIR::InstPtr analyze_expand_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                 std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                 IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2 && args.size() != 3){
        Utils::error(filename, name, "Instruction expand expects 2 or 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction expand expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    if(!Utils::type_eq(dest->get_type(), args[0].second)){
        Utils::error(filename, name, "Instruction expand expects the first argument to have the same type as the destination simd type, but got first argument type " + args[0].second->to_string() + " and destination type " + dest->get_type()->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    if(!Utils::is_vector_of_int(args[1].second, 1, dest_simd_type->get_size())){
        Utils::error(filename, name, "Instruction expand expects the second argument to be of type <i1,N> where N is the same as the destination simd type size");
    }
    IR::LiteralExprPtr passthru_literal = nullptr;
    if(args.size() == 3){
        if(!Utils::type_eq(dest->get_type(), args[2].second)){
            Utils::error(filename, name, "Instruction expand expects the third argument to have the same type as the destination simd type, but got third argument type " + args[2].second->to_string() + " and destination type " + dest->get_type()->to_string());
        }
        passthru_literal = args[2].first->get_literal();
    }
    if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"zeropassthru"});
        if(passthru_literal != nullptr && flag_attrs["zeropassthru"]){
            Utils::error(filename, name, "Instruction expand cannot have both a third argument and the zeropassthru attribute");
        }
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for expand instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntExpandInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), passthru_literal, flag_attrs["zeropassthru"]);
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::PtrTypeExpr){
        auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"zeropassthru"});
        if(passthru_literal != nullptr && flag_attrs["zeropassthru"]){
            Utils::error(filename, name, "Instruction expand cannot have both a third argument and the zeropassthru attribute");
        }
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for expand instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::PtrExpandInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), passthru_literal, flag_attrs["zeropassthru"]);
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto [flag_attrs, remaining_attrs1] = Utils::extract_flag_attrs(filename, attributes, {"zeropassthru"});
        auto [fast_math_attr, remaining_attrs] = Utils::extract_fastmath_attrs(filename, remaining_attrs1);
        if(passthru_literal != nullptr && flag_attrs["zeropassthru"]){
            Utils::error(filename, name, "Instruction expand cannot have both a third argument and the zeropassthru attribute");
        }
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for expand instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatExpandInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), passthru_literal, flag_attrs["zeropassthru"], fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction expand expects the destination simd type to have base type of integer, float, or pointer, but got " + dest_simd_type->get_basetype()->to_string());
    }
}
MIR::InstPtr analyze_interleave_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                     std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                     IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    std::size_t expected_count = 0;
    if(name.value == ".interleave2"){
        expected_count = 2;
    }
    else if(name.value == ".interleave3"){
        expected_count = 3;
    }
    else if(name.value == ".interleave4"){
        expected_count = 4;
    }
    else{
        Utils::error(filename, name, "Unknown interleave instruction: " + name.value);
    }
    if(args.size() != expected_count){
        Utils::error(filename, name, "Instruction " + name.value + " expects " + std::to_string(expected_count) + " arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction " + name.value + " expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    std::vector<IR::LiteralExprPtr> arg_literals = {args[0].first->get_literal()};
    for(size_t i = 1; i < args.size(); i++){
        if(!Utils::type_eq(args[0].second, args[i].second)){
            Utils::error(filename, name, "Instruction " + name.value + " expects all arguments to have the same type, but got argument " + std::to_string(i) + " type " + args[i].second->to_string() + " and first argument type " + args[0].second->to_string());
        }
        arg_literals.push_back(args[i].first->get_literal());
    }
    if(!Utils::type_eq(dest_simd_type->get_basetype(), arg0_simd_type->get_basetype())){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination simd type to have the same base type as the arguments, but got destination base type " + dest_simd_type->get_basetype()->to_string() + " and argument base type " + arg0_simd_type->get_basetype()->to_string());
    }
    if(dest_simd_type->get_size() != expected_count * arg0_simd_type->get_size()){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination simd type size to be " + std::to_string(expected_count) + " times the argument simd type size, but got destination size " + std::to_string(dest_simd_type->get_size()) + " and argument size " + std::to_string(arg0_simd_type->get_size()));
    }
    if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction " + name.value + " takes no attributes when the destination simd type has integer base type");
        }
        return std::make_shared<MIR::IntInterleaveInst>(inst_stmt, dest, arg_literals);
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::PtrTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction " + name.value + " takes no attributes when the destination simd type has pointer base type");
        }
        return std::make_shared<MIR::PtrInterleaveInst>(inst_stmt, dest, arg_literals);
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto [fast_math_attr, remaining_attrs] = Utils::extract_fastmath_attrs(filename, attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for " + name.value + " instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatInterleaveInst>(inst_stmt, dest, arg_literals, fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination simd type to have base type of integer, float, or pointer, but got " + dest_simd_type->get_basetype()->to_string());
    }
}
MIR::InstPtr analyze_deinterleave_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                       std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                       IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    std::size_t expected_kind = 0;
    if(name.value == ".deinterleave2"){
        expected_kind = 2;
    }
    else if(name.value == ".deinterleave3"){
        expected_kind = 3;
    }
    else if(name.value == ".deinterleave4"){
        expected_kind = 4;
    }
    else{
        Utils::error(filename, name, "Unknown deinterleave instruction: " + name.value);
    }
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction " + name.value + " expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination argument to be of simd type, but got " + dest->get_type()->to_string());
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
        Utils::error(filename, name, "Instruction " + name.value + " expects the first argument to be of simd type, but got " + args[0].second->to_string());
    }
    auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
    auto arg0_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
    if(!Utils::type_eq(dest_simd_type->get_basetype(), arg0_simd_type->get_basetype())){
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination simd type to have the same base type as the first argument simd type, but got destination base type " + dest_simd_type->get_basetype()->to_string() + " and first argument base type " + arg0_simd_type->get_basetype()->to_string());
    }
    if(arg0_simd_type->get_size() != expected_kind * dest_simd_type->get_size()){
        Utils::error(filename, name, "Instruction " + name.value + " expects the first argument simd type size to be " + std::to_string(expected_kind) + " times the destination simd type size, but got first argument size " + std::to_string(arg0_simd_type->get_size()) + " and destination size " + std::to_string(dest_simd_type->get_size()));
    }
    if(!Utils::is_int(args[1].second, 8)){
        Utils::error(filename, name, "Instruction " + name.value + " expects the second argument to be of type i8, but got " + args[1].second->to_string());
    }
    if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction " + name.value + " takes no attributes when the destination simd type has integer base type");
        }
        return std::make_shared<MIR::IntDeinterleaveInst>(inst_stmt, dest, args[0].first->get_literal(), args[0].second, args[1].first->get_literal());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::PtrTypeExpr){
        if(attributes.size() != 0){
            Utils::error(filename, name, "Instruction " + name.value + " takes no attributes when the destination simd type has pointer base type");
        }
        return std::make_shared<MIR::PtrDeinterleaveInst>(inst_stmt, dest, args[0].first->get_literal(), args[0].second, args[1].first->get_literal());
    }
    else if(dest_simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto [fast_math_attr, remaining_attrs] = Utils::extract_fastmath_attrs(filename, attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for " + name.value + " instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatDeinterleaveInst>(inst_stmt, dest, args[0].first->get_literal(), args[0].second, args[1].first->get_literal(), fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction " + name.value + " expects the destination simd type to have base type of integer, float, or pointer, but got " + dest_simd_type->get_basetype()->to_string());
    }
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