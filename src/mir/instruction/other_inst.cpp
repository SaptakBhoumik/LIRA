#include "mir/instruction/other_inst.hpp"
#include "ast/ast.hpp"
#include "mir/instruction.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

namespace LIRA {
namespace MIR {
ScalarSelectInst::ScalarSelectInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr condition, 
                             IR::LiteralExprPtr true_value, IR::LiteralExprPtr false_value):Inst(instruction_stmt, destination){
    this->condition = condition;
    this->true_value = true_value;
    this->false_value = false_value;
}

IR::LiteralExprPtr ScalarSelectInst::get_condition() const {
    return this->condition;
}

IR::LiteralExprPtr ScalarSelectInst::get_true_value() const {
    return this->true_value;
}

IR::LiteralExprPtr ScalarSelectInst::get_false_value() const {
    return this->false_value;
}

IR::TypeExprPtr ScalarSelectInst::get_type() const {
    return this->destination->get_type();
}
InstType ScalarSelectInst::get_inst_type() const {
    return InstType::ScalarSelectInst;
}
std::string ScalarSelectInst::to_string() const {
    return "let " + this->destination->to_string() + " = .select(i1:" + this->condition->to_string() 
            + " , " + get_type()->to_string() + ":" + this->true_value->to_string() + " , " + get_type()->to_string() + ":" + this->false_value->to_string() + ")";
}


LanewiseSelectInst::LanewiseSelectInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr condition, 
                                        IR::LiteralExprPtr true_value, IR::LiteralExprPtr false_value):Inst(instruction_stmt, destination){
    this->condition = condition;
    this->true_value = true_value;
    this->false_value = false_value;
}
IR::LiteralExprPtr LanewiseSelectInst::get_condition() const {
    return this->condition;
}
IR::LiteralExprPtr LanewiseSelectInst::get_true_value() const {
    return this->true_value;
}
IR::LiteralExprPtr LanewiseSelectInst::get_false_value() const {
    return this->false_value;
}
std::shared_ptr<IR::SIMDTypeExpr> LanewiseSelectInst::get_casted_type() const {
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
IR::TypeExprPtr LanewiseSelectInst::get_basetype() const {
    return get_casted_type()->get_basetype();
}
std::size_t LanewiseSelectInst::get_num_elements() const {
    return get_casted_type()->get_size();
}
InstType LanewiseSelectInst::get_inst_type() const {
    return InstType::LanewiseSelectInst;
}
std::string LanewiseSelectInst::to_string() const {
    return "let " + this->destination->to_string() + " = .select(<i1,"+ std::to_string(get_num_elements()) + ">:" + this->condition->to_string() 
            + " , " + get_casted_type()->to_string() + ":" + this->true_value->to_string() + " , " + get_casted_type()->to_string() + ":" + this->false_value->to_string() + ")";
}


FreezeInst::FreezeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                        :Inst(instruction_stmt, destination){
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
    return "let " + this->destination->to_string() + " = .freeze(" + this->value->to_string() + ")";
}


VaargInst::VaargInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer)
                    :Inst(instruction_stmt, destination){
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
    return "let " + this->destination->to_string() + " = .va_arg(ptr:" + this->pointer->to_string() + ")";
}


PtrMaskInst::PtrMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask)
                    :Inst(instruction_stmt, destination){
    this->pointer = pointer;
    this->mask = mask;
}
IR::LiteralExprPtr PtrMaskInst::get_pointer() const{
    return this->pointer;
}
IR::LiteralExprPtr PtrMaskInst::get_mask() const{
    return this->mask;
}
std::size_t PtrMaskInst::get_mask_bit_width() const{
    return 64;
}
InstType PtrMaskInst::get_inst_type() const{
    return InstType::PtrMaskInst;
}
std::string PtrMaskInst::to_string() const{
    return "let " + this->destination->to_string() + " = .ptr_mask(ptr:" + this->pointer->to_string() + ", i64:" + this->mask->to_string() + ")";
}


ShuffleVectorInst::ShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::pair<IR::LiteralExprPtr,IR::TypeExprPtr> input1, 
                                     std::pair<IR::LiteralExprPtr,IR::TypeExprPtr> input2, std::vector<std::int16_t> mask)
                    :Inst(instruction_stmt, destination){
    this->input1 = input1;
    this->input2 = input2;
    this->mask = mask;
}
std::pair<IR::LiteralExprPtr,IR::TypeExprPtr> ShuffleVectorInst::get_input1() const{
    return this->input1;
}
std::pair<IR::LiteralExprPtr,IR::TypeExprPtr> ShuffleVectorInst::get_input2() const{
    return this->input2;
}
std::pair<std::shared_ptr<IR::SIMDTypeExpr>,std::shared_ptr<IR::SIMDTypeExpr>> ShuffleVectorInst::get_casted_input_types() const{
    return std::make_pair(std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input1.second), std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input2.second));
}
std::pair<std::size_t,std::size_t> ShuffleVectorInst::get_input_vector_size() const{
    auto casted_types = get_casted_input_types();
    return std::make_pair(casted_types.first->get_size(), casted_types.second->get_size());
}
IR::TypeExprPtr ShuffleVectorInst::get_input_basetype() const{
    auto casted_types = get_casted_input_types();
    return casted_types.first->get_basetype();
}
std::vector<std::int16_t> ShuffleVectorInst::get_mask() const{
    return this->mask;
}
InstType ShuffleVectorInst::get_inst_type() const{
    return InstType::ShuffleVectorInst;
}
std::string ShuffleVectorInst::to_string() const{
    std::string res = "let " + this->destination->to_string() + " = .shuffle_vector("
                    +  input1.second->to_string() + ":" + input1.first->to_string() + ", " + input2.second->to_string() + ":" + input2.first->to_string() +
            ", <i64" + std::to_string(this->mask.size()) + ">:<";
    for(std::size_t i = 0; i < this->mask.size(); i++){
        res += std::to_string(this->mask[i]);
        if(i != this->mask.size() - 1){
            res += ", ";
        }
    }
    res += ">)";
    return res; 
}
}
}