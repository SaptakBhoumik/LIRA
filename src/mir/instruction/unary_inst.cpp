#include "mir/instruction/unary_inst.hpp"

namespace LIRA {
namespace MIR {
UnaryInst::UnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, std::optional<FastMathAttr> fast_math_attr)
                    :Inst(instruction_stmt,destination, fast_math_attr){
    this->value = value;
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

// --------------------------- Int Unary operations ---------------------------
IntUnaryInst::IntUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, bool nuw, bool nsw, bool zero_poison)
                    :UnaryInst(instruction_stmt, destination, value, std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->zero_poison = zero_poison;
}
std::string IntUnaryInst::to_string_helper(std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->value->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    if(this->zero_poison){
        res += " #[zero_poison]";
    }
    return res;
}
bool IntUnaryInst::is_nuw() const{
    return this->nuw;
}
bool IntUnaryInst::is_nsw() const{
    return this->nsw;
}
bool IntUnaryInst::is_zero_poison() const{
    return this->zero_poison;
}
std::shared_ptr<IR::IntTypeExpr> IntUnaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
}
std::size_t IntUnaryInst::get_bitwidth() const{
    return this->get_casted_operand_type()->get_bits();
}
TypeVariant IntUnaryInst::get_type_variant() const{
    return TypeVariant::Int;
}


IntNegInst::IntNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, bool nsw)
                        :IntUnaryInst(instruction_stmt, destination, value, false, nsw, false){}
UnaryInst::OpType IntNegInst::get_op_type() const{
    return OpType::NEG;
}
std::string IntNegInst::to_string() const{
    return this->to_string_helper("int_neg");
}


IntNotInst::IntNotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                        :IntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType IntNotInst::get_op_type() const{
    return OpType::NOT;
}
std::string IntNotInst::to_string() const{
    return this->to_string_helper("int_not");
}

IntAbsInst::IntAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, bool nsw)
                        :IntUnaryInst(instruction_stmt, destination, value, false, nsw, false){}
UnaryInst::OpType IntAbsInst::get_op_type() const{
    return OpType::ABS;
}
std::string IntAbsInst::to_string() const{
    return this->to_string_helper("int_abs");
}


IntPopcountInst::IntPopcountInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                                :IntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType IntPopcountInst::get_op_type() const{
    return OpType::POPCOUNT;
}
std::string IntPopcountInst::to_string() const{
    return this->to_string_helper("int_popcount");
}


IntCLZInst::IntCLZInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, bool zero_poison)
                    :IntUnaryInst(instruction_stmt, destination, value, false, false, zero_poison){}
UnaryInst::OpType IntCLZInst::get_op_type() const{
    return OpType::CLZ;
}
std::string IntCLZInst::to_string() const{
    return this->to_string_helper("int_clz");
}


IntCTZInst::IntCTZInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, bool zero_poison)
                    :IntUnaryInst(instruction_stmt, destination, value, false, false, zero_poison){}
UnaryInst::OpType IntCTZInst::get_op_type() const{
    return OpType::CTZ;
}
std::string IntCTZInst::to_string() const{
    return this->to_string_helper("int_ctz");
}


IntParityInst::IntParityInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                            :IntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType IntParityInst::get_op_type() const{
    return OpType::PARITY;
}
std::string IntParityInst::to_string() const{
    return this->to_string_helper("int_parity");
}


IntBswapInst::IntBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                            :IntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType IntBswapInst::get_op_type() const{
    return OpType::BSWAP;
}
std::string IntBswapInst::to_string() const{
    return this->to_string_helper("int_bswap");
}


IntBitreverseInst::IntBitreverseInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                                    :IntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType IntBitreverseInst::get_op_type() const{
    return OpType::BITREVERSE;
}
std::string IntBitreverseInst::to_string() const{
    return this->to_string_helper("int_bitreverse");
}


IntCLRSBInst::IntCLRSBInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                            :IntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType IntCLRSBInst::get_op_type() const{
    return OpType::CLRSB;
}
std::string IntCLRSBInst::to_string() const{
    return this->to_string_helper("int_clrsb");
}


IntBLSIInst::IntBLSIInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value) 
                            :IntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType IntBLSIInst::get_op_type() const{
    return OpType::BLSI;
}
std::string IntBLSIInst::to_string() const{
    return this->to_string_helper("int_blsi");
}


IntBLSRInst::IntBLSRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value) 
                            :IntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType IntBLSRInst::get_op_type() const{
    return OpType::BLSR;
}
std::string IntBLSRInst::to_string() const{
    return this->to_string_helper("int_blsr");
}


