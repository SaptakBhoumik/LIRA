#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// ---------------------------- Carry/Borrowing Type 1 instructions ---------------------------
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

    virtual TypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual IR::LiteralExprPtr get_carr_borr_val() const final;
    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};


// ---------------------------- Int Carry/Borrowing Type 1 instructions ---------------------------
class IntCarrBorrType1Inst:public CarrBorrType1Inst {
    protected:
    public:
    IntCarrBorrType1Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                         IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;
    virtual std::size_t get_bitwidth() const final;
    
    virtual TypeVarient get_operand_type_varient() const override final;
};

class IntCarrAddInst:public IntCarrBorrType1Inst {
    public:
    IntCarrAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntCarrSubInst:public IntCarrBorrType1Inst {
    public:
    IntCarrSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntCarrShlInst:public IntCarrBorrType1Inst {
    public:
    IntCarrShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                   IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntCarrLshrInst:public IntCarrBorrType1Inst {
    public:
    IntCarrLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                    IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntCarrAshrInst:public IntCarrBorrType1Inst {
    public:
    IntCarrAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                    IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


// ---------------------------- Vec Int Carry/Borrowing Type 1 instructions ---------------------------
class VecIntCarrBorrType1Inst:public CarrBorrType1Inst {
    protected:
    public:
    VecIntCarrBorrType1Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;
    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_basetype() const final;
    virtual std::size_t get_operand_basetype_bitwidth() const final;
    virtual std::size_t get_vector_size() const final;
    
    virtual TypeVarient get_operand_type_varient() const override final;
};


class VecIntCarrAddInst:public VecIntCarrBorrType1Inst {
    public:
    VecIntCarrAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntCarrSubInst:public VecIntCarrBorrType1Inst {
    public:
    VecIntCarrSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntCarrShlInst:public VecIntCarrBorrType1Inst {
    public:
    VecIntCarrShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                      IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntCarrLshrInst:public VecIntCarrBorrType1Inst {
    public:
    VecIntCarrLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                       IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntCarrAshrInst:public VecIntCarrBorrType1Inst {
    public:
    VecIntCarrAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                       IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


// ---------------------------- Carry/Borrowing Type 2 instructions ---------------------------
class CarrBorrType2Inst:public Inst {
    // This carry/borrowing instruction is for cases where we return the carry/borrow as an T i/e the output is {T,T}
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;//Maybe nullptr like for carry_shl_n,carry_lshr_n,carry_ashr_n. VERY IMP. REMEMBER IT
    IR::LiteralExprPtr carr_borr_val;
    bool unsigned_; 

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    enum class OpType:std::uint64_t{
        MAC_WIDE = 1 << 6,
        CARRY_SHL_N = 1 << 7,
        CARRY_ASHL_N  = 1 << 8,
        CARRY_LSHL_N  = 1 << 9,
    };
    CarrBorrType2Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    virtual bool is_unsigned() const final;

    virtual TypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual IR::LiteralExprPtr get_carr_borr_val() const final;
    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};

// ---------------------------- Int Carry/Borrowing Type 1 instructions ---------------------------
class IntCarrBorrType2Inst:public CarrBorrType2Inst {
    protected:
    public:
    IntCarrBorrType2Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                         IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;
    virtual std::size_t get_bitwidth() const final;
    
    virtual TypeVarient get_operand_type_varient() const override final;
};

class IntMacWideInst:public IntCarrBorrType2Inst {
    public:
    IntMacWideInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntCarryShlNInst:public IntCarrBorrType2Inst {
    public:
    IntCarryShlNInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                     IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntCarryLshrNInst:public IntCarrBorrType2Inst {
    public:
    IntCarryLshrNInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                      IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntCarryAshrNInst:public IntCarrBorrType2Inst {
    public:
    IntCarryAshrNInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                      IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

// ---------------------------- Vec Int Carry/Borrowing Type 2 instructions ---------------------------
class VecIntCarrBorrType2Inst:public CarrBorrType2Inst {
    protected:
    public:
    VecIntCarrBorrType2Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;
    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_basetype() const final;
    virtual std::size_t get_operand_basetype_bitwidth() const final;
    virtual std::size_t get_vector_size() const final;
    
    virtual TypeVarient get_operand_type_varient() const override final;
};

class VecIntMacWideInst:public VecIntCarrBorrType2Inst {
    public:
    VecIntMacWideInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      IR::LiteralExprPtr carr_borr_val, bool unsigned_);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntCarryShlNInst:public VecIntCarrBorrType2Inst {
    public:
    VecIntCarryShlNInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                        IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntCarryLshrNInst:public VecIntCarrBorrType2Inst {
    public:
    VecIntCarryLshrNInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                         IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntCarryAshrNInst:public VecIntCarrBorrType2Inst {
    public:
    VecIntCarryAshrNInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                         IR::LiteralExprPtr carr_borr_val);

    OpType get_op_type() const override;
    std::string to_string() const override;
};
}
}