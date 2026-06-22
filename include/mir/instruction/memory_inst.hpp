#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <cstddef>
namespace LIRA {
namespace MIR {
//--------------------------------- Uncategorized Memory Instructions ---------------------------------
class LocalInst:public Inst {
    IR::LiteralExprPtr value;
    public:
    LocalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
              std::optional<FastMathAttr> fast_math_attr);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_type() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class AllocaInst:public Inst {
    IR::LiteralExprPtr size;//The size variable 
    std::size_t alignment;
    public:
    AllocaInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,IR::LiteralExprPtr size, std::size_t alignment);

    IR::LiteralExprPtr get_size() const;
    std::size_t get_alignment() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class LoadInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to load from. Must be of type ptr

    bool volatile_ = false;//Whether it has the volatile attribute or not
    bool invariant_load = false;//Whether it has the invariant.load attribute or not
    bool nontemporal = false;//Whether it has the nontemporal attribute or not
    bool nonull = false;
    bool nopoison = false;
    bool nsb = false;
    std::size_t alignment;
    std::size_t dereferenceable_bytes; //If 0 means the value is not set
    std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info;
    public:
    LoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, 
             bool volatile_, bool invariant_load, bool nontemporal, bool nonull, bool nopoison, 
             std::size_t alignment, std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info);

    IR::LiteralExprPtr get_pointer() const;
    IR::TypeExprPtr get_type() const;
    
    bool is_volatile() const;
    bool is_invariant_load() const;
    bool is_nontemporal() const;
    bool is_nonull() const;
    bool is_nopoison() const;
    bool is_nsb() const;
    std::size_t get_alignment() const;
    std::size_t get_dereferenceable_bytes() const;
    std::optional<std::pair<AtomicOrdering,SyncScope>> get_atomic_info() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class StoreInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to store to. Must be of type ptr
    IR::LiteralExprPtr value;//The value to store.
    IR::TypeExprPtr type;//The reduced type of the value. 

    bool volatile_ = false;//Whether it has the volatile attribute or not
    bool nontemporal = false;//Whether it has the nontemporal attribute or not
    bool nonull = false;
    bool nopoison = false;
    std::size_t alignment;
    std::size_t dereferenceable_bytes; //If 0 means the value is not set
    std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info;
    public:
    StoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, IR::TypeExprPtr type, 
              bool volatile_, bool nontemporal, bool nonull, bool nopoison, 
              std::size_t alignment, std::size_t dereferenceable_bytes,std::optional<FastMathAttr> fast_math_attr, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info);

    IR::LiteralExprPtr get_pointer() const;
    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_type() const;

    bool is_volatile() const;
    bool is_nontemporal() const;
    bool is_nonull() const;
    bool is_nopoison() const;
    std::size_t get_alignment() const;
    std::size_t get_dereferenceable_bytes() const;
    std::optional<std::pair<AtomicOrdering,SyncScope>> get_atomic_info() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class MaskedLoadInst:public Inst {
    protected:
    IR::LiteralExprPtr pointer;//The pointer to load from. Must be of type ptr
    IR::LiteralExprPtr mask;//The mask to use for the masked load. Must be of type <n x i1>. nullptr if not provided
    IR::LiteralExprPtr passthru;//The value to use for the elements that are not loaded. Must be of the same type as the reduced type of destination variable. nullptr if not provided

    bool volatile_ = false;
    bool nontemporal = false;
    bool nonull = false;
    bool zeropassthru = false;//Whether it has the zeropassthru attribute or not. If this is set then passthru must be nullptr and mask cant be 0
    std::size_t alignment;
    std::size_t dereferenceable_bytes;

    std::string to_string_helper(std::string opname) const;
    public:
    MaskedLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask, 
                    IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                    std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_pointer() const final;
    virtual IR::LiteralExprPtr get_mask() const final;
    virtual IR::LiteralExprPtr get_passthru() const final;
    virtual IR::TypeExprPtr get_element_type() const final;
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_vector_type() const final;
    virtual std::size_t get_vector_size() const final;

    virtual bool is_volatile() const final;
    virtual bool is_nontemporal() const final;
    virtual bool is_nonull() const final;
    virtual bool is_zeropassthru() const final;
    virtual std::size_t get_alignment() const final;
    virtual std::size_t get_dereferenceable_bytes() const final;

    virtual InstType get_inst_type() const override final;
    virtual TypeVarient get_element_type_varient() const = 0;
};