IntBLSMaskInst::IntBLSMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value) 
                            :IntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType IntBLSMaskInst::get_op_type() const{
    return OpType::BLSMASK;
}
std::string IntBLSMaskInst::to_string() const{
    return this->to_string_helper("int_blsmask");
}
// --------------------------- Vector Int Unary operations ---------------------------
VecIntUnaryInst::VecIntUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, bool nuw, bool nsw, bool zero_poison)
                                :UnaryInst(instruction_stmt, destination, value, std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->zero_poison = zero_poison;
}
std::string VecIntUnaryInst::to_string_helper(std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->value->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    if(this->zero_poison){
        res += " #[zero_poison]";
    }
    return res;
}
bool VecIntUnaryInst::is_nuw() const{
    return this->nuw;
}
bool VecIntUnaryInst::is_nsw() const{
    return this->nsw;
}
bool VecIntUnaryInst::is_zero_poison() const{
    return this->zero_poison;
}
std::shared_ptr<IR::SIMDTypeExpr> VecIntUnaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::size_t VecIntUnaryInst::get_basetype_bitwidth() const{
    auto basetype = this->get_casted_operand_type()->get_basetype();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(basetype)->get_bits();
}
std::size_t VecIntUnaryInst::get_num_elements() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVariant VecIntUnaryInst::get_type_variant() const{
    return TypeVariant::VecInt;
}


VecIntNegInst::VecIntNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, bool nsw)
                        :VecIntUnaryInst(instruction_stmt, destination, value, false, nsw, false){}
UnaryInst::OpType VecIntNegInst::get_op_type() const{
    return OpType::NEG;
}
std::string VecIntNegInst::to_string() const{
    return this->to_string_helper("vec_int_neg");
}


VecIntNotInst::VecIntNotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                        :VecIntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType VecIntNotInst::get_op_type() const{
    return OpType::NOT;
}
std::string VecIntNotInst::to_string() const{
    return this->to_string_helper("vec_int_not");
}

VecIntAbsInst::VecIntAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, bool nsw)
                        :VecIntUnaryInst(instruction_stmt, destination, value, false, nsw, false){}
UnaryInst::OpType VecIntAbsInst::get_op_type() const{
    return OpType::ABS;
}
std::string VecIntAbsInst::to_string() const{
    return this->to_string_helper("vec_int_abs");
}


VecIntPopcountInst::VecIntPopcountInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                                :VecIntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType VecIntPopcountInst::get_op_type() const{
    return OpType::POPCOUNT;
}
std::string VecIntPopcountInst::to_string() const{
    return this->to_string_helper("vec_int_popcount");
}


VecIntCLZInst::VecIntCLZInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, bool zero_poison)
                    :VecIntUnaryInst(instruction_stmt, destination, value, false, false, zero_poison){}
UnaryInst::OpType VecIntCLZInst::get_op_type() const{
    return OpType::CLZ;
}
std::string VecIntCLZInst::to_string() const{
    return this->to_string_helper("vec_int_clz");
}


VecIntCTZInst::VecIntCTZInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, bool zero_poison)
                    :VecIntUnaryInst(instruction_stmt, destination, value, false, false, zero_poison){}
UnaryInst::OpType VecIntCTZInst::get_op_type() const{
    return OpType::CTZ;
}
std::string VecIntCTZInst::to_string() const{
    return this->to_string_helper("vec_int_ctz");
}


VecIntParityInst::VecIntParityInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                            :VecIntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType VecIntParityInst::get_op_type() const{
    return OpType::PARITY;
}
std::string VecIntParityInst::to_string() const{
    return this->to_string_helper("vec_int_parity");
}


VecIntBswapInst::VecIntBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                            :VecIntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType VecIntBswapInst::get_op_type() const{
    return OpType::BSWAP;
}
std::string VecIntBswapInst::to_string() const{
    return this->to_string_helper("vec_int_bswap");
}


VecIntBitreverseInst::VecIntBitreverseInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                                    :VecIntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType VecIntBitreverseInst::get_op_type() const{
    return OpType::BITREVERSE;
}
std::string VecIntBitreverseInst::to_string() const{
    return this->to_string_helper("vec_int_bitreverse");
}


VecIntCLRSBInst::VecIntCLRSBInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                            :VecIntUnaryInst(instruction_stmt, destination, value, false, false, false){}
UnaryInst::OpType VecIntCLRSBInst::get_op_type() const{
    return OpType::CLRSB;
}
std::string VecIntCLRSBInst::to_string() const{
    return this->to_string_helper("vec_int_clrsb");
}


