#include "mir/instruction/other_arithmetic_inst.hpp"
#include "ast/ast.hpp"
#include <optional>

namespace LIRA {
namespace MIR {
// ---------------------------- Combined Quotient and Remainder instructions ---------------------------
DivmodInst::DivmodInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                 bool unsigned_, std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt, destination, fast_math_attr){
    this->lhs = lhs;
    this->rhs = rhs;
    this->unsigned_ = unsigned_;
}
std::string DivmodInst::to_string_helper(const std::string op_name) const{
    std::string type_str = this->get_operand_type()->to_string();
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + type_str + ":" + this->lhs->to_string() + ", " + type_str + ":" + this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    if(this->fast_math_attr.has_value()){
        res+= " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
bool DivmodInst::is_unsigned() const{
    return this->unsigned_;
}
IR::TypeExprPtr DivmodInst::get_operand_type() const{
    auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(this->destination->get_type());
    return struct_type->get_fields()[0];
}
IR::LiteralExprPtr DivmodInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr DivmodInst::get_rhs() const{
    return this->rhs;
}
InstType DivmodInst::get_inst_type() const{
    return InstType::DivmodInst;
}


IntDivmodInst::IntDivmodInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                             bool unsigned_)
                     :DivmodInst(instruction_stmt, destination, lhs, rhs, unsigned_, std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntDivmodInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntDivmodInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVariant IntDivmodInst::get_operand_type_variant() const{
    return TypeVariant::Int;
}
std::string IntDivmodInst::to_string() const{
    return this->to_string_helper("int_divmod");
}


VecIntDivmodInst::VecIntDivmodInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                bool unsigned_)
                                :DivmodInst(instruction_stmt, destination, lhs, rhs, unsigned_, std::nullopt){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntDivmodInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntDivmodInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntDivmodInst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntDivmodInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVariant VecIntDivmodInst::get_operand_type_variant() const{
    return TypeVariant::VecInt;
}
std::string VecIntDivmodInst::to_string() const{
    return this->to_string_helper("vec_int_divmod");
}


FloatDivmodInst::FloatDivmodInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                 FastMathAttr fast_math_attr)
                                 :DivmodInst(instruction_stmt, destination, lhs, rhs, false, fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatDivmodInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_operand_type());
}
std::size_t FloatDivmodInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
bool FloatDivmodInst::is_brain_float() const{
    return this->get_casted_operand_type()->is_brain_float();
}
TypeVariant FloatDivmodInst::get_operand_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatDivmodInst::to_string() const{
    return this->to_string_helper("float_divmod");
}


VecFloatDivmodInst::VecFloatDivmodInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                       FastMathAttr fast_math_attr)
                                       :DivmodInst(instruction_stmt, destination, lhs, rhs, false, fast_math_attr){}
std::shared_ptr<IR::SIMDTypeExpr> VecFloatDivmodInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatDivmodInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecFloatDivmodInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVariant VecFloatDivmodInst::get_operand_type_variant() const{
    return TypeVariant::VecFloat;
}
std::string VecFloatDivmodInst::to_string() const{
    return this->to_string_helper("vec_float_divmod");
}


WideningDivmodInst::WideningDivmodInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr dividend_hi, IR::LiteralExprPtr dividend_lo,
                                                   IR::LiteralExprPtr divisor, bool unsigned_, bool exact)
                                                   :Inst(instruction_stmt, destination,std::nullopt){
    this->dividend_hi = dividend_hi;
    this->dividend_lo = dividend_lo;
    this->divisor = divisor;
    this->unsigned_ = unsigned_;
    this->exact = exact;
}
std::string WideningDivmodInst::to_string_helper(const std::string op_name) const{
    std::string type_str = this->get_operand_type()->to_string();
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->dividend_hi->to_string() + ", " 
                                                                                                    + this->dividend_lo->to_string() + ", "
                                                                                                    + this->divisor->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    if(this->exact){
        res += " #[exact]";
    }
    return res;
}
bool WideningDivmodInst::is_unsigned() const{
    return this->unsigned_;
}
bool WideningDivmodInst::is_exact() const{
    return this->exact;
}
IR::TypeExprPtr WideningDivmodInst::get_operand_type() const{
    auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(this->destination->get_type());
    return struct_type->get_fields()[0];
}
IR::LiteralExprPtr WideningDivmodInst::get_dividend_hi() const{
    return this->dividend_hi;
}
IR::LiteralExprPtr WideningDivmodInst::get_dividend_lo() const{
    return this->dividend_lo;
}
IR::LiteralExprPtr WideningDivmodInst::get_divisor() const{
    return this->divisor;
}
InstType WideningDivmodInst::get_inst_type() const{
    return InstType::WideningDivmodInst;
}


IntWideningDivmodInst::IntWideningDivmodInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr dividend_hi, IR::LiteralExprPtr dividend_lo,
                                             IR::LiteralExprPtr divisor, bool unsigned_, bool exact)
                                             :WideningDivmodInst(instruction_stmt, destination, dividend_hi, dividend_lo, divisor, unsigned_, exact){}
