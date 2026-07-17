#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <cstdint>
#include <iostream>
#include <functional>
#include <memory>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt)>;
                                                
MIR::InstPtr analyze_cpuid_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_rdtsc_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_rdtscp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_rdrand_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_rdseed_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_get_fpenv_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_set_fpenv_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fpenv_get_field_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fpenv_set_field_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_get_fpstatus_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_clear_fpstatus_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_aesenc_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_aesenclast_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_aesdec_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_aesdeclast_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_aesimc_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_aeskeygenassist_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_clmul_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_sha1rnds4_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_sha1nexte_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_sha1msg1_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_sha1msg2_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_sha256rnds2_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_sha256msg1_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_sha256msg2_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_crc32_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_syscall_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_rdssp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_incssp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_saveprevssp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_rstorssp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_setssbsy_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_wrss_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_hardware_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".cpuid", analyze_cpuid_inst},
        {".rdtsc", analyze_rdtsc_inst},
        {".rdtscp", analyze_rdtscp_inst},
        {".rdrand", analyze_rdrand_inst},
        {".rdseed", analyze_rdseed_inst},
        {".get_fpenv", analyze_get_fpenv_inst},
        {".set_fpenv", analyze_set_fpenv_inst},
        {".fpenv_get_field", analyze_fpenv_get_field_inst},
        {".fpenv_set_field", analyze_fpenv_set_field_inst},
        {".get_fpstatus", analyze_get_fpstatus_inst},
        {".clear_fpstatus", analyze_clear_fpstatus_inst},
        {".aesenc", analyze_aesenc_inst},
        {".aesenclast", analyze_aesenclast_inst},
        {".aesdec", analyze_aesdec_inst},
        {".aesdeclast", analyze_aesdeclast_inst},
        {".aesimc", analyze_aesimc_inst},
        {".aeskeygenassist", analyze_aeskeygenassist_inst},
        {".clmul", analyze_clmul_inst},
        {".sha1rnds4", analyze_sha1rnds4_inst},
        {".sha1nexte", analyze_sha1nexte_inst},
        {".sha1msg1", analyze_sha1msg1_inst},
        {".sha1msg2", analyze_sha1msg2_inst},
        {".sha256rnds2", analyze_sha256rnds2_inst},
        {".sha256msg1", analyze_sha256msg1_inst},
        {".sha256msg2", analyze_sha256msg2_inst},
        {".crc32", analyze_crc32_inst},
        {".syscall", analyze_syscall_inst},
        {".rdssp", analyze_rdssp_inst},
        {".incssp", analyze_incssp_inst},
        {".saveprevssp", analyze_saveprevssp_inst},
        {".rstorssp", analyze_rstorssp_inst},
        {".setssbsy", analyze_setssbsy_inst},
        {".wrss", analyze_wrss_inst},
    };
    auto args = inst_stmt->get_value()->get_operands();
    auto dest = process_local_dest_arg(inst_stmt);
    for(size_t i = 0; i < args.size(); i++){
        args[i].second = Utils::get_reduced_type(this->type_symtable,args[i].second);
        if(!Utils::type_compatible(this->var_symtable, args[i].second,args[i].first)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->get_token().value + " is not compatible with assigned type " + args[i].second->to_string());
        }
    }

    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,name,args,inst_stmt);
    }
    else{
        std::cerr << "Unknown hardware instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_cpuid_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction cpuid expects 2 arguments, but got " + std::to_string(args.size()));
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_int(args[i].second, 32)){
            Utils::error(filename, name, "Instruction cpuid expects arguments to be of type i32, but got argument " + std::to_string(i) + " of type " + args[i].second->to_string());
        }
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction cpuid expects a destination argument, but got none");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::StructTypeExpr){
        Utils::error(filename, name, "Instruction cpuid expects the destination argument to be of struct type, but got " + dest->get_type()->to_string());
    }
    else{
        auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(dest->get_type());
        if(struct_type->get_fields().size() != 4){
            Utils::error(filename, name, "Instruction cpuid expects the destination argument to be of struct type with 4 fields, but got " + std::to_string(struct_type->get_fields().size()));
        }
        for(size_t i = 0; i < struct_type->get_fields().size(); i++){
            if(!Utils::is_int(struct_type->get_fields()[i], 32)){
                Utils::error(filename, name, "Instruction cpuid expects the destination argument to be of struct type with 4 fields of i32 type, but got field " + std::to_string(i) + " of type " + struct_type->get_fields()[i]->to_string());
            }
        }
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction cpuid takes no attributes");
    }
    return std::make_shared<MIR::CpuIdInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_rdtsc_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction rdtsc expects no arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction rdtsc expects a destination argument, but got none");
    }
    if(!Utils::is_int(dest->get_type(), 64)){
        Utils::error(filename, name, "Instruction rdtsc expects the destination argument to be of type i64, but got " + dest->get_type()->to_string());
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction rdtsc takes no attributes");  
    }
    return std::make_shared<MIR::RdTscInst>(inst_stmt, dest);
}
MIR::InstPtr analyze_rdtscp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction rdtscp expects no arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction rdtscp expects a destination argument, but got none");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::StructTypeExpr){
        Utils::error(filename, name, "Instruction rdtscp expects the destination argument to be of struct type, but got " + dest->get_type()->to_string());
    }
    else{
        auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(dest->get_type());
        if(struct_type->get_fields().size() != 2){
            Utils::error(filename, name, "Instruction rdtscp expects the destination argument to be of struct type with 2 fields, but got " + std::to_string(struct_type->get_fields().size()));
        }
        if(!Utils::is_int(struct_type->get_fields()[0], 64)){
            Utils::error(filename, name, "Instruction rdtscp expects the first field of the destination argument to be of type i64, but got " + struct_type->get_fields()[0]->to_string());
        }
        if(!Utils::is_int(struct_type->get_fields()[1], 32)){
            Utils::error(filename, name, "Instruction rdtscp expects the second field of the destination argument to be of type i32, but got " + struct_type->get_fields()[1]->to_string());
        }
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction rdtscp takes no attributes");  
    }
    return std::make_shared<MIR::RdTscpInst>(inst_stmt, dest);
}
MIR::InstPtr analyze_rdrand_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction rdrand expects no arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction rdrand expects a destination argument, but got none");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::StructTypeExpr){
        Utils::error(filename, name, "Instruction rdrand expects the destination argument to be of struct type, but got " + dest->get_type()->to_string());
    }
    else{
        auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(dest->get_type());
        if(struct_type->get_fields().size() != 2){
            Utils::error(filename, name, "Instruction rdrand expects the destination argument to be of struct type with 2 fields, but got " + std::to_string(struct_type->get_fields().size()));
        }
        auto field1 = struct_type->get_fields()[0];
        if(!Utils::is_int(field1, 16) && !Utils::is_int(field1, 32) && !Utils::is_int(field1, 64)){
            Utils::error(filename, name, "Instruction rdrand expects the first field of the destination argument to be of type i16, i32 or i64, but got " + field1->to_string());
        }
        if(!Utils::is_int(struct_type->get_fields()[1], 1)){
            Utils::error(filename, name, "Instruction rdrand expects the second field of the destination argument to be of type i1, but got " + struct_type->get_fields()[1]->to_string());
        }
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction rdrand takes no attributes");  
    }
    return std::make_shared<MIR::RdrandInst>(inst_stmt, dest);
}
MIR::InstPtr analyze_rdseed_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction rdseed expects no arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction rdseed expects a destination argument, but got none");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::StructTypeExpr){
        Utils::error(filename, name, "Instruction rdseed expects the destination argument to be of struct type, but got " + dest->get_type()->to_string());
    }
    else{
        auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(dest->get_type());
        if(struct_type->get_fields().size() != 2){
            Utils::error(filename, name, "Instruction rdseed expects the destination argument to be of struct type with 2 fields, but got " + std::to_string(struct_type->get_fields().size()));
        }
        auto field1 = struct_type->get_fields()[0];
        if(!Utils::is_int(field1, 16) && !Utils::is_int(field1, 32) && !Utils::is_int(field1, 64)){
            Utils::error(filename, name, "Instruction rdseed expects the first field of the destination argument to be of type i16, i32 or i64, but got " + field1->to_string());
        }
        if(!Utils::is_int(struct_type->get_fields()[1], 1)){
            Utils::error(filename, name, "Instruction rdseed expects the second field of the destination argument to be of type i1, but got " + struct_type->get_fields()[1]->to_string());
        }
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction rdseed takes no attributes");  
    }
    return std::make_shared<MIR::RdseedInst>(inst_stmt, dest);
}
MIR::InstPtr analyze_get_fpenv_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction get_fpenv expects no arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction get_fpenv expects a destination argument, but got none");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"x87"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, name, "Instruction get_fpenv takes no attributes other than x87");
    }
    if(flag_attrs["x87"]){
        if(!Utils::is_int(dest->get_type(), 16)){
            Utils::error(filename, name, "Instruction get_fpenv with x87 flag expects the destination argument to be of type i16, but got " + dest->get_type()->to_string());
        }
    }
    else{
        if(!Utils::is_int(dest->get_type(), 32)){
            Utils::error(filename, name, "Instruction get_fpenv expects the destination argument to be of type i32, but got " + dest->get_type()->to_string());
        }
    }
    return std::make_shared<MIR::GetFpEnvInst>(inst_stmt, dest, flag_attrs["x87"]);
}
MIR::InstPtr analyze_set_fpenv_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction set_fpenv expects 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction set_fpenv expects no destination argument, but got one");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"x87","volatile"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, name, "Instruction set_fpenv takes no attributes other than x87 and volatile");
    }
    if(flag_attrs["x87"]){
        if(!Utils::is_int(args[0].second, 16)){
            Utils::error(filename, name, "Instruction set_fpenv with x87 flag expects the argument to be of type i16, but got " + args[0].second->to_string());
        }
    }
    else{
        if(!Utils::is_int(args[0].second, 32)){
            Utils::error(filename, name, "Instruction set_fpenv expects the argument to be of type i32, but got " + args[0].second->to_string());
        }
    }
    return std::make_shared<MIR::SetFpEnvInst>(inst_stmt, args[0].first->get_literal(), flag_attrs["volatile"], flag_attrs["x87"]);
}
MIR::InstPtr analyze_fpenv_get_field_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction fpenv_get_field expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction fpenv_get_field expects a destination argument, but got none");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"x87"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, name, "Instruction fpenv_get_field takes no attributes other than x87");
    }
    if(flag_attrs["x87"]){
        if(!Utils::is_int(args[0].second, 16)){
            Utils::error(filename, name, "Instruction fpenv_get_field with x87 flag expects the first argument to be of type i16, but got " + args[0].second->to_string());
        }
    }
    else{
        if(!Utils::is_int(args[0].second, 32)){
            Utils::error(filename, name, "Instruction fpenv_get_field expects the first argument to be of type i32, but got " + args[0].second->to_string());
        }
    }
    if(!Utils::is_int(dest->get_type(), 32)){
        Utils::error(filename, name, "Instruction fpenv_get_field expects the destination argument to be of type i32, but got " + dest->get_type()->to_string());
    }
    auto field = Utils::get_fpenv_field(args[1].first, flag_attrs["x87"]);
    if(!field.has_value()){
        Utils::error(filename, name, "Instruction fpenv_get_field expects the second argument to be a valid fpenv field, but got " + args[1].first->to_string());
    }
    return std::make_shared<MIR::FpenvGetFieldInst>(inst_stmt, dest, args[0].first->get_literal(), field.value(), flag_attrs["x87"]);
}
MIR::InstPtr analyze_fpenv_set_field_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction fpenv_set_field expects 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction fpenv_set_field expects a destination argument, but got none");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"x87"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, name, "Instruction fpenv_set_field takes no attributes other than x87");
    }
    if(!Utils::is_int(args[2].second, 32)){
        Utils::error(filename, name, "Instruction fpenv_set_field expects the third argument to be of type i32, but got " + args[2].second->to_string());
    }
    auto field = Utils::get_fpenv_field(args[1].first, flag_attrs["x87"]);
    if(!field.has_value()){
        Utils::error(filename, name, "Instruction fpenv_set_field expects the second argument to be a valid fpenv field, but got " + args[1].first->to_string());
    }
    if(flag_attrs["x87"]){
        if(!Utils::is_int(args[0].second, 16)){
            Utils::error(filename, name, "Instruction fpenv_set_field with x87 flag expects the first argument to be of type i16, but got " + args[0].second->to_string());
        }
    }
    else{
        if(!Utils::is_int(args[0].second, 32)){
            Utils::error(filename, name, "Instruction fpenv_set_field expects the first argument to be of type i32, but got " + args[0].second->to_string());
        }
    }
    if(!Utils::type_eq(dest->get_type(), args[0].second)){
        Utils::error(filename, name, "Instruction fpenv_set_field expects the destination argument to be of the same type as the first argument, but got destination of type " + dest->get_type()->to_string() + " and first argument of type " + args[0].second->to_string());
    }
    return std::make_shared<MIR::FpenvSetFieldInst>(inst_stmt, dest, args[0].first->get_literal(), field.value(), args[2].first->get_literal(), flag_attrs["x87"]);
}
MIR::InstPtr analyze_get_fpstatus_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction get_fpstatus expects no arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction get_fpstatus expects a destination argument, but got none");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"x87"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, name, "Instruction get_fpstatus takes no attributes other than x87");
    }
    if(flag_attrs["x87"]){
        if(!Utils::is_int(dest->get_type(), 16)){
            Utils::error(filename, name, "Instruction get_fpstatus with x87 flag expects the destination argument to be of type i16, but got " + dest->get_type()->to_string());
        }
    }
    else{
        if(!Utils::is_int(dest->get_type(), 32)){
            Utils::error(filename, name, "Instruction get_fpstatus expects the destination argument to be of type i32, but got " + dest->get_type()->to_string());
        }
    }
    return std::make_shared<MIR::GetFpStatusInst>(inst_stmt, dest, flag_attrs["x87"]);
}
MIR::InstPtr analyze_clear_fpstatus_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction clear_fpstatus expects no arguments, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction clear_fpstatus expects no destination argument, but got one");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"x87"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, name, "Instruction clear_fpstatus takes no attributes other than x87");
    }
    return std::make_shared<MIR::ClearFpStatusInst>(inst_stmt, flag_attrs["x87"]);
}
MIR::InstPtr analyze_aesenc_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction aesenc expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction aesenc expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction aesenc takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 8, 16)){
        Utils::error(filename, name, "Instruction aesenc expects the destination argument to be of type vector<16 x i8>, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_vector_of_int(args[i].second, 8, 16)){
            Utils::error(filename, name, "Instruction aesenc expects the argument " + std::to_string(i) + " to be of type vector<16 x i8>, but got " + args[i].second->to_string());
        }
    }
    return std::make_shared<MIR::AesEncInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_aesenclast_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction aesenclast expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction aesenclast expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction aesenclast takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 8, 16)){
        Utils::error(filename, name, "Instruction aesenclast expects the destination argument to be of type vector<16 x i8>, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_vector_of_int(args[i].second, 8, 16)){
            Utils::error(filename, name, "Instruction aesenclast expects the argument " + std::to_string(i) + " to be of type vector<16 x i8>, but got " + args[i].second->to_string());
        }
    }
    return std::make_shared<MIR::AesEncLastInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_aesdec_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction aesdec expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction aesdec expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction aesdec takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 8, 16)){
        Utils::error(filename, name, "Instruction aesdec expects the destination argument to be of type vector<16 x i8>, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_vector_of_int(args[i].second, 8, 16)){
            Utils::error(filename, name, "Instruction aesdec expects the argument " + std::to_string(i) + " to be of type vector<16 x i8>, but got " + args[i].second->to_string());
        }
    }
    return std::make_shared<MIR::AesDecInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_aesdeclast_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction aesdeclast expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction aesdeclast expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction aesdeclast takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 8, 16)){
        Utils::error(filename, name, "Instruction aesdeclast expects the destination argument to be of type vector<16 x i8>, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_vector_of_int(args[i].second, 8, 16)){
            Utils::error(filename, name, "Instruction aesdeclast expects the argument " + std::to_string(i) + " to be of type vector<16 x i8>, but got " + args[i].second->to_string());
        }
    }
    return std::make_shared<MIR::AesDecLastInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_aesimc_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction aesimc expects 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction aesimc expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction aesimc takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 8, 16)){
        Utils::error(filename, name, "Instruction aesimc expects the destination argument to be of type vector<16 x i8>, but got " + dest->get_type()->to_string());
    }
    if(!Utils::is_vector_of_int(args[0].second, 8, 16)){
        Utils::error(filename, name, "Instruction aesimc expects the argument to be of type vector<16 x i8>, but got " + args[0].second->to_string());
    }
    return std::make_shared<MIR::AesImcInst>(inst_stmt, dest, args[0].first->get_literal());
}
MIR::InstPtr analyze_aeskeygenassist_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction aeskeygenassist expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction aeskeygenassist expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction aeskeygenassist takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 8, 16)){
        Utils::error(filename, name, "Instruction aeskeygenassist expects the destination argument to be of type vector<16 x i8>, but got " + dest->get_type()->to_string());
    }
    if(!Utils::is_vector_of_int(args[0].second, 8, 16)){
        Utils::error(filename, name, "Instruction aeskeygenassist expects the first argument to be of type vector<16 x i8>, but got " + args[0].second->to_string());
    }
    if(!Utils::is_int(args[1].second, 8)){
        Utils::error(filename, name, "Instruction aeskeygenassist expects the second argument to be of type i8, but got " + args[1].second->to_string());
    }
    return std::make_shared<MIR::AesKeyGenAssistInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_clmul_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction clmul expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction clmul expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction clmul takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 64, 2)){
        Utils::error(filename, name, "Instruction clmul expects the destination argument to be of type vector<2 x i64>, but got " + dest->get_type()->to_string());
    }
    if(!Utils::is_int(args[0].second, 64)){
        Utils::error(filename, name, "Instruction clmul expects the first argument to be of type i64, but got " + args[0].second->to_string());
    }
    if(!Utils::is_int(args[1].second, 64)){
        Utils::error(filename, name, "Instruction clmul expects the second argument to be of type i64, but got " + args[1].second->to_string());
    }
    return std::make_shared<MIR::ClmulInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_sha1rnds4_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction sha1rnds4 expects 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction sha1rnds4 expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction sha1rnds4 takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 32, 4)){
        Utils::error(filename, name, "Instruction sha1rnds4 expects the destination argument to be of type vector<4 x i32>, but got " + dest->get_type()->to_string());
    }
    if(!Utils::is_vector_of_int(args[0].second, 32, 4)){
        Utils::error(filename, name, "Instruction sha1rnds4 expects the first argument to be of type vector<4 x i32>, but got " + args[0].second->to_string());
    }
    if(!Utils::is_vector_of_int(args[1].second, 32, 4)){
        Utils::error(filename, name, "Instruction sha1rnds4 expects the second argument to be of type vector<4 x i32>, but got " + args[1].second->to_string());
    }
    if(!Utils::is_int(args[2].second, 8)){
        Utils::error(filename, name, "Instruction sha1rnds4 expects the third argument to be of type i8, but got " + args[2].second->to_string());
    }
    if(Utils::is_constexpr(args[2].first)){
        auto val = Utils::to_numeric<int8_t>(filename,args[2].first,args[2].second);
        if(val < 0 || val > 3){
            Utils::error(filename, name, "Instruction sha1rnds4 expects the third argument to be a constant integer in the range [0,3], but got " + std::to_string(val));
        }
    }
    return std::make_shared<MIR::Sha1Rnds4Inst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal());
}
MIR::InstPtr analyze_sha1nexte_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction sha1nexte expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction sha1nexte expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction sha1nexte takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 32, 4)){
        Utils::error(filename, name, "Instruction sha1nexte expects the destination argument to be of type vector<4 x i32>, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_vector_of_int(args[i].second, 32, 4)){
            Utils::error(filename, name, "Instruction sha1nexte expects the argument " + std::to_string(i) + " to be of type vector<4 x i32>, but got " + args[i].second->to_string());
        }
    }
    return std::make_shared<MIR::Sha1NextEInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_sha1msg1_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction sha1msg1 expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction sha1msg1 expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction sha1msg1 takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 32, 4)){
        Utils::error(filename, name, "Instruction sha1msg1 expects the destination argument to be of type vector<4 x i32>, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_vector_of_int(args[i].second, 32, 4)){
            Utils::error(filename, name, "Instruction sha1msg1 expects the argument " + std::to_string(i) + " to be of type vector<4 x i32>, but got " + args[i].second->to_string());
        }
    }
    return std::make_shared<MIR::Sha1Msg1Inst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_sha1msg2_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction sha1msg2 expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction sha1msg2 expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction sha1msg2 takes no attributes");   
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 32, 4)){
        Utils::error(filename, name, "Instruction sha1msg2 expects the destination argument to be of type vector<4 x i32>, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_vector_of_int(args[i].second, 32, 4)){
            Utils::error(filename, name, "Instruction sha1msg2 expects the argument " + std::to_string(i) + " to be of type vector<4 x i32>, but got " + args[i].second->to_string());
        }
    }
    return std::make_shared<MIR::Sha1Msg2Inst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_sha256rnds2_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction sha256rnds2 expects 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction sha256rnds2 expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction sha256rnds2 takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 32, 4)){
        Utils::error(filename, name, "Instruction sha256rnds2 expects the destination argument to be of type vector<4 x i32>, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_vector_of_int(args[i].second, 32, 4)){
            Utils::error(filename, name, "Instruction sha256rnds2 expects the argument "+ std::to_string(i) + " to be of type vector<4 x i32>, but got " + args[i].second->to_string());
        }
    }
    return std::make_shared<MIR::Sha256Rnds2Inst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal());
}
MIR::InstPtr analyze_sha256msg1_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction sha256msg1 expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction sha256msg1 expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction sha256msg1 takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 32, 4)){
        Utils::error(filename, name, "Instruction sha256msg1 expects the destination argument to be of type vector<4 x i32>, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_vector_of_int(args[i].second, 32, 4)){
            Utils::error(filename, name, "Instruction sha256msg1 expects the argument "+ std::to_string(i) + " to be of type vector<4 x i32>, but got " + args[i].second->to_string());
        }
    }
    return std::make_shared<MIR::Sha256Msg1Inst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_sha256msg2_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction sha256msg2 expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction sha256msg2 expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction sha256msg2 takes no attributes");
    }
    if(!Utils::is_vector_of_int(dest->get_type(), 32, 4)){
        Utils::error(filename, name, "Instruction sha256msg2 expects the destination argument to be of type vector<4 x i32>, but got " + dest->get_type()->to_string());
    }
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_vector_of_int(args[i].second, 32, 4)){
            Utils::error(filename, name, "Instruction sha256msg2 expects the argument "+ std::to_string(i) + " to be of type vector<4 x i32>, but got " + args[i].second->to_string());
        }
    }
    return std::make_shared<MIR::Sha256Msg2Inst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal());
}
MIR::InstPtr analyze_crc32_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction crc32 expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction crc32 expects a destination argument, but got none");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction crc32 takes no attributes");
    }
    if(!Utils::type_eq(dest->get_type(), args[0].second)){
        Utils::error(filename, name, "Instruction crc32 expects the destination argument to be of the same type as the first argument, but got " + dest->get_type()->to_string() + " and " + args[0].second->to_string());
    }
    if(Utils::is_int(args[0].second, 32)){
        if(!Utils::is_int(args[1].second, 8) && !Utils::is_int(args[1].second, 16) && !Utils::is_int(args[1].second, 32)){
            Utils::error(filename, name, "Instruction crc32 expects the second argument to be of type i8, i16 or i32, but got " + args[1].second->to_string());
        }
    }
    else if(Utils::is_int(args[0].second, 64)){
        if(!Utils::is_int(args[1].second, 8) && !Utils::is_int(args[1].second, 64)){
            Utils::error(filename, name, "Instruction crc32 expects the second argument to be of type i8 or i64, but got " + args[1].second->to_string());
        }
    }
    else{
        Utils::error(filename, name, "Instruction crc32 expects the first argument to be of type i32 or i64, but got " + args[0].second->to_string());
    }
    return std::make_shared<MIR::Crc32Inst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[0].second, args[1].second);
}
MIR::InstPtr analyze_syscall_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() > 7){
        Utils::error(filename, name, "Instruction syscall expects at most 7 arguments, but got " + std::to_string(args.size()));
    }
    if(args.size() < 1){
        Utils::error(filename, name, "Instruction syscall expects at least 1 argument, but got " + std::to_string(args.size()));
    }
    std::vector<IR::LiteralExprPtr> arg_literals;
    for(size_t i = 0; i < args.size(); i++){
        if(!Utils::is_int(args[i].second, 64)){
            Utils::error(filename, name, "Instruction syscall expects the argument " + std::to_string(i) + " to be of type i64, but got " + args[i].second->to_string());
        }
        if(i!=0){//The first one is the syscall number
            arg_literals.push_back(args[i].first->get_literal());
        }
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"noreturn","nosideeffect","pure"});
    if(remaining_attrs.size() != 0){
        Utils::error(filename, name, "Instruction syscall takes only the attributes noreturn, nosideeffect and pure");
    }
    if(dest == nullptr && !flag_attrs["noreturn"]){
        Utils::error(filename, name, "Instruction syscall expects a destination argument, but got none");
    }
    if(dest != nullptr){
        if(!Utils::is_int(dest->get_type(), 64)){
            Utils::error(filename, name, "Instruction syscall expects the destination argument to be of type i64, but got " + dest->get_type()->to_string());
        }
        if(flag_attrs["noreturn"]){
            Utils::error(filename, name, "Instruction syscall cannot have a destination argument if noreturn attribute is specified");
        }
    }
    return std::make_shared<MIR::SyscallInst>(inst_stmt, dest, args[0].first->get_literal(), arg_literals, flag_attrs["noreturn"], flag_attrs["nosideeffect"], flag_attrs["pure"]);
}
MIR::InstPtr analyze_rdssp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction rdssp expects no arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction rdssp expects a destination argument, but got none");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction rdssp expects the destination argument to be of pointer type, but got " + dest->get_type()->to_string());
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction rdssp takes no attributes");
    }
    return std::make_shared<MIR::RdsspInst>(inst_stmt, dest);
}
MIR::InstPtr analyze_incssp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction incssp expects 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction incssp expects no destination argument, but got one");
    }
    if(!Utils::is_int(args[0].second, 64)){
        Utils::error(filename, name, "Instruction incssp expects the argument to be of type i64, but got " + args[0].second->to_string());
    }
    if(Utils::is_constexpr(args[0].first)){
        auto val = Utils::to_numeric<uint64_t>(filename, args[0].first, args[0].second);
        if(val < 1){
            Utils::error(filename, name, "Instruction incssp expects the argument to be a constant integer greater than 0, but got " + std::to_string(val));
        }
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction incssp takes no attributes");
    }
    return std::make_shared<MIR::IncsspInst>(inst_stmt, args[0].first->get_literal());
}
MIR::InstPtr analyze_saveprevssp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction saveprevssp expects no arguments, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction saveprevssp expects no destination argument, but got one");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction saveprevssp takes no attributes");
    }
    return std::make_shared<MIR::SavePrevSspInst>(inst_stmt);
}
MIR::InstPtr analyze_rstorssp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction rstorssp expects 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction rstorssp expects no destination argument, but got one");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction rstorssp expects the argument to be of pointer type, but got " + args[0].second->to_string());
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction rstorssp takes no attributes");
    }
    return std::make_shared<MIR::RstorSspInst>(inst_stmt, args[0].first->get_literal());
}
MIR::InstPtr analyze_setssbsy_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction setssbsy expects no arguments, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction setssbsy expects no destination argument, but got one");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction setssbsy takes no attributes");
    }
    return std::make_shared<MIR::SetssbsyInst>(inst_stmt);
}
MIR::InstPtr analyze_wrss_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction wrss expects 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction wrss expects no destination argument, but got one");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction wrss takes no attributes");
    }
    if(!Utils::is_int(args[0].second, 64) && !Utils::is_int(args[0].second, 32)){
        Utils::error(filename, name, "Instruction wrss expects the first argument to be of type i64 or i32, but got " + args[0].second->to_string());
    }
    if(args[1].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction wrss expects the second argument to be of pointer type, but got " + args[1].second->to_string());
    }
    return std::make_shared<MIR::WrssInst>(inst_stmt, args[0].first->get_literal(), args[1].first->get_literal(), args[0].second);
}
}
}