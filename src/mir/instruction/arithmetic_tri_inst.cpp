#include "mir/instruction/arithmetic_tri_inst.hpp"
#include "ast/ast.hpp"
#include <memory>

namespace LIRA {
namespace MIR {
ArithmeticTrinaryInst::ArithmeticTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, 
                                             IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, IR::LiteralExprPtr arg3,
                                             std::optional<FastMathAttr> fast_math_attr)
                                             :Inst(instruction_stmt, destination,fast_math_attr){
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->arg3 = arg3;
}
IR::TypeExprPtr ArithmeticTrinaryInst::get_operand_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr ArithmeticTrinaryInst::get_arg1() const{
    return this->arg1;
}
IR::LiteralExprPtr ArithmeticTrinaryInst::get_arg2() const{
    return this->arg2;
}
IR::LiteralExprPtr ArithmeticTrinaryInst::get_arg3() const{
    return this->arg3;
}
InstType ArithmeticTrinaryInst::get_inst_type() const{
    return InstType::ArithmeticTrinaryInst;
}


// ---------------------------- Integer Trinary operations ---------------------------
IntArithmeticTrinaryInst::IntArithmeticTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                                                     IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating)
                                                     :ArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3,std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
}
std::string IntArithmeticTrinaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->arg1->to_string() + ", " + this->arg2->to_string() + ", " + this->arg3->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    if(this->saturating){
        res += " #[saturating]";
    }
    return res;
}
bool IntArithmeticTrinaryInst::is_nuw() const{
    return this->nuw;
}
bool IntArithmeticTrinaryInst::is_nsw() const{
    return this->nsw;
}
bool IntArithmeticTrinaryInst::is_unsigned() const{
    return this->unsigned_;
}
bool IntArithmeticTrinaryInst::is_saturating() const{
    return this->saturating;
}
std::shared_ptr<IR::IntTypeExpr> IntArithmeticTrinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
}
std::size_t IntArithmeticTrinaryInst::get_bitwidth() const{
    auto type = this->get_casted_operand_type();
    return type->get_bits();
}
InstOperandTypeVarient IntArithmeticTrinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::Int;
}


IntFMAInst::IntFMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                        IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating)
                        :IntArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, nuw, nsw, unsigned_, saturating){}
IntArithmeticTrinaryInst::OpType IntFMAInst::get_op_type() const{
    return OpType::FMA;
}
std::string IntFMAInst::to_string() const{
    return this->to_string_helper("int_fma");
}


IntFMSInst::IntFMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                        IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating)
                        :IntArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, nuw, nsw, unsigned_, saturating){}
IntArithmeticTrinaryInst::OpType IntFMSInst::get_op_type() const{
    return OpType::FMS;
}
std::string IntFMSInst::to_string() const{
    return this->to_string_helper("int_fms");
}


IntFNMAInst::IntFNMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                         IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating)
                         :IntArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, nuw, nsw, unsigned_, saturating){}
IntArithmeticTrinaryInst::OpType IntFNMAInst::get_op_type() const{
    return OpType::FNMA;
}
std::string IntFNMAInst::to_string() const{
    return this->to_string_helper("int_fnma");
}


IntFNMSInst::IntFNMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                         IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating)
                         :IntArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, nuw, nsw, unsigned_, saturating){}
IntArithmeticTrinaryInst::OpType IntFNMSInst::get_op_type() const{
    return OpType::FNMS;
}
std::string IntFNMSInst::to_string() const{
    return this->to_string_helper("int_fnms");
}


IntClampInst::IntClampInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                            IR::LiteralExprPtr arg3, bool unsigned_)
                            :IntArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, false, false, unsigned_, false){}
IntArithmeticTrinaryInst::OpType IntClampInst::get_op_type() const{
    return OpType::CLAMP;
}
std::string IntClampInst::to_string() const{
    return this->to_string_helper("int_clamp");
}

// ----------------------------- Vector integer Trinary operations ---------------------------
VecIntArithmeticTrinaryInst::VecIntArithmeticTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                                                     IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating)
                                                     :ArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
}
std::string VecIntArithmeticTrinaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->arg1->to_string() + ", " + this->arg2->to_string() + ", " + this->arg3->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    if(this->saturating){
        res += " #[saturating]";
    }
    return res;
}
bool VecIntArithmeticTrinaryInst::is_nuw() const{
    return this->nuw;
}
bool VecIntArithmeticTrinaryInst::is_nsw() const{
    return this->nsw;
}
bool VecIntArithmeticTrinaryInst::is_unsigned() const{
    return this->unsigned_;
}
bool VecIntArithmeticTrinaryInst::is_saturating() const{
    return this->saturating;
}
std::shared_ptr<IR::SIMDTypeExpr> VecIntArithmeticTrinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::size_t VecIntArithmeticTrinaryInst::get_basetype_bitwidth() const{
    auto type = this->get_casted_operand_type();
    auto basetype = std::dynamic_pointer_cast<IR::IntTypeExpr>(type->get_basetype());
    return basetype->get_bits();
}
std::size_t VecIntArithmeticTrinaryInst::get_num_elements() const{
    auto type = this->get_casted_operand_type();
    return type->get_size();
}
InstOperandTypeVarient VecIntArithmeticTrinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::VecInt;
}


