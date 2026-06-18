#include "mir/instruction/cmp_bin_inst.hpp"
#include "ast/ast.hpp"
#include <memory>
#include <string>
#include <memory>

namespace LIRA {
namespace MIR {
CmpBinaryInst::CmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                             IR::TypeExprPtr type, std::optional<FastMathAttr> fast_math_attr):
                             Inst(instruction_stmt, destination, fast_math_attr){
    this->lhs = lhs;
    this->rhs = rhs;
    this->type = type;
}
IR::TypeExprPtr CmpBinaryInst::get_operand_type() const{
    return this->type;
}
IR::LiteralExprPtr CmpBinaryInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr CmpBinaryInst::get_rhs() const{
    return this->rhs;
}
InstType CmpBinaryInst::get_inst_type() const{
    return InstType::CmpBinaryInst;
}


// ---------------------------- Integer Comparison Binary operations ---------------------------
IntCmpBinaryInst::IntCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    IR::TypeExprPtr type, bool unsigned_):CmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, std::nullopt){
    this->unsigned_ = unsigned_;
}
std::string IntCmpBinaryInst::to_string_helper(std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->type->to_string() + ":" + this->lhs->to_string() + ", " + this->type->to_string() + ":" +  this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}
bool IntCmpBinaryInst::is_unsigned() const{
    return this->unsigned_;
}
std::shared_ptr<IR::IntTypeExpr> IntCmpBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->type);
}
std::size_t IntCmpBinaryInst::get_bitwidth() const{
    auto int_type = this->get_casted_operand_type();
    return int_type->get_bits();
}
InstOperandTypeVarient IntCmpBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::Int;
}


IntEqInst::IntEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                IntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, false){}
CmpBinaryInst::OpType IntEqInst::get_op_type() const{
    return OpType::EQ;
}
std::string IntEqInst::to_string() const{
    return this->to_string_helper("int_eq");
}


IntNeqInst::IntNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                IntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, false){}
CmpBinaryInst::OpType IntNeqInst::get_op_type() const{
    return OpType::NEQ;
}
std::string IntNeqInst::to_string() const{
    return this->to_string_helper("int_neq");
}


IntLtInst::IntLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                     bool unsigned_):IntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, unsigned_){}
CmpBinaryInst::OpType IntLtInst::get_op_type() const{
    return OpType::LT;
}
std::string IntLtInst::to_string() const{
    return this->to_string_helper("int_lt");
}


IntGtInst::IntGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                     bool unsigned_):IntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, unsigned_){}
CmpBinaryInst::OpType IntGtInst::get_op_type() const{
    return OpType::GT;
}
std::string IntGtInst::to_string() const{
    return this->to_string_helper("int_gt");
}


IntLeInst::IntLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                     bool unsigned_):IntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, unsigned_){}
CmpBinaryInst::OpType IntLeInst::get_op_type() const{
    return OpType::LE;
}
std::string IntLeInst::to_string() const{
    return this->to_string_helper("int_le");
}


IntGeInst::IntGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                     bool unsigned_):IntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, unsigned_){}
CmpBinaryInst::OpType IntGeInst::get_op_type() const{
    return OpType::GE;
}
std::string IntGeInst::to_string() const{
    return this->to_string_helper("int_ge");
}


// ---------------------------Vector integer Comparison Binary operations ---------------------------
VecIntCmpBinaryInst::VecIntCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                            bool unsigned_):CmpBinaryInst(instruction_stmt, destination, lhs, rhs, type,std::nullopt){
    this->unsigned_ = unsigned_;
}
std::string VecIntCmpBinaryInst::to_string_helper(std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->type->to_string() + ":" + this->lhs->to_string() + ", " + this->type->to_string() + ":" +  this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}
bool VecIntCmpBinaryInst::is_unsigned() const{
    return this->unsigned_;
}
std::shared_ptr<IR::SIMDTypeExpr> VecIntCmpBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->type);
}
std::size_t VecIntCmpBinaryInst::get_basetype_bitwidth() const{
    auto simd_type = this->get_casted_operand_type();
    auto basetype = simd_type->get_basetype();
    auto int_basetype = std::dynamic_pointer_cast<IR::IntTypeExpr>(basetype);
    return int_basetype->get_bits();
}
std::size_t VecIntCmpBinaryInst::get_num_elements() const{
    auto simd_type = this->get_casted_operand_type();
    return simd_type->get_size();
}
InstOperandTypeVarient VecIntCmpBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::VecInt;
}


VecIntEqInst::VecIntEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                            VecIntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, false){}
CmpBinaryInst::OpType VecIntEqInst::get_op_type() const{
    return OpType::EQ;
}
std::string VecIntEqInst::to_string() const{
    return this->to_string_helper("vec_int_eq");
}


