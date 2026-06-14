#include "mir/instruction/arithmetic_bin_inst.hpp"

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
IntArithmeticBinaryInst::IntArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                                bool nuw, bool nsw, bool unsigned_, bool saturating, bool floor, bool exact):
                                                ArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
    this->floor = floor;
    this->exact = exact;
}
std::string IntArithmeticBinaryInst::to_string_helper(const std::string op_name) const{
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
    if(this->saturating){
        res += " #[saturating]";
    }
    if(this->floor){
        res += " #[floor]";
    }
    if(this->exact){
        res += " #[exact]";
    }
    return res;
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
bool IntArithmeticBinaryInst::is_saturating() const{
    return this->saturating;
}
bool IntArithmeticBinaryInst::is_floor() const{
    return this->floor;
}
bool IntArithmeticBinaryInst::is_exact() const{
    return this->exact;
}
std::shared_ptr<IR::IntTypeExpr> IntArithmeticBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
}
std::size_t IntArithmeticBinaryInst::get_bitwidth() const{
    auto int_type = this->get_casted_operand_type();
    return int_type->get_bits();
}
InstOperandTypeVarient IntArithmeticBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::Int;
}


IntAddInst::IntAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw, bool unsigned_, bool saturating)
                        :IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, unsigned_, saturating, false, false){}
ArithmeticBinaryInst::OpType IntAddInst::get_op_type() const{
    return OpType::ADD;
}
std::string IntAddInst::to_string() const{
    return this->to_string_helper("int_add");
}


IntSubInst::IntSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw, bool unsigned_, bool saturating)
                        :IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, unsigned_, saturating, false, false){}
ArithmeticBinaryInst::OpType IntSubInst::get_op_type() const{
    return OpType::SUB;
}
std::string IntSubInst::to_string() const{
    return this->to_string_helper("int_sub");
}


IntMulInst::IntMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw, bool unsigned_, bool saturating)
                        :IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, unsigned_, saturating, false, false){}
ArithmeticBinaryInst::OpType IntMulInst::get_op_type() const{
    return OpType::MUL;
}
std::string IntMulInst::to_string() const{
    return this->to_string_helper("int_mul");
}


IntDivInst::IntDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_, bool exact)
                        :IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, false, false, exact){}
ArithmeticBinaryInst::OpType IntDivInst::get_op_type() const{
    return OpType::DIV;
}
std::string IntDivInst::to_string() const{
    return this->to_string_helper("int_div");
}


IntRemInst::IntRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_)
                        :IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, false, false, false){}
ArithmeticBinaryInst::OpType IntRemInst::get_op_type() const{
    return OpType::REM;
}
std::string IntRemInst::to_string() const{
    return this->to_string_helper("int_rem");
}


IntCopySignInst::IntCopySignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false, false, false){}
ArithmeticBinaryInst::OpType IntCopySignInst::get_op_type() const{
    return OpType::COPYSIGN;
}
std::string IntCopySignInst::to_string() const{
    return this->to_string_helper("int_copysign");
}


IntMinInst::IntMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_)
                        :IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, false, false, false){}
ArithmeticBinaryInst::OpType IntMinInst::get_op_type() const{
    return OpType::MIN;
}
std::string IntMinInst::to_string() const{
    return this->to_string_helper("int_min");
}


IntMaxInst::IntMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_)
                        :IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, false, false, false){}
ArithmeticBinaryInst::OpType IntMaxInst::get_op_type() const{
    return OpType::MAX;
}
std::string IntMaxInst::to_string() const{
    return this->to_string_helper("int_max");
}


IntAvgInst::IntAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool nuw, bool nsw ,bool unsigned_, bool floor)
                        :IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, unsigned_, false, floor, false){}
ArithmeticBinaryInst::OpType IntAvgInst::get_op_type() const{
    return OpType::AVG;
}
std::string IntAvgInst::to_string() const{
    return this->to_string_helper("int_avg");
}

