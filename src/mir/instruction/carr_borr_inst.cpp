#include "mir/instruction/carr_borr_inst.hpp"

namespace LIRA {
namespace MIR {
// ---------------------------- Carry/Borrowing Type 1 instructions ---------------------------
CarrBorrType1Inst::CarrBorrType1Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                         IR::LiteralExprPtr carr_borr_val, bool unsigned_):Inst(instruction_stmt, destination, std::nullopt){
    this->lhs = lhs;
    this->rhs = rhs;
    this->carr_borr_val = carr_borr_val;
    this->unsigned_ = unsigned_;
}
std::string CarrBorrType1Inst::to_string_helper(const std::string op_name) const{
    std::string type_str = this->get_operand_type()->to_string();
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + type_str + ":" + this->lhs->to_string() + ", " +
                                                                                                 (this->rhs != nullptr ? type_str + ":" + this->rhs->to_string() + ", " : "") +
                                                                                                 type_str + ":" + this->carr_borr_val->to_string() + ")";                                       
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}
bool CarrBorrType1Inst::is_unsigned() const{
    return this->unsigned_;
}
IR::TypeExprPtr CarrBorrType1Inst::get_operand_type() const{
    auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(this->destination->get_type());
    return struct_type->get_fields()[0];
}
IR::LiteralExprPtr CarrBorrType1Inst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr CarrBorrType1Inst::get_rhs() const{
    return this->rhs;
}
IR::LiteralExprPtr CarrBorrType1Inst::get_carr_borr_val() const{
    return this->carr_borr_val;
}
InstType CarrBorrType1Inst::get_inst_type() const{
    return InstType::CarrBorrType1Inst;
}

// ---------------------------- Int Carry/Borrowing Type 1 instructions ---------------------------
IntCarrBorrType1Inst::IntCarrBorrType1Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                           IR::LiteralExprPtr carr_borr_val, bool unsigned_)
                                           :CarrBorrType1Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, unsigned_){}
std::shared_ptr<IR::IntTypeExpr> IntCarrBorrType1Inst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntCarrBorrType1Inst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVariant IntCarrBorrType1Inst::get_operand_type_variant() const{
    return TypeVariant::Int;
}


IntCarrAddInst::IntCarrAddInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                               IR::LiteralExprPtr carr_borr_val, bool unsigned_)
                               :IntCarrBorrType1Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, unsigned_){}
CarrBorrType1Inst::OpType IntCarrAddInst::get_op_type() const{
    return OpType::CARRY_ADD;
}
std::string IntCarrAddInst::to_string() const{
    return this->to_string_helper("int_carry_add");
}


IntCarrSubInst::IntCarrSubInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                               IR::LiteralExprPtr carr_borr_val, bool unsigned_)
                               :IntCarrBorrType1Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, unsigned_){}
CarrBorrType1Inst::OpType IntCarrSubInst::get_op_type() const{
    return OpType::CARRY_SUB;
}
std::string IntCarrSubInst::to_string() const{
    return this->to_string_helper("int_carry_sub");
}


IntCarrShlInst::IntCarrShlInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs,
                               IR::LiteralExprPtr carr_borr_val)
                               :IntCarrBorrType1Inst(instruction_stmt, destination, lhs, nullptr, carr_borr_val, false){}
CarrBorrType1Inst::OpType IntCarrShlInst::get_op_type() const{
    return OpType::CARRY_SHL;
}
std::string IntCarrShlInst::to_string() const{
    return this->to_string_helper("int_carry_shl");
}


IntCarrLshrInst::IntCarrLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs,
                                 IR::LiteralExprPtr carr_borr_val)
                                 :IntCarrBorrType1Inst(instruction_stmt, destination, lhs, nullptr, carr_borr_val, false){}
CarrBorrType1Inst::OpType IntCarrLshrInst::get_op_type() const{
    return OpType::CARRY_LSHL;
}
std::string IntCarrLshrInst::to_string() const{
    return this->to_string_helper("int_carry_lshr");
}


IntCarrAshrInst::IntCarrAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs,
                                 IR::LiteralExprPtr carr_borr_val)
                                 :IntCarrBorrType1Inst(instruction_stmt, destination, lhs, nullptr, carr_borr_val, false){}
CarrBorrType1Inst::OpType IntCarrAshrInst::get_op_type() const{
    return OpType::CARRY_ASHL;
}
std::string IntCarrAshrInst::to_string() const{
    return this->to_string_helper("int_carry_ashr");
}