VecIntNeqInst::VecIntNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                            VecIntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, false){}
CmpBinaryInst::OpType VecIntNeqInst::get_op_type() const{
    return OpType::NEQ;
}
std::string VecIntNeqInst::to_string() const{
    return this->to_string_helper("vec_int_neq");
}


VecIntLtInst::VecIntLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                            bool unsigned_):VecIntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, unsigned_){}
CmpBinaryInst::OpType VecIntLtInst::get_op_type() const{
    return OpType::LT;
}
std::string VecIntLtInst::to_string() const{
    return this->to_string_helper("vec_int_lt");
}


VecIntGtInst::VecIntGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                            bool unsigned_):VecIntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, unsigned_){}
CmpBinaryInst::OpType VecIntGtInst::get_op_type() const{
    return OpType::GT;
}
std::string VecIntGtInst::to_string() const{
    return this->to_string_helper("vec_int_gt");
}


VecIntLeInst::VecIntLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                            bool unsigned_):VecIntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, unsigned_){}
CmpBinaryInst::OpType VecIntLeInst::get_op_type() const{
    return OpType::LE;
}
std::string VecIntLeInst::to_string() const{
    return this->to_string_helper("vec_int_le");
}


VecIntGeInst::VecIntGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                            bool unsigned_):VecIntCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, unsigned_){}
CmpBinaryInst::OpType VecIntGeInst::get_op_type() const{
    return OpType::GE;
}
std::string VecIntGeInst::to_string() const{
    return this->to_string_helper("vec_int_ge");
}


// ---------------------------Ptr Comparison Binary operations ---------------------------
PtrCmpBinaryInst::PtrCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs):
                                    CmpBinaryInst(instruction_stmt, destination, lhs, rhs, std::make_shared<IR::PtrTypeExpr>(IR::Token{.value = "ptr"},std::vector<IR::AttributePtr>{}), std::nullopt){}
std::string PtrCmpBinaryInst::to_string_helper(std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->type->to_string() + ":" + this->lhs->to_string() + ", " + this->type->to_string() + ":" +  this->rhs->to_string() + ")";
    return res;
}
std::size_t PtrCmpBinaryInst::get_bitwidth() const{
    return 64;//We support only x86_64 for now but can return diffrent in future if we support more arch. Just a helper function to make life easier
}
InstOperandTypeVarient PtrCmpBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::Ptr;
}


PtrEqInst::PtrEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs):
                PtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs){}
CmpBinaryInst::OpType PtrEqInst::get_op_type() const{
    return OpType::EQ;
}
std::string PtrEqInst::to_string() const{
    return this->to_string_helper("ptr_eq");
}


PtrNeqInst::PtrNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs):
                PtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs){}
CmpBinaryInst::OpType PtrNeqInst::get_op_type() const{
    return OpType::NEQ;
}
std::string PtrNeqInst::to_string() const{
    return this->to_string_helper("ptr_neq");
}


PtrGtInst::PtrGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs):
                PtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs){}
CmpBinaryInst::OpType PtrGtInst::get_op_type() const{
    return OpType::GT;
}
std::string PtrGtInst::to_string() const{
    return this->to_string_helper("ptr_gt");
}


PtrLtInst::PtrLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs):
                PtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs){}
CmpBinaryInst::OpType PtrLtInst::get_op_type() const{
    return OpType::LT;
}
std::string PtrLtInst::to_string() const{
    return this->to_string_helper("ptr_lt");
}


PtrLeInst::PtrLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs):
                PtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs){}
CmpBinaryInst::OpType PtrLeInst::get_op_type() const{
    return OpType::LE;
}
std::string PtrLeInst::to_string() const{
    return this->to_string_helper("ptr_le");
}


PtrGeInst::PtrGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs):
                PtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs){}
CmpBinaryInst::OpType PtrGeInst::get_op_type() const{
    return OpType::GE;
}
std::string PtrGeInst::to_string() const{
    return this->to_string_helper("ptr_ge");
}


// ---------------------------Vector ptr Comparison Binary operations ---------------------------
VecPtrCmpBinaryInst::VecPtrCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                                        CmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, std::nullopt){}
std::string VecPtrCmpBinaryInst::to_string_helper(std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->type->to_string() + ":" + this->lhs->to_string() + ", " + this->type->to_string() + ":" +  this->rhs->to_string() + ")";
    return res;
}
std::shared_ptr<IR::SIMDTypeExpr> VecPtrCmpBinaryInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->type);
}
std::size_t VecPtrCmpBinaryInst::get_basetype_bitwidth() const{
    return 64;//We support only x86_64 for now but can return diffrent in future if we support more arch. Just a helper function to make life easier
}
std::size_t VecPtrCmpBinaryInst::get_num_elements() const{
    auto simd_type = this->get_casted_type();
    return simd_type->get_size();
}
InstOperandTypeVarient VecPtrCmpBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::VecPtr;
}


