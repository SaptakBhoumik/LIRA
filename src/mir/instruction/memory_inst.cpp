#include "mir/instruction/memory_inst.hpp"

namespace LIRA {
namespace MIR {
//--------------------------------- Uncategorized Memory Instructions ---------------------------------
LocalInst::LocalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, std::size_t alignment,
                     std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt,destination,fast_math_attr){
    this->value = value;
    this->alignment = alignment;
}
IR::LiteralExprPtr LocalInst::get_value() const{
    return this->value;
}
IR::TypeExprPtr LocalInst::get_type() const{
    return this->destination->get_type();
}
std::size_t LocalInst::get_alignment() const{
    return this->alignment;
}
InstType LocalInst::get_inst_type() const{
    return InstType::LocalInst;
}
std::string LocalInst::to_string() const{
    return "let " + this->destination->to_string() + " = .local(" + this->value->to_string() + ")" 
                  + (this->alignment != 0 ? " #[align(" + std::to_string(this->alignment) + ")]" : "")
                  + (this->fast_math_attr.has_value() ? " " + this->fast_math_attr.value().to_string() : "");
}


AllocaInst::AllocaInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,IR::LiteralExprPtr size, std::size_t alignment)
                       :Inst(instruction_stmt,destination,std::nullopt){
    this->size = size;
    this->alignment = alignment;
}
IR::LiteralExprPtr AllocaInst::get_size() const{
    return this->size;
}
std::size_t AllocaInst::get_alignment() const{
    return this->alignment;
}
InstType AllocaInst::get_inst_type() const{
    return InstType::AllocaInst;
}
std::string AllocaInst::to_string() const{
    std::string str = "let " + this->destination->to_string() + " = .alloca(i64:" + this->size->to_string() + ")";
    if(this->alignment != 0){
        str += " #[align(" + std::to_string(this->alignment)+")]";
    }
    return str;
}


LoadInst::LoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, 
             bool volatile_, bool invariant_load, bool nontemporal, bool nonull, bool nopoison, 
             std::size_t alignment, std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info)
             :Inst(instruction_stmt,destination,fast_math_attr){
    this->pointer = pointer;
    this->volatile_ = volatile_;
    this->invariant_load = invariant_load;
    this->nontemporal = nontemporal;
    this->nonull = nonull;
    this->nopoison = nopoison;
    this->alignment = alignment;
    this->dereferenceable_bytes = dereferenceable_bytes;
    this->atomic_info = atomic_info;
}
IR::LiteralExprPtr LoadInst::get_pointer() const{
    return this->pointer;
}
IR::TypeExprPtr LoadInst::get_type() const{
    return this->destination->get_type();
}
bool LoadInst::is_volatile() const{
    return this->volatile_;
}
bool LoadInst::is_invariant_load() const{
    return this->invariant_load;
}
bool LoadInst::is_nontemporal() const{
    return this->nontemporal;
}
bool LoadInst::is_nonull() const{
    return this->nonull;
}
bool LoadInst::is_nopoison() const{
    return this->nopoison;
}
bool LoadInst::is_nsb() const{
    return this->nsb;
}
std::size_t LoadInst::get_alignment() const{
    return this->alignment;
}
std::size_t LoadInst::get_dereferenceable_bytes() const{
    return this->dereferenceable_bytes;
}
std::optional<std::pair<AtomicOrdering,SyncScope>> LoadInst::get_atomic_info() const{
    return this->atomic_info;
}
InstType LoadInst::get_inst_type() const{
    return InstType::LoadInst;
}
std::string LoadInst::to_string() const{
    std::string str = "let " + this->destination->to_string() + " = .load(ptr:" + this->pointer->to_string() + ")";
    if(this->volatile_){
        str += " #[volatile]";
    }
    if(this->invariant_load){
        str += " #[invariant.load]";
    }
    if(this->nontemporal){
        str += " #[nontemporal]";
    }
    if(this->nonull){
        str += " #[nonnull]";
    }   
    if(this->nopoison){
        str += " #[nopoison]";
    }
    if(this->alignment != 0){
        str += " #[align(" + std::to_string(this->alignment)+")]";
    }
    if(this->dereferenceable_bytes != 0){
        str += " #[dereferenceable(" + std::to_string(this->dereferenceable_bytes)+")]";
    }
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    if(this->atomic_info.has_value()){
        str += " #[atomic(" + MIR::to_string(this->atomic_info.value().first) + ")]"
                + " #[syncscope(" + MIR::to_string(this->atomic_info.value().second) + ")]";
    }
    return str;
}

StoreInst::StoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, IR::TypeExprPtr type, 
                     bool volatile_, bool nontemporal, bool nonull, bool nopoison, 
                     std::size_t alignment, std::size_t dereferenceable_bytes,std::optional<FastMathAttr> fast_math_attr, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info)
                     :Inst(instruction_stmt,nullptr,fast_math_attr){
    this->pointer = pointer;
    this->value = value;
    this->type = type;
    this->volatile_ = volatile_;
    this->nontemporal = nontemporal;
    this->nonull = nonull;
    this->nopoison = nopoison;
    this->alignment = alignment;
    this->dereferenceable_bytes = dereferenceable_bytes;
    this->atomic_info = atomic_info;
};
IR::LiteralExprPtr StoreInst::get_pointer() const{
    return this->pointer;
}
IR::LiteralExprPtr StoreInst::get_value() const{
    return this->value;
}
IR::TypeExprPtr StoreInst::get_type() const{
    return this->type;
}
bool StoreInst::is_volatile() const{
    return this->volatile_;
}
bool StoreInst::is_nontemporal() const{
    return this->nontemporal;
}
bool StoreInst::is_nonull() const{
    return this->nonull;
}
bool StoreInst::is_nopoison() const{
    return this->nopoison;
}
std::size_t StoreInst::get_alignment() const{
    return this->alignment;
}
std::size_t StoreInst::get_dereferenceable_bytes() const{
    return this->dereferenceable_bytes;
}
std::optional<std::pair<AtomicOrdering,SyncScope>> StoreInst::get_atomic_info() const{
    return this->atomic_info;
}
InstType StoreInst::get_inst_type() const{
    return InstType::StoreInst;
}
std::string StoreInst::to_string() const{
    std::string str = ".store(" + this->type->to_string() + ":" + this->value->to_string() + ", ptr:" + this->pointer->to_string() + ")";
    if(this->volatile_){
        str += " #[volatile]";
    }
    if(this->nontemporal){
        str += " #[nontemporal]";
    }
    if(this->nonull){
        str += " #[nonnull]";
    }
    if(this->nopoison){
        str += " #[nopoison]";
    }
    if(this->alignment != 0){
        str += " #[align(" + std::to_string(this->alignment)+")]";
    }
    if(this->dereferenceable_bytes != 0){
        str += " #[dereferenceable(" + std::to_string(this->dereferenceable_bytes)+")]";
    }
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    if(this->atomic_info.has_value()){
        str += " #[atomic(" + MIR::to_string(this->atomic_info.value().first) + ")]"
                + " #[syncscope(" + MIR::to_string(this->atomic_info.value().second) + ")]";
    }
    return str;
};


