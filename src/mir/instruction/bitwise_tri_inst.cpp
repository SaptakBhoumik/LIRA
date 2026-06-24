#include "mir/instruction/bitwise_tri_inst.hpp"

namespace LIRA {
namespace MIR {
BitwiseTrinaryInst::BitwiseTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3)
                                        :Inst(instruction_stmt, destination, std::nullopt){
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->arg3 = arg3;
}
std::string BitwiseTrinaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->arg1->to_string() + ", " + this->arg2->to_string() + ", " + this->arg3->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
IR::TypeExprPtr BitwiseTrinaryInst::get_operand_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr BitwiseTrinaryInst::get_arg1() const{
    return this->arg1;
}
IR::LiteralExprPtr BitwiseTrinaryInst::get_arg2() const{
    return this->arg2;
}
IR::LiteralExprPtr BitwiseTrinaryInst::get_arg3() const{
    return this->arg3;
}
InstType BitwiseTrinaryInst::get_inst_type() const{
    return InstType::BitwiseTrinaryInst;
}


// ---------------------------- Integer Trinary operations ---------------------------
IntBitwiseTrinaryInst::IntBitwiseTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3)
                                        :BitwiseTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3){}
std::shared_ptr<IR::IntTypeExpr> IntBitwiseTrinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
}
std::size_t IntBitwiseTrinaryInst::get_bitwidth() const{
    auto type = this->get_casted_operand_type();
    return type->get_bits();
}
TypeVarient IntBitwiseTrinaryInst::get_operand_type_varient() const{
    return TypeVarient::Int;
}


IntFshlInst::IntFshlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3)
                         :IntBitwiseTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3){}
BitwiseTrinaryInst::OpType IntFshlInst::get_op_type() const{
    return OpType::FSHL;
}
std::string IntFshlInst::to_string() const{
    return this->to_string_helper("int_fshl");
}


IntFshrInst::IntFshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3)
                         :IntBitwiseTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3){}
BitwiseTrinaryInst::OpType IntFshrInst::get_op_type() const{
    return OpType::FSHR;
}
std::string IntFshrInst::to_string() const{
    return this->to_string_helper("int_fshr");
}


IntBitblendInst::IntBitblendInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3)
                                 :IntBitwiseTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3){}
BitwiseTrinaryInst::OpType IntBitblendInst::get_op_type() const{
    return OpType::BITBLEND;
}
std::string IntBitblendInst::to_string() const{
    return this->to_string_helper("int_bitblend");
}

// ---------------------------- Vector Integer Trinary operations ---------------------------
VecIntBitwiseTrinaryInst::VecIntBitwiseTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3)
                                                    :BitwiseTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntBitwiseTrinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::size_t VecIntBitwiseTrinaryInst::get_basetype_bitwidth() const{
    auto type = this->get_casted_operand_type();
    auto basetype = std::dynamic_pointer_cast<IR::IntTypeExpr>(type->get_basetype());
    return basetype->get_bits();
}
std::size_t VecIntBitwiseTrinaryInst::get_num_elements() const{
    auto type = this->get_casted_operand_type();
    return type->get_size();
}
TypeVarient VecIntBitwiseTrinaryInst::get_operand_type_varient() const{
    return TypeVarient::VecInt;
}


VecIntFshlInst::VecIntFshlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3)
                         :VecIntBitwiseTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3){}
BitwiseTrinaryInst::OpType VecIntFshlInst::get_op_type() const{
    return OpType::FSHL;
}
std::string VecIntFshlInst::to_string() const{
    return this->to_string_helper("vec_int_fshl");
}


VecIntFshrInst::VecIntFshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3)
                         :VecIntBitwiseTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3){}
BitwiseTrinaryInst::OpType VecIntFshrInst::get_op_type() const{
    return OpType::FSHR;
}
std::string VecIntFshrInst::to_string() const{
    return this->to_string_helper("vec_int_fshr");
}


VecIntBitblendInst::VecIntBitblendInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3)
                                 :VecIntBitwiseTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3){}
BitwiseTrinaryInst::OpType VecIntBitblendInst::get_op_type() const{
    return OpType::BITBLEND;
}
std::string VecIntBitblendInst::to_string() const{
    return this->to_string_helper("vec_int_bitblend");
}
}
}