class IntMaskedLoadInst:public MaskedLoadInst {
    public:
    IntMaskedLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask, 
                    IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                    std::size_t dereferenceable_bytes);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class PtrMaskedLoadInst:public MaskedLoadInst {
    public:
    PtrMaskedLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask, 
                    IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                    std::size_t dereferenceable_bytes);
    
    std::size_t get_element_bitwidth() const;

    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class FloatMaskedLoadInst:public MaskedLoadInst {
    public:
    FloatMaskedLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask, 
                    IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                    std::size_t dereferenceable_bytes, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_brain_float() const;

    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class MaskedStoreInst:public Inst {
    protected:
    IR::LiteralExprPtr pointer;//The pointer to store to. Must be of type ptr
    IR::LiteralExprPtr value;//The value to store. 
    IR::TypeExprPtr value_type;//The reduced type of the value.
    IR::LiteralExprPtr mask;//The mask to use for the masked store. Must be of type <n x i1>. nullptr if not provided

    bool volatile_ = false;
    bool nontemporal = false;
    bool nonull = false;
    std::size_t alignment;
    std::size_t dereferenceable_bytes;

    std::string to_string_helper(std::string opname) const;
    public:
    MaskedStoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                    std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_pointer() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual IR::LiteralExprPtr get_mask() const final;
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_value_type() const final;
    virtual IR::TypeExprPtr get_value_basetype() const final;
    virtual std::size_t get_vector_size() const final;

    virtual bool is_volatile() const final;
    virtual bool is_nontemporal() const final;
    virtual bool is_nonull() const final;
    virtual std::size_t get_alignment() const final;
    virtual std::size_t get_dereferenceable_bytes() const final;

    virtual InstType get_inst_type() const override final;
    virtual TypeVarient get_element_type_varient() const = 0;
};

class IntMaskedStoreInst:public MaskedStoreInst {
    public:
    IntMaskedStoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                       IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                       std::size_t dereferenceable_bytes);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_value_basetype() const;
    std::size_t get_value_basetype_bitwidth() const;

    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class PtrMaskedStoreInst:public MaskedStoreInst {
    public:
    PtrMaskedStoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                       IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                       std::size_t dereferenceable_bytes);
    
    std::size_t get_value_basetype_bitwidth() const;

    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class FloatMaskedStoreInst:public MaskedStoreInst {
    public:
    FloatMaskedStoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                         IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                         std::size_t dereferenceable_bytes, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_value_basetype() const;
    std::size_t get_value_basetype_bitwidth() const;
    bool is_brain_float() const;

    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class MaskedGatherInst:public Inst {
    protected:
    IR::LiteralExprPtr vec_of_ptrs;//The vector of pointers to gather from. Must be of type <n x ptr>
    IR::LiteralExprPtr mask;//The mask to use for the masked gather. Must be of type <n x i1>. nullptr if not provided
    IR::LiteralExprPtr passthru;//The value to use for the elements that are not gathered. Must be of the same type as the reduced type of destination variable. nullptr if not provided

    bool volatile_ = false;//Whether it has the volatile attribute or not
    bool nontemporal = false;//Whether it has the nontemporal attribute or not
    bool nonull = false;
    bool zeropassthru = false;//Whether it has the zeropassthru attribute or not. If this is set then passthru must be nullptr and mask cant be 0
    std::size_t alignment;
    std::size_t dereferenceable_bytes;

    std::string to_string_helper(std::string opname) const;
    public:
    MaskedGatherInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr mask, 
                     IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                     std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_vec_of_ptrs() const final;
    virtual IR::LiteralExprPtr get_mask() const final;
    virtual IR::LiteralExprPtr get_passthru() const final;
    virtual IR::TypeExprPtr get_element_type() const final;
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_vector_type() const final;
    virtual std::size_t get_vector_size() const final;

    virtual bool is_volatile() const final;
    virtual bool is_nontemporal() const final;
    virtual bool is_nonull() const final;
    virtual bool is_zeropassthru() const final;
    virtual std::size_t get_alignment() const final;
    virtual std::size_t get_dereferenceable_bytes() const final;

    virtual InstType get_inst_type() const override final;
    virtual TypeVarient get_element_type_var() const = 0;
};

class IntMaskedGatherInst:public MaskedGatherInst {
    public:
    IntMaskedGatherInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr mask, 
                        IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                        std::size_t dereferenceable_bytes);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    TypeVarient get_element_type_var() const override;
    std::string to_string() const override;
};

class PtrMaskedGatherInst:public MaskedGatherInst {
    public:
    PtrMaskedGatherInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr mask, 
                        IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                        std::size_t dereferenceable_bytes);
    
    std::size_t get_element_bitwidth() const;

    TypeVarient get_element_type_var() const override;
    std::string to_string() const override;
};

