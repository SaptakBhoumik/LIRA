#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
class LocalInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    IR::LiteralExprPtr value;//The value and its type to store. The type must be a pointer type
    IR::TypeExprPtr type;//The reduced type of value. Must be same as the type of value but without ptr. We need this because we want to support opaque pointers in future where we dont have the type information in the pointer itself. So we need to store the reduced type separately to make sure we can do type checking and other stuff correctly.
    public:
    LocalInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::TypeExprPtr type);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_type() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own based on type of value
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};


class AllocaInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    IR::TypeExprPtr size_var_type;//The type of the size variable. Must be of integer type.
    IR::LiteralExprPtr size_var;//The size variable 

    std::size_t alignment;//The alignment of the allocated memory. Must be a power of 2 and less than or equal to 16. We need this because we want to support alloca with alignment in future. For now we can just set it to 0 and ignore it.
     public:
    AllocaInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::TypeExprPtr size_var_type, 
                IR::LiteralExprPtr size_var, std::size_t alignment);

    IR::TypeExprPtr get_size_var_type() const;
    IR::LiteralExprPtr get_size_var() const;
    std::size_t get_alignment() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//The type of destination is ptr
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};

class LoadInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    IR::LiteralExprPtr pointer;//The pointer to load from. Must be of type ptr
    IR::TypeExprPtr type;//The reduced type of the output

    bool volatile_ = false;//Whether it has the volatile attribute or not
    bool temporal = false;//Whether it has the temporal attribute or not
    bool invariant_load = false;//Whether it has the invariant.load attribute or not
    bool nonull = false;
    bool nopoison = false;
    std::size_t alignment;
    std::size_t dereferenceable_bytes; //If 0 means the value is not set
    public:
    LoadInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::TypeExprPtr type, 
             bool volatile_, bool temporal, bool invariant_load, bool nonull, bool nopoison, std::size_t alignment, std::size_t dereferenceable_bytes);

    virtual ~LoadInst() = default;

    virtual IR::LiteralExprPtr get_pointer() const final;
    virtual IR::TypeExprPtr get_type() const final;
    virtual bool is_volatile() const final;
    virtual bool is_temporal() const final;
    virtual bool is_invariant_load() const final;
    virtual bool is_nonull() const final;
    virtual bool is_nopoison() const final;
    virtual std::size_t get_alignment() const final;
    virtual std::size_t get_dereferenceable_bytes() const final;

    virtual std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//The type of destination is type
    virtual InstType get_inst_type() const override;
    virtual IR::InstructionStmtPtr get_instruction_stmt() const override;
    virtual std::string to_string() const override;
};

class AtomicLoadInst: public LoadInst{
    SyncScope sync_scope;
    AtomicOrdering ordering;

    public:
    AtomicLoadInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::TypeExprPtr type, 
                    bool volatile_, bool temporal, bool invariant_load, bool nonull, bool nopoison, std::size_t alignment, std::size_t dereferenceable_bytes, 
                    SyncScope sync_scope, AtomicOrdering ordering);

    SyncScope get_sync_scope() const;
    AtomicOrdering get_ordering() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//The type of destination is type
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};
//TODO:Like these define the other instruciton that have a atomic varient like store, atomic store etc
class ExtractElementInst:public Inst {
    protected:
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    IR::LiteralExprPtr value;
    IR::LiteralExprPtr index;
    IR::TypeExprPtr type;//Reduced type of value 
    std::shared_ptr<IR::IntTypeExpr> index_type;//The type of index. 
    bool inbounds = false;//Whether it has the inbounds attribute or not
    public:
    ExtractElementInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::LiteralExprPtr index, 
                        IR::TypeExprPtr type,std::shared_ptr<IR::IntTypeExpr> index_type,bool inbounds);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_value_type() const;
    IR::LiteralExprPtr get_index() const;
    std::shared_ptr<IR::IntTypeExpr> get_index_type() const;
    bool is_inbounds() const;
    bool has_const_index() const;//Whether the index is a constant or not. 

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own based on type of value
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};


class InsertElementInst:public Inst {
    protected:
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    IR::LiteralExprPtr value;
    IR::LiteralExprPtr element;
    IR::LiteralExprPtr index;
    IR::TypeExprPtr type;//Reduced type of value 
    std::shared_ptr<IR::IntTypeExpr> index_type;//The type of index. 
    bool inbounds = false;//Whether it has the inbounds attribute or not
    public:
    InsertElementInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr value, IR::LiteralExprPtr element, 
                        IR::LiteralExprPtr index, IR::TypeExprPtr type,std::shared_ptr<IR::IntTypeExpr> index_type,bool inbounds);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_value_type() const;
    IR::LiteralExprPtr get_element() const;
    IR::TypeExprPtr get_element_Type() const;//Will figure out the type of element on it's own based on type of value
    IR::LiteralExprPtr get_index() const;
    std::shared_ptr<IR::IntTypeExpr> get_index_type() const;
    bool is_inbounds() const;
    bool has_const_index() const;//Whether the index is a constant or not. 

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Will figure out the type of destination on it's own based on type of value
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};


}
}