#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <cstddef>
namespace LIRA {
namespace MIR {
class ScalarSelectInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    IR::LiteralExprPtr condition;//The condition to check. Must be of i1
    IR::LiteralExprPtr true_value;//The value and its type to return if condition is true
    IR::LiteralExprPtr false_value;//The value and its type to return if condition is false
    IR::TypeExprPtr type;//The reduced type of true_value and false_value. Both must be of same type
    public:
    ScalarSelectInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr condition, 
                     IR::LiteralExprPtr true_value, IR::LiteralExprPtr false_value, IR::TypeExprPtr type);

    IR::LiteralExprPtr get_condition() const;
    IR::LiteralExprPtr get_true_value() const;
    IR::LiteralExprPtr get_false_value() const;
    IR::TypeExprPtr get_type() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own based on type of value 
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};

class LanewiseSelectInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    IR::LiteralExprPtr condition;//The condition to check. Must be of i1
    IR::LiteralExprPtr true_value;//The value and its type to return if condition is true
    IR::LiteralExprPtr false_value;//The value and its type to return if condition is false
    std::shared_ptr<IR::SIMDTypeExpr> type;//The reduced type of true_value and false_value. Both must be of same type and must be SIMD type

    public:
    LanewiseSelectInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr condition, 
                     IR::LiteralExprPtr true_value, IR::LiteralExprPtr false_value, IR::TypeExprPtr type);
        
    IR::LiteralExprPtr get_condition() const;
    IR::LiteralExprPtr get_true_value() const;
    IR::LiteralExprPtr get_false_value() const;
    std::shared_ptr<IR::SIMDTypeExpr> get_type() const;
    IR::TypeExprPtr get_basetype() const;//Returns the base type of the SIMD type. Just a helper function to make life easier
    std::size_t get_num_elements() const;//Returns the number of elements in the SIMD type. Just a helper function to make life easier

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own based on type of value and mask
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};


class FreezeInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    IR::LiteralExprPtr value;//The value and its type to freeze
    IR::TypeExprPtr type;//The reduced type of value
    public:
    FreezeInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_type() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own based on type of value 
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};


class VaargInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    IR::LiteralExprPtr pointer;//The pointer to the variable argument list. Must be of type i8*
    IR::TypeExprPtr type;//The type of the argument to retrieve. Can be any type
    public:
    VaargInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::TypeExprPtr type);    

    IR::LiteralExprPtr get_pointer() const;
    IR::TypeExprPtr get_type() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own based on type of value
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};


class PtrMaskInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    IR::LiteralExprPtr pointer;//The pointer to mask. Must be of type ptr
    IR::LiteralExprPtr mask;//The value and its type to mask. The type must be of integer type and must have same bit width as pointer i.e i64 for our case
    public:
    PtrMaskInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask);

    IR::LiteralExprPtr get_pointer() const;
    IR::LiteralExprPtr get_mask() const;
    std::size_t get_mask_bit_width() const;//Returns the bit width of the mask. We only support x86_64 so return 64

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own based on type of value
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};

class ShuffleVectorInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    std::pair<IR::LiteralExprPtr,std::shared_ptr<IR::SIMDTypeExpr>> input1;//The first input vector and its type
    std::pair<IR::LiteralExprPtr,std::shared_ptr<IR::SIMDTypeExpr>> input2;//The second input vector and its type
    std::vector<std::int16_t> mask;//The shuffle mask. It is a vector of integers. -1 mean poison value
    public:
    ShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, std::pair<IR::LiteralExprPtr,std::shared_ptr<IR::SIMDTypeExpr>> input1, 
                      std::pair<IR::LiteralExprPtr,std::shared_ptr<IR::SIMDTypeExpr>> input2, std::vector<std::int16_t> mask);
    
    std::pair<IR::LiteralExprPtr,std::shared_ptr<IR::SIMDTypeExpr>> get_input1() const;
    std::pair<IR::LiteralExprPtr,std::shared_ptr<IR::SIMDTypeExpr>> get_input2() const;
    std::vector<std::int16_t> get_mask() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own based on type of value and mask
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};
}
}