#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Fetch Unary operations ---------------------------
class FetchUnaryInst:public Inst {
    protected:
    std::size_t alignment;//The alignment of the memory access in bytes
    bool volatile_;//Whether the memory access is volatile or not
    std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info;//If the instruction is atomic, then this field contains the sync scope and atomic ordering of the instruction. Otherwise, it is std::nullopt
    
    IR::LiteralExprPtr value;
    public:
    enum class OpType:std::uint64_t{
        FETCH_NEG = 1 << 6,
        FETCH_NOT = 1 << 7,
        FETCH_ABS = 1 << 8,
        FETCH_CEIL = 1 << 9,
        FETCH_FLOOR = 1 << 10,
        FETCH_INTEGRAL_PART = 1 << 11,
        FETCH_FRACTIONAL_PART = 1 << 12,
        FETCH_ROUND_NEAREST = 1 << 13,
        FETCH_ROUND_EVEN = 1 << 14,
        FETCH_SQRT = 1 << 15,
        FETCH_RECIPROCAL = 1 << 16,
        FETCH_RSQRT = 1 << 17,
        FETCH_POPCOUNT = 1 << 18,
        FETCH_CLZ = 1 << 19,
        FETCH_CTZ = 1 << 20,
        FETCH_PARITY = 1 << 21,
        FETCH_BSWAP = 1 << 22,
        FETCH_BITREVERSE = 1 << 23,
        FETCH_CLRSB = 1 << 24,
        FETCH_BLSI = 1 << 25,
        FETCH_BLSR = 1 << 26,
        FETCH_BLSMASK = 1 << 27
    };
    FetchUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                  std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, std::optional<FastMathAttr> fast_math_attr);

    virtual ~FetchUnaryInst() = default;

    virtual InstOperandTypeVarient get_type_varient() const = 0;
    virtual IR::TypeExprPtr get_type() const final;
    virtual IR::LiteralExprPtr get_value() const final;

    virtual std::size_t get_alignment() const final;
    virtual bool is_volatile() const final;
    virtual std::optional<std::pair<SyncScope,AtomicOrdering>> get_atomic_info() const final;
    virtual OpType get_op_type() const = 0;

    virtual InstType get_inst_type() const override final;
};

// --------------------------- Int Fetch Unary operations ---------------------------
class IntFetchUnaryInst:public FetchUnaryInst{
    protected:
    bool nuw;
    bool nsw;
    bool zero_poison;
    
    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    IntFetchUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, bool nuw, bool nsw, bool zero_poison);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_zero_poison() const final;

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;
    virtual std::size_t get_bitwidth() const final;
    
    virtual InstOperandTypeVarient get_type_varient() const override final;
};

class IntFetchNegInst:public IntFetchUnaryInst {
    public:
    IntFetchNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, bool nsw);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchNotInst:public IntFetchUnaryInst {
    public:
    IntFetchNotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchAbsInst:public IntFetchUnaryInst {
    public:
    IntFetchAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, bool nsw);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchPopcountInst:public IntFetchUnaryInst {
    public:
    IntFetchPopcountInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                         std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchCLZInst:public IntFetchUnaryInst {
    public:
    IntFetchCLZInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, bool zero_poison);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchCTZInst:public IntFetchUnaryInst {
    public:
    IntFetchCTZInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, bool zero_poison);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchParityInst:public IntFetchUnaryInst {
    public:
    IntFetchParityInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                       std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchBswapInst:public IntFetchUnaryInst {
    public:
    IntFetchBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchBitreverseInst:public IntFetchUnaryInst {
    public:
    IntFetchBitreverseInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                          std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchCLRSBInst:public IntFetchUnaryInst {
    public:
    IntFetchCLRSBInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchBLSIInst:public IntFetchUnaryInst {
    public:
    IntFetchBLSIInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                     std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchBLSRInst:public IntFetchUnaryInst {
    public:
    IntFetchBLSRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                     std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFetchBLSMaskInst:public IntFetchUnaryInst {
    public:
    IntFetchBLSMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                        std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

// --------------------------- Float Fetch Unary operations ---------------------------
class FloatFetchUnaryInst:public FetchUnaryInst{
    protected:
    bool approx;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    FloatFetchUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                        std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, 
                        FastMathAttr fast_math_attr,bool approx);

    virtual bool is_approx() const final;

    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_operand_type() const final;
    virtual std::size_t get_bitwidth() const final;
    virtual bool is_brain_float() const final;
    
    virtual InstOperandTypeVarient get_type_varient() const override final;
};

class FloatFetchNegInst:public FloatFetchUnaryInst {
    public:
    FloatFetchNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                      FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchAbsInst:public FloatFetchUnaryInst {
    public:
    FloatFetchAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                      FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchCeilInst:public FloatFetchUnaryInst {
    public:
    FloatFetchCeilInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                       std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                       FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchFloorInst:public FloatFetchUnaryInst {
    public:
    FloatFetchFloorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                        std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                        FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchIntregralPartInst:public FloatFetchUnaryInst {
    public:
    FloatFetchIntregralPartInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                                FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchFractionalPartInst:public FloatFetchUnaryInst {
    public:
    FloatFetchFractionalPartInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                                FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchRoundNearestInst:public FloatFetchUnaryInst {
    public:
    FloatFetchRoundNearestInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                                FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchRoundEvenInst:public FloatFetchUnaryInst {
    public:
    FloatFetchRoundEvenInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                            std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                            FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchSqrtInst:public FloatFetchUnaryInst {
    public:
    FloatFetchSqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                       std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                       FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchReciprocalInst:public FloatFetchUnaryInst {
    public:
    FloatFetchReciprocalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                             std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                             FastMathAttr fast_math_attr, bool approx);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchRsqrtInst:public FloatFetchUnaryInst {
    public:
    FloatFetchRsqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                        std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                        FastMathAttr fast_math_attr, bool approx);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFetchBswapInst:public FloatFetchUnaryInst {
    public:
    FloatFetchBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                        std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                        FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}