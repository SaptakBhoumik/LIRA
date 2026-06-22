#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// ---------------------------Bitwise Binary operations ---------------------------
class BitwiseBinaryInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;

    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool exact;//Whether it has the exact attribute
    bool disjoint;//Whether it has the disjoint attribute or not

    std::string to_string_helper(const std::string op_name) const;
    public:
    enum class OpType:std::uint64_t{
        AND = 1 << 6,
        NAND = 1 << 7,
        OR = 1 << 8,
        NOR = 1 << 9,
        XOR = 1 << 10,
        XNOR = 1 << 11,
        SHL = 1 << 12,
        LSHR = 1 << 13,
        ASHR = 1 << 14,
        ROTL = 1 << 15,
        ROTR = 1 << 16,
        PEXT = 1 << 17,
        PDEP = 1 << 18
    };
    BitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                      bool nuw, bool nsw, bool exact, bool disjoint);

    virtual TypeVarient get_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual OpType get_op_type() const = 0;
    
    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_exact() const final;
    virtual bool is_disjoint() const final;

    virtual InstType get_inst_type() const override final;
};

// ---------------------------Integer Binary Bitwise operations ---------------------------
class IntBitwiseBinaryInst:public BitwiseBinaryInst {
    public:
    IntBitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                         bool nuw, bool nsw, bool exact, bool disjoint);

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the operand type. Just a helper function to make life easier

    virtual TypeVarient get_type_varient() const override final;
};

class IntAndInst:public IntBitwiseBinaryInst {
    public:
    IntAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntNandInst:public IntBitwiseBinaryInst {
    public:
    IntNandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntOrInst:public IntBitwiseBinaryInst {
    public:
    IntOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
              bool disjoint);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntNorInst:public IntBitwiseBinaryInst {
    public:
    IntNorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
              bool disjoint);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntXorInst:public IntBitwiseBinaryInst {
    public:
    IntXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntXnorInst:public IntBitwiseBinaryInst {
    public:
    IntXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntShlInst:public IntBitwiseBinaryInst {
    public:
    IntShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool nuw, bool nsw);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntLshrInst:public IntBitwiseBinaryInst {
    public:
    IntLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool exact);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntAshrInst:public IntBitwiseBinaryInst {
    public:
    IntAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool exact);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntRotlInst:public IntBitwiseBinaryInst {
    public:
    IntRotlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntRotrInst:public IntBitwiseBinaryInst {
    public:
    IntRotrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntPextInst:public IntBitwiseBinaryInst {
    public:
    IntPextInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntPdepInst:public IntBitwiseBinaryInst {
    public:
    IntPdepInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};
// ---------------------------Vector Integer Binary Bitwise operations ---------------------------
class VecIntBitwiseBinaryInst:public BitwiseBinaryInst {
    public:
    VecIntBitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                         bool disjoint, bool nuw, bool nsw, bool exact);

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_basetype_bitwidth() const final;//Returns the bit width of the operand basetype. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier

    virtual TypeVarient get_type_varient() const override final;
};

class VecIntAndInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntNandInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntNandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntOrInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
              bool disjoint);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntNorInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntNorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
              bool disjoint);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntXorInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntXnorInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntShlInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool nuw, bool nsw);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntLshrInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool exact);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntAshrInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool exact);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntRotlInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntRotlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntRotrInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntRotrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntPextInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntPextInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class VecIntPdepInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntPdepInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override;
    std::string to_string() const override;
};
}
}