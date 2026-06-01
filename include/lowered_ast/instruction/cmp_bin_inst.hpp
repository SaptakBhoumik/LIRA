#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// ---------------------------Comparison Binary operations ---------------------------
class CmpBinaryInst:public Inst {
    protected:
    IR::InstructionStmtPtr instruction_stmt;

    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::TypeExprPtr type;//Reduced type. 
    public:
    CmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    virtual ~CmpBinaryInst() = default;

    IR::TypeExprPtr get_operand_type() const;
    IR::LiteralExprPtr get_lhs() const;
    IR::LiteralExprPtr get_rhs() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own. <i1,M> if ``type``
                                                                                          //is vector and i1 if it is scalar
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
};

// ---------------------------Int Comparison Binary operations ---------------------------
class IntCmpBinaryInst:public CmpBinaryInst {
    bool unsigned_;//Whether it is unsigned comparison or not. Ignored for eq and neq instructions
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.
    public:
    IntCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                     bool unsigned_);

    virtual bool is_unsigned() const final;

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bit_width() const final;//Returns the bit width of the operand type. Just a helper function to make life easier
};

class IntEqInst:public IntCmpBinaryInst {
    public:
    IntEqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    std::string to_string() const override;
};

class IntNeqInst:public IntCmpBinaryInst {
    public:
    IntNeqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    std::string to_string() const override;
};

class IntLtInst:public IntCmpBinaryInst {
    public:
    IntLtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    std::string to_string() const override;
};

class IntGtInst:public IntCmpBinaryInst {
    public:
    IntGtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    std::string to_string() const override;
};


class IntLeInst:public IntCmpBinaryInst {
    public:
    IntLeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    std::string to_string() const override;
};


class IntGeInst:public IntCmpBinaryInst {
    public:
    IntGeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    std::string to_string() const override;
};

// ---------------------------Vector integer Comparison Binary operations ---------------------------
class VecCmpBinaryInst:public CmpBinaryInst {
    bool unsigned_;//Whether it is unsigned comparison or not. Ignored for eq and neq instructions
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.
    public:
    VecCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                     bool unsigned_);

    virtual bool is_unsigned() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_basetype_width() const final;//Returns the bit width of the operand basetype. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
};

class VecEqInst:public VecCmpBinaryInst {
    public:
    VecEqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    std::string to_string() const override;
};

class VecNeqInst:public VecCmpBinaryInst {
    public:
    VecNeqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    std::string to_string() const override;
};

class VecLtInst:public VecCmpBinaryInst {
    public:
    VecLtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    std::string to_string() const override;
};

class VecGtInst:public VecCmpBinaryInst {
    bool unsigned_;//Whether it is signed comparison or not.
    public:
    VecGtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    std::string to_string() const override;
};


class VecLeInst:public VecCmpBinaryInst {
    bool unsigned_;//Whether it is signed comparison or not.
    public:
    VecLeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    std::string to_string() const override;
};


class VecGeInst:public VecCmpBinaryInst {
    bool unsigned_;//Whether it is signed comparison or not.
    public:
    VecGeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    std::string to_string() const override;
};

// ---------------------------Float Comparison Binary operations ---------------------------
class FloatCmpBinaryInst:public CmpBinaryInst {
    FastMathAttr fast_math_attr;
    bool unordered;//Ignored for either_nan and neither_nan. Says if the op is ordered or unordered
    public:
    FloatCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                FastMathAttr fast_math_attr, bool unordered);

    virtual FastMathAttr get_fast_math_attr() const final;
    virtual bool is_unordered() const final;

    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bit_width() const final;//Returns the bit width of the operand type. Just a helper function to make life easier
};

class FloatEqInst:public FloatCmpBinaryInst {
    public:
    FloatEqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class FloatNeqInst:public FloatCmpBinaryInst {
    public:
    FloatNeqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class FloatLtInst:public FloatCmpBinaryInst {
    public:
    FloatLtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class FloatGtInst:public FloatCmpBinaryInst {
    public:
    FloatGtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class FloatLeInst:public FloatCmpBinaryInst {
    public:
    FloatLeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class FloatGeInst:public FloatCmpBinaryInst {
    public:
    FloatGeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class EitherNaNInst:public FloatCmpBinaryInst {
    public:
    EitherNaNInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr);

    std::string to_string() const override;
};

class NeitherNaNInst:public FloatCmpBinaryInst {
    public:
    NeitherNaNInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr);

    std::string to_string() const override;
};


// --------------------------- Vector Float Comparison Binary operations ---------------------------
class VecFloatCmpBinaryInst:public CmpBinaryInst {
    FastMathAttr fast_math_attr;
    bool unordered;//Ignored for either_nan and neither_nan. Says if the op is ordered or unordered
    public:
    VecFloatCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                FastMathAttr fast_math_attr, bool unordered);

    virtual FastMathAttr get_fast_math_attr() const final;
    virtual bool is_unordered() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::shared_ptr<IR::FloatTypeExpr> get_basetype() const final;//We dont return width of base type because it can be f16,bf16 and so on. Width alone not enough
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
};

class VecFloatEqInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatEqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class VecFloatNeqInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatNeqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class VecFloatLtInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatLtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class VecFloatGtInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatGtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class VecFloatLeInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatLeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class VecFloatGeInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatGeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                   FastMathAttr fast_math_attr, bool unordered);

    std::string to_string() const override;
};

class VecEitherNaNInst:public VecFloatCmpBinaryInst {
    public:
    VecEitherNaNInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                     FastMathAttr fast_math_attr);

    std::string to_string() const override;
};

class VecNeitherNaNInst:public VecFloatCmpBinaryInst {
    public:
    VecNeitherNaNInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                      FastMathAttr fast_math_attr);

    std::string to_string() const override;
};
}
}