VecPtrEqInst::VecPtrEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                VecPtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type){}
CmpBinaryInst::OpType VecPtrEqInst::get_op_type() const{
    return OpType::EQ;
}
std::string VecPtrEqInst::to_string() const{
    return this->to_string_helper("vec_ptr_eq");
}


VecPtrNeqInst::VecPtrNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                VecPtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type){}
CmpBinaryInst::OpType VecPtrNeqInst::get_op_type() const{
    return OpType::NEQ;
}
std::string VecPtrNeqInst::to_string() const{
    return this->to_string_helper("vec_ptr_neq");
}


VecPtrLtInst::VecPtrLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                VecPtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type){}
CmpBinaryInst::OpType VecPtrLtInst::get_op_type() const{
    return OpType::LT;
}
std::string VecPtrLtInst::to_string() const{
    return this->to_string_helper("vec_ptr_lt");
}


VecPtrGtInst::VecPtrGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                VecPtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type){}
CmpBinaryInst::OpType VecPtrGtInst::get_op_type() const{
    return OpType::GT;
}
std::string VecPtrGtInst::to_string() const{
    return this->to_string_helper("vec_ptr_gt");
}


VecPtrLeInst::VecPtrLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                VecPtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type){}
CmpBinaryInst::OpType VecPtrLeInst::get_op_type() const{
    return OpType::LE;
}
std::string VecPtrLeInst::to_string() const{
    return this->to_string_helper("vec_ptr_le");
}


VecPtrGeInst::VecPtrGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type):
                VecPtrCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type){}
CmpBinaryInst::OpType VecPtrGeInst::get_op_type() const{
    return OpType::GE;
}
std::string VecPtrGeInst::to_string() const{
    return this->to_string_helper("vec_ptr_ge");
}


// ---------------------------Float Comparison Binary operations ---------------------------
FloatCmpBinaryInst::FloatCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                        FastMathAttr fast_math_attr, bool unordered):CmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr){
    this->unordered = unordered;
}
std::string FloatCmpBinaryInst::to_string_helper(std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->type->to_string() + ":" + this->lhs->to_string() + ", " + this->type->to_string() + ":" +  this->rhs->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res+= " " + this->fast_math_attr.value().to_string();
    }
    if(this->unordered){
        res += " #[unordered]";
    }
    return res;
}
bool FloatCmpBinaryInst::is_unordered() const{
    return this->unordered;
}
std::shared_ptr<IR::FloatTypeExpr> FloatCmpBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->type);
}
std::size_t FloatCmpBinaryInst::get_bitwidth() const{
    auto float_type = this->get_casted_operand_type();
    return float_type->get_bits();
}
bool FloatCmpBinaryInst::is_brain_float() const{
    return false;
}
InstOperandTypeVarient FloatCmpBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::Float;
}


FloatEqInst::FloatEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):FloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType FloatEqInst::get_op_type() const{
    return OpType::EQ;
}
std::string FloatEqInst::to_string() const{
    return this->to_string_helper("float_eq");
}


FloatNeqInst::FloatNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):FloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType FloatNeqInst::get_op_type() const{
    return OpType::NEQ;
}
std::string FloatNeqInst::to_string() const{
    return this->to_string_helper("float_neq");
}


FloatLtInst::FloatLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):FloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType FloatLtInst::get_op_type() const{
    return OpType::LT;
}
std::string FloatLtInst::to_string() const{
    return this->to_string_helper("float_lt");
}


FloatGtInst::FloatGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):FloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType FloatGtInst::get_op_type() const{
    return OpType::GT;
}
std::string FloatGtInst::to_string() const{
    return this->to_string_helper("float_gt");
}


FloatLeInst::FloatLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):FloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType FloatLeInst::get_op_type() const{
    return OpType::LE;
}
std::string FloatLeInst::to_string() const{
    return this->to_string_helper("float_le");
}


FloatGeInst::FloatGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):FloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType FloatGeInst::get_op_type() const{
    return OpType::GE;
}
std::string FloatGeInst::to_string() const{
    return this->to_string_helper("float_ge");
}


FloatEitherNanInst::FloatEitherNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr):FloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, false){}
CmpBinaryInst::OpType FloatEitherNanInst::get_op_type() const{
    return OpType::EITHER_NAN;
}
std::string FloatEitherNanInst::to_string() const{
    return this->to_string_helper("float_either_nan");
}


