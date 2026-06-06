#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Atomic read write modify operations ---------------------------
class AtomicRMWInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    std::optional<DestinationVar> destination;//The destination variable token for identifying the output variable

    std::size_t alignment;//The alignment of the memory access in bytes
    bool volatile_;//Whether the memory access is volatile or not
    SyncScope syncscope;//The synchronization scope of the atomic operation. It can be "singlethread" or "global"

    IR::LiteralExprPtr pointer;//Always of type ptr
    IR::LiteralExprPtr value;
    IR::TypeExprPtr type;//Reduced type of value
    public:
    enum class OpType:std::uint32_t{
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
    AtomicRMWInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                  IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    virtual ~AtomicRMWInst() = default;

    virtual InstOperandTypeVarient get_type_varient() const final;//Can be calculated easily from ``type``. Just a helper function
    virtual IR::TypeExprPtr get_type() const final;
    virtual IR::LiteralExprPtr get_pointer() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual std::size_t get_alignment() const final;
    virtual bool is_volatile() const final;
    virtual SyncScope get_sync_scope() const final;
    virtual OpType get_op_type() const = 0;//Whether it is xchg,add,sub,and,nand,or,xor,max,min,umax or umin etc.

    virtual std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override final;
    virtual InstType get_inst_type() const override final;
    virtual IR::InstructionStmtPtr get_instruction_stmt() const override final;
};

// --------------------------- Integer Atomic read modify operations ---------------------------
class IntAtomicRMWInst:public AtomicRMWInst {
    bool signed_;//Whether the integer type is signed or not. Just a helper function to make life easier. False for unsigned integer. Ignored for instruction that dont care
    public:
    IntAtomicRMWInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                     IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, bool signed_);

    std::shared_ptr<IR::IntTypeExpr> get_casted_type() const;//Returns the type casted to IntTypeExpr. Just a helper function to make life easier
    std::size_t get_bit_width() const;//Returns the bit width of the type. Calculated automatically

};

class IntAtomicXchgInst:public IntAtomicRMWInst {
    public:
    IntAtomicXchgInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchAddInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchAddInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchSubInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchSubInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchAndInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchAndInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchNandInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchNandInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                     IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchOrInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchOrInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                   IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchXorInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchXorInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchMaxInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, bool signed_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicFetchMinInst:public IntAtomicRMWInst {
    public:
    IntAtomicFetchMinInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope, bool signed_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicUincWrapInst:public IntAtomicRMWInst {
    public:
    IntAtomicUincWrapInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntAtomicIdecWrapInst:public IntAtomicRMWInst {
    public:
    IntAtomicIdecWrapInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

// --------------------------- Float Atomic read modify operations ---------------------------
class FloatAtomicRMWInst:public AtomicRMWInst {
    public:
    FloatAtomicRMWInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                        IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_type() const;//Returns the type casted to FloatTypeExpr. Just a helper function to make life easier
    std::size_t get_bit_width() const;//Returns the bit width of the type. Calculated automatically
    bool is_brain_float() const;//Whether the type is brain float or not. Just a helper function to make life easier
};

class FloatAtomicXchgInst:public FloatAtomicRMWInst {
    public:
    FloatAtomicXchgInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                  IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatAtomicFetchAddInst:public FloatAtomicRMWInst {
    public:
    FloatAtomicFetchAddInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatAtomicFetchSubInst:public FloatAtomicRMWInst {
    public:
    FloatAtomicFetchSubInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatAtomicFetchMaxInst:public FloatAtomicRMWInst {
    public:
    FloatAtomicFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatAtomicFetchMinInst:public FloatAtomicRMWInst {
    public:
    FloatAtomicFetchMinInst(IR::InstructionStmtPtr instruction_stmt, std::optional<DestinationVar> destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                      IR::TypeExprPtr type, std::size_t alignment, bool volatile_, SyncScope syncscope);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}