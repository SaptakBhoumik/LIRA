#include "mir/instruction/conv_inst.hpp"

namespace LIRA {
namespace MIR {
ConvInst::ConvInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type,
                   bool nuw, bool nsw, bool nsb, bool unsigned_, bool saturating, std::optional<FastMathAttr> fast_math_attr):
                   Inst(instruction_stmt, destination, fast_math_attr){
    this->value = value;
    this->in_type = in_type;
    this->nuw = nuw;
    this->nsw = nsw;
    this->nsb = nsb;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
}
std::string ConvInst::to_string_helper(std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(" + this->in_type->to_string() + ":" + this->value->to_string() + ")";
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    if(this->nsb){
        res += " #[nsb]";
    }
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    if(this->saturating){
        res += " #[saturating]";
    }
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
std::optional<TypeVariant> ConvInst::get_in_type_variant() const{
    return get_type_variant_from_type(this->in_type);
}
std::optional<TypeVariant> ConvInst::get_out_type_variant() const{
    return get_type_variant_from_type(this->destination->get_type());
}
IR::TypeExprPtr ConvInst::get_in_type() const{
    return this->in_type;
}
IR::TypeExprPtr ConvInst::get_out_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr ConvInst::get_value() const{
    return this->value;
}
bool ConvInst::is_nuw() const{
    return this->nuw;
}
bool ConvInst::is_nsw() const{
    return this->nsw;
}
bool ConvInst::is_nsb() const{
    return this->nsb;
}
bool ConvInst::is_unsigned() const{
    return this->unsigned_;
}
bool ConvInst::is_saturating() const{
    return this->saturating;
}
InstType ConvInst::get_inst_type() const{
    return InstType::ConvInst;
}

// --------------------------- Scalar conversion operations ---------------------------
ScalarConvInst::ScalarConvInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                                bool nuw, bool nsw, bool nsb, bool unsigned_, bool saturating, std::optional<FastMathAttr> fast_math_attr)
                                :ConvInst(instruction_stmt, destination, value, in_type, nuw, nsw, nsb, unsigned_, saturating, fast_math_attr){}

        
IntTruncInst::IntTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                           bool nuw, bool nsw, bool unsigned_, bool saturating)
                           :ScalarConvInst(instruction_stmt, destination, value, in_type, nuw, nsw, false, unsigned_, saturating, std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntTruncInst::get_casted_in_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->in_type);
}
std::shared_ptr<IR::IntTypeExpr> IntTruncInst::get_casted_out_type() const{ 
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
}
std::size_t IntTruncInst::get_in_type_bitwidth() const{
    return this->get_casted_in_type()->get_bits();
}
std::size_t IntTruncInst::get_out_type_bitwidth() const{
    return this->get_casted_out_type()->get_bits();
}
ConvInst::OpType IntTruncInst::get_op_type() const{
    return OpType::TRUNC;
}
std::string IntTruncInst::to_string() const{
    return to_string_helper("int_trunc");
}


FloatTruncInst::FloatTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type,
                               FastMathAttr fast_math_attr)
                               :ScalarConvInst(instruction_stmt, destination, value, in_type, false, false, false, false, false, fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatTruncInst::get_casted_in_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->in_type);
}
std::shared_ptr<IR::FloatTypeExpr> FloatTruncInst::get_casted_out_type() const{ 
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->destination->get_type());
}
bool FloatTruncInst::is_in_bf16() const{
    auto in_type = this->get_casted_in_type();
    return in_type->is_brain_float();
}
bool FloatTruncInst::is_out_bf16() const{
    auto out_type = this->get_casted_out_type();
    return out_type->is_brain_float();
}
std::size_t FloatTruncInst::get_in_type_bitwidth() const{
    return this->get_casted_in_type()->get_bits();
}
std::size_t FloatTruncInst::get_out_type_bitwidth() const{
    return this->get_casted_out_type()->get_bits();
}
ConvInst::OpType FloatTruncInst::get_op_type() const{
    return OpType::TRUNC;
}
std::string FloatTruncInst::to_string() const{
    return to_string_helper("float_trunc");
}


