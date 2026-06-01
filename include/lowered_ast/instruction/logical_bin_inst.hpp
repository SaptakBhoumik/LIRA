#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
// ---------------------------Logical Binary operations ---------------------------
class LogicalBinaryInst:public Inst {
    protected:
    InstructionStmtPtr instruction_stmt;

    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable
    LiteralExprPtr lhs;
    LiteralExprPtr rhs;
    TypeExprPtr type;//Reduced type. 
    public:
    LogicalBinaryInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type);

    virtual ~LogicalBinaryInst() = default;

    TypeExprPtr get_operand_type() const;
    LiteralExprPtr get_lhs() const;
    LiteralExprPtr get_rhs() const;

    std::optional<std::pair<DestinationVar,TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own. <i1,M> if ``type``
                                                                                          //is vector and i1 if it is scalar
    InstructionStmtPtr get_instruction_stmt() const override;
};

// ---------------------------Logical Integer Binary operations ---------------------------
class IntANDInst:public LogicalBinaryInst {
    public:
    IntANDInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type);

    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class IntORInst:public LogicalBinaryInst {
    bool disjoint = false;//Whether it has the disjoint attribute or not

    public:
    IntORInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
              bool disjoint);

    bool is_disjoint() const;
    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class IntXORInst:public LogicalBinaryInst {
    public:
    IntXORInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type);

    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class IntSHLInst:public LogicalBinaryInst {
    bool nuw;//Whether it has the nsw or nuw attribute.
    bool nsw;//Whether it has the nsw or nuw attribute.

    public:
    IntSHLInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type,
                bool nuw, bool nsw);

    bool is_nuw() const;
    bool is_nsw() const;
    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class IntLSHRInst:public LogicalBinaryInst {
    bool exact;//Whether it has the exact attribute.
    
    public:
    IntLSHRInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type,
                bool exact);

    bool is_exact() const;
    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class IntASHRInst:public LogicalBinaryInst {
    bool exact;//Whether it has the exact attribute.
    
    public:
    IntASHRInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type,
                bool exact);

    bool is_exact() const;
    std::shared_ptr<IntTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to IntTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};


// ---------------------------Vector Integer Binary operations ---------------------------
class VecIntANDInst:public LogicalBinaryInst {
    public:
    VecIntANDInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type);

    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecIntORInst:public LogicalBinaryInst {
    bool disjoint = false;//Whether it has the disjoint attribute or not

    public:
    VecIntORInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type, 
              bool disjoint);

    bool is_disjoint() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecIntXORInst:public LogicalBinaryInst {
    public:
    VecIntXORInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type);

    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecIntSHLInst:public LogicalBinaryInst {
    bool nuw;//Whether it has the nsw or nuw attribute.
    bool nsw;//Whether it has the nsw or nuw attribute.

    public:
    VecIntSHLInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type,
                   bool nuw, bool nsw);

    bool is_nuw() const;
    bool is_nsw() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecIntLSHRInst:public LogicalBinaryInst {
    bool exact;//Whether it has the exact attribute.
    
    public:
    VecIntLSHRInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type,
                bool exact);

    bool is_exact() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};

class VecIntASHRInst:public LogicalBinaryInst {
    bool exact;//Whether it has the exact attribute.
    
    public:
    VecIntASHRInst(InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, LiteralExprPtr lhs, LiteralExprPtr rhs, TypeExprPtr type,
                bool exact);

    bool is_exact() const;
    std::shared_ptr<SIMDTypeExpr> get_casted_operand_type() const;//Returns the operand type casted to SIMDTypeExpr. Just a helper function to make life easier

    InstType get_type() const override;
    std::string to_string() const override;
};
}