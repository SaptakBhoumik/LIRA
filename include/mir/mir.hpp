#pragma once
#include "ast/ast.hpp"
#include "instruction.hpp"
#include "register.hpp"
namespace LIRA {
namespace MIR{
class Label{
    std::string name;

    std::vector<LabelParamRegisterPtr> parameters; //In proper order
    std::unordered_map<std::string,std::uint64_t> parameter_map;//For faster access. The second argument is the index of the parameter
    std::vector<InstPtr> instructions;
    std::unordered_map<std::string,std::uint64_t> local_var_map;//For faster access. The second argument is the index of the local variable in the instructions
                                                                //That is it returns the index of the instruction that defines the local variable. 
    public:
    Label(std::string name, std::vector<LabelParamRegisterPtr> parameters, std::vector<InstPtr> instructions);

    std::string get_name() const;

    std::vector<LabelParamRegisterPtr> get_parameters() const;
    std::vector<LocalRegisterPtr> get_local_vars() const;
    std::vector<InstPtr> get_instructions() const;

    std::uint64_t get_parameter_index(std::string name) const;
    std::uint64_t get_local_var_index(std::string name) const;
    LabelParamRegisterPtr get_parameter(std::string name) const;
    LocalRegisterPtr get_local_var(std::string name) const;

    std::string to_string() const;
};

using LabelPtr = std::shared_ptr<Label>;

class FunctionSignature{
    std::string name;
    std::vector<FuncParamRegisterPtr> parameters; //In proper order
    std::unordered_map<std::string,std::uint64_t> parameter_map;//For faster access. The second argument is the index of the parameter
    IR::TypeExprPtr return_type;
    bool has_varargs;
    bool has_body;
};

using FunctionSignaturePtr = std::shared_ptr<FunctionSignature>;

class Function{
    FunctionSignaturePtr signature;

    std::vector<LabelPtr> labels;
    std::unordered_map<std::string,std::uint64_t> label_map;//For faster access. The second argument is the index of the label in the labels vector
    std::unordered_map<std::string,std::uint64_t> scope_var_map;//For faster access. The second argument is the index of the label in the labels vector that defines it
    std::vector<IR::ScopePtr> scope_def;//I am not defining this Scope class again because I dont think there is much to add here
    std::unordered_map<std::string,std::uint64_t> scope_map;//For faster access. The second argument is the index of the scope in the scope_def vector
};

using FunctionPtr = std::shared_ptr<Function>;

class Program{
    std::vector<FunctionSignaturePtr> function_signatures;//Even the ones that have a body
    std::unordered_map<std::string,std::uint64_t> function_signature_map;//For faster access. The second argument is the index of the function signature in the function_signatures vector
    std::vector<FunctionPtr> functions;
    std::unordered_map<std::string,std::uint64_t> function_map;//For faster access. The second argument is the index of the function in the functions vector
    std::vector<IR::GlobalItemPtr> global_items;
    std::unordered_map<std::string,std::uint64_t> global_item_map;//For faster access.
};
}
}