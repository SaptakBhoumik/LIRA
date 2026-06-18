#include "mir/instruction/widening_bin_inst.hpp"
#include <memory>

namespace LIRA {
namespace MIR {
WideningBinaryInst::WideningBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                       IR::TypeExprPtr input_type, std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt, destination, fast_math_attr){
    this->lhs = lhs;
    this->rhs = rhs;
    this->input_type = input_type;
}
IR::TypeExprPtr WideningBinaryInst::get_input_type() const {
    return input_type;
}
IR::TypeExprPtr WideningBinaryInst::get_result_type() const {
    return destination->get_type();
}
IR::LiteralExprPtr WideningBinaryInst::get_lhs() const {
    return lhs;
}
IR::LiteralExprPtr WideningBinaryInst::get_rhs() const {
    return rhs;
}
InstType WideningBinaryInst::get_inst_type() const {
    return InstType::WideningBinaryInst;
}


// ---------------------------- Integer Widening Binary operations ---------------------------
IntWideningBinaryInst::IntWideningBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                             IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_)
                                             :WideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
}
std::string IntWideningBinaryInst::to_string_helper(const std::string op_name) const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}
bool IntWideningBinaryInst::is_nuw() const {
    return this->nuw;
}
bool IntWideningBinaryInst::is_nsw() const {
    return this->nsw;
}
bool IntWideningBinaryInst::is_unsigned() const {
    return this->unsigned_;
}
std::shared_ptr<IR::IntTypeExpr> IntWideningBinaryInst::get_casted_input_type() const {
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->input_type);
}
std::shared_ptr<IR::IntTypeExpr> IntWideningBinaryInst::get_casted_result_type() const {
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
}
std::size_t IntWideningBinaryInst::get_input_bitwidth() const {
    return this->get_casted_input_type()->get_bits();
}
std::size_t IntWideningBinaryInst::get_result_bitwidth() const {
    return this->get_casted_result_type()->get_bits();
}
InstOperandTypeVarient IntWideningBinaryInst::get_type_varient() const {
    return InstOperandTypeVarient::Int;
}


IntWideningAddInst::IntWideningAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_)
                            :IntWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, nuw, nsw, unsigned_){}
WideningBinaryInst::OpType IntWideningAddInst::get_op_type() const{
    return OpType::WIDENING_ADD;
}
std::string IntWideningAddInst::to_string() const{
    return this->to_string_helper("int_widening_add");
}


IntWideningSubInst::IntWideningSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_)
                            :IntWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, nuw, nsw, unsigned_){}

WideningBinaryInst::OpType IntWideningSubInst::get_op_type() const{
    return OpType::WIDENING_SUB;
}
std::string IntWideningSubInst::to_string() const{
    return this->to_string_helper("int_widening_sub");
}


IntWideningMulInst::IntWideningMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_)
                            :IntWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, nuw, nsw, unsigned_){}
WideningBinaryInst::OpType IntWideningMulInst::get_op_type() const{
    return OpType::WIDENING_MUL;
}
std::string IntWideningMulInst::to_string() const{
    return this->to_string_helper("int_widening_mul");
}


// ---------------------------- Integer Widening Binary operations ---------------------------
VecIntWideningBinaryInst::VecIntWideningBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                             IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_)
                                             :WideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
}
std::string VecIntWideningBinaryInst::to_string_helper(const std::string op_name) const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}
bool VecIntWideningBinaryInst::is_nuw() const {
    return this->nuw;
}
bool VecIntWideningBinaryInst::is_nsw() const {
    return this->nsw;
}
bool VecIntWideningBinaryInst::is_unsigned() const {
    return this->unsigned_;
}
std::shared_ptr<IR::SIMDTypeExpr> VecIntWideningBinaryInst::get_casted_input_type() const {
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_type);
}
std::shared_ptr<IR::SIMDTypeExpr> VecIntWideningBinaryInst::get_casted_result_type() const {
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::size_t VecIntWideningBinaryInst::get_input_base_bitwidth() const {
    auto simd_input_type = this->get_casted_input_type();
    auto int_input_type = std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_input_type->get_basetype());
    return int_input_type->get_bits();
}
std::size_t VecIntWideningBinaryInst::get_result_base_bitwidth() const {
    auto simd_result_type = this->get_casted_result_type();
    auto int_result_type = std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_result_type->get_basetype());
    return int_result_type->get_bits();
}
std::size_t VecIntWideningBinaryInst::get_num_elements() const {
    return this->get_casted_input_type()->get_size();
}
InstOperandTypeVarient VecIntWideningBinaryInst::get_type_varient() const {
    return InstOperandTypeVarient::VecInt;
}


VecIntWideningAddInst::VecIntWideningAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_)
                            :VecIntWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, nuw, nsw, unsigned_){}
WideningBinaryInst::OpType VecIntWideningAddInst::get_op_type() const{
    return OpType::WIDENING_ADD;
}
std::string VecIntWideningAddInst::to_string() const{
    return this->to_string_helper("vec_int_widening_add");
}


VecIntWideningSubInst::VecIntWideningSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_)
                            :VecIntWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, nuw, nsw, unsigned_){}
WideningBinaryInst::OpType VecIntWideningSubInst::get_op_type() const{
    return OpType::WIDENING_SUB;
}
std::string VecIntWideningSubInst::to_string() const{
    return this->to_string_helper("vec_int_widening_sub");
}


