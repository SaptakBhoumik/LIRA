#pragma once
#include "ast/ast.hpp"
#include "lexer/token.hpp"
#include "mir/register.hpp"
#include "mir/instruction.hpp"
#include "mir/instruction/_instruction.hpp"
#include "symtable/symtable.hpp"
#include <map>
namespace LIRA {
namespace Utils {
//Put it in a proper file later. Perhaps type_utils.hpp and error function in error_util.hpp. Or something like that
bool type_eq(IR::TypeExprPtr t1, IR::TypeExprPtr t2);//Check if two types are equal. This is a recursive function that checks if the two types are equal
bool type_ge(std::string filename, IR::TypeExprPtr t1, IR::TypeExprPtr t2);//Check if type t1 is greater than or equal to type t2. Expects 2 type of the same TypeVariant(Else error)
                                                                           //Expects float or int or their vector(Otherwise error)
                                                                           //If scaler float/int then return if basetype size is greater or equal. 
                                                                           //If vector then we expect the same number of elements(Error otherwise) and expects the base type to have same TypeVariant(Else error)
                                                                           //If same number of element we compare size of basetype
bool is_int(IR::TypeExprPtr type, std::size_t bits);//Check if the type is an integer type of the given bit width. Expects reduced type. Returns false if type is not int type
bool is_vector_of_int(IR::TypeExprPtr type, std::size_t bits, std::size_t size);//Check if the type is an vector of int of the given bit width and size. Expects reduced type. Returns false if type is not vector of int type
bool is_float(IR::TypeExprPtr type, std::size_t bits, bool is_brain_float);//Check if the type is an float type of the given bit width. Expects reduced type. Returns false if type is not float type
bool type_compatible(VarSymTablePtr var_symtable, IR::TypeExprPtr type, IR::ExprPtr literal);//Check if a reduced type is compatible with a literal. This is used to check if a literal can be assigned to a variable of a certain type.
bool is_constexpr(IR::ExprPtr expr);//Check if an expression is a constant expression
std::optional<std::string> reduce_str_value(IR::ExprPtr literal);//If the literal is a constant expresstion then we return the reduced string value as the second element of the pair
                                                                 //In case of raw string or regular string literal, return the valid string. Like we currently store string as stuff
                                                                 //like "Hello\nWorld" but we want the string with \n replaced with an actual new line
std::optional<MIR::FPEnvField> get_fpenv_field(IR::ExprPtr literal, bool is_x87);//Get the FP environment field from an expression. Returns nullopt if the expression is not a valid FP environment field or if it not a constexpr str
bool is_18_array(IR::TypeExprPtr type);//Check if the type is an array of i8. Expects reduced type. Returns false if type is not an array of i8
std::optional<std::string> get_var_name(IR::ExprPtr expr);//Get the variable name from an expression. Returns nullopt if the expression is not a variable
template<typename T>
T to_numeric(std::string filename, IR::ExprPtr value, IR::TypeExprPtr type, bool allow_hex = false, bool allow_binary = false);//Expects constexpr. Returns error if false
                                                                                                                               //Also returns error if the value dont fit in type. Expects type to be integer/float or else error
                                                                                                                               //Uses ``T to_numeric(const std::string& str, bool allow_hex = false, bool allow_binary = false);`` in the underlying implementation
                                                                                                                               //The decoding for when allow_hex/allow_binary is true is done based on if T is float or int. 
                                                                                                                               //If T is float then we treat the hex/bin as float of that size. Else we treat it as int of that size
std::size_t get_type_size(IR::TypeExprPtr type);//Get the size of a reduced type in bits.
[[noreturn]] void error(std::string filename, IR::Token tok, std::string msg,std::string submsg="",std::string ecode="");
//extract_flag_attrs, extract_common_fetch_attrs, extract_attrs_with_num_args and extract_fastmath_attrs may throw error if duplicate of the attribute is found. Like if they are asked to search for "attr_name" and "attr_name"
//is present twice then error. Note no error if "attr_name" is present twice if we dont ask to search for "attr_name". So we check duplicate only for the attributes asked
//for error they both need std::string
//Combining ieee754_2019 with nsz is compile time error. ``extract_fastmath_attrs`` checks that
std::pair<MIR::FastMathAttr, std::vector<IR::AttributePtr>> extract_fastmath_attrs(std::string filename, const std::vector<IR::AttributePtr>& attributes);//Extract fast math attributes from the given attributes and return them as a pair of FastMathAttr and the remaining attributes. 
std::pair<std::map<std::string,bool>, std::vector<IR::AttributePtr>> extract_flag_attrs(std::string filename, const std::vector<IR::AttributePtr>& attributes,
                                                                                        std::vector<std::string> flags_to_extract);//Extract flag attributes from the given attributes and return them as a map of flag name to the corresponding attributes and the remaining attributes.
                                                                                                                                   // True if flag found. Else false. Assumes the flag attribute has no argument. IF it has error then error
std::pair<MIR::CommonFetchInstAttrs, std::vector<IR::AttributePtr>> extract_common_fetch_attrs(std::string filename, const std::vector<IR::AttributePtr>& attributes);
std::pair<MIR::CommonMemoryInstAttrs, std::vector<IR::AttributePtr>> extract_common_memory_attrs(std::string filename, const std::vector<IR::AttributePtr>& attributes);
std::optional<MIR::AtomicOrdering> get_atomic_ordering(IR::ExprPtr literal);//Expects a constexpr string literal with valid atomic ordering name. Returns std::nullopt if not true
std::pair<MIR::SyncScope, std::vector<IR::AttributePtr>> extract_syncscope_attr(std::string filename, const std::vector<IR::AttributePtr>& attributes);//Returns global if not found 
std::pair<std::optional<std::pair<MIR::AtomicOrdering, MIR::SyncScope>>, std::vector<IR::AttributePtr>> extract_atomic_info_attr(std::string filename, const std::vector<IR::AttributePtr>& attributes);
template<typename T>
std::pair<std::map<std::string,std::vector<T>>, std::vector<IR::AttributePtr>> extract_attrs_with_num_args(std::string filename, const std::vector<IR::AttributePtr>& attributes, std::vector<std::string> attrs_to_extract);//Extract numerical argument attributes from the given attributes and return them as a map of attribute name to the corresponding attributes and the remaining attributes.
                                                                                                                                                                                                                       //The map contains the attribute name as the key and a vector of T as the value. The vector contains the numerical arguments of the attribute. 
bool contains_float(IR::TypeExprPtr type);//Check if the type contains a float. Like struct with float,array of float,vector of float or just a regular float                                                                                                                                                                                                                //Assumes the attribute has numerical arguments. If it has no argument or non-numerical argument then error
IR::TypeExprPtr get_sym_reduced_type(VarSymTablePtr var_symtable, IR::Token name);//Get the reduced type of symbol.                                                                                                                                                 
IR::TypeExprPtr get_reduced_type(TypeSymTablePtr type_symtable, IR::TypeExprPtr type);//Get the reduced type of a type expression. Throws error if unsupported attribute is found or if type defination is wrong
bool is_pow_of_2(std::size_t n);//Check if a number is a power of 2. Returns true if n is a power of 2, false otherwise. Returns false for n=0
}
namespace SemanticAnalyzer {
class IRToMIRSemanticAnalyzer {
    IR::ProgramPtr program;
    std::string filename;
    Utils::VarSymTablePtr var_symtable;
    Utils::TypeSymTablePtr type_symtable;
    IR::TypeExprPtr curr_func_ret_type;//Return type of the current function being analyzed. Nullptr if not in a function.
    //Utils.
    //type_eq,type_compatible,add_global_type all expect reduced types. So the caller should call get_reduced_type before calling these functions.
    //Throws error if name is already defined in the current scope.
    void add_local_sym(IR::Token name, IR::TypeExprPtr type);
    void add_local_temp_block_sym(IR::Token name, IR::TypeExprPtr type);//Temporary block variable only defined in the current block
    void add_global_sym(IR::Token name, IR::TypeExprPtr type);
    void add_global_type(IR::Token name, IR::TypeExprPtr type);
    
    
    //TODO:Other things

