#include "ast/ast.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    IR::LiteralExprPtr optional_arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt)>;
MIR::InstPtr analyze_divmod_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                 IR::LiteralExprPtr optional_arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_widening_divmod_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                         IR::LiteralExprPtr optional_arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_mulhi_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                IR::LiteralExprPtr optional_arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_mulfix_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                 IR::LiteralExprPtr optional_arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_other_arithmetic_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    std::map<std::string, DispatchFuncType> dispatch_map = {
            {".divmod", analyze_divmod_inst},
            {".widening_divmod", analyze_widening_divmod_inst},
            {".mulhi", analyze_mulhi_inst},
            {".mulfix", analyze_mulfix_inst}
    };
    auto args = inst_stmt->get_value()->get_operands();
    if(args.size() != 2){
        if(name.value == ".mulfix" || name.value == ".widening_divmod"){
            if(args.size() != 3){
                Utils::error(this->filename, name, "Divmod instruction must have 3 arguments");
            }
        }
        else{
            Utils::error(this->filename, name, "Arithmetic binary instruction must have 2 arguments");
        }
    }
    auto _dest = inst_stmt->get_name();
    if(!_dest.has_value()){
        Utils::error(this->filename, name, "Arithmetic binary instruction must have a destination i.e assign this instruction to a variable");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    if(name.value == ".divmod" || name.value == ".widening_divmod"){
        if(type->get_kind() != IR::TypeExprKind::StructTypeExpr){
            Utils::error(this->filename, name, "Destination type for this instruction must be a struct type");
        }
        auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(type);
        if(struct_type->get_fields().size() != 2){
            Utils::error(this->filename, name, "Destination type for this instruction must be a struct type with 2 fields");
        }
        else if(!Utils::type_eq(struct_type->get_fields()[0], struct_type->get_fields()[1])){
            Utils::error(this->filename, name, "Destination type for this instruction must be a struct type with 2 fields of the same type");
        }
        type = struct_type->get_fields()[0];//The type of the quotient and remainder is the type of the first field of the struct
    }
    for(size_t i=0;i<args.size();i++){
        args[i].second = Utils::get_reduced_type(this->type_symtable,args[i].second);
        if(!Utils::type_eq(type,args[i].second)){
            if(i==2 && name.value == ".mulfix"){
                if(args[i].second->get_kind() != IR::TypeExprKind::IntTypeExpr){
                    Utils::error(this->filename, args[i].first->get_token(), "Scale argument of mulfix instruction must be a 64 bit integer");
                }
                auto int_type = std::dynamic_pointer_cast<IR::IntTypeExpr>(args[i].second);
                if(int_type->get_bits() != 64){
                    Utils::error(this->filename, args[i].first->get_token(), "Scale argument of mulfix instruction must be a 64-bit integer");
                }
            }
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->to_string() + " is not the same as destination type " + type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, args[i].second,args[i].first)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].second->to_string() + " is not compatible with assigned type " + args[i].second->to_string());
        }
    }
    auto type_variant = MIR::get_type_variant_from_type(type);
    if(!type_variant.has_value()){
        Utils::error(this->filename, name, "Unsupported type for this instruction: " + type->to_string());
    }
    if(MIR::is_float_typevariant(type_variant.value())){
        if(name.value != ".divmod"){
            Utils::error(this->filename, name, "Only int types are supported for this instruction");
        }
    }
    else if(!MIR::is_int_typevariant(type_variant.value())){
        Utils::error(this->filename, name, "Unsupported type for this instruction: " + type->to_string());
    }
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        if(args.size() == 2){
            return it->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),nullptr,type_variant.value(),inst_stmt);
        }
        else{
            return it->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),args[2].first->get_literal(),type_variant.value(),inst_stmt);
        }
    }
    else{
        std::cerr << "Unknown instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_divmod_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                 IR::LiteralExprPtr optional_arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(MIR::is_float_typevariant(type_variant)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float divmod instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatDivmodInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatDivmodInst>(inst_stmt,dest,lhs,rhs,fast_math_attr);
        }
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int divmod instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variant == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntDivmodInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntDivmodInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
        }
    }
}
MIR::InstPtr analyze_widening_divmod_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                         IR::LiteralExprPtr optional_arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned", "exact"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int widening divmod instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntWideningDivmodInst>(inst_stmt,dest,lhs,rhs,optional_arg3,flag_attrs["unsigned"],flag_attrs["exact"]);
    }
    else{
        return std::make_shared<MIR::VecIntWideningDivmodInst>(inst_stmt,dest,lhs,rhs,optional_arg3,flag_attrs["unsigned"],flag_attrs["exact"]);
    }
}
MIR::InstPtr analyze_mulhi_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                IR::LiteralExprPtr optional_arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, { "unsigned"});
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int mulhi instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntMulHiInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
    }
    else{
        return std::make_shared<MIR::VecIntMulHiInst>(inst_stmt,dest,lhs,rhs,flag_attrs["unsigned"]);
    }
}
MIR::InstPtr analyze_mulfix_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                 IR::LiteralExprPtr optional_arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes,{ "nuw","nsw", "unsigned", "saturating", "round" });
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int mulfix instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntMulFixInst>(inst_stmt,dest,lhs,rhs,optional_arg3,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"],flag_attrs["round"]);
    }
    else{
        return std::make_shared<MIR::VecIntMulFixInst>(inst_stmt,dest,lhs,rhs,optional_arg3,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"],flag_attrs["round"]);
    }
}
}
}