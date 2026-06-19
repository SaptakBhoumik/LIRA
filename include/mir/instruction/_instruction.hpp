#pragma once
#include "ast/ast.hpp"
#include <string>
#include <sys/cdefs.h>
#include "mir/destregister.hpp"
namespace LIRA {
namespace MIR{
enum class InstType:std::int16_t{
    ArithmeticBinaryInst,

    ArithmeticTrinaryInst,

    BitwiseTrinaryInst,

    //## Fixed-Point Arithmetic Instructions

    WideningBinaryInst,
    
    // ## Carry/Borrowing instructions
    // ## Combined Quotient and Remainder (`divmod`)
    WrapBinaryInst,
    // ## High-Half Multiply

    BitwiseBinaryInst,
    
    // ## Bitwise Trinary Instructions
 
    CmpBinaryInst,

    ConvInst,

    UnaryInst,
    
    NumericalClassifyInst,

    LocalInst,
    AllocaInst,
    LoadInst,//Even the atomic varient returns this as type. We use the is_atomic method to know if atomic or not
    StoreInst,//Even the atomic varient returns this as type. We use the is_atomic method to know if atomic or not
    GetAddressInst,
    PtrOffsetInst,
    ExtractElementInst,
    InsertElementInst,
    FenceInst,
    CmpXchgInst,

    FetchArithmeticBinInst,

    FetchBitwiseBinInst,

    FetchUnaryInst,

    RetInst,
    UnreachableInst,
    TrapInst,
    JmpInst,
    ConditionalJmpInst,
    SwitchInst,
    IndirectJmpInst,

    CallInst,

    ScalarSelectInst,
    LanewiseSelectInst,
    FreezeInst,
    VastartInst,
    VaendInst,
    VacopyInst,
    VaargInst,
    PtrMaskInst,
    PauseInst,
    AssumeInst,
    AssumeRangeInst,
    AssumeNotInst,
    AssumeNotRangeInst,
    ExpectInst,
    ExpectRangeInst,
    NopInst,
    AnnotationInst,
    Endbr64Inst,
    LaunderInst,
    StripInvariantGroupInst,

    CpuIdInst,
    RdTscInst,
    RdTscpInst,
    RdrandInst,
    RdseedInst,
    GetFpEnvInst,
    SetFpEnvInst,
    FpenvGetFieldInst,
    FpenvSetFieldInst,
    GetFpStatusInst,
    ClearFpStatusInst,
    AesEncInst,
    AesEncLastInst,
    AesDecInst,
    AesDecLastInst,
    AesImcInst,
    CTAesKeyGenAssistInst,
    RTAesKeyGenAssistInst,
    ClmulInst,
    CTSha1Rnds4Inst,
    RTSha1Rnds4Inst,
    Sha1NextEInst,
    Sha1Msg1Inst,
    Sha1Msg2Inst,
    Sha256Rnds2Inst,
    Sha256Msg1Inst,
    Sha256Msg2Inst,
    Crc32Inst,
    SyscallInst,
    RdsspInst,
    IncsspInst,
    SavePrevSspInst,
    RstorSspInst,
    SetssbsyInst,
    WrssInst
};

struct FastMathAttr {
    bool nnans = false;
    bool ninfs = false;
    bool nsz = false;
    bool arcp = false;
    bool contract = false;
    bool afns = false;
    bool reassoc = false;

    std::string to_string() const;
};

// I am going to define the instruction set of LIRA. A lot of the instructions are lot lowered. Like .add is lowered to .fadd, .iadd, .vadd and so on. It is done
// to make my life easier in the codegen phase. Although it is possible to merge a few of these instructions but I want to keep them separate because I think it will be better
// Although I admit I may be wrong and it may be better to merge some of these instructions but I will keep them separate for now 
class Inst {
    protected:
    LocalDestRegisterPtr destination;
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<FastMathAttr> fast_math_attr;//Only used for floating point instructions.
    public:
    Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::optional<FastMathAttr> fast_math_attr);
    
    virtual ~Inst() = default;

    virtual LocalDestRegisterPtr get_destination() const final;//For faster access if needed. Return nullptr if no destination
    virtual std::optional<FastMathAttr> get_fast_math_attr() const final;
    virtual InstType get_inst_type() const = 0;
    virtual IR::InstructionStmtPtr get_instruction_stmt() const final;//For error reporting
    virtual std::string to_string() const = 0;
    virtual IR::DebugInfoPtr get_debug_info() const final;//Return get_instruction_stmt()->get_value()->get_debug_info() if get_value() is not empty else nullptr.
};

using InstPtr = std::shared_ptr<Inst>;

enum class InstOperandTypeVarient:std::uint64_t{
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
    enum class OpType:std::uint64_t{
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
                auto element_type = simd_type->get_basetype();
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
constexpr std::uint64_t operator|(InstOperandTypeVarient a, E b) {
    return static_cast<std::uint64_t>(a) | static_cast<std::uint64_t>(b);
}


enum class SyncScope:std::uint64_t{
    SingleThread = 1 << 0,
    Global = 1 << 1
};
std::string to_string(SyncScope syncscope);

enum class AtomicOrdering:std::uint64_t{
    UNORDERED = 1 << 0,
    MONOTONIC = 1 << 1,
    ACQUIRE = 1 << 2,
    RELEASE = 1 << 3,
    ACQUIRE_RELEASE = 1 << 4, // acq_rel
    SEQUENTIALLY_CONSISTENT = 1 << 5 // seq_cst
};
std::string to_string(AtomicOrdering ordering);

enum class CallingConv:std::uint64_t{
    CCC = 1 << 0,
    FASTCC = 1 << 1,
    COLDCC = 1 << 2,
    TAILCC = 1 << 3,
};
std::string to_string(CallingConv ordering);



enum class FPEnvField:uint8_t {
    Round,
    FlushToZero,        // "ftz"
    DenormalsAreZero,   // "daz"
    ExceptMask,
    ExceptStatus,
};
std::string to_string(FPEnvField field);
}
}
