#include "ast/ast.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                                    IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_fshl_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                   IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fshr_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                   IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_bitblend_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                       IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt);


MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_bitwise_tri_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".fshl", analyze_fshl_tri_inst},
        {".fshr", analyze_fshr_tri_inst},
        {".bitblend", analyze_bitblend_tri_inst}
    };
    auto args = inst_stmt->get_value()->get_operands();
    auto _dest = inst_stmt->get_name();
    if(!_dest.has_value()){
        Utils::error(this->filename, name, "Bitwise trinary instruction must have a destination i.e assign this instruction to a variable");
    }
    if(args.size() != 3){
        Utils::error(this->filename, name, "Bitwise trinary instruction must have 3 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    for(auto arg:args){
        arg.second = Utils::get_reduced_type(this->type_symtable,arg.second);
        if(!Utils::type_eq(type,arg.second)){
            Utils::error(this->filename, arg.first->get_token(), "Argument type " + arg.second->to_string() + " is not the same as destination type " + type->to_string());
        }
        else if(!Utils::type_compatible(this->var_symtable, type,arg.first)){
            Utils::error(this->filename, arg.first->get_token(), "Argument type " + arg.second->get_token().value + " is not compatible with destination type " + type->to_string());
        }
    }
    auto type_variant = MIR::get_type_variant_from_type(type);
    if(!type_variant.has_value()){
        Utils::error(this->filename, name, "Unsupported type for bitwise trinary instruction: " + type->to_string());
    }
    if(!MIR::is_int_typevariant(type_variant.value())){
        Utils::error(this->filename, name, "Only int types are supported for bitwise trinary instruction");
    }

    //After this stage, type variant can only be int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),args[2].first->get_literal(),type_variant.value(),inst_stmt);
    }
    else{
        std::cerr << "Unknown bitwise trinary instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}
MIR::InstPtr analyze_fshl_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                   IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise trinary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntFshlInst>(inst_stmt,dest,arg1,arg2,arg3);
    }
    else{
        return std::make_shared<MIR::VecIntFshlInst>(inst_stmt,dest,arg1,arg2,arg3);
    }
}
MIR::InstPtr analyze_fshr_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                   IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise trinary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntFshrInst>(inst_stmt,dest,arg1,arg2,arg3);
    }
    else{
        return std::make_shared<MIR::VecIntFshrInst>(inst_stmt,dest,arg1,arg2,arg3);
    }
}
MIR::InstPtr analyze_bitblend_tri_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                       IR::LiteralExprPtr arg3, MIR::TypeVariant type_variant, IR::InstructionStmtPtr inst_stmt){
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitwise trinary instruction: " + attributes[0]->to_string());
    }
    if(type_variant == MIR::TypeVariant::Int){
        return std::make_shared<MIR::IntBitblendInst>(inst_stmt,dest,arg1,arg2,arg3);
    }
    else{
        return std::make_shared<MIR::VecIntBitblendInst>(inst_stmt,dest,arg1,arg2,arg3);
    }
}
}
}