BroadcastLoadInst::BroadcastLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, 
                      bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                      std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr)
                      :Inst(instruction_stmt,destination,fast_math_attr){
    this->src = src;
    this->volatile_ = volatile_;
    this->nontemporal = nontemporal;
    this->nonull = nonull;
    this->alignment = alignment;
    this->dereferenceable_bytes = dereferenceable_bytes;
};
std::string BroadcastLoadInst::to_string_helper(const std::string op_name) const{
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(ptr:" + this->src->to_string() + ")";
    if(this->volatile_){
        str += " #[volatile]";
    }
    if(this->nontemporal){
        str += " #[nontemporal]";
    }
    if(this->nonull){
        str += " #[nonnull]";
    }
    if(this->alignment != 0){
        str += " #[align(" + std::to_string(this->alignment)+")]";
    }
    if(this->dereferenceable_bytes != 0){
        str += " #[dereferenceable(" + std::to_string(this->dereferenceable_bytes)+")]";
    }
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr BroadcastLoadInst::get_pointer() const{
    return this->src;
}
IR::TypeExprPtr BroadcastLoadInst::get_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::shared_ptr<IR::SIMDTypeExpr> BroadcastLoadInst::get_casted_vector_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::size_t BroadcastLoadInst::get_vector_size() const{
    return this->get_casted_vector_type()->get_size();
}
bool BroadcastLoadInst::is_volatile() const{
    return this->volatile_;
}
bool BroadcastLoadInst::is_nontemporal() const{
    return this->nontemporal;
}
bool BroadcastLoadInst::is_nonull() const{
    return this->nonull;
}
std::size_t BroadcastLoadInst::get_alignment() const{
    return this->alignment;
}
std::size_t BroadcastLoadInst::get_dereferenceable_bytes() const{
    return this->dereferenceable_bytes;
}
InstType BroadcastLoadInst::get_inst_type() const{
    return InstType::BroadcastLoadInst;
}


IntBroadcastLoadInst::IntBroadcastLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, 
                         bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                         std::size_t dereferenceable_bytes)
                         :BroadcastLoadInst(instruction_stmt,destination,src,volatile_,nontemporal,nonull,alignment,dereferenceable_bytes,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntBroadcastLoadInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntBroadcastLoadInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntBroadcastLoadInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntBroadcastLoadInst::to_string() const{
    return this->to_string_helper("int_broadcast_load");
}


PtrBroadcastLoadInst::PtrBroadcastLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, 
                         bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                         std::size_t dereferenceable_bytes)
                         :BroadcastLoadInst(instruction_stmt,destination,src,volatile_,nontemporal,nonull,alignment,dereferenceable_bytes,std::nullopt){}
std::size_t PtrBroadcastLoadInst::get_element_bitwidth() const{
    return 64; //Assuming 64 bit pointers
}
TypeVariant PtrBroadcastLoadInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrBroadcastLoadInst::to_string() const{
    return this->to_string_helper("ptr_broadcast_load");
}


FloatBroadcastLoadInst::FloatBroadcastLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, 
                           bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                           std::size_t dereferenceable_bytes, FastMathAttr fast_math_attr)
                           :BroadcastLoadInst(instruction_stmt,destination,src,volatile_,nontemporal,nonull,alignment,dereferenceable_bytes,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatBroadcastLoadInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatBroadcastLoadInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatBroadcastLoadInst::is_element_brain_float() const{
    return this->get_casted_element_type()->is_brain_float();
}
TypeVariant FloatBroadcastLoadInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatBroadcastLoadInst::to_string() const{
    return this->to_string_helper("float_broadcast_load");
}


MaskedLoadInst::MaskedLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask, 
                    IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                    std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr)
                    :Inst(instruction_stmt,destination,fast_math_attr){
    this->pointer = pointer;
    this->mask = mask;
    this->passthru = passthru;
    this->volatile_ = volatile_;
    this->nontemporal = nontemporal;
    this->nonull = nonull;
    this->zeropassthru = zeropassthru;
    this->alignment = alignment;
    this->dereferenceable_bytes = dereferenceable_bytes;
};
std::string MaskedLoadInst::to_string_helper(std::string opname) const{
    std::string str = "let " + this->destination->to_string() + " = ." + opname + "(ptr:" + this->pointer->to_string();
    if(this->mask != nullptr){
        str +=  ", <i1," + std::to_string(this->get_vector_size()) + ">:" + this->mask->to_string(); 
    }
    if(this->passthru != nullptr){
        str +=  ", <" + this->get_element_type()->to_string() + "," + std::to_string(this->get_vector_size()) + ">:" + this->passthru->to_string(); 
    }
    str+= ")";
    if(this->volatile_){
        str += " #[volatile]";
    }
    if(this->nontemporal){
        str += " #[nontemporal]";
    }
    if(this->nonull){
        str += " #[nonnull]";
    }
    if(this->zeropassthru){
        str += " #[zeropassthru]";
    }
    if(this->alignment != 0){
        str += " #[align(" + std::to_string(this->alignment)+")]";
    }
    if(this->dereferenceable_bytes != 0){
        str += " #[dereferenceable(" + std::to_string(this->dereferenceable_bytes)+")]";
    }
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr MaskedLoadInst::get_pointer() const{
    return this->pointer;
}
IR::LiteralExprPtr MaskedLoadInst::get_mask() const{
    return this->mask;
}
IR::LiteralExprPtr MaskedLoadInst::get_passthru() const{
    return this->passthru;
}
IR::TypeExprPtr MaskedLoadInst::get_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::shared_ptr<IR::SIMDTypeExpr> MaskedLoadInst::get_casted_vector_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::size_t MaskedLoadInst::get_vector_size() const{
    return this->get_casted_vector_type()->get_size();
}
bool MaskedLoadInst::is_volatile() const{
    return this->volatile_;
}
bool MaskedLoadInst::is_nontemporal() const{
    return this->nontemporal;
}
bool MaskedLoadInst::is_nonull() const{
    return this->nonull;
}
bool MaskedLoadInst::is_zeropassthru() const{
    return this->zeropassthru;
}
std::size_t MaskedLoadInst::get_alignment() const{
    return this->alignment;
}
std::size_t MaskedLoadInst::get_dereferenceable_bytes() const{
    return this->dereferenceable_bytes;
}
InstType MaskedLoadInst::get_inst_type() const{
    return InstType::MaskedLoadInst;
}

IntMaskedLoadInst::IntMaskedLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask, 
                    IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                    std::size_t dereferenceable_bytes)
                    :MaskedLoadInst(instruction_stmt,destination,pointer,mask,passthru,volatile_,nontemporal,nonull,zeropassthru,alignment,dereferenceable_bytes,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntMaskedLoadInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntMaskedLoadInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntMaskedLoadInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntMaskedLoadInst::to_string() const{
    return this->to_string_helper("int_masked_load");
}


PtrMaskedLoadInst::PtrMaskedLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask, 
                    IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                    std::size_t dereferenceable_bytes)
                    :MaskedLoadInst(instruction_stmt,destination,pointer,mask,passthru,volatile_,nontemporal,nonull,zeropassthru,alignment,dereferenceable_bytes,std::nullopt){}