// ---------------------------- Vec Int Carry/Borrowing Type 1 instructions ---------------------------
VecIntCarrBorrType1Inst::VecIntCarrBorrType1Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                                 IR::LiteralExprPtr carr_borr_val, bool unsigned_)
                                                 :CarrBorrType1Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, unsigned_){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntCarrBorrType1Inst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntCarrBorrType1Inst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntCarrBorrType1Inst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntCarrBorrType1Inst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVariant VecIntCarrBorrType1Inst::get_operand_type_variant() const{
    return TypeVariant::VecInt;
}


VecIntCarrAddInst::VecIntCarrAddInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::LiteralExprPtr carr_borr_val, bool unsigned_)
                                     :VecIntCarrBorrType1Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, unsigned_){}
CarrBorrType1Inst::OpType VecIntCarrAddInst::get_op_type() const{
    return OpType::CARRY_ADD;
}
std::string VecIntCarrAddInst::to_string() const{
    return this->to_string_helper("vec_int_carry_add");
}


VecIntCarrSubInst::VecIntCarrSubInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::LiteralExprPtr carr_borr_val, bool unsigned_)
                                     :VecIntCarrBorrType1Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, unsigned_){}
CarrBorrType1Inst::OpType VecIntCarrSubInst::get_op_type() const{
    return OpType::CARRY_SUB;
}
std::string VecIntCarrSubInst::to_string() const{
    return this->to_string_helper("vec_int_carry_sub");
}


VecIntCarrShlInst::VecIntCarrShlInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs,
                                     IR::LiteralExprPtr carr_borr_val)
                                     :VecIntCarrBorrType1Inst(instruction_stmt, destination, lhs, nullptr, carr_borr_val, false){}
CarrBorrType1Inst::OpType VecIntCarrShlInst::get_op_type() const{
    return OpType::CARRY_SHL;
}
std::string VecIntCarrShlInst::to_string() const{
    return this->to_string_helper("vec_int_carry_shl");
}


VecIntCarrLshrInst::VecIntCarrLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs,
                                       IR::LiteralExprPtr carr_borr_val)
                                       :VecIntCarrBorrType1Inst(instruction_stmt, destination, lhs, nullptr, carr_borr_val, false){}
CarrBorrType1Inst::OpType VecIntCarrLshrInst::get_op_type() const{
    return OpType::CARRY_LSHL;
}
std::string VecIntCarrLshrInst::to_string() const{
    return this->to_string_helper("vec_int_carry_lshr");
}


VecIntCarrAshrInst::VecIntCarrAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs,
                                       IR::LiteralExprPtr carr_borr_val)
                                       :VecIntCarrBorrType1Inst(instruction_stmt, destination, lhs, nullptr, carr_borr_val, false){}
CarrBorrType1Inst::OpType VecIntCarrAshrInst::get_op_type() const{
    return OpType::CARRY_ASHL;
}
std::string VecIntCarrAshrInst::to_string() const{
    return this->to_string_helper("vec_int_carry_ashr");
}


// ---------------------------- Carry/Borrowing Type 2 instructions ---------------------------
CarrBorrType2Inst::CarrBorrType2Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::LiteralExprPtr carr_borr_val, bool unsigned_):Inst(instruction_stmt, destination, std::nullopt){
    this->lhs = lhs;
    this->rhs = rhs;
    this->carr_borr_val = carr_borr_val;
    this->unsigned_ = unsigned_;
}
std::string CarrBorrType2Inst::to_string_helper(const std::string op_name) const{
    std::string type_str = this->get_operand_type()->to_string();
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + type_str + ":" + this->lhs->to_string() + ", " +
                                                                                                 type_str + ":" + this->rhs->to_string() + ", " +
                                                                                                 type_str + ":" + this->carr_borr_val->to_string() + ")";                                       
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}
bool CarrBorrType2Inst::is_unsigned() const{
    return this->unsigned_;
}
IR::TypeExprPtr CarrBorrType2Inst::get_operand_type() const{
    auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(this->destination->get_type());
    return struct_type->get_fields()[0];
}
IR::LiteralExprPtr CarrBorrType2Inst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr CarrBorrType2Inst::get_rhs() const{
    return this->rhs;
}
IR::LiteralExprPtr CarrBorrType2Inst::get_carr_borr_val() const{
    return this->carr_borr_val;
}
InstType CarrBorrType2Inst::get_inst_type() const{
    return InstType::CarrBorrType2Inst;
}
// ---------------------------- Int Carry/Borrowing Type 1 instructions ---------------------------
IntCarrBorrType2Inst::IntCarrBorrType2Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                           IR::LiteralExprPtr carr_borr_val, bool unsigned_)
                                           :CarrBorrType2Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, unsigned_){}