VecIntWideningMulInst::VecIntWideningMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, bool nuw, bool nsw, bool unsigned_)
                            :VecIntWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, nuw, nsw, unsigned_){}
WideningBinaryInst::OpType VecIntWideningMulInst::get_op_type() const{
    return OpType::WIDENING_MUL;
}
std::string VecIntWideningMulInst::to_string() const{
    return this->to_string_helper("vec_int_widening_mul");
}


// ---------------------------- Float Widening Binary operations ---------------------------
FloatWideningBinaryInst::FloatWideningBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                                                 IR::LiteralExprPtr rhs, IR::TypeExprPtr input_type, FastMathAttr fast_math_attr)
                                                 :WideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, fast_math_attr){}
std::string FloatWideningBinaryInst::to_string_helper(const std::string op_name) const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res+= " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
std::shared_ptr<IR::FloatTypeExpr> FloatWideningBinaryInst::get_casted_input_type() const {
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->input_type);
}
std::shared_ptr<IR::FloatTypeExpr> FloatWideningBinaryInst::get_casted_result_type() const {
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->destination->get_type());
}
std::size_t FloatWideningBinaryInst::get_input_bitwidth() const {
    return this->get_casted_input_type()->get_bits();
}
std::size_t FloatWideningBinaryInst::get_result_bitwidth() const {
    return this->get_casted_result_type()->get_bits();
}
bool FloatWideningBinaryInst::is_input_brain_float() const {
    return this->get_casted_input_type()->is_brain_float();
}
bool FloatWideningBinaryInst::is_result_brain_float() const {
    return this->get_casted_result_type()->is_brain_float();
}
InstOperandTypeVarient FloatWideningBinaryInst::get_type_varient() const {
    return InstOperandTypeVarient::Float;
}   


FloatWideningAddInst::FloatWideningAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, FastMathAttr fast_math_attr)
                            :FloatWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, fast_math_attr){}
WideningBinaryInst::OpType FloatWideningAddInst::get_op_type() const{
    return OpType::WIDENING_ADD;
}
std::string FloatWideningAddInst::to_string() const{
    return this->to_string_helper("float_widening_add");
}


FloatWideningSubInst::FloatWideningSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, FastMathAttr fast_math_attr)
                            :FloatWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, fast_math_attr){}
WideningBinaryInst::OpType FloatWideningSubInst::get_op_type() const{
    return OpType::WIDENING_SUB;
}
std::string FloatWideningSubInst::to_string() const{
    return this->to_string_helper("float_widening_sub");
}


FloatWideningMulInst::FloatWideningMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, FastMathAttr fast_math_attr)
                            :FloatWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, fast_math_attr){}
WideningBinaryInst::OpType FloatWideningMulInst::get_op_type() const{
    return OpType::WIDENING_MUL;
}
std::string FloatWideningMulInst::to_string() const{
    return this->to_string_helper("float_widening_mul");
}


// ---------------------------- Vector Float Widening Binary operations ---------------------------
VecFloatWideningBinaryInst::VecFloatWideningBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs,
                                                 IR::LiteralExprPtr rhs, IR::TypeExprPtr input_type, FastMathAttr fast_math_attr)
                                                 :WideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, fast_math_attr){}
std::string VecFloatWideningBinaryInst::to_string_helper(const std::string op_name) const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res+= " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
std::shared_ptr<IR::SIMDTypeExpr> VecFloatWideningBinaryInst::get_casted_input_type() const {
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_type);
}
std::shared_ptr<IR::SIMDTypeExpr> VecFloatWideningBinaryInst::get_casted_result_type() const {
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatWideningBinaryInst::get_casted_input_basetype() const {
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_casted_input_type()->get_basetype());
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatWideningBinaryInst::get_casted_result_basetype() const {
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_casted_result_type()->get_basetype());
}
InstOperandTypeVarient VecFloatWideningBinaryInst::get_type_varient() const {
    return InstOperandTypeVarient::VecFloat;
}   


VecFloatWideningAddInst::VecFloatWideningAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, FastMathAttr fast_math_attr)
                            :VecFloatWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, fast_math_attr){}
WideningBinaryInst::OpType VecFloatWideningAddInst::get_op_type() const{
    return OpType::WIDENING_ADD;
}
std::string VecFloatWideningAddInst::to_string() const{
    return this->to_string_helper("vec_float_widening_add");
}


VecFloatWideningSubInst::VecFloatWideningSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, FastMathAttr fast_math_attr)
                            :VecFloatWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, fast_math_attr){}
WideningBinaryInst::OpType VecFloatWideningSubInst::get_op_type() const{
    return OpType::WIDENING_SUB;
}
std::string VecFloatWideningSubInst::to_string() const{
    return this->to_string_helper("vec_float_widening_sub");
}


VecFloatWideningMulInst::VecFloatWideningMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            IR::TypeExprPtr input_type, FastMathAttr fast_math_attr)
                            :VecFloatWideningBinaryInst(instruction_stmt, destination, lhs, rhs, input_type, fast_math_attr){}
WideningBinaryInst::OpType VecFloatWideningMulInst::get_op_type() const{
    return OpType::WIDENING_MUL;
}
std::string VecFloatWideningMulInst::to_string() const{
    return this->to_string_helper("vec_float_widening_mul");
}
}
}