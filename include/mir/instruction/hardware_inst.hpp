#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <cstddef>
namespace LIRA {
namespace MIR {
//---------------------------------Processor Identification Instructions ---------------------------------
class CpuIdInst : public Inst {
    IR::LiteralExprPtr leaf;
    IR::LiteralExprPtr subleaf;
    public:
    CpuIdInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr leaf, IR::LiteralExprPtr subleaf);

    IR::LiteralExprPtr get_leaf() const;
    IR::LiteralExprPtr get_subleaf() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};
 
//---------------------------------Timestamp Counter Instructions---------------------------------
class RdTscInst : public Inst {
    public:
    RdTscInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class RdTscpInst : public Inst {
    public:
    RdTscpInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//---------------------------------Hardware Random Number Instructions---------------------------------
class RdrandInst : public Inst {
    public:
    RdrandInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class RdseedInst : public Inst {
    public:
    RdseedInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//---------------------------------Floating-Point Environment---------------------------------
class GetFpEnvInst : public Inst {
    bool x87;
    public:
    GetFpEnvInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, bool x87);

    bool is_x87() const;
    
    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class SetFpEnvInst : public Inst {
    IR::LiteralExprPtr env;
    bool volatile_;
    bool x87;
    public:
    SetFpEnvInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr env, bool volatile_, bool x87);

    bool is_x87() const;
    IR::LiteralExprPtr get_env() const;
    bool is_volatile() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class FpenvGetFieldInst : public Inst {
    IR::LiteralExprPtr env;
    FPEnvField field;
    bool x87;
    public:
    FpenvGetFieldInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr env, FPEnvField field, bool x87);

    bool is_x87() const;
    IR::LiteralExprPtr get_env() const;
    FPEnvField get_field() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class FpenvSetFieldInst : public Inst {
    IR::LiteralExprPtr env;
    FPEnvField field;
    IR::LiteralExprPtr value;
    bool x87;
    public:
    FpenvSetFieldInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr env, FPEnvField field, 
                      IR::LiteralExprPtr value, bool x87);

    bool is_x87() const;
    IR::LiteralExprPtr get_env() const;
    FPEnvField get_field() const;
    IR::LiteralExprPtr get_value() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class GetFpStatusInst : public Inst {
    bool x87;
    public:
    GetFpStatusInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, bool x87);

    bool is_x87() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class ClearFpStatusInst : public Inst {
    bool x87;
    public:
    ClearFpStatusInst(IR::InstructionStmtPtr instruction_stmt, bool x87);

    bool is_x87() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//---------------------------------Crypto Extensions---------------------------------
// ---- AES (all operate on <i8,16> blocks) ----
class AesEncInst : public Inst {
    IR::LiteralExprPtr state;
    IR::LiteralExprPtr roundkey;
    public:
    AesEncInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
               IR::LiteralExprPtr state, IR::LiteralExprPtr roundkey);

    IR::LiteralExprPtr get_state() const;
    IR::LiteralExprPtr get_roundkey() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class AesEncLastInst : public Inst {
    IR::LiteralExprPtr state;
    IR::LiteralExprPtr roundkey;
    public:
    AesEncLastInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                   IR::LiteralExprPtr state, IR::LiteralExprPtr roundkey);

    IR::LiteralExprPtr get_state() const;
    IR::LiteralExprPtr get_roundkey() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class AesDecInst : public Inst {
    IR::LiteralExprPtr state;
    IR::LiteralExprPtr roundkey;
    public:
    AesDecInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
               IR::LiteralExprPtr state, IR::LiteralExprPtr roundkey);

    IR::LiteralExprPtr get_state() const;
    IR::LiteralExprPtr get_roundkey() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class AesDecLastInst : public Inst {
    IR::LiteralExprPtr state;
    IR::LiteralExprPtr roundkey;
    public:
    AesDecLastInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                   IR::LiteralExprPtr state, IR::LiteralExprPtr roundkey);

    IR::LiteralExprPtr get_state() const;
    IR::LiteralExprPtr get_roundkey() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class AesImcInst : public Inst {
    IR::LiteralExprPtr roundkey;
    public:
    AesImcInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
               IR::LiteralExprPtr roundkey);

    IR::LiteralExprPtr get_roundkey() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class AesKeyGenAssistInst : public Inst {
    IR::LiteralExprPtr a;
    IR::LiteralExprPtr rcon;
    public:
    AesKeyGenAssistInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                        IR::LiteralExprPtr a, IR::LiteralExprPtr rcon);

    IR::LiteralExprPtr get_a() const;
    IR::LiteralExprPtr get_rcon() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

// ---- Carry-less Multiply ----
class ClmulInst : public Inst {
    IR::LiteralExprPtr a;
    IR::LiteralExprPtr b;
    public:
    ClmulInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
              IR::LiteralExprPtr a, IR::LiteralExprPtr b);

    IR::LiteralExprPtr get_a() const;
    IR::LiteralExprPtr get_b() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

// ---- SHA (all operate on <i32,4> state) ----
class Sha1Rnds4Inst : public Inst {
    IR::LiteralExprPtr abcd;
    IR::LiteralExprPtr msg;
    IR::LiteralExprPtr func;
    public:
    Sha1Rnds4Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                    IR::LiteralExprPtr abcd, IR::LiteralExprPtr msg, IR::LiteralExprPtr func);

    IR::LiteralExprPtr get_abcd() const;
    IR::LiteralExprPtr get_msg() const;
    IR::LiteralExprPtr get_func() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class Sha1NextEInst : public Inst {
    IR::LiteralExprPtr abcd;
    IR::LiteralExprPtr e;
    public:
    Sha1NextEInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                  IR::LiteralExprPtr abcd, IR::LiteralExprPtr e);

    IR::LiteralExprPtr get_abcd() const;
    IR::LiteralExprPtr get_e() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class Sha1Msg1Inst : public Inst {
    IR::LiteralExprPtr a;
    IR::LiteralExprPtr b;
    public:
    Sha1Msg1Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                 IR::LiteralExprPtr a, IR::LiteralExprPtr b);

    IR::LiteralExprPtr get_a() const;
    IR::LiteralExprPtr get_b() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class Sha1Msg2Inst : public Inst {
    IR::LiteralExprPtr a;
    IR::LiteralExprPtr b;
    public:
    Sha1Msg2Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                 IR::LiteralExprPtr a, IR::LiteralExprPtr b);

    IR::LiteralExprPtr get_a() const;
    IR::LiteralExprPtr get_b() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class Sha256Rnds2Inst : public Inst {
    IR::LiteralExprPtr abef;
    IR::LiteralExprPtr cdgh;
    IR::LiteralExprPtr wk;
    public:
    Sha256Rnds2Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                    IR::LiteralExprPtr abef, IR::LiteralExprPtr cdgh, IR::LiteralExprPtr wk);

    IR::LiteralExprPtr get_abef() const;
    IR::LiteralExprPtr get_cdgh() const;
    IR::LiteralExprPtr get_wk() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class Sha256Msg1Inst : public Inst {
    IR::LiteralExprPtr a;
    IR::LiteralExprPtr b;
    public:
    Sha256Msg1Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                   IR::LiteralExprPtr a, IR::LiteralExprPtr b);

    IR::LiteralExprPtr get_a() const;
    IR::LiteralExprPtr get_b() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class Sha256Msg2Inst : public Inst {
    IR::LiteralExprPtr a;
    IR::LiteralExprPtr b;
    public:
    Sha256Msg2Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                   IR::LiteralExprPtr a, IR::LiteralExprPtr b);

    IR::LiteralExprPtr get_a() const;
    IR::LiteralExprPtr get_b() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

// ---- CRC32 ----
class Crc32Inst : public Inst {
    IR::LiteralExprPtr acc;
    IR::LiteralExprPtr data;
    IR::TypeExprPtr acc_type;
    IR::TypeExprPtr data_type;
    public:
    Crc32Inst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
              IR::LiteralExprPtr acc, IR::LiteralExprPtr data, IR::TypeExprPtr acc_type, IR::TypeExprPtr data_type);

    IR::LiteralExprPtr get_acc() const;
    IR::LiteralExprPtr get_data() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_acc_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_data_type() const;
    std::size_t get_acc_type_bitwidth() const;
    std::size_t get_data_type_bitwidth() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//---------------------------------System Call---------------------------------
class SyscallInst : public Inst {
    IR::LiteralExprPtr nr;
    std::vector<IR::LiteralExprPtr> args; // 0-6 entries
    bool noreturn_;
    bool nosideeffect;
    bool pure;
    public:
    //destination is nullptr if no return
    SyscallInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination,
                IR::LiteralExprPtr nr, std::vector<IR::LiteralExprPtr> args,
                bool noreturn_, bool nosideeffect, bool pure);

    IR::LiteralExprPtr get_nr() const;
    std::vector<IR::LiteralExprPtr> get_args() const;
    bool is_noreturn() const;
    bool is_nosideeffect() const;
    bool is_pure() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//---------------------------------CET Shadow Stack---------------------------------
class RdsspInst : public Inst {
    public:
    RdsspInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

// count must be >= 1; advances SSP by 8*count bytes.
class IncsspInst : public Inst {
    IR::LiteralExprPtr count;
    public:
    IncsspInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr count);

    IR::LiteralExprPtr get_count() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class SavePrevSspInst : public Inst {
    public:
    SavePrevSspInst(IR::InstructionStmtPtr instruction_stmt);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class RstorSspInst : public Inst {
    IR::LiteralExprPtr token_addr;
    public:
    RstorSspInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr token_addr);

    IR::LiteralExprPtr get_token_addr() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class SetssbsyInst : public Inst {
    public:
    SetssbsyInst(IR::InstructionStmtPtr instruction_stmt);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

// T must be i32 or i64; #[volatile] is implicit per the spec.
class WrssInst : public Inst {
    IR::LiteralExprPtr value;
    IR::TypeExprPtr value_type;
    IR::LiteralExprPtr addr;
    public:
    WrssInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr value, IR::LiteralExprPtr addr, IR::TypeExprPtr value_type);

    IR::LiteralExprPtr get_value() const;
    IR::LiteralExprPtr get_addr() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_value_type() const;
    std::size_t get_value_type_bitwidth() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};
}
}