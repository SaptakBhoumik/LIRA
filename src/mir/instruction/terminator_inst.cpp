#include "mir/instruction/terminator_inst.hpp"
#include "ast/ast.hpp"

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


ConditionalJmpInst::ConditionalJmpInst(IR::InstructionStmtPtr instruction_stmt, std::string true_block_name, std::string false_block_name, 
                       IR::TypeExprPtr true_label_type, IR::TypeExprPtr false_label_type,
                       std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> true_label_args, std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> false_label_args, 
                       IR::LiteralExprPtr condition, std::vector<std::size_t> frequency_profile, bool unpredictable):Inst(instruction_stmt, nullptr) {
    this->true_block_name = true_block_name;
    this->false_block_name = false_block_name;
    this->true_label_type = true_label_type;
    this->false_label_type = false_label_type;
    this->true_label_args = true_label_args;
    this->false_label_args = false_label_args;
    this->condition = condition;
    this->frequency_profile = frequency_profile;
    this->unpredictable = unpredictable;
}
std::string ConditionalJmpInst::get_true_block_name() const{
    return this->true_block_name;
}
std::string ConditionalJmpInst::get_false_block_name() const{
    return this->false_block_name;
}
std::shared_ptr<IR::LabelTypeExpr> ConditionalJmpInst::get_casted_true_label_type() const{
    return std::dynamic_pointer_cast<IR::LabelTypeExpr>(this->true_label_type);
}
std::shared_ptr<IR::LabelTypeExpr> ConditionalJmpInst::get_casted_false_label_type() const{
    return std::dynamic_pointer_cast<IR::LabelTypeExpr>(this->false_label_type);
}
std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> ConditionalJmpInst::get_true_label_args() const{
    return this->true_label_args;
}
std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> ConditionalJmpInst::get_false_label_args() const{
    return this->false_label_args;
}
IR::LiteralExprPtr ConditionalJmpInst::get_condition() const{
    return this->condition;
}
std::vector<std::size_t> ConditionalJmpInst::get_frequency_profile() const{
    return this->frequency_profile;
}
bool ConditionalJmpInst::is_unpredictable() const{
    return this->unpredictable;
}
InstType ConditionalJmpInst::get_inst_type() const {
    return InstType::ConditionalJmpInst;
}
std::string ConditionalJmpInst::to_string() const {
    std::string res = ".cond_jmp(i1:" + this->condition->to_string() + ", ";
    res += this->true_label_type->to_string() + ":" + this->true_block_name + ", " + pretty_print_label_args(this->true_label_args) + ", ";
    res += this->false_label_type->to_string() + ":" + this->false_block_name + ", " + pretty_print_label_args(this->false_label_args) + ")";
    if(!this->frequency_profile.empty()){
        res += " #[freq(";
        for(std::size_t i=0;i<this->frequency_profile.size();i++){
            res += std::to_string(this->frequency_profile[i]);
            if(i!=this->frequency_profile.size()-1){
                res += ",";
            }
        }
        res += ")]";
    }
    if(this->unpredictable){
        res += " #[unpredictable]";
    }
    return res;
}


SwitchInst::SwitchInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr value, IR::TypeExprPtr value_type, std::vector<std::string> case_block_names, std::vector<IR::TypeExprPtr> case_label_types, 
              std::vector<std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>>> case_label_args, std::vector<IR::LiteralExprPtr> case_values, std::string default_block_name,
              IR::TypeExprPtr default_label_type, std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> default_label_args, std::vector<std::size_t> frequency_profile, bool unpredictable)
              :Inst(instruction_stmt, nullptr) {
    this->value = value;
    this->value_type = value_type;
    this->case_block_names = case_block_names;
    this->case_label_types = case_label_types;
    this->case_label_args = case_label_args;
    this->case_values = case_values;
    this->default_block_name = default_block_name;
    this->default_label_type = default_label_type;
    this->default_label_args = default_label_args;
    this->frequency_profile = frequency_profile;
    this->unpredictable = unpredictable;
}

IR::LiteralExprPtr SwitchInst::get_value() const {
    return this->value;
}

std::shared_ptr<IR::IntTypeExpr> SwitchInst::get_casted_value_type() const {
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->value_type);
}

std::size_t SwitchInst::get_value_bit_width() const {
    return get_casted_value_type()->get_bits();
}

