#include "ast/ast.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt)>;
 
MIR::InstPtr analyze_wrap_add_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_wrap_sub_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_wrap_absdiff_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                       MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_wrap_mul_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_wrap_div_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_wrap_rem_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_wrap_copysign_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                        MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_wrap_shl_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_wrap_lshr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_wrap_ashr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);


MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_wrap_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".wrap_add", analyze_wrap_add_inst},
        {".wrap_sub", analyze_wrap_sub_inst},
        {".wrap_absdiff", analyze_wrap_absdiff_inst},
        {".wrap_mul", analyze_wrap_mul_inst},
        {".wrap_div", analyze_wrap_div_inst},
        {".wrap_rem", analyze_wrap_rem_inst},
        {".wrap_copysign", analyze_wrap_copysign_inst},
        {".wrap_shl", analyze_wrap_shl_inst},
        {".wrap_lshr", analyze_wrap_lshr_inst},
        {".wrap_ashr", analyze_wrap_ashr_inst},
    };
    auto args = inst_stmt->get_value()->get_operands();
    if(args.size() != 2){
        Utils::error(this->filename, name, "Wrap binary instruction must have 2 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    if(dest == nullptr){
        Utils::error(this->filename, name, "Wrap binary instruction must have a destination i.e assign this instruction to a variable");
    }
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    if(type->get_kind()!=IR::TypeExprKind::StructTypeExpr){
        Utils::error(this->filename, name, "Wrap binary instruction destination type must be a struct type");
    }
    else{
        auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(type);
        if(struct_type->get_fields().size() != 2){
            Utils::error(this->filename, name, "Wrap binary instruction destination type must be a struct type with 2 fields");
        }
        else{
            type = struct_type->get_fields()[0];
            auto field2_type = struct_type->get_fields()[1];
            if(field2_type->get_kind()==IR::TypeExprKind::SIMDTypeExpr){
                if(type->get_kind() != IR::TypeExprKind::SIMDTypeExpr){
                    Utils::error(this->filename, name, "Wrap binary instruction destination type must be a struct type with 2 fields where the first field is a vector type if the second field is a vector type");
                }
                auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(field2_type);
                auto simd_dest_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(type);
                if(simd_dest_type->get_size() != simd_type->get_size()){
                    Utils::error(this->filename, name, "Wrap binary instruction destination type must be a struct type with 2 fields where the first field is a vector type of the same size as the second field if the second field is a vector type");
                }
                else if(!Utils::is_int(simd_type->get_basetype(),1)){
                    Utils::error(this->filename, name, "Wrap binary instruction destination type must be a struct type with 2 fields where the second field is a vector type with base type i1");
                }
            }
            else if(!Utils::is_int(field2_type,1)){
                Utils::error(this->filename, name, "Wrap binary instruction destination type must be a struct type with 2 fields where the second field is a boolean type");
            }
        }
    }
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
        Utils::error(this->filename, name, "Unsupported type for wrap binary instruction: " + type->to_string());
    }
    if(!MIR::is_int_typevariant(type_variant.value())){
        Utils::error(this->filename, name, "Only int types are supported for wrap binary instruction");
    }

    //After this stage, type variant can only be int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),type_variant.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown wrap binary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_wrap_add_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned","saturating"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for wrap instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWrapAddInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
    else{
        return std::make_shared<MIR::VecIntWrapAddInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_wrap_sub_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned","saturating"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for wrap instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWrapSubInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
    else{
        return std::make_shared<MIR::VecIntWrapSubInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_wrap_absdiff_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned","saturating"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for wrap instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWrapAbsDiffInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
    else{
        return std::make_shared<MIR::VecIntWrapAbsDiffInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_wrap_mul_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned","saturating"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for wrap instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWrapMulInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
    else{
        return std::make_shared<MIR::VecIntWrapMulInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_wrap_div_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned","saturating"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for wrap instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWrapDivInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
    else{
        return std::make_shared<MIR::VecIntWrapDivInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_wrap_rem_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned","saturating"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for wrap instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWrapRemInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
    else{
        return std::make_shared<MIR::VecIntWrapRemInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_wrap_copysign_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                        MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "saturating"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for wrap instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWrapCopysignInst>(inst_stmt,dest,lhs,rhs,flag_attrs["saturating"]);
    }
    else{
        return std::make_shared<MIR::VecIntWrapCopysignInst>(inst_stmt,dest,lhs,rhs,flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_wrap_shl_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                   MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "saturating"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for wrap instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWrapShlInst>(inst_stmt,dest,lhs,rhs,flag_attrs["saturating"]);
    }
    else{
        return std::make_shared<MIR::VecIntWrapShlInst>(inst_stmt,dest,lhs,rhs,flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_wrap_lshr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "saturating"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for wrap instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWrapLshrInst>(inst_stmt,dest,lhs,rhs,flag_attrs["saturating"]);
    }
    else{
        return std::make_shared<MIR::VecIntWrapLshrInst>(inst_stmt,dest,lhs,rhs,flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_wrap_ashr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                    MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "saturating"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for wrap instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWrapAshrInst>(inst_stmt,dest,lhs,rhs,flag_attrs["saturating"]);
    }
    else{
        return std::make_shared<MIR::VecIntWrapAshrInst>(inst_stmt,dest,lhs,rhs,flag_attrs["saturating"]);
    }
}
}
}