    //Instruction analysis. NOTE: The analyze_instruction function analyzes instruction within a label so cant handle stuff like .global and .assign_type which are global 
    MIR::InstPtr analyze_instruction(IR::InstructionStmtPtr inst_stmt);//Analyze an instruction statement, add symbols to the symbol table and return the corresponding MIR instruction.
    MIR::InstPtr analyze_arithmetic_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_arithmetic_tri_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_widening_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_carry_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_other_arithmetic_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_wrap_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_bitwise_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_bitwise_tri_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_cmp_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_conv_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_unary_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_numerical_classify_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_mem_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_terminator_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_arithmetic_fetch_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_bitwise_fetch_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_unary_fetch_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_call_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_simd_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_other_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_hardware_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);

    //Destination argument
    MIR::LocalRegisterPtr process_local_dest_arg(IR::InstructionStmtPtr inst_stmt);//Reduce type,aReturn nullptr if no destination argument
                                                                                       //Throws error if the type is ``type`` because typedef is allowed only at global scope
                                                                                       //Does not to symbol table because the destination variable cant be used as an operand in the same instruction. 
                                                                                       //So we add it to the symbol table in analyze_instruction after analyzing the instruction
                                                                                       //It also checks if the attributes of destination are valid for the type of destination
    void add_dest_to_symtable(MIR::LocalRegisterPtr dest);//Does nothing if dest is nullptr. Adds destination to symbol table if not nullptr. 
                                                              //Used in the MIR::InstPtr IRToMIRSemanticAnalyzer::analyze_instruction(IR::InstructionStmtPtr inst_stmt) method at the end after analyzing the instruction. 
    public:
    IRToMIRSemanticAnalyzer(IR::ProgramPtr program);
};
}
}