#include "ast/ast.hpp"
#include "mir/instruction.hpp"
#include <iostream>
#include <memory>

namespace LIRA {
namespace MIR {
UnaryInst::UnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                    :Inst(instruction_stmt, destination){
    this->value = value;
    this->fast_math_attr = fast_math_attr;
}
FastMathAttr UnaryInst::get_fast_math_attr() const{
    return this->fast_math_attr;
}
InstOperandTypeVarient UnaryInst::get_type_varient() const{
    return get_type_varient_from_type(this->destination->get_type()).value();
}
IR::TypeExprPtr UnaryInst::get_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr UnaryInst::get_value() const{
    return this->value;
}
InstType UnaryInst::get_inst_type() const{
    return InstType::UnaryInst;
}


// --------------------------- Scalar Unary operations ---------------------------
ScalarUnaryInst::ScalarUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                    :UnaryInst(instruction_stmt, destination, value, fast_math_attr){}

bool ScalarUnaryInst::is_brain_float() const{
    if(this->get_type_varient() != InstOperandTypeVarient::Float){
        return false;
    }
    auto float_type = std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_type());
    return float_type->is_brain_float();
}
std::size_t ScalarUnaryInst::get_type_bitwidth() const{
    if(this->get_type_varient() == InstOperandTypeVarient::Int){
        auto int_type = std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_type());
        return int_type->get_bits();
    }
    else if(this->get_type_varient() == InstOperandTypeVarient::Float){
        auto float_type = std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_type());
        return float_type->get_bits();
    }
    else{
        std::cerr << "Error: Unsupported type varient for getting bit width in ScalarUnaryInst. This should never happen. Please report this to the developers." << std::endl;
        std::exit(1);
    }
}


IntNegInst::IntNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                    :ScalarUnaryInst(instruction_stmt, destination, value, FastMathAttr{}){}
std::shared_ptr<IR::IntTypeExpr> IntNegInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_type());
}
UnaryInst::OpType IntNegInst::get_op_type() const{
    return OpType::NEG;
}
std::string IntNegInst::to_string() const{
    return this->destination->to_string() + " = .int_neg(" + this->value->to_string() + ")";
}


FloatNegInst::FloatNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                    :ScalarUnaryInst(instruction_stmt, destination, value, fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatNegInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_type());
}
UnaryInst::OpType FloatNegInst::get_op_type() const{
    return OpType::NEG;
}
std::string FloatNegInst::to_string() const{
    return this->destination->to_string() + " = .float_neg(" + this->value->to_string() + ") " + this->get_fast_math_attr().to_string();
}


IntNotInst::IntNotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                    :ScalarUnaryInst(instruction_stmt, destination, value, FastMathAttr{}){}
std::shared_ptr<IR::IntTypeExpr> IntNotInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_type());
}
UnaryInst::OpType IntNotInst::get_op_type() const{
    return OpType::NOT;
}
std::string IntNotInst::to_string() const{
    return this->destination->to_string() + " = .int_not(" + this->value->to_string() + ")";
}


LaneWiseUnaryInst::LaneWiseUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                    :UnaryInst(instruction_stmt, destination, value, fast_math_attr){}
std::shared_ptr<IR::SIMDTypeExpr> LaneWiseUnaryInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->get_type());
}
bool LaneWiseUnaryInst::is_brain_float() const{
    auto simd_type = this->get_casted_type();
    if(simd_type->get_basetype()->get_kind() != IR::TypeExprKind::FloatTypeExpr){
        return false;
    }
    auto float_type = std::dynamic_pointer_cast<IR::FloatTypeExpr>(simd_type->get_basetype());
    return float_type->is_brain_float();
}
std::size_t LaneWiseUnaryInst::get_basetype_bitwidth() const{
    auto simd_type = this->get_casted_type();
    if(simd_type->get_basetype()->get_kind() == IR::TypeExprKind::IntTypeExpr){
        auto int_type = std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
        return int_type->get_bits();
    }
    else if(simd_type->get_basetype()->get_kind() == IR::TypeExprKind::FloatTypeExpr){
        auto float_type = std::dynamic_pointer_cast<IR::FloatTypeExpr>(simd_type->get_basetype());
        return float_type->get_bits();
    }
    else{
        std::cerr << "Error: Unsupported base type for getting bit width in LaneWiseUnaryInst. This should never happen. Please report this to the developers." << std::endl;
        std::exit(1);
    }
}
std::size_t LaneWiseUnaryInst::get_num_elements() const{
    auto simd_type = this->get_casted_type();
    return simd_type->get_size();
}


LaneWiseIntNegInst::LaneWiseIntNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                                        :LaneWiseUnaryInst(instruction_stmt, destination, value, FastMathAttr{}){}
std::shared_ptr<IR::IntTypeExpr> LaneWiseIntNegInst::get_casted_basetype() const{
    auto simd_type = this->get_casted_type();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
UnaryInst::OpType LaneWiseIntNegInst::get_op_type() const{
    return OpType::NEG;
}
std::string LaneWiseIntNegInst::to_string() const{
    return this->destination->to_string() + " = .vec_int_neg(" + this->value->to_string() + ")";
}


LaneWiseFloatNegInst::LaneWiseFloatNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                        :LaneWiseUnaryInst(instruction_stmt, destination, value, fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> LaneWiseFloatNegInst::get_casted_basetype() const{
    auto simd_type = this->get_casted_type();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(simd_type->get_basetype());
}
UnaryInst::OpType LaneWiseFloatNegInst::get_op_type() const{
    return OpType::NEG;
}
std::string LaneWiseFloatNegInst::to_string() const{
    return this->destination->to_string() + " = .vec_float_neg(" + this->value->to_string() + ") " + this->get_fast_math_attr().to_string();
}


LaneWiseIntNotInst::LaneWiseIntNotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                                        :LaneWiseUnaryInst(instruction_stmt, destination, value, FastMathAttr{}){}
std::shared_ptr<IR::IntTypeExpr> LaneWiseIntNotInst::get_casted_basetype() const{
    auto simd_type = this->get_casted_type();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
UnaryInst::OpType LaneWiseIntNotInst::get_op_type() const{
    return OpType::NOT;
}
std::string LaneWiseIntNotInst::to_string() const{
    return this->destination->to_string() + " = .vec_int_not(" + this->value->to_string() + ")";
}
}
}