#pragma once
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
    std::vector<LocalDestRegisterPtr> get_local_vars() const;
    std::vector<InstPtr> get_instructions() const;

    std::uint64_t get_parameter_index(std::string name) const;
    std::uint64_t get_local_var_index(std::string name) const;
    LabelParamRegisterPtr get_parameter(std::string name) const;
    LocalDestRegisterPtr get_local_var(std::string name) const;

    std::string to_string() const;
};

using LabelPtr = std::shared_ptr<Label>;
}
}