std::size_t PtrMaskedLoadInst::get_element_bitwidth() const{
    return 64; //Assuming 64 bit pointers
}
TypeVariant PtrMaskedLoadInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrMaskedLoadInst::to_string() const{
    return this->to_string_helper("ptr_masked_load");
}


FloatMaskedLoadInst::FloatMaskedLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask, 
                    IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                    std::size_t dereferenceable_bytes, FastMathAttr fast_math_attr)
                    :MaskedLoadInst(instruction_stmt,destination,pointer,mask,passthru,volatile_,nontemporal,nonull,zeropassthru,alignment,dereferenceable_bytes,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatMaskedLoadInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatMaskedLoadInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatMaskedLoadInst::is_element_brain_float() const{
    return this->get_casted_element_type()->is_brain_float();
}
TypeVariant FloatMaskedLoadInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatMaskedLoadInst::to_string() const{
    return this->to_string_helper("float_masked_load");
}


MaskedStoreInst::MaskedStoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                                 IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                                 std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr)
                                 :Inst(instruction_stmt,nullptr,fast_math_attr){
    this->pointer = pointer;
    this->value = value;
    this->value_type = value_type;
    this->mask = mask;
    this->volatile_ = volatile_;
    this->nontemporal = nontemporal;
    this->nonull = nonull;
    this->alignment = alignment;
    this->dereferenceable_bytes = dereferenceable_bytes;
}
std::string MaskedStoreInst::to_string_helper(std::string opname) const{
    std::string str = "." + opname + "(" + this->value_type->to_string() + ":" + this->value->to_string() + ", ptr:" + this->pointer->to_string();
    if(this->mask != nullptr){
        str +=  ", <i1," + std::to_string(this->get_vector_size()) + ">:" + this->mask->to_string(); 
    }
    str+= ")";
    if(this->volatile_){
        str += " #[volatile]";
    }
    if(this->nontemporal){
        str += " #[nontemporal]";
    }
    if(this->nonull){
        str += " #[nonnull]";
    }
    if(this->alignment != 0){
        str += " #[align(" + std::to_string(this->alignment)+")]";
    }
    if(this->dereferenceable_bytes != 0){
        str += " #[dereferenceable(" + std::to_string(this->dereferenceable_bytes)+")]";
    }
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr MaskedStoreInst::get_pointer() const{
    return this->pointer;
}
IR::LiteralExprPtr MaskedStoreInst::get_value() const{
    return this->value;
}
IR::LiteralExprPtr MaskedStoreInst::get_mask() const{
    return this->mask;
}
std::shared_ptr<IR::SIMDTypeExpr> MaskedStoreInst::get_casted_value_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->value_type);
}
IR::TypeExprPtr MaskedStoreInst::get_value_basetype() const{
    return this->get_casted_value_type()->get_basetype();
}
std::size_t MaskedStoreInst::get_vector_size() const{
    return this->get_casted_value_type()->get_size();
}
bool MaskedStoreInst::is_volatile() const{
    return this->volatile_;
}
bool MaskedStoreInst::is_nontemporal() const{
    return this->nontemporal;
}
bool MaskedStoreInst::is_nonull() const{
    return this->nonull;
}
std::size_t MaskedStoreInst::get_alignment() const{
    return this->alignment;
}
std::size_t MaskedStoreInst::get_dereferenceable_bytes() const{
    return this->dereferenceable_bytes;
}
InstType MaskedStoreInst::get_inst_type() const{
    return InstType::MaskedStoreInst;
}


IntMaskedStoreInst::IntMaskedStoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                       IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                       std::size_t dereferenceable_bytes)
                       :MaskedStoreInst(instruction_stmt,pointer,value,value_type,mask,volatile_,nontemporal,nonull,alignment,dereferenceable_bytes,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntMaskedStoreInst::get_casted_value_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_value_basetype());
}
std::size_t IntMaskedStoreInst::get_value_basetype_bitwidth() const{
    return this->get_casted_value_basetype()->get_bits();
}
TypeVariant IntMaskedStoreInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntMaskedStoreInst::to_string() const{
    return this->to_string_helper("int_masked_store");  
}


PtrMaskedStoreInst::PtrMaskedStoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                       IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                       std::size_t dereferenceable_bytes)
                       :MaskedStoreInst(instruction_stmt,pointer,value,value_type,mask,volatile_,nontemporal,nonull,alignment,dereferenceable_bytes,std::nullopt){}
std::size_t PtrMaskedStoreInst::get_value_basetype_bitwidth() const{
    return 64; //Assuming 64 bit pointers
}
TypeVariant PtrMaskedStoreInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrMaskedStoreInst::to_string() const{
    return this->to_string_helper("ptr_masked_store");  
}


FloatMaskedStoreInst::FloatMaskedStoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                         IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                         std::size_t dereferenceable_bytes, FastMathAttr fast_math_attr)
                         :MaskedStoreInst(instruction_stmt,pointer,value,value_type,mask,volatile_,nontemporal,nonull,alignment,dereferenceable_bytes,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatMaskedStoreInst::get_casted_value_basetype() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_value_basetype());
}
std::size_t FloatMaskedStoreInst::get_value_basetype_bitwidth() const{
    return this->get_casted_value_basetype()->get_bits();
}
bool FloatMaskedStoreInst::is_element_brain_float() const{
    return this->get_casted_value_basetype()->is_brain_float();
}
TypeVariant FloatMaskedStoreInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatMaskedStoreInst::to_string() const{
    return this->to_string_helper("float_masked_store");
}


