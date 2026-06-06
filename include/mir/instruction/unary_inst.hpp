#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Unary operations ---------------------------
class UnaryInst:public Inst {
    protected:
    IR::InstructionStmtPtr instruction_stmt;

    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable
    IR::LiteralExprPtr value;
    IR::TypeExprPtr type;//Reduced in type. 
    public:
    enum class OpType:std::uint32_t{
        NEG = 1 << 6,
        NOT = 1 << 7,
    };
    UnaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type);

    virtual ~UnaryInst() = default;

    virtual InstOperandTypeVarient get_type_varient() const final;//Can be calculated easily from ``type``. Just a helper function
    virtual IR::TypeExprPtr get_type() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual OpType get_op_type() const = 0;//Whether it is neg or not etc.

    virtual std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override final;
    virtual InstType get_inst_type() const override final;
    virtual IR::InstructionStmtPtr get_instruction_stmt() const override final;
};

// --------------------------- Scalar Unary operations ---------------------------
class RegularUnaryInst:public UnaryInst{
    // When the instruction doesnt act lane wise
    FastMathAttr fast_math_attr;//Only for floating point
    // Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.
    public:
    RegularUnaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type, FastMathAttr fast_math_attr);

    virtual FastMathAttr get_fast_math_attr() const final;
    virtual bool is_brain_float() const final;//Whether the operand type is brain float or not. Just a helper function to make life easier. False for integer

    virtual std::size_t get_type_bit_width() const final;//Returns the bit width of the in type. Calculated automatically
};

class IntNegInst:public RegularUnaryInst{
    public:
    IntNegInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type);

    std::shared_ptr<IR::IntTypeExpr> get_casted_type() const;//Returns the type casted to IntTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatNegInst:public RegularUnaryInst{
    public:
    FloatNegInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type, FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_type() const;//Returns the type casted to FloatTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntNotInst:public RegularUnaryInst{
    public:
    IntNotInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type);

    std::shared_ptr<IR::IntTypeExpr> get_casted_type() const;//Returns the type casted to IntTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


// --------------------------- Vector Unary operations ---------------------------
class LaneWiseUnaryInst:public UnaryInst{
    // When the instruction doesnt act lane wise
    FastMathAttr fast_math_attr;//Only for floating point
    // Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.
    public:
    LaneWiseUnaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type, FastMathAttr fast_math_attr);

    virtual FastMathAttr get_fast_math_attr() const final;
    virtual bool is_brain_float() const final;//Whether the operand base type is brain float or not. Just a helper function to make life easier. False for integer

    virtual std::size_t get_basetype_bit_width() const final;//Returns the bit width of the type. Calculated automatically
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Calculated automatically
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_type() const final;//Returns the out type casted to SIMDTypeExpr. 
};

class LaneWiseIntNegInst:public LaneWiseUnaryInst{
    public:
    LaneWiseIntNegInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type);

    std::shared_ptr<IR::IntTypeExpr> get_casted_basetype() const;//Returns the base type casted to IntTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWiseFloatNegInst:public LaneWiseUnaryInst{
    public:
    LaneWiseFloatNegInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type, FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_basetype() const;//Returns the base type casted to FloatTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWiseIntNotInst:public LaneWiseUnaryInst{
    public:
    LaneWiseIntNotInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type);

    std::shared_ptr<IR::IntTypeExpr> get_casted_basetype() const;//Returns the base type casted to IntTypeExpr. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}