class FloatMaskedGatherInst:public MaskedGatherInst {
    public:
    FloatMaskedGatherInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr mask, 
                          IR::LiteralExprPtr passthru, bool volatile_, bool nontemporal, bool nonull, bool zeropassthru, std::size_t alignment, 
                          std::size_t dereferenceable_bytes, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_brain_float() const;

    TypeVarient get_element_type_var() const override;
    std::string to_string() const override;
};

class MaskedScatterInst:public Inst {
    protected:
    IR::LiteralExprPtr vec_of_ptrs;//The vector of pointers to scatter to. Must be of type <n x ptr>
    IR::LiteralExprPtr value;//The value to scatter. Must be of the same type as the reduced type of vec_of_ptrs
    IR::TypeExprPtr value_type;//The reduced type of the value.
    IR::LiteralExprPtr mask;//The mask to use for the masked scatter. Must be of type <n x i1>. nullptr if not provided

    bool volatile_ = false;
    bool nontemporal = false;
    bool nonull = false;
    std::size_t alignment;
    std::size_t dereferenceable_bytes;

    std::string to_string_helper(std::string opname) const;
    public:
    MaskedScatterInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr value, 
                      IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                      std::size_t dereferenceable_bytes, std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_vec_of_ptrs() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual IR::LiteralExprPtr get_mask() const final;
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_value_type() const final;
    virtual IR::TypeExprPtr get_value_basetype() const final;
    virtual std::size_t get_vector_size() const final;

    virtual bool is_volatile() const final;
    virtual bool is_nontemporal() const final;
    virtual bool is_nonull() const final;
    virtual std::size_t get_alignment() const final;
    virtual std::size_t get_dereferenceable_bytes() const final;

    virtual InstType get_inst_type() const override final;
    virtual TypeVarient get_element_type_var() const = 0;
};

class IntMaskedScatterInst:public MaskedScatterInst {
    public:
    IntMaskedScatterInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr value, 
                         IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                         std::size_t dereferenceable_bytes);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_value_basetype() const;
    std::size_t get_value_basetype_bitwidth() const;

    TypeVarient get_element_type_var() const override;
    std::string to_string() const override;
};

class PtrMaskedScatterInst:public MaskedScatterInst {
    public:
    PtrMaskedScatterInst(IR::InstructionStmtPtr instruction_stmt,  IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr value, 
                         IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                         std::size_t dereferenceable_bytes);
    
    std::size_t get_value_basetype_bitwidth() const;

    TypeVarient get_element_type_var() const override;
    std::string to_string() const override;
};

class FloatMaskedScatterInst:public MaskedScatterInst {
    public:
    FloatMaskedScatterInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr vec_of_ptrs, IR::LiteralExprPtr value, 
                           IR::TypeExprPtr value_type, IR::LiteralExprPtr mask, bool volatile_, bool nontemporal, bool nonull, std::size_t alignment, 
                           std::size_t dereferenceable_bytes, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_value_basetype() const;
    std::size_t get_value_basetype_bitwidth() const;
    bool is_brain_float() const;

    TypeVarient get_element_type_var() const override;
    std::string to_string() const override;
};

class PrefetchInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to prefetch. Must be of type ptr

    bool write;
    bool instruction;
    std::size_t prefetch_locality;
    public:
    PrefetchInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, bool write, bool instruction, std::size_t prefetch_locality);

    IR::LiteralExprPtr get_pointer() const;
    bool is_write() const;
    bool is_instruction() const;
    std::size_t get_prefetch_locality() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class MemcopyInst:public Inst {
    IR::LiteralExprPtr dest;//The destination pointer. Must be of type ptr
    IR::LiteralExprPtr src;//The source pointer. Must be of type ptr
    IR::LiteralExprPtr size;//The size in bytes to copy. Must be of integer type

    bool nooverlap = false;//Whether it has the nooverlap attribute or not.
    bool volatile_ = false;//Whether it has the volatile attribute or not
    std::pair<bool,bool> nontemporal;//{whether dest access is nontemporal, whether src access is nontemporal}
    std::pair<bool,bool> nonnull;//{whether dest pointer is nonnull, whether src pointer is nonnull}
    std::pair<bool,bool> nopoison;//{whether dest pointer is nopoison, whether src pointer is nopoison}
    std::pair<size_t, size_t> alignment;//{alignment of dest, alignment of src}
    std::pair<size_t, size_t> dereferenceable_bytes;//{dereferenceable bytes of dest, dereferenceable bytes of src}
    public:
    MemcopyInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr dest, IR::LiteralExprPtr src, 
               IR::LiteralExprPtr size, bool nooverlap, bool volatile_, 
               std::pair<bool,bool> nontemporal, std::pair<bool,bool> nonnull, std::pair<bool,bool> nopoison,
               std::pair<size_t, size_t> alignment, std::pair<size_t, size_t> dereferenceable_bytes);

    IR::LiteralExprPtr get_dest() const;
    IR::LiteralExprPtr get_src() const;
    IR::LiteralExprPtr get_size() const;

    bool is_nooverlap() const;
    bool is_volatile() const;
    std::pair<bool,bool> is_nontemporal() const;
    std::pair<bool,bool> is_nonnull() const;
    std::pair<bool,bool> is_nopoison() const;
    std::pair<size_t, size_t> get_alignment() const;
    std::pair<size_t, size_t> get_dereferenceable_bytes() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class MemsetInst:public Inst {
    IR::LiteralExprPtr dest;//The destination pointer. Must be of type ptr
    IR::LiteralExprPtr value;
    IR::LiteralExprPtr size;//The size in bytes to copy. Must be of integer type

    bool volatile_ = false;//Whether it has the volatile attribute or not
    bool nontemporal = false;//Whether it has the nontemporal attribute or not
    bool nonnull = false;
    bool nopoison = false;
    std::size_t alignment;
    std::size_t dereferenceable_bytes;
    public:
    MemsetInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr dest, IR::LiteralExprPtr value, 
               IR::LiteralExprPtr size, bool volatile_, bool nontemporal, bool nonnull, bool nopoison,
               std::size_t alignment, std::size_t dereferenceable_bytes);

    IR::LiteralExprPtr get_dest() const;
    IR::LiteralExprPtr get_value() const;
    IR::LiteralExprPtr get_size() const;

    bool is_volatile() const;
    bool is_nontemporal() const;
    bool is_nonnull() const;
    bool is_nopoison() const;
    std::size_t get_alignment() const;
    std::size_t get_dereferenceable_bytes() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class MemcmpInst:public Inst {
    IR::LiteralExprPtr ptr1;//The first pointer. Must be of type ptr
    IR::LiteralExprPtr ptr2;//The second pointer. Must be of type ptr
    IR::LiteralExprPtr size;//The size in bytes to compare. Must be of integer type

    bool volatile_ = false;//Whether it has the volatile attribute or not
    std::pair<bool,bool> nontemporal;//{whether ptr1 access is nontemporal, whether ptr2 access is nontemporal}
    std::pair<bool,bool> nonnull;//{whether ptr1 pointer is nonnull, whether ptr2 pointer is nonnull}
    std::pair<bool,bool> nopoison;//{whether ptr1 pointer is nopoison, whether ptr2 pointer is nopoison}
    std::pair<size_t, size_t> alignment;//{alignment of ptr1, alignment of ptr2}
    std::pair<size_t, size_t> dereferenceable_bytes;//{dereferenceable bytes of ptr1, dereferenceable bytes of ptr2}
    public:
    MemcmpInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr ptr1, IR::LiteralExprPtr ptr2, IR::LiteralExprPtr size, 
               bool volatile_, std::pair<bool,bool> nontemporal, std::pair<bool,bool> nonnull, std::pair<bool,bool> nopoison, 
               std::pair<size_t, size_t> alignment, std::pair<size_t, size_t> dereferenceable_bytes);   
    
    IR::LiteralExprPtr get_ptr1() const;
    IR::LiteralExprPtr get_ptr2() const;
    IR::LiteralExprPtr get_size() const;

    bool is_volatile() const;
    std::pair<bool,bool> is_nontemporal() const;
    std::pair<bool,bool> is_nonnull() const;
    std::pair<bool,bool> is_nopoison() const;
    std::pair<size_t, size_t> get_alignment() const;
    std::pair<size_t, size_t> get_dereferenceable_bytes() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class GetAddressInst:public Inst {
    IR::LiteralExprPtr value;//The value to get the address of.
    IR::TypeExprPtr value_type;//The reduced type of the value.
    IR::LiteralExprPtr offset;//The offset in bytes to add to the address. You get &value + offset and not &value[offset]

    bool unsigned_;
    bool nsw;
    bool nuw;
    bool inbounds;
    public:
    GetAddressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    IR::LiteralExprPtr offset, bool unsigned_, bool nsw, bool nuw, bool inbounds, std::optional<FastMathAttr> fast_math_attr);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_value_type() const;
    IR::LiteralExprPtr get_offset() const;

    bool is_unsigned() const;
    bool is_nsw() const;
    bool is_nuw() const;
    bool is_inbounds() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class PtrOffsetInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to add the offset to. Must be of type ptr
    IR::LiteralExprPtr offset;//The offset in bytes to add to the pointer. You get pointer + offset and not pointer[offset]

    bool unsigned_;
    bool nsw;
    bool nuw;
    bool inbounds;
    public:
    PtrOffsetInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, 
                    IR::LiteralExprPtr offset, bool unsigned_, bool nsw, bool nuw, bool inbounds);

    IR::LiteralExprPtr get_pointer() const;
    IR::LiteralExprPtr get_offset() const;

    bool is_unsigned() const;
    bool is_nsw() const;
    bool is_nuw() const;
    bool is_inbounds() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

