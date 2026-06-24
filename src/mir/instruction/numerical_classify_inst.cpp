#include "mir/instruction/numerical_classify_inst.hpp"

namespace LIRA {
namespace MIR {
NumericalClassifyInst::NumericalClassifyInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                             IR::TypeExprPtr value_type, std::optional<FastMathAttr> fast_math_attr)
                                            :Inst(instruction_stmt, destination, fast_math_attr){
    this->value = value;
    this->value_type = value_type;
}
IR::TypeExprPtr NumericalClassifyInst::get_value_type() const{
    return this->value_type;
}
IR::LiteralExprPtr NumericalClassifyInst::get_value() const{
    return this->value;
}
InstType NumericalClassifyInst::get_inst_type() const{
    return InstType::NumericalClassifyInst;
}


// --------------------------- Float Classification operations ---------------------------
FloatClassifyInst::FloatClassifyInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                     FastMathAttr fast_math_attr):NumericalClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
std::string FloatClassifyInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->value_type->to_string() + ":" + this->value->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res+= " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
std::shared_ptr<IR::FloatTypeExpr> FloatClassifyInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->destination->get_type());
}
std::size_t FloatClassifyInst::get_bitwidth() const{
    auto float_type = this->get_casted_operand_type();
    return float_type->get_bits();
}
bool FloatClassifyInst::is_brain_float() const{
    auto float_type = this->get_casted_operand_type();
    return float_type->is_brain_float();
}
TypeVarient FloatClassifyInst::get_type_varient() const{
    return TypeVarient::Float;
}


FloatIsNanInst::FloatIsNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                FastMathAttr fast_math_attr):FloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType FloatIsNanInst::get_op_type() const{
    return OpType::ISNAN;
}
std::string FloatIsNanInst::to_string() const{
    return this->to_string_helper("float_isnan");
}


FloatIsInfInst::FloatIsInfInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                FastMathAttr fast_math_attr):FloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType FloatIsInfInst::get_op_type() const{
    return OpType::ISINF;
}
std::string FloatIsInfInst::to_string() const{
    return this->to_string_helper("float_isinf");
}


FloatIsFiniteInst::FloatIsFiniteInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                     FastMathAttr fast_math_attr):FloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType FloatIsFiniteInst::get_op_type() const{
    return OpType::ISFINITE;
}
std::string FloatIsFiniteInst::to_string() const{
    return this->to_string_helper("float_isfinite");
}


FloatIsNormalInst::FloatIsNormalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                     FastMathAttr fast_math_attr):FloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType FloatIsNormalInst::get_op_type() const{
    return OpType::ISNORMAL;
}
std::string FloatIsNormalInst::to_string() const{
    return this->to_string_helper("float_isnormal");
}


FloatIsSubnormalInst::FloatIsSubnormalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                            FastMathAttr fast_math_attr):FloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType FloatIsSubnormalInst::get_op_type() const{
    return OpType::ISSUBNORMAL;
}
std::string FloatIsSubnormalInst::to_string() const{
    return this->to_string_helper("float_issubnormal");
}


FloatIsZeroInst::FloatIsZeroInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                FastMathAttr fast_math_attr):FloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType FloatIsZeroInst::get_op_type() const{
    return OpType::ISZERO;
}
std::string FloatIsZeroInst::to_string() const{
    return this->to_string_helper("float_iszero");
}


FloatIsNegativeInst::FloatIsNegativeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                            FastMathAttr fast_math_attr):FloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType FloatIsNegativeInst::get_op_type() const{
    return OpType::ISNEGATIVE;
}
std::string FloatIsNegativeInst::to_string() const{
    return this->to_string_helper("float_isnegative");
}


FloatIsPositiveInst::FloatIsPositiveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                         FastMathAttr fast_math_attr):FloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType FloatIsPositiveInst::get_op_type() const{
    return OpType::ISPOSITIVE;
}
std::string FloatIsPositiveInst::to_string() const{
    return this->to_string_helper("float_ispositive");
}


//--------------------------- Vector Float Classification operations ---------------------------
VecFloatClassifyInst::VecFloatClassifyInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                           FastMathAttr fast_math_attr):NumericalClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
std::string VecFloatClassifyInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->value_type->to_string() + ":" + this->value->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res+= " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
std::shared_ptr<IR::SIMDTypeExpr> VecFloatClassifyInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatClassifyInst::get_basetype() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_casted_operand_type());
}
std::size_t VecFloatClassifyInst::get_num_elements() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVarient VecFloatClassifyInst::get_type_varient() const{
    return TypeVarient::VecFloat;
}


VecFloatIsNanInst::VecFloatIsNanInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                FastMathAttr fast_math_attr):VecFloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType VecFloatIsNanInst::get_op_type() const{
    return OpType::ISNAN;
}
std::string VecFloatIsNanInst::to_string() const{
    return this->to_string_helper("vec_float_isnan");
}


VecFloatIsInfInst::VecFloatIsInfInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                FastMathAttr fast_math_attr):VecFloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType VecFloatIsInfInst::get_op_type() const{
    return OpType::ISINF;
}
std::string VecFloatIsInfInst::to_string() const{
    return this->to_string_helper("vec_float_isinf");
}


VecFloatIsFiniteInst::VecFloatIsFiniteInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                     FastMathAttr fast_math_attr):VecFloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType VecFloatIsFiniteInst::get_op_type() const{
    return OpType::ISFINITE;
}
std::string VecFloatIsFiniteInst::to_string() const{
    return this->to_string_helper("vec_float_isfinite");
}


VecFloatIsNormalInst::VecFloatIsNormalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                     FastMathAttr fast_math_attr):VecFloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType VecFloatIsNormalInst::get_op_type() const{
    return OpType::ISNORMAL;
}
std::string VecFloatIsNormalInst::to_string() const{
    return this->to_string_helper("vec_float_isnormal");
}


VecFloatIsSubnormalInst::VecFloatIsSubnormalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                            FastMathAttr fast_math_attr):VecFloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType VecFloatIsSubnormalInst::get_op_type() const{
    return OpType::ISSUBNORMAL;
}
std::string VecFloatIsSubnormalInst::to_string() const{
    return this->to_string_helper("vec_float_issubnormal");
}


VecFloatIsZeroInst::VecFloatIsZeroInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                FastMathAttr fast_math_attr):VecFloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType VecFloatIsZeroInst::get_op_type() const{
    return OpType::ISZERO;
}
std::string VecFloatIsZeroInst::to_string() const{
    return this->to_string_helper("vec_float_iszero");
}


VecFloatIsNegativeInst::VecFloatIsNegativeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                            FastMathAttr fast_math_attr):VecFloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType VecFloatIsNegativeInst::get_op_type() const{
    return OpType::ISNEGATIVE;
}
std::string VecFloatIsNegativeInst::to_string() const{
    return this->to_string_helper("vec_float_isnegative");
}


VecFloatIsPositiveInst::VecFloatIsPositiveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr value_type,
                                         FastMathAttr fast_math_attr):VecFloatClassifyInst(instruction_stmt, destination, value, value_type, fast_math_attr){}
NumericalClassifyInst::OpType VecFloatIsPositiveInst::get_op_type() const{
    return OpType::ISPOSITIVE;
}
std::string VecFloatIsPositiveInst::to_string() const{
    return this->to_string_helper("vec_float_ispositive");
}
}
}