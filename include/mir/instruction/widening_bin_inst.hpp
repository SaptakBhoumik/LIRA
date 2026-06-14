#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Widening Binary operations ---------------------------
class WideningBinaryInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::TypeExprPtr input_type;
    public:
    enum class OpType:std::uint64_t{
        WIDENING_ADD = 1 << 6,
        WIDENING_SUB = 1 << 7,
        WIDENING_MUL = 1 << 8,
    };
    WideningBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr input_type);

    virtual ~WideningBinaryInst() = default;

    virtual InstOperandTypeVarient get_type_varient() const = 0;//Type varient of result and input is gonna be same
    virtual IR::TypeExprPtr get_input_type() const final;
    virtual IR::TypeExprPtr get_result_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};


// ---------------------------- Integer Widening Binary operations ---------------------------
class IntWideningBinaryInst:public WideningBinaryInst {
    protected:
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool unsigned_;//Whether it is unsigned operation or not
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    IntWideningBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                          IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_unsigned() const final;

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_input_type() const final;
    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_result_type() const final;
    virtual std::size_t get_input_bitwidth() const final;
    virtual std::size_t get_result_bitwidth() const final;
    
    virtual InstOperandTypeVarient get_type_varient() const override final;
};

class IntWideningAddInst:public IntWideningBinaryInst {
    public:
    IntWideningAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntWideningSubInst:public IntWideningBinaryInst {
    public:
    IntWideningSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntWideningMulInst:public IntWideningBinaryInst {
    public:
    IntWideningMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

// ----------------------------- Vector Integer Widening Binary operations ---------------------------
class VecIntWideningBinaryInst:public WideningBinaryInst {
    protected:
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool unsigned_;//Whether it is unsigned operation or not
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    VecIntWideningBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                              IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_unsigned() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_input_type() const final;
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_result_type() const final;
    virtual std::size_t get_input_base_bitwidth() const final;
    virtual std::size_t get_result_base_bitwidth() const final;
    virtual std::size_t get_num_elements() const final;
    
    virtual InstOperandTypeVarient get_type_varient() const override final;
};

class VecIntWideningAddInst:public VecIntWideningBinaryInst {
    public:
    VecIntWideningAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                          IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntWideningSubInst:public VecIntWideningBinaryInst {
    public:
    VecIntWideningSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                          IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntWideningMulInst:public VecIntWideningBinaryInst {
    public:
    VecIntWideningMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                          IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

// ---------------------------- Float Widening Binary operations ---------------------------
class FloatWideningBinaryInst:public WideningBinaryInst {
    protected:
    FastMathAttr fast_math_attr;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    FloatWideningBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, FastMathAttr fast_math_attr);

    virtual FastMathAttr get_fast_math_attr() const final;

    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_input_type() const final;
    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_result_type() const final;
    virtual std::size_t get_input_bitwidth() const final;
    virtual std::size_t get_result_bitwidth() const final;
    virtual bool is_input_brain_float() const final;
    virtual bool is_result_brain_float() const final;

    virtual InstOperandTypeVarient get_type_varient() const override final;
};

class FloatWideningAddInst:public FloatWideningBinaryInst {
    public:
    FloatWideningAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                          IR::TypeExprPtr input_type, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatWideningSubInst:public FloatWideningBinaryInst {
    public:
    FloatWideningSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                          IR::TypeExprPtr input_type, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatWideningMulInst:public FloatWideningBinaryInst {
    public:
    FloatWideningMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                          IR::TypeExprPtr input_type, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
// ---------------------------- Vector Float Widening Binary operations ---------------------------
class VecFloatWideningBinaryInst:public WideningBinaryInst {
    protected:
    FastMathAttr fast_math_attr;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    VecFloatWideningBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, FastMathAttr fast_math_attr);

    virtual FastMathAttr get_fast_math_attr() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_input_type() const final;
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_result_type() const final;
    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_input_basetype() const final;
    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_result_basetype() const final;
    virtual std::size_t get_num_elements() const final;

    virtual InstOperandTypeVarient get_type_varient() const override final;
};

class VecFloatWideningAddInst:public VecFloatWideningBinaryInst {
    public:
    VecFloatWideningAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                          IR::TypeExprPtr input_type, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatWideningSubInst:public VecFloatWideningBinaryInst {
    public:
    VecFloatWideningSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                          IR::TypeExprPtr input_type, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatWideningMulInst:public VecFloatWideningBinaryInst {
    public:
    VecFloatWideningMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                          IR::TypeExprPtr input_type, FastMathAttr fast_math_attr);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}