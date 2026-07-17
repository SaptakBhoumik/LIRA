#include "ast/ast.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
#include <unordered_set>
namespace LIRA {
namespace SemanticAnalyzer {
//rhs is nullptr for stuff like carry_ashr,carry_lshr,carry_shl
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_carry_add_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                    IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_carry_sub_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                    IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_carry_shl_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                    IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_carry_lshr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_carry_ashr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_mac_wide_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                   IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_carry_shl_n_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                      IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_carry_lshr_n_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                       IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_carry_ashr_n_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                       IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_carry_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".carry_add",    analyze_carry_add_inst},
        {".carry_sub",    analyze_carry_sub_inst},
        {".carry_shl",    analyze_carry_shl_inst},
        {".carry_lshr",   analyze_carry_lshr_inst},
        {".carry_ashr",   analyze_carry_ashr_inst},
        {".mac_wide",     analyze_mac_wide_inst},
        {".carry_shl_n",  analyze_carry_shl_n_inst},
        {".carry_lshr_n", analyze_carry_lshr_n_inst},
        {".carry_ashr_n", analyze_carry_ashr_n_inst},
    };
    std::unordered_set<std::string> type1_carry = {".carry_add", ".carry_sub",".carry_shl",".carry_lshr",".carry_ashr"};//The carry is returned as i1 or vec of i1
    std::unordered_set<std::string> type2_carry = {".mac_wide", ".carry_shl_n", ".carry_lshr_n", ".carry_ashr_n"};//The carry is returned as int or vec of int and same type as the first struct field
    auto args = inst_stmt->get_value()->get_operands();
    if(args.size() != 3){
        if(args.size() == 2 && (name.value == ".carry_shl" || name.value == ".carry_lshr" || name.value == ".carry_ashr")){
            args.push_back(args[1]);
            args[1].first = nullptr;
            args[1].second = nullptr;
        }
        else{
            Utils::error(this->filename, name, "Carry binary instruction must have 3 arguments");
        }
    }
    auto dest = process_local_dest_arg(inst_stmt);
    if(dest == nullptr){
        Utils::error(this->filename, name, "Carry binary instruction must have a destination i.e assign this instruction to a variable");
    }
    IR::TypeExprPtr temp_type = dest->get_type();//Already reduced type by process_local_dest_arg
    IR::TypeExprPtr field1_type = nullptr;
    IR::TypeExprPtr field2_type = nullptr;
    if(temp_type->get_kind()!=IR::TypeExprKind::StructTypeExpr){
        Utils::error(this->filename, name, "Carry binary instruction destination type must be a struct type");
    }
    else{
        auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(temp_type);
        if(struct_type->get_fields().size() != 2){
            Utils::error(this->filename, name, "Carry binary instruction destination type must be a struct type with 2 fields");
        }
        else{
            field1_type = struct_type->get_fields()[0];
            field2_type = struct_type->get_fields()[1];
            if(type2_carry.find(name.value) != type2_carry.end()){
                if(!Utils::type_eq(field1_type,field2_type)){
                    Utils::error(this->filename, name, "Carry binary instruction destination type must be a struct type with 2 fields where the first field is the same type as the second field");
                }
            }
            else if(field2_type->get_kind()==IR::TypeExprKind::SIMDTypeExpr){
                if(field1_type->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
                    Utils::error(this->filename, name, "Carry binary instruction destination type must be a struct type with 2 fields where the first field is a vector type if the second field is a vector type");
                }
                auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(field2_type);
                auto simd_dest_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(field1_type);
                if(simd_dest_type->get_size() != simd_type->get_size()){
                    Utils::error(this->filename, name, "Carry binary instruction destination type must be a struct type with 2 fields where the first field is a vector type of the same size as the second field if the second field is a vector type");
                }
                else if(!Utils::is_int(simd_type->get_basetype(),1)){
                    Utils::error(this->filename, name, "Carry binary instruction destination type must be a struct type with 2 fields where the second field is a vector type with base type i1");
                }
            }
            else if(!Utils::is_int(field2_type,1)){
                Utils::error(this->filename, name, "Carry binary instruction destination type must be a struct type with 2 fields where the second field is a boolean type");
            }
        }
    }


    {
        args[0].second = Utils::get_reduced_type(this->type_symtable,args[0].second);
        if(!Utils::type_eq(field1_type,args[0].second)){
            Utils::error(this->filename, args[0].first->get_token(), "Argument type " + args[0].second->to_string() + " is not the same as destination type " + field1_type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, args[0].second,args[0].first)){
            Utils::error(this->filename, args[0].first->get_token(), "Argument " + args[0].first->to_string() + " is not compatible with assigned type " + args[0].second->to_string());
        }
    }
    if(args[1].second != nullptr){
        args[1].second = Utils::get_reduced_type(this->type_symtable,args[1].second);
        if(!Utils::type_eq(field1_type,args[1].second)){
            Utils::error(this->filename, args[1].first->get_token(), "Argument type " + args[1].second->to_string() + " is not the same as destination type " + field1_type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, args[1].second,args[1].first)){
            Utils::error(this->filename, args[1].first->get_token(), "Argument " + args[1].first->to_string() + " is not compatible with assigned type " + args[1].second->to_string());
        }
    }
    {
        args[2].second = Utils::get_reduced_type(this->type_symtable,args[2].second);
        if(!Utils::type_eq(field2_type,args[2].second)){
            Utils::error(this->filename, args[2].first->get_token(), "Argument type " + args[2].second->to_string() + " is not the same as destination type " + field2_type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, args[2].second,args[2].first)){
            Utils::error(this->filename, args[2].first->get_token(), "Argument " + args[2].first->to_string() + " is not compatible with assigned type " + args[2].second->to_string());
        }
    }
    
    auto type_variant = MIR::get_type_variant_from_type(field1_type);
    if(!type_variant.has_value()){
        Utils::error(this->filename, name, "Unsupported type for carry binary instruction: " + field1_type->to_string());
    }
    if(!MIR::is_int_typevariant(type_variant.value())){
        Utils::error(this->filename, name, "Only int types are supported for carry binary instruction");
    }
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),(args[1].first!=nullptr?args[1].first->get_literal():nullptr),args[2].first->get_literal(),type_variant.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown carry binary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_carry_add_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                    IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for carry instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCarrAddInst>(inst_stmt,dest,lhs,rhs,carr_borr,flag_attrs["unsigned"]);
    }
    else{
        return std::make_shared<MIR::VecIntCarrAddInst>(inst_stmt,dest,lhs,rhs,carr_borr,flag_attrs["unsigned"]);
    }
}

