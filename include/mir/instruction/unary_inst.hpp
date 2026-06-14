#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Unary operations ---------------------------
class UnaryInst:public Inst {
    protected:
    LocalDestRegisterPtr destination;//The destination variable token for identifying the output variable
    IR::LiteralExprPtr value;
    FastMathAttr fast_math_attr;//Only for floating point. All fields are false for non floating point types
    public:
    enum class OpType:std::uint64_t{
        NEG = 1 << 6,
        NOT = 1 << 7,
    };
    UnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr);

    virtual ~UnaryInst() = default;

    virtual FastMathAttr get_fast_math_attr() const final;
    virtual InstOperandTypeVarient get_type_varient() const final;//Can be calculated easily from ``type``. Just a helper function
    virtual IR::TypeExprPtr get_type() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual OpType get_op_type() const = 0;//Whether it is neg or not etc.

    virtual InstType get_inst_type() const override final;
};

// --------------------------- Scalar Unary operations ---------------------------
class ScalarUnaryInst:public UnaryInst{
    // When the instruction doesnt act lane wise
    public:
    ScalarUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr);

    virtual bool is_brain_float() const final;//Whether the operand type is brain float or not. Just a helper function to make life easier. False for integer
    virtual std::size_t get_type_bitwidth() const final;//Returns the bit width of the in type. Calculated automatically
};

class IntNegInst:public ScalarUnaryInst{
    public:
    IntNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);

    std::shared_ptr<IR::IntTypeExpr> get_casted_type() const;//Returns the type casted to IntTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatNegInst:public ScalarUnaryInst{
    public:
    FloatNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_type() const;//Returns the type casted to FloatTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntNotInst:public ScalarUnaryInst{
    public:
    IntNotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);

    std::shared_ptr<IR::IntTypeExpr> get_casted_type() const;//Returns the type casted to IntTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


// --------------------------- Vector Unary operations ---------------------------
class LaneWiseUnaryInst:public UnaryInst{
    // When the instruction act lane wise
    public:
    LaneWiseUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr);

    virtual bool is_brain_float() const final;//Whether the operand base type is brain float or not. Just a helper function to make life easier. False for integer
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_type() const final;//Returns the out type casted to SIMDTypeExpr. 
    virtual std::size_t get_basetype_bitwidth() const final;//Returns the bit width of the type. Calculated automatically
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Calculated automatically
};

class LaneWiseIntNegInst:public LaneWiseUnaryInst{
    public:
    LaneWiseIntNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);

    std::shared_ptr<IR::IntTypeExpr> get_casted_basetype() const;//Returns the base type casted to IntTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWiseFloatNegInst:public LaneWiseUnaryInst{
    public:
    LaneWiseFloatNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_basetype() const;//Returns the base type casted to FloatTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWiseIntNotInst:public LaneWiseUnaryInst{
    public:
    LaneWiseIntNotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);

    std::shared_ptr<IR::IntTypeExpr> get_casted_basetype() const;//Returns the base type casted to IntTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}