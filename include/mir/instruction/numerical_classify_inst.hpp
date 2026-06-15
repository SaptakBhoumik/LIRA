#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Numerical Classification operations ---------------------------
class NumericalClassifyInst:public Inst {
    //Handles both float and vector of float. Whether it is float or vector of float is determined by the type of the operand.
    protected:
    IR::LiteralExprPtr value;
    IR::TypeExprPtr value_type;

    public:
    enum class OpType:std::uint64_t{
        ISNAN = 1 << 6,
        ISINF = 1 << 7,
        ISFINITE = 1 << 11,
        ISNORMAL = 1 << 8,
        ISSUBNORMAL = 1 << 9,
        ISZERO = 1 << 10,
        ISNEGATIVE = 1 << 12,
        ISPOSITIVE = 1 << 13,
    };
    NumericalClassifyInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type);

    virtual ~NumericalClassifyInst() = default;

    virtual InstOperandTypeVarient get_type_varient() const = 0;
    virtual IR::TypeExprPtr get_value_type() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual OpType get_op_type() const = 0;//Whether it is neg or not etc.

    virtual InstType get_inst_type() const override final;
};


// --------------------------- Float Classification operations ---------------------------
class FloatClassifyInst:public NumericalClassifyInst{
    protected:
    FastMathAttr fast_math_attr;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    FloatClassifyInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    virtual FastMathAttr get_fast_math_attr() const final;

    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_operand_type() const final;
    virtual std::size_t get_bitwidth() const final;
    virtual bool is_brain_float() const final;
    
    virtual InstOperandTypeVarient get_type_varient() const override final;
};

class FloatIsNanInst:public FloatClassifyInst {
    public:
    FloatIsNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatIsInfInst:public FloatClassifyInst {
    public:
    FloatIsInfInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatIsFiniteInst:public FloatClassifyInst {
    public:
    FloatIsFiniteInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatIsNormalInst:public FloatClassifyInst {
    public:
    FloatIsNormalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatIsSubnormalInst:public FloatClassifyInst {
    public:
    FloatIsSubnormalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type, 
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatIsZeroInst:public FloatClassifyInst {
    public:
    FloatIsZeroInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatIsNegativeInst:public FloatClassifyInst {
    public:
    FloatIsNegativeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatIsPositiveInst:public FloatClassifyInst {
    public:
    FloatIsPositiveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
//--------------------------- Vector Float Classification operations ---------------------------
class VecFloatClassifyInst:public NumericalClassifyInst{
    protected:
    FastMathAttr fast_math_attr;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    VecFloatClassifyInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                            FastMathAttr fast_math_attr);

    virtual FastMathAttr get_fast_math_attr() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;
    virtual std::shared_ptr<IR::FloatTypeExpr> get_basetype() const final;
    virtual std::size_t get_num_elements() const final;
    
    virtual InstOperandTypeVarient get_type_varient() const override final;
};

class VecFloatIsNanInst:public VecFloatClassifyInst {
    public:
    VecFloatIsNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatIsInfInst:public VecFloatClassifyInst {
    public:
    VecFloatIsInfInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatIsFiniteInst:public VecFloatClassifyInst {
    public:
    VecFloatIsFiniteInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatIsNormalInst:public VecFloatClassifyInst {
    public:
    VecFloatIsNormalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatIsSubnormalInst:public VecFloatClassifyInst {
    public:
    VecFloatIsSubnormalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatIsZeroInst:public VecFloatClassifyInst {
    public:
    VecFloatIsZeroInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatIsNegativeInst:public VecFloatClassifyInst {
    public:
    VecFloatIsNegativeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatIsPositiveInst:public VecFloatClassifyInst {
    public:
    VecFloatIsPositiveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}