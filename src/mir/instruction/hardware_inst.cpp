#include "mir/instruction/hardware_inst.hpp"
#include <cstddef>
#include <memory>
#include <optional>

namespace LIRA {
namespace MIR {
//---------------------------------Processor Identification Instructions ---------------------------------
CpuIdInst::CpuIdInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr leaf, IR::LiteralExprPtr subleaf):
                     Inst(instruction_stmt, destination, std::nullopt){
    this->leaf = leaf;
    this->subleaf = subleaf;
}
IR::LiteralExprPtr CpuIdInst::get_leaf() const{
    return this->leaf;
}
IR::LiteralExprPtr CpuIdInst::get_subleaf() const{
    return this->subleaf;
}
InstType CpuIdInst::get_inst_type() const{
    return InstType::CpuIdInst;
}
std::string CpuIdInst::to_string() const{
    std::string res = "let " + this->destination->to_string() + " = .cpuid(i32:" + this->leaf->to_string() + ", i32:" + this->subleaf->to_string() + ")";
    return res;
}


//---------------------------------Timestamp Counter Instructions---------------------------------
RdTscInst::RdTscInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination):
                     Inst(instruction_stmt, destination, std::nullopt){}
InstType RdTscInst::get_inst_type() const{
    return InstType::RdTscInst;
}
std::string RdTscInst::to_string() const{
    return "let " + this->destination->to_string() + " = .rdtsc()";
}


RdTscpInst::RdTscpInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination):
                     Inst(instruction_stmt, destination, std::nullopt){}
InstType RdTscpInst::get_inst_type() const{
    return InstType::RdTscpInst;
}
std::string RdTscpInst::to_string() const{
    return "let " + this->destination->to_string() + " = .rdtscp()";
}


//---------------------------------Hardware Random Number Instructions---------------------------------
RdrandInst::RdrandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination):
                     Inst(instruction_stmt, destination, std::nullopt){}
InstType RdrandInst::get_inst_type() const{
    return InstType::RdrandInst;
}
std::string RdrandInst::to_string() const{
    return "let " + this->destination->to_string() + " = .rdrand()";
}


RdseedInst::RdseedInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination):
                     Inst(instruction_stmt, destination, std::nullopt){}
InstType RdseedInst::get_inst_type() const{
    return InstType::RdseedInst;
}
std::string RdseedInst::to_string() const{
    return "let " + this->destination->to_string() + " = .rdseed()";
}


//---------------------------------Floating-Point Environment---------------------------------
GetFpEnvInst::GetFpEnvInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, bool x87):
                     Inst(instruction_stmt, destination, std::nullopt){
    this->x87 = x87;
}
bool GetFpEnvInst::is_x87() const{
    return this->x87;
}
InstType GetFpEnvInst::get_inst_type() const{
    return InstType::GetFpEnvInst;
}
std::string GetFpEnvInst::to_string() const{
    return "let " + this->destination->to_string() + " = .get_fp_env()" + (this->x87 ? " #[x87]" : "");
}


SetFpEnvInst::SetFpEnvInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr env, bool volatile_, bool x87):
                     Inst(instruction_stmt, nullptr, std::nullopt){
    this->env = env;
    this->volatile_ = volatile_;
    this->x87 = x87;
}
bool SetFpEnvInst::is_x87() const{
    return this->x87;
}
IR::LiteralExprPtr SetFpEnvInst::get_env() const{
    return this->env;
}
bool SetFpEnvInst::is_volatile() const{
    return this->volatile_;
}
InstType SetFpEnvInst::get_inst_type() const{
    return InstType::SetFpEnvInst;
}
std::string SetFpEnvInst::to_string() const{
    std::string T = this->x87 ? "i16" : "i32";
    return ".set_fp_env(" + T + ":" + this->env->to_string() + ")" + (this->volatile_ ? " #[volatile]" : "") + (this->x87 ? " #[x87]" : "");
}


