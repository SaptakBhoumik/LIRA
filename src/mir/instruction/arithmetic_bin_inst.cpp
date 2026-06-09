#include "mir/instruction.hpp"
#include <memory>

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
std::shared_ptr<IR::IntTypeExpr> IntArithmeticBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
}
std::size_t IntArithmeticBinaryInst::get_bit_width() const{
    auto int_type = this->get_casted_operand_type();
    return int_type->get_bits();
}
InstOperandTypeVarient IntArithmeticBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::Int;
}


IntAddInst::IntAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw):IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, false, false){}
ArithmeticBinaryInst::OpType IntAddInst::get_op_type() const{
    return OpType::ADD;
}
std::string IntAddInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_add(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    return res;
}


IntSubInst::IntSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw):IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, false, false){}
ArithmeticBinaryInst::OpType IntSubInst::get_op_type() const{
    return OpType::SUB;
}
std::string IntSubInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_sub(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    return res;
}


IntMulInst::IntMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw):IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, false, false){}
ArithmeticBinaryInst::OpType IntMulInst::get_op_type() const{
    return OpType::MUL;
}
std::string IntMulInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_mul(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    return res;
}


IntDivInst::IntDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_, bool exact):IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, exact){}
ArithmeticBinaryInst::OpType IntDivInst::get_op_type() const{
    return OpType::DIV;
}
std::string IntDivInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_div(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    if(this->exact){
        res += " #[exact]";
    }
    return res;
}


IntRemInst::IntRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool unsigned_):IntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, false){}
ArithmeticBinaryInst::OpType IntRemInst::get_op_type() const{
    return OpType::REM;
}
std::string IntRemInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_rem(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}


// ----------------------------- Vector integer binary operations ---------------------------
VecIntArithmeticBinaryInst::VecIntArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                bool nuw, bool nsw, bool unsigned_, bool exact):ArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->exact = exact;
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
                                bool nuw, bool nsw):VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, false, false){}
ArithmeticBinaryInst::OpType VecIntAddInst::get_op_type() const{
    return OpType::ADD;
}
std::string VecIntAddInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_add(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    return res;
}


VecIntSubInst::VecIntSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                bool nuw, bool nsw):VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, false, false){}
ArithmeticBinaryInst::OpType VecIntSubInst::get_op_type() const{
    return OpType::SUB; 
}
std::string VecIntSubInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_sub(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    return res;
}


VecIntMulInst::VecIntMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                bool nuw, bool nsw):VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, false, false){}
ArithmeticBinaryInst::OpType VecIntMulInst::get_op_type() const{
    return OpType::MUL;
}
std::string VecIntMulInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_mul(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    return res;
}


VecIntDivInst::VecIntDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                bool unsigned_, bool exact):VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, exact){}
ArithmeticBinaryInst::OpType VecIntDivInst::get_op_type() const{
    return OpType::DIV;
}
std::string VecIntDivInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_div(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    if(this->exact){
        res += " #[exact]";
    }
    return res;
}


VecIntRemInst::VecIntRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                bool unsigned_):VecIntArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, unsigned_, false){}
ArithmeticBinaryInst::OpType VecIntRemInst::get_op_type() const{
    return OpType::REM;
}
std::string VecIntRemInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_rem(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}


// ---------------------------- Float binary operations ---------------------------
FloatArithmeticBinaryInst::FloatArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                FastMathAttr fast_math_attr):ArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs){
    this->fast_math_attr = fast_math_attr;
}
FastMathAttr FloatArithmeticBinaryInst::get_fast_math_attr() const{
    return this->fast_math_attr;
}
std::shared_ptr<IR::FloatTypeExpr> FloatArithmeticBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->destination->get_type());
}
std::size_t FloatArithmeticBinaryInst::get_bit_width() const{
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
                                FastMathAttr fast_math_attr):FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr){}
ArithmeticBinaryInst::OpType FloatAddInst::get_op_type() const{
    return OpType::ADD;
}
std::string FloatAddInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .float_add(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    return res;
}


FloatSubInst::FloatSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                FastMathAttr fast_math_attr):FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr){}
ArithmeticBinaryInst::OpType FloatSubInst::get_op_type() const{
    return OpType::SUB;
}
std::string FloatSubInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .float_sub(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    return res;
}


FloatMulInst::FloatMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                FastMathAttr fast_math_attr):FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr){}
ArithmeticBinaryInst::OpType FloatMulInst::get_op_type() const{
    return OpType::MUL;
}
std::string FloatMulInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .float_mul(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    return res;
}


FloatDivInst::FloatDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                FastMathAttr fast_math_attr):FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr){}
ArithmeticBinaryInst::OpType FloatDivInst::get_op_type() const{
    return OpType::DIV;
}
std::string FloatDivInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .float_div(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    return res;
}


FloatRemInst::FloatRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                FastMathAttr fast_math_attr):FloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr){}
ArithmeticBinaryInst::OpType FloatRemInst::get_op_type() const{
    return OpType::REM;
}
std::string FloatRemInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .float_rem(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    return res;
}


// ---------------------------- Vector Float binary operations ---------------------------
VecFloatArithmeticBinaryInst::VecFloatArithmeticBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                FastMathAttr fast_math_attr):ArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs){
    this->fast_math_attr = fast_math_attr;
}
FastMathAttr VecFloatArithmeticBinaryInst::get_fast_math_attr() const{
    return this->fast_math_attr;
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
                    FastMathAttr fast_math_attr):VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr){}
ArithmeticBinaryInst::OpType VecFloatAddInst::get_op_type() const{
    return OpType::ADD;
}
std::string VecFloatAddInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_float_add(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    return res;
}


VecFloatSubInst::VecFloatSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                    FastMathAttr fast_math_attr):VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr){}
ArithmeticBinaryInst::OpType VecFloatSubInst::get_op_type() const{
    return OpType::SUB;
}
std::string VecFloatSubInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_float_sub(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    return res;
}


VecFloatMulInst::VecFloatMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                    FastMathAttr fast_math_attr):VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr){}
ArithmeticBinaryInst::OpType VecFloatMulInst::get_op_type() const{
    return OpType::MUL;
}
std::string VecFloatMulInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_float_mul(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    return res;
}


VecFloatDivInst::VecFloatDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                    FastMathAttr fast_math_attr):VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr){}
ArithmeticBinaryInst::OpType VecFloatDivInst::get_op_type() const{
    return OpType::DIV;
}
std::string VecFloatDivInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_float_div(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    return res;
}


VecFloatRemInst::VecFloatRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                    FastMathAttr fast_math_attr):VecFloatArithmeticBinaryInst(instruction_stmt, destination, lhs, rhs, fast_math_attr){}
ArithmeticBinaryInst::OpType VecFloatRemInst::get_op_type() const{
    return OpType::REM;
}
std::string VecFloatRemInst::to_string() const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_float_rem(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    return res;
}
}
}