#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Bitwise trinary operations ---------------------------
class BitwiseTrinaryInst:public Inst {
    protected:
    IR::LiteralExprPtr arg1;
    IR::LiteralExprPtr arg2;
    IR::LiteralExprPtr arg3;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    enum class OpType:std::uint64_t{
        FSHL = 1 << 6,
        FSHR = 1 << 7,
        BITBLEND = 1 << 8
    };
    BitwiseTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3);

    virtual TypeVariant get_operand_type_variant() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_arg1() const final;
    virtual IR::LiteralExprPtr get_arg2() const final;
    virtual IR::LiteralExprPtr get_arg3() const final;
    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};


// ---------------------------- Integer Trinary operations ---------------------------
class IntBitwiseTrinaryInst:public BitwiseTrinaryInst {
    public:
    IntBitwiseTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3);

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the operand type. Just a helper function to make life easier
    
    virtual TypeVariant get_operand_type_variant() const override final;
};

class IntFshlInst:public IntBitwiseTrinaryInst {
    public:
    IntFshlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFshrInst:public IntBitwiseTrinaryInst {
    public:
    IntFshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class IntBitblendInst:public IntBitwiseTrinaryInst {
    public:
    IntBitblendInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

// ---------------------------- Vector Integer Trinary operations ---------------------------
class VecIntBitwiseTrinaryInst:public BitwiseTrinaryInst {
    public:
    VecIntBitwiseTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3);

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_basetype_bitwidth() const final;//Returns the bit width of the operand basetype. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
    
    virtual TypeVariant get_operand_type_variant() const override final;
};

class VecIntFshlInst:public VecIntBitwiseTrinaryInst {
    public:
    VecIntFshlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntFshrInst:public VecIntBitwiseTrinaryInst {
    public:
    VecIntFshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3);

    OpType get_op_type() const override;
    std::string to_string() const override;
};


class VecIntBitblendInst:public VecIntBitwiseTrinaryInst {
    public:
    VecIntBitblendInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3);

    OpType get_op_type() const override;
    std::string to_string() const override;
};
}
}