FpenvGetFieldInst::FpenvGetFieldInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr env, FPEnvField field, bool x87):
                     Inst(instruction_stmt, destination, std::nullopt){
    this->env = env;
    this->field = field;
    this->x87 = x87;
}
bool FpenvGetFieldInst::is_x87() const{
    return this->x87;
}
IR::LiteralExprPtr FpenvGetFieldInst::get_env() const{
    return this->env;
}
FPEnvField FpenvGetFieldInst::get_field() const{
    return this->field;
}
InstType FpenvGetFieldInst::get_inst_type() const{
    return InstType::FpenvGetFieldInst;
}
std::string FpenvGetFieldInst::to_string() const{
    std::string T = this->x87 ? "i16" : "i32";
    return "let " + this->destination->to_string() + " = .fp_env_get_field(" + T + ":" + this->env->to_string() + ", str:\"" + MIR::to_string(this->field) + "\")" + (this->x87 ? " #[x87]" : "");
}


FpenvSetFieldInst::FpenvSetFieldInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr env, FPEnvField field, 
                      IR::LiteralExprPtr value, bool x87):
                     Inst(instruction_stmt, destination, std::nullopt){
    this->env = env;
    this->field = field;
    this->value = value;
    this->x87 = x87;
}
bool FpenvSetFieldInst::is_x87() const{
    return this->x87;
}
IR::LiteralExprPtr FpenvSetFieldInst::get_env() const{
    return this->env;
}
FPEnvField FpenvSetFieldInst::get_field() const{
    return this->field;
}
IR::LiteralExprPtr FpenvSetFieldInst::get_value() const{
    return this->value;
}
InstType FpenvSetFieldInst::get_inst_type() const{
    return InstType::FpenvSetFieldInst;
}
std::string FpenvSetFieldInst::to_string() const{
    std::string T = this->x87 ? "i16" : "i32";
    return "let " + this->destination->to_string() + " = .fp_env_set_field(" + T + ":" + this->env->to_string() + ", str:\"" + MIR::to_string(this->field) + "\", i32:" + this->value->to_string() + ")" + (this->x87 ? " #[x87]" : "");
}


GetFpStatusInst::GetFpStatusInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, bool x87):
                     Inst(instruction_stmt, destination, std::nullopt){
    this->x87 = x87;
}
bool GetFpStatusInst::is_x87() const{
    return this->x87;
}
InstType GetFpStatusInst::get_inst_type() const{
    return InstType::GetFpStatusInst;
}
std::string GetFpStatusInst::to_string() const{
    return "let " + this->destination->to_string() + " = .get_fp_status()" + (this->x87 ? " #[x87]" : "");
}


ClearFpStatusInst::ClearFpStatusInst(IR::InstructionStmtPtr instruction_stmt, bool x87):
                     Inst(instruction_stmt, nullptr, std::nullopt){
    this->x87 = x87;
}
bool ClearFpStatusInst::is_x87() const{
    return this->x87;
}
InstType ClearFpStatusInst::get_inst_type() const{
    return InstType::ClearFpStatusInst;
}
std::string ClearFpStatusInst::to_string() const{
    return (this->x87 ? ".clear_fp_status() #[x87]" : ".clear_fp_status()");
}
//---------------------------------Crypto Extensions---------------------------------
// ---- AES (all operate on <i8,16> blocks) ----
AesEncInst::AesEncInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                       IR::LiteralExprPtr state, IR::LiteralExprPtr roundkey):Inst(instruction_stmt, destination, std::nullopt){
    this->state = state;
    this->roundkey = roundkey;
}
IR::LiteralExprPtr AesEncInst::get_state() const{
    return this->state;
}
IR::LiteralExprPtr AesEncInst::get_roundkey() const{
    return this->roundkey;
}
InstType AesEncInst::get_inst_type() const{
    return InstType::AesEncInst;
}
std::string AesEncInst::to_string() const{
    return "let " + this->destination->to_string() + " = .aes_enc(<i8,16>:" + this->state->to_string() + ", <i8,16>:" + this->roundkey->to_string() + ")";
}


