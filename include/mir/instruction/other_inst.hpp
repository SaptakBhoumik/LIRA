#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <cstddef>
namespace LIRA {
namespace MIR {
class ScalarSelectInst:public Inst {
    IR::LiteralExprPtr condition;//The condition to check. Must be of i1
    IR::LiteralExprPtr true_value;//The value and its type to return if condition is true
    IR::LiteralExprPtr false_value;//The value and its type to return if condition is false
    public:
    ScalarSelectInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr condition, 
                     IR::LiteralExprPtr true_value, IR::LiteralExprPtr false_value);

    IR::LiteralExprPtr get_condition() const;
    IR::LiteralExprPtr get_true_value() const;
    IR::LiteralExprPtr get_false_value() const;
    IR::TypeExprPtr get_type() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class LanewiseSelectInst:public Inst {
    IR::LiteralExprPtr condition;//The condition to check. Must be of i1
    IR::LiteralExprPtr true_value;//The value and its type to return if condition is true
    IR::LiteralExprPtr false_value;//The value and its type to return if condition is false

    public:
    LanewiseSelectInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr condition, 
                       IR::LiteralExprPtr true_value, IR::LiteralExprPtr false_value);
        
    IR::LiteralExprPtr get_condition() const;
    IR::LiteralExprPtr get_true_value() const;
    IR::LiteralExprPtr get_false_value() const;
    std::shared_ptr<IR::SIMDTypeExpr> get_casted_type() const;
    IR::TypeExprPtr get_basetype() const;//Returns the base type of the SIMD type. Just a helper function to make life easier
    std::size_t get_num_elements() const;//Returns the number of elements in the SIMD type. Just a helper function to make life easier

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class FreezeInst:public Inst {
    IR::LiteralExprPtr value;//The value and its type to freeze
    public:
    FreezeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_type() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class VaargInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to the variable argument list. Must be of type i8*
    IR::TypeExprPtr type;//The type of the argument to retrieve. Can be any type
    public:
    VaargInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer);    

    IR::LiteralExprPtr get_pointer() const;
    IR::TypeExprPtr get_type() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class PtrMaskInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to mask. Must be of type ptr
    IR::LiteralExprPtr mask;//The value and its type to mask. The type must be of integer type and must have same bit width as pointer i.e i64 for our case
    public:
    PtrMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask);

    IR::LiteralExprPtr get_pointer() const;
    IR::LiteralExprPtr get_mask() const;
    std::size_t get_mask_bitwidth() const;//Returns the bit width of the mask. We only support x86_64 so return 64

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

}
}