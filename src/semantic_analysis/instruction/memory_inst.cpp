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
                                                    std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                                    IR::InstructionStmtPtr inst_stmt)>;

MIR::InstPtr analyze_local_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_alloca_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_load_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_store_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_broadcast_load_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_masked_load_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_masked_store_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_masked_gather_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_masked_scatter_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_prefetch_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_memcopy_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_memset_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_memcmp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_getaddress_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_ptroffset_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_stacksave_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_stackrestore_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_extractelement_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_insertelement_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_fence_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_atomic_cmpxchg_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_clflush_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_clwb_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_cldemote_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_lifetime_start_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_lifetime_end_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_invariant_start_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);
MIR::InstPtr analyze_invariant_end_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt);

MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_mem_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt){
    const std::unordered_map<std::string, DispatchFuncType> dispatch_map = {
        {".local", analyze_local_inst},
        {".alloca", analyze_alloca_inst},
        {".load", analyze_load_inst},
        {".store", analyze_store_inst},
        {".broadcast_load", analyze_broadcast_load_inst},
        {".masked_load", analyze_masked_load_inst},
        {".masked_store", analyze_masked_store_inst},
        {".masked_gather", analyze_masked_gather_inst},
        {".masked_scatter", analyze_masked_scatter_inst},
        {".prefetch", analyze_prefetch_inst},
        {".memcopy", analyze_memcopy_inst},
        {".memset", analyze_memset_inst},
        {".memcmp", analyze_memcmp_inst},
        {".getaddress", analyze_getaddress_inst},
        {".ptroffset", analyze_ptroffset_inst},
        {".stacksave", analyze_stacksave_inst},
        {".stackrestore", analyze_stackrestore_inst},
        {".extractelement", analyze_extractelement_inst},
        {".insertelement", analyze_insertelement_inst},
        {".fence", analyze_fence_inst},
        {".atomic_cmpxchg", analyze_atomic_cmpxchg_inst},
        {".clflush", analyze_clflush_inst},
        {".clwb", analyze_clwb_inst},
        {".cldemote", analyze_cldemote_inst},
        {".lifetime.start", analyze_lifetime_start_inst},
        {".lifetime.end", analyze_lifetime_end_inst},
        {".invariant.start", analyze_invariant_start_inst},
        {".invariant.end", analyze_invariant_end_inst},
    };
    auto args = inst_stmt->get_value()->get_operands();
    auto dest = process_local_dest_arg(inst_stmt);
    for(size_t i = 0; i < args.size(); i++){
        args[i].second = Utils::get_reduced_type(this->type_symtable,args[i].second);
        if(!Utils::type_compatible(this->var_symtable, args[i].second,args[i].first)){
            Utils::error(this->filename, args[i].first->get_token(), "Argument type " + args[i].first->to_string() + " is not compatible with assigned type " + args[i].second->to_string());
        }
    }

    auto it = dispatch_map.find(name.value);
    if(it != dispatch_map.end()){
        return it->second(this->filename,dest,name,args,inst_stmt);
    }
    else{
        std::cerr << "Unknown memory instruction: " << name.value << std::endl;
        std::cerr << "This should never happen cuz we already check the instruction name before calling this function. If it happens report this as a bug." << std::endl;
        exit(1);
    }
}

