#include "mir/instruction/fetch_bitwise_bin_inst.hpp"
#include "mir/instruction/_instruction.hpp"

namespace LIRA {
namespace MIR {
FetchBitwiseBinInst::FetchBitwiseBinInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                           CommonFetchInstAttrs common_fetch_inst_attrs,
                           bool nuw, bool nsw, bool exact, bool disjoint)
                           :Inst(instruction_stmt, destination, std::nullopt){
    this->pointer = pointer;
    this->value = value;
    this->common_fetch_inst_attrs = common_fetch_inst_attrs;
    this->nuw = nuw;
    this->nsw = nsw;
    this->exact = exact;
    this->disjoint = disjoint;
};
std::string FetchBitwiseBinInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(ptr:" + this->pointer->to_string() + ", " + this->destination->get_type()->to_string() + ":" + this->value->to_string() + ")";
    res += this->common_fetch_inst_attrs.to_string();
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
IR::TypeExprPtr FetchBitwiseBinInst::get_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr FetchBitwiseBinInst::get_pointer() const{
    return this->pointer;
}
IR::LiteralExprPtr FetchBitwiseBinInst::get_value() const{
    return this->value;
}
CommonFetchInstAttrs FetchBitwiseBinInst::get_common_fetch_inst_attrs() const{
    return this->common_fetch_inst_attrs;
}
bool FetchBitwiseBinInst::is_nuw() const{
    return this->nuw;
}
bool FetchBitwiseBinInst::is_nsw() const{
    return this->nsw;
}
bool FetchBitwiseBinInst::is_exact() const{
    return this->exact;
}
bool FetchBitwiseBinInst::is_disjoint() const{
    return this->disjoint;
}
InstType FetchBitwiseBinInst::get_inst_type() const{
    return InstType::FetchBitwiseBinInst;
}


// --------------------------- Integer read modify operations ---------------------------
IntFetchBitwiseBinInst::IntFetchBitwiseBinInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                           CommonFetchInstAttrs common_fetch_inst_attrs, bool nuw, bool nsw, bool exact, bool disjoint)
                           :FetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, nuw, nsw, exact, disjoint){}
std::shared_ptr<IR::IntTypeExpr> IntFetchBitwiseBinInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_type());
}
std::size_t IntFetchBitwiseBinInst::get_bitwidth() const{
    return this->get_casted_type()->get_bits();
}
TypeVariant IntFetchBitwiseBinInst::get_type_variant() const{
    return TypeVariant::Int;
}


IntFetchAndInst::IntFetchAndInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchAndInst::get_op_type() const{
    return OpType::FETCH_AND;
}
std::string IntFetchAndInst::to_string() const{
    return this->to_string_helper("int_fetch_and");
}


IntFetchNandInst::IntFetchNandInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchNandInst::get_op_type() const{
    return OpType::FETCH_NAND;
}
std::string IntFetchNandInst::to_string() const{
    return this->to_string_helper("int_fetch_nand");
}


IntFetchOrInst::IntFetchOrInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool disjoint)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, disjoint){}
FetchBitwiseBinInst::OpType IntFetchOrInst::get_op_type() const{
    return OpType::FETCH_OR;
}
std::string IntFetchOrInst::to_string() const{
    return this->to_string_helper("int_fetch_or");
}


IntFetchNorInst::IntFetchNorInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool disjoint)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, disjoint){}
FetchBitwiseBinInst::OpType IntFetchNorInst::get_op_type() const{
    return OpType::FETCH_NOR;
}
std::string IntFetchNorInst::to_string() const{
    return this->to_string_helper("int_fetch_nor");
}


IntFetchXorInst::IntFetchXorInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchXorInst::get_op_type() const{
    return OpType::FETCH_XOR;
}
std::string IntFetchXorInst::to_string() const{
    return this->to_string_helper("int_fetch_xor");
}


IntFetchXnorInst::IntFetchXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchXnorInst::get_op_type() const{
    return OpType::FETCH_XNOR;
}
std::string IntFetchXnorInst::to_string() const{
    return this->to_string_helper("int_fetch_xnor");
}


IntFetchShlInst::IntFetchShlInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool nuw, bool nsw)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, nuw, nsw, false, false){}
FetchBitwiseBinInst::OpType IntFetchShlInst::get_op_type() const{
    return OpType::FETCH_SHL;
}
std::string IntFetchShlInst::to_string() const{
    return this->to_string_helper("int_fetch_shl");
}

IntFetchLshrInst::IntFetchLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool exact)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, exact, false){}
FetchBitwiseBinInst::OpType IntFetchLshrInst::get_op_type() const{
    return OpType::FETCH_LSHR;
}
std::string IntFetchLshrInst::to_string() const{
    return this->to_string_helper("int_fetch_lshr");
}


IntFetchAshrInst::IntFetchAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool exact)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, exact, false){}
FetchBitwiseBinInst::OpType IntFetchAshrInst::get_op_type() const{
    return OpType::FETCH_ASHR;
}
std::string IntFetchAshrInst::to_string() const{
    return this->to_string_helper("int_fetch_ashr");
}


IntFetchRotlInst::IntFetchRotlInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchRotlInst::get_op_type() const{
    return OpType::FETCH_ROTL;
}
std::string IntFetchRotlInst::to_string() const{
    return this->to_string_helper("int_fetch_rotl");
}


IntFetchRotrInst::IntFetchRotrInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchRotrInst::get_op_type() const{
    return OpType::FETCH_ROTR;
}
std::string IntFetchRotrInst::to_string() const{
    return this->to_string_helper("int_fetch_rotr");
}


IntFetchPextInst::IntFetchPextInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchPextInst::get_op_type() const{
    return OpType::FETCH_PEXT;
}
std::string IntFetchPextInst::to_string() const{
    return this->to_string_helper("int_fetch_pext");
}


IntFetchPdepInst::IntFetchPdepInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchPdepInst::get_op_type() const{
    return OpType::FETCH_PDEP;
}
std::string IntFetchPdepInst::to_string() const{
    return this->to_string_helper("int_fetch_pdep");
}
}
}