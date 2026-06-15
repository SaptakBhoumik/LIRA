#include "mir/instruction.hpp"
#include <memory>

namespace LIRA {
namespace MIR {
BitwiseBinaryInst::BitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                                    : Inst(instruction_stmt, destination){
    this->lhs = lhs;
    this->rhs = rhs;
}
IR::TypeExprPtr BitwiseBinaryInst::get_operand_type() const {
    return this->destination->get_type();
}
IR::LiteralExprPtr BitwiseBinaryInst::get_lhs() const {
    return this->lhs;
}
IR::LiteralExprPtr BitwiseBinaryInst::get_rhs() const {
    return this->rhs;
}
InstType BitwiseBinaryInst::get_inst_type() const {
    return InstType::BitwiseBinaryInst;
}
// ---------------------------Bitwise Integer Binary Bitwise operations ---------------------------
IntBitwiseBinaryInst::IntBitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                            bool disjoint, bool nuw, bool nsw, bool exact)
                                            : BitwiseBinaryInst(instruction_stmt, destination, lhs, rhs){
    this->disjoint = disjoint;
    this->nuw = nuw;
    this->nsw = nsw;
    this->exact = exact;
}
bool IntBitwiseBinaryInst::is_disjoint() const {
    return this->disjoint;
}
bool IntBitwiseBinaryInst::is_nuw() const {
    return this->nuw;
}
bool IntBitwiseBinaryInst::is_nsw() const {
    return this->nsw;
}
bool IntBitwiseBinaryInst::is_exact() const {
    return this->exact;
}
std::shared_ptr<IR::IntTypeExpr>IntBitwiseBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntBitwiseBinaryInst::get_bitwidth() const{
    auto int_type = this->get_casted_operand_type();
    return int_type->get_bits();
}
InstOperandTypeVarient IntBitwiseBinaryInst::get_operand_type_varient() const {
    return InstOperandTypeVarient::Int;
}


IntANDInst::IntANDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                : IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType IntANDInst::get_op_type() const {
    return OpType::AND;
}
std::string IntANDInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_and(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    return res;
}


IntORInst::IntORInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool disjoint):IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, disjoint, false, false, false){}
BitwiseBinaryInst::OpType IntORInst::get_op_type() const {
    return OpType::OR;
}
std::string IntORInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_or(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->disjoint){
        res += " #[disjoint]";
    }
    return res;
}


IntXORInst::IntXORInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                : IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType IntXORInst::get_op_type() const {
    return OpType::XOR;
}
std::string IntXORInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_xor(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    return res;
}


IntSHLInst::IntSHLInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool nuw, bool nsw):IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, nuw, nsw, false){}
BitwiseBinaryInst::OpType IntSHLInst::get_op_type() const {
    return OpType::SHL;
}
std::string IntSHLInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_shl(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    return res;
}


IntLSHRInst::IntLSHRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool exact):IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, exact){}
BitwiseBinaryInst::OpType IntLSHRInst::get_op_type() const {
    return OpType::LSHR;
}
std::string IntLSHRInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_lshr(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->exact){
        res += " #[exact]";
    }
    return res;
}


IntASHRInst::IntASHRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool exact):IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, exact){}
BitwiseBinaryInst::OpType IntASHRInst::get_op_type() const {
    return OpType::ASHR;
}
std::string IntASHRInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .int_ashr(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->exact){
        res += " #[exact]";
    }
    return res;
}


// ---------------------------Vector Integer Binary Bitwise operations ---------------------------
VecIntBitwiseBinaryInst::VecIntBitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                                   bool disjoint, bool nuw, bool nsw, bool exact) : BitwiseBinaryInst(instruction_stmt, destination, lhs, rhs){
    this->disjoint = disjoint;
    this->nuw = nuw;
    this->nsw = nsw;
    this->exact = exact;
}
bool VecIntBitwiseBinaryInst::is_disjoint() const {
    return this->disjoint;
}
bool VecIntBitwiseBinaryInst::is_nuw() const {
    return this->nuw;
}
bool VecIntBitwiseBinaryInst::is_nsw() const {
    return this->nsw;
}
bool VecIntBitwiseBinaryInst::is_exact() const {
    return this->exact;
}
std::shared_ptr<IR::SIMDTypeExpr> VecIntBitwiseBinaryInst::get_casted_operand_type() const {
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::size_t VecIntBitwiseBinaryInst::get_basetype_bitwidth() const {
    auto int_base_type = std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
    return int_base_type->get_bits();  
}
size_t VecIntBitwiseBinaryInst::get_num_elements() const {
    return this->get_casted_operand_type()->get_size();
}


VecIntANDInst::VecIntANDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                                :VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, disjoint, false, false, false){}
BitwiseBinaryInst::OpType VecIntANDInst::get_op_type() const {
    return OpType::AND;
}
std::string VecIntANDInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_and(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    return res;
}


VecIntORInst::VecIntORInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                            bool disjoint):VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, disjoint, false, false, false){}
BitwiseBinaryInst::OpType VecIntORInst::get_op_type() const {
    return OpType::OR;
}
std::string VecIntORInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_or(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->disjoint){
        res += " #[disjoint]";
    }
    return res;
}


VecIntXORInst::VecIntXORInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                                :VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType VecIntXORInst::get_op_type() const {
    return OpType::XOR;
}
std::string VecIntXORInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_xor(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    return res;
}


VecIntSHLInst::VecIntSHLInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                bool nuw, bool nsw):VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, nuw, nsw, false){}
BitwiseBinaryInst::OpType VecIntSHLInst::get_op_type() const {
    return OpType::SHL;
}
std::string VecIntSHLInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_shl(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    return res;
}


VecIntLSHRInst::VecIntLSHRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                bool exact):VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, exact){}
BitwiseBinaryInst::OpType VecIntLSHRInst::get_op_type() const {
    return OpType::LSHR;
}
std::string VecIntLSHRInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_lshr(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->exact){
        res += " #[exact]";
    }
    return res;
}


VecIntASHRInst::VecIntASHRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                bool exact):VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, exact){}
BitwiseBinaryInst::OpType VecIntASHRInst::get_op_type() const {
    return OpType::ASHR;
}
std::string VecIntASHRInst::to_string() const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = .vec_int_ashr(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->exact){
        res += " #[exact]";
    }
    return res;
}
}
}