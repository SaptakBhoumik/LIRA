#pragma once
#include "ast/ast.hpp"
#include <sys/cdefs.h>
namespace LIRA {
namespace MIR{
enum class InstType:std::int16_t{
    ArithmeticBinaryInst,
    CmpBinaryInst,
    LogicalBinaryInst,

    ExtractElementInst,
    InsertElementInst,
    ShuffleVectorInst,
    //TODO:FInish it
};
class DestinationVar{};//TODO:Implement it to store the attribute in a structured manner(Like the token name and the attributes in a strutured way)
// I am going to define the instruction set of LIRA. A lot of the instructions are lot lowered. Like .add is lowered to .fadd, .iadd, .vadd and so on. It is done
// to make my life easier in the codegen phase. Although it is possible to merge a few of these instructions but I want to keep them separate because I think it will be better
// Although I admit I may be wrong and it may be better to merge some of these instructions but I will keep them separate for now 
class Inst {
    public:
    virtual ~Inst() = default;

    virtual std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const;//For faster access if needed
    virtual InstType get_inst_type() const = 0;
    virtual IR::InstructionStmtPtr get_instruction_stmt() const = 0;//For error reporting
    virtual std::string to_string() const = 0;
    virtual IR::DebugInfoPtr get_debug_info() const final;//Return get_instruction_stmt()->get_value()->get_debug_info() if get_value() is not empty else nullptr.
};

using InstPtr = std::shared_ptr<Inst>;

struct FastMathAttr {
    bool nnans = false;
    bool ninfs = false;
    bool nsz = false;
    bool arcp = false;
    bool contract = false;
    bool afns = false;
    bool reassoc = false;
};

enum class InstOperandTypeVarient:std::uint32_t{
    // A lot of operands are divided into int,float,ptr,vector etc based on the type they operate on. Not every instruction show this property but a lot do. It is for them
    Int = 1 << 0,
    Float = 1 << 1,
    Ptr = 1 << 2,
    VecInt = 1 << 3,
    VecFloat = 1 << 4,
    VecPtr = 1 << 5
    /*
    We will usually do matching on InstOperandTypeVarient | Opcode. So for every enum opcode, make sure to have a unique bit pattern starting from 1 << 6.
    Like the following
    enum class OpType:std::uint32_t{
        ADD = 1 << 6,
        SUB = 1 << 7,
        MUL = 1 << 8,
        DIV = 1 << 9,
        REM = 1 << 10
    };
    */
};

__always_inline bool is_vector_typevarient(const InstOperandTypeVarient var) {
    return var == InstOperandTypeVarient::VecInt || var == InstOperandTypeVarient::VecFloat || var == InstOperandTypeVarient::VecPtr;
}

__always_inline bool is_scalar_typevarient(const InstOperandTypeVarient var) {
    return var == InstOperandTypeVarient::Int || var == InstOperandTypeVarient::Float || var == InstOperandTypeVarient::Ptr;
}

__always_inline bool is_ptr_typevarient(const InstOperandTypeVarient var) {
    return var == InstOperandTypeVarient::Ptr || var == InstOperandTypeVarient::VecPtr;
}

__always_inline bool is_float_typevarient(const InstOperandTypeVarient var) {
    return var == InstOperandTypeVarient::Float || var == InstOperandTypeVarient::VecFloat;
}

__always_inline bool is_int_typevarient(const InstOperandTypeVarient var) {
    return var == InstOperandTypeVarient::Int || var == InstOperandTypeVarient::VecInt;
}

inline std::optional<InstOperandTypeVarient> get_type_varient_from_type(const IR::TypeExprPtr type){
    //DOnt __always_inline this
    switch(type->get_kind()){
        case IR::TypeExprKind::IntTypeExpr:{
            return InstOperandTypeVarient::Int;
        }
        case IR::TypeExprKind::FloatTypeExpr:{
            return InstOperandTypeVarient::Float;
        }
        case IR::TypeExprKind::PtrTypeExpr:{
            return InstOperandTypeVarient::Ptr;
        }
        case IR::TypeExprKind::SIMDTypeExpr:{
                auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(type);
                if(simd_type == nullptr) return std::nullopt;
                auto element_type = simd_type->get_base_type();
                switch(element_type->get_kind()){
                    case IR::TypeExprKind::IntTypeExpr:{
                        return InstOperandTypeVarient::VecInt;
                    }
                    case IR::TypeExprKind::FloatTypeExpr:{  
                        return InstOperandTypeVarient::VecFloat;
                    }
                    case IR::TypeExprKind::PtrTypeExpr:{
                        return InstOperandTypeVarient::VecPtr;
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

template<typename E>
    requires (std::is_enum_v<E> && (!std::is_same_v<E, InstOperandTypeVarient>))
constexpr std::uint32_t operator|(InstOperandTypeVarient a, E b) {
    return static_cast<std::uint32_t>(a) | static_cast<std::uint32_t>(b);
}


enum class SyncScope:std::uint32_t{
    SingleThread = 1 << 0,
    Global = 1 << 1
};
}
}
