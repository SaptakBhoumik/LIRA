#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/semantic_analysis.hpp"
#include <iostream>

namespace LIRA {
namespace Pass {
MIR::InstPtr SemanticAnalyzer::analyze_cmp_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    auto args = inst_stmt->get_value()->get_operands();
    auto _dest = inst_stmt->get_name();
    if(!_dest.has_value()){
        error(name,"Comparison binary instruction must have a destination i.e assign this instruction to a variable");
    }
    if(args.size() != 2){
        error(name,"Comparison binary instruction must have 2 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);

    args[0].second = get_reduced_type(args[0].second);
    args[1].second = get_reduced_type(args[1].second);
    if(!type_eq(args[0].second, args[1].second)){
        error(name,"Type of arguments of comparison binary instruction must be the same");
    }
    auto type = args[0].second;
    if(!type_compatible(type, args[0].first) || !type_compatible(type, args[1].first)){
        error(name,"Type of arguments of comparison binary instruction must be compatible with the specified type for the instruction");
    }
    if(type->get_kind() == IR::TypeExprKind::SIMDTypeExpr){
        if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
            error(name,"Destination of comparison binary instruction must be a <i1, N> if the operand type is a vector type");
        }
        auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(type);
        auto simd_dest_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
        if(simd_dest_type->get_size() != simd_type->get_size()){
            error(name,"Destination of comparison binary instruction must be a <i1, N> "\
                                "where N is the same as the size of the operand type if the operand type is a vector type");
        }
        else if(simd_dest_type->get_basetype()->get_kind() != IR::TypeExprKind::IntTypeExpr){
            error(name,"Destination of comparison binary instruction must be a <i1, N> if the operand type is a vector type");
        }
        else if(std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_dest_type->get_basetype())->get_bits() != 1){
            error(name,"Destination of comparison binary instruction must be a <i1, N> if the operand type is a vector type");
        }
    }
    else{
        if(dest->get_type()->get_kind() != IR::TypeExprKind::IntTypeExpr){
            error(name,"Destination of comparison binary instruction must be a i1 if the operand type is not a vector type");
        }
        else if(std::dynamic_pointer_cast<IR::IntTypeExpr>(dest->get_type())->get_bits() != 1){
            error(name,"Destination of comparison binary instruction must be a i1 if the operand type is not a vector type");
        }
    }

    auto type_varient = MIR::get_type_varient_from_type(type);
    if(!type_varient.has_value()){
        error(name,"Unsupported type for comparison binary instruction: " + type->to_string());
    }
    else if((!MIR::is_int_typevarient(type_varient.value())) && (!MIR::is_float_typevarient(type_varient.value())) && (!MIR::is_ptr_typevarient(type_varient.value())) ){
        error(name,"Only int, float, and pointer types and their vectors are supported for comparison binary instruction");
    }

