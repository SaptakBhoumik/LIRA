#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Atomic read write modify operations ---------------------------
class AtomicRMWInst:public Inst {
    protected:
    std::size_t alignment;//The alignment of the memory access in bytes
    bool volatile_;//Whether the memory access is volatile or not
    SyncScope syncscope;//The synchronization scope of the atomic operation. It can be "singlethread" or "global"
    AtomicOrdering ordering;//The ordering of the atomic operation. It can be unordered,monotonic,acquire,release,acq_rel or seq_cst

    IR::LiteralExprPtr pointer;//Always of type ptr
    IR::LiteralExprPtr value;
    IR::TypeExprPtr type;//Reduced type of value
    public:
    enum class OpType:std::uint64_t{
        XCHG = 1 << 6,
        FETCH_ADD = 1 << 7,
        FETCH_SUB = 1 << 8,
        FETCH_AND = 1 << 9,
        FETCH_NAND = 1 << 10,
        FETCH_OR = 1 << 11,
        FETCH_XOR = 1 << 12,
        FETCH_MAX = 1 << 13,
        FETCH_MIN = 1 << 14,
        UINC_WRAP = 1 << 15,
        IDEC_WRAP = 1 << 16
    };
    AtomicRMWInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                  IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    virtual ~AtomicRMWInst() = default;

    virtual InstOperandTypeVarient get_type_varient() const = 0;
    virtual IR::TypeExprPtr get_type() const final;
    virtual IR::LiteralExprPtr get_pointer() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual std::size_t get_alignment() const final;
    virtual bool is_volatile() const final;
    virtual SyncScope get_sync_scope() const final;
    virtual AtomicOrdering get_ordering() const final;
    virtual OpType get_op_type() const = 0;//Whether it is xchg,add,sub,and,nand,or,xor,max,min,umax or umin etc.

    virtual InstType get_inst_type() const override final;
};


// --------------------------- Integer Atomic read modify operations ---------------------------
class IntAtomicRMWInst:public AtomicRMWInst {
    protected:
    bool unsigned_;//Whether the integer type is unsigned or not. Just a helper function to make life easier. False for unsigned integer. Ignored for instruction that dont care
    public:
    IntAtomicRMWInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                     IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering, bool unsigned_);

    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_type() const final;//Returns the type casted to IntTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bit_width() const final;//Returns the bit width of the type. Calculated automatically

    virtual InstOperandTypeVarient get_type_varient() const override final;
};

class IntAtomicXchgInst:public IntAtomicRMWInst {
    public:
    IntAtomicXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchAddInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchSubInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchAndInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchNandInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchNandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                     IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchOrInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                   IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchXorInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchMaxInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchMinInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicUincWrapInst:public IntAtomicRMWInst {
    public:
    IntAtomicUincWrapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicIdecWrapInst:public IntAtomicRMWInst {
    public:
    IntAtomicIdecWrapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

// --------------------------- Float Atomic read modify operations ---------------------------
class FloatAtomicRMWInst:public AtomicRMWInst {
    public:
    FloatAtomicRMWInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                        IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_type() const final;//Returns the type casted to FloatTypeExpr. Just a helper function to make life easier
    virtual std::size_t get_bit_width() const final;//Returns the bit width of the type. Calculated automatically
    virtual bool is_brain_float() const final;//Whether the type is brain float or not. Just a helper function to make life easier

    virtual InstOperandTypeVarient get_type_varient() const override final;
};

class FloatAtomicXchgInst:public FloatAtomicRMWInst {
    public:
    FloatAtomicXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                  IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatAtomicFetchAddInst:public FloatAtomicRMWInst {
    public:
    FloatAtomicFetchAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatAtomicFetchSubInst:public FloatAtomicRMWInst {
    public:
    FloatAtomicFetchSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatAtomicFetchMaxInst:public FloatAtomicRMWInst {
    public:
    FloatAtomicFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatAtomicFetchMinInst:public FloatAtomicRMWInst {
    public:
    FloatAtomicFetchMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, AtomicOrdering ordering);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}