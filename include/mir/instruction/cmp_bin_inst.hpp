#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <memory>
namespace LIRA {
namespace MIR {
// ---------------------------Comparison Binary operations ---------------------------
class CmpBinaryInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::TypeExprPtr type;//Reduced type. 
    public:
    enum class OpType:std::uint64_t{
        EQ = 1 << 6,
        NEQ = 1 << 7,
        LT = 1 << 8,
        GT = 1 << 9,
        LE = 1 << 10,
        GE = 1 << 11,
        NEITHER_NAN = 1 << 12,
        EITHER_NAN = 1 << 13,
        BOTH_NAN = 1 << 14
    };

    CmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                  IR::TypeExprPtr type, std::optional<FastMathAttr> fast_math_attr);

    virtual InstOperandTypeVarient get_operand_type_varient() const = 0;//Can be calculated easily from ``type``. Just a helper function
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual OpType get_op_type() const = 0;//Whether it is eq,neq,lt,gt,le,ge,either_nan or neither_nan.
    //Dont implement bitwidth helper here because for vector it is not that helpful

    virtual InstType get_inst_type() const override final;
};

// ---------------------------Integer Comparison Binary operations ---------------------------
class IntCmpBinaryInst:public CmpBinaryInst {
    protected:
    bool unsigned_;//Whether it is unsigned comparison or not. Ignored for eq and neq instructions
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.

    virtual std::string to_string_helper(std::string op_name) const final;
    public:
    IntCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                     bool unsigned_);

    virtual bool is_unsigned() const final;

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the operand type. Just a helper function to make life easier
    virtual InstOperandTypeVarient get_operand_type_varient() const final;
};

