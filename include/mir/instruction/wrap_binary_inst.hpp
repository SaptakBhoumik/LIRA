#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <memory>
namespace LIRA {
namespace MIR {
// --------------------------- Wrap Arithmetic Binary Operations ---------------------------
class WrapBinaryInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    bool unsigned_;
    bool saturating;

    std::string to_string_helper(const std::string op_name) const;
    public:
    enum class OpType:std::uint64_t{
        WRAP_ADD = 1 << 6,
        WRAP_SUB = 1 << 7,
        WRAP_MUL = 1 << 8,
        WRAP_DIV = 1 << 9,
        WRAP_REM = 1 << 10,
        WRAP_COPYSIGN = 1 << 11,
        WRAP_SHL = 1 << 12,
        WRAP_LSHR = 1 << 13,
        WRAP_ASHR = 1 << 14,
    };
    WrapBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                   bool unsigned_, bool saturating);

    virtual ~WrapBinaryInst() = default;

    virtual bool is_unsigned() const final;
    virtual bool is_saturating() const final;

    virtual InstOperandTypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};


// ---------------------------- Integer Wrap Arithmetic Binary Operations ---------------------------
class IntWrapBinaryInst:public WrapBinaryInst {
    public:
    IntWrapBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      bool unsigned_, bool saturating);

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;
    virtual std::size_t get_bitwidth() const final;
    
    virtual InstOperandTypeVarient get_operand_type_varient() const override final;
};

class IntWrapAddInst:public IntWrapBinaryInst {
    public:
    IntWrapAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class IntWrapSubInst:public IntWrapBinaryInst {
    public:
    IntWrapSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class IntWrapMulInst:public IntWrapBinaryInst {   
    public:
    IntWrapMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class IntWrapDivInst:public IntWrapBinaryInst {
    public:
    IntWrapDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class IntWrapRemInst:public IntWrapBinaryInst {
    public:
    IntWrapRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class IntWrapCopysignInst:public IntWrapBinaryInst {
    public:
    IntWrapCopysignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class IntWrapShlInst:public IntWrapBinaryInst {
    public:
    IntWrapShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class IntWrapLshrInst:public IntWrapBinaryInst {
    public:
    IntWrapLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                    bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class IntWrapAshrInst:public IntWrapBinaryInst {
    public:
    IntWrapAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                    bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};


// ---------------------------- Vector Integer Wrap Arithmetic Binary Operations ---------------------------
class VecIntWrapBinaryInst:public WrapBinaryInst {
    public:
    VecIntWrapBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                         bool unsigned_, bool saturating);

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;
    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_basetype() const final;
    virtual std::size_t get_operand_basetype_bitwidth() const final;
    virtual std::size_t get_vector_size() const final;
    
    virtual InstOperandTypeVarient get_operand_type_varient() const override final;
};

class VecIntWrapAddInst:public VecIntWrapBinaryInst {
    public:
    VecIntWrapAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class VecIntWrapSubInst:public VecIntWrapBinaryInst {
    public:
    VecIntWrapSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class VecIntWrapMulInst:public VecIntWrapBinaryInst {   
    public:
    VecIntWrapMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                      bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class VecIntWrapDivInst:public VecIntWrapBinaryInst {
    public:
    VecIntWrapDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class VecIntWrapRemInst:public VecIntWrapBinaryInst {
    public:
    VecIntWrapRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class VecIntWrapCopysignInst:public VecIntWrapBinaryInst {
    public:
    VecIntWrapCopysignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                           bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class VecIntWrapShlInst:public VecIntWrapBinaryInst {
    public:
    VecIntWrapShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class VecIntWrapLshrInst:public VecIntWrapBinaryInst {
    public:
    VecIntWrapLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                       bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

class VecIntWrapAshrInst:public VecIntWrapBinaryInst {
    public:
    VecIntWrapAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                       bool unsigned_, bool saturating);

    virtual OpType get_op_type() const override final;
    virtual std::string to_string() const override final;
};

}
}