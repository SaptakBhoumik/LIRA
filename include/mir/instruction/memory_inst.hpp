#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
class LocalInst:public Inst {
    IR::LiteralExprPtr value;//The value and its type to store. The type must be a pointer type
    IR::TypeExprPtr type;//The reduced type of value. Must be same as the type of value but without ptr. We need this because we want to support opaque pointers in future where we dont have the type information in the pointer itself. So we need to store the reduced type separately to make sure we can do type checking and other stuff correctly.
    public:
    LocalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr type);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_type() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class AllocaInst:public Inst {
    IR::TypeExprPtr size_var_type;//The type of the size variable. Must be of integer type.
    IR::LiteralExprPtr size_var;//The size variable 

    std::size_t alignment;
    public:
    AllocaInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::TypeExprPtr size_var_type, 
                IR::LiteralExprPtr size_var, std::size_t alignment);

    IR::TypeExprPtr get_size_var_type() const;
    IR::LiteralExprPtr get_size_var() const;
    std::size_t get_alignment() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class LoadInst:public Inst {
    protected:
    IR::LiteralExprPtr pointer;//The pointer to load from. Must be of type ptr
    IR::TypeExprPtr type;//The reduced type of the output

    bool volatile_ = false;//Whether it has the volatile attribute or not
    bool nontemporal = false;//Whether it has the nontemporal attribute or not
    bool invariant_load = false;//Whether it has the invariant.load attribute or not
    bool nonull = false;
    bool nopoison = false;
    std::size_t alignment;
    std::size_t dereferenceable_bytes; //If 0 means the value is not set
    public:
    LoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::TypeExprPtr type, 
             bool volatile_, bool nontemporal, bool invariant_load, bool nonull, bool nopoison, std::size_t alignment, std::size_t dereferenceable_bytes);

    virtual IR::LiteralExprPtr get_pointer() const final;
    virtual IR::TypeExprPtr get_type() const final;
    virtual bool is_volatile() const final;
    virtual bool is_nontemporal() const final;
    virtual bool is_invariant_load() const final;
    virtual bool is_nonull() const final;
    virtual bool is_nopoison() const final;
    virtual std::size_t get_alignment() const final;
    virtual std::size_t get_dereferenceable_bytes() const final;
    virtual bool is_atomic() const;//Whether it is the atomic variant

    virtual InstType get_inst_type() const override;
    virtual std::string to_string() const override;
};

class AtomicLoadInst: public LoadInst{
    protected:
    SyncScope sync_scope;
    AtomicOrdering ordering;

    public:
    AtomicLoadInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::TypeExprPtr type, 
                    bool volatile_, bool nontemporal, bool invariant_load, bool nonull, bool nopoison, std::size_t alignment, std::size_t dereferenceable_bytes, 
                    SyncScope sync_scope, AtomicOrdering ordering);

    SyncScope get_sync_scope() const;
    AtomicOrdering get_ordering() const;
    bool is_atomic() const override;//Whether it is the atomic variant

    InstType get_inst_type() const override;
    std::string to_string() const override;
};
class StoreInst:public Inst {
    protected:
    IR::LiteralExprPtr pointer;//The pointer to store to. Must be of type ptr
    IR::LiteralExprPtr value;//The value to store.
    IR::TypeExprPtr type;//The reduced type of the value. 

    bool volatile_ = false;//Whether it has the volatile attribute or not
    bool nontemporal = false;//Whether it has the nontemporal attribute or not
    bool nonull = false;
    bool nopoison = false;
    std::size_t alignment;
    std::size_t dereferenceable_bytes; //If 0 means the value is not set
    public:
    StoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, IR::TypeExprPtr type, 
              bool volatile_, bool nontemporal, bool nonull, bool nopoison, std::size_t alignment, std::size_t dereferenceable_bytes);

    virtual IR::LiteralExprPtr get_pointer() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual IR::TypeExprPtr get_type() const final;
    virtual bool is_volatile() const final;
    virtual bool is_nontemporal() const final;
    virtual bool is_nonull() const final;
    virtual bool is_nopoison() const final;
    virtual std::size_t get_alignment() const final;
    virtual std::size_t get_dereferenceable_bytes() const final;
    virtual bool is_atomic() const;//Whether it is the atomic variant

    virtual InstType get_inst_type() const override;
    virtual std::string to_string() const override;
};

class AtomicStoreInst: public StoreInst{
    protected:
    SyncScope sync_scope;
    AtomicOrdering ordering;

