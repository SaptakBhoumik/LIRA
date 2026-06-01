#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// ---------------------------Logical Binary operations ---------------------------
class LogicalBinaryInst:public Inst {
    protected:
    IR::InstructionStmtPtr instruction_stmt;

    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::TypeExprPtr type;//Reduced type. 
    public:
    LogicalBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    virtual ~LogicalBinaryInst() = default;

    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;

    virtual std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override final;//Will figure out the type of destination on it's own. <i1,M> if ``type``
                                                                                          //is vector and i1 if it is scalar
    virtual InstType get_inst_type() const override final;
    virtual IR::InstructionStmtPtr get_instruction_stmt() const override final;
};

// ---------------------------Logical Integer Binary operations ---------------------------
class IntLogicalBinaryInst:public LogicalBinaryInst {
    bool disjoint;//Whether it has the disjoint attribute or not
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool exact;//Whether it has the exact attribute
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.
    public:
    IntLogicalBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                         bool disjoint, bool nuw, bool nsw, bool exact);

    virtual bool is_disjoint() const final;
    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_exact() const final;

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bit_width() const final;//Returns the bit width of the operand type. Just a helper function to make life easier
};

class IntANDInst:public IntLogicalBinaryInst {
    public:
    IntANDInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    std::string to_string() const override;
};

class IntORInst:public IntLogicalBinaryInst {
    public:
    IntORInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
              bool disjoint);

    std::string to_string() const override;
};

class IntXORInst:public IntLogicalBinaryInst {
    public:
    IntXORInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    std::string to_string() const override;
};

class IntSHLInst:public IntLogicalBinaryInst {
    public:
    IntSHLInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                bool nuw, bool nsw);

    std::string to_string() const override;
};

class IntLSHRInst:public IntLogicalBinaryInst {
    public:
    IntLSHRInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                bool exact);

    std::string to_string() const override;
};

class IntASHRInst:public IntLogicalBinaryInst {
    public:
    IntASHRInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                bool exact);

    std::string to_string() const override;
};


// ---------------------------Vector Integer Binary operations ---------------------------
class VecIntLogicalBinaryInst:public LogicalBinaryInst {
    bool disjoint;//Whether it has the disjoint attribute or not
    bool nuw;//Whether it has the nsw or nuw attribute. 
    bool nsw;//Whether it has the nsw or nuw attribute. 
    bool exact;//Whether it has the exact attribute
    //Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used
    public:
    VecIntLogicalBinaryInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                         bool disjoint, bool nuw, bool nsw, bool exact);

    virtual bool is_disjoint() const final;
    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_exact() const final;

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const final;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_basetype_width() const final;//Returns the bit width of the operand basetype. Just a helper function to make life easier
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Just a helper function to make life easier
};


class VecIntANDInst:public VecIntLogicalBinaryInst {
    public:
    VecIntANDInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    std::string to_string() const override;
};

class VecIntORInst:public VecIntLogicalBinaryInst {
    bool disjoint = false;//Whether it has the disjoint attribute or not

    public:
    VecIntORInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type, 
              bool disjoint);

    std::string to_string() const override;
};

class VecIntXORInst:public VecIntLogicalBinaryInst {
    public:
    VecIntXORInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type);

    std::string to_string() const override;
};

class VecIntSHLInst:public VecIntLogicalBinaryInst {
    public:
    VecIntSHLInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                   bool nuw, bool nsw);

    std::string to_string() const override;
};

class VecIntLSHRInst:public VecIntLogicalBinaryInst {
    public:
    VecIntLSHRInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                bool exact);

    std::string to_string() const override;
};

class VecIntASHRInst:public VecIntLogicalBinaryInst { 
    public:
    VecIntASHRInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                    bool exact);

    std::string to_string() const override;
};
}
}