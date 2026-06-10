#include "mir/instruction.hpp"
#include <memory>

namespace LIRA {
namespace MIR {
AtomicRMWInst::AtomicRMWInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                             IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering):Inst(instruction_stmt, destination){
    this->pointer = pointer;
    this->value = value;
    this->type = type;
    this->alignment = alignment;
    this->volatile_ = volatile_;
    this->syncscope = syncscope;
    this->ordering = ordering;
}

IR::TypeExprPtr AtomicRMWInst::get_type() const{
    return this->type;
}
IR::LiteralExprPtr AtomicRMWInst::get_pointer() const{
    return this->pointer;
}
IR::LiteralExprPtr AtomicRMWInst::get_value() const{
    return this->value;
}
std::size_t AtomicRMWInst::get_alignment() const{
    return this->alignment;
}
bool AtomicRMWInst::is_volatile() const{
    return this->volatile_;
}
SyncScope AtomicRMWInst::get_sync_scope() const{
    return this->syncscope;
}
AtomicOrdering AtomicRMWInst::get_ordering() const{
    return this->ordering;
}
InstType AtomicRMWInst::get_inst_type() const{
    return InstType::AtomicRMWInst;
}


// --------------------------- Integer Atomic read modify operations ---------------------------
IntAtomicRMWInst::IntAtomicRMWInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering, bool unsigned_)
                                        :AtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering){
    this->unsigned_ = unsigned_;
}
std::shared_ptr<IR::IntTypeExpr> IntAtomicRMWInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->type);
}
std::size_t IntAtomicRMWInst::get_bit_width() const{
    return this->get_casted_type()->get_bits();
}
InstOperandTypeVarient IntAtomicRMWInst::get_type_varient() const{
    return InstOperandTypeVarient::Int;
}


IntAtomicXchgInst::IntAtomicXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, false){}
AtomicRMWInst::OpType IntAtomicXchgInst::get_op_type() const{
    return OpType::XCHG;
}
std::string IntAtomicXchgInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_xchg(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


IntAtomicFetchAddInst::IntAtomicFetchAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, false){}
AtomicRMWInst::OpType IntAtomicFetchAddInst::get_op_type() const{
    return OpType::FETCH_ADD;
}
std::string IntAtomicFetchAddInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_fetchadd(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


IntAtomicFetchSubInst::IntAtomicFetchSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, false){}
AtomicRMWInst::OpType IntAtomicFetchSubInst::get_op_type() const{
    return OpType::FETCH_SUB;
}
std::string IntAtomicFetchSubInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_fetchsub(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


IntAtomicFetchAndInst::IntAtomicFetchAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, false){}
AtomicRMWInst::OpType IntAtomicFetchAndInst::get_op_type() const{
    return OpType::FETCH_AND;
}
std::string IntAtomicFetchAndInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_fetchand(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


IntAtomicFetchNandInst::IntAtomicFetchNandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, false){}
AtomicRMWInst::OpType IntAtomicFetchNandInst::get_op_type() const{
    return OpType::FETCH_NAND;
}
std::string IntAtomicFetchNandInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_fetchnand(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


IntAtomicFetchOrInst::IntAtomicFetchOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, false){}
AtomicRMWInst::OpType IntAtomicFetchOrInst::get_op_type() const{
    return OpType::FETCH_OR;    
}
std::string IntAtomicFetchOrInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_fetchor(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


IntAtomicFetchXorInst::IntAtomicFetchXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, false){}
AtomicRMWInst::OpType IntAtomicFetchXorInst::get_op_type() const{
    return OpType::FETCH_XOR;
}
std::string IntAtomicFetchXorInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_fetchxor(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


IntAtomicFetchMinInst::IntAtomicFetchMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering, bool unsigned_)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, unsigned_){}
AtomicRMWInst::OpType IntAtomicFetchMinInst::get_op_type() const{
    return OpType::FETCH_MIN;
}
std::string IntAtomicFetchMinInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_fetchmin(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    if(this->unsigned_){
        result += " #[unsigned]";
    }
    return result;
}


