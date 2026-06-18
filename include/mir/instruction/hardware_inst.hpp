#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <cstddef>
namespace LIRA {
namespace MIR {
//---------------------------------Processor Identification---------------------------------
class CpuIdInst : public Inst {
    IR::LiteralExprPtr leaf;
    IR::LiteralExprPtr subleaf;
    public:
    CpuIdInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr leaf, IR::LiteralExprPtr subleaf);

    IR::LiteralExprPtr get_leaf() const;
    IR::LiteralExprPtr get_subleaf() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//---------------------------------Timestamp Counter Instructions---------------------------------
class RdTscInst : public Inst {
    public:
    RdTscInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class RdTscpInst : public Inst {
    public:
    RdTscpInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//---------------------------------Hardware Random Number Instructions---------------------------------
class RdrandInst : public Inst {
    public:
    RdrandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class RdseedInst : public Inst {
    public:
    RdseedInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//---------------------------------Floating-Point Environment (SSE)---------------------------------
class GetFpEnvInst : public Inst {
    public:
    GetFpEnvInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class SetFpEnvInst : public Inst {
    IR::LiteralExprPtr env;
    bool volatile_;
    public:
    SetFpEnvInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr env, bool volatile_);

    IR::LiteralExprPtr get_env() const;
    bool is_volatile() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};
}
}