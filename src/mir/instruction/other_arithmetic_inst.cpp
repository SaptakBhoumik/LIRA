#include "mir/instruction/other_arithmetic_inst.hpp"
#include "ast/ast.hpp"
#include <optional>

namespace LIRA {
namespace MIR {
// ---------------------------- Combined Quotient and Remainder instructions ---------------------------
DivModInst::DivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                 bool unsigned_, std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt, destination, fast_math_attr){
    this->lhs = lhs;
    this->rhs = rhs;
    this->unsigned_ = unsigned_;
}
std::string DivModInst::to_string_helper(const std::string op_name) const{
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
bool DivModInst::is_unsigned() const{
    return this->unsigned_;
}
IR::TypeExprPtr DivModInst::get_operand_type() const{
    auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(this->destination->get_type());
    return struct_type->get_fields()[0];
}
IR::LiteralExprPtr DivModInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr DivModInst::get_rhs() const{
    return this->rhs;
}
InstType DivModInst::get_inst_type() const{
    return InstType::DivModInst;
}


IntDivModInst::IntDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                             bool unsigned_)
                     :DivModInst(instruction_stmt, destination, lhs, rhs, unsigned_, std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntDivModInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntDivModInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVarient IntDivModInst::get_operand_type_varient() const{
    return TypeVarient::Int;
}
std::string IntDivModInst::to_string() const{
    return this->to_string_helper("int_divmod");
}


VecIntDivModInst::VecIntDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                bool unsigned_)
                                :DivModInst(instruction_stmt, destination, lhs, rhs, unsigned_, std::nullopt){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntDivModInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntDivModInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntDivModInst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntDivModInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVarient VecIntDivModInst::get_operand_type_varient() const{
    return TypeVarient::VecInt;
}
std::string VecIntDivModInst::to_string() const{
    return this->to_string_helper("vec_int_divmod");
}


FloatDivModInst::FloatDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                 FastMathAttr fast_math_attr)
                                 :DivModInst(instruction_stmt, destination, lhs, rhs, false, fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatDivModInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_operand_type());
}
std::size_t FloatDivModInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
bool FloatDivModInst::is_brain_float() const{
    return this->get_casted_operand_type()->is_brain_float();
}
TypeVarient FloatDivModInst::get_operand_type_varient() const{
    return TypeVarient::Float;
}
std::string FloatDivModInst::to_string() const{
    return this->to_string_helper("float_divmod");
}


VecFloatDivModInst::VecFloatDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                       FastMathAttr fast_math_attr)
                                       :DivModInst(instruction_stmt, destination, lhs, rhs, false, fast_math_attr){}
std::shared_ptr<IR::SIMDTypeExpr> VecFloatDivModInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatDivModInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecFloatDivModInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVarient VecFloatDivModInst::get_operand_type_varient() const{
    return TypeVarient::VecFloat;
}
std::string VecFloatDivModInst::to_string() const{
    return this->to_string_helper("vec_float_divmod");
}


WideningDivModInst::WideningDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr dividend_hi, IR::LiteralExprPtr dividend_lo,
                                                   IR::LiteralExprPtr divisor, bool unsigned_, bool exact)
                                                   :Inst(instruction_stmt, destination,std::nullopt){
    this->dividend_hi = dividend_hi;
    this->dividend_lo = dividend_lo;
    this->divisor = divisor;
    this->unsigned_ = unsigned_;
    this->exact = exact;
}
std::string WideningDivModInst::to_string_helper(const std::string op_name) const{
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
bool WideningDivModInst::is_unsigned() const{
    return this->unsigned_;
}
bool WideningDivModInst::is_exact() const{
    return this->exact;
}
IR::TypeExprPtr WideningDivModInst::get_operand_type() const{
    auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(this->destination->get_type());
    return struct_type->get_fields()[0];
}
IR::LiteralExprPtr WideningDivModInst::get_dividend_hi() const{
    return this->dividend_hi;
}
IR::LiteralExprPtr WideningDivModInst::get_dividend_lo() const{
    return this->dividend_lo;
}
IR::LiteralExprPtr WideningDivModInst::get_divisor() const{
    return this->divisor;
}
InstType WideningDivModInst::get_inst_type() const{
    return InstType::WideningDivModInst;
}


IntWideningDivModInst::IntWideningDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr dividend_hi, IR::LiteralExprPtr dividend_lo,
                                             IR::LiteralExprPtr divisor, bool unsigned_, bool exact)
                                             :WideningDivModInst(instruction_stmt, destination, dividend_hi, dividend_lo, divisor, unsigned_, exact){}
std::shared_ptr<IR::IntTypeExpr> IntWideningDivModInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntWideningDivModInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVarient IntWideningDivModInst::get_operand_type_varient() const{
    return TypeVarient::Int;
}
std::string IntWideningDivModInst::to_string() const{
    return this->to_string_helper("int_widening_divmod");
}


