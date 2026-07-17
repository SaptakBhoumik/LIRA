#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
#include <unordered_map>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    IR::TypeExprPtr type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt)>; 
MIR::InstPtr analyze_eq_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                 IR::TypeExprPtr type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_neq_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  IR::TypeExprPtr type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_gt_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  IR::TypeExprPtr type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_lt_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  IR::TypeExprPtr type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_ge_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                  IR::TypeExprPtr type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_le_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                  IR::TypeExprPtr type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_either_nan_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                        IR::TypeExprPtr type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_neither_nan_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                         IR::TypeExprPtr type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);         
MIR::InstPtr analyze_both_nan_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                        IR::TypeExprPtr type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);                                             
MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_cmp_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".eq", analyze_eq_bin_inst},
        {".neq", analyze_neq_bin_inst},
        {".gt", analyze_gt_bin_inst},
        {".lt", analyze_lt_bin_inst},
        {".ge", analyze_ge_bin_inst},
        {".le", analyze_le_bin_inst},
        {".either_nan", analyze_either_nan_bin_inst},
        {".neither_nan", analyze_neither_nan_bin_inst},
        {".both_nan", analyze_both_nan_bin_inst}
    };
    auto args = inst_stmt->get_value()->get_operands();
    if(args.size() != 2){
        Utils::error(this->filename,name,"Comparison binary instruction must have 2 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    if(dest == nullptr){
        Utils::error(this->filename,name,"Comparison binary instruction must have a destination i.e assign this instruction to a variable");
    }

    args[0].second = Utils::get_reduced_type(this->type_symtable, args[0].second);
    args[1].second = Utils::get_reduced_type(this->type_symtable, args[1].second);
    if(!Utils::type_eq(args[0].second, args[1].second)){
        Utils::error(this->filename,name,"Type of arguments of comparison binary instruction must be the same");
    }
    auto type = args[0].second;
    if(!Utils::type_compatible(this->var_symtable, type, args[0].first) || !Utils::type_compatible(this->var_symtable, type, args[1].first)){
        Utils::error(this->filename,name,"Type of arguments of comparison binary instruction must be compatible with the specified type for the instruction");
    }
    if(type->get_kind() == IR::TypeExprKind::SIMDTypeExpr){
        if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
            Utils::error(this->filename,name,"Destination of comparison binary instruction must be a <i1, N> if the operand type is a vector type");
        }
        auto arg_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(type);
        auto simd_dest_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
        if(simd_dest_type->get_size() != arg_simd_type->get_size()){
            Utils::error(this->filename,name,"Destination of comparison binary instruction must be a <i1, N> "\
                                "where N is the same as the size of the operand type if the operand type is a vector type");
        }
        else if(Utils::is_int(simd_dest_type->get_basetype(),1) == false){
            Utils::error(this->filename,name,"Destination of comparison binary instruction must be a <i1, N> "\
                                "where N is the same as the size of the operand type if the operand type is a vector type");
        }
    }
    else if(!Utils::is_int(dest->get_type(),1)){
        Utils::error(this->filename,name,"Destination of comparison binary instruction must be i1 if the operand type is not a vector type");
    }

    auto type_variant = MIR::get_type_variant_from_type(type);
    if(!type_variant.has_value()){
        Utils::error(this->filename,name,"Unsupported type for comparison binary instruction: " + type->to_string());
    }
    else if((!MIR::is_int_typevariant(type_variant.value())) && (!MIR::is_float_typevariant(type_variant.value())) && (!MIR::is_ptr_typevariant(type_variant.value())) ){
        Utils::error(this->filename,name,"Only int, float, and pointer types and their vectors are supported for comparison binary instruction");
    }

    //After this stage, type variant can only be float or int or ptr or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto dispatch_func = dispatch_map.find(name.value);
    if(dispatch_func != dispatch_map.end()){
        return dispatch_func->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),type,type_variant.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown comparison binary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_eq_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                 MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs, final_remaining_attrs] = Utils::extract_flag_attrs(filename,remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            Utils::error(filename,final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .eq instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatEqInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatEqInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
    }
    else if(MIR::is_int_typevariant(type_variant)){
        if(attributes.size() > 0){
            Utils::error(filename,attributes[0]->get_token(), "Attributes are not supported for .eq instruction with integer operands");
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntEqInst>(inst_stmt, dest, lhs, rhs, type);
        }
        else{
            return std::make_shared<MIR::VecIntEqInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
    else{
        if(attributes.size() > 0){
            Utils::error(filename,attributes[0]->get_token(), "Attributes are not supported for .eq instruction with pointer operands");
        }
        if(type_variant == MIR::TypeVariant::Ptr){
            return std::make_shared<MIR::PtrEqInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrEqInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
}
MIR::InstPtr analyze_neq_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs, final_remaining_attrs] = Utils::extract_flag_attrs(filename,remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            Utils::error(filename,final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .neq instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatNeqInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatNeqInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        } 
    }
    else if(MIR::is_int_typevariant(type_variant)){
        if(attributes.size() > 0){
            Utils::error(filename,attributes[0]->get_token(), "Attributes are not supported for .neq instruction with integer operands");
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntNeqInst>(inst_stmt, dest, lhs, rhs, type);
        }
        else{
            return std::make_shared<MIR::VecIntNeqInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
    else{
        if(attributes.size() > 0){
            Utils::error(filename,attributes[0]->get_token(), "Attributes are not supported for .neq instruction with pointer operands");
        }
        if(type_variant == MIR::TypeVariant::Ptr){
            return std::make_shared<MIR::PtrNeqInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrNeqInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
}
MIR::InstPtr analyze_gt_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                 MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs, final_remaining_attrs] = Utils::extract_flag_attrs(filename,remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            Utils::error(filename,final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .gt instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatGtInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatGtInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }   
    }
    else if(MIR::is_int_typevariant(type_variant)){
        auto [flag_attrs, final_remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(!final_remaining_attrs.empty()){
            Utils::error(filename,final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .gt instruction with integer operands: " + final_remaining_attrs[0]->to_string());
        }
        bool is_unsigned = flag_attrs["unsigned"];
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntGtInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
        else{
            return std::make_shared<MIR::VecIntGtInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
    }
    else{
        if(attributes.size() > 0){
            Utils::error(filename,attributes[0]->get_token(), "Attributes are not supported for .gt instruction with pointer operands");
        }
        if(type_variant == MIR::TypeVariant::Ptr){
            return std::make_shared<MIR::PtrGtInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrGtInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
}
MIR::InstPtr analyze_lt_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                 MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs, final_remaining_attrs] = Utils::extract_flag_attrs(filename,remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            Utils::error(filename,final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .lt instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatLtInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatLtInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
    }
    else if(MIR::is_int_typevariant(type_variant)){
        auto [flag_attrs, final_remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(!final_remaining_attrs.empty()){
            Utils::error(filename,final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .lt instruction with integer operands: " + final_remaining_attrs[0]->to_string());
        }
        bool is_unsigned = flag_attrs["unsigned"];
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntLtInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
        else{
            return std::make_shared<MIR::VecIntLtInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
    }
    else{
        if(attributes.size() > 0){
            Utils::error(filename,attributes[0]->get_token(), "Attributes are not supported for .lt instruction with pointer operands");
        }
        if(type_variant == MIR::TypeVariant::Ptr){
            return std::make_shared<MIR::PtrLtInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrLtInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
}
MIR::InstPtr analyze_ge_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                 MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs, final_remaining_attrs] = Utils::extract_flag_attrs(filename,remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            Utils::error(filename,final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .ge instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatGeInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatGeInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
    }
    else if(MIR::is_int_typevariant(type_variant)){
        auto [flag_attrs, final_remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(!final_remaining_attrs.empty()){
            Utils::error(filename,final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .ge instruction with integer operands: " + final_remaining_attrs[0]->to_string());
        }
        bool is_unsigned = flag_attrs["unsigned"];
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntGeInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
        else{
            return std::make_shared<MIR::VecIntGeInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
    }
    else{
        if(attributes.size() > 0){
            Utils::error(filename,attributes[0]->get_token(), "Attributes are not supported for .ge instruction with pointer operands");
        }
        if(type_variant == MIR::TypeVariant::Ptr){
            return std::make_shared<MIR::PtrGeInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrGeInst>(inst_stmt, dest, lhs, rhs, type);
        } 
    }
}
MIR::InstPtr analyze_le_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                 MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs, final_remaining_attrs] = Utils::extract_flag_attrs(filename,remaining_attrs, {"unordered"});
        if(!final_remaining_attrs.empty()){
            Utils::error(filename,final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .le instruction with floating point operands: " + final_remaining_attrs[0]->to_string());
        }
        bool unordered = flag_attrs["unordered"];
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatLeInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
        else{
            return std::make_shared<MIR::VecFloatLeInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr, unordered);
        }
    }
    else if(MIR::is_int_typevariant(type_variant)){
        auto [flag_attrs, final_remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(!final_remaining_attrs.empty()){
            Utils::error(filename,final_remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .le instruction with integer operands: " + final_remaining_attrs[0]->to_string());
        }
        bool is_unsigned = flag_attrs["unsigned"];
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntLeInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
        else{
            return std::make_shared<MIR::VecIntLeInst>(inst_stmt, dest, lhs, rhs, type, is_unsigned);
        }
    }
    else{
        if(attributes.size() > 0){
            Utils::error(filename,attributes[0]->get_token(), "Attributes are not supported for .le instruction with pointer operands");
        }
        if(type_variant == MIR::TypeVariant::Ptr){
            return std::make_shared<MIR::PtrLeInst>(inst_stmt, dest, lhs, rhs);
        }
        else{
            return std::make_shared<MIR::VecPtrLeInst>(inst_stmt, dest, lhs, rhs, type);
        }
    }
}

MIR::InstPtr analyze_either_nan_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                         MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    if(!MIR::is_float_typevariant(type_variant)){
        Utils::error(filename,inst_stmt->get_value()->get_token(), ".either_nan instruction only supports floating point types");
    }
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(!remaining_attrs.empty()){
        Utils::error(filename,remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .either_nan instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatEitherNanInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatEitherNanInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr);
    }
}
MIR::InstPtr analyze_neither_nan_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                          MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){

    if(!MIR::is_float_typevariant(type_variant)){
        Utils::error(filename,inst_stmt->get_value()->get_token(), ".neither_nan instruction only supports floating point types");
    }
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(!remaining_attrs.empty()){
        Utils::error(filename,remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .neither_nan instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatNeitherNanInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatNeitherNanInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr);
    }
}
MIR::InstPtr analyze_both_nan_bin_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                                       MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){

    if(!MIR::is_float_typevariant(type_variant)){
        Utils::error(filename,inst_stmt->get_value()->get_token(), ".both_nan instruction only supports floating point types");
    }
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(!remaining_attrs.empty()){
        Utils::error(filename,remaining_attrs[0]->get_token(), "Unsupported attribute(s) for .both_nan instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatBothNanInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatBothNanInst>(inst_stmt, dest, lhs, rhs, type, fast_math_attr);
    }
}
}
}