#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
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