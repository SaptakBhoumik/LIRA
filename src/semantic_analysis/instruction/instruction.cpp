#include "semantic_analysis/ir_to_mir.hpp"

namespace LIRA {
namespace SemanticAnalyzer {
bool is_arithmetic_bin_inst(std::string inst_name){
    return inst_name == ".add" || inst_name == ".sub" || inst_name == ".absdiff" || inst_name == ".mul" || inst_name == ".div" || inst_name == ".rem" || 
           inst_name == ".copysign" || inst_name == ".min" || inst_name == ".max" || inst_name == ".avg";
}
bool is_arithmetic_tri_inst(std::string inst_name){
    return inst_name == ".fma" || inst_name == ".fms" || inst_name == ".fnma" || inst_name == ".fnms" || inst_name == ".clamp";
}
bool is_widening_bin_inst(std::string inst_name){
    return inst_name == ".widening_add" || inst_name == ".widening_sub" || inst_name == ".widening_absdiff" || inst_name == ".widening_mul";
}
bool is_carry_inst(std::string inst_name){
    return inst_name == ".carry_add" || inst_name == ".carry_sub" || inst_name == ".carry_shl" || inst_name == ".carry_lshr" || inst_name == ".carry_ashr" || 
           inst_name == ".mac_wide" || inst_name == ".carry_shl_n"|| inst_name == ".carry_lshr_n"|| inst_name == ".carry_ashr_n";
}
bool is_other_arithmetic_inst(std::string inst_name){
    return inst_name == ".divmod" || inst_name == ".widening_divmod" || inst_name == ".mulhi" || inst_name == ".mulfix";
}
bool is_wrap_bin_inst(std::string inst_name){
    return inst_name ==".wrap_add" || inst_name == ".wrap_sub" || inst_name == ".wrap_absdiff" || inst_name == ".wrap_mul" || inst_name == ".wrap_div" || 
           inst_name == ".wrap_rem" || inst_name == ".wrap_copysign" || inst_name == ".wrap_shl" || inst_name == ".wrap_lshr" || 
           inst_name == ".wrap_ashr";
}
bool is_bitwise_bin_inst(std::string inst_name){
    return inst_name == ".and" || inst_name == ".nand" || inst_name == ".or" || inst_name == ".nor" || inst_name == ".xor" || inst_name == ".xnor" || 
           inst_name == ".shl" || inst_name == ".lshr" || inst_name == ".ashr" || inst_name == ".rotl" || inst_name == ".rotr" || 
           inst_name == ".pext" || inst_name == ".pdep";
}
bool is_bitwise_tri_inst(std::string inst_name){
    return inst_name == ".fshl" || inst_name == ".fshr" || inst_name == ".bitblend";
}
bool is_cmp_bin_inst(std::string inst_name){
    return inst_name == ".eq" || inst_name == ".neq" || inst_name == ".gt" || inst_name == ".ge" || inst_name == ".lt" || inst_name == ".le" ||  
           inst_name == ".either_nan" || inst_name == ".neither_nan" || inst_name == ".both_nan";
}
bool is_conv_inst(std::string inst_name){
    return inst_name == ".trunc" || inst_name == ".ext" || inst_name == ".float_to_int" || inst_name == ".int_to_float" || inst_name == ".ptr_to_int" ||  
           inst_name == ".int_to_ptr" || inst_name == ".bitcast";
}
bool is_unary_inst(std::string inst_name){
    return inst_name == ".neg" || inst_name == ".not" || inst_name == ".abs" || inst_name == ".ceil" || inst_name == ".floor" ||  
           inst_name == ".integral_part" || inst_name == ".fractional_part" || inst_name == ".roundnearest" || inst_name == ".roundeven" ||  
           inst_name == ".sqrt" || inst_name == ".reciprocal" || inst_name == ".rsqrt" || inst_name == ".popcount" || inst_name == ".clz" || 
           inst_name == ".ctz" || inst_name == ".parity" || inst_name == ".bswap" || inst_name == ".bitreverse" || inst_name == ".clrsb" || 
           inst_name == ".blsi" || inst_name == ".blsr" || inst_name == ".blsmask";
}
bool is_numerical_classify_inst(std::string inst_name){
    return inst_name == ".isnan" || inst_name == ".isinf" || inst_name == ".isfinite" || inst_name == ".isnormal" || inst_name == ".issubnormal" || 
           inst_name == ".iszero" || inst_name == ".isnegative" || inst_name == ".ispositive";
}
bool is_mem_inst(std::string inst_name){
    return inst_name == ".local" || inst_name == ".alloca" || inst_name == ".load" || inst_name == ".store" || inst_name == ".broadcast_load" || 
           inst_name == ".masked_load" || inst_name == ".masked_store" || inst_name == ".masked_gather" || inst_name == ".masked_scatter" || 
           inst_name == ".prefetch" || inst_name == ".memcopy" || inst_name == ".memset" || inst_name == ".memcmp" || inst_name == ".getaddress" || 
           inst_name == ".ptroffset" || inst_name == ".stacksave" || inst_name == ".stackrestore" || inst_name == ".extractelement" || 
           inst_name == ".insertelement" || inst_name == ".fence" || inst_name == ".atomic_cmpxchg" || inst_name == ".clflush" || inst_name == ".clwb" || 
           inst_name == ".cldemote" || inst_name == ".lifetime.start" || inst_name == ".lifetime.end" || inst_name == ".invariant.start" || inst_name == ".invariant.end";
}
bool is_arithmetic_fetch_bin_inst(std::string inst_name){
    return inst_name == ".fetch_xchg" || inst_name == ".fetch_add" || inst_name == ".fetch_sub" || inst_name == ".fetch_absdiff" || inst_name == ".fetch_mul" || inst_name == ".fetch_div" || inst_name == ".fetch_rem" ||  
           inst_name == ".fetch_copysign" || inst_name == ".fetch_min" || inst_name == ".fetch_max" || inst_name == ".fetch_avg";
}
bool is_bitwise_fetch_bin_inst(std::string inst_name){
    return inst_name == ".fetch_and" || inst_name == ".fetch_nand" || inst_name == ".fetch_or" || inst_name == ".fetch_nor" || inst_name == ".fetch_xor" || inst_name == ".fetch_xnor" ||  
           inst_name == ".fetch_shl" || inst_name == ".fetch_lshr" || inst_name == ".fetch_ashr" || inst_name == ".fetch_rotl" || inst_name == ".fetch_rotr" || 
           inst_name == ".fetch_pext" || inst_name == ".fetch_pdep";
}
bool is_unary_fetch_inst(std::string inst_name){
    return inst_name == ".fetch_neg" || inst_name == ".fetch_not" || inst_name == ".fetch_abs" || inst_name == ".fetch_ceil" || inst_name == ".fetch_floor" ||  
           inst_name == ".fetch_integral_part" || inst_name == ".fetch_fractional_part" || inst_name == ".fetch_roundnearest" || inst_name == ".fetch_roundeven" || 
           inst_name == ".fetch_sqrt" || inst_name == ".fetch_reciprocal" || inst_name == ".fetch_rsqrt" || inst_name == ".fetch_popcount" || inst_name == ".fetch_clz" || 
           inst_name == ".fetch_ctz" || inst_name == ".fetch_parity" || inst_name == ".fetch_bswap" || inst_name == ".fetch_bitreverse" || inst_name == ".fetch_clrsb" || 
           inst_name == ".fetch_blsi" || inst_name == ".fetch_blsr" || inst_name == ".fetch_blsmask";
}
bool is_terminator_inst(std::string inst_name){
    return inst_name == ".ret" || inst_name == ".unreachable" || inst_name == ".br" || inst_name == ".switch" || inst_name == ".indirectbr";
}
bool is_call_inst(std::string inst_name){
    return inst_name == ".call";
}
bool is_simd_inst(std::string inst_name){
    return inst_name == ".shufflevector" || inst_name == ".ternlog" || inst_name == ".splat" || inst_name == ".step_vector" || inst_name == ".insert_subvector" ||
           inst_name == ".extract_subvector" || inst_name == ".active_lane_mask" || inst_name == ".addsub" || inst_name == ".reduce_add" || inst_name == ".reduce_mul" ||
           inst_name == ".reduce_avg" || inst_name == ".reduce_min" || inst_name == ".reduce_max" || inst_name == ".reduce_and" || inst_name == ".reduce_or" ||
           inst_name == ".reduce_xor" || inst_name == ".reduce_xnor" || inst_name == ".hadd" || inst_name == ".hsub" || inst_name == ".habsdiff" || inst_name == ".haddsub" ||
           inst_name == ".hmul" || inst_name == ".havg" || inst_name == ".hmin" || inst_name == ".hmax" || inst_name == ".hand" || inst_name == ".hor" || 
           inst_name == ".hxor" || inst_name == ".hnand" || inst_name == ".hnor" || inst_name == ".hxnor" || inst_name == ".dot" || inst_name == ".sad" ||
           inst_name == ".pack_sat" || inst_name == ".unpack_lo" || inst_name == ".unpack_hi" || inst_name == ".compress" || inst_name == ".expand" ||
           inst_name == ".interleave2" || inst_name == ".interleave3" || inst_name == ".interleave4" || inst_name == ".deinterleave2" || inst_name == ".deinterleave3" ||
           inst_name == ".deinterleave4" || inst_name == ".mask_to_int" || inst_name == ".int_to_mask";
}
bool is_other_inst(std::string inst_name){
    return inst_name == ".select" || inst_name == ".freeze" || inst_name == ".va_start" || inst_name == ".va_end" || inst_name == ".va_copy" || 
           inst_name == ".va_arg" || inst_name == ".ptrmask" || inst_name == ".pause" || inst_name == ".assume" || inst_name == ".assume_range" || 
           inst_name == ".assume_not" || inst_name == ".assume_not_range" || inst_name == ".expect" || inst_name == ".expect_range" || 
           inst_name == ".expect_not" || inst_name == ".expect_not_range" || inst_name == ".nop" ||  inst_name == ".annotation" || inst_name == ".endbr64" || 
           inst_name == ".launder" || inst_name == ".strip_invariant_group";
}
bool is_hardware_inst(std::string inst_name){
    return inst_name == ".cpuid" || inst_name == ".rdtsc" || inst_name == ".rdtscp" || inst_name == ".rdrand" || inst_name == ".rdseed" || inst_name == ".get_fpenv" ||
           inst_name == ".set_fpenv" || inst_name == ".fpenv_get_field" || inst_name == ".fpenv_set_field" || inst_name == ".get_fpstatus" || inst_name == ".clear_fpstatus" ||
           inst_name == ".aesenc" || inst_name == ".aesenclast" || inst_name == ".aesdec" || inst_name == ".aesdeclast" || inst_name == ".aesimc" || inst_name == ".aeskeygenassist" ||
           inst_name == ".clmul" || inst_name == ".sha1rnds4" || inst_name == ".sha1nexte" || inst_name == ".sha1msg1" || inst_name == ".sha1msg2" || inst_name == ".sha256rnds2" ||
           inst_name == ".sha256msg1" || inst_name == ".sha256msg2" || inst_name == ".crc32" || inst_name == ".syscall" || inst_name == ".rdssp" || inst_name == ".incssp" ||
           inst_name == ".saveprevssp" || inst_name == ".rstorssp" || inst_name == ".setssbsy" || inst_name == ".wrss";
}
bool is_global_inst(std::string inst_name){
    return inst_name == ".global" || inst_name == ".assign_type";
}
MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_instruction(IR::InstructionStmtPtr inst_stmt){
    auto instruction = inst_stmt->get_value();
    if(!instruction.has_value()){
        Utils::error(this->filename,inst_stmt->get_token(),"Instruction statement has no instruction value", "Assign to .local(T:poison) if you want to create a undef value variable");
    }
    IR::Token inst_name = instruction.value().get_token();
    MIR::InstPtr inst = nullptr;
    if(is_arithmetic_bin_inst(inst_name.value)){
        inst = analyze_arithmetic_bin_inst(inst_name,inst_stmt);
    }
    else if(is_arithmetic_tri_inst(inst_name.value)){
        inst = analyze_arithmetic_tri_inst(inst_name,inst_stmt);
    }
    else if(is_widening_bin_inst(inst_name.value)){
        inst = analyze_widening_bin_inst(inst_name,inst_stmt);
    }
    else if(is_carry_inst(inst_name.value)){
        inst = analyze_carry_inst(inst_name,inst_stmt);
    }
    else if(is_other_arithmetic_inst(inst_name.value)){
        inst = analyze_other_arithmetic_inst(inst_name,inst_stmt);
    }
    else if(is_wrap_bin_inst(inst_name.value)){
        inst = analyze_wrap_bin_inst(inst_name,inst_stmt);
    }
    else if(is_bitwise_bin_inst(inst_name.value)){
        inst = analyze_bitwise_bin_inst(inst_name,inst_stmt);
    }
    else if(is_bitwise_tri_inst(inst_name.value)){
        inst = analyze_bitwise_tri_inst(inst_name,inst_stmt);
    }
    else if(is_cmp_bin_inst(inst_name.value)){
        inst = analyze_cmp_bin_inst(inst_name,inst_stmt);
    }
    else if(is_conv_inst(inst_name.value)){
        inst = analyze_conv_inst(inst_name,inst_stmt);
    }
    else if(is_unary_inst(inst_name.value)){
        inst = analyze_unary_inst(inst_name,inst_stmt);
    }
    else if(is_numerical_classify_inst(inst_name.value)){
        inst = analyze_numerical_classify_inst(inst_name,inst_stmt);
    }
    else if(is_mem_inst(inst_name.value)){
        inst = analyze_mem_inst(inst_name,inst_stmt);
    }
    else if(is_arithmetic_fetch_bin_inst(inst_name.value)){
        inst = analyze_arithmetic_fetch_bin_inst(inst_name,inst_stmt);
    }
    else if(is_bitwise_fetch_bin_inst(inst_name.value)){
        inst = analyze_bitwise_fetch_bin_inst(inst_name,inst_stmt);
    }
    else if(is_unary_fetch_inst(inst_name.value)){
        inst = analyze_unary_fetch_inst(inst_name,inst_stmt);
    }
    else if(is_terminator_inst(inst_name.value)){
        inst = analyze_terminator_inst(inst_name,inst_stmt);
    }
    else if(is_call_inst(inst_name.value)){
        inst = analyze_call_inst(inst_name,inst_stmt);
    }
    else if(is_simd_inst(inst_name.value)){
        inst = analyze_simd_inst(inst_name,inst_stmt);
    }
    else if(is_other_inst(inst_name.value)){
        inst = analyze_other_inst(inst_name,inst_stmt);
    }
    else if(is_hardware_inst(inst_name.value)){
        inst = analyze_hardware_inst(inst_name,inst_stmt);
    }
    else if(is_global_inst(inst_name.value)){
        Utils::error(this->filename,inst_stmt->get_value()->get_token(),"Instruction " + inst_name.value + " is a global instruction and cannot be used within a label");
    }
    else{
        Utils::error(this->filename,inst_stmt->get_value()->get_token(),"Unknown instruction: " + inst_name.value);
    }
    add_dest_to_symtable(inst->get_destination());
    return inst;
}
}
}