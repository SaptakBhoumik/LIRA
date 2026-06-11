#pragma once
#include "ast/ast.hpp"
#include "lexer/token.hpp"
#include "mir/destregister.hpp"
#include "mir/instruction.hpp"
#include "mir/instruction/_instruction.hpp"
#include <map>
namespace LIRA {
namespace Pass {
class SemanticAnalyzer {
    IR::ProgramPtr program;

    //Utils.
    //type_eq,type_compatible,add_global_type all expect reduced types. So the caller should call get_reduced_type before calling these functions.
    bool type_eq(IR::TypeExprPtr t1, IR::TypeExprPtr t2) const;//Check if two types are equal. This is a recursive function that checks if the two types are equal
    bool type_compatible(IR::TypeExprPtr type, IR::ExprPtr literal) const;//Check if a reduced type is compatible with a literal. This is used to check if a literal can be assigned to a variable of a certain type.
    //Throws error if name is already defined in the current scope.
    void add_local_sym(IR::Token name, IR::TypeExprPtr type);
    void add_local_temp_block_sym(IR::Token name, IR::TypeExprPtr type);//Temporary block variable only defined in the current block
    void add_global_sym(IR::Token name, IR::TypeExprPtr type);
    void add_global_type(IR::Token name, IR::TypeExprPtr type);
    [[noreturn]] void error(IR::Token tok, std::string msg,std::string submsg="",std::string ecode="") const;
    std::pair<MIR::FastMathAttr, std::vector<IR::AttributePtr>> extract_fastmath_attrs(const std::vector<IR::AttributePtr>& attributes) const;//Extract fast math attributes from the given attributes and return them as a pair of FastMathAttr and the remaining attributes. 
    std::pair<std::map<std::string,bool>, std::vector<IR::AttributePtr>> extract_flag_attrs(const std::vector<IR::AttributePtr>& attributes,
                                                                                            std::vector<std::string> flags_to_extract) const;//Extract flag attributes from the given attributes and return them as a map of flag name to the corresponding attributes and the remaining attributes.
                                                                                                                                                   // True if flag found. Else false. Assumes the flag attribute has no argument. IF it has error then error

    IR::TypeExprPtr get_sym_reduced_type(IR::Token name) const;//Get the reduced type of symbol.
    IR::TypeExprPtr get_reduced_type(IR::TypeExprPtr type) const;//Get the reduced type of a type expression. Throws error if unsupported attribute is found or if type defination is wrong
    //TODO:Other things

    //Instruction analysis. NOTE: The analyze_instruction function analyzes instruction within a label so cant handle stuff like .global and .assign_type which are global 
    MIR::InstPtr analyze_instruction(IR::InstructionStmtPtr inst_stmt);//Analyze an instruction statement, add symbols to the symbol table and return the corresponding MIR instruction.
    
    MIR::InstPtr analyze_arithmetic_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_add_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient, 
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_sub_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient, 
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_mul_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient, 
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_div_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient, 
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_rem_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient, 
                                      IR::InstructionStmtPtr inst_stmt);

    MIR::InstPtr analyze_bitwise_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_and_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient, 
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_or_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient, 
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_xor_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient, 
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_shl_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient,
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_lshr_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient,
                                      IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_ashr_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, MIR::InstOperandTypeVarient type_varient,
                                      IR::InstructionStmtPtr inst_stmt);


    MIR::InstPtr analyze_cmp_bin_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_eq_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                     IR::TypeExprPtr type, MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_neq_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                      IR::TypeExprPtr type, MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_gt_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                      IR::TypeExprPtr type, MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_lt_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                      IR::TypeExprPtr type, MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_ge_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                      IR::TypeExprPtr type, MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_le_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                      IR::TypeExprPtr type, MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_either_nan_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs,
                                            IR::TypeExprPtr type, MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_neither_nan_bin_inst(MIR::LocalDestRegisterPtr dest, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                             IR::TypeExprPtr type, MIR::InstOperandTypeVarient type_varient, IR::InstructionStmtPtr inst_stmt);
    
    MIR::InstPtr analyze_conv_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_unary_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_mem_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_fetch_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_terminator_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_call_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);
    MIR::InstPtr analyze_other_inst(IR::Token name,IR::InstructionStmtPtr inst_stmt);

    //Destination argument
    MIR::LocalDestRegisterPtr process_local_dest_arg(IR::InstructionStmtPtr inst_stmt);//Reduce type,add symbol to symol table
    public:
    SemanticAnalyzer(IR::ProgramPtr program);
};
}
}