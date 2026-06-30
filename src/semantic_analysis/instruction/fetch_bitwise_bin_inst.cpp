#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
namespace LIRA {
namespace SemanticAnalyzer {
//In case we allow vector/float type in future so dispatch funciton must take in the type varient argument as well even if useless right now
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt)>;
 
MIR::InstPtr analyze_fetch_and_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_nand_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_or_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                       MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_nor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_xor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_xnor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_shl_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_lshr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_ashr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_rotl_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_rotr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_pext_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_pdep_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_bitwise_fetch_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".fetch_and",  analyze_fetch_and_bin_inst},
        {".fetch_nand", analyze_fetch_nand_bin_inst},
        {".fetch_or",   analyze_fetch_or_bin_inst},
        {".fetch_nor",  analyze_fetch_nor_bin_inst},
        {".fetch_xor",  analyze_fetch_xor_bin_inst},
        {".fetch_xnor", analyze_fetch_xnor_bin_inst},
        {".fetch_shl",  analyze_fetch_shl_bin_inst},
        {".fetch_lshr", analyze_fetch_lshr_bin_inst},
        {".fetch_ashr", analyze_fetch_ashr_bin_inst},
        {".fetch_rotl", analyze_fetch_rotl_bin_inst},
        {".fetch_rotr", analyze_fetch_rotr_bin_inst},
        {".fetch_pext", analyze_fetch_pext_bin_inst},
        {".fetch_pdep", analyze_fetch_pdep_bin_inst},
    };
    auto args = inst_stmt->get_value()->get_operands();
    auto _dest = inst_stmt->get_name();
    if(!_dest.has_value()){
        Utils::error(this->filename, name, "Bitwise binary fetch instruction must have a destination i.e assign this instruction to a variable");
    }
    if(args.size() != 2){
        Utils::error(this->filename, name, "Bitwise binary fetch instruction must have 2 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [common_fetch_attrs,remaining_attrs] = Utils::extract_common_atomic_attrs(this->filename,attributes);
    if(Utils::get_type_size(type) > 128 && common_fetch_attrs.atomic_ordering.has_value()){
        Utils::error(this->filename, name, "Atomic bitwise binary fetch instruction destination type size must be less than or equal to 128 bits. Found: " + std::to_string(Utils::get_type_size(type)) + " bits");
    }
    
    {
        args[0].second = Utils::get_reduced_type(this->type_symtable,args[0].second);
        if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
            Utils::error(this->filename, args[0].first->get_token(), "Argument type " + args[0].second->to_string() + " is not a pointer type");
        }
        else if(!Utils::type_compatible(this->var_symtable, args[0].second,args[0].first)){
            Utils::error(this->filename, args[0].first->get_token(), "Argument type ptr is not compatible with assigned type " + args[0].first->to_string());
        }
    }
    {
        args[1].second = Utils::get_reduced_type(this->type_symtable,args[1].second);
        if(!Utils::type_eq(type,args[1].second)){
            Utils::error(this->filename, args[1].first->get_token(), "Argument type " + args[1].second->to_string() + " is not the same as destination type " + type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, args[1].second,args[1].first)){
            Utils::error(this->filename, args[1].first->get_token(), "Argument type " + args[1].second->to_string() + " is not compatible with assigned type " + args[1].first->to_string());
        }
    }
    auto type_variant = MIR::get_type_variant_from_type(type);
    if(!type_variant.has_value()){
        Utils::error(this->filename, name, "Unsupported type for bitwise binary fetch instruction: " + type->to_string());
    }
    if(MIR::is_vector_typevariant(type_variant.value())){
        Utils::error(this->filename, name, "Vector type is not supported for bitwise binary fetch instruction: " + type->to_string());
    }
    if(type_variant.value() != MIR::TypeVariant::Int){
        Utils::error(this->filename, name, "Only int types are supported for bitwise binary fetch instruction");
    }

    //After this stage, type variant can only be float or int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),type_variant.value(),common_fetch_attrs,remaining_attrs,inst_stmt);
    }
    else{
        std::cerr << "Unknown bitwise binary fetch instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}
MIR::InstPtr analyze_fetch_and_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + attributes[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchAndInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_nand_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + attributes[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchNandInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_or_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                       MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes,{"disjoint"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchOrInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["disjoint"]);
}
MIR::InstPtr analyze_fetch_nor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes,{"disjoint"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchNorInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["disjoint"]);
}
MIR::InstPtr analyze_fetch_xor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + attributes[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchXorInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_xnor_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + attributes[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchXnorInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_shl_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes,{"nuw","nsw"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchShlInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["nuw"],flag_attrs["nsw"]);
}
MIR::InstPtr analyze_fetch_lshr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes,{"exact"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchLshrInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["exact"]);
}
MIR::InstPtr analyze_fetch_ashr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes,{"exact"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchAshrInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["exact"]);
}
MIR::InstPtr analyze_fetch_rotl_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + attributes[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchRotlInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_rotr_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + attributes[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchRotrInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_pext_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + attributes[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchPextInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs);
}
MIR::InstPtr analyze_fetch_pdep_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for bitwise binary fetch instruction: " + attributes[0]->to_string());
    }
    return std::make_shared<MIR::IntFetchPdepInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs);
}
}
}