std::shared_ptr<IR::IntTypeExpr> IntWideningDivmodInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntWideningDivmodInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVariant IntWideningDivmodInst::get_operand_type_variant() const{
    return TypeVariant::Int;
}
std::string IntWideningDivmodInst::to_string() const{
    return this->to_string_helper("int_widening_divmod");
}


VecIntWideningDivmodInst::VecIntWideningDivmodInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr dividend_hi, IR::LiteralExprPtr dividend_lo,
                                                   IR::LiteralExprPtr divisor, bool unsigned_, bool exact)
                                                   :WideningDivmodInst(instruction_stmt, destination, dividend_hi, dividend_lo, divisor, unsigned_, exact){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntWideningDivmodInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntWideningDivmodInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntWideningDivmodInst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntWideningDivmodInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVariant VecIntWideningDivmodInst::get_operand_type_variant() const{
    return TypeVariant::VecInt;
}
std::string VecIntWideningDivmodInst::to_string() const{
    return this->to_string_helper("vec_int_widening_divmod");
}
// ---------------------------- High-Half Arithmetic instructions ---------------------------
MulHiInst::MulHiInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                     bool unsigned_):Inst(instruction_stmt, destination,std::nullopt){
    this->lhs = lhs;
    this->rhs = rhs;
    this->unsigned_ = unsigned_;
}
std::string MulHiInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}
bool MulHiInst::is_unsigned() const{
    return this->unsigned_;
}
IR::TypeExprPtr MulHiInst::get_operand_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr MulHiInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr MulHiInst::get_rhs() const{
    return this->rhs;
}
InstType MulHiInst::get_inst_type() const{
    return InstType::MulHiInst;
}


IntMulHiInst::IntMulHiInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                             bool unsigned_)
                             :MulHiInst(instruction_stmt, destination, lhs, rhs, unsigned_){}

std::shared_ptr<IR::IntTypeExpr> IntMulHiInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntMulHiInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVariant IntMulHiInst::get_operand_type_variant() const{
    return TypeVariant::Int;
}
std::string IntMulHiInst::to_string() const{
    return this->to_string_helper("int_mulhi");
}


VecIntMulHiInst::VecIntMulHiInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                 bool unsigned_)
                                 :MulHiInst(instruction_stmt, destination, lhs, rhs, unsigned_){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntMulHiInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntMulHiInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntMulHiInst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntMulHiInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVariant VecIntMulHiInst::get_operand_type_variant() const{
    return TypeVariant::VecInt;
}
std::string VecIntMulHiInst::to_string() const{
    return this->to_string_helper("vec_int_mulhi");
}


// ---------------------------- Fixed-Point Arithmetic instructions ---------------------------
MulFixInst::MulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                       IR::LiteralExprPtr scale, bool nuw, bool nsw, bool unsigned_, bool saturating, bool round)
                       :Inst(instruction_stmt, destination,std::nullopt){
    this->lhs = lhs;
    this->rhs = rhs;
    this->scale = scale;

    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
    this->round = round;
}
std::string MulFixInst::to_string_helper(const std::string op_name) const{    
    std::string type_str = this->get_operand_type()->to_string();
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + type_str + ":" + this->lhs->to_string() + ", " 
                                                                                                    + type_str + ":" + this->rhs->to_string() + ", "
                                                                                                    + "i64:" + this->scale->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    if(this->saturating){
        res += " #[saturating]";
    }
    if(this->round){
        res += " #[round]";
    }
    return res;
}
bool MulFixInst::is_unsigned() const{
    return this->unsigned_;
}
IR::TypeExprPtr MulFixInst::get_operand_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr MulFixInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr MulFixInst::get_rhs() const{
    return this->rhs;
}
IR::LiteralExprPtr MulFixInst::get_scale() const{
    return this->scale;
}
InstType MulFixInst::get_inst_type() const{
    return InstType::MulFixInst;
}


IntMulFixInst::IntMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                             IR::LiteralExprPtr scale, bool nuw, bool nsw, bool unsigned_, bool saturating, bool round)
                             :MulFixInst(instruction_stmt, destination, lhs, rhs, scale, nuw, nsw, unsigned_, saturating, round){}
std::shared_ptr<IR::IntTypeExpr> IntMulFixInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntMulFixInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVariant IntMulFixInst::get_operand_type_variant() const{
    return TypeVariant::Int;
}
std::string IntMulFixInst::to_string() const{
    return this->to_string_helper("int_mulfix");
}


VecIntMulFixInst::VecIntMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                   IR::LiteralExprPtr scale, bool nuw, bool nsw, bool unsigned_, bool saturating, bool round)
                                   :MulFixInst(instruction_stmt, destination, lhs, rhs, scale, nuw, nsw, unsigned_, saturating, round){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntMulFixInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntMulFixInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntMulFixInst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntMulFixInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVariant VecIntMulFixInst::get_operand_type_variant() const{
    return TypeVariant::VecInt;
}
std::string VecIntMulFixInst::to_string() const{
    return this->to_string_helper("vec_int_mulfix");
}
}
}