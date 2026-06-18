#include "mir/instruction/other_inst.hpp"
#include "ast/ast.hpp"
#include "mir/instruction.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

namespace LIRA {
namespace MIR {
ScalarSelectInst::ScalarSelectInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr condition, 
                                    IR::LiteralExprPtr true_value, IR::LiteralExprPtr false_value, std::optional<FastMathAttr> fast_math_attr):
                                    Inst(instruction_stmt, destination, fast_math_attr){
    this->condition = condition;
    this->true_value = true_value;
    this->false_value = false_value;
}
IR::LiteralExprPtr ScalarSelectInst::get_condition() const{
    return this->condition;
}
IR::LiteralExprPtr ScalarSelectInst::get_true_value() const{
    return this->true_value;
}
IR::LiteralExprPtr ScalarSelectInst::get_false_value() const{
    return this->false_value;
}
IR::TypeExprPtr ScalarSelectInst::get_type() const{
    return this->destination->get_type();
}
InstType ScalarSelectInst::get_inst_type() const{
    return InstType::ScalarSelectInst;
}
std::string ScalarSelectInst::to_string() const{
    std::string res = "let " + this->destination->to_string() + " = .select(i1:" + this->condition->to_string() + ", "  +
                                                                            get_type()->to_string() + ":" + this->true_value->to_string() + ", " +
                                                                            get_type()->to_string() + ":" + this->false_value->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;     
}


LanewiseSelectInst::LanewiseSelectInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr condition, 
                                   IR::LiteralExprPtr true_value, IR::LiteralExprPtr false_value, std::optional<FastMathAttr> fast_math_attr):
                                   Inst(instruction_stmt, destination, fast_math_attr){
    this->condition = condition;
    this->true_value = true_value;
    this->false_value = false_value;
}
IR::LiteralExprPtr LanewiseSelectInst::get_condition() const{
    return this->condition;
}
IR::LiteralExprPtr LanewiseSelectInst::get_true_value() const{
    return this->true_value;
}
IR::LiteralExprPtr LanewiseSelectInst::get_false_value() const{
    return this->false_value;
}
std::shared_ptr<IR::SIMDTypeExpr> LanewiseSelectInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
IR::TypeExprPtr LanewiseSelectInst::get_basetype() const{
    return this->get_casted_type()->get_basetype();
}
std::size_t LanewiseSelectInst::get_num_elements() const{
    return this->get_casted_type()->get_size();
}
InstType LanewiseSelectInst::get_inst_type() const{
    return InstType::LanewiseSelectInst;
}
std::string LanewiseSelectInst::to_string() const{
    std::string res = "let " + this->destination->to_string() + " = .select(<i1," + std::to_string(this->get_num_elements()) + ">:" + this->condition->to_string() + ", "  +
                                                                            this->get_casted_type()->to_string() + ":" + this->true_value->to_string() + ", " +
                                                                            this->get_casted_type()->to_string() + ":" + this->false_value->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;     
}


FreezeInst::FreezeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, std::optional<FastMathAttr> fast_math_attr):
                Inst(instruction_stmt, destination, fast_math_attr){
    this->value = value;
}
IR::LiteralExprPtr FreezeInst::get_value() const{
    return this->value;
}
IR::TypeExprPtr FreezeInst::get_type() const{
    return this->destination->get_type();
}
InstType FreezeInst::get_inst_type() const{
    return InstType::FreezeInst;
}
std::string FreezeInst::to_string() const{
    std::string res = "let " + this->destination->to_string() + " = .freeze(" + this->value->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}


VastartInst::VastartInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer):
                         Inst(instruction_stmt, nullptr, std::nullopt){
    this->pointer = pointer;
}
IR::LiteralExprPtr VastartInst::get_pointer() const{
    return this->pointer;
}
InstType VastartInst::get_inst_type() const{
    return InstType::VastartInst;
}
std::string VastartInst::to_string() const{
    return ".vastart(ptr:" + this->pointer->to_string() + ")";
}


VaendInst::VaendInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer):
                     Inst(instruction_stmt, nullptr, std::nullopt){
    this->pointer = pointer;
}
IR::LiteralExprPtr VaendInst::get_pointer() const{
    return this->pointer;
}
InstType VaendInst::get_inst_type() const{
    return InstType::VaendInst;
}
std::string VaendInst::to_string() const{
    return ".vaend(ptr:" + this->pointer->to_string() + ")";
}


VacopyInst::VacopyInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr dest_pointer, IR::LiteralExprPtr src_pointer):
                      Inst(instruction_stmt, nullptr, std::nullopt){
    this->dest_pointer = dest_pointer;
    this->src_pointer = src_pointer;
}
IR::LiteralExprPtr VacopyInst::get_dest_pointer() const{
    return this->dest_pointer;
}
IR::LiteralExprPtr VacopyInst::get_src_pointer() const{
    return this->src_pointer;
}
InstType VacopyInst::get_inst_type() const{
    return InstType::VacopyInst;
}
std::string VacopyInst::to_string() const{
    return ".vacopy(ptr:" + this->dest_pointer->to_string() + ", ptr:" + this->src_pointer->to_string() + ")";
}


VaargInst::VaargInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, std::optional<FastMathAttr> fast_math_attr):
                     Inst(instruction_stmt, destination, fast_math_attr){
    this->pointer = pointer;
}
IR::LiteralExprPtr VaargInst::get_pointer() const{
    return this->pointer;
}
IR::TypeExprPtr VaargInst::get_type() const{
    return this->destination->get_type();
}
InstType VaargInst::get_inst_type() const{
    return InstType::VaargInst;
}
std::string VaargInst::to_string() const{
    return "let " + this->destination->to_string() + " = .vaarg(ptr:" + this->pointer->to_string() + ")";
}


PtrMaskInst::PtrMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask):
                     Inst(instruction_stmt, destination, std::nullopt){
    this->pointer = pointer;
    this->mask = mask;
}
IR::LiteralExprPtr PtrMaskInst::get_pointer() const{
    return this->pointer;
}
IR::LiteralExprPtr PtrMaskInst::get_mask() const{
    return this->mask;
}
InstType PtrMaskInst::get_inst_type() const{
    return InstType::PtrMaskInst;
}
std::string PtrMaskInst::to_string() const{
    return "let " + this->destination->to_string() + " = .ptrmask(ptr:" + this->pointer->to_string() + ", i64:" + this->mask->to_string() + ")";
}


PauseInst::PauseInst(IR::InstructionStmtPtr instruction_stmt):Inst(instruction_stmt, nullptr, std::nullopt){}
InstType PauseInst::get_inst_type() const{
    return InstType::PauseInst;
}
std::string PauseInst::to_string() const{
    return ".pause";
}
}
}