AesEncLastInst::AesEncLastInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                           IR::LiteralExprPtr state, IR::LiteralExprPtr roundkey):Inst(instruction_stmt, destination, std::nullopt){
    this->state = state;
    this->roundkey = roundkey;
}
IR::LiteralExprPtr AesEncLastInst::get_state() const{
    return this->state;
}
IR::LiteralExprPtr AesEncLastInst::get_roundkey() const{
    return this->roundkey;
}
InstType AesEncLastInst::get_inst_type() const{
    return InstType::AesEncLastInst;
}
std::string AesEncLastInst::to_string() const{
    return "let " + this->destination->to_string() + " = .aes_enc_last(<i8,16>:" + this->state->to_string() + ", <i8,16>:" + this->roundkey->to_string() + ")";
}


AesDecInst::AesDecInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                       IR::LiteralExprPtr state, IR::LiteralExprPtr roundkey):Inst(instruction_stmt, destination, std::nullopt){
    this->state = state;
    this->roundkey = roundkey;
}
IR::LiteralExprPtr AesDecInst::get_state() const{
    return this->state;
}
IR::LiteralExprPtr AesDecInst::get_roundkey() const{
    return this->roundkey;
}
InstType AesDecInst::get_inst_type() const{
    return InstType::AesDecInst;
}
std::string AesDecInst::to_string() const{
    return "let " + this->destination->to_string() + " = .aes_dec(<i8,16>:" + this->state->to_string() + ", <i8,16>:" + this->roundkey->to_string() + ")";
}


AesDecLastInst::AesDecLastInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                           IR::LiteralExprPtr state, IR::LiteralExprPtr roundkey):Inst(instruction_stmt, destination, std::nullopt){
    this->state = state;
    this->roundkey = roundkey;
}
IR::LiteralExprPtr AesDecLastInst::get_state() const{
    return this->state;
}
IR::LiteralExprPtr AesDecLastInst::get_roundkey() const{
    return this->roundkey;
}
InstType AesDecLastInst::get_inst_type() const{
    return InstType::AesDecLastInst;
}
std::string AesDecLastInst::to_string() const{
    return "let " + this->destination->to_string() + " = .aes_dec_last(<i8,16>:" + this->state->to_string() + ", <i8,16>:" + this->roundkey->to_string() + ")";
}


AesImcInst::AesImcInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                       IR::LiteralExprPtr roundkey):Inst(instruction_stmt, destination, std::nullopt){
    this->roundkey = roundkey;
}
IR::LiteralExprPtr AesImcInst::get_roundkey() const{
    return this->roundkey;
}
InstType AesImcInst::get_inst_type() const{
    return InstType::AesImcInst;
}
std::string AesImcInst::to_string() const{
    return "let " + this->destination->to_string() + " = .aes_imc(<i8,16>:" + this->roundkey->to_string() + ")";
}


AesKeyGenAssistInst::AesKeyGenAssistInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                                         IR::LiteralExprPtr a, IR::LiteralExprPtr rcon):Inst(instruction_stmt, destination, std::nullopt){
    this->a = a;
    this->rcon = rcon;
}
IR::LiteralExprPtr AesKeyGenAssistInst::get_a() const{
    return this->a;
}
IR::LiteralExprPtr AesKeyGenAssistInst::get_rcon() const{
    return this->rcon;
}
InstType AesKeyGenAssistInst::get_inst_type() const{
    return InstType::AesKeyGenAssistInst;
}
std::string AesKeyGenAssistInst::to_string() const{
    return "let " + this->destination->to_string() + " = .aeskeygenassist(<i8,16>:" + this->a->to_string() + ", <i8,16>:" + this->rcon->to_string() + ")";
}


// ---- Carry-less Multiply ----
ClmulInst::ClmulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                 IR::LiteralExprPtr a, IR::LiteralExprPtr b):
                     Inst(instruction_stmt, destination, std::nullopt){
    this->a = a;
    this->b = b;
}
IR::LiteralExprPtr ClmulInst::get_a() const{
    return this->a;
}
IR::LiteralExprPtr ClmulInst::get_b() const{
    return this->b;
}
InstType ClmulInst::get_inst_type() const{
    return InstType::ClmulInst;
}
std::string ClmulInst::to_string() const{
    return "let " + this->destination->to_string() + " = .clmul(i64:" + this->a->to_string() + ", i64:" + this->b->to_string() + ")";
}


