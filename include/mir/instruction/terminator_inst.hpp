#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
class RetInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;

    bool noreturn;//Whether the instruction has the noreturn attribute or not. 
    std::optional<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> ret_value;//The first input vector and its type
    public:
    RetInst(IR::InstructionStmtPtr instruction_stmt, std::optional<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> ret_value, bool noreturn);

    std::optional<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> get_ret_value() const;
    bool is_noreturn() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Return std::nullopt
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};

class UnreachableInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    public:
    UnreachableInst(IR::InstructionStmtPtr instruction_stmt);

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Return std::nullopt
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};


class JmpInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    
    std::string target_block_name;//The name of the target block to jump to
    std::shared_ptr<IR::LabelTypeExpr> label_type;
    std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> args;//The arguments to pass to the target block. The type of each argument must match the corresponding parameter type of the target block
    public:
    JmpInst(IR::InstructionStmtPtr instruction_stmt, std::string target_block_name, std::shared_ptr<IR::LabelTypeExpr> label_type, 
            std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> args);
    
    std::string get_target_block_name() const;
    std::shared_ptr<IR::LabelTypeExpr> get_label_type() const;
    std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> get_args() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Return std::nullopt
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};

class ConditionalJmpInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    
    std::string true_block_name;//The name of the target block to jump to if condition is true
    std::string false_block_name;//The name of the target block to jump to if condition is false
    std::shared_ptr<IR::LabelTypeExpr> true_label_type;
    std::shared_ptr<IR::LabelTypeExpr> false_label_type;
    std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> true_label_args;
    std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> false_label_args;
    IR::LiteralExprPtr condition;//The condition to check. Must be of i1 type

    std::vector<std::size_t> frequency_profile;//The frequency profile of the conditional jump instruction. It is a vector of two integers. Empty if not provided. Note empty dont mean unpredictable. We still try to figure out the most frequent case unless u explicitly set unpredictable to true
    bool unpredictable;//If set then it is unpredictable. We should not try to figure out even if frequency_profile not provided
    public:
    ConditionalJmpInst(IR::InstructionStmtPtr instruction_stmt, std::string true_block_name, std::string false_block_name, 
                       std::shared_ptr<IR::LabelTypeExpr> true_label_type, std::shared_ptr<IR::LabelTypeExpr> false_label_type,
                       std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> true_label_args, std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> false_label_args, 
                       IR::LiteralExprPtr condition, std::vector<std::size_t> frequency_profile, bool unpredictable);
    
    std::string get_true_block_name() const;
    std::string get_false_block_name() const;
    std::shared_ptr<IR::LabelTypeExpr> get_true_label_type() const;
    std::shared_ptr<IR::LabelTypeExpr> get_false_label_type() const;
    std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> get_true_label_args() const;
    std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> get_false_label_args() const;
    IR::LiteralExprPtr get_condition() const;
    std::vector<std::size_t> get_frequency_profile() const;
    bool is_unpredictable() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Return std::nullopt
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};


class SwitchInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    
    IR::LiteralExprPtr condition;//The condition to check. Must be of integer type

    std::vector<std::string> case_block_names;//The name of the target block to jump to for each case
    std::vector<std::shared_ptr<IR::LabelTypeExpr>> case_label_types;
    std::vector<std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>>> case_label_args;
    std::vector<IR::LiteralExprPtr> case_values;//The value of each case. Must be of the same type as condition. 
    //Note:-The order of case_block_names, case_label_types, case_label_args and case_values must be the same. i.e. case_block_names[i], case_label_types[i], case_label_args[i] and case_values[i] must correspond to the same case

    std::string default_block_name;//The name of the default block to jump to if no case matches
    std::shared_ptr<IR::LabelTypeExpr> default_label_type;
    std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> default_label_args;

    std::vector<std::size_t> frequency_profile;//The frequency profile of the switch instruction. It is a vector of integers. Empty if not provided. Note empty dont mean unpredictable. We still try to figure out the most frequent case unless u explicitly set unpredictable to true
    bool unpredictable;//If set then it is unpredictable. We should not try to figure out even if frequency_profile not provided
    public:
    SwitchInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr condition, std::vector<std::string> case_block_names, std::vector<std::shared_ptr<IR::LabelTypeExpr>> case_label_types, 
              std::vector<std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>>> case_label_args, std::vector<IR::LiteralExprPtr> case_values, std::string default_block_name, 
              std::shared_ptr<IR::LabelTypeExpr> default_label_type, std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> default_label_args, std::vector<std::size_t> frequency_profile, bool unpredictable);
    
    IR::LiteralExprPtr get_condition() const;
    std::vector<std::string> get_case_block_names() const;
    std::vector<std::shared_ptr<IR::LabelTypeExpr>> get_case_label_types() const;
    std::vector<std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>>> get_case_label_args() const;
    std::vector<IR::LiteralExprPtr> get_case_values() const;
    std::string get_default_block_name() const;
    std::shared_ptr<IR::LabelTypeExpr> get_default_label_type() const;
    std::vector<std::pair<IR::TypeExprPtr,IR::LiteralExprPtr>> get_default_label_args() const;
    std::vector<std::size_t> get_frequency_profile() const;
    bool is_unpredictable() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Return std::nullopt
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};


class IndirectJmpInst:public Inst {
    IR::InstructionStmtPtr instruction_stmt;
    
    IR::LiteralExprPtr target_block_address;//The address of the target block to jump to. Must be of pointer type pointing to a label type
    std::vector<std::string> possible_target_blocks;//The names of the possible target blocks to jump to. Used for optimization. Cant be empty. These block cant take in argument
    //Also remember, IndirectJmpInst and other similar instruction may reference a block that is not yet declared. But that is allowed because blocks are accessible regardless of their position
    //Remember it when making the typechecker. Block exist even if not yet declared
    /*
    fn name() -> void {
        label @start:
            %x = 10
            br @next//allowed even if next not yet declared because block exist regardless of their position
        label @next:
            br @hello(12)
        label @hello(i32 %a)://%a is only accessible in this block i.e local to this block
            br @bye
        label @bye:
            ret %x//%x is accessible but %a is not
    }
    */

    std::vector<std::size_t> frequency_profile;//The frequency profile of the switch instruction. It is a vector of integers. Empty if not provided. Note empty dont mean unpredictable. We still try to figure out the most frequent case unless u explicitly set unpredictable to true
    bool unpredictable;//If set then it is unpredictable. We should not try to figure out even if frequency_profile not provided
    public:
    IndirectJmpInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr target_block_address, std::vector<std::string> possible_target_blocks, 
                    std::vector<std::size_t> frequency_profile, bool unpredictable);
    
    IR::LiteralExprPtr get_target_block_address() const;
    std::vector<std::string> get_possible_target_blocks() const;
    std::vector<std::size_t> get_frequency_profile() const;
    bool is_unpredictable() const;

    std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const override;//Return std::nullopt
    InstType get_inst_type() const override;
    IR::InstructionStmtPtr get_instruction_stmt() const override;
    std::string to_string() const override;
};
}
}