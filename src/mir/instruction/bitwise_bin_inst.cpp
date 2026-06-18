#include "mir/instruction/bitwise_bin_inst.hpp"

namespace LIRA {
namespace MIR {
BitwiseBinaryInst::BitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     bool nuw, bool nsw, bool exact, bool disjoint):Inst(instruction_stmt, destination, std::nullopt){
    this->lhs = lhs;
    this->rhs = rhs;
    this->nuw = nuw;
    this->nsw = nsw;
    this->exact = exact;
    this->disjoint = disjoint;
}
std::string BitwiseBinaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    if(this->exact){
        res += " #[exact]";
    }
    if(this->disjoint){
        res += " #[disjoint]";
    }
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
IR::TypeExprPtr BitwiseBinaryInst::get_operand_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr BitwiseBinaryInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr BitwiseBinaryInst::get_rhs() const{
    return this->rhs;
}
bool BitwiseBinaryInst::is_nuw() const{
    return this->nuw;
}
bool BitwiseBinaryInst::is_nsw() const{
    return this->nsw;
}
bool BitwiseBinaryInst::is_exact() const{
    return this->exact;
}
bool BitwiseBinaryInst::is_disjoint() const{
    return this->disjoint;
}
InstType BitwiseBinaryInst::get_inst_type() const{
    return InstType::BitwiseBinaryInst;
}


// ---------------------------Integer Binary Bitwise operations ---------------------------
IntBitwiseBinaryInst::IntBitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                           bool nuw, bool nsw, bool exact, bool disjoint):BitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, exact, disjoint){}
std::shared_ptr<IR::IntTypeExpr> IntBitwiseBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntBitwiseBinaryInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
InstOperandTypeVarient IntBitwiseBinaryInst::get_type_varient() const{
    return InstOperandTypeVarient::Int;
}


IntAndInst::IntAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType IntAndInst::get_op_type() const{
    return OpType::AND;
}
std::string IntAndInst::to_string() const{
    return this->to_string_helper("int_and");
}


IntNandInst::IntNandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType IntNandInst::get_op_type() const{
    return OpType::NAND;
}
std::string IntNandInst::to_string() const{
    return this->to_string_helper("int_nand");
}


IntOrInst::IntOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                       bool disjoint):IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, disjoint){}
BitwiseBinaryInst::OpType IntOrInst::get_op_type() const{
    return OpType::OR;
}
std::string IntOrInst::to_string() const{
    return this->to_string_helper("int_or");
}


IntNorInst::IntNorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                       bool disjoint):IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, disjoint){}
BitwiseBinaryInst::OpType IntNorInst::get_op_type() const{
    return OpType::NOR;
}
std::string IntNorInst::to_string() const{
    return this->to_string_helper("int_nor");
}


IntXorInst::IntXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType IntXorInst::get_op_type() const{
    return OpType::XOR;
}
std::string IntXorInst::to_string() const{
    return this->to_string_helper("int_xor");
}


IntXnorInst::IntXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType IntXnorInst::get_op_type() const{
    return OpType::XNOR;
}
std::string IntXnorInst::to_string() const{
    return this->to_string_helper("int_xnor");
}


IntShlInst::IntShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool nuw, bool nsw):IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, false, false){}
BitwiseBinaryInst::OpType IntShlInst::get_op_type() const{
    return OpType::SHL;
}
std::string IntShlInst::to_string() const{
    return this->to_string_helper("int_shl");
}


IntLshrInst::IntLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool exact):IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, exact, false){}
BitwiseBinaryInst::OpType IntLshrInst::get_op_type() const{
    return OpType::LSHR;
}
std::string IntLshrInst::to_string() const{
    return this->to_string_helper("int_lshr");
}


IntAshrInst::IntAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool exact):IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, exact, false){}
BitwiseBinaryInst::OpType IntAshrInst::get_op_type() const{
    return OpType::ASHR;
}
std::string IntAshrInst::to_string() const{
    return this->to_string_helper("int_ashr");
}


IntRotlInst::IntRotlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType IntRotlInst::get_op_type() const{
    return OpType::ROTL;
}
std::string IntRotlInst::to_string() const{
    return this->to_string_helper("int_rotl");
}


IntRotrInst::IntRotrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType IntRotrInst::get_op_type() const{
    return OpType::ROTR;
}
std::string IntRotrInst::to_string() const{
    return this->to_string_helper("int_rotr");
}


IntPextInst::IntPextInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType IntPextInst::get_op_type() const{
    return OpType::PEXT;
}
std::string IntPextInst::to_string() const{
    return this->to_string_helper("int_pext");
}