// ---- SHA (all operate on <i32,4> state) ----
Sha1Rnds4Inst::Sha1Rnds4Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                             IR::LiteralExprPtr abcd, IR::LiteralExprPtr msg, IR::LiteralExprPtr func):Inst(instruction_stmt,destination,std::nullopt){
    this->abcd = abcd;
    this->msg = msg;
    this->func = func;
}
IR::LiteralExprPtr Sha1Rnds4Inst::get_abcd() const{
    return this->abcd;
}
IR::LiteralExprPtr Sha1Rnds4Inst::get_msg() const{
    return this->msg;
}
IR::LiteralExprPtr Sha1Rnds4Inst::get_func() const{
    return this->func;
}
InstType Sha1Rnds4Inst::get_inst_type() const{
    return InstType::Sha1Rnds4Inst;
}
std::string Sha1Rnds4Inst::to_string() const{
    return "let " + this->destination->to_string() + " = .sha1rnds4(<i32,4>:" + this->abcd->to_string() + ", <i32,4>:" + this->msg->to_string() + ", i8:" + this->func->to_string() + ")";
}


Sha1NextEInst::Sha1NextEInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                             IR::LiteralExprPtr abcd, IR::LiteralExprPtr e):Inst(instruction_stmt,destination,std::nullopt){
    this->abcd = abcd;
    this->e = e;
}
IR::LiteralExprPtr Sha1NextEInst::get_abcd() const{
    return this->abcd;
}
IR::LiteralExprPtr Sha1NextEInst::get_e() const{
    return this->e;
}
InstType Sha1NextEInst::get_inst_type() const{
    return InstType::Sha1NextEInst;
}
std::string Sha1NextEInst::to_string() const{
    return "let " + this->destination->to_string() + " = .sha1_next_e(<i32,4>:" + this->abcd->to_string() + ", <i32,4>:" + this->e->to_string() + ")";
}


Sha1Msg1Inst::Sha1Msg1Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                           IR::LiteralExprPtr a, IR::LiteralExprPtr b):Inst(instruction_stmt,destination,std::nullopt){
    this->a = a;
    this->b = b;
}
IR::LiteralExprPtr Sha1Msg1Inst::get_a() const{
    return this->a;
}
IR::LiteralExprPtr Sha1Msg1Inst::get_b() const{
    return this->b;
}
InstType Sha1Msg1Inst::get_inst_type() const{
    return InstType::Sha1Msg1Inst;
}
std::string Sha1Msg1Inst::to_string() const{
    return "let " + this->destination->to_string() + " = .sha1_msg1(<i32,4>:" + this->a->to_string() + ", <i32,4>:" + this->b->to_string() + ")";
}


Sha1Msg2Inst::Sha1Msg2Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                           IR::LiteralExprPtr a, IR::LiteralExprPtr b):Inst(instruction_stmt,destination,std::nullopt){
    this->a = a;
    this->b = b;
}
IR::LiteralExprPtr Sha1Msg2Inst::get_a() const{
    return this->a;
}
IR::LiteralExprPtr Sha1Msg2Inst::get_b() const{
    return this->b;
}
InstType Sha1Msg2Inst::get_inst_type() const{
    return InstType::Sha1Msg2Inst;
}
std::string Sha1Msg2Inst::to_string() const{
    return "let " + this->destination->to_string() + " = .sha1_msg2(<i32,4>:" + this->a->to_string() + ", <i32,4>:" + this->b->to_string() + ")";
}


