#include "mir/instruction/arithmetic_bin_inst.hpp"
#include "mir/instruction.hpp"

namespace LIRA {
namespace MIR {
ArithmeticBinaryInst::ArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, 
                                           IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs):Inst(instruction_stmt, destination){
    this->lhs = lhs;
    this->rhs = rhs;
}

IR::TypeExprPtr ArithmeticBinaryInst::get_operand_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr ArithmeticBinaryInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr ArithmeticBinaryInst::get_rhs() const{
    return this->rhs;
}
InstType ArithmeticBinaryInst::get_inst_type() const{
    return InstType::ArithmeticBinaryInst;
}
// ---------------------------- Integer binary operations ---------------------------
IntArithmeticBinaryInst::IntArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, 
                                                IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, bool nuw, bool nsw, bool unsigned_, bool exact):
                                                ArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->exact = exact;
}

bool IntArithmeticBinaryInst::is_nuw() const{
    return this->nuw;
}
bool IntArithmeticBinaryInst::is_nsw() const{
    return this->nsw;
}
bool IntArithmeticBinaryInst::is_unsigned() const{
    return this->unsigned_;
}
bool IntArithmeticBinaryInst::is_exact() const{
    return this->exact;
}

IntAddInst::IntAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw):IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, false, false){}
ArithmeticBinaryInst::OpType IntAddInst::get_op_type() const{
    return OpType::ADD;
}
std::string IntAddInst::to_string() const{
    std::string res = "let " + destination->get_dest_register_name() + " = .int_add(" + lhs->to_string() + ", " + rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    return res;
}
}
}