std::vector<std::string> SwitchInst::get_case_block_names() const {
    return this->case_block_names;
}

std::vector<std::shared_ptr<IR::LabelTypeExpr>> SwitchInst::get_casted_case_label_types() const {
    std::vector<std::shared_ptr<IR::LabelTypeExpr>> casted_types;
    for (const auto &type : this->case_label_types) {
        casted_types.push_back(std::dynamic_pointer_cast<IR::LabelTypeExpr>(type));
    }
    return casted_types;
}

std::vector<std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>>> SwitchInst::get_case_label_args() const {
    return this->case_label_args;
}
std::vector<IR::LiteralExprPtr> SwitchInst::get_case_values() const {
    return this->case_values;
}
std::string SwitchInst::get_default_block_name() const {
    return this->default_block_name;
}
std::shared_ptr<IR::LabelTypeExpr> SwitchInst::get_casted_default_label_type() const {
    return std::dynamic_pointer_cast<IR::LabelTypeExpr>(this->default_label_type);
}
std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> SwitchInst::get_default_label_args() const {
    return this->default_label_args;
}
std::vector<std::size_t> SwitchInst::get_frequency_profile() const {
    return this->frequency_profile;
}
bool SwitchInst::is_unpredictable() const {
    return this->unpredictable;
}
InstType SwitchInst::get_inst_type() const {
    return InstType::SwitchInst;
}
std::string SwitchInst::to_string() const{
    std::string res = ".switch(" + this->value_type->to_string() + ":" + this->value->to_string() + ", " + this->default_label_type->to_string() + ":" + this->default_block_name + ", " + pretty_print_label_args(this->default_label_args) + ", ";
    for(std::size_t i=0;i<this->case_block_names.size();i++){
        res += this->value_type->to_string() + ":" + this->case_values[i]->to_string() + ", ";
        res += this->case_label_types[i]->to_string() + ":" + this->case_block_names[i] + ", " + pretty_print_label_args(this->case_label_args[i]);
        if(i!=this->case_block_names.size()-1){
            res += "; ";
        }
    }
    res+= ")";
    if(!this->frequency_profile.empty()){
        res += " #[freq(";
        for(std::size_t i=0;i<this->frequency_profile.size();i++){
            res += std::to_string(this->frequency_profile[i]);
            if(i!=this->frequency_profile.size()-1){
                res += ",";
            }
        }
        res += ")]";
    }
    if(this->unpredictable){
        res += " #[unpredictable]";
    }
    return res;
}


IndirectJmpInst::IndirectJmpInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr target_block_address, std::vector<std::string> possible_target_blocks, 
                                 std::vector<std::size_t> frequency_profile, bool unpredictable)
                                 :Inst(instruction_stmt, nullptr) {
    this->target_block_address = target_block_address;
    this->possible_target_blocks = possible_target_blocks;
    this->frequency_profile = frequency_profile;
    this->unpredictable = unpredictable;    
}
IR::LiteralExprPtr IndirectJmpInst::get_target_block_address() const {
    return this->target_block_address;
}
std::vector<std::string> IndirectJmpInst::get_possible_target_blocks() const {
    return this->possible_target_blocks;
}
std::vector<std::size_t> IndirectJmpInst::get_frequency_profile() const {
    return this->frequency_profile;
}
bool IndirectJmpInst::is_unpredictable() const {
    return this->unpredictable;
}
InstType IndirectJmpInst::get_inst_type() const {
    return InstType::IndirectJmpInst;
}
std::string IndirectJmpInst::to_string() const {
    std::string res = ".indirect_jmp(ptr:" + this->target_block_address->to_string() + ", ";
    for(std::size_t i=0;i<this->possible_target_blocks.size();i++){
        res += "label:" + this->possible_target_blocks[i];
        if(i!=this->possible_target_blocks.size()-1){
            res += ",";
        }
    }
    res += ")";
    if(!this->frequency_profile.empty()){
        res += " #[freq(";
        for(std::size_t i=0;i<this->frequency_profile.size();i++){
            res += std::to_string(this->frequency_profile[i]);
            if(i!=this->frequency_profile.size()-1){
                res += ",";
            }
        }
        res += ")]";
    }
    if(this->unpredictable){
        res += " #[unpredictable]";
    }
    return res;
}
}
}