FloatNeitherNanInst::FloatNeitherNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                        FastMathAttr fast_math_attr):FloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, false){}
CmpBinaryInst::OpType FloatNeitherNanInst::get_op_type() const{
    return OpType::NEITHER_NAN;
}
std::string FloatNeitherNanInst::to_string() const{
    return this->to_string_helper("float_neither_nan");
}

FloatBothNanInst::FloatBothNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                        FastMathAttr fast_math_attr):FloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, false){}
CmpBinaryInst::OpType FloatBothNanInst::get_op_type() const{
    return OpType::BOTH_NAN;
}
std::string FloatBothNanInst::to_string() const{
    return this->to_string_helper("float_both_nan");
}
// --------------------------- Vector Float Comparison Binary operations ---------------------------
VecFloatCmpBinaryInst::VecFloatCmpBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                        FastMathAttr fast_math_attr, bool unordered):CmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr){
    this->unordered = unordered;
}
std::string VecFloatCmpBinaryInst::to_string_helper(std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->type->to_string() + ":" + this->lhs->to_string() + ", " + this->type->to_string() + ":" +  this->rhs->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res+= " " + this->fast_math_attr.value().to_string();
    }
    if(this->unordered){
        res += " #[unordered]";
    }
    return res;
}
bool VecFloatCmpBinaryInst::is_unordered() const{
    return this->unordered;
}
std::shared_ptr<IR::SIMDTypeExpr> VecFloatCmpBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->type);
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatCmpBinaryInst::get_basetype() const{
    auto simd_type = this->get_casted_operand_type();
    auto basetype = simd_type->get_basetype();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(basetype);
}
std::size_t VecFloatCmpBinaryInst::get_num_elements() const{
    auto simd_type = this->get_casted_operand_type();
    return simd_type->get_size();
}
InstOperandTypeVarient VecFloatCmpBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::VecFloat;
}


VecFloatEqInst::VecFloatEqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):VecFloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType VecFloatEqInst::get_op_type() const{
    return OpType::EQ;
}
std::string VecFloatEqInst::to_string() const{
    return this->to_string_helper("vec_float_eq");
}


VecFloatNeqInst::VecFloatNeqInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):VecFloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType VecFloatNeqInst::get_op_type() const{
    return OpType::NEQ;
}
std::string VecFloatNeqInst::to_string() const{
    return this->to_string_helper("vec_float_neq");
}


VecFloatLtInst::VecFloatLtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):VecFloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType VecFloatLtInst::get_op_type() const{
    return OpType::LT;
}
std::string VecFloatLtInst::to_string() const{
    return this->to_string_helper("vec_float_lt");
}


VecFloatGtInst::VecFloatGtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):VecFloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType VecFloatGtInst::get_op_type() const{
    return OpType::GT;
}
std::string VecFloatGtInst::to_string() const{
    return this->to_string_helper("vec_float_gt");
}


VecFloatLeInst::VecFloatLeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):VecFloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType VecFloatLeInst::get_op_type() const{
    return OpType::LE;
}
std::string VecFloatLeInst::to_string() const{
    return this->to_string_helper("vec_float_le");
}


VecFloatGeInst::VecFloatGeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr, bool unordered):VecFloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, unordered){}
CmpBinaryInst::OpType VecFloatGeInst::get_op_type() const{
    return OpType::GE;
}
std::string VecFloatGeInst::to_string() const{
    return this->to_string_helper("vec_float_ge");
}


VecFloatEitherNanInst::VecFloatEitherNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                FastMathAttr fast_math_attr):VecFloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, false){}
CmpBinaryInst::OpType VecFloatEitherNanInst::get_op_type() const{
    return OpType::EITHER_NAN;
}
std::string VecFloatEitherNanInst::to_string() const{
    return this->to_string_helper("vec_float_either_nan");
}


VecFloatNeitherNanInst::VecFloatNeitherNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                        FastMathAttr fast_math_attr):VecFloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, false){}
CmpBinaryInst::OpType VecFloatNeitherNanInst::get_op_type() const{
    return OpType::NEITHER_NAN;
}
std::string VecFloatNeitherNanInst::to_string() const{
    return this->to_string_helper("vec_float_neither_nan");
}


VecFloatBothNanInst::VecFloatBothNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr type,
                                        FastMathAttr fast_math_attr):VecFloatCmpBinaryInst(instruction_stmt, destination, lhs, rhs, type, fast_math_attr, false){}
CmpBinaryInst::OpType VecFloatBothNanInst::get_op_type() const{
    return OpType::BOTH_NAN;
}
std::string VecFloatBothNanInst::to_string() const{
    return this->to_string_helper("vec_float_both_nan");
}
}
}