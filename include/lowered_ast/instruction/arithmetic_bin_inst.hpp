#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Arithmatic Binary operations ---------------------------
class ArithmeticBinaryInst:public Inst {
    protected:
    IR::InstructionStmtPtr instruction_stmt;

    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::TypeExprPtr type;//Reduced type. 
    public:
    ArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    virtual ~ArithmeticBinaryInst() = default;

    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;

    virtual std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override final;
    virtual InstType get_inst_type() const override final;
    virtual IR::InstructionStmtPtr get_instruction_stmt() const override final;
};

// ---------------------------- Integer binary operations ---------------------------
class IntArithmeticBinaryInst:public ArithmeticBinaryInst {
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool unsigned_;//Whether it is unsigned operation or not
    bool exact;//Whether it has the exact attribute
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used
    public:
    IntArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                            bool nuw, bool nsw, bool unsigned_, bool exact);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_unsigned() const final;
    virtual bool is_exact() const final;

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bit_width() const final;//Returns the bit width of the operand type. Just a helper function to make life easier
};

class IntAddInst:public IntArithmeticBinaryInst {
    public:
    IntAddInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                bool nuw, bool nsw);

    std::string to_string() const override;
};


class IntSubInst:public IntArithmeticBinaryInst {
    public:
    IntSubInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                bool nuw, bool nsw);

    std::string to_string() const override;
};


class IntMulInst:public IntArithmeticBinaryInst {
    public:
    IntMulInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                bool nuw, bool nsw);

    std::string to_string() const override;
};

class IntDivInst:public IntArithmeticBinaryInst {
    public:
    IntDivInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                bool unsigned_, bool exact);

    std::string to_string() const override;
};

class IntRemInst:public IntArithmeticBinaryInst {
    public:
    IntRemInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                bool unsigned_);

    std::string to_string() const override;
};

// ----------------------------- Vector integer binary operations ---------------------------
class VecIntArithmeticBinaryInst:public ArithmeticBinaryInst {
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool unsigned_;//Whether it is unsigned operation or not
    bool exact;//Whether it has the exact attribute
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used
    public:
    VecIntArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                bool nuw, bool nsw, bool unsigned_, bool exact);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_unsigned() const final;
    virtual bool is_exact() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_basetype_width() const final;//Returns the bit width of the operand basetype. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
};

class VecIntAddInst:public VecIntArithmeticBinaryInst {
    public:
    VecIntAddInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                bool nuw, bool nsw);

    std::string to_string() const override;
};


class VecIntSubInst:public VecIntArithmeticBinaryInst {
    public:
    VecIntSubInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                bool nuw, bool nsw);

    std::string to_string() const override;
};


class VecIntMulInst:public VecIntArithmeticBinaryInst {
    public:
    VecIntMulInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                bool nuw, bool nsw);

    std::string to_string() const override;
};

class VecIntDivInst:public VecIntArithmeticBinaryInst {
    public:
    VecIntDivInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                bool unsigned_, bool exact);

    std::string to_string() const override;
};

class VecIntRemInst:public VecIntArithmeticBinaryInst {
    public:
    VecIntRemInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                bool unsigned_);

    std::string to_string() const override;
};


// ---------------------------- Float binary operations ---------------------------
class FloatArithmeticBinaryInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    FloatArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                FastMathAttr fast_math_attr);

    virtual FastMathAttr get_fast_math_attr() const final;

    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bit_width() const final;//Returns the bit width of the operand type. Just a helper function to make life easier
};
class FloatAddInst:public FloatArithmeticBinaryInst {
    public:
    FloatAddInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                FastMathAttr fast_math_attr);

    std::string to_string() const override;
};

class FloatSubInst:public FloatArithmeticBinaryInst {
    public:
    FloatSubInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                FastMathAttr fast_math_attr);

    std::string to_string() const override;
};

class FloatMulInst:public FloatArithmeticBinaryInst {
    public:
    FloatMulInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                FastMathAttr fast_math_attr);

    std::string to_string() const override;
};

class FloatDivInst:public FloatArithmeticBinaryInst {
    public:
    FloatDivInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                FastMathAttr fast_math_attr);

    std::string to_string() const override;
};

class FloatRemInst:public FloatArithmeticBinaryInst {
    public:
    FloatRemInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                FastMathAttr fast_math_attr);

    std::string to_string() const override;
};


// ---------------------------- Vector Float binary operations ---------------------------
class VecFloatArithmeticBinaryInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    VecFloatArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                FastMathAttr fast_math_attr);

    virtual FastMathAttr get_fast_math_attr() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::shared_ptr<IR::FloatTypeExpr> get_basetype() const final;//We dont return width of base type because it can be f16,bf16 and so on. Width alone not enough
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
};

class VecFloatAddInst:public VecFloatArithmeticBinaryInst {
    public:
    VecFloatAddInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                    FastMathAttr fast_math_attr);

    std::string to_string() const override;
};

class VecFloatSubInst:public VecFloatArithmeticBinaryInst {
    public:
    VecFloatSubInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                    FastMathAttr fast_math_attr);

    std::string to_string() const override;
};

class VecFloatMulInst:public VecFloatArithmeticBinaryInst {
    public:
    VecFloatMulInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                    FastMathAttr fast_math_attr);

    std::string to_string() const override;
};

class VecFloatDivInst:public VecFloatArithmeticBinaryInst {
    public:
    VecFloatDivInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                    FastMathAttr fast_math_attr);

    std::string to_string() const override;
};

class VecFloatRemInst:public VecFloatArithmeticBinaryInst {
    public:
    VecFloatRemInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
                    FastMathAttr fast_math_attr);

    std::string to_string() const override;
};
}
}