class IntEqInst:public IntCmpBinaryInst {
    public:
    IntEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntNeqInst:public IntCmpBinaryInst {
    public:
    IntNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntLtInst:public IntCmpBinaryInst {
    public:
    IntLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntGtInst:public IntCmpBinaryInst {
    public:
    IntGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class IntLeInst:public IntCmpBinaryInst {
    public:
    IntLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class IntGeInst:public IntCmpBinaryInst {
    public:
    IntGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

// ---------------------------Vector integer Comparison Binary operations ---------------------------
class VecIntCmpBinaryInst:public CmpBinaryInst {
    protected:
    bool unsigned_;//Whether it is unsigned comparison or not. Ignored for eq and neq instructions
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.

    virtual std::string to_string_helper(std::string op_name) const final;
    public:
    VecIntCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                         bool unsigned_);

    virtual bool is_unsigned() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_basetype_bitwidth() const final;//Returns the bit width of the operand basetype. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
    virtual InstOperandTypeVarient get_operand_type_varient() const final;
};

class VecIntEqInst:public VecIntCmpBinaryInst {
    public:
    VecIntEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntNeqInst:public VecIntCmpBinaryInst {
    public:
    VecIntNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntLtInst:public VecIntCmpBinaryInst {
    public:
    VecIntLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntGtInst:public VecIntCmpBinaryInst {
    public:
    VecIntGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class VecIntLeInst:public VecIntCmpBinaryInst {
    public:
    VecIntLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class VecIntGeInst:public VecIntCmpBinaryInst {
    public:
    VecIntGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
              bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


// ---------------------------Ptr Comparison Binary operations ---------------------------
class PtrCmpBinaryInst:public CmpBinaryInst {
    protected:
    virtual std::string to_string_helper(std::string op_name) const final;
    public:
    //We already know the in type. No need to get the type again because it is always ptr
    PtrCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the operand type. We only support x86_64 so returns 64. I made this function just in case we support more arch in future
                                                    //Just a helper function to make life easier. 
    virtual InstOperandTypeVarient get_operand_type_varient() const final;
};

class PtrEqInst:public PtrCmpBinaryInst {
    public:
    PtrEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class PtrNeqInst:public PtrCmpBinaryInst {
    public:
    PtrNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class PtrLtInst:public PtrCmpBinaryInst {
    public:
    PtrLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class PtrGtInst:public PtrCmpBinaryInst {
    public:
    PtrGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class PtrLeInst:public PtrCmpBinaryInst {
    public:
    PtrLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


class PtrGeInst:public PtrCmpBinaryInst {
    public:
    PtrGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

// ---------------------------Vector ptr Comparison Binary operations ---------------------------
class VecPtrCmpBinaryInst:public CmpBinaryInst {
    protected:
    virtual std::string to_string_helper(std::string op_name) const final;
    public:
    VecPtrCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_type() const final;
    virtual std::size_t get_basetype_bitwidth() const final;//Returns the bit width of the operand basetype. Returns 64 cuz we support only x86_64 but can return diffrent in future if we support more arch. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
    virtual InstOperandTypeVarient get_operand_type_varient() const final;
};

class VecPtrEqInst:public VecPtrCmpBinaryInst {
    //Here we take in the type because we need to know the number of element in vec. We could have just taken the number of element instead of the full type but this works
    public:
    VecPtrEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrNeqInst:public VecPtrCmpBinaryInst {
    public:
    VecPtrNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrLtInst:public VecPtrCmpBinaryInst {
    public:
    VecPtrLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrGtInst:public VecPtrCmpBinaryInst {
    public:
    VecPtrGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrLeInst:public VecPtrCmpBinaryInst {
    public:
    VecPtrLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrGeInst:public VecPtrCmpBinaryInst {
    public:
    VecPtrGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
// ---------------------------Float Comparison Binary operations ---------------------------
class FloatCmpBinaryInst:public CmpBinaryInst {
    protected:
    bool unordered;//Ignored for either_nan and neither_nan. Says if the op is ordered or unordered

    virtual std::string to_string_helper(std::string op_name) const final;
    public:
    FloatCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                FastMathAttr fast_math_attr, bool unordered);

    virtual bool is_unordered() const final;

    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the operand type. Just a helper function to make life easier
    virtual bool is_brain_float() const final;
    virtual InstOperandTypeVarient get_operand_type_varient() const final;
};

class FloatEqInst:public FloatCmpBinaryInst {
    public:
    FloatEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatNeqInst:public FloatCmpBinaryInst {
    public:
    FloatNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatLtInst:public FloatCmpBinaryInst {
    public:
    FloatLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatGtInst:public FloatCmpBinaryInst {
    public:
    FloatGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatLeInst:public FloatCmpBinaryInst {
    public:
    FloatLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatGeInst:public FloatCmpBinaryInst {
    public:
    FloatGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatEitherNanInst:public FloatCmpBinaryInst {
    public:
    FloatEitherNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatNeitherNanInst:public FloatCmpBinaryInst {
    public:
    FloatNeitherNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatBothNanInst:public FloatCmpBinaryInst {
    public:
    FloatBothNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
// --------------------------- Vector Float Comparison Binary operations ---------------------------
class VecFloatCmpBinaryInst:public CmpBinaryInst {
    protected:
    bool unordered;//Ignored for either_nan and neither_nan. Says if the op is ordered or unordered
    
    virtual std::string to_string_helper(std::string op_name) const final;
    public:
    VecFloatCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                          FastMathAttr fast_math_attr, bool unordered);

    virtual bool is_unordered() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::shared_ptr<IR::FloatTypeExpr> get_basetype() const final;//We dont return width of base type because it can be f16,bf16 and so on. Width alone not enough
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
    virtual InstOperandTypeVarient get_operand_type_varient() const final;
};

class VecFloatEqInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatNeqInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatLtInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                   FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatGtInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatLeInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatGeInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                   FastMathAttr fast_math_attr, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatEitherNanInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatEitherNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                          FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatNeitherNanInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatNeitherNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                            FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatBothNanInst:public VecFloatCmpBinaryInst {
    public:
    VecFloatBothNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                        FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}