#include "mir/instruction/other_inst.hpp"

namespace LIRA {
namespace MIR {
// --------------------------Unclassified other instructions-------------------------------
ScalarSelectInst::ScalarSelectInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr condition, 
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


LanewiseSelectInst::LanewiseSelectInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr condition, 
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


FreezeInst::FreezeInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, std::optional<FastMathAttr> fast_math_attr):
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


VaargInst::VaargInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, std::optional<FastMathAttr> fast_math_attr):
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


PtrMaskInst::PtrMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask):
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


IntPtrMaskInst::IntPtrMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask)
                               :PtrMaskInst(instruction_stmt, destination, pointer, mask){}
TypeVariant IntPtrMaskInst::get_dest_type_var() const{
    return TypeVariant::Ptr;
}
std::string IntPtrMaskInst::to_string() const{
    return "let " + this->destination->to_string() + " = .ptrmask(ptr:" + this->pointer->to_string() + ", i64:" + this->mask->to_string() + ")";
}


VecIntPtrMaskInst::VecIntPtrMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask)
                               :PtrMaskInst(instruction_stmt, destination, pointer, mask){}
TypeVariant VecIntPtrMaskInst::get_dest_type_var() const{
    return TypeVariant::Ptr;
}
std::size_t VecIntPtrMaskInst::get_vector_size() const{
    auto type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return type->get_size();
}
std::string VecIntPtrMaskInst::to_string() const{
    std::string size = std::to_string(this->get_vector_size());
    return "let " + this->destination->to_string() + " = .ptrmask(<ptr," + size + ">:" + this->pointer->to_string() + ", <i64," + size + ">:" + this->mask->to_string() + ")";
}


PauseInst::PauseInst(IR::InstructionStmtPtr instruction_stmt):Inst(instruction_stmt, nullptr, std::nullopt){}
InstType PauseInst::get_inst_type() const{
    return InstType::PauseInst;
}
std::string PauseInst::to_string() const{
    return ".pause";
}


// --------------------------Binding Assumptions-------------------------------
AssumeInst::AssumeInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, std::vector<IR::LiteralExprPtr> assumed_values, IR::TypeExprPtr type, 
                      std::optional<FastMathAttr> fast_math_attr):
                       Inst(instruction_stmt, nullptr, fast_math_attr){
    this->assumed_values = assumed_values;
    this->type = type;
    this->varname = varname;    
}
std::string AssumeInst::get_varname() const{
    return this->varname;
}
std::vector<IR::LiteralExprPtr> AssumeInst::get_assumed_values() const{
    return this->assumed_values;
}
IR::TypeExprPtr AssumeInst::get_type() const{
    return this->type;
}
InstType AssumeInst::get_inst_type() const{
    return InstType::AssumeInst;
}
std::string AssumeInst::to_string() const{
    std::string res = ".assume(" + this->type->to_string() + ":" + this->varname;
    for(auto& val: this->assumed_values){
        res += ", " + this->type->to_string() + ":" + val->to_string();
    }
    res += ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}


AssumeRangeInst::AssumeRangeInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, IR::LiteralExprPtr min_value, IR::LiteralExprPtr max_value, 
                                 IR::TypeExprPtr type, bool unsigned_, std::optional<FastMathAttr> fast_math_attr):
                                  Inst(instruction_stmt, nullptr, fast_math_attr){
    this->min_value = min_value;
    this->max_value = max_value;
    this->type = type;
    this->varname = varname;
    this->unsigned_ = unsigned_;
}
std::string AssumeRangeInst::get_varname() const{
    return this->varname;
}
IR::LiteralExprPtr AssumeRangeInst::get_min_value() const{
    return this->min_value;
}
IR::LiteralExprPtr AssumeRangeInst::get_max_value() const{
    return this->max_value;
}
IR::TypeExprPtr AssumeRangeInst::get_type() const{
    return this->type;
}
bool AssumeRangeInst::is_unsigned() const{
    return this->unsigned_;
}
InstType AssumeRangeInst::get_inst_type() const{
    return InstType::AssumeRangeInst;
}
std::string AssumeRangeInst::to_string() const{
    std::string res = ".assume(" + this->type->to_string() + ":" + this->varname + ", " + this->type->to_string() + ":" + this->min_value->to_string() + ", " +
                      this->type->to_string() + ":" + this->max_value->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}


AssumeNotInst::AssumeNotInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, std::vector<IR::LiteralExprPtr> assumed_values, IR::TypeExprPtr type, 
                      std::optional<FastMathAttr> fast_math_attr):
                       Inst(instruction_stmt, nullptr, fast_math_attr){
    this->assumed_values = assumed_values;
    this->type = type;
    this->varname = varname;    
}
std::string AssumeNotInst::get_varname() const{
    return this->varname;
}
std::vector<IR::LiteralExprPtr> AssumeNotInst::get_assumed_values() const{
    return this->assumed_values;
}
IR::TypeExprPtr AssumeNotInst::get_type() const{
    return this->type;
}
InstType AssumeNotInst::get_inst_type() const{
    return InstType::AssumeNotInst;
}
std::string AssumeNotInst::to_string() const{
    std::string res = ".assume_not(" + this->type->to_string() + ":" + this->varname;
    for(auto& val: this->assumed_values){
        res += ", " + this->type->to_string() + ":" + val->to_string();
    }
    res += ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}


