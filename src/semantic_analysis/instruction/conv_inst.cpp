#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
#include <memory>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                                    std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants, 
                                                    //For vector instructions ``base_types`` is the base type of vector. For scalar it is same as ``type_exprs``
                                                    std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                                    IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_trunc_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                                std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_ext_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                              std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                              std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                              IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_float_to_int_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                       std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                                       std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                       IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_int_to_float_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                       std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                                       std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                       IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_ptr_to_int_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                     std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                                     std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                     IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_int_to_ptr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                     std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                                     std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                     IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_conv_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".trunc", analyze_trunc_inst},
        {".ext", analyze_ext_inst},
        {".float_to_int", analyze_float_to_int_inst},
        {".int_to_float", analyze_int_to_float_inst},
        {".ptr_to_int", analyze_ptr_to_int_inst},
        {".int_to_ptr", analyze_int_to_ptr_inst},
    };
    auto args = inst_stmt->get_value()->get_operands();
    if(args.size() != 1){
        Utils::error(this->filename, name, "Conversion instruction must have 1 argument");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    if(dest == nullptr){
        Utils::error(this->filename, name, "Conversion instruction must have a destination i.e assign this instruction to a variable");
    }
    {
        args[0].second = Utils::get_reduced_type(this->type_symtable,args[0].second);
        if(!Utils::type_compatible(this->var_symtable, args[0].second,args[0].first)){
            Utils::error(this->filename, args[0].first->get_token(), "Argument type " + args[0].second->get_token().value + " is not compatible with assigned type " + args[0].second->to_string());
        }
    }
    auto dest_type_variant = MIR::get_type_variant_from_type(dest->get_type());
    auto arg_type_variant = MIR::get_type_variant_from_type(args[0].second);
    if(name.value == ".bitcast"){
        if(Utils::get_type_size(dest->get_type()) != Utils::get_type_size(args[0].second)){
            Utils::error(this->filename, name, "Bitcast instruction requires the source and destination types to have the same size. Destination type: " + dest->get_type()->to_string() + " has size " + std::to_string(Utils::get_type_size(dest->get_type())) + " bits. Source type: " + args[0].second->to_string() + " has size " + std::to_string(Utils::get_type_size(args[0].second)) + " bits.");
        }
        auto attributes = inst_stmt->get_value()->get_attributes();
        if(Utils::contains_float(dest->get_type()) || Utils::contains_float(args[0].second)){
            auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
            if(remaining_attrs.size() > 0){
                Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float bitcast instruction: " + remaining_attrs[0]->to_string());
            }
            return std::make_shared<MIR::BitcastInst>(inst_stmt,dest,args[0].first->get_literal(),args[0].second,fast_math_attr);
        }
        else{
            if(attributes.size() > 0){
                Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int bitcast instruction: " + attributes[0]->to_string());
            }
            return std::make_shared<MIR::BitcastInst>(inst_stmt,dest,args[0].first->get_literal(),args[0].second,std::nullopt);
        }
    }
    if((!dest_type_variant.has_value()) || (!arg_type_variant.has_value())){
        Utils::error(this->filename, name, "Conversion instruction requires both the source and destination types to be valid.");
    }
    else if(MIR::is_vector_typevariant(dest_type_variant.value()) ^ MIR::is_vector_typevariant(arg_type_variant.value())){
        Utils::error(this->filename, name, "Conversion instruction requires both the source and destination types to be either vector or scalar. Destination type: " + dest->get_type()->to_string() + " is " + (MIR::is_vector_typevariant(dest_type_variant.value()) ? "vector" : "scalar") + ". Source type: " + args[0].second->to_string() + " is " + (MIR::is_vector_typevariant(arg_type_variant.value()) ? "vector" : "scalar") + ".");
    }
    auto it = dispatch_map.find(name.value);
    if(it == dispatch_map.end()){
        std::cerr << "Unknown conversion instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
    if(MIR::is_vector_typevariant(dest_type_variant.value())){
        auto dest_vectype = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type());
        auto arg_vectype = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second);
        if(dest_vectype->get_size() != arg_vectype->get_size()){
            Utils::error(this->filename, name, "Conversion instruction requires both the source and destination vector types to have the same number of elements. Destination type: " + dest->get_type()->to_string() + " has " + std::to_string(dest_vectype->get_size()) + " elements. Source type: " + args[0].second->to_string() + " has " + std::to_string(arg_vectype->get_size()) + " elements.");
        }
        auto dest_basetype = dest_vectype->get_basetype();
        auto arg_basetype = arg_vectype->get_basetype();
        return it->second(this->filename,dest,args[0].first->get_literal(),
                          std::make_pair(dest->get_type(),args[0].second),
                          std::make_pair(dest_type_variant.value(),arg_type_variant.value()),
                          std::make_pair(dest_basetype,arg_basetype),inst_stmt);
    }
    else{
        return it->second(this->filename,dest,args[0].first->get_literal(),
                          std::make_pair(dest->get_type(),args[0].second),
                          std::make_pair(dest_type_variant.value(),arg_type_variant.value()),
                          std::make_pair(dest->get_type(),args[0].second),inst_stmt);
    }
}

