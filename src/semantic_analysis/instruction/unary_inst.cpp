#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
#include <memory>
#include <unordered_set>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value, 
                                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_neg_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                              MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_not_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                              MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_abs_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                              MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_ceil_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                               MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_floor_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_integral_part_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                        MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fractional_part_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                          MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_roundnearest_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                       MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_roundeven_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_sqrt_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                               MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_reciprocal_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                     MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_rsqrt_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_popcount_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_clz_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                              MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_ctz_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                              MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_parity_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                 MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_bswap_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_bitreverse_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                     MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_clrsb_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_blsi_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                               MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_blsr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                               MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_blsmask_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_unary_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".neg", analyze_neg_inst},
        {".not", analyze_not_inst},
        {".abs", analyze_abs_inst},
        {".ceil", analyze_ceil_inst},
        {".floor", analyze_floor_inst},
        {".integral_part", analyze_integral_part_inst},
        {".fractional_part", analyze_fractional_part_inst},
        {".roundnearest", analyze_roundnearest_inst},
        {".roundeven", analyze_roundeven_inst},
        {".sqrt", analyze_sqrt_inst},
        {".reciprocal", analyze_reciprocal_inst},
        {".rsqrt", analyze_rsqrt_inst},
        {".popcount", analyze_popcount_inst},
        {".clz", analyze_clz_inst},
        {".ctz", analyze_ctz_inst},
        {".parity", analyze_parity_inst},
        {".bswap", analyze_bswap_inst},
        {".bitreverse", analyze_bitreverse_inst},
        {".clrsb", analyze_clrsb_inst},
        {".blsi", analyze_blsi_inst},
        {".blsr", analyze_blsr_inst},
        {".blsmask", analyze_blsmask_inst}
    };
    std::unordered_set<std::string> unary_that_support_int = {
        ".neg",".not", ".abs",".popcount",".clz",".ctz",".parity",".bswap",".bitreverse",".clrsb",".blsi",".blsr",".blsmask"
    };
    std::unordered_set<std::string> unary_that_support_float = {
        ".neg",".abs",".ceil",".floor",".integral_part",".fractional_part",".roundnearest",".roundeven",".sqrt",".reciprocal",".rsqrt", ".bswap"
    };
    auto args = inst_stmt->get_value()->get_operands();
    if(args.size() != 1){
        Utils::error(this->filename, name, "Unary instruction must have 1 argument");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    if(dest == nullptr){
        Utils::error(this->filename, name, "Unary instruction must have a destination i.e assign this instruction to a variable");
    }
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    {
        args[0].second = Utils::get_reduced_type(this->type_symtable,args[0].second);
        if(!Utils::type_eq(type,args[0].second)){
            Utils::error(this->filename, args[0].first->get_token(), "Argument type " + args[0].second->to_string() + " is not the same as destination type " + type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, args[0].second,args[0].first)){
            Utils::error(this->filename, args[0].first->get_token(), "Argument type " + args[0].second->get_token().value + " is not compatible with assigned type " + args[0].second->to_string());
        }
    }
    auto type_variant = MIR::get_type_variant_from_type(type);
    if(!type_variant.has_value()){
        Utils::error(this->filename, name, "Unsupported type for unary instruction: " + type->to_string());
    }
    if(MIR::is_float_typevariant(type_variant.value()) && unary_that_support_float.find(name.value) == unary_that_support_float.end()){
        Utils::error(this->filename, name, "Unsupported float type for unary instruction: " + type->to_string());
    }
    else if(MIR::is_int_typevariant(type_variant.value()) && unary_that_support_int.find(name.value) == unary_that_support_int.end()){
        Utils::error(this->filename, name, "Unsupported int type for unary instruction: " + type->to_string());
    }
    else if((!MIR::is_float_typevariant(type_variant.value())) && (!MIR::is_int_typevariant(type_variant.value()))){
        Utils::error(this->filename, name, "Only int and float types are supported for unary instruction");
    }

    //After this stage, type variant can only be float or int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),type_variant.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown unary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_neg_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                              MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatNegInst>(inst_stmt,dest,value,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatNegInst>(inst_stmt,dest,value,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntNegInst>(inst_stmt,dest,value,flag_attrs["nsw"]);
        }
        else{
            return std::make_shared<MIR::VecIntNegInst>(inst_stmt,dest,value,flag_attrs["nsw"]);
        }
    }
}
MIR::InstPtr analyze_not_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                              MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int unary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntNotInst>(inst_stmt,dest,value);
    }
    else{
        return std::make_shared<MIR::VecIntNotInst>(inst_stmt,dest,value);
    }
}
MIR::InstPtr analyze_abs_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                              MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatAbsInst>(inst_stmt,dest,value,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatAbsInst>(inst_stmt,dest,value,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntAbsInst>(inst_stmt,dest,value,flag_attrs["nsw"]);
        }
        else{
            return std::make_shared<MIR::VecIntAbsInst>(inst_stmt,dest,value,flag_attrs["nsw"]);
        }
    }
}
MIR::InstPtr analyze_ceil_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                               MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatCeilInst>(inst_stmt,dest,value,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatCeilInst>(inst_stmt,dest,value,fast_math_attr);
    }
}
MIR::InstPtr analyze_floor_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatFloorInst>(inst_stmt,dest,value,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatFloorInst>(inst_stmt,dest,value,fast_math_attr);
    }
}
MIR::InstPtr analyze_integral_part_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                        MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatIntegralPartInst>(inst_stmt,dest,value,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatIntegralPartInst>(inst_stmt,dest,value,fast_math_attr);
    }
}
MIR::InstPtr analyze_fractional_part_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                          MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatFractionalPartInst>(inst_stmt,dest,value,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatFractionalPartInst>(inst_stmt,dest,value,fast_math_attr);
    }
}
MIR::InstPtr analyze_roundnearest_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                       MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatRoundNearestInst>(inst_stmt,dest,value,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatRoundNearestInst>(inst_stmt,dest,value,fast_math_attr);
    }
}
MIR::InstPtr analyze_roundeven_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatRoundEvenInst>(inst_stmt,dest,value,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatRoundEvenInst>(inst_stmt,dest,value,fast_math_attr);
    }
}
MIR::InstPtr analyze_sqrt_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                               MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatSqrtInst>(inst_stmt,dest,value,fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatSqrtInst>(inst_stmt,dest,value,fast_math_attr);
    }
}
MIR::InstPtr analyze_reciprocal_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                     MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    auto [flags,remaining_attrs] = Utils::extract_flag_attrs(filename,_remaining_attrs,{"approx"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatReciprocalInst>(inst_stmt,dest,value,fast_math_attr,flags["approx"]);
    }
    else{
        return std::make_shared<MIR::VecFloatReciprocalInst>(inst_stmt,dest,value,fast_math_attr,flags["approx"]);
    }
}
MIR::InstPtr analyze_rsqrt_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
    auto [flags,remaining_attrs] = Utils::extract_flag_attrs(filename,_remaining_attrs,{"approx"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Float){
        return std::make_shared<MIR::FloatRsqrtInst>(inst_stmt,dest,value,fast_math_attr,flags["approx"]);
    }
    else{
        return std::make_shared<MIR::VecFloatRsqrtInst>(inst_stmt,dest,value,fast_math_attr,flags["approx"]);
    }
}
MIR::InstPtr analyze_popcount_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int unary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntPopcountInst>(inst_stmt,dest,value);
    }
    else{
        return std::make_shared<MIR::VecIntPopcountInst>(inst_stmt,dest,value);
    }
}
MIR::InstPtr analyze_clz_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                              MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"zero_poison"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCLZInst>(inst_stmt,dest,value,flag_attrs["zero_poison"]);
    }
    else{
        return std::make_shared<MIR::VecIntCLZInst>(inst_stmt,dest,value,flag_attrs["zero_poison"]);
    }
}
MIR::InstPtr analyze_ctz_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                              MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"zero_poison"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCTZInst>(inst_stmt,dest,value,flag_attrs["zero_poison"]);
    }
    else{
        return std::make_shared<MIR::VecIntCTZInst>(inst_stmt,dest,value,flag_attrs["zero_poison"]);
    }
}
MIR::InstPtr analyze_parity_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                 MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int unary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntParityInst>(inst_stmt,dest,value);  
    }
    else{
        return std::make_shared<MIR::VecIntParityInst>(inst_stmt,dest,value);
    }
}
MIR::InstPtr analyze_bswap_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_vector_typevariant(type_variant)){
        auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
        if(Utils::get_type_size(simd_type->get_basetype()) % 8 != 0){
            Utils::error(filename, inst_stmt->get_value()->get_token(), "Vector type for bswap instruction must have element size multiple of 8 bits");
        }
    }
    else if(Utils::get_type_size(dest->get_type()) % 8 != 0){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "Type for bswap instruction must have size multiple of 8 bits");
    }
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float unary instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatBswapInst>(inst_stmt,dest,value,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatBswapInst>(inst_stmt,dest,value,fast_math_attr);
        }
    }
    else{
        if(attributes.size() > 0){
            Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int unary instruction: " + attributes[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntBswapInst>(inst_stmt,dest,value);
        }
        else{
            return std::make_shared<MIR::VecIntBswapInst>(inst_stmt,dest,value);
        }
    }
}
MIR::InstPtr analyze_bitreverse_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                     MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int unary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntBitreverseInst>(inst_stmt,dest,value);
    }
    else{
        return std::make_shared<MIR::VecIntBitreverseInst>(inst_stmt,dest,value);
    }
}
MIR::InstPtr analyze_clrsb_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int unary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCLRSBInst>(inst_stmt,dest,value);
    }
    else{
        return std::make_shared<MIR::VecIntCLRSBInst>(inst_stmt,dest,value);
    }
}
MIR::InstPtr analyze_blsi_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                               MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int unary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntBLSIInst>(inst_stmt,dest,value);
    }
    else{
        return std::make_shared<MIR::VecIntBLSIInst>(inst_stmt,dest,value);
    }
}
MIR::InstPtr analyze_blsr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                               MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int unary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntBLSRInst>(inst_stmt,dest,value);
    }
    else{
        return std::make_shared<MIR::VecIntBLSRInst>(inst_stmt,dest,value);
    }
}
MIR::InstPtr analyze_blsmask_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr value,
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){  
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int unary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntBLSMaskInst>(inst_stmt,dest,value);
    }
    else{
        return std::make_shared<MIR::VecIntBLSMaskInst>(inst_stmt,dest,value);
    }
}
}
}