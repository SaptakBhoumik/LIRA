#include "mir//instruction/_instruction.hpp"
#include <optional>

namespace LIRA {
namespace MIR {
Inst::Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::optional<FastMathAttr> fast_math_attr){
    this->instruction_stmt = instruction_stmt;
    this->destination = destination;
    this->fast_math_attr = fast_math_attr;
}
LocalDestRegisterPtr Inst::get_destination() const{
    return this->destination;
}
std::optional<FastMathAttr> Inst::get_fast_math_attr() const{
    return this->fast_math_attr;
}
IR::InstructionStmtPtr Inst::get_instruction_stmt() const{
    return this->instruction_stmt;
}
IR::DebugInfoPtr Inst::get_debug_info() const{
    return this->instruction_stmt->get_value()->get_debug_info();
}
}
}