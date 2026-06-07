#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <cstddef>
namespace LIRA {
namespace MIR {
class CallInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable
};
}
}