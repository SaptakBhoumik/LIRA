#pragma once
#include "ast/ast.hpp"
#include "lexer/token.hpp"
#include "mir/destregister.hpp"
#include "mir/instruction.hpp"
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
bool type_compatible(VarSymTablePtr var_symtable, IR::TypeExprPtr type, IR::ExprPtr literal);//Check if a reduced type is compatible with a literal. This is used to check if a literal can be assigned to a variable of a certain type.
[[noreturn]] void error(std::string filename, IR::Token tok, std::string msg,std::string submsg="",std::string ecode="");
//extract_flag_attrs and extract_fastmath_attrs may throw error if duplicate of the attribute is found. Like if they are asked to search for "attr_name" and "attr_name"
//is present twice then error. Note no error if "attr_name" is present twice if we dont ask to search for "attr_name". So we check duplicate only for the attributes asked
//for error they both need std::string
std::pair<MIR::FastMathAttr, std::vector<IR::AttributePtr>> extract_fastmath_attrs(std::string filename, const std::vector<IR::AttributePtr>& attributes);//Extract fast math attributes from the given attributes and return them as a pair of FastMathAttr and the remaining attributes. 
std::pair<std::map<std::string,bool>, std::vector<IR::AttributePtr>> extract_flag_attrs(std::string filename, const std::vector<IR::AttributePtr>& attributes,
                                                                                        std::vector<std::string> flags_to_extract);//Extract flag attributes from the given attributes and return them as a map of flag name to the corresponding attributes and the remaining attributes.
IR::TypeExprPtr get_sym_reduced_type(VarSymTablePtr var_symtable, IR::Token name);//Get the reduced type of symbol.                                                                                                                                                 // True if flag found. Else false. Assumes the flag attribute has no argument. IF it has error then error
IR::TypeExprPtr get_reduced_type(TypeSymTablePtr type_symtable, IR::TypeExprPtr type);//Get the reduced type of a type expression. Throws error if unsupported attribute is found or if type defination is wrong
}
namespace SemanticAnalyzer {
class IRToMIRSemanticAnalyzer {
    IR::ProgramPtr program;
    std::string filename;
    Utils::VarSymTablePtr var_symtable;
    Utils::TypeSymTablePtr type_symtable;
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
    //## Fixed-Point Arithmetic Instructions
    MIR::InstPtr analyze_widening_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    // ## Carry/Borrowing instructions
    // ## Combined Quotient and Remainder (`divmod`)
    // ## Overflow-Wrap (Checked Arithmetic) Instructions
    // ## High-Half Multiply

    MIR::InstPtr analyze_bitwise_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_and_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_or_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_xor_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant, 
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_shl_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant,
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_lshr_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant,
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_ashr_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::TypeVariant type_variant,
                                      IR::InstructionStmtPtr inst_stmt);
    // ## Bitwise Trinary Instructions
    MIR::InstPtr analyze_cmp_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_conv_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_unary_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_numerical_classify_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_mem_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_fetch_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_terminator_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_call_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_other_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);

    //Destination argument
    MIR::LocalDestRegisterPtr process_local_dest_arg(IR::InstructionStmtPtr inst_stmt);//Reduce type,add symbol to symol table
    public:
    IRToMIRSemanticAnalyzer(IR::ProgramPtr program);
};
}
}