VecIntFMAInst::VecIntFMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                            IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating)
                            :VecIntArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, nuw, nsw, unsigned_, saturating){}
VecIntArithmeticTrinaryInst::OpType VecIntFMAInst::get_op_type() const{
    return OpType::FMA;
}
std::string VecIntFMAInst::to_string() const{
    return this->to_string_helper("vec_int_fma");
}


VecIntFMSInst::VecIntFMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                             IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating)
                             :VecIntArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, nuw, nsw, unsigned_, saturating){}
VecIntArithmeticTrinaryInst::OpType VecIntFMSInst::get_op_type() const{
    return OpType::FMS;
}
std::string VecIntFMSInst::to_string() const{
    return this->to_string_helper("vec_int_fms");
}


VecIntFNMAInst::VecIntFNMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                         IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating)
                         :VecIntArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, nuw, nsw, unsigned_, saturating){}
VecIntArithmeticTrinaryInst::OpType VecIntFNMAInst::get_op_type() const{
    return OpType::FNMA;
}
std::string VecIntFNMAInst::to_string() const{
    return this->to_string_helper("vec_int_fnma");
}


VecIntFNMSInst::VecIntFNMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                         IR::LiteralExprPtr arg3, bool nuw, bool nsw, bool unsigned_, bool saturating)
                         :VecIntArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, nuw, nsw, unsigned_, saturating){}
VecIntArithmeticTrinaryInst::OpType VecIntFNMSInst::get_op_type() const{
    return OpType::FNMS;
}
std::string VecIntFNMSInst::to_string() const{
    return this->to_string_helper("vec_int_fnms");
}


VecIntClampInst::VecIntClampInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                            IR::LiteralExprPtr arg3, bool unsigned_)
                            :VecIntArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, false, false, unsigned_, false){}
VecIntArithmeticTrinaryInst::OpType VecIntClampInst::get_op_type() const{
    return OpType::CLAMP;
}
std::string VecIntClampInst::to_string() const{
    return this->to_string_helper("vec_int_clamp");
}
// ---------------------------- Float Trinary operations ---------------------------
FloatArithmeticTrinaryInst::FloatArithmeticTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                                        IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr,bool ieee754_2019, bool unordered)
                                                        :ArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr){
    this->ieee754_2019 = ieee754_2019;
    this->unordered = unordered;
}
std::string FloatArithmeticTrinaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->arg1->to_string() + ", " + this->arg2->to_string() + ", " + this->arg3->to_string() + ")";
    if(this->get_fast_math_attr().has_value()){
        res += " " + this->get_fast_math_attr()->to_string();
    }
    if(this->ieee754_2019){
        res += " #[ieee754_2019]";
    }
    if(this->unordered){
        res += " #[unordered]";
    }
    return res;
}
bool FloatArithmeticTrinaryInst::is_ieee754_2019() const{
    return this->ieee754_2019;
}
bool FloatArithmeticTrinaryInst::is_unordered() const{
    return this->unordered;
}
std::shared_ptr<IR::FloatTypeExpr> FloatArithmeticTrinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->destination->get_type());
}
std::size_t FloatArithmeticTrinaryInst::get_bitwidth() const{
    auto type = this->get_casted_operand_type();
    return type->get_bits();
}
bool FloatArithmeticTrinaryInst::is_brain_float() const{
    auto type = this->get_casted_operand_type();
    return type->is_brain_float();
}
InstOperandTypeVarient FloatArithmeticTrinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::Float;
}


FloatFMAInst::FloatFMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                  IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr)
                  :FloatArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr,false,false){}
FloatArithmeticTrinaryInst::OpType FloatFMAInst::get_op_type() const{
    return OpType::FMA;
}
std::string FloatFMAInst::to_string() const{
    return this->to_string_helper("float_fma");
}


FloatFMSInst::FloatFMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                  IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr)
                  :FloatArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr,false,false){}