std::shared_ptr<IR::IntTypeExpr> IntCarrBorrType2Inst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntCarrBorrType2Inst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVariant IntCarrBorrType2Inst::get_operand_type_variant() const{
    return TypeVariant::Int;
}


IntMacWideInst::IntMacWideInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                               IR::LiteralExprPtr carr_borr_val, bool unsigned_)
                               :IntCarrBorrType2Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, unsigned_){}
CarrBorrType2Inst::OpType IntMacWideInst::get_op_type() const{
    return OpType::MAC_WIDE;
}
std::string IntMacWideInst::to_string() const{
    return this->to_string_helper("int_mac_wide");
}


IntCarrShlNInst::IntCarrShlNInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                   IR::LiteralExprPtr carr_borr_val)
                                   :IntCarrBorrType2Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, false){}
CarrBorrType2Inst::OpType IntCarrShlNInst::get_op_type() const{
    return OpType::CARRY_SHL_N;
}
std::string IntCarrShlNInst::to_string() const{
    return this->to_string_helper("int_carry_shl_n");
}


IntCarrLshrNInst::IntCarrLshrNInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::LiteralExprPtr carr_borr_val)
                                     :IntCarrBorrType2Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, false){}
CarrBorrType2Inst::OpType IntCarrLshrNInst::get_op_type() const{
    return OpType::CARRY_LSHL_N;
}
std::string IntCarrLshrNInst::to_string() const{
    return this->to_string_helper("int_carry_lshr_n");
}

IntCarrAshrNInst::IntCarrAshrNInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::LiteralExprPtr carr_borr_val)
                                     :IntCarrBorrType2Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, false){}
CarrBorrType2Inst::OpType IntCarrAshrNInst::get_op_type() const{
    return OpType::CARRY_ASHL_N;
}
std::string IntCarrAshrNInst::to_string() const{
    return this->to_string_helper("int_carry_ashr_n");
}
// ---------------------------- Vec Int Carry/Borrowing Type 1 instructions ---------------------------
VecIntCarrBorrType2Inst::VecIntCarrBorrType2Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                                 IR::LiteralExprPtr carr_borr_val, bool unsigned_)
                                                 :CarrBorrType2Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, unsigned_){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntCarrBorrType2Inst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntCarrBorrType2Inst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntCarrBorrType2Inst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntCarrBorrType2Inst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVariant VecIntCarrBorrType2Inst::get_operand_type_variant() const{
    return TypeVariant::VecInt;
}


VecIntMacWideInst::VecIntMacWideInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::LiteralExprPtr carr_borr_val, bool unsigned_)
                                     :VecIntCarrBorrType2Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, unsigned_){}
CarrBorrType2Inst::OpType VecIntMacWideInst::get_op_type() const{
    return OpType::MAC_WIDE;
}
std::string VecIntMacWideInst::to_string() const{
    return this->to_string_helper("vec_int_mac_wide");
}


VecIntCarrShlNInst::VecIntCarrShlNInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                         IR::LiteralExprPtr carr_borr_val)
                                         :VecIntCarrBorrType2Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, false){}
CarrBorrType2Inst::OpType VecIntCarrShlNInst::get_op_type() const{
    return OpType::CARRY_SHL_N;
}
std::string VecIntCarrShlNInst::to_string() const{
    return this->to_string_helper("vec_int_carry_shl_n");
}


VecIntCarrLshrNInst::VecIntCarrLshrNInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                          IR::LiteralExprPtr carr_borr_val)
                                          :VecIntCarrBorrType2Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, false){}
CarrBorrType2Inst::OpType VecIntCarrLshrNInst::get_op_type() const{
    return OpType::CARRY_LSHL_N;
}
std::string VecIntCarrLshrNInst::to_string() const{
    return this->to_string_helper("vec_int_carry_lshr_n");
}

VecIntCarrAshrNInst::VecIntCarrAshrNInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                           IR::LiteralExprPtr carr_borr_val)
                                           :VecIntCarrBorrType2Inst(instruction_stmt, destination, lhs, rhs, carr_borr_val, false){}
CarrBorrType2Inst::OpType VecIntCarrAshrNInst::get_op_type() const{
    return OpType::CARRY_ASHL_N;
}
std::string VecIntCarrAshrNInst::to_string() const{
    return this->to_string_helper("vec_int_carry_ashr_n");
}
}
}