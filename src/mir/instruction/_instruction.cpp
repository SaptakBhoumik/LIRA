#include "mir/instruction.hpp"

namespace LIRA {
namespace MIR {
Inst::Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination){
    this->instruction_stmt = instruction_stmt;
    this->destination = destination;
}

LocalDestRegisterPtr Inst::get_destination() const{
    return destination;
}
IR::InstructionStmtPtr Inst::get_instruction_stmt() const{
    return instruction_stmt;
}
IR::DebugInfoPtr Inst::get_debug_info() const{
    return instruction_stmt->get_value()->get_debug_info();
}
}
}