AssumeNotRangeInst::AssumeNotRangeInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, IR::LiteralExprPtr min_value, IR::LiteralExprPtr max_value, 
                                        IR::TypeExprPtr type, bool unsigned_, std::optional<FastMathAttr> fast_math_attr):
                                        Inst(instruction_stmt, nullptr, fast_math_attr){
    this->min_value = min_value;
    this->max_value = max_value;
    this->type = type;
    this->varname = varname;
    this->unsigned_ = unsigned_;
}
std::string AssumeNotRangeInst::get_varname() const{
    return this->varname;
}
IR::LiteralExprPtr AssumeNotRangeInst::get_min_value() const{
    return this->min_value;
}
IR::LiteralExprPtr AssumeNotRangeInst::get_max_value() const{
    return this->max_value;
}
IR::TypeExprPtr AssumeNotRangeInst::get_type() const{
    return this->type;
}
bool AssumeNotRangeInst::is_unsigned() const{
    return this->unsigned_;
}
InstType AssumeNotRangeInst::get_inst_type() const{
    return InstType::AssumeNotRangeInst;
}
std::string AssumeNotRangeInst::to_string() const{
    std::string res = ".assume_not_range(" + this->type->to_string() + ":" + this->varname + ", " + this->type->to_string() + ":" + this->min_value->to_string() + ", " +
                      this->type->to_string() + ":" + this->max_value->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}


// --------------------------Non-Binding Expectation Hints-------------------------------
ExpectInst::ExpectInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, std::vector<IR::LiteralExprPtr> assumed_values, IR::TypeExprPtr type, 
                       std::optional<double> probability, std::optional<FastMathAttr> fast_math_attr):
                       Inst(instruction_stmt, nullptr, fast_math_attr){
    this->assumed_values = assumed_values;
    this->type = type;
    this->varname = varname;
    this->probability = probability;
}
std::string ExpectInst::get_varname() const{
    return this->varname;
}
std::vector<IR::LiteralExprPtr> ExpectInst::get_assumed_values() const{
    return this->assumed_values;
}
std::optional<double> ExpectInst::get_probability() const{
    return this->probability;
}
IR::TypeExprPtr ExpectInst::get_type() const{
    return this->type;
}
InstType ExpectInst::get_inst_type() const{
    return InstType::ExpectInst;
}
std::string ExpectInst::to_string() const{
    std::string res = ".expect(" + this->type->to_string() + ":" + this->varname;
    for(auto& val: this->assumed_values){
        res += ", " + this->type->to_string() + ":" + val->to_string();
    }
    res += ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    if(this->probability.has_value()){
        res += " #[probability(f64:" + std::to_string(this->probability.value()) + ")]";
    }
    return res;
}


ExpectRangeInst::ExpectRangeInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, IR::LiteralExprPtr min_value, IR::LiteralExprPtr max_value, 
                                 IR::TypeExprPtr type, std::optional<double> probability, bool unsigned_, std::optional<FastMathAttr> fast_math_attr):
                                  Inst(instruction_stmt, nullptr, fast_math_attr){
    this->min_value = min_value;
    this->max_value = max_value;
    this->type = type;
    this->varname = varname;
    this->probability = probability;
    this->unsigned_ = unsigned_;
}
std::string ExpectRangeInst::get_varname() const{
    return this->varname;
}
IR::LiteralExprPtr ExpectRangeInst::get_min_value() const{
    return this->min_value;
}
IR::LiteralExprPtr ExpectRangeInst::get_max_value() const{
    return this->max_value;
}
std::optional<double> ExpectRangeInst::get_probability() const{
    return this->probability;
}
IR::TypeExprPtr ExpectRangeInst::get_type() const{
    return this->type;
}
bool ExpectRangeInst::is_unsigned() const{
    return this->unsigned_;
}
InstType ExpectRangeInst::get_inst_type() const{
    return InstType::ExpectRangeInst;
}
std::string ExpectRangeInst::to_string() const{
    std::string res = ".expect_range(" + this->type->to_string() + ":" + this->varname + ", " + this->type->to_string() + ":" + this->min_value->to_string() + ", " +
                      this->type->to_string() + ":" + this->max_value->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    if(this->probability.has_value()){
        res += " #[probability(f64:" + std::to_string(this->probability.value()) + ")]";
    }
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}