MaskedGatherInst::MaskedGatherInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr mask, 
                                   IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                                   std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr)
                                   :Inst(instruction_stmt,destination,fast_math_attr){
    this->vec_of_ptrs = vec_of_ptrs;
    this->mask = mask;
    this->passthru = passthru;
    this->volatile_ = volatile_;
    this->nontemporal = nontemporal;
    this->nonull = nonull;
    this->zeropassthru = zeropassthru;
    this->alignment = alignment;
    this->dereferenceable_bytes = dereferenceable_bytes;    
}
std::string MaskedGatherInst::to_string_helper(std::string opname) const{
    std::string str = "let " + this->destination->to_string() + " = ." + opname + "(<ptr," + std::to_string(this->get_vector_size()) + ">:" + this->vec_of_ptrs->to_string();
    if(this->mask != nullptr){
        str +=  ", <i1," + std::to_string(this->get_vector_size()) + ">:" + this->mask->to_string(); 
    }
    if(this->passthru != nullptr){
        str +=  ", <" + this->get_element_type()->to_string() + "," + std::to_string(this->get_vector_size()) + ">:" + this->passthru->to_string(); 
    }
    str+= ")";
    if(this->volatile_){
        str += " #[volatile]";
    }
    if(this->nontemporal){
        str += " #[nontemporal]";
    }
    if(this->nonull){
        str += " #[nonnull]";
    }
    if(this->zeropassthru){
        str += " #[zeropassthru]";
    }
    if(this->alignment != 0){
        str += " #[align(" + std::to_string(this->alignment)+")]";
    }
    if(this->dereferenceable_bytes != 0){
        str += " #[dereferenceable(" + std::to_string(this->dereferenceable_bytes)+")]";
    }
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr MaskedGatherInst::get_vec_of_ptrs() const{
    return this->vec_of_ptrs;
}
IR::LiteralExprPtr MaskedGatherInst::get_mask() const{
    return this->mask;
}
IR::LiteralExprPtr MaskedGatherInst::get_passthru() const{
    return this->passthru;
}
IR::TypeExprPtr MaskedGatherInst::get_element_type() const{
    return this->get_casted_vector_type()->get_basetype();
}
std::shared_ptr<IR::SIMDTypeExpr> MaskedGatherInst::get_casted_vector_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::size_t MaskedGatherInst::get_vector_size() const{
    return this->get_casted_vector_type()->get_size();
}
bool MaskedGatherInst::is_volatile() const{
    return this->volatile_;
}
bool MaskedGatherInst::is_nontemporal() const{
    return this->nontemporal;
}
bool MaskedGatherInst::is_nonull() const{
    return this->nonull;
}
bool MaskedGatherInst::is_zeropassthru() const{
    return this->zeropassthru;
}
std::size_t MaskedGatherInst::get_alignment() const{
    return this->alignment;
}
std::size_t MaskedGatherInst::get_dereferenceable_bytes() const{
    return this->dereferenceable_bytes;
}
InstType MaskedGatherInst::get_inst_type() const{
    return InstType::MaskedGatherInst;
}


IntMaskedGatherInst::IntMaskedGatherInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr mask, 
                                   IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                                   std::size_t dereferenceable_bytes)
                                   :MaskedGatherInst(instruction_stmt,destination,vec_of_ptrs,mask,passthru,volatile_,nontemporal,nonull,zeropassthru,alignment,dereferenceable_bytes,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntMaskedGatherInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntMaskedGatherInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntMaskedGatherInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntMaskedGatherInst::to_string() const{
    return this->to_string_helper("int_masked_gather");
}


PtrMaskedGatherInst::PtrMaskedGatherInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr mask, 
                                   IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                                   std::size_t dereferenceable_bytes)
                                   :MaskedGatherInst(instruction_stmt,destination,vec_of_ptrs,mask,passthru,volatile_,nontemporal,nonull,zeropassthru,alignment,dereferenceable_bytes,std::nullopt){}
std::size_t PtrMaskedGatherInst::get_element_bitwidth() const{
    return 64; //Assuming 64 bit pointers
}
TypeVariant PtrMaskedGatherInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrMaskedGatherInst::to_string() const{
    return this->to_string_helper("ptr_masked_gather");
}


FloatMaskedGatherInst::FloatMaskedGatherInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr mask, 
                                   IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                                   std::size_t dereferenceable_bytes, FastMathAttr fast_math_attr)
                                   :MaskedGatherInst(instruction_stmt,destination,vec_of_ptrs,mask,passthru,volatile_,nontemporal,nonull,zeropassthru,alignment,dereferenceable_bytes,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatMaskedGatherInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatMaskedGatherInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatMaskedGatherInst::is_element_brain_float() const{
    return this->get_casted_element_type()->is_brain_float();
}
TypeVariant FloatMaskedGatherInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatMaskedGatherInst::to_string() const{
    return this->to_string_helper("float_masked_gather");
}


MaskedScatterInst::MaskedScatterInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr value, 
                                     IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                                     std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr)
                                     :Inst(instruction_stmt,nullptr,fast_math_attr){
    this->vec_of_ptrs = vec_of_ptrs;
    this->value = value;
    this->value_type = value_type;
    this->mask = mask;
    this->volatile_ = volatile_;
    this->nontemporal = nontemporal;
    this->nonull = nonull;
    this->alignment = alignment;
    this->dereferenceable_bytes = dereferenceable_bytes;
}
std::string MaskedScatterInst::to_string_helper(std::string opname) const{
    std::string str = "." + opname + "(<ptr," + std::to_string(this->get_vector_size()) + ">:" + this->vec_of_ptrs->to_string() + ", " + this->value_type->to_string() + ":" + this->value->to_string();
    if(this->mask != nullptr){
        str +=  ", <i1," + std::to_string(this->get_vector_size()) + ">:" + this->mask->to_string(); 
    }
    str+= ")";
    if(this->volatile_){
        str += " #[volatile]";
    }
    if(this->nontemporal){
        str += " #[nontemporal]";
    }
    if(this->nonull){
        str += " #[nonnull]";
    }
    if(this->alignment != 0){
        str += " #[align(" + std::to_string(this->alignment)+")]";
    }
    if(this->dereferenceable_bytes != 0){
        str += " #[dereferenceable(" + std::to_string(this->dereferenceable_bytes)+")]";
    }
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr MaskedScatterInst::get_vec_of_ptrs() const{
    return this->vec_of_ptrs;
}
IR::LiteralExprPtr MaskedScatterInst::get_value() const{
    return this->value;
}
IR::LiteralExprPtr MaskedScatterInst::get_mask() const{
    return this->mask;
}
std::shared_ptr<IR::SIMDTypeExpr> MaskedScatterInst::get_casted_value_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_value_basetype());
}
IR::TypeExprPtr MaskedScatterInst::get_value_basetype() const{
    return this->get_casted_value_type()->get_basetype();
}
std::size_t MaskedScatterInst::get_vector_size() const{
    return this->get_casted_value_type()->get_size();
}
bool MaskedScatterInst::is_volatile() const{
    return this->volatile_;
}
bool MaskedScatterInst::is_nontemporal() const{
    return this->nontemporal;
}
bool MaskedScatterInst::is_nonull() const{
    return this->nonull;
}
std::size_t MaskedScatterInst::get_alignment() const{
    return this->alignment;
}
std::size_t MaskedScatterInst::get_dereferenceable_bytes() const{
    return this->dereferenceable_bytes;
}
InstType MaskedScatterInst::get_inst_type() const{
    return InstType::MaskedScatterInst;
}