FloatArithmeticTrinaryInst::OpType FloatFMSInst::get_op_type() const{
    return OpType::FMS;
}
std::string FloatFMSInst::to_string() const{
    return this->to_string_helper("float_fms");
}


FloatFNMAInst::FloatFNMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                   IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr)
                   :FloatArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr,false,false){}
FloatArithmeticTrinaryInst::OpType FloatFNMAInst::get_op_type() const{
    return OpType::FNMA;
}
std::string FloatFNMAInst::to_string() const{
    return this->to_string_helper("float_fnma");
}


FloatFNMSInst::FloatFNMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                   IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr)
                   :FloatArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr,false,false){}
FloatArithmeticTrinaryInst::OpType FloatFNMSInst::get_op_type() const{
    return OpType::FNMS;
}
std::string FloatFNMSInst::to_string() const{
    return this->to_string_helper("float_fnms");
}


FloatClampInst::FloatClampInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                    IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                    :FloatArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr, ieee754_2019, unordered){}
FloatArithmeticTrinaryInst::OpType FloatClampInst::get_op_type() const{
    return OpType::CLAMP;
}
std::string FloatClampInst::to_string() const{
    return this->to_string_helper("float_clamp");
}
// ---------------------------- Vector Float Trinary operations ---------------------------
VecFloatArithmeticTrinaryInst::VecFloatArithmeticTrinaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2, 
                                                        IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr,bool ieee754_2019, bool unordered)
                                                        :ArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr){
    this->ieee754_2019 = ieee754_2019;
    this->unordered = unordered;
}
std::string VecFloatArithmeticTrinaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->arg1->to_string() + ", " + this->arg2->to_string() + ", " + this->arg3->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res+= " " + this->fast_math_attr.value().to_string();
    }
    if(this->ieee754_2019){
        res += " #[ieee754_2019]";
    }
    if(this->unordered){
        res += " #[unordered]";
    }
    return res;
}
bool VecFloatArithmeticTrinaryInst::is_ieee754_2019() const{
    return this->ieee754_2019;
}
bool VecFloatArithmeticTrinaryInst::is_unordered() const{
    return this->unordered;
}
std::shared_ptr<IR::SIMDTypeExpr> VecFloatArithmeticTrinaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatArithmeticTrinaryInst::get_basetype() const{
    auto type = this->get_casted_operand_type();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(type->get_basetype());
}
std::size_t VecFloatArithmeticTrinaryInst::get_num_elements() const{
    auto type = this->get_casted_operand_type();
    return type->get_size();
}
InstOperandTypeVarient VecFloatArithmeticTrinaryInst::get_operand_type_varient() const{
    return InstOperandTypeVarient::VecFloat;
}


VecFloatFMAInst::VecFloatFMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                  IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr)
                  :VecFloatArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr,false,false){}
VecFloatArithmeticTrinaryInst::OpType VecFloatFMAInst::get_op_type() const{
    return OpType::FMA;
}
std::string VecFloatFMAInst::to_string() const{
    return this->to_string_helper("vec_float_fma");
}


VecFloatFMSInst::VecFloatFMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                  IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr)
                  :VecFloatArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr,false,false){}
VecFloatArithmeticTrinaryInst::OpType VecFloatFMSInst::get_op_type() const{
    return OpType::FMS;
}
std::string VecFloatFMSInst::to_string() const{
    return this->to_string_helper("vec_float_fms");
}


VecFloatFNMAInst::VecFloatFNMAInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                   IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr)
                   :VecFloatArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr,false,false){}
VecFloatArithmeticTrinaryInst::OpType VecFloatFNMAInst::get_op_type() const{
    return OpType::FNMA;
}
std::string VecFloatFNMAInst::to_string() const{
    return this->to_string_helper("vec_float_fnma");
}


VecFloatFNMSInst::VecFloatFNMSInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                   IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr)
                   :VecFloatArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr,false,false){}
VecFloatArithmeticTrinaryInst::OpType VecFloatFNMSInst::get_op_type() const{
    return OpType::FNMS;
}
std::string VecFloatFNMSInst::to_string() const{
    return this->to_string_helper("vec_float_fnms");
}


VecFloatClampInst::VecFloatClampInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg1, IR::LiteralExprPtr arg2,
                    IR::LiteralExprPtr arg3, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                    :VecFloatArithmeticTrinaryInst(instruction_stmt, destination, arg1, arg2, arg3, fast_math_attr, ieee754_2019, unordered){}
VecFloatArithmeticTrinaryInst::OpType VecFloatClampInst::get_op_type() const{
    return OpType::CLAMP;
}
std::string VecFloatClampInst::to_string() const{
    return this->to_string_helper("vec_float_clamp");
}
}
}