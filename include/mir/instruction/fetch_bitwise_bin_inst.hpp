#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// ---------------------------  read write modify operations ---------------------------
class FetchBitwiseBinInst:public Inst {
    protected:
    std::size_t alignment;//The alignment of the memory access in bytes
    bool volatile_;//Whether the memory access is volatile or not
    std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info;//If the instruction is atomic, then this field contains the sync scope and atomic ordering of the instruction. Otherwise, it is std::nullopt
    
    IR::LiteralExprPtr pointer;//Always of type ptr
    IR::LiteralExprPtr value;//Same type as destination

    bool nuw;
    bool nsw;
    bool exact;
    bool disjoint;

    std::string to_string_helper(const std::string op_name) const;
    public:
    enum class OpType:std::uint64_t{
        FETCH_AND = 1 << 6,
        FETCH_NAND = 1 << 7,
        FETCH_OR = 1 << 8,
        FETCH_NOR = 1 << 9,
        FETCH_XOR = 1 << 10,
        FETCH_XNOR = 1 << 11,
        FETCH_SHL = 1 << 12,
        FETCH_LSHR = 1 << 13,
        FETCH_ASHR = 1 << 14,
        FETCH_ROTL = 1 << 15,
        FETCH_ROTR = 1 << 16,
        FETCH_PEXT = 1 << 17,
        FETCH_PDEP = 1 << 18
    };
    FetchBitwiseBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                        std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                        bool nuw, bool nsw, bool exact, bool disjoint);

    virtual TypeVariant get_type_variant() const = 0;
    virtual IR::TypeExprPtr get_type() const final;
    virtual IR::LiteralExprPtr get_pointer() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    
    virtual std::size_t get_alignment() const final;
    virtual bool is_volatile() const final;
    virtual std::optional<std::pair<AtomicOrdering,SyncScope>> get_atomic_info() const final;
    virtual OpType get_op_type() const = 0;

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_exact() const final;
    virtual bool is_disjoint() const final;

    virtual InstType get_inst_type() const override final;
};
//Why a seperate class for int? In case I allow vector of ints in future
// --------------------------- Integer read modify operations ---------------------------
class IntFetchBitwiseBinInst:public FetchBitwiseBinInst {
    public:
    IntFetchBitwiseBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                        std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                        bool nuw, bool nsw, bool exact, bool disjoint);

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_type() const final;//Returns the type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bitwidth() const final;//Returns the bit width of the type. Calculated automatically

    virtual TypeVariant get_type_variant() const override final;
};

class IntFetchAndInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchNandInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchNandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchOrInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                    bool disjoint);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchNorInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchNorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                    bool disjoint);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchXorInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchXnorInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchShlInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchShlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                    bool nuw, bool nsw);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchLshrInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchLshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                    bool exact);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchAshrInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchAshrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                    bool exact);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchRotlInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchRotlInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchRotrInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchRotrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchPextInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchPextInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntFetchPdepInst:public IntFetchBitwiseBinInst {
    public:
    IntFetchPdepInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info);

    OpType get_op_type() const override;
    std::string to_string() const override;
};
}
}