IntMaskedScatterInst::IntMaskedScatterInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr value, 
                                     IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                                     std::size_t dereferenceable_bytes)
                                     :MaskedScatterInst(instruction_stmt,vec_of_ptrs,value,value_type,mask,volatile_,nontemporal,nonull,alignment,dereferenceable_bytes,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntMaskedScatterInst::get_casted_value_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_value_basetype());
}
std::size_t IntMaskedScatterInst::get_value_basetype_bitwidth() const{
    return this->get_casted_value_basetype()->get_bits();
}
TypeVariant IntMaskedScatterInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntMaskedScatterInst::to_string() const{
    return this->to_string_helper("int_masked_scatter");
}


PtrMaskedScatterInst::PtrMaskedScatterInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr value, 
                                     IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                                     std::size_t dereferenceable_bytes)
                                     :MaskedScatterInst(instruction_stmt,vec_of_ptrs,value,value_type,mask,volatile_,nontemporal,nonull,alignment,dereferenceable_bytes,std::nullopt){}
std::size_t PtrMaskedScatterInst::get_value_basetype_bitwidth() const{
    return 64; //Assuming 64 bit pointers
}
TypeVariant PtrMaskedScatterInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrMaskedScatterInst::to_string() const{
    return this->to_string_helper("ptr_masked_scatter");
}


FloatMaskedScatterInst::FloatMaskedScatterInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr value, 
                                     IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                                     std::size_t dereferenceable_bytes, FastMathAttr fast_math_attr)
                                     :MaskedScatterInst(instruction_stmt,vec_of_ptrs,value,value_type,mask,volatile_,nontemporal,nonull,alignment,dereferenceable_bytes,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatMaskedScatterInst::get_casted_value_basetype() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_value_basetype());
}
std::size_t FloatMaskedScatterInst::get_value_basetype_bitwidth() const{
    return this->get_casted_value_basetype()->get_bits();
}
bool FloatMaskedScatterInst::is_element_brain_float() const{
    return this->get_casted_value_basetype()->is_brain_float();
}
TypeVariant FloatMaskedScatterInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatMaskedScatterInst::to_string() const{
    return this->to_string_helper("float_masked_scatter");
}


PrefetchInst::PrefetchInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, bool write, bool instruction, std::size_t prefetch_locality)
                            :Inst(instruction_stmt,nullptr,std::nullopt){
    this->pointer = pointer;
    this->write = write;
    this->instruction = instruction;
    this->prefetch_locality = prefetch_locality;
}
IR::LiteralExprPtr PrefetchInst::get_pointer() const{
    return this->pointer;
}
bool PrefetchInst::is_write() const{
    return this->write;
}
bool PrefetchInst::is_instruction() const{
    return this->instruction;
}
std::size_t PrefetchInst::get_prefetch_locality() const{
    return this->prefetch_locality;
}
InstType PrefetchInst::get_inst_type() const{
    return InstType::PrefetchInst;
}
std::string PrefetchInst::to_string() const{
    std::string str = ".prefetch(ptr:" + this->pointer->to_string() + ")";
    if(this->write){
        str += " #[write]";
    }
    if(this->instruction){
        str += " #[instruction]";
    }
    str+= " #[locality(i8" + std::to_string(this->prefetch_locality) + ")]";
    return str;
}


MemcopyInst::MemcopyInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr dest, IR::LiteralExprPtr src, 
                         IR::LiteralExprPtr size, bool nooverlap, bool volatile_, 
                         std::pair<bool,bool> nontemporal, std::pair<bool,bool> nonnull, std::pair<bool,bool> nopoison,
                         std::pair<size_t, size_t> alignment, std::pair<size_t, size_t> dereferenceable_bytes):
                         Inst(instruction_stmt,nullptr,std::nullopt){   
    this->dest = dest;
    this->src = src;
    this->size = size;
    this->nooverlap = nooverlap;
    this->volatile_ = volatile_;
    this->nontemporal = nontemporal;
    this->nonnull = nonnull;
    this->nopoison = nopoison;
    this->alignment = alignment;
    this->dereferenceable_bytes = dereferenceable_bytes;
}
IR::LiteralExprPtr MemcopyInst::get_dest() const{
    return this->dest;
}
IR::LiteralExprPtr MemcopyInst::get_src() const{
    return this->src;
}
IR::LiteralExprPtr MemcopyInst::get_size() const{
    return this->size;
}
bool MemcopyInst::is_nooverlap() const{
    return this->nooverlap;
}
bool MemcopyInst::is_volatile() const{
    return this->volatile_;
}
std::pair<bool,bool> MemcopyInst::is_nontemporal() const{
    return this->nontemporal;
}
std::pair<bool,bool> MemcopyInst::is_nonnull() const{
    return this->nonnull;
}
std::pair<bool,bool> MemcopyInst::is_nopoison() const{
    return this->nopoison;
}
std::pair<size_t, size_t> MemcopyInst::get_alignment() const{
    return this->alignment;
}
std::pair<size_t, size_t> MemcopyInst::get_dereferenceable_bytes() const{
    return this->dereferenceable_bytes;
}
InstType MemcopyInst::get_inst_type() const{
    return InstType::MemcopyInst;
}
std::string MemcopyInst::to_string() const{
    std::string str = ".memcopy(ptr:" + this->dest->to_string() + ", ptr:" + this->src->to_string() + ", i64:" + this->size->to_string() + ")";
    if(this->nooverlap){
        str += " #[nooverlap]";
    }
    if(this->volatile_){
        str += " #[volatile]";
    }
    str += " #[nontemporal(" + std::to_string(this->nontemporal.first) + "," + std::to_string(this->nontemporal.second) + ")]";
    str += " #[nonnull(" + std::to_string(this->nonnull.first) + "," + std::to_string(this->nonnull.second) + ")]";
    str += " #[nopoison(" + std::to_string(this->nopoison.first) + "," + std::to_string(this->nopoison.second) + ")]";
    str += " #[align(" + std::to_string(this->alignment.first) + "," + std::to_string(this->alignment.second) + ")]";
    str += " #[dereferenceable(" + std::to_string(this->dereferenceable_bytes.first) + "," + std::to_string(this->dereferenceable_bytes.second) + ")]";
    return str;
}


