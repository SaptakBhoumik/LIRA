#include "mir/instruction/wrap_binary_inst.hpp"
#include <memory>
#include <optional>
#include <string>

namespace LIRA {
namespace MIR {
WrapBinaryInst::WrapBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                bool unsigned_, bool saturating):Inst(instruction_stmt, destination, std::nullopt){
    this->lhs = lhs;
    this->rhs = rhs;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
}
bool WrapBinaryInst::is_unsigned() const{
    return this->unsigned_;
}
bool WrapBinaryInst::is_saturating() const{
    return this->saturating;
}
std::string WrapBinaryInst::to_string_helper(const std::string op_name) const{
    std::string type_str = this->get_operand_type()->to_string();
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + type_str + ":" + this->lhs->to_string() + ", " + type_str + ":" + this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    if(this->saturating){
        res += " #[saturating]";
    }
    return res;
}
IR::TypeExprPtr WrapBinaryInst::get_operand_type() const{
    auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(this->destination->get_type());
    return struct_type->get_fields()[0];
}
IR::LiteralExprPtr WrapBinaryInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr WrapBinaryInst::get_rhs() const{
    return this->rhs;
}
InstType WrapBinaryInst::get_inst_type() const{
    return InstType::WrapBinaryInst;
}


// ---------------------------- Integer Wrap Arithmetic Binary Operations ---------------------------
IntWrapBinaryInst::IntWrapBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                     bool unsigned_, bool saturating):WrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
std::shared_ptr<IR::IntTypeExpr> IntWrapBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_operand_type());
}
std::size_t IntWrapBinaryInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
InstOperandTypeVarient IntWrapBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::Int;
}


IntWrapAddInst::IntWrapAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                               bool unsigned_, bool saturating):IntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType IntWrapAddInst::get_op_type() const{
    return OpType::WRAP_ADD;
}
std::string IntWrapAddInst::to_string() const{
    return this->to_string_helper("int_wrap_add");
}


IntWrapSubInst::IntWrapSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                               bool unsigned_, bool saturating):IntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType IntWrapSubInst::get_op_type() const{
    return OpType::WRAP_SUB;
}
std::string IntWrapSubInst::to_string() const{
    return this->to_string_helper("int_wrap_sub");
}


IntWrapMulInst::IntWrapMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                               bool unsigned_, bool saturating):IntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType IntWrapMulInst::get_op_type() const{
    return OpType::WRAP_MUL;
}
std::string IntWrapMulInst::to_string() const{
    return this->to_string_helper("int_wrap_mul");
}


IntWrapDivInst::IntWrapDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                               bool unsigned_, bool saturating):IntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType IntWrapDivInst::get_op_type() const{
    return OpType::WRAP_DIV;
}
std::string IntWrapDivInst::to_string() const{
    return this->to_string_helper("int_wrap_div");
}


IntWrapRemInst::IntWrapRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                               bool unsigned_, bool saturating):IntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType IntWrapRemInst::get_op_type() const{
    return OpType::WRAP_REM;
}
std::string IntWrapRemInst::to_string() const{
    return this->to_string_helper("int_wrap_rem");
}


IntWrapCopysignInst::IntWrapCopysignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                         bool unsigned_, bool saturating):IntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType IntWrapCopysignInst::get_op_type() const{
    return OpType::WRAP_COPYSIGN;
}
std::string IntWrapCopysignInst::to_string() const{
    return this->to_string_helper("int_wrap_copysign");
}


IntWrapShlInst::IntWrapShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                               bool unsigned_, bool saturating):IntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType IntWrapShlInst::get_op_type() const{
    return OpType::WRAP_SHL;
}
std::string IntWrapShlInst::to_string() const{
    return this->to_string_helper("int_wrap_shl");
}


IntWrapLshrInst::IntWrapLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                 bool unsigned_, bool saturating):IntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType IntWrapLshrInst::get_op_type() const{
    return OpType::WRAP_LSHR;
}
std::string IntWrapLshrInst::to_string() const{
    return this->to_string_helper("int_wrap_lshr");
}