// --------------------------- Float Unary operations ---------------------------
FloatUnaryInst::FloatUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr, bool approx)
                    :UnaryInst(instruction_stmt, destination, value, fast_math_attr){
    this->approx = approx;
}
std::string FloatUnaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->value->to_string() + ")";
    if(this->fast_math_attr){
        res += " " + this->fast_math_attr.value().to_string();
    }
    if(this->approx){
        res += " #[approx]";
    }
    return res;
}
bool FloatUnaryInst::is_approx() const{
    return this->approx;
}
std::shared_ptr<IR::FloatTypeExpr> FloatUnaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->destination->get_type());
}
std::size_t FloatUnaryInst::get_bitwidth() const{
    auto float_type = this->get_casted_operand_type();
    return float_type->get_bits();
}
bool FloatUnaryInst::is_brain_float() const{
    auto float_type = this->get_casted_operand_type();
    return float_type->is_brain_float();
}
TypeVariant FloatUnaryInst::get_type_variant() const{
    return TypeVariant::Float;
}


FloatNegInst::FloatNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                        :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType FloatNegInst::get_op_type() const{
    return OpType::NEG;
}
std::string FloatNegInst::to_string() const{
    return this->to_string_helper("float_neg");
}


FloatAbsInst::FloatAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                        :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType FloatAbsInst::get_op_type() const{
    return OpType::ABS;
}
std::string FloatAbsInst::to_string() const{
    return this->to_string_helper("float_abs");
}


FloatCeilInst::FloatCeilInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                             :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType FloatCeilInst::get_op_type() const{
    return OpType::CEIL;
}
std::string FloatCeilInst::to_string() const{
    return this->to_string_helper("float_ceil");
}


FloatFloorInst::FloatFloorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType FloatFloorInst::get_op_type() const{
    return OpType::FLOOR;
}
std::string FloatFloorInst::to_string() const{
    return this->to_string_helper("float_floor");
}


FloatIntegralPartInst::FloatIntegralPartInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                              :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType FloatIntegralPartInst::get_op_type() const{
    return OpType::INTEGRAL_PART;
}
std::string FloatIntegralPartInst::to_string() const{
    return this->to_string_helper("float_integral_part");
}


FloatFractionalPartInst::FloatFractionalPartInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                                  :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType FloatFractionalPartInst::get_op_type() const{
    return OpType::FRACTIONAL_PART;
}
std::string FloatFractionalPartInst::to_string() const{
    return this->to_string_helper("float_fractional_part");
}


FloatRoundNearestInst::FloatRoundNearestInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                            :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType FloatRoundNearestInst::get_op_type() const{
    return OpType::ROUND_NEAREST;
}
std::string FloatRoundNearestInst::to_string() const{
    return this->to_string_helper("float_round_nearest");
}


FloatRoundEvenInst::FloatRoundEvenInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                            :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType FloatRoundEvenInst::get_op_type() const{
    return OpType::ROUND_EVEN;
}
std::string FloatRoundEvenInst::to_string() const{
    return this->to_string_helper("float_round_even");
}


FloatSqrtInst::FloatSqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                             :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType FloatSqrtInst::get_op_type() const{
    return OpType::SQRT;
}
std::string FloatSqrtInst::to_string() const{
    return this->to_string_helper("float_sqrt");
}


FloatReciprocalInst::FloatReciprocalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr, bool approx)
                                        :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr, approx){}
UnaryInst::OpType FloatReciprocalInst::get_op_type() const{
    return OpType::RECIPROCAL;
}
std::string FloatReciprocalInst::to_string() const{
    return this->to_string_helper("float_reciprocal");
}


FloatRsqrtInst::FloatRsqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr, bool approx)
                                :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr, approx){}
UnaryInst::OpType FloatRsqrtInst::get_op_type() const{
    return OpType::RSQRT;
}
std::string FloatRsqrtInst::to_string() const{
    return this->to_string_helper("float_rsqrt");
}


FloatBswapInst::FloatBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                            :FloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType FloatBswapInst::get_op_type() const{
    return OpType::BSWAP;
}
std::string FloatBswapInst::to_string() const{
    return this->to_string_helper("float_bswap");
}