MemsetInst::MemsetInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr dest, IR::LiteralExprPtr value, 
                       IR::LiteralExprPtr size, bool volatile_, bool nontemporal, bool nonnull, bool nopoison,
                       std::size_t alignment, std::size_t dereferenceable_bytes):
                       Inst(instruction_stmt,nullptr,std::nullopt){
    this->dest = dest;
    this->value = value;
    this->size = size;
    this->volatile_ = volatile_;
    this->nontemporal = nontemporal;
    this->nonnull = nonnull;
    this->nopoison = nopoison;
    this->alignment = alignment;
    this->dereferenceable_bytes = dereferenceable_bytes;
};
IR::LiteralExprPtr MemsetInst::get_dest() const{
    return this->dest;
}
IR::LiteralExprPtr MemsetInst::get_value() const{
    return this->value;
}
IR::LiteralExprPtr MemsetInst::get_size() const{
    return this->size;
}
bool MemsetInst::is_volatile() const{
    return this->volatile_;
}
bool MemsetInst::is_nontemporal() const{
    return this->nontemporal;
}
bool MemsetInst::is_nonnull() const{
    return this->nonnull;
}
bool MemsetInst::is_nopoison() const{
    return this->nopoison;
}
std::size_t MemsetInst::get_alignment() const{
    return this->alignment;
}
std::size_t MemsetInst::get_dereferenceable_bytes() const{
    return this->dereferenceable_bytes;
}
InstType MemsetInst::get_inst_type() const{
    return InstType::MemsetInst;
}
std::string MemsetInst::to_string() const{
    std::string str = ".memset(ptr:" + this->dest->to_string() + ", i8:" + this->value->to_string() + ", i64:" + this->size->to_string() + ")";
    if(this->volatile_){
        str += " #[volatile]";
    }
    if(this->nontemporal){
        str += " #[nontemporal]";
    }
    if(this->nonnull){
        str += " #[nonnull]";
    }
    if(this->nopoison){
        str += " #[nopoison]";
    }
    if(this->alignment != 0){
        str += " #[align(" + std::to_string(this->alignment)+")]";
    }
    if(this->dereferenceable_bytes != 0){
        str += " #[dereferenceable(" + std::to_string(this->dereferenceable_bytes)+")]";
    }
    return str;
}


MemcmpInst::MemcmpInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr ptr1, IR::LiteralExprPtr ptr2, IR::LiteralExprPtr size, 
                       bool volatile_, std::pair<bool,bool> nontemporal, std::pair<bool,bool> nonnull, std::pair<bool,bool> nopoison, 
                       std::pair<size_t, size_t> alignment, std::pair<size_t, size_t> dereferenceable_bytes):
                       Inst(instruction_stmt,destination,std::nullopt){
    this->ptr1 = ptr1;
    this->ptr2 = ptr2;
    this->size = size;
    this->volatile_ = volatile_;
    this->nontemporal = nontemporal;
    this->nonnull = nonnull;
    this->nopoison = nopoison;
    this->alignment = alignment;
    this->dereferenceable_bytes = dereferenceable_bytes;
}
IR::LiteralExprPtr MemcmpInst::get_ptr1() const{
    return this->ptr1;
}
IR::LiteralExprPtr MemcmpInst::get_ptr2() const{
    return this->ptr2;
}
IR::LiteralExprPtr MemcmpInst::get_size() const{
    return this->size;
}
bool MemcmpInst::is_volatile() const{
    return this->volatile_;
}
std::pair<bool,bool> MemcmpInst::is_nontemporal() const{
    return this->nontemporal;
}
std::pair<bool,bool> MemcmpInst::is_nonnull() const{
    return this->nonnull;
}
std::pair<bool,bool> MemcmpInst::is_nopoison() const{
    return this->nopoison;
}
std::pair<size_t, size_t> MemcmpInst::get_alignment() const{
    return this->alignment;
}
std::pair<size_t, size_t> MemcmpInst::get_dereferenceable_bytes() const{
    return this->dereferenceable_bytes;
}
InstType MemcmpInst::get_inst_type() const{
    return InstType::MemcmpInst;
}
std::string MemcmpInst::to_string() const{
    std::string str = "let " + this->destination->to_string() + " = .memcmp(ptr:" + this->ptr1->to_string() + ", ptr:" + this->ptr2->to_string() + ", i64:" + this->size->to_string() + ")";
    if(this->volatile_){
        str += " #[volatile]";
    }
    str += " #[nontemporal(" + std::to_string(this->nontemporal.first) + "," + std::to_string(this->nontemporal.second) + ")]";
    str += " #[nonnull(" + std::to_string(this->nonnull.first) + "," + std::to_string(this->nonnull.second) + ")]";
    str += " #[nopoison(" + std::to_string(this->nopoison.first) + "," + std::to_string(this->nopoison.second) + ")]";
    str += " #[align(" + std::to_string(this->alignment.first) + "," + std::to_string(this->alignment.second) + ")]";
    str += " #[dereferenceable(" + std::to_string(this->dereferenceable_bytes.first) + "," + std::to_string(this->dereferenceable_bytes.second) + ")]";
    return str;
}


GetAddressInst::GetAddressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                               IR::LiteralExprPtr offset, bool unsigned_, bool nsw, bool nuw, bool inbounds, std::optional<FastMathAttr> fast_math_attr):
                               Inst(instruction_stmt,destination,fast_math_attr){
    this->value = value;
    this->value_type = value_type;
    this->offset = offset;
    this->unsigned_ = unsigned_;
    this->nsw = nsw;
    this->nuw = nuw;
    this->inbounds = inbounds;
}    
IR::LiteralExprPtr GetAddressInst::get_value() const{
    return this->value;
}
IR::TypeExprPtr GetAddressInst::get_value_type() const{
    return this->value_type;
}
IR::LiteralExprPtr GetAddressInst::get_offset() const{
    return this->offset;
}
bool GetAddressInst::is_unsigned() const{
    return this->unsigned_;
}
bool GetAddressInst::is_nsw() const{
    return this->nsw;
}
bool GetAddressInst::is_nuw() const{
    return this->nuw;
}
bool GetAddressInst::is_inbounds() const{
    return this->inbounds;
}
InstType GetAddressInst::get_inst_type() const{
    return InstType::GetAddressInst;
}
std::string GetAddressInst::to_string() const{
    std::string str = "let " + this->destination->to_string() + " = .getaddress(" + this->value_type->to_string() + ":" + this->value->to_string() + ", i64:" + this->offset->to_string() + ")";
    if(this->unsigned_){
        str += " #[unsigned]";
    }
    if(this->nsw){
        str += " #[nsw]";
    }
    if(this->nuw){
        str += " #[nuw]";
    }
    if(this->inbounds){
        str += " #[inbounds]";
    }
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}