// GetAddressInst and PtrOffsetInst both basically do ptr + offset. Add doesnt care about signedness but then why we care here? Because add doesnt care if both are
// signed or both unsigned. Here ptr is unsigned but offset can be signed or unsigned so we have to care


class StackSaveInst:public Inst {
    public:
    StackSaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class StackRestoreInst:public Inst {
    IR::LiteralExprPtr value;//The value to restore the stack to. Must be of type ptr and must be a value returned by a StackSaveInst

    public:
    StackRestoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr value);

    IR::LiteralExprPtr get_value() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class ExtractElementInst:public Inst {
    protected:
    IR::LiteralExprPtr value;
    IR::LiteralExprPtr index;
    IR::TypeExprPtr value_type;//Reduced type of value 

    bool inbounds = false;//Whether it has the inbounds attribute or not
    public:
    ExtractElementInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::LiteralExprPtr index, 
                        IR::TypeExprPtr value_type,bool inbounds);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_value_type() const;
    IR::LiteralExprPtr get_index() const;
    bool is_inbounds() const;
    bool has_const_index() const;//Whether the index is a constant or not. 

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class InsertElementInst:public Inst {
    protected:
    IR::LiteralExprPtr value;
    IR::LiteralExprPtr element;
    IR::LiteralExprPtr index;
    IR::TypeExprPtr value_type;//Reduced type of value 
    bool inbounds = false;//Whether it has the inbounds attribute or not
    public:
    InsertElementInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::LiteralExprPtr element, 
                        IR::LiteralExprPtr index, IR::TypeExprPtr value_type, bool inbounds);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_value_type() const;
    IR::LiteralExprPtr get_element() const;
    IR::TypeExprPtr get_element_Type() const;//Will figure out the type of element on it's own based on type of value
    IR::LiteralExprPtr get_index() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_index_type() const;
    bool is_inbounds() const;
    bool has_const_index() const;//Whether the index is a constant or not. 

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class FenceInst:public Inst {
    SyncScope sync_scope;
    AtomicOrdering ordering;
    bool store_only = false;
    bool load_only = false;
    public:
    FenceInst(IR::InstructionStmtPtr instruction_stmt, SyncScope sync_scope, AtomicOrdering ordering, bool store_only, bool load_only);

    SyncScope get_sync_scope() const;
    AtomicOrdering get_ordering() const;
    bool is_store_only() const;
    bool is_load_only() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class CmpXchgInst: public Inst {
    IR::LiteralExprPtr pointer;//The pointer to compare and exchange. Must be of type ptr
    IR::LiteralExprPtr expected;//The expected value.
    IR::LiteralExprPtr desired;//The desired value.

    AtomicOrdering success_ordering;
    AtomicOrdering failure_ordering;

    bool volatile_ = false;//Whether it has the volatile attribute or not
    bool weak = false;//Whether it has the weak attribute or not. 
    std::size_t alignment;
    SyncScope sync_scope;
    public:
    CmpXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr expected, 
                IR::LiteralExprPtr desired, AtomicOrdering success_ordering, AtomicOrdering failure_ordering, 
                bool volatile_, bool weak, std::size_t alignment, SyncScope sync_scope, std::optional<FastMathAttr> fast_math_attr);

    IR::LiteralExprPtr get_pointer() const;
    IR::LiteralExprPtr get_expected() const;
    IR::LiteralExprPtr get_desired() const;
    IR::TypeExprPtr get_type() const;//type of the expected and desired. Destination type is {T,i1}. This function returns T.
    AtomicOrdering get_success_ordering() const;
    AtomicOrdering get_failure_ordering() const;

    bool is_volatile() const;
    bool is_weak() const;
    std::size_t get_alignment() const;
    SyncScope get_sync_scope() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//--------------------------------- Cache Control Instructions ---------------------------------
class ClflushInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to flush. Must be of type ptr
    bool opt;
    public:
    ClflushInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, bool opt);

