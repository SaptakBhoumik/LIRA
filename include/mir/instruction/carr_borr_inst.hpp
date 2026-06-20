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

    virtual ~CarrBorrType1Inst() = default;
    
    virtual bool is_unsigned() const final;

    virtual InstOperandTypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_arg1() const final;
    virtual IR::LiteralExprPtr get_arg2() const final;
    virtual IR::LiteralExprPtr get_arg3() const final;
    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};
}
}