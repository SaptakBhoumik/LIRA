#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
#include <memory>
#include <unordered_set>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_fetch_neg_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_not_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_abs_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_ceil_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                     MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_floor_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                      MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_integral_part_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                              MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_fractional_part_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                                MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_roundnearest_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                             MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_roundeven_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                          MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_sqrt_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                     MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_reciprocal_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                           MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_rsqrt_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                      MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_popcount_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_clz_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_ctz_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_parity_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                       MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_bswap_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                      MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_bitreverse_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                           MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_clrsb_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                      MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_blsi_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                     MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_blsr_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                     MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_blsmask_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_unary_fetch_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".fetch_neg", analyze_fetch_neg_inst},
        {".fetch_not", analyze_fetch_not_inst},
        {".fetch_abs", analyze_fetch_abs_inst},
        {".fetch_ceil", analyze_fetch_ceil_inst},
        {".fetch_floor", analyze_fetch_floor_inst},
        {".fetch_integral_part", analyze_fetch_integral_part_inst},
        {".fetch_fractional_part", analyze_fetch_fractional_part_inst},
        {".fetch_roundnearest", analyze_fetch_roundnearest_inst},
        {".fetch_roundeven", analyze_fetch_roundeven_inst},
        {".fetch_sqrt", analyze_fetch_sqrt_inst},
        {".fetch_reciprocal", analyze_fetch_reciprocal_inst},
        {".fetch_rsqrt", analyze_fetch_rsqrt_inst},
        {".fetch_popcount", analyze_fetch_popcount_inst},
        {".fetch_clz", analyze_fetch_clz_inst},
        {".fetch_ctz", analyze_fetch_ctz_inst},
        {".fetch_parity", analyze_fetch_parity_inst},
        {".fetch_bswap", analyze_fetch_bswap_inst},
        {".fetch_bitreverse", analyze_fetch_bitreverse_inst},
        {".fetch_clrsb", analyze_fetch_clrsb_inst},
        {".fetch_blsi", analyze_fetch_blsi_inst},
        {".fetch_blsr", analyze_fetch_blsr_inst},
        {".fetch_blsmask", analyze_fetch_blsmask_inst}
    };
    std::unordered_set<std::string> unary_fetch_that_support_int = {
        ".fetch_neg",".fetch_not", ".fetch_abs",".fetch_popcount",".fetch_clz",".fetch_ctz",".fetch_parity",".fetch_bswap",".fetch_bitreverse",".fetch_clrsb",".fetch_blsi",".fetch_blsr",".fetch_blsmask"
    };
    std::unordered_set<std::string> unary_fetch_that_support_float = {
        ".fetch_neg",".fetch_abs",".fetch_ceil",".fetch_floor",".fetch_integral_part",".fetch_fractional_part",".fetch_roundnearest",".fetch_roundeven",".fetch_sqrt",".fetch_reciprocal",".fetch_rsqrt", ".fetch_bswap"
    };
    auto args = inst_stmt->get_value()->get_operands();
    auto _dest = inst_stmt->get_name();
    if(!_dest.has_value()){
        Utils::error(this->filename, name, "Unary fetch instruction must have a destination i.e assign this instruction to a variable");
    }
    if(args.size() != 1){
        Utils::error(this->filename, name, "Unary fetch instruction must have 1 argument");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [common_fetch_attrs,remaining_attrs] = Utils::extract_common_atomic_inst(this->filename,attributes);
    if(Utils::get_type_size(type) > 128 && common_fetch_attrs.atomic_ordering.has_value()){
        Utils::error(this->filename, name, "Atomic unary fetch instruction destination type size must be less than or equal to 128 bits. Found: " + std::to_string(Utils::get_type_size(type)) + " bits");
    }
    {
        args[0].second = Utils::get_reduced_type(this->type_symtable,args[0].second);
        if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
            Utils::error(this->filename, args[0].first->get_token(), "Argument type " + args[0].second->to_string() + " is not a pointer type");
        }
        else if(!Utils::type_compatible(this->var_symtable, args[0].second,args[0].first)){
            Utils::error(this->filename, args[0].first->get_token(), "Argument type ptr is not compatible with assigned type " + args[0].first->to_string());
        }
    }
    auto type_variant = MIR::get_type_variant_from_type(type);
    if(!type_variant.has_value()){
        Utils::error(this->filename, name, "Unsupported type for unary fetch instruction: " + type->to_string());
    }
    if(MIR::is_vector_typevariant(type_variant.value())){
        Utils::error(this->filename, name, "Vector type is not supported for unary fetch instruction: " + type->to_string());
    }
    else if(MIR::is_float_typevariant(type_variant.value()) && unary_fetch_that_support_float.find(name.value) == unary_fetch_that_support_float.end()){
        Utils::error(this->filename, name, "Unsupported float type for unary fetch instruction: " + type->to_string());
    }
    else if(MIR::is_int_typevariant(type_variant.value()) && unary_fetch_that_support_int.find(name.value) == unary_fetch_that_support_int.end()){
        Utils::error(this->filename, name, "Unsupported int type for unary fetch instruction: " + type->to_string());
    }
    else if((!MIR::is_float_typevariant(type_variant.value())) && (!MIR::is_int_typevariant(type_variant.value()))){
        Utils::error(this->filename, name, "Only int and float types are supported for unary fetch instruction");
    }

    //After this stage, type variant can only be float or int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),type_variant.value(),common_fetch_attrs,remaining_attrs,inst_stmt);
    }
    else{
        std::cerr << "Unknown unary fetch instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}
MIR::InstPtr analyze_fetch_neg_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
        if(_remaining_attrs.size() > 0){
            Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchNegInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr);
    }
    else{
        auto [flag_attrs,_remaining_attrs] = Utils::extract_flag_attrs(filename,remaining_attrs, {"nsw"});
        if(_remaining_attrs.size() > 0){
            Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + _remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchNegInst>(inst_stmt,dest,value,common_fetch_attrs,flag_attrs["nsw"]);
    }
}
MIR::InstPtr analyze_fetch_not_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchNotInst>(inst_stmt,dest,value,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_abs_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
        if(_remaining_attrs.size() > 0){
            Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchAbsInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr);
    }
    else{
        auto [flag_attrs,_remaining_attrs] = Utils::extract_flag_attrs(filename,remaining_attrs, {"nsw"});
        if(_remaining_attrs.size() > 0){
            Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + _remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchAbsInst>(inst_stmt,dest,value,common_fetch_attrs,flag_attrs["nsw"]);
    }
}
MIR::InstPtr analyze_fetch_ceil_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                     MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::FloatFetchCeilInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr);
}
MIR::InstPtr analyze_fetch_floor_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                      MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::FloatFetchFloorInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr);
}
MIR::InstPtr analyze_fetch_integral_part_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                              MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::FloatFetchIntegralPartInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr);
}
MIR::InstPtr analyze_fetch_fractional_part_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                                MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::FloatFetchFractionalPartInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr);
}
MIR::InstPtr analyze_fetch_roundnearest_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                             MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::FloatFetchRoundNearestInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr);
}
MIR::InstPtr analyze_fetch_roundeven_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                          MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::FloatFetchRoundEvenInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr);
}
MIR::InstPtr analyze_fetch_sqrt_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                     MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::FloatFetchSqrtInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr);
}
MIR::InstPtr analyze_fetch_reciprocal_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                           MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [fast_math_attr,__remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
    auto [flag_attrs,_remaining_attrs] = Utils::extract_flag_attrs(filename,__remaining_attrs, {"approx"});
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::FloatFetchReciprocalInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr,flag_attrs["approx"]);
}
MIR::InstPtr analyze_fetch_rsqrt_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                      MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [fast_math_attr,__remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
    auto [flag_attrs,_remaining_attrs] = Utils::extract_flag_attrs(filename,__remaining_attrs, {"approx"});
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::FloatFetchRsqrtInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr,flag_attrs["approx"]);
}
MIR::InstPtr analyze_fetch_popcount_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchPopcountInst>(inst_stmt,dest,value,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_clz_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [flag_attrs,_remaining_attrs] = Utils::extract_flag_attrs(filename,remaining_attrs, {"zero_poison"});
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchCLZInst>(inst_stmt,dest,value,common_fetch_attrs,flag_attrs["zero_poison"]);
}
MIR::InstPtr analyze_fetch_ctz_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto [flag_attrs,_remaining_attrs] = Utils::extract_flag_attrs(filename,remaining_attrs, {"zero_poison"});
    if(_remaining_attrs.size() > 0){
        Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + _remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchCTZInst>(inst_stmt,dest,value,common_fetch_attrs,flag_attrs["zero_poison"]);
}
MIR::InstPtr analyze_fetch_parity_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                       MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchParityInst>(inst_stmt,dest,value,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_bswap_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                      MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    auto type = dest->get_type();
    if(Utils::get_type_size(type) % 8 != 0){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "bswap instruction destination type size must be a multiple of 8 bits. Found: " + std::to_string(Utils::get_type_size(type)) + " bits");
    }

    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,remaining_attrs);
        if(_remaining_attrs.size() > 0){
            Utils::error(filename, _remaining_attrs[0]->get_token(), "Unsupported attribute for float unary fetch instruction: " + _remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchBswapInst>(inst_stmt,dest,value,common_fetch_attrs,fast_math_attr);
    }
    else{
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchBswapInst>(inst_stmt,dest,value,common_fetch_attrs);
    }
}
MIR::InstPtr analyze_fetch_bitreverse_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                           MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchBitreverseInst>(inst_stmt,dest,value,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_clrsb_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                      MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchCLRSBInst>(inst_stmt,dest,value,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_blsi_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                     MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchBLSIInst>(inst_stmt,dest,value,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_blsr_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                     MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchBLSRInst>(inst_stmt,dest,value,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_blsmask_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr value, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> remaining_attrs, IR::InstructionStmtPtr inst_stmt){
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int unary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchBLSMaskInst>(inst_stmt,dest,value,common_fetch_attrs);
}
}
}