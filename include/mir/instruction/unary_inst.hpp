#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Unary operations ---------------------------
class UnaryInst:public Inst {
    protected:
    IR::LiteralExprPtr value;
    public:
    enum class OpType:std::uint64_t{
        NEG = 1 << 6,
        NOT = 1 << 7,
        ABS = 1 << 8,
        CEIL = 1 << 9,
        FLOOR = 1 << 10,
        INTEGRAL_PART = 1 << 11,
        FRACTIONAL_PART = 1 << 12,
        ROUND_NEAREST = 1 << 13,
        ROUND_EVEN = 1 << 14,
        SQRT = 1 << 15,
        RECIPROCAL = 1 << 16,
        RSQRT = 1 << 17,
        POPCOUNT = 1 << 18,
        CLZ = 1 << 19,
        CTZ = 1 << 20,
        PARITY = 1 << 21,
        BSWAP = 1 << 22,
        BITREVERSE = 1 << 23,
        CLRSB = 1 << 24,
        BLSI = 1 << 25,
        BLSR = 1 << 26,
        BLSMASK = 1 << 27
    };
    UnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, std::optional<FastMathAttr> fast_math_attr);

    virtual TypeVariant get_type_variant() const = 0;
    virtual IR::TypeExprPtr get_type() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual OpType get_op_type() const = 0;//Whether it is neg or not etc.

    virtual InstType get_inst_type() const override final;
};

// --------------------------- Int Unary operations ---------------------------
class IntUnaryInst:public UnaryInst{
    protected:
    bool nuw;
    bool nsw;
    bool zero_poison;
    
    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    IntUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, bool nuw, bool nsw, bool zero_poison);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_zero_poison() const final;

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;
    virtual std::size_t get_bitwidth() const final;
    
    virtual TypeVariant get_type_variant() const override final;
};