// ----------------------------- Vector integer binary operations ---------------------------
VecIntArithmeticBinaryInst::VecIntArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                                        bool nuw, bool nsw, bool unsigned_, bool saturating, bool floor, bool exact)
                                                        :ArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
    this->floor = floor;
    this->exact = exact;
}
std::string VecIntArithmeticBinaryInst::to_string_helper(const std::string op_name) const{
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
    if(this->saturating){
        res += " #[saturating]";
    }
    if(this->floor){
        res += " #[floor]";
    }
    if(this->exact){
        res += " #[exact]";
    }
    return res;
}
bool VecIntArithmeticBinaryInst::is_nuw() const{
    return this->nuw;
}
bool VecIntArithmeticBinaryInst::is_nsw() const{
    return this->nsw;
}
bool VecIntArithmeticBinaryInst::is_unsigned() const{
    return this->unsigned_;
}
bool VecIntArithmeticBinaryInst::is_saturating() const{
    return this->saturating;
}
bool VecIntArithmeticBinaryInst::is_floor() const{
    return this->floor;
}
bool VecIntArithmeticBinaryInst::is_exact() const{
    return this->exact;
}
std::shared_ptr<IR::SIMDTypeExpr> VecIntArithmeticBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::size_t VecIntArithmeticBinaryInst::get_basetype_width() const{
    auto basetype = this->get_casted_operand_type()->get_basetype();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(basetype)->get_bits();
}
std::size_t VecIntArithmeticBinaryInst::get_num_elements() const{
    return this->get_casted_operand_type()->get_size();
}   
InstOperandTypeVarient VecIntArithmeticBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::VecInt;
}


VecIntAddInst::VecIntAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw, bool unsigned_, bool saturating)
                        :VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, unsigned_, saturating, false, false){}
ArithmeticBinaryInst::OpType VecIntAddInst::get_op_type() const{
    return OpType::ADD;
}
std::string VecIntAddInst::to_string() const{
    return this->to_string_helper("vec_int_add");
}


VecIntSubInst::VecIntSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw, bool unsigned_, bool saturating)
                        :VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, unsigned_, saturating, false, false){}
ArithmeticBinaryInst::OpType VecIntSubInst::get_op_type() const{
    return OpType::SUB;
}
std::string VecIntSubInst::to_string() const{
    return this->to_string_helper("vec_int_sub");
}


VecIntMulInst::VecIntMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw, bool unsigned_, bool saturating)
                        :VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, unsigned_, saturating, false, false){}
ArithmeticBinaryInst::OpType VecIntMulInst::get_op_type() const{
    return OpType::MUL;
}
std::string VecIntMulInst::to_string() const{
    return this->to_string_helper("vec_int_mul");
}


VecIntDivInst::VecIntDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_, bool exact)
                        :VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, false, false, exact){}
ArithmeticBinaryInst::OpType VecIntDivInst::get_op_type() const{
    return OpType::DIV;
}
std::string VecIntDivInst::to_string() const{
    return this->to_string_helper("vec_int_div");
}


VecIntRemInst::VecIntRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_)
                        :VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, false, false, false){}
ArithmeticBinaryInst::OpType VecIntRemInst::get_op_type() const{
    return OpType::REM;
}
std::string VecIntRemInst::to_string() const{
    return this->to_string_helper("vec_int_rem");
}


VecIntCopySignInst::VecIntCopySignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false, false, false){}
ArithmeticBinaryInst::OpType VecIntCopySignInst::get_op_type() const{
    return OpType::COPYSIGN;
}
std::string VecIntCopySignInst::to_string() const{
    return this->to_string_helper("vec_int_copysign");
}


VecIntMinInst::VecIntMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_)
                        :VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, false, false, false){}
ArithmeticBinaryInst::OpType VecIntMinInst::get_op_type() const{
    return OpType::MIN;
}
std::string VecIntMinInst::to_string() const{
    return this->to_string_helper("vec_int_min");
}


VecIntMaxInst::VecIntMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_)
                        :VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, false, false, false){}
ArithmeticBinaryInst::OpType VecIntMaxInst::get_op_type() const{
    return OpType::MAX;
}
std::string VecIntMaxInst::to_string() const{
    return this->to_string_helper("vec_int_max");
}


VecIntAvgInst::VecIntAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool nuw, bool nsw ,bool unsigned_, bool floor)
                        :VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, unsigned_, false, floor, false){}
