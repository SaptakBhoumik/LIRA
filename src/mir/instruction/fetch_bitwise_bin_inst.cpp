#include "mir/instruction/fetch_bitwise_bin_inst.hpp"
#include <memory>

namespace LIRA {
namespace MIR {
FetchBitwiseBinInst::FetchBitwiseBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                           std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                           bool nuw, bool nsw, bool exact, bool disjoint)
                           :Inst(instruction_stmt, destination){
    this->pointer = pointer;
    this->value = value;
    this->alignment = alignment;
    this->volatile_ = volatile_;
    this->atomic_info = atomic_info;
    this->nuw = nuw;
    this->nsw = nsw;
    this->exact = exact;
    this->disjoint = disjoint;
};
std::string FetchBitwiseBinInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(ptr:" + this->pointer->to_string() + ", " + this->destination->get_type()->to_string() + ":" + this->value->to_string() + ")";
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
std::size_t FetchBitwiseBinInst::get_alignment() const{
    return this->alignment;
}
bool FetchBitwiseBinInst::is_volatile() const{
    return this->volatile_;
}
std::optional<std::pair<SyncScope,AtomicOrdering>> FetchBitwiseBinInst::get_atomic_info() const{
    return this->atomic_info;
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
InstType FetchBitwiseBinInst::get_inst_type() const {
    return InstType::FetchBitwiseBinInst;
}


// --------------------------- Integer read modify operations ---------------------------
IntFetchBitwiseBinInst::IntFetchBitwiseBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                           std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                           bool nuw, bool nsw, bool exact, bool disjoint)
                           :FetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, nuw, nsw, exact, disjoint){}
std::shared_ptr<IR::IntTypeExpr> IntFetchBitwiseBinInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_type());
}
std::size_t IntFetchBitwiseBinInst::get_bitwidth() const{
    return this->get_casted_type()->get_bits();
}
InstOperandTypeVarient IntFetchBitwiseBinInst::get_type_varient() const{
    return InstOperandTypeVarient::Int;
}


IntFetchAndInst::IntFetchAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchAndInst::get_op_type() const {
    return OpType::FETCH_AND;
}
std::string IntFetchAndInst::to_string() const {
    return this->to_string_helper("int_fetch_and");
}


IntFetchNandInst::IntFetchNandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchNandInst::get_op_type() const {
    return OpType::FETCH_NAND;
}
std::string IntFetchNandInst::to_string() const {
    return this->to_string_helper("int_fetch_nand");
}


IntFetchOrInst::IntFetchOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool disjoint)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, disjoint){}
FetchBitwiseBinInst::OpType IntFetchOrInst::get_op_type() const {
    return OpType::FETCH_OR;
}
std::string IntFetchOrInst::to_string() const {
    return this->to_string_helper("int_fetch_or");
}


IntFetchNorInst::IntFetchNorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool disjoint)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, disjoint){}
FetchBitwiseBinInst::OpType IntFetchNorInst::get_op_type() const {
    return OpType::FETCH_NOR;
}
std::string IntFetchNorInst::to_string() const {
    return this->to_string_helper("int_fetch_nor");
}


IntFetchXorInst::IntFetchXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchXorInst::get_op_type() const {
    return OpType::FETCH_XOR;
}
std::string IntFetchXorInst::to_string() const {
    return this->to_string_helper("int_fetch_xor");
}


IntFetchXnorInst::IntFetchXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchXnorInst::get_op_type() const {
    return OpType::FETCH_XNOR;
}
std::string IntFetchXnorInst::to_string() const {
    return this->to_string_helper("int_fetch_xnor");
}


IntFetchShlInst::IntFetchShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, bool nuw, bool nsw)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, nuw, nsw, false, false){}
FetchBitwiseBinInst::OpType IntFetchShlInst::get_op_type() const {
    return OpType::FETCH_SHL;
}
std::string IntFetchShlInst::to_string() const {
    return this->to_string_helper("int_fetch_shl");
}

IntFetchLshrInst::IntFetchLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, bool exact)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, exact, false){}
FetchBitwiseBinInst::OpType IntFetchLshrInst::get_op_type() const {
    return OpType::FETCH_LSHR;
}
std::string IntFetchLshrInst::to_string() const {
    return this->to_string_helper("int_fetch_lshr");
}


IntFetchAshrInst::IntFetchAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info, bool exact)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, exact, false){}
FetchBitwiseBinInst::OpType IntFetchAshrInst::get_op_type() const {
    return OpType::FETCH_ASHR;
}
std::string IntFetchAshrInst::to_string() const {
    return this->to_string_helper("int_fetch_ashr");
}


IntFetchRotlInst::IntFetchRotlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchRotlInst::get_op_type() const {
    return OpType::FETCH_ROTL;
}
std::string IntFetchRotlInst::to_string() const {
    return this->to_string_helper("int_fetch_rotl");
}


IntFetchRotrInst::IntFetchRotrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info)
                    :IntFetchBitwiseBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, false){}
FetchBitwiseBinInst::OpType IntFetchRotrInst::get_op_type() const {
    return OpType::FETCH_ROTR;
}
std::string IntFetchRotrInst::to_string() const {
    return this->to_string_helper("int_fetch_rotr");
}
}
}