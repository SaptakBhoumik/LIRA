#include "semantic_analysis/ir_to_mir.hpp"

namespace LIRA {
namespace SemanticAnalyzer {
bool is_arithmetic_bin_inst(std::string inst_name){
    return inst_name == ".add" || inst_name == ".sub" || inst_name == ".absdiff" || inst_name == ".mul" || inst_name == ".div" || inst_name == ".rem" 
            || inst_name == ".copysign" || inst_name == ".min" || inst_name == ".max" || inst_name == ".avg";
}
bool is_arithmetic_tri_inst(std::string inst_name){
    return inst_name == ".fma" || inst_name == ".fms" || inst_name == ".fnma" || inst_name == ".fnms" || inst_name == ".clamp";
}
bool is_widening_bin_inst(std::string inst_name){
    return inst_name == ".widening_add" || inst_name == ".widening_sub" || inst_name == ".widening_absdiff" || inst_name == ".widening_mul";
}
bool is_other_arithmetic_inst(std::string inst_name){
    return inst_name == ".divmod" || inst_name == ".widening_divmod" || inst_name == ".mulhi" || inst_name == ".mulfix";
}
bool is_bitwise_bin_inst(std::string inst_name){
    return inst_name == ".and" || inst_name == ".or" || inst_name == ".xor" || inst_name == ".shl" || inst_name == ".lshr" || inst_name == ".ashr";
}
// ## Bitwise Trinary Instructions
bool is_cmp_bin_inst(std::string inst_name){
    return inst_name == ".eq" || inst_name == ".neq" || inst_name == ".gt" || inst_name == ".ge" || inst_name == ".lt" || inst_name == ".le" 
            || inst_name == ".either_nan" || inst_name == ".neither_nan" || inst_name == ".both_nan";
}
bool is_conv_inst(std::string inst_name){
    return inst_name == ".trunc" || inst_name == ".ext" || inst_name == ".float_to_int" || inst_name == ".int_to_float" || inst_name == ".ptr_to_int" 
            || inst_name == ".int_to_ptr" || inst_name == ".bitcast";
}
bool is_unary_inst(std::string inst_name){
    return inst_name == ".neg" || inst_name == ".not" || inst_name == ".abs" || inst_name == ".ceil" || inst_name == ".floor" 
          || inst_name == ".integral_part" || inst_name == ".fractional_part" || inst_name == ".roundnearest" || inst_name == ".roundeven" 
          || inst_name == ".sqrt" || inst_name == ".reciprocal" || inst_name == ".rsqrt" || inst_name == ".popcount" || inst_name == ".clz"
          || inst_name == ".ctz" || inst_name == ".parity" || inst_name == ".bswap" || inst_name == ".bitreverse" || inst_name == ".clrsb";
}
bool is_numerical_classify_inst(std::string inst_name){
    return inst_name == ".isnan" || inst_name == ".isinf" || inst_name == ".isfinite" || inst_name == ".isnormal" || inst_name == ".issubnormal"
            || inst_name == ".iszero" || inst_name == ".isnegative" || inst_name == ".ispositive";
}
bool is_mem_inst(std::string inst_name){
    return inst_name == ".local" || inst_name == ".alloca" || inst_name == ".load" || inst_name == ".store" || inst_name == ".getaddress" || inst_name == ".ptroffset"
            || inst_name == ".extractelement" || inst_name == ".insertelement" || inst_name == ".fence" || inst_name == ".cmpxchg";
}
bool is_fetch_inst(std::string inst_name){
    return inst_name == ".fetchxchg" || inst_name == ".fetchadd" || inst_name == ".fetchsub" || inst_name == ".fetchand" 
            || inst_name == ".fetchnand" || inst_name == ".fetchor" || inst_name == ".fetchxor" || inst_name == ".fetchmin" 
            || inst_name == ".fetchmax";
}
bool is_terminator_inst(std::string inst_name){
    return inst_name == ".ret" || inst_name == ".unreachable" || inst_name == ".br" || inst_name == ".switch" || inst_name == ".indirectbr";
}
bool is_call_inst(std::string inst_name){
    return inst_name == ".call";
}
bool is_other_inst(std::string inst_name){
    return inst_name == ".select" || inst_name == ".freeze" || inst_name == ".va_arg" || inst_name == ".ptrmask" || inst_name == ".shufflevector" ;
}
MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_instruction(IR::InstructionStmtPtr inst_stmt){
    IR::Token inst_name = inst_stmt->get_value()->get_token();
    if(is_arithmetic_bin_inst(inst_name.value)){
        return analyze_arithmetic_bin_inst(inst_name,inst_stmt);
    }
    else if(is_arithmetic_tri_inst(inst_name.value)){
        return analyze_arithmetic_tri_inst(inst_name,inst_stmt);
    }
    else if(is_widening_bin_inst(inst_name.value)){
        return analyze_widening_bin_inst(inst_name,inst_stmt);
    }
    else if(is_other_arithmetic_inst(inst_name.value)){
        return analyze_other_arithmetic_inst(inst_name,inst_stmt);
    }
    else if(is_bitwise_bin_inst(inst_name.value)){
        return analyze_bitwise_bin_inst(inst_name,inst_stmt);
    }
    // ## Bitwise Trinary Instructions
    else if(is_cmp_bin_inst(inst_name.value)){
        return analyze_cmp_bin_inst(inst_name,inst_stmt);
    }
    else if(is_conv_inst(inst_name.value)){
        return analyze_conv_inst(inst_name,inst_stmt);
    }
    else if(is_unary_inst(inst_name.value)){
        return analyze_unary_inst(inst_name,inst_stmt);
    }
    else if(is_numerical_classify_inst(inst_name.value)){
        return analyze_numerical_classify_inst(inst_name,inst_stmt);
    }
    else if(is_mem_inst(inst_name.value)){
        return analyze_mem_inst(inst_name,inst_stmt);
    }
    else if(is_fetch_inst(inst_name.value)){
        return analyze_fetch_inst(inst_name,inst_stmt);
    }
    else if(is_terminator_inst(inst_name.value)){
        return analyze_terminator_inst(inst_name,inst_stmt);
    }
    else if(is_call_inst(inst_name.value)){
        return analyze_call_inst(inst_name,inst_stmt);
    }
    else if(is_other_inst(inst_name.value)){
        return analyze_other_inst(inst_name,inst_stmt);
    }
    else{
        Utils::error(this->filename,inst_stmt->get_value()->get_token(),"Unknown instruction: " + inst_name.value);
    }
}
}
}