IntExtInst::IntExtInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type,
                       bool nsb, bool unsigned_):
                       ScalarConvInst(instruction_stmt, destination, value, in_type, false, false, nsb, unsigned_, false, std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntExtInst::get_casted_in_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->in_type);
}
std::shared_ptr<IR::IntTypeExpr> IntExtInst::get_casted_out_type() const{ 
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
}
std::size_t IntExtInst::get_in_type_bitwidth() const{
    return this->get_casted_in_type()->get_bits();
}
std::size_t IntExtInst::get_out_type_bitwidth() const{
    return this->get_casted_out_type()->get_bits();
}
ConvInst::OpType IntExtInst::get_op_type() const{
    return OpType::EXT;
}
std::string IntExtInst::to_string() const{
    return to_string_helper("int_ext");
}


FloatExtInst::FloatExtInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, FastMathAttr fast_math_attr)
                            :ScalarConvInst(instruction_stmt, destination, value, in_type, false, false, false, false, false, fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatExtInst::get_casted_in_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->in_type);
}
std::shared_ptr<IR::FloatTypeExpr> FloatExtInst::get_casted_out_type() const{ 
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->destination->get_type());
}
bool FloatExtInst::is_in_bf16() const{
    auto in_type = this->get_casted_in_type();
    return in_type->is_brain_float();
}
bool FloatExtInst::is_out_bf16() const{
    auto out_type = this->get_casted_out_type();
    return out_type->is_brain_float();
}
std::size_t FloatExtInst::get_in_type_bitwidth() const{
    return this->get_casted_in_type()->get_bits();
}
std::size_t FloatExtInst::get_out_type_bitwidth() const{
    return this->get_casted_out_type()->get_bits();
}
ConvInst::OpType FloatExtInst::get_op_type() const{
    return OpType::EXT;
}
std::string FloatExtInst::to_string() const{
    return to_string_helper("float_ext");
}


FloatToIntInst::FloatToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                               bool nsb, bool unsigned_, bool saturating, FastMathAttr fast_math_attr)
                               :ScalarConvInst(instruction_stmt, destination, value, in_type, false, false, nsb, unsigned_, saturating, fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatToIntInst::get_casted_in_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->in_type);
}
std::shared_ptr<IR::IntTypeExpr> FloatToIntInst::get_casted_out_type() const{ 
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
}
bool FloatToIntInst::is_in_bf16() const{
    auto in_type = this->get_casted_in_type();
    return in_type->is_brain_float();
}
std::size_t FloatToIntInst::get_in_type_bitwidth() const{
    return this->get_casted_in_type()->get_bits();
}
std::size_t FloatToIntInst::get_out_type_bitwidth() const{
    return this->get_casted_out_type()->get_bits();
}
ConvInst::OpType FloatToIntInst::get_op_type() const{
    return OpType::FLOAT_TO_INT;
}
std::string FloatToIntInst::to_string() const{
    return to_string_helper("float_to_int");
}


IntToFloatInst::IntToFloatInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                               bool nsb, bool unsigned_, FastMathAttr fast_math_attr)
                               :ScalarConvInst(instruction_stmt, destination, value, in_type, false, false, nsb, unsigned_, false, fast_math_attr){}
std::shared_ptr<IR::IntTypeExpr> IntToFloatInst::get_casted_in_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->in_type);
}
std::shared_ptr<IR::FloatTypeExpr> IntToFloatInst::get_casted_out_type() const{ 
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->destination->get_type());
}
bool IntToFloatInst::is_out_bf16() const{
    auto out_type = this->get_casted_out_type();
    return out_type->is_brain_float();
}
std::size_t IntToFloatInst::get_in_type_bitwidth() const{
    return this->get_casted_in_type()->get_bits();
}
std::size_t IntToFloatInst::get_out_type_bitwidth() const{
    return this->get_casted_out_type()->get_bits();
}
ConvInst::OpType IntToFloatInst::get_op_type() const{
    return OpType::INT_TO_FLOAT;
}
std::string IntToFloatInst::to_string() const{
    return to_string_helper("int_to_float");
}