Sha256Rnds2Inst::Sha256Rnds2Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                                 IR::LiteralExprPtr abef, IR::LiteralExprPtr cdgh, IR::LiteralExprPtr wk):Inst(instruction_stmt,destination,std::nullopt){
    this->abef = abef;
    this->cdgh = cdgh;
    this->wk = wk;
}
IR::LiteralExprPtr Sha256Rnds2Inst::get_abef() const{
    return this->abef;
}
IR::LiteralExprPtr Sha256Rnds2Inst::get_cdgh() const{
    return this->cdgh;
}
IR::LiteralExprPtr Sha256Rnds2Inst::get_wk() const{
    return this->wk;
}
InstType Sha256Rnds2Inst::get_inst_type() const{
    return InstType::Sha256Rnds2Inst;
}
std::string Sha256Rnds2Inst::to_string() const{
    return "let " + this->destination->to_string() + " = .sha256rnds2(<i32,4>:" + this->abef->to_string() + ", <i32,4>:" + this->cdgh->to_string() + ", <i32,4>:" + this->wk->to_string() + ")";
}


Sha256Msg1Inst::Sha256Msg1Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                             IR::LiteralExprPtr a, IR::LiteralExprPtr b):Inst(instruction_stmt,destination,std::nullopt){
    this->a = a;
    this->b = b;
}
IR::LiteralExprPtr Sha256Msg1Inst::get_a() const{
    return this->a;
}
IR::LiteralExprPtr Sha256Msg1Inst::get_b() const{
    return this->b;
}
InstType Sha256Msg1Inst::get_inst_type() const{
    return InstType::Sha256Msg1Inst;
}
std::string Sha256Msg1Inst::to_string() const{
    return "let " + this->destination->to_string() + " = .sha256_msg1(<i32,4>:" + this->a->to_string() + ", <i32,4>:" + this->b->to_string() + ")";
}


Sha256Msg2Inst::Sha256Msg2Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                             IR::LiteralExprPtr a, IR::LiteralExprPtr b):Inst(instruction_stmt,destination,std::nullopt){
    this->a = a;
    this->b = b;
}
IR::LiteralExprPtr Sha256Msg2Inst::get_a() const{
    return this->a;
}
IR::LiteralExprPtr Sha256Msg2Inst::get_b() const{
    return this->b;
}
InstType Sha256Msg2Inst::get_inst_type() const{
    return InstType::Sha256Msg2Inst;
}
std::string Sha256Msg2Inst::to_string() const{
    return "let " + this->destination->to_string() + " = .sha256_msg2(<i32,4>:" + this->a->to_string() + ", <i32,4>:" + this->b->to_string() + ")";
}


// ---- CRC32 ----
Crc32Inst::Crc32Inst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                     IR::LiteralExprPtr acc, IR::LiteralExprPtr data, IR::TypeExprPtr acc_type, IR::TypeExprPtr data_type):
                     Inst(instruction_stmt, destination, std::nullopt){
    this->acc = acc;
    this->data = data;
    this->acc_type = acc_type;
    this->data_type = data_type;
}
IR::LiteralExprPtr Crc32Inst::get_acc() const{
    return this->acc;
}
IR::LiteralExprPtr Crc32Inst::get_data() const{
    return this->data;
}
std::shared_ptr<IR::IntTypeExpr> Crc32Inst::get_casted_acc_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->acc_type);
}
std::shared_ptr<IR::IntTypeExpr> Crc32Inst::get_casted_data_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->data_type);
}
std::size_t Crc32Inst::get_acc_type_bitwidth() const{
    return get_casted_acc_type()->get_bits();
}
std::size_t Crc32Inst::get_data_type_bitwidth() const{
    return get_casted_data_type()->get_bits();
}
InstType Crc32Inst::get_inst_type() const{
    return InstType::Crc32Inst;
}
std::string Crc32Inst::to_string() const{
    return "let " + this->destination->to_string() + " = .crc32("+ this->acc_type->to_string() + ":" + this->acc->to_string() + ", " 
                                                                 + this->data_type->to_string() + ":" + this->data->to_string() + ")";
}


