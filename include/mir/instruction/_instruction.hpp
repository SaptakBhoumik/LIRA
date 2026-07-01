#pragma once
#include "ast/ast.hpp"
#include <cstddef>
#include <string>
#include <sys/cdefs.h>
#include "mir/destregister.hpp"
namespace LIRA {
namespace MIR{
enum class InstType:std::int16_t{
    ArithmeticBinaryInst,

    ArithmeticTrinaryInst,

    WideningBinaryInst,
    
    DivmodInst,
    WideningDivmodInst,
    MulHiInst,
    MulFixInst,

    CarrBorrType1Inst,
    CarrBorrType2Inst,

    WrapBinaryInst,

    BitwiseBinaryInst,
    
    BitwiseTrinaryInst,
 
    CmpBinaryInst,

    ConvInst,

    UnaryInst,
    
    NumericalClassifyInst,

    LocalInst,
    AllocaInst,
    LoadInst,
    StoreInst,
    BroadcastLoadInst,
    MaskedLoadInst,
    MaskedStoreInst,
    MaskedGatherInst,
    MaskedScatterInst,
    PrefetchInst,
    MemcopyInst,
    MemsetInst,
    MemcmpInst,
    GetAddressInst,
    PtrOffsetInst,
    StackSaveInst,
    StackRestoreInst,
    ExtractElementInst,
    InsertElementInst,
    FenceInst,
    CmpXchgInst,
    ClflushInst,
    ClwbInst,
    CldemoteInst,
    LifetimeStartInst,
    LifetimeEndInst,
    InvariantStartInst,
    InvariantEndInst,

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

    ShuffleVectorInst,
    TernLogInst,
    SplatInst,
    StepVectorInst,
    InsertSubVectorInst,
    ExtractSubVectorInst,
    ActiveLaneMaskInst,
    AddSubInst,
    ReduceArithmeticSIMDInst,
    IntReduceBitwiseSIMDInst,
    HArithmeticSIMDInst,
    IntHBitwiseSIMDInst,
    DotInst,
    SADInst,
    PackSatInst,
    UnpackLoInst,
    UnpackHiInst,
    CompressInst,
    ExpandInst,
    InterleaveInst,
    DeinterleaveInst,
    MaskToIntInst,
    IntToMaskInst,

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
    AesKeyGenAssistInst,
    ClmulInst,
    Sha1Rnds4Inst,
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

enum class TypeVariant:std::uint64_t{
    // A lot of operands are divided into int,float,ptr,vector etc based on the type they operate on. Not every instruction show this property but a lot do. It is for them
    Int = 1 << 0,
    Float = 1 << 1,
    Ptr = 1 << 2,
    VecInt = 1 << 3,
    VecFloat = 1 << 4,
    VecPtr = 1 << 5
    /*
    We will usually do matching on TypeVariant | Opcode. So for every enum opcode, make sure to have a unique bit pattern starting from 1 << 6.
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

bool is_vector_typevariant(const TypeVariant var);
bool is_scalar_typevariant(const TypeVariant var);
bool is_ptr_typevariant(const TypeVariant var);
bool is_float_typevariant(const TypeVariant var);
bool is_int_typevariant(const TypeVariant var);

std::optional<TypeVariant> get_type_variant_from_type(const IR::TypeExprPtr type);

template<typename E>
    requires (std::is_enum_v<E> && (!std::is_same_v<E, TypeVariant>))
constexpr std::uint64_t operator|(TypeVariant a, E b){
    return static_cast<std::uint64_t>(a) | static_cast<std::uint64_t>(b);
}


enum class SyncScope:std::uint64_t{
    SingleThread = 1 << 0,
    Global = 1 << 1
};
std::string to_string(SyncScope syncscope);

enum class AtomicOrdering:std::uint64_t{
    // ACQUIRE and RELEASE have same strength but enum says ACQUIRE<RELEASE because C++ needs distinct type. Keep in mind when comparing 
    UNORDERED = 1 << 0,
    MONOTONIC = 1 << 1,
    ACQUIRE = 1 << 2,
    RELEASE = 1 << 3,
    ACQUIRE_RELEASE = 1 << 4, // acq_rel
    SEQUENTIALLY_CONSISTENT = 1 << 5 // seq_cst
};
std::string to_string(AtomicOrdering ordering);

struct CommonFetchInstAttrs{
    std::optional<std::pair<AtomicOrdering, SyncScope>> atomic_ordering;
    std::size_t alignment = 0;
    bool volatile_flag = false;

    std::string to_string() const;
};

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

struct CommonMemoryInstAttrs{
    std::size_t alignment = 0;
    std::size_t dereferenceable_bytes = 0;
    bool volatile_ = false;
    bool nontemporal = false;
    bool nonull = false;
};
}
}