ArithmeticBinaryInst::OpType VecIntAvgInst::get_op_type() const{
    return OpType::AVG;
}
std::string VecIntAvgInst::to_string() const{
    return this->to_string_helper("vec_int_avg");
}


// ---------------------------- Float binary operations ---------------------------
FloatArithmeticBinaryInst::FloatArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                FastMathAttr fast_math_attr,bool ieee754_2019, bool unordered):ArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs){
    this->fast_math_attr = fast_math_attr;
    this->ieee754_2019 = ieee754_2019;
    this->unordered = unordered;
}
std::string FloatArithmeticBinaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res+= " " + this->fast_math_attr.to_string();
    if(this->ieee754_2019){
        res += " #[ieee754_2019]";
    }
    if(this->unordered){
        res += " #[unordered]";
    }
    return res;
}
FastMathAttr FloatArithmeticBinaryInst::get_fast_math_attr() const{
    return this->fast_math_attr;
}
bool FloatArithmeticBinaryInst::is_ieee754_2019() const{
    return this->ieee754_2019;
}
bool FloatArithmeticBinaryInst::is_unordered() const{
    return this->unordered;
}
std::shared_ptr<IR::FloatTypeExpr> FloatArithmeticBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->destination->get_type());
}
std::size_t FloatArithmeticBinaryInst::get_bitwidth() const{
    auto float_type = this->get_casted_operand_type();
    return float_type->get_bits();
}
bool FloatArithmeticBinaryInst::is_brain_float() const{
    auto float_type = this->get_casted_operand_type();
    return float_type->is_brain_float();
}
InstOperandTypeVarient FloatArithmeticBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::Float;
}


FloatAddInst::FloatAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                            FastMathAttr fast_math_attr)
                            :FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr,false,false){}
ArithmeticBinaryInst::OpType FloatAddInst::get_op_type() const{
    return OpType::ADD;
}
std::string FloatAddInst::to_string() const{
    return this->to_string_helper("float_add");
}


FloatSubInst::FloatSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                            FastMathAttr fast_math_attr)
                            :FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr,false,false){}
ArithmeticBinaryInst::OpType FloatSubInst::get_op_type() const{
    return OpType::SUB;
}
std::string FloatSubInst::to_string() const{
    return this->to_string_helper("float_sub");
}


FloatMulInst::FloatMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            FastMathAttr fast_math_attr)
                            :FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType FloatMulInst::get_op_type() const{
    return OpType::MUL;
}
std::string FloatMulInst::to_string() const{
    return this->to_string_helper("float_mul");
}


FloatDivInst::FloatDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                FastMathAttr fast_math_attr)
                                :FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType FloatDivInst::get_op_type() const{
    return OpType::DIV;
}
std::string FloatDivInst::to_string() const{
    return this->to_string_helper("float_div");
}


FloatRemInst::FloatRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            FastMathAttr fast_math_attr)
                            :FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType FloatRemInst::get_op_type() const{
    return OpType::REM;
}
std::string FloatRemInst::to_string() const{
    return this->to_string_helper("float_rem");
}


FloatCopySignInst::FloatCopySignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                        FastMathAttr fast_math_attr)
                                        :FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType FloatCopySignInst::get_op_type() const{
    return OpType::COPYSIGN;
}
std::string FloatCopySignInst::to_string() const{
    return this->to_string_helper("float_copysign");
}


FloatMinInst::FloatMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                            :FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, ieee754_2019, unordered){}
ArithmeticBinaryInst::OpType FloatMinInst::get_op_type() const{
    return OpType::MIN;
}
std::string FloatMinInst::to_string() const{
    return this->to_string_helper("float_min");
}


FloatMaxInst::FloatMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                            :FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, ieee754_2019, unordered){}
ArithmeticBinaryInst::OpType FloatMaxInst::get_op_type() const{
    return OpType::MAX;
}
std::string FloatMaxInst::to_string() const{
    return this->to_string_helper("float_max");
}       


