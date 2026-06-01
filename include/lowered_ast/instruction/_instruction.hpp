#pragma once
#include "ast/ast.hpp"
namespace LIRA {
namespace MIR{
enum class InstType:std::int16_t{
    //TODO:Decide in future how I want to create the instruction. Do I have BinaryInst,... or just FloatADD,IntAdd.....
};
class DestinationVar{};//TODO:Implement it to store the attribute in a structured manner(Like the token name and the attributes in a strutured way)
// I am going to define the instruction set of LIRA. A lot of the instructions are lot lowered. Like .add is lowered to .fadd, .iadd, .vadd and so on. It is done
// to make my life easier in the codegen phase. Although it is possible to merge a few of these instructions but I want to keep them separate because I think it will be better
// Although I admit I may be wrong and it may be better to merge some of these instructions but I will keep them separate for now 
class Inst {
    public:
    virtual ~Inst() = default;

    virtual std::optional<std::pair<DestinationVar,IR::TypeExprPtr>> get_destination() const;//For faster access if needed
    virtual InstType get_inst_type() const = 0;
    virtual IR::InstructionStmtPtr get_instruction_stmt() const = 0;//For error reporting
    virtual std::string to_string() const = 0;
    virtual IR::DebugInfoPtr get_debug_info() const final;//Return get_instruction_stmt()->get_value()->get_debug_info() if get_value() is not empty else nullptr.
};

using InstPtr = std::shared_ptr<Inst>;

struct FastMathAttr {
    bool nnans = false;
    bool ninfs = false;
    bool nsz = false;
    bool arcp = false;
    bool contract = false;
    bool afns = false;
    bool reassoc = false;
};
}
}
