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
    enum class OpType:std::uint32_t{
        EQ = 1 << 6,
        NEQ = 1 << 7,
        LT = 1 << 8,
        GT = 1 << 9,
        LE = 1 << 10,
        GE = 1 << 11,
        NEITHER_NAN = 1 << 12,
        EITHER_NAN = 1 << 13
    };

    CmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    virtual ~CmpBinaryInst() = default;

    virtual InstOperandTypeVarient get_operand_type_varient() const final;//Can be calculated easily from ``type``. Just a helper function
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual OpType get_op_type() const = 0;//Whether it is eq,neq,lt,gt,le,ge,either_nan or neither_nan.
    //Dont implement bitwidth helper here because for vector it is not that helpful

    virtual std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override final;//Will figure out the type of destination on it's own. <i1,M> if ``type``
                                                                                          //is vector and i1 if it is scalar
    virtual InstType get_inst_type() const override final;
    virtual IR::InstructionStmtPtr get_instruction_stmt() const override final;
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

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntNeqInst:public IntCmpBinaryInst {
    public:
    IntNeqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntLtInst:public IntCmpBinaryInst {
    public:
    IntLtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntGtInst:public IntCmpBinaryInst {
    public:
    IntGtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class IntLeInst:public IntCmpBinaryInst {
    public:
    IntLeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class IntGeInst:public IntCmpBinaryInst {
    public:
    IntGeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

// ---------------------------Vector integer Comparison Binary operations ---------------------------
class VecIntCmpBinaryInst:public CmpBinaryInst {
    bool unsigned_;//Whether it is unsigned comparison or not. Ignored for eq and neq instructions
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.
    public:
    VecIntCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                         bool unsigned_);

    virtual bool is_unsigned() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_basetype_width() const final;//Returns the bit width of the operand basetype. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
};

class VecIntEqInst:public VecIntCmpBinaryInst {
    public:
    VecIntEqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntNeqInst:public VecIntCmpBinaryInst {
    public:
    VecIntNeqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntLtInst:public VecIntCmpBinaryInst {
    public:
    VecIntLtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntGtInst:public VecIntCmpBinaryInst {
    public:
    VecIntGtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class VecIntLeInst:public VecIntCmpBinaryInst {
    public:
    VecIntLeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class VecIntGeInst:public VecIntCmpBinaryInst {
    public:
    VecIntGeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


// ---------------------------Int Comparison Binary operations ---------------------------
class PtrCmpBinaryInst:public CmpBinaryInst {
    public:
    //We already know the in type. No need to get the type again because it is always ptr
    PtrCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    virtual std::size_t get_bit_width() const final;//Returns the bit width of the operand type. We only support x86_64 so returns 64. I made this function just in case we support more arch in future
                                                    //Just a helper function to make life easier. 
};

class PtrEqInst:public PtrCmpBinaryInst {
    public:
    PtrEqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class PtrNeqInst:public PtrCmpBinaryInst {
    public:
    PtrNeqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class PtrLtInst:public PtrCmpBinaryInst {
    public:
    PtrLtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class PtrGtInst:public PtrCmpBinaryInst {
    public:
    PtrGtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class PtrLeInst:public PtrCmpBinaryInst {
    public:
    PtrLeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class PtrGeInst:public PtrCmpBinaryInst {
    public:
    PtrGeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

// ---------------------------Vector integer Comparison Binary operations ---------------------------
class VecPtrCmpBinaryInst:public CmpBinaryInst {
    public:
    VecPtrCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    virtual bool is_unsigned() const final;

    virtual std::size_t get_basetype_width() const final;//Returns the bit width of the operand basetype. Returns 64 cuz we support only x86_64 but can return diffrent in future if we support more arch. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
};

class VecPtrEqInst:public VecPtrCmpBinaryInst {
    //Here we take in the type because we need to know the number of element in vec. We could have just taken the number of element instead of the full type but this works
    public:
    VecPtrEqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrNeqInst:public VecPtrCmpBinaryInst {
    public:
    VecPtrNeqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrLtInst:public VecPtrCmpBinaryInst {
    public:
    VecPtrLtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrGtInst:public VecPtrCmpBinaryInst {
    public:
    VecPtrGtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrLeInst:public VecPtrCmpBinaryInst {
    public:
    VecPtrLeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrGeInst:public VecPtrCmpBinaryInst {
    public:
    VecPtrGeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
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

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatNeqInst:public FloatCmpBinaryInst {
    public:
    FloatNeqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatLtInst:public FloatCmpBinaryInst {
    public:
    FloatLtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatGtInst:public FloatCmpBinaryInst {
    public:
    FloatGtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatLeInst:public FloatCmpBinaryInst {
    public:
    FloatLeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatGeInst:public FloatCmpBinaryInst {
    public:
    FloatGeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class EitherNaNInst:public FloatCmpBinaryInst {
    public:
    EitherNaNInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class NeitherNaNInst:public FloatCmpBinaryInst {
    public:
    NeitherNaNInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
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

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatNeqInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatNeqInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatLtInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatLtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatGtInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatGtInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatLeInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatLeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatGeInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatGeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                   FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecEitherNaNInst:public VecFloatCmpBinaryInst {
    public:
    VecEitherNaNInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                     FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecNeitherNaNInst:public VecFloatCmpBinaryInst {
    public:
    VecNeitherNaNInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                      FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}