PtrToIntInst::PtrToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value)
                    :ScalarConvInst(instruction_stmt, destination, value, std::make_shared<IR::PtrTypeExpr>(IR::Token{},std::vector<IR::AttributePtr>{}), false, false, false, false, false, std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> PtrToIntInst::get_casted_out_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
}
std::size_t PtrToIntInst::get_in_type_bitwidth() const{
    return 64;//Because only x86_64
}
std::size_t PtrToIntInst::get_out_type_bitwidth() const{
    return this->get_casted_out_type()->get_bits();
}
ConvInst::OpType PtrToIntInst::get_op_type() const{
    return OpType::PTR_TO_INT;
}
std::string PtrToIntInst::to_string() const{
    return to_string_helper("ptr_to_int");
}


IntToPtrInst::IntToPtrInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type)
                            :ScalarConvInst(instruction_stmt, destination, value, in_type, false, false, false, false, false, std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntToPtrInst::get_casted_in_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->in_type);
}
std::size_t IntToPtrInst::get_in_type_bitwidth() const{
    return this->get_casted_in_type()->get_bits();
}
std::size_t IntToPtrInst::get_out_type_bitwidth() const{
    return 64;//Because only x86_64
}
ConvInst::OpType IntToPtrInst::get_op_type() const{
    return OpType::INT_TO_PTR;
}
std::string IntToPtrInst::to_string() const{
    return to_string_helper("int_to_ptr");
}


BitcastInst::BitcastInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type,std::optional<FastMathAttr> fast_math_attr)
                        :ScalarConvInst(instruction_stmt, destination, value, in_type, false, false, false, false, false, fast_math_attr){}
std::size_t BitcastInst::get_in_type_bitwidth() const{
    return 0;
}
std::size_t BitcastInst::get_out_type_bitwidth() const{
    return 0;
}
ConvInst::OpType BitcastInst::get_op_type() const{
    return OpType::BITCAST;
}
std::string BitcastInst::to_string() const{
    return to_string_helper("bitcast");
}


// --------------------------- Vector conversion operations ---------------------------
VecConvInst::VecConvInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                   bool nuw, bool nsw, bool nsb, bool unsigned_, bool saturating, std::optional<FastMathAttr> fast_math_attr)
                   :ConvInst(instruction_stmt, destination, value, in_type, nuw, nsw, nsb, unsigned_, saturating, fast_math_attr){}
std::shared_ptr<IR::SIMDTypeExpr> VecConvInst::get_casted_in_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->in_type);
}
std::shared_ptr<IR::SIMDTypeExpr> VecConvInst::get_casted_out_type() const{
    return std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
}
std::size_t VecConvInst::get_num_elements() const{
    return this->get_casted_in_type()->get_size();
}