PtrOffsetInst::PtrOffsetInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, 
                            IR::LiteralExprPtr offset, bool unsigned_, bool nsw, bool nuw, bool inbounds):Inst(instruction_stmt,destination,std::nullopt){
    this->pointer = pointer;
    this->offset = offset;
    this->unsigned_ = unsigned_;
    this->nsw = nsw;
    this->nuw = nuw;
    this->inbounds = inbounds;
}
IR::LiteralExprPtr PtrOffsetInst::get_pointer() const{
    return this->pointer;
}
IR::LiteralExprPtr PtrOffsetInst::get_offset() const{
    return this->offset;
}
bool PtrOffsetInst::is_unsigned() const{
    return this->unsigned_;
}
bool PtrOffsetInst::is_nsw() const{
    return this->nsw;
}
bool PtrOffsetInst::is_nuw() const{
    return this->nuw;
}
bool PtrOffsetInst::is_inbounds() const{
    return this->inbounds;
}
InstType PtrOffsetInst::get_inst_type() const{
    return InstType::PtrOffsetInst;
}
std::string PtrOffsetInst::to_string() const{
    std::string str = "let " + this->destination->to_string() + " = .ptroffset(ptr:" + this->pointer->to_string() + ", i64:" + this->offset->to_string() + ")";
    if(this->unsigned_){
        str += " #[unsigned]";
    }
    if(this->nsw){
        str += " #[nsw]";
    }
    if(this->nuw){
        str += " #[nuw]";
    }
    if(this->inbounds){
        str += " #[inbounds]";
    }
    return str;
}


StackSaveInst::StackSaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination):
                             Inst(instruction_stmt,destination,std::nullopt){}
InstType StackSaveInst::get_inst_type() const{
    return InstType::StackSaveInst;
}
std::string StackSaveInst::to_string() const{
    std::string str = "let " + this->destination->to_string() + " = .stacksave()";
    return str;
}


StackRestoreInst::StackRestoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer):
                             Inst(instruction_stmt,nullptr,std::nullopt){
    this->pointer = pointer;    
}
IR::LiteralExprPtr StackRestoreInst::get_pointer() const{
    return this->pointer;
}
InstType StackRestoreInst::get_inst_type() const{
    return InstType::StackRestoreInst;
}
std::string StackRestoreInst::to_string() const{
    std::string str = ".stackrestore(" + this->pointer->to_string() + ")";
    return str;
}


ExtractElementInst::ExtractElementInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::LiteralExprPtr index, 
                                        IR::TypeExprPtr value_type,bool inbounds, std::optional<FastMathAttr> fast_math_attr):
                                        Inst(instruction_stmt,destination,fast_math_attr){
    this->value = value;
    this->index = index;
    this->value_type = value_type;
    this->inbounds = inbounds;
}
IR::LiteralExprPtr ExtractElementInst::get_value() const{
    return this->value;
}
IR::TypeExprPtr ExtractElementInst::get_value_type() const{
    return this->value_type;
}
IR::LiteralExprPtr ExtractElementInst::get_index() const{
    return this->index;
}
bool ExtractElementInst::is_inbounds() const{
    return this->inbounds;
}
bool ExtractElementInst::has_const_index() const{
    return dynamic_cast<IR::LiteralExpr*>(this->index.get()) != nullptr;
}
InstType ExtractElementInst::get_inst_type() const{
    return InstType::ExtractElementInst;
}
std::string ExtractElementInst::to_string() const{
    std::string str = "let " + this->destination->to_string() + " = .extractelement(" + this->value_type->to_string() + ":" + this->value->to_string() + ", i64:" + this->index->to_string() + ")";
    if(this->inbounds){
        str += " #[inbounds]";
    }
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}

InsertElementInst::InsertElementInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::LiteralExprPtr element, 
                                     IR::LiteralExprPtr index, IR::TypeExprPtr value_type, IR::TypeExprPtr element_type, bool inbounds, std::optional<FastMathAttr> fast_math_attr):
                                    Inst(instruction_stmt,destination,fast_math_attr){
    this->value = value;
    this->element = element;
    this->index = index;
    this->element_type = element_type;
    this->inbounds = inbounds;
}
IR::LiteralExprPtr InsertElementInst::get_value() const{
    return this->value;
}
IR::TypeExprPtr InsertElementInst::get_value_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr InsertElementInst::get_element() const{
    return this->element;
}
IR::TypeExprPtr InsertElementInst::get_element_Type() const{
    return this->element_type;
}
IR::LiteralExprPtr InsertElementInst::get_index() const{
    return this->index;
}
bool InsertElementInst::is_inbounds() const{
    return this->inbounds;
}
bool InsertElementInst::has_const_index() const{
    return dynamic_cast<IR::LiteralExpr*>(this->index.get()) != nullptr;
}
InstType InsertElementInst::get_inst_type() const{
    return InstType::InsertElementInst;
}
std::string InsertElementInst::to_string() const{
    std::string str = "let " + this->destination->to_string() + " = .insertelement(" + this->get_value_type()->to_string() + ":" + this->value->to_string() + ", " + this->element_type->to_string() + ":" + this->element->to_string() + ", i64:" + this->index->to_string() + ")";
    if(this->inbounds){
        str += " #[inbounds]";
    }
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}


FenceInst::FenceInst(IR::InstructionStmtPtr instruction_stmt, SyncScope sync_scope, AtomicOrdering ordering, bool store_only, bool load_only):
                     Inst(instruction_stmt,nullptr,std::nullopt){
    this->sync_scope = sync_scope;
    this->ordering = ordering;
    this->store_only = store_only;
    this->load_only = load_only;
}
SyncScope FenceInst::get_sync_scope() const{
    return this->sync_scope;
}
AtomicOrdering FenceInst::get_ordering() const{
    return this->ordering;
}
bool FenceInst::is_store_only() const{
    return this->store_only;
}
bool FenceInst::is_load_only() const{
    return this->load_only;
}
InstType FenceInst::get_inst_type() const{
    return InstType::FenceInst;
}
std::string FenceInst::to_string() const{
    std::string str = ".fence(str:" + MIR::to_string(this->ordering) + ")";
    str += " #[sync_scope(" + MIR::to_string(this->sync_scope) + ")]";
    if(this->store_only){
        str += " #[store_only]";
    }
    if(this->load_only){
        str += " #[load_only]";
    }
    return str;
}


