#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <cstddef>
namespace LIRA {
namespace MIR {
// ---------------------------- Combined Quotient and Remainder instructions ---------------------------
class DivModInst:public Inst {
    // Return {T,T} i.e the output is {quotient,remainder}. This instruction is for cases where we want both quotient and remainder.}
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    bool unsigned_; 

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    DivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                bool unsigned_, std::optional<FastMathAttr> fast_math_attr);

    virtual bool is_unsigned() const final;

    virtual TypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual InstType get_inst_type() const override final;
};

class IntDivModInst:public DivModInst {
    public:
    IntDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                  bool unsigned_);

    std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const;
    std::size_t get_bitwidth() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};

class VecIntDivModInst:public DivModInst {
    public:
    VecIntDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                     bool unsigned_);

    std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_operand_basetype() const;
    std::size_t get_operand_basetype_bitwidth() const;
    std::size_t get_vector_size() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};

class FloatDivModInst:public DivModInst {
    public:
    FloatDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                    FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_operand_type() const;
    std::size_t get_bitwidth() const;
    bool is_brain_float() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};

class VecFloatDivModInst:public DivModInst {
    public:
    VecFloatDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                       FastMathAttr fast_math_attr);

    std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_operand_basetype() const;
    std::size_t get_vector_size() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};


class WideningDivModInst:public Inst {
    // Return {T,T} i.e the output is {quotient,remainder}. This instruction is for cases where we want both quotient and remainder.}
    protected:
    IR::LiteralExprPtr dividend_hi;
    IR::LiteralExprPtr dividend_lo;
    IR::LiteralExprPtr divisor;
    bool unsigned_; 
    bool exact; 

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    WideningDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr dividend_hi, IR::LiteralExprPtr dividend_lo, 
                       IR::LiteralExprPtr divisor, bool unsigned_, bool exact);

    virtual bool is_unsigned() const final;
    virtual bool is_exact() const final;

    virtual TypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_dividend_hi() const final;
    virtual IR::LiteralExprPtr get_dividend_lo() const final;
    virtual IR::LiteralExprPtr get_divisor() const final;
    virtual InstType get_inst_type() const override final;
};

class IntWideningDivModInst:public WideningDivModInst {
    public:
    IntWideningDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr dividend_hi, IR::LiteralExprPtr dividend_lo,
                          IR::LiteralExprPtr divisor, bool unsigned_, bool exact);

    std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const;
    std::size_t get_bitwidth() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};

class VecIntWideningDivModInst:public WideningDivModInst {
    public:
    VecIntWideningDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr dividend_hi, IR::LiteralExprPtr dividend_lo,
                             IR::LiteralExprPtr divisor, bool unsigned_, bool exact);

    std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_operand_basetype() const;
    std::size_t get_operand_basetype_bitwidth() const;
    std::size_t get_vector_size() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};


// ---------------------------- High-Half Arithmetic instructions ---------------------------
class MulHiInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    bool unsigned_; 

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    MulHiInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
              bool unsigned_);

    virtual bool is_unsigned() const final;

    virtual TypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual InstType get_inst_type() const override final;
};

class IntMulHiInst:public MulHiInst {
    public:
    IntMulHiInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                 bool unsigned_);

    std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const;
    std::size_t get_bitwidth() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};

class VecIntMulHiInst:public MulHiInst {
    public:
    VecIntMulHiInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                    bool unsigned_);

    std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_operand_basetype() const;
    std::size_t get_operand_basetype_bitwidth() const;
    std::size_t get_vector_size() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};


// ---------------------------- Fixed-Point Arithmetic instructions ---------------------------
class CTMulFixInst:public Inst {
    //THe compile time scale version
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    std::uint64_t scale;

    bool nuw;
    bool nsw;
    bool unsigned_; 
    bool saturating;
    bool round;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    CTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                 std::uint64_t scale, bool nuw, bool nsw, bool unsigned_, bool saturating, bool round);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_unsigned() const final;
    virtual bool is_saturating() const final;
    virtual bool is_round() const final;
    
    virtual TypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual std::uint64_t get_scale() const final;
    virtual InstType get_inst_type() const override final;
};

class IntCTMulFixInst:public CTMulFixInst {
    public:
    IntCTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                    std::uint64_t scale, bool unsigned_, bool saturating, bool nsw, bool nuw, bool round);

    std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const;
    std::size_t get_bitwidth() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};

class VecIntCTMulFixInst:public CTMulFixInst {
    public:
    VecIntCTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        std::uint64_t scale, bool unsigned_, bool saturating, bool nsw, bool nuw, bool round);

    std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_operand_basetype() const;
    std::size_t get_operand_basetype_bitwidth() const;
    std::size_t get_vector_size() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};


class RTMulFixInst:public Inst {
    //THe run time scale version
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::LiteralExprPtr scale;

    bool nuw;
    bool nsw;
    bool unsigned_; 
    bool saturating;
    bool round;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    RTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                 IR::LiteralExprPtr scale, bool nuw, bool nsw, bool unsigned_, bool saturating, bool round);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_unsigned() const final;
    virtual bool is_saturating() const final;
    virtual bool is_round() const final;
    
    virtual TypeVarient get_operand_type_varient() const = 0;
    virtual IR::TypeExprPtr get_operand_type() const final;
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual IR::LiteralExprPtr get_scale() const final;
    virtual InstType get_inst_type() const override final;
};

class IntRTMulFixInst:public RTMulFixInst {
    public:
    IntRTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                    IR::LiteralExprPtr scale, bool unsigned_, bool saturating, bool nsw, bool nuw, bool round);

    std::shared_ptr<IR::IntTypeExpr> get_casted_operand_type() const;
    std::size_t get_bitwidth() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};

class VecIntRTMulFixInst:public RTMulFixInst {
    public:
    VecIntRTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        IR::LiteralExprPtr scale, bool unsigned_, bool saturating, bool nsw, bool nuw, bool round);

    std::shared_ptr<IR::SIMDTypeExpr> get_casted_operand_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_operand_basetype() const;
    std::size_t get_operand_basetype_bitwidth() const;
    std::size_t get_vector_size() const;
    TypeVarient get_operand_type_varient() const override;

    std::string to_string() const override;
};
}
}