FloatAvgInst::FloatAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            FastMathAttr fast_math_attr)
                            :FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType FloatAvgInst::get_op_type() const{
    return OpType::AVG;
}
std::string FloatAvgInst::to_string() const{
    return this->to_string_helper("float_avg");
}
// ---------------------------- Vector Float binary operations ---------------------------
VecFloatArithmeticBinaryInst::VecFloatArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                                            FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                                                            :ArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs){
    this->fast_math_attr = fast_math_attr;
    this->ieee754_2019 = ieee754_2019;
    this->unordered = unordered;
}
FastMathAttr VecFloatArithmeticBinaryInst::get_fast_math_attr() const{
    return this->fast_math_attr;
}
std::string VecFloatArithmeticBinaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res+= " " + this->fast_math_attr.to_string();
    if(this->ieee754_2019){
        res += " #[ieee754_2019]";
    }
    if(this->unordered){
        res += " #[unordered]";
    }
    return res;
}
bool VecFloatArithmeticBinaryInst::is_ieee754_2019() const{
    return this->ieee754_2019;
}
bool VecFloatArithmeticBinaryInst::is_unordered() const{
    return this->unordered;
}
std::shared_ptr<IR::SIMDTypeExpr> VecFloatArithmeticBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatArithmeticBinaryInst::get_basetype() const{
    auto simd_type = this->get_casted_operand_type();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(simd_type->get_basetype());
}
std::size_t VecFloatArithmeticBinaryInst::get_num_elements() const{
    return this->get_casted_operand_type()->get_size();
}
InstOperandTypeVarient VecFloatArithmeticBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::VecFloat;
}


VecFloatAddInst::VecFloatAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                            FastMathAttr fast_math_attr)
                            :VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType VecFloatAddInst::get_op_type() const{
    return OpType::ADD;
}
std::string VecFloatAddInst::to_string() const{
    return this->to_string_helper("vec_float_add");
}


VecFloatSubInst::VecFloatSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                            FastMathAttr fast_math_attr)
                            :VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType VecFloatSubInst::get_op_type() const{
    return OpType::SUB;
}
std::string VecFloatSubInst::to_string() const{
    return this->to_string_helper("vec_float_sub");
}


VecFloatMulInst::VecFloatMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            FastMathAttr fast_math_attr)
                            :VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType VecFloatMulInst::get_op_type() const{
    return OpType::MUL;
}
std::string VecFloatMulInst::to_string() const{
    return this->to_string_helper("vec_float_mul");
}


VecFloatDivInst::VecFloatDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                FastMathAttr fast_math_attr)
                                :VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType VecFloatDivInst::get_op_type() const{
    return OpType::DIV;
}
std::string VecFloatDivInst::to_string() const{
    return this->to_string_helper("vec_float_div");
}


VecFloatRemInst::VecFloatRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            FastMathAttr fast_math_attr)
                            :VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType VecFloatRemInst::get_op_type() const{
    return OpType::REM;
}
std::string VecFloatRemInst::to_string() const{
    return this->to_string_helper("vec_float_rem");
}


VecFloatCopySignInst::VecFloatCopySignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                        FastMathAttr fast_math_attr)
                                        :VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType VecFloatCopySignInst::get_op_type() const{
    return OpType::COPYSIGN;
}
std::string VecFloatCopySignInst::to_string() const{
    return this->to_string_helper("vec_float_copysign");
}


VecFloatMinInst::VecFloatMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                            :VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, ieee754_2019, unordered){}
ArithmeticBinaryInst::OpType VecFloatMinInst::get_op_type() const{
    return OpType::MIN;
}
std::string VecFloatMinInst::to_string() const{
    return this->to_string_helper("vec_float_min");
}


VecFloatMaxInst::VecFloatMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                            :VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, ieee754_2019, unordered){}
ArithmeticBinaryInst::OpType VecFloatMaxInst::get_op_type() const{
    return OpType::MAX;
}
std::string VecFloatMaxInst::to_string() const{
    return this->to_string_helper("vec_float_max");
}       


VecFloatAvgInst::VecFloatAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                            FastMathAttr fast_math_attr)
                            :VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr, false, false){}
ArithmeticBinaryInst::OpType VecFloatAvgInst::get_op_type() const{
    return OpType::AVG;
}
std::string VecFloatAvgInst::to_string() const{
    return this->to_string_helper("vec_float_avg");
}
}
}