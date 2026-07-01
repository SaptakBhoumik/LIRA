#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include "semantic_analysis/ir_to_mir.hpp"
#include <iostream>
#include <functional>
namespace LIRA {
namespace SemanticAnalyzer {
using DispatchFuncType = std::function<MIR::InstPtr(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                                    MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt)>;
 
MIR::InstPtr analyze_fetch_xchg_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_add_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_sub_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_absdiff_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                            MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_mul_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_div_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_rem_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_copysign_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                             MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_min_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_max_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fetch_avg_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt);


MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_arithmetic_fetch_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    //NOTE:Dont use a common templated function for all. The attributes can change in future. It is more code but more maintainable imo+The error messages can be more specific
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".fetch_xchg", analyze_fetch_xchg_bin_inst},
        {".fetch_add", analyze_fetch_add_bin_inst},
        {".fetch_sub", analyze_fetch_sub_bin_inst},
        {".fetch_absdiff", analyze_fetch_absdiff_bin_inst},
        {".fetch_mul", analyze_fetch_mul_bin_inst},
        {".fetch_div", analyze_fetch_div_bin_inst},
        {".fetch_rem", analyze_fetch_rem_bin_inst},
        {".fetch_copysign", analyze_fetch_copysign_bin_inst},
        {".fetch_min", analyze_fetch_min_bin_inst},
        {".fetch_max", analyze_fetch_max_bin_inst},
        {".fetch_avg", analyze_fetch_avg_bin_inst}
    };
    auto args = inst_stmt->get_value()->get_operands();
    if(args.size() != 2){
        Utils::error(this->filename, name, "Arithmetic binary fetch instruction must have 2 arguments");
    }
    auto dest = process_local_dest_arg(inst_stmt);
    if(dest == nullptr){
        Utils::error(this->filename, name, "Arithmetic binary fetch instruction must have a destination i.e assign this instruction to a variable");
    }
    IR::TypeExprPtr type = dest->get_type();//Already reduced type by process_local_dest_arg
    std::vector<IR::AttributePtr> attributes = inst_stmt->get_value()->get_attributes();
    auto [common_fetch_attrs,remaining_attrs] = Utils::extract_common_fetch_attrs(this->filename,attributes);
    if(Utils::get_type_size(type) > 128 && common_fetch_attrs.atomic_ordering.has_value()){
        Utils::error(this->filename, name, "Atomic arithmetic binary fetch instruction destination type size must be less than or equal to 128 bits. Found: " + std::to_string(Utils::get_type_size(type)) + " bits");
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
        Utils::error(this->filename, name, "Unsupported type for arithmetic binary fetch instruction: " + type->to_string());
    }
    if(MIR::is_vector_typevariant(type_variant.value())){
        Utils::error(this->filename, name, "Vector type is not supported for arithmetic binary fetch instruction: " + type->to_string());
    }
    if((!MIR::is_int_typevariant(type_variant.value())) && (!MIR::is_float_typevariant(type_variant.value()))){
        Utils::error(this->filename, name, "Only int and float types are supported for arithmetic binary fetch instruction");
    }

    //After this stage, type variant can only be float or int or it's vector. So the args are literal expr. No need to check if they are literal expr or not cuz gurrentee
    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,args[0].first->get_literal(),args[1].first->get_literal(),type_variant.value(),common_fetch_attrs,remaining_attrs,inst_stmt);
    }
    else{
        std::cerr << "Unknown arithmetic binary fetch instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_fetch_xchg_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                         MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchXchgInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr);
    }
    else{
        if(attributes.size() > 0){
            Utils::error(filename, attributes[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + attributes[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchXchgInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs);
    }
}
MIR::InstPtr analyze_fetch_add_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchAddInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr);
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw", "nuw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchAddInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_fetch_sub_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchSubInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr);
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw", "nuw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchSubInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_fetch_absdiff_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                            MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchAbsDiffInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr);
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw", "nuw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchAbsDiffInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_fetch_mul_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchMulInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr);
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw", "nuw","unsigned", "saturating"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchMulInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["saturating"]);
    }
}
MIR::InstPtr analyze_fetch_div_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchDivInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr);
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"exact", "unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchDivInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["exact"],flag_attrs["unsigned"]);
    }
}
MIR::InstPtr analyze_fetch_rem_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchRemInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr);
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchRemInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["unsigned"]);
        
    }
}
MIR::InstPtr analyze_fetch_copysign_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                             MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchCopySignInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr);
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nsw"});

        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchCopySignInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["nsw"]);
    }
}
MIR::InstPtr analyze_fetch_min_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,_remaining_attrs, {"unordered", "ieee754_2019"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchMinInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr,flag_attrs["ieee754_2019"],flag_attrs["unordered"]);
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchMinInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["unsigned"]);
    }
}
MIR::InstPtr analyze_fetch_max_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,_remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,_remaining_attrs, {"unordered", "ieee754_2019"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchMaxInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr,flag_attrs["ieee754_2019"],flag_attrs["unordered"]);
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchMaxInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["unsigned"]);
    }
}
MIR::InstPtr analyze_fetch_avg_bin_inst(std::string filename, MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                        MIR::CommonFetchInstAttrs common_fetch_attrs, std::vector<IR::AttributePtr> attributes, IR::InstructionStmtPtr inst_stmt){
    if(type_variant == MIR::TypeVariant::Float){
        auto [fast_math_attr,remaining_attrs] = Utils::extract_fastmath_attrs(filename,attributes);
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for float arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::FloatFetchAvgInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,fast_math_attr);
    }
    else{
        auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"nuw", "nsw","unsigned", "floor"});
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for int arithmetic binary fetch instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntFetchAvgInst>(inst_stmt,dest,lhs,rhs,common_fetch_attrs,flag_attrs["nuw"],flag_attrs["nsw"],flag_attrs["unsigned"],flag_attrs["floor"]);
    }
}
}
}