MIR::InstPtr analyze_carry_sub_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                    IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for carry instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCarrSubInst>(inst_stmt,dest,lhs,rhs,carr_borr,flag_attrs["unsigned"]);
    }
    else{
        return std::make_shared<MIR::VecIntCarrSubInst>(inst_stmt,dest,lhs,rhs,carr_borr,flag_attrs["unsigned"]);
    }
}

MIR::InstPtr analyze_carry_shl_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                    IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for carry instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCarrShlInst>(inst_stmt,dest,lhs,carr_borr);
    }
    else{
        return std::make_shared<MIR::VecIntCarrShlInst>(inst_stmt,dest,lhs,carr_borr);
    }
}

MIR::InstPtr analyze_carry_lshr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for carry instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCarrLshrInst>(inst_stmt,dest,lhs,carr_borr);
    }
    else{
        return std::make_shared<MIR::VecIntCarrLshrInst>(inst_stmt,dest,lhs,carr_borr);
    }
}

MIR::InstPtr analyze_carry_ashr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for carry instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCarrAshrInst>(inst_stmt,dest,lhs,carr_borr);
    }
    else{
        return std::make_shared<MIR::VecIntCarrAshrInst>(inst_stmt,dest,lhs,carr_borr);
    }
}

MIR::InstPtr analyze_mac_wide_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                   IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for carry instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntMacWideInst>(inst_stmt,dest,lhs,rhs,carr_borr,flag_attrs["unsigned"]);
    }
    else{
        return std::make_shared<MIR::VecIntMacWideInst>(inst_stmt,dest,lhs,rhs,carr_borr,flag_attrs["unsigned"]);
    }
}

MIR::InstPtr analyze_carry_shl_n_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                      IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for carry instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCarrShlNInst>(inst_stmt,dest,lhs,rhs,carr_borr);
    }
    else{
        return std::make_shared<MIR::VecIntCarrShlNInst>(inst_stmt,dest,lhs,rhs,carr_borr);
    }
}

MIR::InstPtr analyze_carry_lshr_n_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                       IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for carry instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCarrLshrNInst>(inst_stmt,dest,lhs,rhs,carr_borr);
    }
    else{
        return std::make_shared<MIR::VecIntCarrLshrNInst>(inst_stmt,dest,lhs,rhs,carr_borr);
    }
}

MIR::InstPtr analyze_carry_ashr_n_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                       IR::LiteralExprPtr carr_borr, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for carry instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntCarrAshrNInst>(inst_stmt,dest,lhs,rhs,carr_borr);
    }
    else{
        return std::make_shared<MIR::VecIntCarrAshrNInst>(inst_stmt,dest,lhs,rhs,carr_borr);
    }
}
}
}