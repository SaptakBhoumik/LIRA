#include "ast/ast.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt)>;
 
MIR::InstPtr analyze_and_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_nand_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_or_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                 MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_nor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_xor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_xnor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_shl_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_lshr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_ashr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_rotl_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_rotr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_pext_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_pdep_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_bitwise_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".and", analyze_and_bin_inst},
        {".nand", analyze_nand_bin_inst},
        {".or", analyze_or_bin_inst},
        {".nor", analyze_nor_bin_inst},
        {".xor", analyze_xor_bin_inst},
        {".xnor", analyze_xnor_bin_inst},
        {".shl", analyze_shl_bin_inst},
        {".lshr", analyze_lshr_bin_inst},
        {".ashr", analyze_ashr_bin_inst},
        {".rotl", analyze_rotl_bin_inst},
        {".rotr", analyze_rotr_bin_inst},
        {".pext", analyze_pext_bin_inst},
        {".pdep", analyze_pdep_bin_inst}
    };
    auto args = inst_stmt->get_value()->get_operands();
    auto _dest = inst_stmt->get_name();
    if(!_dest.has_value()){
        Utils::error(this->filename, name, "Bitwise binary instruction must have a destination i.e assign this instruction to a variable");
    }
    if(args.size() != 2){
        Utils::error(this->filename, name, "Bitwise binary instruction must have 2 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    for(size_t i = 0; i < args.size(); i++){
        args[i].second = Utils::get_reduced_type(this->type_symtable,args[i].second);
        if(!Utils::type_eq(type,args[i].second)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->to_string() + " is not the same as destination type " + type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, args[i].second,args[i].first)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->get_token().value + " is not compatible with assigned type " + args[i].second->to_string());
        }
    }
    auto type_variant = MIR::get_type_variant_from_type(type);
    if(!type_variant.has_value()){
        Utils::error(this->filename, name, "Unsupported type for bitwise binary instruction: " + type->to_string());
    }
    if(!MIR::is_int_typevariant(type_variant.value())){
        Utils::error(this->filename, name, "Only int types are supported for bitwise binary instruction");
    }

    //After this stage, type variant can only be int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),type_variant.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown bitwise binary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_and_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntAndInst>(inst_stmt,dest,lhs,rhs);
    }
    else{
        return std::make_shared<MIR::VecIntAndInst>(inst_stmt,dest,lhs,rhs);
    }
}
MIR::InstPtr analyze_nand_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntNandInst>(inst_stmt,dest,lhs,rhs);
    }
    else{
        return std::make_shared<MIR::VecIntNandInst>(inst_stmt,dest,lhs,rhs);
    }
}
MIR::InstPtr analyze_or_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                 MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"disjoint"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntOrInst>(inst_stmt,dest,lhs,rhs,flag_attrs["disjoint"]);
    }
    else{
        return std::make_shared<MIR::VecIntOrInst>(inst_stmt,dest,lhs,rhs,flag_attrs["disjoint"]);
    }
}
MIR::InstPtr analyze_nor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"disjoint"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntNorInst>(inst_stmt,dest,lhs,rhs,flag_attrs["disjoint"]);
    }
    else{
        return std::make_shared<MIR::VecIntNorInst>(inst_stmt,dest,lhs,rhs,flag_attrs["disjoint"]);
    }
}
MIR::InstPtr analyze_xor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntXorInst>(inst_stmt,dest,lhs,rhs);
    }
    else{
        return std::make_shared<MIR::VecIntXorInst>(inst_stmt,dest,lhs,rhs);
    }
}
MIR::InstPtr analyze_xnor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntXnorInst>(inst_stmt,dest,lhs,rhs);
    }
    else{
        return std::make_shared<MIR::VecIntXnorInst>(inst_stmt,dest,lhs,rhs);
    }
}
MIR::InstPtr analyze_shl_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                  MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nuw", "nsw"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntShlInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"]);
    }
    else{
        return std::make_shared<MIR::VecIntShlInst>(inst_stmt,dest,lhs,rhs,flag_attrs["nuw"],flag_attrs["nsw"]);
    }
}
MIR::InstPtr analyze_lshr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"exact"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntLshrInst>(inst_stmt,dest,lhs,rhs,flag_attrs["exact"]);
    }
    else{
        return std::make_shared<MIR::VecIntLshrInst>(inst_stmt,dest,lhs,rhs,flag_attrs["exact"]);
    }
}
MIR::InstPtr analyze_ashr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"exact"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntAshrInst>(inst_stmt,dest,lhs,rhs,flag_attrs["exact"]);
    }
    else{
        return std::make_shared<MIR::VecIntAshrInst>(inst_stmt,dest,lhs,rhs,flag_attrs["exact"]);
    }
}
MIR::InstPtr analyze_rotl_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntRotlInst>(inst_stmt,dest,lhs,rhs);
    }
    else{
        return std::make_shared<MIR::VecIntRotlInst>(inst_stmt,dest,lhs,rhs);
    }
}
MIR::InstPtr analyze_rotr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntRotrInst>(inst_stmt,dest,lhs,rhs);
    }
    else{
        return std::make_shared<MIR::VecIntRotrInst>(inst_stmt,dest,lhs,rhs);
    }
}
MIR::InstPtr analyze_pext_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntPextInst>(inst_stmt,dest,lhs,rhs);
    }
    else{
        return std::make_shared<MIR::VecIntPextInst>(inst_stmt,dest,lhs,rhs);
    }
}
MIR::InstPtr analyze_pdep_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise binary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntPdepInst>(inst_stmt,dest,lhs,rhs);
    }
    else{
        return std::make_shared<MIR::VecIntPdepInst>(inst_stmt,dest,lhs,rhs);
    }
}
}
}