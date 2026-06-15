#include "mir/instruction/terminator_inst.hpp"
#include "ast/ast.hpp"
#include "mir/instruction.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

namespace LIRA {
namespace MIR {
RetInst::RetInst(IR::InstructionStmtPtr instruction_stmt, std::optional<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> ret_value, bool noreturn)
                :Inst(instruction_stmt, nullptr) {
    this->ret_value = ret_value;
    this->noreturn = noreturn;
}
std::optional<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> RetInst::get_ret_value() const {
    return this->ret_value;
}
bool RetInst::is_noreturn() const {
    return this->noreturn;
}
InstType RetInst::get_inst_type() const {
    return InstType::RetInst;
}
std::string RetInst::to_string() const {
    std::string res = ".ret" + (ret_value.has_value() ? "(" + ret_value.value().first->to_string() + ":" + ret_value.value().second->to_string() + ")" : "");
    if(noreturn){
        res += " #[noreturn]";
    }
    return res;
}


UnreachableInst::UnreachableInst(IR::InstructionStmtPtr instruction_stmt):Inst(instruction_stmt, nullptr) {}
InstType UnreachableInst::get_inst_type() const {
    return InstType::UnreachableInst;
}
std::string UnreachableInst::to_string() const {
    return ".unreachable";
}


TrapInst::TrapInst(IR::InstructionStmtPtr instruction_stmt, bool breakpoint):Inst(instruction_stmt, nullptr) {
    this->breakpoint = breakpoint;
}
bool TrapInst::is_breakpoint() const {
    return this->breakpoint;
}
InstType TrapInst::get_inst_type() const {
    return InstType::TrapInst;
}
std::string TrapInst::to_string() const {
    std::string res = ".trap";
    if(breakpoint){
        res += " #[breakpoint]";
    }
    return res;
}

std::string pretty_print_label_args(const std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>>& label_args){
    if(label_args.empty()){
        return "";
    }
    std::string res = "{";
    //NOTE:Just using the way we represent label args in IR source
    for(std::size_t i=0;i<label_args.size();i++){
        res += label_args[i].first->to_string() ;
        if(i!=label_args.size()-1){
            res += ",";
        }
    }
    res += "}:{";
    for(std::size_t i=0;i<label_args.size();i++){
        res += label_args[i].second->to_string() ;
        if(i!=label_args.size()-1){
            res += ",";
        }
    }
    res += "}";
    return res;
}
JmpInst::JmpInst(IR::InstructionStmtPtr instruction_stmt, std::string target_block_name, IR::TypeExprPtr label_type, 
                std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> args):Inst(instruction_stmt, nullptr) {
    this->target_block_name = target_block_name;
    this->label_type = label_type;
    this->args = args;
}
std::string JmpInst::get_target_block_name() const{
    return this->target_block_name;
}
std::shared_ptr<IR::LabelTypeExpr> JmpInst::get_casted_label_type() const{
    return std::dynamic_pointer_cast<IR::LabelTypeExpr>(this->label_type);
}
std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> JmpInst::get_args() const{
    return this->args;
}
InstType JmpInst::get_inst_type() const {
    return InstType::JmpInst;
}
std::string JmpInst::to_string() const {
    std::string res = ".jmp(" + this->target_block_name;
    if(!this->args.empty()){
        res += ", " + pretty_print_label_args(this->args);
    }
    res += ")";
    return res;
}
}
}