//---------------------------------System Call---------------------------------
SyscallInst::SyscallInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination,
                         IR::LiteralExprPtr nr, std::vector<IR::LiteralExprPtr> args,
                         bool noreturn_, bool nosideeffect, bool pure):Inst(instruction_stmt, destination, std::nullopt){
    this->nr = nr;
    this->args = args;
    this->noreturn_ = noreturn_;
    this->nosideeffect = nosideeffect;
    this->pure = pure;
}
IR::LiteralExprPtr SyscallInst::get_nr() const{
    return this->nr;
}
std::vector<IR::LiteralExprPtr> SyscallInst::get_args() const{
    return this->args;
}
bool SyscallInst::is_noreturn() const{
    return this->noreturn_;
}
bool SyscallInst::is_nosideeffect() const{
    return this->nosideeffect;
}
bool SyscallInst::is_pure() const{
    return this->pure;
}
InstType SyscallInst::get_inst_type() const{
    return InstType::SyscallInst;
}
std::string SyscallInst::to_string() const{
    std::string res = "let " + this->destination->to_string() + " = .syscall(i64:" + this->nr->to_string();
    for (const auto& arg : this->args){
        res += ", i64:" + arg->to_string();
    }
    res += ")";
    if(this->noreturn_){
        res += " #[noreturn]";
    }
    if(this->nosideeffect){
        res += " #[nosideeffect]";
    }
    if(this->pure){
        res += " #[pure]";
    }
    return res;
}


//---------------------------------CET Shadow Stack---------------------------------
RdsspInst::RdsspInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination):
                     Inst(instruction_stmt, destination, std::nullopt){}
InstType RdsspInst::get_inst_type() const{
    return InstType::RdsspInst;
}
std::string RdsspInst::to_string() const{
    return "let " + this->destination->to_string() + " = .rdssp()";
}


IncsspInst::IncsspInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr count):
                     Inst(instruction_stmt, nullptr, std::nullopt){
    this->count = count;
}
IR::LiteralExprPtr IncsspInst::get_count() const{
    return this->count;
}
InstType IncsspInst::get_inst_type() const{
    return InstType::IncsspInst;
}
std::string IncsspInst::to_string() const{
    return "let " + this->destination->to_string() + " = .incssp(i64:" + this->count->to_string() + ")";
}


SavePrevSspInst::SavePrevSspInst(IR::InstructionStmtPtr instruction_stmt):
                                Inst(instruction_stmt, nullptr, std::nullopt){}
InstType SavePrevSspInst::get_inst_type() const{
    return InstType::SavePrevSspInst;
}
std::string SavePrevSspInst::to_string() const{
    return ".save_prev_ssp()";
}


RstorSspInst::RstorSspInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr token_addr):
                                Inst(instruction_stmt, nullptr, std::nullopt){
    this->token_addr = token_addr;
}
IR::LiteralExprPtr RstorSspInst::get_token_addr() const{
    return this->token_addr;
}
InstType RstorSspInst::get_inst_type() const{
    return InstType::RstorSspInst;
}
std::string RstorSspInst::to_string() const{
    return ".rstor_ssp(ptr:" + this->token_addr->to_string() + ")";
}


SetssbsyInst::SetssbsyInst(IR::InstructionStmtPtr instruction_stmt):
                                Inst(instruction_stmt, nullptr, std::nullopt){}
InstType SetssbsyInst::get_inst_type() const{
    return InstType::SetssbsyInst;
}
std::string SetssbsyInst::to_string() const{
    return ".setssbsy()";
}


WrssInst::WrssInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr value, IR::LiteralExprPtr addr, IR::TypeExprPtr value_type):
                    Inst(instruction_stmt, nullptr, std::nullopt){
    this->value = value;
    this->addr = addr;
    this->value_type = value_type;
}
IR::LiteralExprPtr WrssInst::get_value() const{
    return this->value;
}
IR::LiteralExprPtr WrssInst::get_addr() const{
    return this->addr;
}
std::shared_ptr<IR::IntTypeExpr> WrssInst::get_casted_value_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->value_type);
}
std::size_t WrssInst::get_value_type_bitwidth() const{
    return this->get_casted_value_type()->get_bits();
}
InstType WrssInst::get_inst_type() const{
    return InstType::WrssInst;
}
std::string WrssInst::to_string() const{
    return ".wrss("+ this->value_type->to_string() + ":" + this->value->to_string() + ", ptr:" + this->addr->to_string() + ")";
}
}
}