VecIntWideningDivModInst::VecIntWideningDivModInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr dividend_hi, IR::LiteralExprPtr dividend_lo,
                                                   IR::LiteralExprPtr divisor, bool unsigned_, bool exact)
                                                   :WideningDivModInst(instruction_stmt, destination, dividend_hi, dividend_lo, divisor, unsigned_, exact){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntWideningDivModInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntWideningDivModInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntWideningDivModInst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntWideningDivModInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVarient VecIntWideningDivModInst::get_operand_type_varient() const{
    return TypeVarient::VecInt;
}
std::string VecIntWideningDivModInst::to_string() const{
    return this->to_string_helper("vec_int_widening_divmod");
}
// ---------------------------- High-Half Arithmetic instructions ---------------------------
MulHiInst::MulHiInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
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


IntMulHiInst::IntMulHiInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                             bool unsigned_)
                             :MulHiInst(instruction_stmt, destination, lhs, rhs, unsigned_){}

std::shared_ptr<IR::IntTypeExpr> IntMulHiInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntMulHiInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVarient IntMulHiInst::get_operand_type_varient() const{
    return TypeVarient::Int;
}
std::string IntMulHiInst::to_string() const{
    return this->to_string_helper("int_mulhi");
}


VecIntMulHiInst::VecIntMulHiInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
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
TypeVarient VecIntMulHiInst::get_operand_type_varient() const{
    return TypeVarient::VecInt;
}
std::string VecIntMulHiInst::to_string() const{
    return this->to_string_helper("vec_int_mulhi");
}


// ---------------------------- Fixed-Point Arithmetic instructions ---------------------------
CTMulFixInst::CTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                           std::uint64_t scale, bool nuw, bool nsw, bool unsigned_, bool saturating, bool round)
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
std::string CTMulFixInst::to_string_helper(const std::string op_name) const{    
    std::string type_str = this->get_operand_type()->to_string();
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + type_str + ":" + this->lhs->to_string() + ", " 
                                                                                                    + type_str + ":" + this->rhs->to_string() + ", "
                                                                                                    + "i64:" + std::to_string(this->scale) + ")";
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
bool CTMulFixInst::is_unsigned() const{
    return this->unsigned_;
}
IR::TypeExprPtr CTMulFixInst::get_operand_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr CTMulFixInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr CTMulFixInst::get_rhs() const{
    return this->rhs;
}
std::uint64_t CTMulFixInst::get_scale() const{
    return this->scale;
}
InstType CTMulFixInst::get_inst_type() const{
    return InstType::CTMulFixInst;
}


IntCTMulFixInst::IntCTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                 std::uint64_t scale, bool nuw, bool nsw, bool unsigned_, bool saturating, bool round)
                                 :CTMulFixInst(instruction_stmt, destination, lhs, rhs, scale, nuw, nsw, unsigned_, saturating, round){}
std::shared_ptr<IR::IntTypeExpr> IntCTMulFixInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntCTMulFixInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVarient IntCTMulFixInst::get_operand_type_varient() const{
    return TypeVarient::Int;
}
std::string IntCTMulFixInst::to_string() const{
    return this->to_string_helper("int_ct_mulfix");
}


VecIntCTMulFixInst::VecIntCTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                       std::uint64_t scale, bool nuw, bool nsw, bool unsigned_, bool saturating, bool round)
                                       :CTMulFixInst(instruction_stmt, destination, lhs, rhs, scale, nuw, nsw, unsigned_, saturating, round){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntCTMulFixInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntCTMulFixInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntCTMulFixInst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntCTMulFixInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVarient VecIntCTMulFixInst::get_operand_type_varient() const{
    return TypeVarient::VecInt;
}
std::string VecIntCTMulFixInst::to_string() const{
    return this->to_string_helper("vec_int_ct_mulfix");
}

                                       
RTMulFixInst::RTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
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
std::string RTMulFixInst::to_string_helper(const std::string op_name) const{    
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
bool RTMulFixInst::is_unsigned() const{
    return this->unsigned_;
}
IR::TypeExprPtr RTMulFixInst::get_operand_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr RTMulFixInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr RTMulFixInst::get_rhs() const{
    return this->rhs;
}
IR::LiteralExprPtr RTMulFixInst::get_scale() const{
    return this->scale;
}
InstType RTMulFixInst::get_inst_type() const{
    return InstType::RTMulFixInst;
}


IntRTMulFixInst::IntRTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                 IR::LiteralExprPtr scale, bool nuw, bool nsw, bool unsigned_, bool saturating, bool round)
                                 :RTMulFixInst(instruction_stmt, destination, lhs, rhs, scale, nuw, nsw, unsigned_, saturating, round){}
std::shared_ptr<IR::IntTypeExpr> IntRTMulFixInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntRTMulFixInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVarient IntRTMulFixInst::get_operand_type_varient() const{
    return TypeVarient::Int;
}
std::string IntRTMulFixInst::to_string() const{
    return this->to_string_helper("int_rt_mulfix");
}


VecIntRTMulFixInst::VecIntRTMulFixInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                       IR::LiteralExprPtr scale, bool nuw, bool nsw, bool unsigned_, bool saturating, bool round)
                                       :RTMulFixInst(instruction_stmt, destination, lhs, rhs, scale, nuw, nsw, unsigned_, saturating, round){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntRTMulFixInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntRTMulFixInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntRTMulFixInst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntRTMulFixInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVarient VecIntRTMulFixInst::get_operand_type_varient() const{
    return TypeVarient::VecInt;
}
std::string VecIntRTMulFixInst::to_string() const{
    return this->to_string_helper("vec_int_rt_mulfix");
}
}
}