CmpXchgInst::CmpXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr expected, 
                         IR::LiteralExprPtr desired, AtomicOrdering success_ordering, AtomicOrdering failure_ordering, 
                         bool volatile_, bool weak, std::size_t alignment, SyncScope sync_scope, std::optional<FastMathAttr> fast_math_attr):
                         Inst(instruction_stmt,destination,fast_math_attr){
    this->pointer = pointer;
    this->expected = expected;
    this->desired = desired;
    this->success_ordering = success_ordering;
    this->failure_ordering = failure_ordering;
    this->volatile_ = volatile_;
    this->weak = weak;
    this->alignment = alignment;
    this->sync_scope = sync_scope;
}
IR::LiteralExprPtr CmpXchgInst::get_pointer() const{
    return this->pointer;
}
IR::LiteralExprPtr CmpXchgInst::get_expected() const{
    return this->expected;
}
IR::LiteralExprPtr CmpXchgInst::get_desired() const{
    return this->desired;
}
IR::TypeExprPtr CmpXchgInst::get_type() const{//type of the expected and desired. Destination type is {T,i1}. This function returns T.
    auto dest_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(this->destination->get_type());
    return dest_type->get_fields()[0];
}
AtomicOrdering CmpXchgInst::get_success_ordering() const{
    return this->success_ordering;
}
AtomicOrdering CmpXchgInst::get_failure_ordering() const{
    return this->failure_ordering;
}
bool CmpXchgInst::is_volatile() const{
    return this->volatile_;
}
bool CmpXchgInst::is_weak() const{
    return this->weak;
}
std::size_t CmpXchgInst::get_alignment() const{
    return this->alignment;
}
SyncScope CmpXchgInst::get_sync_scope() const{
    return this->sync_scope;
}
InstType CmpXchgInst::get_inst_type() const{
    return InstType::CmpXchgInst;
}
std::string CmpXchgInst::to_string() const{
    std::string str = "let " + this->destination->to_string() + " = .cmpxchg(ptr:" + this->pointer->to_string() + ", " + this->get_type()->to_string() + ":" + this->expected->to_string() + ", " + this->get_type()->to_string() + ":" + this->desired->to_string()
                                                                             + ", str:" + MIR::to_string(this->success_ordering) + ", str:" + MIR::to_string(this->failure_ordering) + ")";
    if(this->volatile_){
        str += " #[volatile]";
    }
    if(this->weak){
        str += " #[weak]";
    }
    if(this->alignment != 0){
        str += " #[align(" + std::to_string(this->alignment)+")]";
    }
    str += " #[sync_scope(" + MIR::to_string(this->sync_scope) + ")]";
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
//--------------------------------- Cache Control Instructions ---------------------------------
ClflushInst::ClflushInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, bool opt): Inst(instruction_stmt,nullptr,std::nullopt){
    this->pointer = pointer;
    this->opt = opt;
}
IR::LiteralExprPtr ClflushInst::get_pointer() const{
    return this->pointer;
}
bool ClflushInst::is_opt() const{
    return this->opt;
}
InstType ClflushInst::get_inst_type() const{
    return InstType::ClflushInst;
}
std::string ClflushInst::to_string() const{
    return ".clflush(ptr:" + this->pointer->to_string() + ")" + (this->opt ? " #[opt]" : "");
}


ClwbInst::ClwbInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer): Inst(instruction_stmt,nullptr,std::nullopt){
    this->pointer = pointer;
}
IR::LiteralExprPtr ClwbInst::get_pointer() const{
    return this->pointer;
}
InstType ClwbInst::get_inst_type() const{
    return InstType::ClwbInst;
}
std::string ClwbInst::to_string() const{
    return ".clwb(ptr:" + this->pointer->to_string() + ")";
}


CldemoteInst::CldemoteInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer): Inst(instruction_stmt,nullptr,std::nullopt){
    this->pointer = pointer;
}
IR::LiteralExprPtr CldemoteInst::get_pointer() const{
    return this->pointer;
}
InstType CldemoteInst::get_inst_type() const{
    return InstType::CldemoteInst;
}
std::string CldemoteInst::to_string() const{
    return ".cldemote(ptr:" + this->pointer->to_string() + ")";
}


//--------------------------------- Lifetime and Invariant Scope Instructions ---------------------------------
LifetimeStartInst::LifetimeStartInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, std::size_t size): Inst(instruction_stmt,nullptr,std::nullopt){
    this->pointer = pointer;
    this->size = size;
}
IR::LiteralExprPtr LifetimeStartInst::get_pointer() const{
    return this->pointer;
}
std::size_t LifetimeStartInst::get_size() const{
    return this->size;
}
InstType LifetimeStartInst::get_inst_type() const{
    return InstType::LifetimeStartInst;
}
std::string LifetimeStartInst::to_string() const{
    return ".lifetime.start(ptr:" + this->pointer->to_string() + ", i64:" + std::to_string(this->size) + ")";
}


LifetimeEndInst::LifetimeEndInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, std::size_t size): Inst(instruction_stmt,nullptr,std::nullopt){
    this->pointer = pointer;
    this->size = size;
}
IR::LiteralExprPtr LifetimeEndInst::get_pointer() const{
    return this->pointer;
}
std::size_t LifetimeEndInst::get_size() const{
    return this->size;
}
InstType LifetimeEndInst::get_inst_type() const{
    return InstType::LifetimeEndInst;
}
std::string LifetimeEndInst::to_string() const{
    return ".lifetime.end(ptr:" + this->pointer->to_string() + ", i64:" + std::to_string(this->size) + ")";
}


InvariantStartInst::InvariantStartInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, std::size_t size):
                                        Inst(instruction_stmt,destination,std::nullopt){
    this->pointer = pointer;
    this->size = size;
}
IR::LiteralExprPtr InvariantStartInst::get_pointer() const{
    return this->pointer;
}
std::size_t InvariantStartInst::get_size() const{
    return this->size;
}
InstType InvariantStartInst::get_inst_type() const{
    return InstType::InvariantStartInst;
}
std::string InvariantStartInst::to_string() const{
    return "let " + this->destination->to_string() + " = .invariant.start(ptr:" + this->pointer->to_string() + ", i64:" + std::to_string(this->size) + ")";
}


InvariantEndInst::InvariantEndInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr scope, IR::LiteralExprPtr pointer, std::size_t size)
                                      : Inst(instruction_stmt, nullptr, std::nullopt){
    this->scope = scope;
    this->pointer = pointer;
    this->size = size;
}
IR::LiteralExprPtr InvariantEndInst::get_scope() const{
    return this->scope;
}
IR::LiteralExprPtr InvariantEndInst::get_pointer() const{
    return this->pointer;
}
std::size_t InvariantEndInst::get_size() const{
    return this->size;
}
InstType InvariantEndInst::get_inst_type() const{
    return InstType::InvariantEndInst;
}
std::string InvariantEndInst::to_string() const{
    return ".invariant.end(ptr:" + this->scope->to_string() + ", ptr:" + this->pointer->to_string() + ", i64:" + std::to_string(this->size) + ")";
}
}
}