MIR::InstPtr analyze_local_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .local expects exactly 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .local expects a destination argument, but got none");
    }
    if(!Utils::type_eq(args[0].second, dest->get_type())){
        Utils::error(filename, name, "Instruction .local expects the argument to be of the same type as the destination");
    }
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(Utils::contains_float(dest->get_type())){
        auto val = Utils::extract_fastmath_attrs(filename,attributes);
        attributes = val.second;
        fast_math_attr = val.first;
    }
    auto [attrs_with_num_args, remaining_attrs] = Utils::extract_attrs_with_num_args<std::uint64_t>(filename, attributes, {"align"});
    if(attrs_with_num_args["align"].size() > 1){
        Utils::error(filename, name, "Attribute 'align' for .local instruction takes at most one argument");
    }
    if(attrs_with_num_args["align"].size() == 1){
        std::uint64_t align_value = attrs_with_num_args["align"][0];
        if(!Utils::is_pow_of_2(align_value)){
            Utils::error(filename, name, "Attribute 'align' for .local instruction must be a power of 2");
        }
    }
    else{
        attrs_with_num_args["align"].push_back(0);
    }
    if(dest->get_alignment() != attrs_with_num_args["align"][0]){
        if(dest->get_alignment() == 0){
            dest->set_alignment(attrs_with_num_args["align"][0]);
        }
        else if(attrs_with_num_args["align"][0] == 0){
            attrs_with_num_args["align"][0] = dest->get_alignment();
        }
        else{
            Utils::error(filename, name, "Attribute 'align' for .local instruction does not match the alignment of the destination register");
        }
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .local instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::LocalInst>(inst_stmt, dest, args[0].first->get_literal(), attrs_with_num_args["align"][0], fast_math_attr);
}
MIR::InstPtr analyze_alloca_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .alloca expects exactly 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .alloca expects a destination argument, but got none");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .alloca expects the destination to be a pointer type");
    }
    if(!Utils::is_int(args[0].second, 64)){
        Utils::error(filename, name, "Instruction .alloca expects the argument to be of type i64");
    }
    auto [attrs_with_num_args, remaining_attrs] = Utils::extract_attrs_with_num_args<std::uint64_t>(filename, attributes, {"align"});
    if(attrs_with_num_args["align"].size() > 1){
        Utils::error(filename, name, "Attribute 'align' for .alloca instruction takes at most one argument");
    }
    if(attrs_with_num_args["align"].size() == 1){
        std::uint64_t align_value = attrs_with_num_args["align"][0];
        if(!Utils::is_pow_of_2(align_value)){
            Utils::error(filename, name, "Attribute 'align' for .alloca instruction must be a power of 2");
        }
    }
    else{
        attrs_with_num_args["align"].push_back(0);
    }
    if(dest->get_alignment() != attrs_with_num_args["align"][0]){
        if(dest->get_alignment() == 0){
            dest->set_alignment(attrs_with_num_args["align"][0]);
        }
        else if(attrs_with_num_args["align"][0] == 0){
            attrs_with_num_args["align"][0] = dest->get_alignment();
        }
        else{
            Utils::error(filename, name, "Attribute 'align' for .alloca instruction does not match the alignment of the destination register");
        }
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .alloca instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::AllocaInst>(inst_stmt, dest, args[0].first->get_literal(), attrs_with_num_args["align"][0]);
}
MIR::InstPtr analyze_load_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .load expects exactly 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .load expects a destination argument, but got none");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .load expects the argument to be a pointer type");
    }
    auto [common_memory_attrs, remaining_attrs] = Utils::extract_common_memory_attrs(filename, attributes);
    auto [atomic_info, remaining_attrs2] = Utils::extract_atomic_info_attr(filename, remaining_attrs);
    auto [flag_attrs, remaining_attrs3] = Utils::extract_flag_attrs(filename, remaining_attrs2, 
                                                   {"invariant.load","nopoison"});
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(Utils::contains_float(dest->get_type())){
        auto val = Utils::extract_fastmath_attrs(filename,remaining_attrs3);
        remaining_attrs3 = val.second;
        fast_math_attr = val.first;
    }
    if(remaining_attrs3.size() > 0){
        Utils::error(filename, remaining_attrs3[0]->get_token(), "Unsupported attribute for .load instruction: " + remaining_attrs3[0]->to_string());
    }
    return std::make_shared<MIR::LoadInst>(inst_stmt, dest, args[0].first->get_literal(), common_memory_attrs.volatile_, flag_attrs["invariant.load"], 
                                           common_memory_attrs.nontemporal, common_memory_attrs.nonull, flag_attrs["nopoison"], 
                                           common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes, fast_math_attr, atomic_info);
                                            
                                            
}
MIR::InstPtr analyze_store_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction .store expects exactly 2 arguments, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .store does not expect a destination argument, but got one");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .store expects the first argument to be a pointer type");
    }
    auto [common_memory_attrs, remaining_attrs] = Utils::extract_common_memory_attrs(filename, attributes);
    auto [atomic_info, remaining_attrs2] = Utils::extract_atomic_info_attr(filename, remaining_attrs);
    auto [flag_attrs, remaining_attrs3] = Utils::extract_flag_attrs(filename, remaining_attrs2, {"nopoison"});
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(Utils::contains_float(args[1].second)){
        auto val = Utils::extract_fastmath_attrs(filename,remaining_attrs3);
        remaining_attrs3 = val.second;
        fast_math_attr = val.first;
    }
    if(remaining_attrs3.size() > 0){
        Utils::error(filename, remaining_attrs3[0]->get_token(), "Unsupported attribute for .store instruction: " + remaining_attrs3[0]->to_string());
    }
    return std::make_shared<MIR::StoreInst>(inst_stmt, args[0].first->get_literal(), args[1].first->get_literal(), args[1].second,
                                           common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull, flag_attrs["nopoison"], 
                                           common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes, fast_math_attr, atomic_info);
}
MIR::InstPtr analyze_broadcast_load_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .broadcast_load expects exactly 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .broadcast_load expects a destination argument, but got none");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .broadcast_load expects the argument to be a pointer type");
    }
    auto [common_memory_attrs, remaining_attrs] = Utils::extract_common_memory_attrs(filename, attributes);
    auto type_varient = MIR::get_type_variant_from_type(dest->get_type());
    if(!type_varient.has_value()){
        Utils::error(filename, name, "Instruction .broadcast_load expects the destination type to be a vector of integers/ptr/float");
    }
    if(type_varient.value() == MIR::TypeVariant::VecInt){
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .broadcast_load instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::IntBroadcastLoadInst>(inst_stmt, dest, args[0].first->get_literal(), common_memory_attrs.volatile_, common_memory_attrs.nontemporal, 
                                                           common_memory_attrs.nonull, common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);
    }
    else if(type_varient.value() == MIR::TypeVariant::VecPtr){
        if(remaining_attrs.size() > 0){
            Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .broadcast_load instruction: " + remaining_attrs[0]->to_string());
        }
        return std::make_shared<MIR::PtrBroadcastLoadInst>(inst_stmt, dest, args[0].first->get_literal(), common_memory_attrs.volatile_, common_memory_attrs.nontemporal, 
                                                           common_memory_attrs.nonull, common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);
    }
    else if(type_varient.value() == MIR::TypeVariant::VecFloat){
        auto [fast_math_attr, remaining_attrs2] = Utils::extract_fastmath_attrs(filename, remaining_attrs);
        if(remaining_attrs2.size() > 0){
            Utils::error(filename, remaining_attrs2[0]->get_token(), "Unsupported attribute for .broadcast_load instruction: " + remaining_attrs2[0]->to_string());
        }
        return std::make_shared<MIR::FloatBroadcastLoadInst>(inst_stmt, dest, args[0].first->get_literal(), common_memory_attrs.volatile_, common_memory_attrs.nontemporal, 
                                                             common_memory_attrs.nonull, common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes, fast_math_attr);
    }
    else{
        Utils::error(filename, name, "Instruction .broadcast_load expects the destination type to be a vector of integers/ptr/float");
    }
}
MIR::InstPtr analyze_masked_load_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() < 1 || args.size() > 3){
        Utils::error(filename, name, "Instruction .masked_load expects 1 to 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .masked_load expects a destination argument, but got none");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .masked_load expects the first argument to be a pointer type");
    }
    auto type_varient = MIR::get_type_variant_from_type(dest->get_type());
    if(!type_varient.has_value()){
        Utils::error(filename, name, "Instruction .masked_load expects the destination type to be a vector of integers/ptr/float");
    }
    if(!MIR::is_vector_typevariant(type_varient.value())){
        Utils::error(filename, name, "Instruction .masked_load expects the destination type to be a vector of integers/ptr/float");
    }
    auto dest_size = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type())->get_size();
    IR::ExprPtr mask_expr = nullptr;
    IR::ExprPtr passthru_expr = nullptr;
    if(args.size() >= 2){
        if(!Utils::is_vector_of_int(args[1].second, 1, dest_size)){
            Utils::error(filename, name, "Instruction .masked_load expects the second argument to be of type <i1,N>");
        }
        mask_expr = args[1].first;
    }
    if(args.size() == 3){
        if(!Utils::type_eq(args[2].second, dest->get_type())){
            Utils::error(filename, name, "Instruction .masked_load expects the third argument to be of the same type as the destination");
        }
        passthru_expr = args[2].first;
    }

    auto [common_memory_attrs, remaining_attrs] = Utils::extract_common_memory_attrs(filename, attributes);
    auto [flag_attrs, remaining_attrs2] = Utils::extract_flag_attrs(filename, remaining_attrs, {"zeropassthru"});
    if(flag_attrs["zeropassthru"]){
        if(args.size() == 3){
            Utils::error(filename, name, "Instruction .masked_load cannot have both 'zeropassthru' attribute and a passthru argument");
        }
        if(args.size() < 2){
            Utils::error(filename, name, "Instruction .masked_load 'zeropassthru' attribute requires a mask argument");
        }
    }
    else if(args.size() == 2){
        Utils::error(filename, name, "Instruction .masked_load requires a passthru argument when a mask is provided, unless the 'zeropassthru' attribute is used");
    }

    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(type_varient.value() == MIR::TypeVariant::VecFloat){
        auto val = Utils::extract_fastmath_attrs(filename, remaining_attrs2);
        remaining_attrs2 = val.second;
        fast_math_attr = val.first;
    }
    if(remaining_attrs2.size() > 0){
        Utils::error(filename, remaining_attrs2[0]->get_token(), "Unsupported attribute for .masked_load instruction: " + remaining_attrs2[0]->to_string());
    }

    IR::LiteralExprPtr mask_lit = mask_expr ? mask_expr->get_literal() : nullptr;
    IR::LiteralExprPtr passthru_lit = passthru_expr ? passthru_expr->get_literal() : nullptr;

    if(type_varient.value() == MIR::TypeVariant::VecInt){
        return std::make_shared<MIR::IntMaskedLoadInst>(inst_stmt, dest, args[0].first->get_literal(), mask_lit, passthru_lit,
                                                        common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull, flag_attrs["zeropassthru"],
                                                        common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);
    }
    else if(type_varient.value() == MIR::TypeVariant::VecPtr){
        return std::make_shared<MIR::PtrMaskedLoadInst>(inst_stmt, dest, args[0].first->get_literal(), mask_lit, passthru_lit,
                                                        common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull, flag_attrs["zeropassthru"],
                                                        common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);
    }
    else{
        return std::make_shared<MIR::FloatMaskedLoadInst>(inst_stmt, dest, args[0].first->get_literal(), mask_lit, passthru_lit,
                                                          common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull, flag_attrs["zeropassthru"],
                                                          common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes, fast_math_attr.value());
    }
}
MIR::InstPtr analyze_masked_store_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2 && args.size() != 3){
        Utils::error(filename, name, "Instruction .masked_store expects 2 or 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .masked_store does not expect a destination argument, but got one");
    }
    auto type_varient = MIR::get_type_variant_from_type(args[0].second);
    if(!type_varient.has_value()){
        Utils::error(filename, name, "Instruction .masked_store expects the first argument to be a vector of integers/ptr/float");
    }
    if(!MIR::is_vector_typevariant(type_varient.value())){
        Utils::error(filename, name, "Instruction .masked_store expects the first argument to be a vector of integers/ptr/float");
    }
    if(args[1].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .masked_store expects the second argument to be a pointer type");
    }
    IR::ExprPtr mask_expr = nullptr;
    if(args.size() == 3){
        auto val_size = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second)->get_size();
        if(!Utils::is_vector_of_int(args[2].second, 1, val_size)){
            Utils::error(filename, name, "Instruction .masked_store expects the third argument to be of type <i1,N>");
        }
        mask_expr = args[2].first;
    }
    auto [common_memory_attrs, remaining_attrs] = Utils::extract_common_memory_attrs(filename, attributes);
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(type_varient.value() == MIR::TypeVariant::VecFloat){
        auto val = Utils::extract_fastmath_attrs(filename, remaining_attrs);
        remaining_attrs = val.second;
        fast_math_attr = val.first;
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .masked_store instruction: " + remaining_attrs[0]->to_string());
    }
    IR::LiteralExprPtr mask_lit = mask_expr ? mask_expr->get_literal() : nullptr;

    if(type_varient.value() == MIR::TypeVariant::VecInt){
        return std::make_shared<MIR::IntMaskedStoreInst>(inst_stmt, args[1].first->get_literal(), args[0].first->get_literal(), args[0].second, mask_lit,
                                                         common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull,
                                                         common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);
    }
    else if(type_varient.value() == MIR::TypeVariant::VecPtr){
        return std::make_shared<MIR::PtrMaskedStoreInst>(inst_stmt, args[1].first->get_literal(), args[0].first->get_literal(), args[0].second, mask_lit,
                                                         common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull,
                                                         common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);
    }
    else{
        return std::make_shared<MIR::FloatMaskedStoreInst>(inst_stmt, args[1].first->get_literal(), args[0].first->get_literal(), args[0].second, mask_lit,
                                                           common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull,
                                                           common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes, fast_math_attr.value());
    }
}
MIR::InstPtr analyze_masked_gather_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() < 1 || args.size() > 3){
        Utils::error(filename, name, "Instruction .masked_gather expects 1 to 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .masked_gather expects a destination argument, but got none");
    }
    auto ptrs_type_varient = MIR::get_type_variant_from_type(args[0].second);
    if(!ptrs_type_varient.has_value() || ptrs_type_varient.value() != MIR::TypeVariant::VecPtr){
        Utils::error(filename, name, "Instruction .masked_gather expects the first argument to be a vector of pointers");
    }
    auto type_varient = MIR::get_type_variant_from_type(dest->get_type());
    if(!type_varient.has_value()){
        Utils::error(filename, name, "Instruction .masked_gather expects the destination type to be a vector of integers/ptr/float");
    }
    if(!MIR::is_vector_typevariant(type_varient.value())){
        Utils::error(filename, name, "Instruction .masked_gather expects the destination type to be a vector of integers/ptr/float");
    }
    auto ptrs_size = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second)->get_size();
    auto dest_size = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(dest->get_type())->get_size();
    if(ptrs_size != dest_size){
        Utils::error(filename, name, "Instruction .masked_gather expects the destination and pointer vector to have the same number of elements");
    }
    IR::ExprPtr mask_expr = nullptr;
    IR::ExprPtr passthru_expr = nullptr;
    if(args.size() >= 2){
        if(!Utils::is_vector_of_int(args[1].second, 1, dest_size)){
            Utils::error(filename, name, "Instruction .masked_gather expects the second argument to be of type <i1,N>");
        }
        mask_expr = args[1].first;
    }
    if(args.size() == 3){
        if(!Utils::type_eq(args[2].second, dest->get_type())){
            Utils::error(filename, name, "Instruction .masked_gather expects the third argument to be of the same type as the destination");
        }
        passthru_expr = args[2].first;
    }
    auto [common_memory_attrs, remaining_attrs] = Utils::extract_common_memory_attrs(filename, attributes);
    auto [flag_attrs, remaining_attrs2] = Utils::extract_flag_attrs(filename, remaining_attrs, {"zeropassthru"});
    if(flag_attrs["zeropassthru"]){
        if(args.size() == 3){
            Utils::error(filename, name, "Instruction .masked_gather cannot have both 'zeropassthru' attribute and a passthru argument");
        }
        if(args.size() < 2){
            Utils::error(filename, name, "Instruction .masked_gather 'zeropassthru' attribute requires a mask argument");
        }
    }
    else if(args.size() == 2){
        Utils::error(filename, name, "Instruction .masked_gather requires a passthru argument when a mask is provided, unless the 'zeropassthru' attribute is used");
    }
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(type_varient.value() == MIR::TypeVariant::VecFloat){
        auto val = Utils::extract_fastmath_attrs(filename, remaining_attrs2);
        remaining_attrs2 = val.second;
        fast_math_attr = val.first;
    }
    if(remaining_attrs2.size() > 0){
        Utils::error(filename, remaining_attrs2[0]->get_token(), "Unsupported attribute for .masked_gather instruction: " + remaining_attrs2[0]->to_string());
    }
    IR::LiteralExprPtr mask_lit = mask_expr ? mask_expr->get_literal() : nullptr;
    IR::LiteralExprPtr passthru_lit = passthru_expr ? passthru_expr->get_literal() : nullptr;

    if(type_varient.value() == MIR::TypeVariant::VecInt){
        return std::make_shared<MIR::IntMaskedGatherInst>(inst_stmt, dest, args[0].first->get_literal(), mask_lit, passthru_lit,
                                                          common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull, flag_attrs["zeropassthru"],
                                                          common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);
    }
    else if(type_varient.value() == MIR::TypeVariant::VecPtr){
        return std::make_shared<MIR::PtrMaskedGatherInst>(inst_stmt, dest, args[0].first->get_literal(), mask_lit, passthru_lit,
                                                          common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull, flag_attrs["zeropassthru"],
                                                          common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);
    }
    else{
        return std::make_shared<MIR::FloatMaskedGatherInst>(inst_stmt, dest, args[0].first->get_literal(), mask_lit, passthru_lit,
                                                            common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull, flag_attrs["zeropassthru"],
                                                            common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes, fast_math_attr.value());
    }
}
MIR::InstPtr analyze_masked_scatter_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2 && args.size() != 3){
        Utils::error(filename, name, "Instruction .masked_scatter expects 2 or 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .masked_scatter does not expect a destination argument, but got one");
    }
    auto ptrs_type_varient = MIR::get_type_variant_from_type(args[0].second);
    if(!ptrs_type_varient.has_value() || ptrs_type_varient.value() != MIR::TypeVariant::VecPtr){
        Utils::error(filename, name, "Instruction .masked_scatter expects the first argument to be a vector of pointers");
    }
    auto type_varient = MIR::get_type_variant_from_type(args[1].second);
    if(!type_varient.has_value()){
        Utils::error(filename, name, "Instruction .masked_scatter expects the second argument to be a vector of integers/ptr/float");
    }
    if(!MIR::is_vector_typevariant(type_varient.value())){
        Utils::error(filename, name, "Instruction .masked_scatter expects the second argument to be a vector of integers/ptr/float");
    }
    auto ptrs_size = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second)->get_size();
    auto val_size = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[1].second)->get_size();
    if(ptrs_size != val_size){
        Utils::error(filename, name, "Instruction .masked_scatter expects the pointer and value vectors to have the same number of elements");
    }
    IR::ExprPtr mask_expr = nullptr;
    if(args.size() == 3){
        if(!Utils::is_vector_of_int(args[2].second, 1, val_size)){
            Utils::error(filename, name, "Instruction .masked_scatter expects the third argument to be of type <i1,N>");
        }
        mask_expr = args[2].first;
    }
    auto [common_memory_attrs, remaining_attrs] = Utils::extract_common_memory_attrs(filename, attributes);
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(type_varient.value() == MIR::TypeVariant::VecFloat){
        auto val = Utils::extract_fastmath_attrs(filename, remaining_attrs);
        remaining_attrs = val.second;
        fast_math_attr = val.first;
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .masked_scatter instruction: " + remaining_attrs[0]->to_string());
    }
    IR::LiteralExprPtr mask_lit = mask_expr ? mask_expr->get_literal() : nullptr;

    if(type_varient.value() == MIR::TypeVariant::VecInt){
        return std::make_shared<MIR::IntMaskedScatterInst>(inst_stmt, args[0].first->get_literal(), args[1].first->get_literal(), args[1].second, mask_lit,
                                                           common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull,
                                                           common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);
    }
    else if(type_varient.value() == MIR::TypeVariant::VecPtr){
        return std::make_shared<MIR::PtrMaskedScatterInst>(inst_stmt, args[0].first->get_literal(), args[1].first->get_literal(), args[1].second, mask_lit,
                                                           common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull,
                                                           common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);
    }
    else{
        return std::make_shared<MIR::FloatMaskedScatterInst>(inst_stmt, args[0].first->get_literal(), args[1].first->get_literal(), args[1].second, mask_lit,
                                                             common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull,
                                                             common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes, fast_math_attr.value());
    }
}
MIR::InstPtr analyze_prefetch_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .prefetch expects exactly 1 argument, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .prefetch does not expect a destination argument, but got one");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .prefetch expects the argument to be a pointer type");
    }
    auto [attrs_with_num_args, _remaining_attrs] = Utils::extract_attrs_with_num_args<std::uint8_t>(filename, attributes, {"locality"});
    if(attrs_with_num_args["locality"].size() > 1){
        Utils::error(filename, name, "Attribute 'locality' for .prefetch instruction takes at most one argument");
    }
    if(attrs_with_num_args["locality"].size() == 1){
        std::uint8_t locality_value = attrs_with_num_args["locality"][0];
        if(locality_value > 3){
            Utils::error(filename, name, "Attribute 'locality' for .prefetch instruction must be in the range [0, 3]");
        }
    }
    else{
        attrs_with_num_args["locality"].push_back(3);
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, _remaining_attrs, {"instruction","write"});
    if(flag_attrs["instruction"] && flag_attrs["write"]){
        Utils::error(filename, name, "Instruction .prefetch cannot have both 'instruction' and 'write' attributes");
    }
    if(remaining_attrs.size() > 0){
        Utils::error(filename, remaining_attrs[0]->get_token(), "Unsupported attribute for .prefetch instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::PrefetchInst>(inst_stmt, args[0].first->get_literal(), flag_attrs["write"], flag_attrs["instruction"], attrs_with_num_args["locality"][0]);
}
MIR::InstPtr analyze_memcopy_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction .memcopy expects exactly 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .memcopy does not expect a destination argument, but got one");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .memcopy expects the first argument to be a pointer type");
    }
    if(args[1].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .memcopy expects the second argument to be a pointer type");
    }
    if(!Utils::is_int(args[2].second, 64)){
        Utils::error(filename, name, "Instruction .memcopy expects the third argument to be of type i64");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"nooverlap","volatile"});
    auto [idx_attrs, remaining_attrs2] = Utils::extract_attrs_with_num_args<std::uint64_t>(filename, remaining_attrs, {"nontemporal","nonnull","nopoison"});
    std::pair<bool,bool> nontemporal = {false,false};
    std::pair<bool,bool> nonnull = {false,false};
    std::pair<bool,bool> nopoison = {false,false};
    for(auto idx : idx_attrs["nontemporal"]){
        if(idx == 0){
            nontemporal.first = true;//dest
        } 
        else if(idx == 1){
            nontemporal.second = true;//src
        } 
        else{
            Utils::error(filename, name, "Instruction .memcopy attribute 'nontemporal' index must be 0 or 1");
        }
    }
    for(auto idx : idx_attrs["nonnull"]){
        if(idx == 0){
            nonnull.first = true;
        } 
        else if(idx == 1){
            nonnull.second = true;
        } 
        else{
            Utils::error(filename, name, "Instruction .memcopy attribute 'nonnull' index must be 0 or 1");
        }
    }
    for(auto idx : idx_attrs["nopoison"]){
        if(idx == 0){
            nopoison.first = true;
        } 
        else if(idx == 1){
            nopoison.second = true;
        } 
        else{
            Utils::error(filename, name, "Instruction .memcopy attribute 'nopoison' index must be 0 or 1");
        }
    }

    auto [pair_attrs, remaining_attrs3] = Utils::extract_attrs_with_num_args<std::uint64_t>(filename, remaining_attrs2, {"align","dereferenceable"});
    std::pair<std::size_t,std::size_t> alignment = {0,0};
    std::pair<std::size_t,std::size_t> dereferenceable_bytes = {0,0};
    if(pair_attrs["align"].size() % 2 != 0){
        Utils::error(filename, name, "Attribute 'align' for .memcopy instruction expects pairs of index and alignment value");
    }
    for(size_t i = 0; i < pair_attrs["align"].size(); i += 2){
        std::uint64_t idx = pair_attrs["align"][i];
        std::uint64_t align_value = pair_attrs["align"][i+1];
        if(!Utils::is_pow_of_2(align_value)){
            Utils::error(filename, name, "Attribute 'align' for .memcopy instruction must be a power of 2");
        }
        if(idx == 0){
            alignment.first = align_value;
        } 
        else if(idx == 1){
            alignment.second = align_value;
        } 
        else{
            Utils::error(filename, name, "Instruction .memcopy attribute 'align' index must be 0 or 1");
        }
    }
    if(pair_attrs["dereferenceable"].size() % 2 != 0){
        Utils::error(filename, name, "Attribute 'dereferenceable' for .memcopy instruction expects pairs of index and byte count");
    }
    for(size_t i = 0; i < pair_attrs["dereferenceable"].size(); i += 2){
        std::uint64_t idx = pair_attrs["dereferenceable"][i];
        std::uint64_t deref_value = pair_attrs["dereferenceable"][i+1];
        if(idx == 0){
            dereferenceable_bytes.first = deref_value;
        } 
        else if(idx == 1){
            dereferenceable_bytes.second = deref_value;
        } 
        else{
            Utils::error(filename, name, "Instruction .memcopy attribute 'dereferenceable' index must be 0 or 1");
        }
    }
    if(remaining_attrs3.size() > 0){
        Utils::error(filename, remaining_attrs3[0]->get_token(), "Unsupported attribute for .memcopy instruction: " + remaining_attrs3[0]->to_string());
    }
    return std::make_shared<MIR::MemcopyInst>(inst_stmt, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(),
                                              flag_attrs["nooverlap"], flag_attrs["volatile"], nontemporal, nonnull, nopoison, alignment, dereferenceable_bytes);
}
MIR::InstPtr analyze_memset_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction .memset expects exactly 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .memset does not expect a destination argument, but got one");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .memset expects the first argument to be a pointer type");
    }
    if(!Utils::is_int(args[1].second, 8)){
        Utils::error(filename, name, "Instruction .memset expects the second argument to be of type i8");
    }
    if(!Utils::is_int(args[2].second, 64)){
        Utils::error(filename, name, "Instruction .memset expects the third argument to be of type i64");
    }
    auto [common_memory_attrs, remaining_attrs] = Utils::extract_common_memory_attrs(filename, attributes);
    auto [flag_attrs, remaining_attrs2] = Utils::extract_flag_attrs(filename, remaining_attrs, {"nopoison"});
    if(remaining_attrs2.size() > 0){
        Utils::error(filename, remaining_attrs2[0]->get_token(), "Unsupported attribute for .memset instruction: " + remaining_attrs2[0]->to_string());
    }
    return std::make_shared<MIR::MemsetInst>(inst_stmt, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), 
                                             common_memory_attrs.volatile_, common_memory_attrs.nontemporal, common_memory_attrs.nonull, flag_attrs["nopoison"], 
                                             common_memory_attrs.alignment, common_memory_attrs.dereferenceable_bytes);    
}
MIR::InstPtr analyze_memcmp_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction .memcmp expects exactly 3 arguments, but got " + std::to_string(args.size()));
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .memcmp expects a destination argument, but got none");
    }
    if(!Utils::is_int(dest->get_type(), 32)){
        Utils::error(filename, name, "Instruction .memcmp expects the destination to be of type i32");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .memcmp expects the first argument to be a pointer type");
    }
    if(args[1].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .memcmp expects the second argument to be a pointer type");
    }
    if(!Utils::is_int(args[2].second, 64)){
        Utils::error(filename, name, "Instruction .memcmp expects the third argument to be of type i64");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename, attributes, {"volatile"});
    auto [idx_attrs, remaining_attrs2] = Utils::extract_attrs_with_num_args<std::uint64_t>(filename, remaining_attrs, {"nontemporal","nonnull","nopoison"});
    std::pair<bool,bool> nontemporal = {false,false};
    std::pair<bool,bool> nonnull = {false,false};
    std::pair<bool,bool> nopoison = {false,false};
    for(auto idx : idx_attrs["nontemporal"]){
        if(idx == 0){
            nontemporal.first = true;
        }
        else if(idx == 1){
            nontemporal.second = true;
        }
        else{
            Utils::error(filename, name, "Instruction .memcmp attribute 'nontemporal' index must be 0 or 1");
        }
    }
    for(auto idx : idx_attrs["nonnull"]){
        if(idx == 0){
            nonnull.first = true;
        }
        else if(idx == 1){
            nonnull.second = true;
        }
        else{
            Utils::error(filename, name, "Instruction .memcmp attribute 'nonnull' index must be 0 or 1");
        }
    }
    for(auto idx : idx_attrs["nopoison"]){
        if(idx == 0){
            nopoison.first = true;
        }
        else if(idx == 1){
            nopoison.second = true;
        }
        else{
            Utils::error(filename, name, "Instruction .memcmp attribute 'nopoison' index must be 0 or 1");
        }
    }

    auto [pair_attrs, remaining_attrs3] = Utils::extract_attrs_with_num_args<std::uint64_t>(filename, remaining_attrs2, {"align","dereferenceable"});
    std::pair<std::size_t,std::size_t> alignment = {0,0};
    std::pair<std::size_t,std::size_t> dereferenceable_bytes = {0,0};
    if(pair_attrs["align"].size() % 2 != 0){
        Utils::error(filename, name, "Attribute 'align' for .memcmp instruction expects pairs of index and alignment value");
    }
    for(size_t i = 0; i < pair_attrs["align"].size(); i += 2){
        std::uint64_t idx = pair_attrs["align"][i];
        std::uint64_t align_value = pair_attrs["align"][i+1];
        if(!Utils::is_pow_of_2(align_value)){
            Utils::error(filename, name, "Attribute 'align' for .memcmp instruction must be a power of 2");
        }
        if(idx == 0){
            alignment.first = align_value;
        }
        else if(idx == 1){
            alignment.second = align_value;
        }
        else{
            Utils::error(filename, name, "Instruction .memcmp attribute 'align' index must be 0 or 1");
        }
    }
    if(pair_attrs["dereferenceable"].size() % 2 != 0){
        Utils::error(filename, name, "Attribute 'dereferenceable' for .memcmp instruction expects pairs of index and byte count");
    }
    for(size_t i = 0; i < pair_attrs["dereferenceable"].size(); i += 2){
        std::uint64_t idx = pair_attrs["dereferenceable"][i];
        std::uint64_t deref_value = pair_attrs["dereferenceable"][i+1];
        if(idx == 0){
            dereferenceable_bytes.first = deref_value;
        }
        else if(idx == 1){
            dereferenceable_bytes.second = deref_value;
        }
        else{
            Utils::error(filename, name, "Instruction .memcmp attribute 'dereferenceable' index must be 0 or 1");
        }
    }
    if(remaining_attrs3.size() > 0){
        Utils::error(filename, remaining_attrs3[0]->get_token(), "Unsupported attribute for .memcmp instruction: " + remaining_attrs3[0]->to_string());
    }
    return std::make_shared<MIR::MemcmpInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(),
                                             flag_attrs["volatile"], nontemporal, nonnull, nopoison, alignment, dereferenceable_bytes);
}
MIR::InstPtr analyze_getaddress_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction .getaddress takes exactly two arguments");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .getaddress requires a destination argument");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .getaddress requires a pointer type destination argument");
    }
    if(!Utils::get_var_name(args[0].first).has_value()){
        Utils::error(filename, name, "Instruction .getaddress requires a non-constexpr value for the first argument");
    }
    if(!Utils::is_int(args[1].second, 64)){
        Utils::error(filename, name, "Instruction .getaddress requires an i64 type for the second argument");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename,attributes,{"unsigned","nsw","nuw","inbounds"});
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(Utils::contains_float(args[0].second)){
        auto val = Utils::extract_fastmath_attrs(filename,remaining_attrs);
        remaining_attrs = val.second;
        fast_math_attr = val.first;
    }
    if(remaining_attrs.size() != 0){
        Utils::error(filename, name, "Unsupported attribute for .getaddress instruction: " +remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::GetAddressInst>(inst_stmt, dest, args[0].first->get_literal(), args[0].second, args[1].first->get_literal(), 
                                                 flag_attrs["unsigned"], flag_attrs["nsw"], flag_attrs["nuw"], flag_attrs["inbounds"], fast_math_attr);
}
MIR::InstPtr analyze_ptroffset_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction .ptroffset takes exactly two arguments");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .ptroffset requires a destination argument");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .ptroffset requires a pointer type destination argument");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .ptroffset requires a pointer type for the first argument");
    }
    if(!Utils::is_int(args[1].second, 64)){
        Utils::error(filename, name, "Instruction .ptroffset requires an i64 type for the second argument");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"unsigned","nsw","nuw","inbounds"});
    if(remaining_attrs.size() != 0){
        Utils::error(filename, name, "Unsupported attribute for .ptroffset instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::PtrOffsetInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), flag_attrs["unsigned"], flag_attrs["nsw"], flag_attrs["nuw"], flag_attrs["inbounds"]);
}
MIR::InstPtr analyze_stacksave_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 0){
        Utils::error(filename, name, "Instruction .stacksave takes exactly zero arguments");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .stacksave requires a destination argument");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .stacksave requires a pointer type destination argument");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .stacksave takes no attributes");
    }
    return std::make_shared<MIR::StackSaveInst>(inst_stmt, dest);
}
MIR::InstPtr analyze_stackrestore_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .stackrestore takes exactly one argument");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .stackrestore has no destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .stackrestore takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .stackrestore takes a pointer type argument for the first argument");
    }
    return std::make_shared<MIR::StackRestoreInst>(inst_stmt, args[0].first->get_literal());
}
MIR::InstPtr analyze_extractelement_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction .extractelement takes exactly two arguments");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .extractelement requires a destination argument");
    }
    if(!Utils::is_int(args[1].second, 64)){
        Utils::error(filename, name, "Instruction .extractelement requires the second argument to be an i64 type");
    }
    IR::TypeExprPtr element_type;
    if(args[0].second->get_kind() == IR::TypeExprKind::SIMDTypeExpr){
        element_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second)->get_basetype();
    }
    else if(args[0].second->get_kind() == IR::TypeExprKind::ArrayTypeExpr){
        element_type = std::dynamic_pointer_cast<IR::ArrayTypeExpr>(args[0].second)->get_basetype();
    }
    else if(args[0].second->get_kind() == IR::TypeExprKind::StructTypeExpr){
        auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(args[0].second);
        auto fields = struct_type->get_fields();
        auto index = Utils::to_numeric<std::uint64_t>(filename, args[1].first, args[1].second, true, true);
        if(fields.size() <= index){
            Utils::error(filename, name, "Instruction .extractelement index out of bounds for struct type");
        }
        element_type = fields[index];
    }
    else{
        Utils::error(filename, name, "Instruction .extractelement requires the first argument to be a SIMD, Array, or Struct type");
    }
    if(!Utils::type_eq(element_type, dest->get_type())){
        Utils::error(filename, name, "Instruction .extractelement requires the destination type to match the element type of the first argument");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"inbounds"});
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(Utils::contains_float(args[0].second)){
        auto val = Utils::extract_fastmath_attrs(filename,remaining_attrs);
        remaining_attrs = val.second;
        fast_math_attr = val.first;
    }
    if(remaining_attrs.size() != 0){
        Utils::error(filename, name, "Unsupported attribute for .extractelement instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::ExtractElementInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[0].second, flag_attrs["inbounds"], fast_math_attr);
}
MIR::InstPtr analyze_insertelement_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction .insertelement takes exactly three arguments");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .insertelement requires a destination argument");
    }
    if(!Utils::is_int(args[2].second, 64)){
        Utils::error(filename, name, "Instruction .insertelement requires the third argument to be an i64 type");
    }
    if(!Utils::type_eq(args[0].second, dest->get_type())){
        Utils::error(filename, name, "Instruction .insertelement requires the destination type to match the first argument type");
    }
    IR::TypeExprPtr element_type;
    if(args[0].second->get_kind() == IR::TypeExprKind::SIMDTypeExpr){
        element_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(args[0].second)->get_basetype();
    }
    else if(args[0].second->get_kind() == IR::TypeExprKind::ArrayTypeExpr){
        element_type = std::dynamic_pointer_cast<IR::ArrayTypeExpr>(args[0].second)->get_basetype();
    }
    else if(args[0].second->get_kind() == IR::TypeExprKind::StructTypeExpr){
        auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(args[0].second);
        auto fields = struct_type->get_fields();
        auto index = Utils::to_numeric<std::uint64_t>(filename, args[2].first, args[2].second, true, true);
        if(fields.size() <= index){
            Utils::error(filename, name, "Instruction .insertelement index out of bounds for struct type");
        }
        element_type = fields[index];
    }
    else{
        Utils::error(filename, name, "Instruction .insertelement requires the first argument to be a SIMD, Array, or Struct type");
    }
    if(!Utils::type_eq(element_type, args[1].second)){
        Utils::error(filename, name, "Instruction .insertelement requires the second argument type to match the element type of the first argument");
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"inbounds"});
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(Utils::contains_float(args[0].second)){
        auto val = Utils::extract_fastmath_attrs(filename,remaining_attrs);
        remaining_attrs = val.second;
        fast_math_attr = val.first;
    }
    if(remaining_attrs.size() != 0){
        Utils::error(filename, name, "Unsupported attribute for .insertelement instruction: " + remaining_attrs[0]->to_string());
    }
    return std::make_shared<MIR::InsertElementInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), args[0].second, element_type, flag_attrs["inbounds"], fast_math_attr);
}
MIR::InstPtr analyze_fence_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .fence takes exactly one argument");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .fence has no destination");
    }
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"store_only","load_only"});
    if(flag_attrs["store_only"] && flag_attrs["load_only"]){
        Utils::error(filename, name, "Instruction .fence cannot have both 'store_only' and 'load_only' attributes");
    }
    auto [syncscope,remaining_attrs2] = Utils::extract_syncscope_attr(filename,remaining_attrs);
    if(remaining_attrs2.size() != 0){
        Utils::error(filename, name, "Instruction .fence takes no other attributes");
    }
    auto _ordering = Utils::get_atomic_ordering(args[0].first);
    if(!_ordering.has_value()){
        Utils::error(filename, name, "Instruction .fence requires a valid atomic ordering argument");
    }
    auto ordering = _ordering.value();
    if(ordering == MIR::AtomicOrdering::ACQUIRE){
        if(flag_attrs["store_only"]){
            Utils::error(filename, name, "Instruction .fence with ordering 'acquire' cannot have 'store_only' attribute");
        }
    }
    else if(ordering == MIR::AtomicOrdering::RELEASE){
        if(flag_attrs["load_only"]){
            Utils::error(filename, name, "Instruction .fence with ordering 'release' cannot have 'load_only' attribute");
        }
    }
    else if(ordering == MIR::AtomicOrdering::ACQUIRE_RELEASE){
        if(flag_attrs["store_only"] || flag_attrs["load_only"]){
            Utils::error(filename, name, "Instruction .fence with ordering 'acquire_release' cannot have 'store_only' or 'load_only' attributes");
        }
    }
    else if(ordering != MIR::AtomicOrdering::SEQUENTIALLY_CONSISTENT){
        Utils::error(filename, name, "Invalid ordering for .fence");
    }
    return std::make_shared<MIR::FenceInst>(inst_stmt, syncscope, ordering, flag_attrs["store_only"], flag_attrs["load_only"]);
}
MIR::InstPtr analyze_atomic_cmpxchg_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 5){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg takes exactly five arguments");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg requires a destination argument");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg requires the first argument to be a pointer type");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::StructTypeExpr){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg requires the destination to be a struct type");
    }
    auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(dest->get_type());
    auto fields = struct_type->get_fields();
    if(fields.size() != 2){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg requires the destination struct type to have exactly two fields");
    }
    IR::TypeExprPtr type = fields[0];
    if(!Utils::type_eq(type, args[1].second) || !Utils::type_eq(type, args[2].second)){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg requires the second and third arguments to be of the same type as the first field of the destination struct type");
    }
    if(!Utils::is_int(fields[1], 1)){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg requires the second field of the destination struct type to be of type i1");
    }
    auto _success_ordering = Utils::get_atomic_ordering(args[3].first);
    auto _failure_ordering = Utils::get_atomic_ordering(args[4].first);
    if(!_success_ordering.has_value()){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg requires a valid atomic ordering argument for the fourth argument");
    }
    if(!_failure_ordering.has_value()){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg requires a valid atomic ordering argument for the fifth argument");
    }
    auto success_ordering = _success_ordering.value();
    auto failure_ordering = _failure_ordering.value();
    if(success_ordering == MIR::AtomicOrdering::UNORDERED){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg cannot have 'unordered' ordering for the fourth argument");
    }
    if(failure_ordering == MIR::AtomicOrdering::UNORDERED || failure_ordering == MIR::AtomicOrdering::RELEASE || failure_ordering == MIR::AtomicOrdering::ACQUIRE_RELEASE){
        Utils::error(filename, name, "Instruction .atomic_cmpxchg cannot have 'unordered' or 'release' or 'acq_rel' ordering for the fifth argument");
    }
    if((uint64_t)success_ordering < (uint64_t)failure_ordering){
        if(success_ordering == MIR::AtomicOrdering::RELEASE && failure_ordering == MIR::AtomicOrdering::ACQUIRE){
            // This is allowed, because acq_rel is stronger than acq but we cant represent that in enum(We need same value in C++ enum which is not allowed in C++ so this hack)
        }
        else{
            Utils::error(filename, name, "Failure ordering cannot be stronger than success ordering in .atomic_cmpxchg instruction");
        }
    }
    auto [flag_attrs, remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"weak","volatile"});
    auto [syncscope, remaining_attrs2] = Utils::extract_syncscope_attr(filename,remaining_attrs);
    auto [attrs_with_num_args, remaining_attrs3] = Utils::extract_attrs_with_num_args<uint64_t>(filename, remaining_attrs2, {"align"});
    if(attrs_with_num_args["align"].size() > 1){
        Utils::error(filename, name, "Attribute 'align' for .atomic_cmpxchg instruction takes at most one argument");
    }
    if(attrs_with_num_args["align"].size() == 0){
        attrs_with_num_args["align"].push_back(0);
    }
    std::optional<MIR::FastMathAttr> fast_math_attr = std::nullopt;
    if(Utils::contains_float(type)){
        auto val = Utils::extract_fastmath_attrs(filename,remaining_attrs3);
        remaining_attrs3 = val.second;
        fast_math_attr = val.first;
    }
    if(remaining_attrs3.size() != 0){
        Utils::error(filename, name, "Unsupported attribute for .atomic_cmpxchg instruction: " + remaining_attrs3[0]->to_string());
    }
    return std::make_shared<MIR::CmpXchgInst>(inst_stmt, dest, args[0].first->get_literal(), args[1].first->get_literal(), args[2].first->get_literal(), success_ordering, failure_ordering, flag_attrs["volatile"], flag_attrs["weak"], attrs_with_num_args["align"][0], syncscope, fast_math_attr);
}
MIR::InstPtr analyze_clflush_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .clflush takes exactly one argument");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .clflush has no destination");
    }
    auto [flag_attrs,remaining_attrs] = Utils::extract_flag_attrs(filename,attributes, {"opt"});
    if(remaining_attrs.size() != 0){
        Utils::error(filename, name, "Instruction .clflush takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .clflush takes a pointer type argument for the first argument");
    }
    return std::make_shared<MIR::ClflushInst>(inst_stmt, args[0].first->get_literal(), flag_attrs["opt"]);
}
MIR::InstPtr analyze_clwb_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .clwb takes exactly one argument");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .clwb has no destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .clwb takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .clwb takes a pointer type argument for the first argument");
    }
    return std::make_shared<MIR::ClwbInst>(inst_stmt, args[0].first->get_literal());
}
MIR::InstPtr analyze_cldemote_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 1){
        Utils::error(filename, name, "Instruction .cldemote takes exactly one argument");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .cldemote has no destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .cldemote takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .cldemote takes a pointer type argument for the first argument");
    }
    return std::make_shared<MIR::CldemoteInst>(inst_stmt, args[0].first->get_literal());
}
MIR::InstPtr analyze_lifetime_start_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction .lifetime.start takes exactly two arguments");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .lifetime.start has no destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .lifetime.start takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .lifetime.start takes a pointer type argument for the first argument");
    }
    if(!Utils::is_int(args[1].second, 64)){
        Utils::error(filename, name, "Instruction .lifetime.start takes a second argument of type i64");
    }
    std::uint64_t size = Utils::to_numeric<std::uint64_t>(filename, args[1].first, args[1].second, true, true); 
    return std::make_shared<MIR::LifetimeStartInst>(inst_stmt, args[0].first->get_literal(), size);
}
MIR::InstPtr analyze_lifetime_end_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction .lifetime.end takes exactly two arguments");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .lifetime.end has no destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .lifetime.end takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .lifetime.end takes a pointer type argument for the first argument");
    }
    if(!Utils::is_int(args[1].second, 64)){
        Utils::error(filename, name, "Instruction .lifetime.end takes a second argument of type i64");
    }
    std::uint64_t size = Utils::to_numeric<std::uint64_t>(filename, args[1].first, args[1].second, true, true); 
    return std::make_shared<MIR::LifetimeEndInst>(inst_stmt, args[0].first->get_literal(), size);
}
MIR::InstPtr analyze_invariant_start_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 2){
        Utils::error(filename, name, "Instruction .invariant.start takes exactly two arguments");
    }
    if(dest == nullptr){
        Utils::error(filename, name, "Instruction .invariant.start requires a destination argument");
    }
    if(dest->get_type()->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .invariant.start requires a pointer type destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .invariant.start takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .invariant.start takes a pointer type argument for the first argument");
    }
    if(!Utils::is_int(args[1].second, 64)){
        Utils::error(filename, name, "Instruction .invariant.start takes a second argument of type i64");
    }
    std::uint64_t size = Utils::to_numeric<std::uint64_t>(filename, args[1].first, args[1].second, true, true); 
    return std::make_shared<MIR::InvariantStartInst>(inst_stmt, dest, args[0].first->get_literal(), size);
}
MIR::InstPtr analyze_invariant_end_inst(std::string filename, MIR::LocalRegisterPtr dest, IR::Token name,
                                std::vector<std::pair<IR::ExprPtr,IR::TypeExprPtr>> args,
                                IR::InstructionStmtPtr inst_stmt){
    auto attributes = inst_stmt->get_value()->get_attributes();
    if(args.size() != 3){
        Utils::error(filename, name, "Instruction .invariant.end takes exactly three arguments");
    }
    if(dest != nullptr){
        Utils::error(filename, name, "Instruction .invariant.end has no destination");
    }
    if(attributes.size() != 0){
        Utils::error(filename, name, "Instruction .invariant.end takes no attributes");
    }
    if(args[0].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .invariant.end takes a pointer type argument for the first argument");
    }
    if(args[1].second->get_kind() != IR::TypeExprKind::PtrTypeExpr){
        Utils::error(filename, name, "Instruction .invariant.end takes a pointer type argument for the second argument");
    }
    if(!Utils::is_int(args[2].second, 64)){
        Utils::error(filename, name, "Instruction .invariant.end takes a third argument of type i64");
    }
    std::uint64_t size = Utils::to_numeric<std::uint64_t>(filename, args[2].first, args[2].second, true, true); 
    return std::make_shared<MIR::InvariantEndInst>(inst_stmt, args[0].first->get_literal(), args[1].first->get_literal(), size);
}
}
}