    IR::LiteralExprPtr get_pointer() const;
    bool is_opt() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class ClwbInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to write back. Must be of type ptr
    public:
    ClwbInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer);

    IR::LiteralExprPtr get_pointer() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class CldemoteInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to demote. Must be of type ptr
    public:
    CldemoteInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer);

    IR::LiteralExprPtr get_pointer() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//--------------------------------- Lifetime and Invariant Scope Instructions ---------------------------------
class LifetimeStartInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to start the lifetime of. Must be of type ptr
    std::size_t size;//The size in bytes of the object. Must be of integer type
    public:
    LifetimeStartInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, std::size_t size);

    IR::LiteralExprPtr get_pointer() const;
    std::size_t get_size() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class LifetimeEndInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to end the lifetime of. Must be of type ptr
    std::size_t size;//The size in bytes of the object. Must be of integer type
    public:
    LifetimeEndInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, std::size_t size);

    IR::LiteralExprPtr get_pointer() const;
    std::size_t get_size() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class InvariantStartInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to start the invariant scope of. Must be of type ptr
    std::size_t size;//The size in bytes of the object. Must be of integer type
    public:
    InvariantStartInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, std::size_t size);

    IR::LiteralExprPtr get_pointer() const;
    std::size_t get_size() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class InvariantEndInst:public Inst {
    IR::LiteralExprPtr scope;
    IR::LiteralExprPtr pointer;
    std::size_t size;
    public:
    InvariantEndInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr scope, IR::LiteralExprPtr pointer, std::size_t size);

    IR::LiteralExprPtr get_scope() const;
    IR::LiteralExprPtr get_pointer() const;
    std::size_t get_size() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};
}
}