    public:
    AtomicStoreInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, IR::TypeExprPtr type, 
                    bool volatile_, bool nontemporal, bool nonull, bool nopoison, std::size_t alignment, std::size_t dereferenceable_bytes, 
                    SyncScope sync_scope, AtomicOrdering ordering);

    SyncScope get_sync_scope() const;
    AtomicOrdering get_ordering() const;
    bool is_atomic() const override;//Whether it is the atomic variant

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class GetAddressInst:public Inst {
    IR::LiteralExprPtr value;//The value to get the address of.
    IR::TypeExprPtr value_type;//The reduced type of the value.
    IR::LiteralExprPtr offset;//The offset in bytes to add to the address. You get &value + offset and not &value[offset]
    IR::TypeExprPtr offset_type;//The type of the offset. Must be of integer type

    bool unsigned_;
    bool nsw;
    bool nuw;
    bool inbounds;
    public:
    GetAddressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                    IR::LiteralExprPtr offset, IR::TypeExprPtr offset_type, bool unsigned_, bool nsw, bool nuw, bool inbounds);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_value_type() const;
    IR::LiteralExprPtr get_offset() const;
    IR::TypeExprPtr get_offset_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_offset_int_type() const;//Returns the type of offset casted to IntTypeExpr. Just a helper function to make life easier
    std::size_t get_offset_bitwidth() const;//Returns the bit width of the offset type. Just a helper function to make life easier

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
    IR::TypeExprPtr offset_type;//The type of the offset. Must be of integer type

    bool unsigned_;
    bool nsw;
    bool nuw;
    bool inbounds;
    public:
    PtrOffsetInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, 
                    IR::LiteralExprPtr offset, IR::TypeExprPtr offset_type, bool unsigned_, bool nsw, bool nuw, bool inbounds);

    IR::LiteralExprPtr get_pointer() const;
    IR::LiteralExprPtr get_offset() const;
    IR::TypeExprPtr get_offset_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_offset_int_type() const;//Returns the type of offset casted to IntTypeExpr. Just a helper function to make life easier
    std::size_t get_offset_bitwidth() const;//Returns the bit width of the offset type. Just a helper function to make life easier

    bool is_unsigned() const;
    bool is_nsw() const;
    bool is_nuw() const;
    bool is_inbounds() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

// GetAddressInst and PtrOffsetInst both basically do ptr + offset. Add doesnt care about signedness but then why we care here? Because add doesnt care if both are
// signed or both unsigned. Here ptr is unsigned but offset can be signed or unsigned

class ExtractElementInst:public Inst {
    protected:
    IR::LiteralExprPtr value;
    IR::LiteralExprPtr index;
    IR::TypeExprPtr type;//Reduced type of value 
    IR::TypeExprPtr index_type;//The type of index. 
    bool inbounds = false;//Whether it has the inbounds attribute or not
    public:
    ExtractElementInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::LiteralExprPtr index, 
                        IR::TypeExprPtr type,IR::TypeExprPtr index_type,bool inbounds);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_value_type() const;
    IR::LiteralExprPtr get_index() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_index_type() const;
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
    IR::TypeExprPtr type;//Reduced type of value 
    IR::TypeExprPtr index_type;//The type of index. 
    bool inbounds = false;//Whether it has the inbounds attribute or not
    public:
    InsertElementInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::LiteralExprPtr element, 
                        IR::LiteralExprPtr index, IR::TypeExprPtr type,IR::TypeExprPtr index_type,bool inbounds);

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
    public:
    FenceInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, SyncScope sync_scope, AtomicOrdering ordering);

    SyncScope get_sync_scope() const;
    AtomicOrdering get_ordering() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class CmpXchgInst: public Inst {
    IR::LiteralExprPtr pointer;//The pointer to compare and exchange. Must be of type ptr
    IR::LiteralExprPtr expected;//The expected value. The type must be same as the reduced type of pointer
    IR::LiteralExprPtr desired;//The desired value. The type must be same as the reduced type of pointer
    IR::TypeExprPtr type;//The reduced type of expected and desired. Output type is {type,i1}

    SyncScope sync_scope;
    AtomicOrdering success_ordering;
    AtomicOrdering failure_ordering;
    std::size_t alignment;
    bool volatile_ = false;//Whether it has the volatile attribute or not
    bool weak = false;//Whether it has the weak attribute or not. 
    public:
    CmpXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr expected, 
                IR::LiteralExprPtr desired, IR::TypeExprPtr type, SyncScope sync_scope, AtomicOrdering success_ordering, AtomicOrdering failure_ordering, 
                std::size_t alignment, bool volatile_, bool weak);

    IR::LiteralExprPtr get_pointer() const;
    IR::LiteralExprPtr get_expected() const;
    IR::LiteralExprPtr get_desired() const;
    IR::TypeExprPtr get_type() const;
    SyncScope get_sync_scope() const;
    AtomicOrdering get_success_ordering() const;
    AtomicOrdering get_failure_ordering() const;
    std::size_t get_alignment() const;
    bool is_volatile() const;
    bool is_weak() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};
}
}