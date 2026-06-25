#include "mir//instruction/_instruction.hpp"
#include <optional>

namespace LIRA {
namespace MIR {
std::string FastMathAttr::to_string() const{
    if(this->nnans && this->ninfs && this->nsz && this->arcp && this->contract && this->afns && this->reassoc){
        return "#[fast]";
    }

    std::string result;
    std::string prefix = "";
    if(this->nnans){
        result += "#[nnans]";
        prefix = " ";
    }
    if(this->ninfs){
        result += prefix + "#[ninfs]";
        prefix = " ";
    }
    if(this->nsz){
        result += prefix + "#[nsz]";
        prefix = " ";
    }
    if(this->arcp){
        result += prefix + "#[arcp]";
        prefix = " ";
    }
    if(this->contract){
        result += prefix + "#[contract]";
        prefix = " ";
    }
    if(this->afns){
        result += prefix + "#[afns]";
        prefix = " ";
    }
    if(this->reassoc){
        result += prefix + "#[reassoc]";
    }
    return result;
}
Inst::Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::optional<FastMathAttr> fast_math_attr){
    this->instruction_stmt = instruction_stmt;
    this->destination = destination;
    this->fast_math_attr = fast_math_attr;
}
LocalDestRegisterPtr Inst::get_destination() const{
    return this->destination;
}
std::optional<FastMathAttr> Inst::get_fast_math_attr() const{
    return this->fast_math_attr;
}
IR::InstructionStmtPtr Inst::get_instruction_stmt() const{
    return this->instruction_stmt;
}
IR::DebugInfoPtr Inst::get_debug_info() const{
    return this->instruction_stmt->get_value()->get_debug_info();
}


bool is_vector_typevariant(const TypeVariant var){
    return var == TypeVariant::VecInt || var == TypeVariant::VecFloat || var == TypeVariant::VecPtr;
}
bool is_scalar_typevariant(const TypeVariant var){
    return var == TypeVariant::Int || var == TypeVariant::Float || var == TypeVariant::Ptr;
}
bool is_ptr_typevariant(const TypeVariant var){
    return var == TypeVariant::Ptr || var == TypeVariant::VecPtr;
}
bool is_float_typevariant(const TypeVariant var){
    return var == TypeVariant::Float || var == TypeVariant::VecFloat;
}
bool is_int_typevariant(const TypeVariant var){
    return var == TypeVariant::Int || var == TypeVariant::VecInt;
}

inline std::optional<TypeVariant> get_type_variant_from_type(const IR::TypeExprPtr type){
    switch(type->get_kind()){
        case IR::TypeExprKind::IntTypeExpr:{
            return TypeVariant::Int;
        }
        case IR::TypeExprKind::FloatTypeExpr:{
            return TypeVariant::Float;
        }
        case IR::TypeExprKind::PtrTypeExpr:{
            return TypeVariant::Ptr;
        }
        case IR::TypeExprKind::SIMDTypeExpr:{
                auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(type);
                if(simd_type == nullptr) return std::nullopt;
                auto element_type = simd_type->get_basetype();
                switch(element_type->get_kind()){
                    case IR::TypeExprKind::IntTypeExpr:{
                        return TypeVariant::VecInt;
                    }
                    case IR::TypeExprKind::FloatTypeExpr:{  
                        return TypeVariant::VecFloat;
                    }
                    case IR::TypeExprKind::PtrTypeExpr:{
                        return TypeVariant::VecPtr;
                    }
                    default:{
                        return std::nullopt;
                    }
                }
        }
        default:{
            return std::nullopt;
        }
    }
}


std::string to_string(SyncScope syncscope){
    switch(syncscope){
        case SyncScope::SingleThread:{
            return "singlethread";
        }
        case SyncScope::Global:{
            return "global";
        }
    }
}


std::string to_string(AtomicOrdering ordering){
    switch(ordering){
        case AtomicOrdering::UNORDERED:{
            return "unordered";
        }
        case AtomicOrdering::MONOTONIC:{
            return "monotonic";
        }
        case AtomicOrdering::ACQUIRE:{
            return "acquire";
        }
        case AtomicOrdering::RELEASE:{
            return "release";
        }
        case AtomicOrdering::ACQUIRE_RELEASE:{
            return "acq_rel";
        }
        case AtomicOrdering::SEQUENTIALLY_CONSISTENT:{
            return "seq_cst";
        }
    }
}


std::string to_string(CallingConv ordering){
    switch(ordering){
        case CallingConv::CCC:{
            return "ccc";
        }
        case CallingConv::FASTCC:{
            return "fastcc";
        }
        case CallingConv::COLDCC:{
            return "coldcc";
        }
        case CallingConv::TAILCC:{
            return "tailcc";
        }
    }
}


std::string to_string(FPEnvField field){
    switch(field){
        case FPEnvField::Round:{
            return "round";
        }
        case FPEnvField::FlushToZero:{
            return "ftz";
        }
        case FPEnvField::DenormalsAreZero:{
            return "daz";
        }
        case FPEnvField::ExceptMask:{
            return "except_mask";
        }
        case FPEnvField::ExceptStatus:{
            return "except_status";
        }
    }
}
}
}