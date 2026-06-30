#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <cstdint>
#include <iostream>
#include <functional>
#include <memory>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                    IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_local_inst(std::string filename, Utils::VarSymTablePtr var_symtable, MIR::LocalDestRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
}
}