VecIntTruncInst::VecIntTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                    bool nuw, bool nsw, bool unsigned_, bool saturating)
                    :VecConvInst(instruction_stmt, destination, value, in_type, nuw, nsw, false, unsigned_, saturating, std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> VecIntTruncInst::get_casted_in_basetype() const{
    auto simd_type = this->get_casted_in_type();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::shared_ptr<IR::IntTypeExpr> VecIntTruncInst::get_casted_out_basetype() const{
    auto simd_type = this->get_casted_out_type();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t VecIntTruncInst::get_in_basetype_bitwidth() const{
    return this->get_casted_in_basetype()->get_bits();
}
std::size_t VecIntTruncInst::get_out_basetype_bitwidth() const{
    return this->get_casted_out_basetype()->get_bits();
}
ConvInst::OpType VecIntTruncInst::get_op_type() const{
    return OpType::TRUNC;
}
std::string VecIntTruncInst::to_string() const{
    return to_string_helper("vec_int_trunc");
}


VecFloatTruncInst::VecFloatTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, FastMathAttr fast_math_attr)
                    :VecConvInst(instruction_stmt, destination, value, in_type, false, false, false, false, false, fast_math_attr){
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatTruncInst::get_casted_in_basetype() const{
    auto simd_type = this->get_casted_in_type();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(simd_type->get_basetype());
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatTruncInst::get_casted_out_basetype() const{
    auto simd_type = this->get_casted_out_type();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(simd_type->get_basetype());
}
bool VecFloatTruncInst::is_in_basetype_bf16() const{
    auto in_type = this->get_casted_in_basetype();
    return in_type->is_brain_float();
}
bool VecFloatTruncInst::is_out_basetype_bf16() const{
    auto out_type = this->get_casted_out_basetype();
    return out_type->is_brain_float();
}
std::size_t VecFloatTruncInst::get_in_basetype_bitwidth() const{
    return this->get_casted_in_basetype()->get_bits();
}
std::size_t VecFloatTruncInst::get_out_basetype_bitwidth() const{
    return this->get_casted_out_basetype()->get_bits();
}
ConvInst::OpType VecFloatTruncInst::get_op_type() const{
    return OpType::TRUNC;
}
std::string VecFloatTruncInst::to_string() const{
    return to_string_helper("vec_float_trunc");
}


VecIntExtInst::VecIntExtInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                             bool nsb, bool unsigned_)
                             :VecConvInst(instruction_stmt, destination, value, in_type, false, false, nsb, unsigned_, false, std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> VecIntExtInst::get_casted_in_basetype() const{
    auto simd_type = this->get_casted_in_type();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::shared_ptr<IR::IntTypeExpr> VecIntExtInst::get_casted_out_basetype() const{
    auto simd_type = this->get_casted_out_type();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t VecIntExtInst::get_in_basetype_bitwidth() const{
    return this->get_casted_in_basetype()->get_bits();
}
std::size_t VecIntExtInst::get_out_basetype_bitwidth() const{
    return this->get_casted_out_basetype()->get_bits();
}
ConvInst::OpType VecIntExtInst::get_op_type() const{
    return OpType::EXT;
}
std::string VecIntExtInst::to_string() const{
    return to_string_helper("vec_int_ext");
}


VecFloatExtInst::VecFloatExtInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, FastMathAttr fast_math_attr)
                                 :VecConvInst(instruction_stmt, destination, value, in_type, false, false, false, false, false, fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> VecFloatExtInst::get_casted_in_basetype() const{
    auto simd_type = this->get_casted_in_type();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(simd_type->get_basetype());
}
std::shared_ptr<IR::FloatTypeExpr> VecFloatExtInst::get_casted_out_basetype() const{
    auto simd_type = this->get_casted_out_type();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(simd_type->get_basetype());
}
bool VecFloatExtInst::is_in_basetype_bf16() const{
    auto in_type = this->get_casted_in_basetype();
    return in_type->is_brain_float();
}
bool VecFloatExtInst::is_out_basetype_bf16() const{
    auto out_type = this->get_casted_out_basetype();
    return out_type->is_brain_float();
}
std::size_t VecFloatExtInst::get_in_basetype_bitwidth() const{
    return this->get_casted_in_basetype()->get_bits();
}
std::size_t VecFloatExtInst::get_out_basetype_bitwidth() const{
    return this->get_casted_out_basetype()->get_bits();
}
ConvInst::OpType VecFloatExtInst::get_op_type() const{
    return OpType::EXT;
}
std::string VecFloatExtInst::to_string() const{
    return to_string_helper("vec_float_ext");
}


VecFloatToIntInst::VecFloatToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                                 bool nsb, bool unsigned_, bool saturating, FastMathAttr fast_math_attr)
                                 :VecConvInst(instruction_stmt, destination, value, in_type, false, false, nsb, unsigned_, saturating, fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> VecFloatToIntInst::get_casted_in_basetype() const{
    auto simd_type = this->get_casted_in_type();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(simd_type->get_basetype());
}
std::shared_ptr<IR::IntTypeExpr> VecFloatToIntInst::get_casted_out_basetype() const{
    auto simd_type = this->get_casted_out_type();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
bool VecFloatToIntInst::is_in_basetype_bf16() const{
    auto in_type = this->get_casted_in_basetype();
    return in_type->is_brain_float();
}
std::size_t VecFloatToIntInst::get_in_basetype_bitwidth() const{
    return this->get_casted_in_basetype()->get_bits();
}
std::size_t VecFloatToIntInst::get_out_basetype_bitwidth() const{
    return this->get_casted_out_basetype()->get_bits();
}
ConvInst::OpType VecFloatToIntInst::get_op_type() const{
    return OpType::FLOAT_TO_INT;
}
std::string VecFloatToIntInst::to_string() const{
    return to_string_helper("vec_float_to_int");
}


VecIntToFloatInst::VecIntToFloatInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                                     bool nsb, bool unsigned_, FastMathAttr fast_math_attr)
                                     :VecConvInst(instruction_stmt, destination, value, in_type, false, false, nsb, unsigned_, false, fast_math_attr){}
std::shared_ptr<IR::IntTypeExpr> VecIntToFloatInst::get_casted_in_basetype() const{
    auto simd_type = this->get_casted_in_type();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::shared_ptr<IR::FloatTypeExpr> VecIntToFloatInst::get_casted_out_basetype() const{
    auto simd_type = this->get_casted_out_type();
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(simd_type->get_basetype());
}
bool VecIntToFloatInst::is_out_basetype_bf16() const{
    auto out_type = this->get_casted_out_basetype();
    return out_type->is_brain_float();
}
std::size_t VecIntToFloatInst::get_in_basetype_bitwidth() const{
    return this->get_casted_in_basetype()->get_bits();
}
std::size_t VecIntToFloatInst::get_out_basetype_bitwidth() const{
    return this->get_casted_out_basetype()->get_bits();
}
ConvInst::OpType VecIntToFloatInst::get_op_type() const{
    return OpType::INT_TO_FLOAT;
}
std::string VecIntToFloatInst::to_string() const{
    return to_string_helper("vec_int_to_float");
}


VecPtrToIntInst::VecPtrToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type)
                    :VecConvInst(instruction_stmt, destination, value, in_type, false, false, false, false, false, std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> VecPtrToIntInst::get_casted_out_basetype() const{
    auto simd_type = this->get_casted_out_type();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t VecPtrToIntInst::get_in_basetype_bitwidth() const{
    return 64;//Cuz only x86_64. 
}
std::size_t VecPtrToIntInst::get_out_basetype_bitwidth() const{
    return this->get_casted_out_basetype()->get_bits();
}
ConvInst::OpType VecPtrToIntInst::get_op_type() const{
    return OpType::PTR_TO_INT;
}
std::string VecPtrToIntInst::to_string() const{
    return to_string_helper("vec_ptr_to_int");
}


VecIntToPtrInst::VecIntToPtrInst(IR::InstructionStmtPtr instruction_stmt, LocalRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type)
                                :VecConvInst(instruction_stmt, destination, value, in_type, false, false, false, false, false, std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> VecIntToPtrInst::get_casted_in_basetype() const{
    auto simd_type = this->get_casted_in_type();
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t VecIntToPtrInst::get_in_basetype_bitwidth() const{
    return this->get_casted_in_basetype()->get_bits();
}
std::size_t VecIntToPtrInst::get_out_basetype_bitwidth() const{
    return 64;//Cuz only x86_64. 
}
ConvInst::OpType VecIntToPtrInst::get_op_type() const{
    return OpType::INT_TO_PTR;
}
std::string VecIntToPtrInst::to_string() const{
    return to_string_helper("vec_int_to_ptr");
}
}
}