ExpectNotInst::ExpectNotInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, std::vector<IR::LiteralExprPtr> assumed_values, IR::TypeExprPtr type, 
                             std::optional<double> probability, std::optional<FastMathAttr> fast_math_attr):
                             Inst(instruction_stmt, nullptr, fast_math_attr){
    this->assumed_values = assumed_values;
    this->type = type;
    this->varname = varname;
    this->probability = probability;
}
std::string ExpectNotInst::get_varname() const{
    return this->varname;
}
std::vector<IR::LiteralExprPtr> ExpectNotInst::get_assumed_values() const{
    return this->assumed_values;
}
std::optional<double> ExpectNotInst::get_probability() const{
    return this->probability;
}
IR::TypeExprPtr ExpectNotInst::get_type() const{
    return this->type;
}
InstType ExpectNotInst::get_inst_type() const{
    return InstType::ExpectNotInst;
}
std::string ExpectNotInst::to_string() const{
    std::string res = ".expect_not(" + this->type->to_string() + ":" + this->varname;
    for(auto& val: this->assumed_values){
        res += ", " + this->type->to_string() + ":" + val->to_string();
    }
    res += ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    if(this->probability.has_value()){
        res += " #[probability(f64:" + std::to_string(this->probability.value()) + ")]";
    }
    return res;
}


ExpectNotRangeInst::ExpectNotRangeInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, IR::LiteralExprPtr min_value, IR::LiteralExprPtr max_value, 
                                       IR::TypeExprPtr type, std::optional<double> probability, bool unsigned_, std::optional<FastMathAttr> fast_math_attr):
                                       Inst(instruction_stmt, nullptr, fast_math_attr){
    this->min_value = min_value;
    this->max_value = max_value;
    this->type = type;
    this->varname = varname;
    this->probability = probability;
    this->unsigned_ = unsigned_;
}
std::string ExpectNotRangeInst::get_varname() const{
    return this->varname;
}
IR::LiteralExprPtr ExpectNotRangeInst::get_min_value() const{
    return this->min_value;
}
IR::LiteralExprPtr ExpectNotRangeInst::get_max_value() const{
    return this->max_value;
}
std::optional<double> ExpectNotRangeInst::get_probability() const{
    return this->probability;
}
IR::TypeExprPtr ExpectNotRangeInst::get_type() const{
    return this->type;
}
bool ExpectNotRangeInst::is_unsigned() const{
    return this->unsigned_;
}
InstType ExpectNotRangeInst::get_inst_type() const{
    return InstType::ExpectNotRangeInst;
}
std::string ExpectNotRangeInst::to_string() const{
    std::string res = ".expect_not_range(" + this->type->to_string() + ":" + this->varname + ", " + this->type->to_string() + ":" + this->min_value->to_string() + ", " +
                      this->type->to_string() + ":" + this->max_value->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    if(this->probability.has_value()){
        res += " #[probability(f64:" + std::to_string(this->probability.value()) + ")]";
    }
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}


// --------------------------Metadata and Machine Instructions-------------------------------
NopInst::NopInst(IR::InstructionStmtPtr instruction_stmt, std::uint8_t size, bool multi_byte):Inst(instruction_stmt, nullptr, std::nullopt){
    this->size = size;
    this->multi_byte = multi_byte;
}
std::uint8_t NopInst::get_size() const{
    return this->size;
}
bool NopInst::is_multi_byte() const{
    return this->multi_byte;
}
InstType NopInst::get_inst_type() const{
    return InstType::NopInst;
}
std::string NopInst::to_string() const{
    std::string res = ".nop(i8:" + std::to_string(this->size)+ ")";
    if(this->multi_byte){
        res += " #[multi_byte]";
    }
    return res;
}


AnnotationInst::AnnotationInst(IR::InstructionStmtPtr instruction_stmt, std::string message):Inst(instruction_stmt, nullptr, std::nullopt){
    this->message = message;
}
std::string AnnotationInst::get_message() const{
    return this->message;
}
InstType AnnotationInst::get_inst_type() const{
    return InstType::AnnotationInst;
}
std::string AnnotationInst::to_string() const{
    return ".annotation(str:\"" + this->message + "\")";
}


Endbr64Inst::Endbr64Inst(IR::InstructionStmtPtr instruction_stmt):Inst(instruction_stmt, nullptr, std::nullopt){}
InstType Endbr64Inst::get_inst_type() const{
    return InstType::Endbr64Inst;
}
std::string Endbr64Inst::to_string() const{
    return ".endbr64";
}


// --------------------------Pointer Provenance Instructions-------------------------------
LaunderInst::LaunderInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr ptr):Inst(instruction_stmt, destination, std::nullopt){
    this->ptr = ptr;
}
IR::LiteralExprPtr LaunderInst::get_ptr() const{
    return this->ptr;
}
InstType LaunderInst::get_inst_type() const{
    return InstType::LaunderInst;
}
std::string LaunderInst::to_string() const{
    return "let " + this->destination->to_string() + " = .launder(ptr:" + this->ptr->to_string() + ")";
}


StripInvariantGroupInst::StripInvariantGroupInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr ptr):Inst(instruction_stmt, destination, std::nullopt){
    this->ptr = ptr;
}
IR::LiteralExprPtr StripInvariantGroupInst::get_ptr() const{
    return this->ptr;
}
InstType StripInvariantGroupInst::get_inst_type() const{
    return InstType::StripInvariantGroupInst;
}
std::string StripInvariantGroupInst::to_string() const{
    return "let " + this->destination->to_string() + " = .strip_invariant(ptr:" + this->ptr->to_string() + ")";
}
}
}