MIR::InstPtr analyze_trunc_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                                std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                IR::InstructionStmtPtr inst_stmt){
    if(Utils::get_type_size(base_types.first) >= Utils::get_type_size(base_types.second)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "Trunc instruction requires the source type to be strictly larger than the destination type. Source type: " + base_types.second->to_string() + " has size " + std::to_string(Utils::get_type_size(base_types.second)) + " bits. Destination type: " + base_types.first->to_string() + " has size " + std::to_string(Utils::get_type_size(base_types.first)) + " bits.");
    }
    if(type_variants.first != type_variants.second){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "Trunc instruction requires the source and destination types to be of the same type variant.");
    }
    if(MIR::is_float_typevariant(type_variants.first)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,inst_stmt->get_value()->get_attributes());
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float trunc instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variants.first == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatTruncInst>(inst_stmt,dest,arg,type_exprs.second,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatTruncInst>(inst_stmt,dest,arg,type_exprs.second,fast_math_attr);
        }
    }
    else if(MIR::is_int_typevariant(type_variants.first)){
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,inst_stmt->get_value()->get_attributes(), {"nuw","nsw","unsigned","saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int trunc instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variants.first == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntTruncInst>(inst_stmt,dest,arg,type_exprs.second,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
        else{
            return std::make_shared<MIR::VecIntTruncInst>(inst_stmt,dest,arg,type_exprs.second,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
        }
    }
    else{
        Utils::error(filename, inst_stmt->get_value()->get_token(), "Unsupported type type for trunc instruction: " + type_exprs.first->to_string() + " and " + type_exprs.second->to_string());
    }
}

MIR::InstPtr analyze_ext_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                              std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                              std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                              IR::InstructionStmtPtr inst_stmt){
    if(Utils::get_type_size(base_types.first) <= Utils::get_type_size(base_types.second)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "Ext instruction requires the source type to be strictly smaller than the destination type. Source type: " + base_types.second->to_string() + " has size " + std::to_string(Utils::get_type_size(base_types.second)) + " bits. Destination type: " + base_types.first->to_string() + " has size " + std::to_string(Utils::get_type_size(base_types.first)) + " bits.");
    }
    if(type_variants.first != type_variants.second){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "Ext instruction requires the source and destination types to be of the same type variant.");
    }
    if(MIR::is_float_typevariant(type_variants.first)){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,inst_stmt->get_value()->get_attributes());
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float ext instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variants.first == MIR::TypeVariant::Float){
            return std::make_shared<MIR::FloatExtInst>(inst_stmt,dest,arg,type_exprs.second,fast_math_attr);
        }
        else{
            return std::make_shared<MIR::VecFloatExtInst>(inst_stmt,dest,arg,type_exprs.second,fast_math_attr);
        }   
    }
    else if(MIR::is_int_typevariant(type_variants.first)){
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,inst_stmt->get_value()->get_attributes(), {"unsigned","nsb"});
        if(flag_attrs["nsb"] && (!flag_attrs["unsigned"])){
            Utils::error(filename, inst_stmt->get_value()->get_token(), "Unsupported attribute combination for int ext instruction: nsb without unsigned");
        }
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int ext instruction: " + remaining_attrs[0]->to_string());
        }
        if(type_variants.first == MIR::TypeVariant::Int){
            return std::make_shared<MIR::IntExtInst>(inst_stmt,dest,arg,type_exprs.second,flag_attrs["nsb"],flag_attrs["unsigned"]);
        }
        else{
            return std::make_shared<MIR::VecIntExtInst>(inst_stmt,dest,arg,type_exprs.second,flag_attrs["nsb"],flag_attrs["unsigned"]);
        }
    }
    else{
        Utils::error(filename, inst_stmt->get_value()->get_token(), "Unsupported type type for ext instruction: " + type_exprs.first->to_string() + " and " + type_exprs.second->to_string());
    }
}