IntPdepInst::IntPdepInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :IntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType IntPdepInst::get_op_type() const{
    return OpType::PDEP;
}
std::string IntPdepInst::to_string() const{
    return this->to_string_helper("int_pdep");
}


// ---------------------------Vector Integer Binary Bitwise operations ---------------------------
VecIntBitwiseBinaryInst::VecIntBitwiseBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                                 bool nuw, bool nsw, bool exact, bool disjoint)
                                                :BitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, exact, disjoint){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntBitwiseBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::size_t VecIntBitwiseBinaryInst::get_basetype_bitwidth() const{
    auto simd_type = this->get_casted_operand_type();
    auto base_type = std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
    return base_type->get_bits();
}
std::size_t VecIntBitwiseBinaryInst::get_num_elements() const{
    auto simd_type = this->get_casted_operand_type();
    return simd_type->get_size();
}
InstOperandTypeVarient VecIntBitwiseBinaryInst::get_type_varient() const{
    return InstOperandTypeVarient::VecInt;
}


VecIntAndInst::VecIntAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                            :VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType VecIntAndInst::get_op_type() const{
    return OpType::AND;
}
std::string VecIntAndInst::to_string() const{
    return this->to_string_helper("vec_int_and");
}


VecIntNandInst::VecIntNandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                            :VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType VecIntNandInst::get_op_type() const{
    return OpType::NAND;
}
std::string VecIntNandInst::to_string() const{
    return this->to_string_helper("vec_int_nand");
}


VecIntOrInst::VecIntOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                       bool disjoint):VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, disjoint){}
BitwiseBinaryInst::OpType VecIntOrInst::get_op_type() const{
    return OpType::OR;
}
std::string VecIntOrInst::to_string() const{
    return this->to_string_helper("vec_int_or");
}


VecIntNorInst::VecIntNorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                       bool disjoint):VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, disjoint){}
BitwiseBinaryInst::OpType VecIntNorInst::get_op_type() const{
    return OpType::NOR;
}
std::string VecIntNorInst::to_string() const{
    return this->to_string_helper("vec_int_nor");
}


VecIntXorInst::VecIntXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType VecIntXorInst::get_op_type() const{
    return OpType::XOR;
}
std::string VecIntXorInst::to_string() const{
    return this->to_string_helper("vec_int_xor");
}


VecIntXnorInst::VecIntXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType VecIntXnorInst::get_op_type() const{
    return OpType::XNOR;
}
std::string VecIntXnorInst::to_string() const{
    return this->to_string_helper("vec_int_xnor");
}


VecIntShlInst::VecIntShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool nuw, bool nsw):VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, nuw, nsw, false, false){}
BitwiseBinaryInst::OpType VecIntShlInst::get_op_type() const{
    return OpType::SHL;
}
std::string VecIntShlInst::to_string() const{
    return this->to_string_helper("vec_int_shl");
}


VecIntLshrInst::VecIntLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool exact):VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, exact, false){}
BitwiseBinaryInst::OpType VecIntLshrInst::get_op_type() const{
    return OpType::LSHR;
}
std::string VecIntLshrInst::to_string() const{
    return this->to_string_helper("vec_int_lshr");
}


VecIntAshrInst::VecIntAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                        bool exact):VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, exact, false){}
BitwiseBinaryInst::OpType VecIntAshrInst::get_op_type() const{
    return OpType::ASHR;
}
std::string VecIntAshrInst::to_string() const{
    return this->to_string_helper("vec_int_ashr");
}


VecIntRotlInst::VecIntRotlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType VecIntRotlInst::get_op_type() const{
    return OpType::ROTL;
}
std::string VecIntRotlInst::to_string() const{
    return this->to_string_helper("vec_int_rotl");
}


VecIntRotrInst::VecIntRotrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType VecIntRotrInst::get_op_type() const{
    return OpType::ROTR;
}
std::string VecIntRotrInst::to_string() const{
    return this->to_string_helper("vec_int_rotr");
}


VecIntPextInst::VecIntPextInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType VecIntPextInst::get_op_type() const{
    return OpType::PEXT;
}
std::string VecIntPextInst::to_string() const{
    return this->to_string_helper("vec_int_pext");
}


VecIntPdepInst::VecIntPdepInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                        :VecIntBitwiseBinaryInst(instruction_stmt, destination, lhs, rhs, false, false, false, false){}
BitwiseBinaryInst::OpType VecIntPdepInst::get_op_type() const{
    return OpType::PDEP;
}
std::string VecIntPdepInst::to_string() const{
    return this->to_string_helper("vec_int_pdep");
}
}
}