// --------------------------- Vector Float Unary operations ---------------------------
VecFloatUnaryInst::VecFloatUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr, bool approx)
                                    :UnaryInst(instruction_stmt, destination, value, fast_math_attr){
    this->approx = approx;
}
std::string VecFloatUnaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->value->to_string() + ")";
    if(this->fast_math_attr){
        res += " " + this->fast_math_attr.value().to_string();
    }
    if(this->approx){
        res += " #[approx]";
    }
    return res;
}
bool VecFloatUnaryInst::is_approx() const{
    return this->approx;
}
std::shared_ptr<IR::SIMDTypeExpr> VecFloatUnaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatUnaryInst::get_basetype() const{
    auto basetype = this->get_casted_operand_type()->get_basetype();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(basetype);
}
std::size_t VecFloatUnaryInst::get_num_elements() const{
    return this->get_casted_operand_type()->get_size();
}
TypeVariant VecFloatUnaryInst::get_type_variant() const{
    return TypeVariant::VecFloat;
}


VecFloatNegInst::VecFloatNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                        :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType VecFloatNegInst::get_op_type() const{
    return OpType::NEG;
}
std::string VecFloatNegInst::to_string() const{
    return this->to_string_helper("vec_float_neg");
}


VecFloatAbsInst::VecFloatAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                        :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType VecFloatAbsInst::get_op_type() const{
    return OpType::ABS;
}
std::string VecFloatAbsInst::to_string() const{
    return this->to_string_helper("vec_float_abs");
}


VecFloatCeilInst::VecFloatCeilInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                             :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType VecFloatCeilInst::get_op_type() const{
    return OpType::CEIL;
}
std::string VecFloatCeilInst::to_string() const{
    return this->to_string_helper("vec_float_ceil");
}


VecFloatFloorInst::VecFloatFloorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType VecFloatFloorInst::get_op_type() const{
    return OpType::FLOOR;
}
std::string VecFloatFloorInst::to_string() const{
    return this->to_string_helper("vec_float_floor");
}


VecFloatIntegralPartInst::VecFloatIntegralPartInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                              :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType VecFloatIntegralPartInst::get_op_type() const{
    return OpType::INTEGRAL_PART;
}
std::string VecFloatIntegralPartInst::to_string() const{
    return this->to_string_helper("vec_float_integral_part");
}


VecFloatFractionalPartInst::VecFloatFractionalPartInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                                  :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType VecFloatFractionalPartInst::get_op_type() const{
    return OpType::FRACTIONAL_PART;
}
std::string VecFloatFractionalPartInst::to_string() const{
    return this->to_string_helper("vec_float_fractional_part");
}


VecFloatRoundNearestInst::VecFloatRoundNearestInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                            :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType VecFloatRoundNearestInst::get_op_type() const{
    return OpType::ROUND_NEAREST;
}
std::string VecFloatRoundNearestInst::to_string() const{
    return this->to_string_helper("vec_float_round_nearest");
}


VecFloatRoundEvenInst::VecFloatRoundEvenInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                                            :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType VecFloatRoundEvenInst::get_op_type() const{
    return OpType::ROUND_EVEN;
}
std::string VecFloatRoundEvenInst::to_string() const{
    return this->to_string_helper("vec_float_round_even");
}


VecFloatSqrtInst::VecFloatSqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                             :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType VecFloatSqrtInst::get_op_type() const{
    return OpType::SQRT;
}
std::string VecFloatSqrtInst::to_string() const{
    return this->to_string_helper("vec_float_sqrt");
}


VecFloatReciprocalInst::VecFloatReciprocalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr, bool approx)
                                        :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr, approx){}
UnaryInst::OpType VecFloatReciprocalInst::get_op_type() const{
    return OpType::RECIPROCAL;
}
std::string VecFloatReciprocalInst::to_string() const{
    return this->to_string_helper("vec_float_reciprocal");
}


VecFloatRsqrtInst::VecFloatRsqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr, bool approx)
                                :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr, approx){}
UnaryInst::OpType VecFloatRsqrtInst::get_op_type() const{
    return OpType::RSQRT;
}
std::string VecFloatRsqrtInst::to_string() const{
    return this->to_string_helper("vec_float_rsqrt");
}


VecFloatBswapInst::VecFloatBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                            :VecFloatUnaryInst(instruction_stmt, destination, value, fast_math_attr,false){}
UnaryInst::OpType VecFloatBswapInst::get_op_type() const{
    return OpType::BSWAP;
}
std::string VecFloatBswapInst::to_string() const{
    return this->to_string_helper("vec_float_bswap");
}
}
}