class IntNegInst:public IntUnaryInst {
    public:
    IntNegInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, bool nsw);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntNotInst:public IntUnaryInst {
    public:
    IntNotInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntAbsInst:public IntUnaryInst {
    public:
    IntAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, bool nsw);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntPopcountInst:public IntUnaryInst {
    public:
    IntPopcountInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntCLZInst:public IntUnaryInst {
    public:
    IntCLZInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, bool zero_poison);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntCTZInst:public IntUnaryInst {
    public:
    IntCTZInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, bool zero_poison);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntParityInst:public IntUnaryInst {
    public:
    IntParityInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntBswapInst:public IntUnaryInst {
    public:
    IntBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntBitreverseInst:public IntUnaryInst {
    public:
    IntBitreverseInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntCLRSBInst:public IntUnaryInst {
    public:
    IntCLRSBInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntBLSIInst:public IntUnaryInst {
    public:
    IntBLSIInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntBLSRInst:public IntUnaryInst {
    public:
    IntBLSRInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntBLSMaskInst:public IntUnaryInst {
    public:
    IntBLSMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

// --------------------------- Vector Int Unary operations ---------------------------
class VecIntUnaryInst:public UnaryInst{
    protected:
    bool nuw;
    bool nsw;
    bool zero_poison;
    
    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    VecIntUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, bool nuw, bool nsw, bool zero_poison);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_zero_poison() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;
    virtual std::size_t get_basetype_bitwidth() const final;
    virtual std::size_t get_num_elements() const final;
    
    virtual TypeVariant get_type_variant() const override final;
};

class VecIntNegInst:public VecIntUnaryInst {
    public:
    VecIntNegInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, bool nsw);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntNotInst:public VecIntUnaryInst {
    public:
    VecIntNotInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntAbsInst:public VecIntUnaryInst {
    public:
    VecIntAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, bool nsw);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntPopcountInst:public VecIntUnaryInst {
    public:
    VecIntPopcountInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntCLZInst:public VecIntUnaryInst {
    public:
    VecIntCLZInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, bool zero_poison);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntCTZInst:public VecIntUnaryInst {
    public:
    VecIntCTZInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, bool zero_poison);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntParityInst:public VecIntUnaryInst {
    public:
    VecIntParityInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntBswapInst:public VecIntUnaryInst {
    public:
    VecIntBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntBitreverseInst:public VecIntUnaryInst {
    public:
    VecIntBitreverseInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntCLRSBInst:public VecIntUnaryInst {
    public:
    VecIntCLRSBInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntBLSIInst:public VecIntUnaryInst {
    public:
    VecIntBLSIInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntBLSRInst:public VecIntUnaryInst {
    public:
    VecIntBLSRInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntBLSMaskInst:public VecIntUnaryInst {
    public:
    VecIntBLSMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override;
    std::string to_string() const override;
};
// --------------------------- Float Unary operations ---------------------------
class FloatUnaryInst:public UnaryInst{
    protected:
    bool approx;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    FloatUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr,bool approx);

    virtual bool is_approx() const final;

    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_operand_type() const final;
    virtual std::size_t get_bitwidth() const final;
    virtual bool is_brain_float() const final;
    
    virtual TypeVariant get_type_variant() const override final;
};

class FloatNegInst:public FloatUnaryInst {
    public:
    FloatNegInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatAbsInst:public FloatUnaryInst {
    public:
    FloatAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatCeilInst:public FloatUnaryInst {
    public:
    FloatCeilInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatFloorInst:public FloatUnaryInst {
    public:
    FloatFloorInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatIntegralPartInst:public FloatUnaryInst {
    public:
    FloatIntegralPartInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatFractionalPartInst:public FloatUnaryInst {
    public:
    FloatFractionalPartInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatRoundNearestInst:public FloatUnaryInst {
    public:
    FloatRoundNearestInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatRoundEvenInst:public FloatUnaryInst {
    public:
    FloatRoundEvenInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatSqrtInst:public FloatUnaryInst {
    public:
    FloatSqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatReciprocalInst:public FloatUnaryInst {
    public:
    FloatReciprocalInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr, bool approx);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatRsqrtInst:public FloatUnaryInst {
    public:
    FloatRsqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr, bool approx);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatBswapInst:public FloatUnaryInst {
    public:
    FloatBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

// --------------------------- Vector Float Unary operations ---------------------------
class VecFloatUnaryInst:public UnaryInst{
    protected:
    bool approx;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    VecFloatUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                      FastMathAttr fast_math_attr,bool approx);

    virtual bool is_approx() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;
    virtual std::shared_ptr<IR::FloatTypeExpr> get_basetype() const final;
    virtual std::size_t get_num_elements() const final;
    
    virtual TypeVariant get_type_variant() const override final;
};

class VecFloatNegInst:public VecFloatUnaryInst {
    public:
    VecFloatNegInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatAbsInst:public VecFloatUnaryInst {
    public:
    VecFloatAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatCeilInst:public VecFloatUnaryInst {
    public:
    VecFloatCeilInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                      FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatFloorInst:public VecFloatUnaryInst {
    public:
    VecFloatFloorInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                      FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatIntegralPartInst:public VecFloatUnaryInst {
    public:
    VecFloatIntegralPartInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                              FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatFractionalPartInst:public VecFloatUnaryInst {
    public:
    VecFloatFractionalPartInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                               FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatRoundNearestInst:public VecFloatUnaryInst {
    public:
    VecFloatRoundNearestInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                             FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatRoundEvenInst:public VecFloatUnaryInst {
    public:
    VecFloatRoundEvenInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                          FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatSqrtInst:public VecFloatUnaryInst {
    public:
    VecFloatSqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                     FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatReciprocalInst:public VecFloatUnaryInst {
    public:
    VecFloatReciprocalInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                           FastMathAttr fast_math_attr, bool approx);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatRsqrtInst:public VecFloatUnaryInst {
    public:
    VecFloatRsqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                      FastMathAttr fast_math_attr, bool approx);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecFloatBswapInst:public VecFloatUnaryInst {
    public:
    VecFloatBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, 
                      FastMathAttr fast_math_attr);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

}
}