#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// ---------------------------- Carry/Borrowing instructions ---------------------------
class CarrBorrType1Inst:public Inst {
    // This carry/borrowing instruction is for cases where we return the carry/borrow bit as an i1 i/e the output is {T,i1}
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;//Maybe nullptr like for carry_shl,carry_lshr,carry_ashr. VERY IMP. REMEMBER IT
    IR::LiteralExprPtr carr_borr_val;
    bool unsigned_; 

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    enum class OpType:std::uint64_t{
        CARRY_ADD = 1 << 6,
        CARRY_SUB = 1 << 7,
        CARRY_SHL = 1 << 8,
        CARRY_ASHL = 1 << 9,
        CARRY_LSHL = 1 << 10,
    };
    CarrBorrType1Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    virtual bool is_unsigned() const final;

    virtual InstOperandTypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual IR::LiteralExprPtr get_carr_borr_val() const final;
    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};


// ---------------------------- Int Carry/Borrowing instructions ---------------------------
class IntCarrBorrType1Inst:public CarrBorrType1Inst {
    protected:
    public:
    IntCarrBorrType1Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                         IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;
    virtual std::size_t get_bitwidth() const final;
    
    virtual InstOperandTypeVarient get_operand_type_varient() const override final;
};


class IntCarrAddInst:public IntCarrBorrType1Inst {
    public:
    IntCarrAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   IR::LiteralExprPtr carr_borr_val, bool unsigned_);

};
}
}