IntWrapAshrInst::IntWrapAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                 bool unsigned_, bool saturating):IntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType IntWrapAshrInst::get_op_type() const{
    return OpType::WRAP_ASHR;
}
std::string IntWrapAshrInst::to_string() const{
    return this->to_string_helper("int_wrap_ashr");
}


// ---------------------------- Vector Integer Wrap Arithmetic Binary Operations ---------------------------
VecIntWrapBinaryInst::VecIntWrapBinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                            bool unsigned_, bool saturating):WrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
std::shared_ptr<IR::SIMDTypeExpr> VecIntWrapBinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_operand_type());
}
std::shared_ptr<IR::IntTypeExpr> VecIntWrapBinaryInst::get_casted_operand_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_casted_operand_type()->get_basetype());
}
std::size_t VecIntWrapBinaryInst::get_operand_basetype_bitwidth() const{
    return this->get_casted_operand_basetype()->get_bits();
}
std::size_t VecIntWrapBinaryInst::get_vector_size() const{
    return this->get_casted_operand_type()->get_size();
}
InstOperandTypeVarient VecIntWrapBinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::VecInt;
}


VecIntWrapAddInst::VecIntWrapAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                     bool unsigned_, bool saturating):VecIntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType VecIntWrapAddInst::get_op_type() const{
    return OpType::WRAP_ADD;
}
std::string VecIntWrapAddInst::to_string() const{
    return this->to_string_helper("vec_int_wrap_add");
}


VecIntWrapSubInst::VecIntWrapSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                     bool unsigned_, bool saturating):VecIntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType VecIntWrapSubInst::get_op_type() const{
    return OpType::WRAP_SUB;
}
std::string VecIntWrapSubInst::to_string() const{
    return this->to_string_helper("vec_int_wrap_sub");
}


VecIntWrapMulInst::VecIntWrapMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                     bool unsigned_, bool saturating):VecIntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType VecIntWrapMulInst::get_op_type() const{
    return OpType::WRAP_MUL;
}
std::string VecIntWrapMulInst::to_string() const{
    return this->to_string_helper("vec_int_wrap_mul");
}


VecIntWrapDivInst::VecIntWrapDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                     bool unsigned_, bool saturating):VecIntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType VecIntWrapDivInst::get_op_type() const{
    return OpType::WRAP_DIV;
}
std::string VecIntWrapDivInst::to_string() const{
    return this->to_string_helper("vec_int_wrap_div");
}


VecIntWrapRemInst::VecIntWrapRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                     bool unsigned_, bool saturating):VecIntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType VecIntWrapRemInst::get_op_type() const{
    return OpType::WRAP_REM;
}
std::string VecIntWrapRemInst::to_string() const{
    return this->to_string_helper("vec_int_wrap_rem");
}


VecIntWrapCopysignInst::VecIntWrapCopysignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                bool unsigned_, bool saturating):VecIntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType VecIntWrapCopysignInst::get_op_type() const{
    return OpType::WRAP_COPYSIGN;
}
std::string VecIntWrapCopysignInst::to_string() const{
    return this->to_string_helper("vec_int_wrap_copysign");
}


VecIntWrapShlInst::VecIntWrapShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                     bool unsigned_, bool saturating):VecIntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType VecIntWrapShlInst::get_op_type() const{
    return OpType::WRAP_SHL;
}
std::string VecIntWrapShlInst::to_string() const{
    return this->to_string_helper("vec_int_wrap_shl");
}


VecIntWrapLshrInst::VecIntWrapLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                       bool unsigned_, bool saturating):VecIntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType VecIntWrapLshrInst::get_op_type() const{
    return OpType::WRAP_LSHR;
}
std::string VecIntWrapLshrInst::to_string() const{
    return this->to_string_helper("vec_int_wrap_lshr");
}


VecIntWrapAshrInst::VecIntWrapAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                       bool unsigned_, bool saturating):VecIntWrapBinaryInst(instruction_stmt, destination, lhs, rhs, unsigned_, saturating){}
WrapBinaryInst::OpType VecIntWrapAshrInst::get_op_type() const{
    return OpType::WRAP_ASHR;
}
std::string VecIntWrapAshrInst::to_string() const{
    return this->to_string_helper("vec_int_wrap_ashr");
}
}
}