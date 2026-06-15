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
    public:
    enum class OpType:std::uint64_t{
        AND = 1 << 6,
        OR = 1 << 7,
        XOR = 1 << 8,
        SHL = 1 << 9,
        LSHR = 1 << 10,
        ASHR = 1 << 11
    };
    BitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    virtual ~BitwiseBinaryInst() = default;

    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual OpType get_op_type() const = 0;//Whether it is and,or,xor,shl,lshr,ashl.
    
    virtual InstType get_inst_type() const override final;
    virtual InstOperandTypeVarient get_operand_type_varient() const = 0;
};

// ---------------------------Integer Binary Bitwise operations ---------------------------
class IntBitwiseBinaryInst:public BitwiseBinaryInst {
    protected:
    bool disjoint;//Whether it has the disjoint attribute or not
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool exact;//Whether it has the exact attribute
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.
    public:
    IntBitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                         bool disjoint, bool nuw, bool nsw, bool exact);

    virtual bool is_disjoint() const final;
    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_exact() const final;
    
    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the operand type. Just a helper function to make life easier

    virtual InstOperandTypeVarient get_operand_type_varient() const override final;
};

class IntANDInst:public IntBitwiseBinaryInst {
    public:
    IntANDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntORInst:public IntBitwiseBinaryInst {
    public:
    IntORInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
              bool disjoint);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntXORInst:public IntBitwiseBinaryInst {
    public:
    IntXORInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntSHLInst:public IntBitwiseBinaryInst {
    public:
    IntSHLInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool nuw, bool nsw);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntLSHRInst:public IntBitwiseBinaryInst {
    public:
    IntLSHRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool exact);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntASHRInst:public IntBitwiseBinaryInst {
    public:
    IntASHRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool exact);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};


// ---------------------------Vector Integer Binary Bitwise operations ---------------------------
class VecIntBitwiseBinaryInst:public BitwiseBinaryInst {
    protected:
    bool disjoint;//Whether it has the disjoint attribute or not
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool exact;//Whether it has the exact attribute
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used
    public:
    VecIntBitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                         bool disjoint, bool nuw, bool nsw, bool exact);

    virtual bool is_disjoint() const final;
    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_exact() const final;
    
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_basetype_bitwidth() const final;//Returns the bit width of the operand basetype. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier

    virtual InstOperandTypeVarient get_operand_type_varient() const override final;
};


class VecIntANDInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntANDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntORInst:public VecIntBitwiseBinaryInst {
    bool disjoint = false;//Whether it has the disjoint attribute or not

    public:
    VecIntORInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
              bool disjoint);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntXORInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntXORInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntSHLInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntSHLInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                   bool nuw, bool nsw);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntLSHRInst:public VecIntBitwiseBinaryInst {
    public:
    VecIntLSHRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool exact);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntASHRInst:public VecIntBitwiseBinaryInst { 
    public:
    VecIntASHRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                    bool exact);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}