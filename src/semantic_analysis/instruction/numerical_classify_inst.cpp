#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
#include <memory>
#include <unordered_set>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value, IR::TypeExprPtr value_type, 
                                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_isnan_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_isinf_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_isfinite_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_isnormal_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_issubnormal_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                      MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_iszero_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                 MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_isnegative_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                     MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_ispositive_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                     MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_numerical_classify_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".isnan", analyze_isnan_inst},
        {".isinf", analyze_isinf_inst},
        {".isfinite", analyze_isfinite_inst},
        {".isnormal", analyze_isnormal_inst},
        {".issubnormal", analyze_issubnormal_inst},
        {".iszero", analyze_iszero_inst},
        {".isnegative", analyze_isnegative_inst},
        {".ispositive", analyze_ispositive_inst}
    };
    std::unordered_set<std::string> inst_that_support_int = {};
    std::unordered_set<std::string> inst_that_support_float = {
        ".isnan", ".isinf", ".isfinite", ".isnormal", ".issubnormal", ".iszero", ".isnegative", ".ispositive"
    };
    auto args = inst_stmt->get_value()->get_operands();
    if(args.size() != 1){
        Utils::error(this->filename, name, "Numerical classification instruction must have 1 argument");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    if(dest == nullptr){
        Utils::error(this->filename, name, "Numerical classification instruction must have a destination i.e assign this instruction to a variable");
    }

    args[0].second = Utils::get_reduced_type(this->type_symtable,args[0].second);
    if(!Utils::type_compatible(this->var_symtable, args[0].second,args[0].first)){
        Utils::error(this->filename, args[0].first->get_token(), "Argument type " + args[0].second->get_token().value + " is not compatible with assigned type " + args[0].second->to_string());
    }
    auto type_variant = MIR::get_type_variant_from_type(args[0].second);
    
    if(!type_variant.has_value()){
        Utils::error(this->filename, name, "Unsupported type for numerical classification instruction: " + args[0].second->to_string());
    }

    if(MIR::is_vector_typevariant(type_variant.value())){
        if(dest->get_type()->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
            Utils::error(this->filename, name, "Destination type for numerical classification instruction must be a vector type");
        }
        auto dest_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
        auto arg_simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
        auto basetype = dest_simd_type->get_basetype();
        if(arg_simd_type->get_size() != dest_simd_type->get_size()){
            Utils::error(this->filename, name, "Vector size mismatch between destination type " + dest_simd_type->to_string() + " and argument type " + arg_simd_type->to_string());
        }
        else if(!Utils::is_int(basetype,1)){
            Utils::error(this->filename, name, "Destination type for numerical classification instruction must be a vector type with base type i1");
        }
    }
    else if(!Utils::is_int(dest->get_type(),1)){
        Utils::error(this->filename, name, "Destination type for numerical classification instruction must be i1 if the argument type is not a vector type");
    }

    if(MIR::is_float_typevariant(type_variant.value()) && inst_that_support_float.find(name.value) == inst_that_support_float.end()){
        Utils::error(this->filename, name, "Unsupported float type for numerical classification instruction: " + args[0].second->to_string());
    }
    else if(MIR::is_int_typevariant(type_variant.value()) && inst_that_support_int.find(name.value) == inst_that_support_int.end()){
        Utils::error(this->filename, name, "Unsupported int type for numerical classification instruction: " + args[0].second->to_string());
    }
    else if((!MIR::is_float_typevariant(type_variant.value())) && (!MIR::is_int_typevariant(type_variant.value()))){
        Utils::error(this->filename, name, "Only int and float types are supported for numerical classification instruction");
    }

    //After this stage, type variant can only be float or int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),args[0].second,type_variant.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown numerical classification instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_isnan_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                IR::TypeExprPtr value_type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatIsNanInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatIsNanInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
}
MIR::InstPtr analyze_isinf_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                IR::TypeExprPtr value_type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatIsInfInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatIsInfInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
}
MIR::InstPtr analyze_isfinite_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                   IR::TypeExprPtr value_type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatIsFiniteInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatIsFiniteInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
}
MIR::InstPtr analyze_isnormal_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                   IR::TypeExprPtr value_type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatIsNormalInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatIsNormalInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
}
MIR::InstPtr analyze_issubnormal_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                      IR::TypeExprPtr value_type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatIsSubnormalInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatIsSubnormalInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
}
MIR::InstPtr analyze_iszero_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                 IR::TypeExprPtr value_type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatIsZeroInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatIsZeroInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
}
MIR::InstPtr analyze_isnegative_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                     IR::TypeExprPtr value_type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatIsNegativeInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatIsNegativeInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
}
MIR::InstPtr analyze_ispositive_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                     IR::TypeExprPtr value_type, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatIsPositiveInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatIsPositiveInst>(inst_stmt,dest,value,value_type,fast_math_attr);
    }
}
}
}