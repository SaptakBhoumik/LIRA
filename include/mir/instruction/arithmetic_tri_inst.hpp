#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- arithmetic trinary operations ---------------------------
class ArithmeticTrinaryInst:public Inst {
    protected:
    IR::LiteralExprPtr arg1;
    IR::LiteralExprPtr arg2;
    IR::LiteralExprPtr arg3;
    public:
    enum class OpType:std::uint64_t{
        FMA = 1 << 6,
        FMS = 1 << 7,
        FNMA = 1 << 8,
        FNMS = 1 << 9,
        CLAMP = 1 << 10,
    };
    ArithmeticTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3);

    virtual ~ArithmeticTrinaryInst() = default;

    virtual InstOperandTypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_arg1() const final;
    virtual IR::LiteralExprPtr get_arg2() const final;
    virtual IR::LiteralExprPtr get_arg3() const final;
    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};


// ---------------------------- Integer Trinary operations ---------------------------
class IntArithmeticTrinaryInst:public ArithmeticTrinaryInst {
    protected:
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool unsigned_;//Whether it is unsigned operation or not
    bool saturating;//Whether it is saturating operation or not
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    IntArithmeticTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                             IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_unsigned() const final;
    virtual bool is_saturating() const final;

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the operand type. Just a helper function to make life easier
    
    virtual InstOperandTypeVarient get_operand_type_varient() const override final;
};

class IntFMAInst:public IntArithmeticTrinaryInst {
    public:
    IntFMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
               IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFMSInst:public IntArithmeticTrinaryInst {
    public:
    IntFMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
               IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFNMAInst:public IntArithmeticTrinaryInst {
    public:
    IntFNMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntFNMSInst:public IntArithmeticTrinaryInst {
    public:
    IntFNMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntClampInst:public IntArithmeticTrinaryInst {
    public:
    IntClampInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                 IR::LiteralExprPtr arg3, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
// ----------------------------- Vector integer Trinary operations ---------------------------
class VecIntArithmeticTrinaryInst:public ArithmeticTrinaryInst {
    protected:
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool unsigned_;//Whether it is unsigned operation or not
    bool saturating;//Whether it is saturating operation or not
    bool floor;//For int avg
    bool exact;//Whether it has the exact attribute
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    VecIntArithmeticTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                                IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_unsigned() const final;
    virtual bool is_saturating() const final;
 
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_basetype_width() const final;//Returns the bit width of the operand basetype. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier

    virtual InstOperandTypeVarient get_operand_type_varient() const override final;
};

class VecIntFMAInst:public VecIntArithmeticTrinaryInst {
    public:
    VecIntFMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                  IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntFMSInst:public VecIntArithmeticTrinaryInst {
    public:
    VecIntFMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                   IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntFNMAInst:public VecIntArithmeticTrinaryInst {
    public:
    VecIntFNMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                    IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntFNMSInst:public VecIntArithmeticTrinaryInst {
    public:
    VecIntFNMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                    IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntClampInst:public VecIntArithmeticTrinaryInst {
    public:
    VecIntClampInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                     IR::LiteralExprPtr arg3, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
// ---------------------------- Float Trinary operations ---------------------------
class FloatArithmeticTrinaryInst:public ArithmeticTrinaryInst {
    protected:
    FastMathAttr fast_math_attr;
    bool ieee754_2019;
    bool unordered;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    FloatArithmeticTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr,bool ieee754_2019, bool unordered);

    virtual FastMathAttr get_fast_math_attr() const final;
    virtual bool is_ieee754_2019() const final;
    virtual bool is_unordered() const final;

    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the operand type. Just a helper function to make life easier
    virtual bool is_brain_float() const final;

    virtual InstOperandTypeVarient get_operand_type_varient() const override final;
};

class FloatFMAInst:public FloatArithmeticTrinaryInst {
    public:
    FloatFMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                  IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFMSInst:public FloatArithmeticTrinaryInst {
    public:
    FloatFMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                  IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFNMAInst:public FloatArithmeticTrinaryInst {
    public:
    FloatFNMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                   IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatFNMSInst:public FloatArithmeticTrinaryInst {
    public:
    FloatFNMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                   IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatClampInst:public FloatArithmeticTrinaryInst {
    public:
    FloatClampInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                    IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
// ---------------------------- Vector Float Trinary operations ---------------------------
class VecFloatArithmeticTrinaryInst:public ArithmeticTrinaryInst {
    protected:
    FastMathAttr fast_math_attr;
    bool ieee754_2019;
    bool unordered;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    VecFloatArithmeticTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                  IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr,bool ieee754_2019, bool unordered);

    virtual FastMathAttr get_fast_math_attr() const final;
    virtual bool is_ieee754_2019() const final;
    virtual bool is_unordered() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::shared_ptr<IR::FloatTypeExpr> get_basetype() const final;//We dont return width of base type because it can be f16,bf16 and so on. Width alone not enough
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
    
    virtual InstOperandTypeVarient get_operand_type_varient() const override final;
};

class VecFloatFMAInst:public VecFloatArithmeticTrinaryInst {
    public:
    VecFloatFMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                     IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatFMSInst:public VecFloatArithmeticTrinaryInst {
    public:
    VecFloatFMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                     IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatFNMAInst:public VecFloatArithmeticTrinaryInst {
    public:
    VecFloatFNMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                       IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatFNMSInst:public VecFloatArithmeticTrinaryInst {
    public:
    VecFloatFNMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                       IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatClampInst:public VecFloatArithmeticTrinaryInst {
    public:
    VecFloatClampInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                       IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}