IntAtomicFetchMaxInst::IntAtomicFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering, bool unsigned_)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, unsigned_){}
AtomicRMWInst::OpType IntAtomicFetchMaxInst::get_op_type() const{
    return OpType::FETCH_MAX;
}
std::string IntAtomicFetchMaxInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_fetchmax(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    if(this->unsigned_){
        result += " #[unsigned]";
    }
    return result;
}


IntAtomicUincWrapInst::IntAtomicUincWrapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, false){}
AtomicRMWInst::OpType IntAtomicUincWrapInst::get_op_type() const{
    return OpType::UINC_WRAP;
}
std::string IntAtomicUincWrapInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_uinc_wrap(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


IntAtomicIdecWrapInst::IntAtomicIdecWrapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :IntAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering, false){}
AtomicRMWInst::OpType IntAtomicIdecWrapInst::get_op_type() const{
    return OpType::IDEC_WRAP;
}
std::string IntAtomicIdecWrapInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .int_atomic_idec_wrap(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


// --------------------------- Float Atomic read modify operations ---------------------------
FloatAtomicRMWInst::FloatAtomicRMWInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                                        :AtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering){}
std::shared_ptr<IR::FloatTypeExpr> FloatAtomicRMWInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->type);
}
std::size_t FloatAtomicRMWInst::get_bit_width() const{
    return this->get_casted_type()->get_bits();
}
bool FloatAtomicRMWInst::is_brain_float() const{
    return this->get_casted_type()->is_brain_float();
}
InstOperandTypeVarient FloatAtomicRMWInst::get_type_varient() const{
    return InstOperandTypeVarient::Float;
}


FloatAtomicXchgInst::FloatAtomicXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :FloatAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering){}
AtomicRMWInst::OpType FloatAtomicXchgInst::get_op_type() const{
    return OpType::XCHG;
}
std::string FloatAtomicXchgInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .float_atomic_xchg(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


FloatAtomicFetchAddInst::FloatAtomicFetchAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :FloatAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering){}
AtomicRMWInst::OpType FloatAtomicFetchAddInst::get_op_type() const{
    return OpType::FETCH_ADD;
}
std::string FloatAtomicFetchAddInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .float_atomic_fetchadd(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


FloatAtomicFetchSubInst::FloatAtomicFetchSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :FloatAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering){}
AtomicRMWInst::OpType FloatAtomicFetchSubInst::get_op_type() const{
    return OpType::FETCH_SUB;
}
std::string FloatAtomicFetchSubInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .float_atomic_fetchsub(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


FloatAtomicFetchMaxInst::FloatAtomicFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :FloatAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering){}
AtomicRMWInst::OpType FloatAtomicFetchMaxInst::get_op_type() const{
    return OpType::FETCH_MAX;
}
std::string FloatAtomicFetchMaxInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .float_atomic_fetchmax(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}


FloatAtomicFetchMinInst::FloatAtomicFetchMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering)
                        :FloatAtomicRMWInst(instruction_stmt, destination, pointer, value, type, alignment, volatile_, syncscope, ordering){}
AtomicRMWInst::OpType FloatAtomicFetchMinInst::get_op_type() const{
    return OpType::FETCH_MIN;
}
std::string FloatAtomicFetchMinInst::to_string() const{
    std::string result ="let " + this->get_destination()->to_string() + " = .float_atomic_fetchmin(ptr:" + this->pointer->to_string() + ", " + this->type->to_string() + " : " + this->value->to_string() + ")";
    result += " #[ordering(" + MIR::to_string(this->ordering) + ")]";
    result += " #[syncscope(" + MIR::to_string(this->syncscope) + ")]";
    result += " #[align(" + std::to_string(this->alignment) + ")]";
    if(this->volatile_){
        result += "#[volatile]";
    }
    return result;
}
}
}