    //After this stage, type varient can only be float or int or ptr or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    if(name.value == ".eq"){
        return analyze_eq_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type,type_varient.value(),inst_stmt);
    }
    else if(name.value == ".neq"){
        return analyze_neq_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type,type_varient.value(),inst_stmt);
    }
    else if(name.value == ".gt"){
        return analyze_gt_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type,type_varient.value(),inst_stmt);
    }
    else if(name.value == ".lt"){
        return analyze_lt_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type,type_varient.value(),inst_stmt);
    }
    else if(name.value == ".ge"){
        return analyze_ge_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type,type_varient.value(),inst_stmt);
    }
    else if(name.value == ".le"){
        return analyze_le_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type,type_varient.value(),inst_stmt);
    }
    else if(name.value == ".either_nan"){
        return analyze_either_nan_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type,type_varient.value(),inst_stmt);
    }
    else if(name.value == ".neither_nan"){
        return analyze_neither_nan_bin_inst(dest,args[0].first->get_literal(),args[1].first->get_literal(),type,type_varient.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown comparison binary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr SemanticAnalyzer::analyze_eq_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                                   MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        auto [flag_attrs, final_remaining_attrs] = extract_flag_attrs(remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            error(final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .eq instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatEqInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatEqInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
    }
    else if(MIR::is_int_typevarient(type_varient)){
        if(attributes.size() > 0){
            error(attributes[0]->get_token(), "Attributes are not supported for .eq instruction with integer operands");
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntEqInst>(inst_stmt, dest, lhs, rhs, type);
        }
        else{
            return std::make_shared<MIR::VecIntEqInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
    else{
        if(attributes.size() > 0){
            error(attributes[0]->get_token(), "Attributes are not supported for .eq instruction with pointer operands");
        }
        if(type_varient == MIR::InstOperandTypeVarient::Ptr){
            return std::make_shared<MIR::PtrEqInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrEqInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
}
MIR::InstPtr SemanticAnalyzer::analyze_neq_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                                    MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        auto [flag_attrs, final_remaining_attrs] = extract_flag_attrs(remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            error(final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .neq instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatNeqInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatNeqInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        } 
    }
    else if(MIR::is_int_typevarient(type_varient)){
        if(attributes.size() > 0){
            error(attributes[0]->get_token(), "Attributes are not supported for .neq instruction with integer operands");
        }
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntNeqInst>(inst_stmt, dest, lhs, rhs, type);
        }
        else{
            return std::make_shared<MIR::VecIntNeqInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
    else{
        if(attributes.size() > 0){
            error(attributes[0]->get_token(), "Attributes are not supported for .neq instruction with pointer operands");
        }
        if(type_varient == MIR::InstOperandTypeVarient::Ptr){
            return std::make_shared<MIR::PtrNeqInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrNeqInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
}
MIR::InstPtr SemanticAnalyzer::analyze_gt_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                                   MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        auto [flag_attrs, final_remaining_attrs] = extract_flag_attrs(remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            error(final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .gt instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatGtInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatGtInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }   
    }
    else if(MIR::is_int_typevarient(type_varient)){
        auto [flag_attrs, final_remaining_attrs] = extract_flag_attrs(attributes, {"unsigned"});
        if(!final_remaining_attrs.empty()){
            error(final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .gt instruction with integer operands: " + final_remaining_attrs[0]->to_string());
        }
        bool is_unsigned = flag_attrs["unsigned"];
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntGtInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
        else{
            return std::make_shared<MIR::VecIntGtInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
    }
    else{
        if(attributes.size() > 0){
            error(attributes[0]->get_token(), "Attributes are not supported for .gt instruction with pointer operands");
        }
        if(type_varient == MIR::InstOperandTypeVarient::Ptr){
            return std::make_shared<MIR::PtrGtInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrGtInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
}
MIR::InstPtr SemanticAnalyzer::analyze_lt_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                                   MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        auto [flag_attrs, final_remaining_attrs] = extract_flag_attrs(remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            error(final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .lt instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatLtInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatLtInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
    }
    else if(MIR::is_int_typevarient(type_varient)){
        auto [flag_attrs, final_remaining_attrs] = extract_flag_attrs(attributes, {"unsigned"});
        if(!final_remaining_attrs.empty()){
            error(final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .lt instruction with integer operands: " + final_remaining_attrs[0]->to_string());
        }
        bool is_unsigned = flag_attrs["unsigned"];
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntLtInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
        else{
            return std::make_shared<MIR::VecIntLtInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
    }
    else{
        if(attributes.size() > 0){
            error(attributes[0]->get_token(), "Attributes are not supported for .lt instruction with pointer operands");
        }
        if(type_varient == MIR::InstOperandTypeVarient::Ptr){
            return std::make_shared<MIR::PtrLtInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrLtInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
}
MIR::InstPtr SemanticAnalyzer::analyze_ge_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                                   MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        auto [flag_attrs, final_remaining_attrs] = extract_flag_attrs(remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            error(final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .ge instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatGeInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatGeInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
    }
    else if(MIR::is_int_typevarient(type_varient)){
        auto [flag_attrs, final_remaining_attrs] = extract_flag_attrs(attributes, {"unsigned"});
        if(!final_remaining_attrs.empty()){
            error(final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .ge instruction with integer operands: " + final_remaining_attrs[0]->to_string());
        }
        bool is_unsigned = flag_attrs["unsigned"];
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntGeInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
        else{
            return std::make_shared<MIR::VecIntGeInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
    }
    else{
        if(attributes.size() > 0){
            error(attributes[0]->get_token(), "Attributes are not supported for .ge instruction with pointer operands");
        }
        if(type_varient == MIR::InstOperandTypeVarient::Ptr){
            return std::make_shared<MIR::PtrGeInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrGeInst>(inst_stmt, dest, lhs, rhs, type);
        } 
    }
}
MIR::InstPtr SemanticAnalyzer::analyze_le_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                                   MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevarient(type_varient)){
        auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
        auto [flag_attrs, final_remaining_attrs] = extract_flag_attrs(remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            error(final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .le instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_varient == MIR::InstOperandTypeVarient::Float){
            return std::make_shared<MIR::FloatLeInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatLeInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
    }
    else if(MIR::is_int_typevarient(type_varient)){
        auto [flag_attrs, final_remaining_attrs] = extract_flag_attrs(attributes, {"unsigned"});
        if(!final_remaining_attrs.empty()){
            error(final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .le instruction with integer operands: " + final_remaining_attrs[0]->to_string());
        }
        bool is_unsigned = flag_attrs["unsigned"];
        if(type_varient == MIR::InstOperandTypeVarient::Int){
            return std::make_shared<MIR::IntLeInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
        else{
            return std::make_shared<MIR::VecIntLeInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
    }
    else{
        if(attributes.size() > 0){
            error(attributes[0]->get_token(), "Attributes are not supported for .le instruction with pointer operands");
        }
        if(type_varient == MIR::InstOperandTypeVarient::Ptr){
            return std::make_shared<MIR::PtrLeInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrLeInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
}

MIR::InstPtr SemanticAnalyzer::analyze_either_nan_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                                           MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){
    if(!MIR::is_float_typevarient(type_varient)){
        error(inst_stmt->get_value()->get_token(), ".either_nan instruction only supports floating point types");
    }
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
    if(!remaining_attrs.empty()){
        error(remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .either_nan instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_varient == MIR::InstOperandTypeVarient::Float){
        return std::make_shared<MIR::FloatEitherNanInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatEitherNanInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr);
    }
}
MIR::InstPtr SemanticAnalyzer::analyze_neither_nan_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                                            MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt){

    if(!MIR::is_float_typevarient(type_varient)){
        error(inst_stmt->get_value()->get_token(), ".neither_nan instruction only supports floating point types");
    }
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = extract_fastmath_attrs(attributes);
    if(!remaining_attrs.empty()){
        error(remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .neither_nan instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_varient == MIR::InstOperandTypeVarient::Float){
        return std::make_shared<MIR::FloatNeitherNanInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatNeitherNanInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr);
    }
}
}
}