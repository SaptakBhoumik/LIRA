#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Read write modify operations ---------------------------
class FetchArithmeticBinInst:public Inst {
    protected:
    std::size_t alignment;//The alignment of the memory access in bytes
    bool volatile_;//Whether the memory access is volatile or not
    std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info;//If the instruction is atomic, then this field contains the sync scope and atomic ordering of the instruction. Otherwise, it is std::nullopt
    
    IR::LiteralExprPtr pointer;//Always of type ptr
    IR::LiteralExprPtr value;//Same type as destination
    public:
    enum class OpType:std::uint64_t{
        FETCH_XCHG = 1 << 6,
        FETCH_ADD = 1 << 7,
        FETCH_SUB = 1 << 8,
        FETCH_MUL = 1 << 9,
        FETCH_DIV = 1 << 10,
        FETCH_REM = 1 << 11,
        FETCH_COPYSIGN = 1 << 12,
        FETCH_MIN = 1 << 13,
        FETCH_MAX = 1 << 14,
        FETCH_AVG = 1 << 15,
    };
    FetchArithmeticBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                  std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, std::optional<FastMathAttr> fast_math_attr);

    virtual ~FetchArithmeticBinInst() = default;

    virtual InstOperandTypeVarient get_type_varient() const = 0;
    virtual IR::TypeExprPtr get_type() const final;
    virtual IR::LiteralExprPtr get_pointer() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual std::size_t get_alignment() const final;
    virtual bool is_volatile() const final;
    virtual std::optional<std::pair<SyncScope,AtomicOrdering>> get_atomic_info() const final;
    virtual OpType get_op_type() const = 0;

    virtual InstType get_inst_type() const override final;
};


// --------------------------- Integer read modify operations ---------------------------
class IntFetchArithmeticBinInst:public FetchArithmeticBinInst {
    protected:
    bool nuw;
    bool nsw;
    bool saturating;
    bool exact;
    bool unsigned_;
    bool floor;

    std::string to_string_helper(const std::string op_name) const;
    public:
    IntFetchArithmeticBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                     std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                     bool nuw, bool nsw, bool saturating, bool exact, bool unsigned_, bool floor);
    
    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_saturating() const final;
    virtual bool is_exact() const final;
    virtual bool is_unsigned() const final;
    virtual bool is_floor() const final;

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_type() const final;//Returns the type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the type. Calculated automatically

    virtual InstOperandTypeVarient get_type_varient() const override final;
};


class IntXchgInst:public IntFetchArithmeticBinInst {
    public:
    IntXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class IntFetchAddInst:public IntFetchArithmeticBinInst {
    public:
    IntFetchAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool nuw, bool nsw, bool saturating, bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class IntFetchSubInst:public IntFetchArithmeticBinInst {
    public:
    IntFetchSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool nuw, bool nsw, bool saturating, bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class IntFetchMulInst:public IntFetchArithmeticBinInst {
    public:
    IntFetchMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool nuw, bool nsw, bool saturating, bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class IntFetchDivInst:public IntFetchArithmeticBinInst {
    public:
    IntFetchDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool unsigned_, bool exact);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class IntFetchRemInst:public IntFetchArithmeticBinInst {
    public:
    IntFetchRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class IntFetchCopySignInst:public IntFetchArithmeticBinInst {
    public:
    IntFetchCopySignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                         std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, 
                         bool nsw);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class IntFetchMaxInst:public IntFetchArithmeticBinInst {
    public:
    IntFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class IntFetchMinInst:public IntFetchArithmeticBinInst {
    public:
    IntFetchMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class IntFetchAvgInst:public IntFetchArithmeticBinInst {
    public:
    IntFetchAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool nuw, bool nsw, bool unsigned_, bool floor);

    OpType get_op_type() const override;
    std::string to_string() const override;
};
// --------------------------- Float read modify operations ---------------------------
class FloatFetchArithmeticBinInst:public FetchArithmeticBinInst {
    protected:
    bool unordered;
    bool ieee754_2019;

    std::string to_string_helper(const std::string op_name) const;
    public:
    FloatFetchArithmeticBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                      FastMathAttr fast_math_attr, bool unordered, bool ieee754_2019);

    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_type() const final;//Returns the type casted to FloatTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the type. Calculated automatically
    virtual bool is_brain_float() const final;//Whether the type is brain float or not. Just a helper function to make life easier

    virtual InstOperandTypeVarient get_type_varient() const override final;
};


class FloatXchgInst:public FloatFetchArithmeticBinInst {
    public:
    FloatXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class FloatFetchAddInst:public FloatFetchArithmeticBinInst {
    public:
    FloatFetchAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                      FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class FloatFetchSubInst:public FloatFetchArithmeticBinInst {
    public:
    FloatFetchSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class FloatFetchMulInst:public FloatFetchArithmeticBinInst {
    public:
    FloatFetchMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class FloatFetchDivInst:public FloatFetchArithmeticBinInst {
    public:
    FloatFetchDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                      FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class FloatFetchRemInst:public FloatFetchArithmeticBinInst {
    public:
    FloatFetchRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class FloatFetchCopySignInst:public FloatFetchArithmeticBinInst {
    public:
    FloatFetchCopySignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                         std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, 
                         FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class FloatFetchMaxInst:public FloatFetchArithmeticBinInst {
    public:
    FloatFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                      FastMathAttr fast_math_attr, bool unordered, bool ieee754_2019);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class FloatFetchMinInst:public FloatFetchArithmeticBinInst {
    public:
    FloatFetchMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                      FastMathAttr fast_math_attr, bool unordered, bool ieee754_2019);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class FloatFetchAvgInst:public FloatFetchArithmeticBinInst {
    public:
    FloatFetchAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};
}
}