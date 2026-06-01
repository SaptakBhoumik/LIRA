#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
// --------------------------- Arithmatic Binary operations ---------------------------
class ArithmeticBinaryInst:public Inst {
    protected:
    InstructionStmtPtr instruction_stmt;

    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable
    LiteralExprPtr lhs;
    LiteralExprPtr rhs;
    TypeExprPtr type;//Reduced type. 
    public:
    ArithmeticBinaryInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type);

    virtual ~ArithmeticBinaryInst() = default;

    TypeExprPtr get_operand_type() const;
    LiteralExprPtr get_lhs() const;
    LiteralExprPtr get_rhs() const;

    std::optional<std::pair<DestinationVar,TypeExprPtr>> get_destination() const override;
    InstructionStmtPtr get_instruction_stmt() const override;
};

// ---------------------------- Integer binary operations ---------------------------
class IntAddInst:public ArithmeticBinaryInst {
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    public:
    IntAddInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                bool nuw, bool nsw);

    bool is_nuw() const;
    bool is_nsw() const;
    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};


class IntSubInst:public ArithmeticBinaryInst {
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    public:
    IntSubInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                bool nuw, bool nsw);

    bool is_nuw() const;
    bool is_nsw() const;
    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};


class IntMulInst:public ArithmeticBinaryInst {
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    public:
    IntMulInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                bool nuw, bool nsw);

    bool is_nuw() const;
    bool is_nsw() const;
    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class IntDivInst:public ArithmeticBinaryInst {
    bool unsigned_;//Whether it is unsigned division or not.
    bool exact;//Whether it has the exact attribute.
    public:
    IntDivInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                bool unsigned_, bool exact);

    bool is_unsigned() const;
    bool is_exact() const;
    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class IntRemInst:public ArithmeticBinaryInst {
    bool unsigned_;//Whether it is unsigned remainder or not.
    public:
    IntRemInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                bool unsigned_);

    bool is_unsigned() const;
    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

// ----------------------------- Vector integer binary operations ---------------------------
class VecIntAddInst:public ArithmeticBinaryInst {
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    public:
    VecIntAddInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                bool nuw, bool nsw);

    bool is_nuw() const;
    bool is_nsw() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};


class VecIntSubInst:public ArithmeticBinaryInst {
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    public:
    VecIntSubInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                bool nuw, bool nsw);

    bool is_nuw() const;
    bool is_nsw() const;
   std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};


class VecIntMulInst:public ArithmeticBinaryInst {
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    public:
    VecIntMulInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                bool nuw, bool nsw);

    bool is_nuw() const;
    bool is_nsw() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecIntDivInst:public ArithmeticBinaryInst {
    bool unsigned_;//Whether it is unsigned division or not.
    bool exact;//Whether it has the exact attribute.
    public:
    VecIntDivInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                bool unsigned_, bool exact);

    bool is_unsigned() const;
    bool is_exact() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecIntRemInst:public ArithmeticBinaryInst {
    bool unsigned_;//Whether it is unsigned remainder or not.
    public:
    VecIntRemInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                bool unsigned_);

    bool is_unsigned() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};


// ---------------------------- Float binary operations ---------------------------
class FloatAddInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    FloatAddInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                FastMathAttr fast_math_attr);

    FastMathAttr get_fast_math_attr() const;
    std::shared_ptr<FloatTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to FloatTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class FloatSubInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    FloatSubInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                FastMathAttr fast_math_attr);

    FastMathAttr get_fast_math_attr() const;
    std::shared_ptr<FloatTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to FloatTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class FloatMulInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    FloatMulInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                FastMathAttr fast_math_attr);

    FastMathAttr get_fast_math_attr() const;
    std::shared_ptr<FloatTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to FloatTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class FloatDivInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    FloatDivInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                FastMathAttr fast_math_attr);

    FastMathAttr get_fast_math_attr() const;
    std::shared_ptr<FloatTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to FloatTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class FloatRemInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    FloatRemInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                FastMathAttr fast_math_attr);

    FastMathAttr get_fast_math_attr() const;
    std::shared_ptr<FloatTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to FloatTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};


// ---------------------------- Vector Float binary operations ---------------------------
class VecFloatAddInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    VecFloatAddInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                    FastMathAttr fast_math_attr);

    FastMathAttr get_fast_math_attr() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecFloatSubInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    VecFloatSubInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                    FastMathAttr fast_math_attr);

    FastMathAttr get_fast_math_attr() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecFloatMulInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    VecFloatMulInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                    FastMathAttr fast_math_attr);

    FastMathAttr get_fast_math_attr() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecFloatDivInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    VecFloatDivInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                    FastMathAttr fast_math_attr);

    FastMathAttr get_fast_math_attr() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecFloatRemInst:public ArithmeticBinaryInst {
    FastMathAttr fast_math_attr;
    public:
    VecFloatRemInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
                    FastMathAttr fast_math_attr);

    FastMathAttr get_fast_math_attr() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};
}