MIR::InstPtr analyze_float_to_int_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                       std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                                       std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                       IR::InstructionStmtPtr inst_stmt){
    if(!MIR::is_int_typevariant(type_variants.first)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "The type varient of the destination type must be int for float_to_int instruction. Destination type: " + type_exprs.first->to_string());
    }
    if(!MIR::is_float_typevariant(type_variants.second)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "The type varient of the source type must be float for float_to_int instruction. Source type: " + type_exprs.second->to_string());
    }
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,inst_stmt->get_value()->get_attributes());
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,_remaining_attrs, {"unsigned","nsb","saturating"});
    if(flag_attrs["nsb"] && (!flag_attrs["unsigned"])){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "Unsupported attribute combination for float_to_int instruction: nsb without unsigned");
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float_to_int instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variants.first == MIR::TypeVariant::Int){
        return std::make_shared<MIR::FloatToIntInst>(inst_stmt,dest,arg,type_exprs.second,flag_attrs["unsigned"],flag_attrs["saturating"],flag_attrs["nsb"],fast_math_attr);
    }
    else{
        return std::make_shared<MIR::VecFloatToIntInst>(inst_stmt,dest,arg,type_exprs.second,flag_attrs["unsigned"],flag_attrs["saturating"],flag_attrs["nsb"],fast_math_attr);
    }
}

MIR::InstPtr analyze_int_to_float_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                       std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                                       std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                       IR::InstructionStmtPtr inst_stmt){
    if(!MIR::is_float_typevariant(type_variants.first)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "The type varient of the destination type must be float for int_to_float instruction. Destination type: " + type_exprs.first->to_string());
    }
    if(!MIR::is_int_typevariant(type_variants.second)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "The type varient of the source type must be int for int_to_float instruction. Source type: " + type_exprs.second->to_string());
    }
    auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,inst_stmt->get_value()->get_attributes());
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,_remaining_attrs, {"unsigned","nsb"});
    if(flag_attrs["nsb"] && (!flag_attrs["unsigned"])){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "Unsupported attribute combination for int_to_float instruction: nsb without unsigned");
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int_to_float instruction: " + remaining_attrs[0]->to_string());
    }
    if(type_variants.first == MIR::TypeVariant::Float){
        return std::make_shared<MIR::IntToFloatInst>(inst_stmt,dest,arg,type_exprs.second,flag_attrs["unsigned"],flag_attrs["nsb"],fast_math_attr); 
    }
    else{
        return std::make_shared<MIR::VecIntToFloatInst>(inst_stmt,dest,arg,type_exprs.second,flag_attrs["unsigned"],flag_attrs["nsb"],fast_math_attr); 
    }
}

MIR::InstPtr analyze_ptr_to_int_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                     std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                                     std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                     IR::InstructionStmtPtr inst_stmt){
    if(!MIR::is_int_typevariant(type_variants.first)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "The type varient of the destination type must be int for ptr_to_int instruction. Destination type: " + type_exprs.first->to_string());
    }
    if(!MIR::is_ptr_typevariant(type_variants.second)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "The type varient of the source type must be pointer for ptr_to_int instruction. Source type: " + type_exprs.second->to_string());
    }
    if(!Utils::is_int(base_types.first,64)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "The type of the destination type must be i64 for ptr_to_int instruction. Destination type: " + type_exprs.first->to_string());
    }
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for ptr_to_int instruction: " + attributes[0]->to_string());
    }
    if(type_variants.first == MIR::TypeVariant::Int){
        return std::make_shared<MIR::PtrToIntInst>(inst_stmt,dest,arg);
    }
    else{
        return std::make_shared<MIR::VecPtrToIntInst>(inst_stmt,dest,arg,type_exprs.second);
    }
}

MIR::InstPtr analyze_int_to_ptr_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::LiteralExprPtr arg,
                                     std::pair<IR::TypeExprPtr, IR::TypeExprPtr> type_exprs, std::pair<MIR::TypeVariant, MIR::TypeVariant> type_variants,
                                     std::pair<IR::TypeExprPtr, IR::TypeExprPtr> base_types,
                                     IR::InstructionStmtPtr inst_stmt){
    if(!MIR::is_ptr_typevariant(type_variants.first)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "The type varient of the destination type must be pointer for int_to_ptr instruction. Destination type: " + type_exprs.first->to_string());
    }
    if(!MIR::is_int_typevariant(type_variants.second)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "The type varient of the source type must be int for int_to_ptr instruction. Source type: " + type_exprs.second->to_string());
    }
    if(!Utils::is_int(base_types.second,64)){
        Utils::error(filename, inst_stmt->get_value()->get_token(), "The type of the source type must be i64 for int_to_ptr instruction. Source type: " + type_exprs.second->to_string());
    }
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(attributes.size() > 0){
        Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int_to_ptr instruction: " + attributes[0]->to_string());
    }
    if(type_variants.first == MIR::TypeVariant::Ptr){
        return std::make_shared<MIR::IntToPtrInst>(inst_stmt,dest,arg,type_exprs.second);
    }
    else{
        return std::make_shared<MIR::VecIntToPtrInst>(inst_stmt,dest,arg,type_exprs.second);    
    }
}
}
}