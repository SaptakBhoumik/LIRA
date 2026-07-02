#include "mir/instruction/simd_inst.hpp"
#include "ast/ast.hpp"
#include "mir/instruction/_instruction.hpp"
#include <memory>
#include <string>

namespace LIRA {
namespace MIR {
//--------------------------------- Uncategorized SIMD Instructions ---------------------------------
ShuffleVectorInst::ShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                                   std::size_t vec1_elm_count, std::size_t vec2_elm_count, std::optional<FastMathAttr> fast_math_attr)
                                   :Inst(instruction_stmt,destination,fast_math_attr){
    this->vector1 = vector1;
    this->vector2 = vector2;
    this->mask = mask;
    this->vec1_elm_count = vec1_elm_count;
    this->vec2_elm_count = vec2_elm_count;
}
std::string ShuffleVectorInst::to_string_helper(const std::string op_name) const{
    std::string vec1_type = "<" + get_basetype()->to_string() + "," + std::to_string(this->vec1_elm_count) + ">:";
    std::string vec2_type = "<" + get_basetype()->to_string() + "," + std::to_string(this->vec2_elm_count) + ">:";
    std::string mask_type = "<i64," + std::to_string(this->get_mask_elm_count()) + ">:";
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + vec1_type + this->vector1->to_string() + ", " 
                                                                                       + vec2_type + this->vector2->to_string() + ", " 
                                                                                       + mask_type + this->mask->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr ShuffleVectorInst::get_vector1() const{
    return this->vector1;
}
IR::LiteralExprPtr ShuffleVectorInst::get_vector2() const{
    return this->vector2;
}
IR::LiteralExprPtr ShuffleVectorInst::get_mask() const{
    return this->mask;
}
IR::TypeExprPtr ShuffleVectorInst::get_basetype() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::size_t ShuffleVectorInst::get_vec1_elm_count() const{
    return this->vec1_elm_count;
}
std::size_t ShuffleVectorInst::get_vec2_elm_count() const{
    return this->vec2_elm_count;
}
std::size_t ShuffleVectorInst::get_mask_elm_count() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType ShuffleVectorInst::get_inst_type() const{
    return InstType::ShuffleVectorInst;
}


IntShuffleVectorInst::IntShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                                         std::size_t vec1_elm_count, std::size_t vec2_elm_count)
                                         :ShuffleVectorInst(instruction_stmt,destination,vector1,vector2,mask,vec1_elm_count,vec2_elm_count,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntShuffleVectorInst::get_casted_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_basetype());
}
std::size_t IntShuffleVectorInst::get_basetype_bitwidth() const{
    return this->get_casted_basetype()->get_bits();
}
TypeVariant IntShuffleVectorInst::get_basetype_variant() const{
    return TypeVariant::Int;
}
std::string IntShuffleVectorInst::to_string() const{
    return this->to_string_helper("int_shuffle_vector");
}


PtrShuffleVectorInst::PtrShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                                         std::size_t vec1_elm_count, std::size_t vec2_elm_count)
                                         :ShuffleVectorInst(instruction_stmt,destination,vector1,vector2,mask,vec1_elm_count,vec2_elm_count,std::nullopt){}
std::size_t PtrShuffleVectorInst::get_basetype_bitwidth() const{
    return 64;
}
TypeVariant PtrShuffleVectorInst::get_basetype_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrShuffleVectorInst::to_string() const{
    return this->to_string_helper("ptr_shuffle_vector");
}


FloatShuffleVectorInst::FloatShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                                             std::size_t vec1_elm_count, std::size_t vec2_elm_count, FastMathAttr fast_math_attr)
                                             :ShuffleVectorInst(instruction_stmt,destination,vector1,vector2,mask,vec1_elm_count,vec2_elm_count,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatShuffleVectorInst::get_casted_basetype() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_basetype());
}
std::size_t FloatShuffleVectorInst::get_basetype_bitwidth() const{
    return this->get_casted_basetype()->get_bits();
}
bool FloatShuffleVectorInst::is_basetype_brain_float() const{
    return this->get_casted_basetype()->is_brain_float();
}
TypeVariant FloatShuffleVectorInst::get_basetype_variant() const{
    return TypeVariant::Float;
}
std::string FloatShuffleVectorInst::to_string() const{
    return this->to_string_helper("float_shuffle_vector");
}


TernLogInst::TernLogInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr a, IR::LiteralExprPtr b, IR::LiteralExprPtr c, 
                         IR::LiteralExprPtr imm):Inst(instruction_stmt, destination, std::nullopt){
    this->a = a;
    this->b = b;
    this->c = c;
    this->imm = imm;
}
IR::LiteralExprPtr TernLogInst::get_a() const{
    return this->a;
}
IR::LiteralExprPtr TernLogInst::get_b() const{
    return this->b;
}
IR::LiteralExprPtr TernLogInst::get_c() const{
    return this->c;
}
IR::LiteralExprPtr TernLogInst::get_imm() const{
    return this->imm;
}
std::size_t TernLogInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType TernLogInst::get_inst_type() const{
    return InstType::TernLogInst;
}
std::string TernLogInst::to_string() const{
    std::string vec_type = this->destination->get_type()->to_string() + ":";
    std::string str = "let " + this->destination->to_string() + " = .tern_log(" + vec_type + this->a->to_string() + ", " 
                                                                                   + this->b->to_string() + ", " 
                                                                                   + this->c->to_string() + ", i8:"
                                                                                   + this->imm->to_string() + ")";
    return str;
}


SplatInst::SplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, std::optional<FastMathAttr> fast_math_attr)
                     :Inst(instruction_stmt,destination,fast_math_attr){
    this->value = value;
}
std::string SplatInst::to_string_helper(const std::string op_name) const{
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + this->get_element_type()->to_string() + ":" + this->value->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr SplatInst::get_value() const{
    return this->value;
}
IR::TypeExprPtr SplatInst::get_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::size_t SplatInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType SplatInst::get_inst_type() const{
    return InstType::SplatInst;
}

IntSplatInst::IntSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                     :SplatInst(instruction_stmt,destination,value,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntSplatInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntSplatInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntSplatInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntSplatInst::to_string() const{
    return this->to_string_helper("int_splat");
}


PtrSplatInst::PtrSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                     :SplatInst(instruction_stmt,destination,value,std::nullopt){}
std::size_t PtrSplatInst::get_element_bitwidth() const{
    return 64;
}
TypeVariant PtrSplatInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrSplatInst::to_string() const{
    return this->to_string_helper("ptr_splat");
}


FloatSplatInst::FloatSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                     :SplatInst(instruction_stmt,destination,value,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatSplatInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatSplatInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatSplatInst::is_brain_float() const{
    return this->get_casted_element_type()->is_brain_float();
}
TypeVariant FloatSplatInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatSplatInst::to_string() const{
    return this->to_string_helper("float_splat");
}


StepVectorInst::StepVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr start, IR::LiteralExprPtr step, 
                               std::optional<FastMathAttr> fast_math_attr)
                               :Inst(instruction_stmt,destination,fast_math_attr){
    this->start = start;
    this->step = step;
}
std::string StepVectorInst::to_string_helper(const std::string op_name) const{
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + this->get_element_type()->to_string() + ":" + this->start->to_string() + ", " 
                                                                                       + this->get_element_type()->to_string() + ":" + this->step->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr StepVectorInst::get_start() const{
    return this->start;
}
IR::LiteralExprPtr StepVectorInst::get_step() const{
    return this->step;
}
IR::TypeExprPtr StepVectorInst::get_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::size_t StepVectorInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType StepVectorInst::get_inst_type() const{
    return InstType::StepVectorInst;
}


IntStepVectorInst::IntStepVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr start, IR::LiteralExprPtr step)
                         :StepVectorInst(instruction_stmt,destination,start,step,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntStepVectorInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntStepVectorInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntStepVectorInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntStepVectorInst::to_string() const{
    return this->to_string_helper("int_step_vector");
}


FloatStepVectorInst::FloatStepVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr start, IR::LiteralExprPtr step, 
                             FastMathAttr fast_math_attr)
                             :StepVectorInst(instruction_stmt,destination,start,step,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatStepVectorInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatStepVectorInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatStepVectorInst::is_brain_float() const{
    return this->get_casted_element_type()->is_brain_float();
}
TypeVariant FloatStepVectorInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatStepVectorInst::to_string() const{
    return this->to_string_helper("float_step_vector");
}


InsertSubVectorInst::InsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size, std::optional<FastMathAttr> fast_math_attr)
                                         :Inst(instruction_stmt,destination,fast_math_attr){
    this->vector = vector;
    this->subvector = subvector;
    this->index = index;
    this->subvector_size = subvector_size;
}
std::string InsertSubVectorInst::to_string_helper(const std::string op_name) const{
    std::string vec_type = this->destination->get_type()->to_string() + ":";
    std::string subvec_type = "<" + this->get_element_type()->to_string() + "," + std::to_string(this->subvector_size) + ">:";
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + this->vector->to_string() + ", " 
                                                                                       + this->subvector->to_string() + ", i64" 
                                                                                       + this->index->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr InsertSubVectorInst::get_vector() const{
    return this->vector;
}
IR::LiteralExprPtr InsertSubVectorInst::get_subvector() const{
    return this->subvector;
}
IR::LiteralExprPtr InsertSubVectorInst::get_index() const{
    return this->index;
}
IR::TypeExprPtr InsertSubVectorInst::get_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::size_t InsertSubVectorInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
std::size_t InsertSubVectorInst::get_subvector_size() const{
    return this->subvector_size;
}
InstType InsertSubVectorInst::get_inst_type() const{
    return InstType::InsertSubVectorInst;
}


IntInsertSubVectorInst::IntInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size)
                                         :InsertSubVectorInst(instruction_stmt,destination,vector,subvector,index,subvector_size,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntInsertSubVectorInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntInsertSubVectorInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntInsertSubVectorInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntInsertSubVectorInst::to_string() const{
    return this->to_string_helper("int_insert_subvector");
}


PtrInsertSubVectorInst::PtrInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size)
                                         :InsertSubVectorInst(instruction_stmt,destination,vector,subvector,index,subvector_size,std::nullopt){}
std::size_t PtrInsertSubVectorInst::get_element_bitwidth() const{
    return 64;
}
TypeVariant PtrInsertSubVectorInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrInsertSubVectorInst::to_string() const{
    return this->to_string_helper("ptr_insert_subvector");
}

FloatInsertSubVectorInst::FloatInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size, FastMathAttr fast_math_attr)
                                         :InsertSubVectorInst(instruction_stmt,destination,vector,subvector,index,subvector_size,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatInsertSubVectorInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatInsertSubVectorInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatInsertSubVectorInst::is_brain_float() const{
    return this->get_casted_element_type()->is_brain_float();
}
TypeVariant FloatInsertSubVectorInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatInsertSubVectorInst::to_string() const{
    return this->to_string_helper("float_insert_subvector");
}


ExtractSubVectorInst::ExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr index, std::size_t vector_size, std::optional<FastMathAttr> fast_math_attr)
                                         :Inst(instruction_stmt,destination,fast_math_attr){
    this->vector = vector;
    this->index = index;
    this->vector_size = vector_size;
}
std::string ExtractSubVectorInst::to_string_helper(const std::string op_name) const{
    std::string vec_type = "<" + this->get_element_type()->to_string() + "," + std::to_string(this->vector_size) + ">:";
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + vec_type + this->vector->to_string() + ", i64:" 
                                                                                       + this->index->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr ExtractSubVectorInst::get_vector() const{
    return this->vector;
}
IR::LiteralExprPtr ExtractSubVectorInst::get_index() const{
    return this->index;
}
std::size_t ExtractSubVectorInst::get_vector_size() const{
    return this->vector_size;
}
IR::TypeExprPtr ExtractSubVectorInst::get_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::size_t ExtractSubVectorInst::get_subvector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType ExtractSubVectorInst::get_inst_type() const{
    return InstType::ExtractSubVectorInst;
}


IntExtractSubVectorInst::IntExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr index, std::size_t vector_size)
                                         :ExtractSubVectorInst(instruction_stmt,destination,vector,index,vector_size,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntExtractSubVectorInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntExtractSubVectorInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntExtractSubVectorInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntExtractSubVectorInst::to_string() const{
    return this->to_string_helper("int_extract_subvector");
}


PtrExtractSubVectorInst::PtrExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr index, std::size_t vector_size)
                                         :ExtractSubVectorInst(instruction_stmt,destination,vector,index,vector_size,std::nullopt){}
std::size_t PtrExtractSubVectorInst::get_element_bitwidth() const{
    return 64;
}
TypeVariant PtrExtractSubVectorInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrExtractSubVectorInst::to_string() const{
    return this->to_string_helper("ptr_extract_subvector");
}


FloatExtractSubVectorInst::FloatExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr index, std::size_t vector_size, FastMathAttr fast_math_attr)
                                         :ExtractSubVectorInst(instruction_stmt,destination,vector,index,vector_size,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatExtractSubVectorInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatExtractSubVectorInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatExtractSubVectorInst::is_brain_float() const{
    return this->get_casted_element_type()->is_brain_float();
}
TypeVariant FloatExtractSubVectorInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatExtractSubVectorInst::to_string() const{
    return this->to_string_helper("float_extract_subvector");
}


ActiveLaneMaskInst::ActiveLaneMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr base, IR::LiteralExprPtr count, 
                                        IR::TypeExprPtr type, bool unsigned_):Inst(instruction_stmt,destination,std::nullopt){
    this->base = base;
    this->count = count;
    this->type = type;
    this->unsigned_ = unsigned_;
}
IR::LiteralExprPtr ActiveLaneMaskInst::get_base() const{
    return this->base;
}
IR::LiteralExprPtr ActiveLaneMaskInst::get_count() const{
    return this->count;
}
std::shared_ptr<IR::IntTypeExpr> ActiveLaneMaskInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->type);
}
std::size_t ActiveLaneMaskInst::get_type_bitwidth() const{
    return this->get_casted_type()->get_bits();
}
std::size_t ActiveLaneMaskInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size(); 
}
bool ActiveLaneMaskInst::is_unsigned() const{
    return this->unsigned_;
}
InstType ActiveLaneMaskInst::get_inst_type() const{
    return InstType::ActiveLaneMaskInst;
}
std::string ActiveLaneMaskInst::to_string() const{
    std::string type_str = this->type->to_string() + ":";
    std::string str = "let " + this->destination->to_string() + " = .active_lane_mask(" + type_str + this->base->to_string() + ", "
                                                                                             + type_str + this->count->to_string() + ")";
    if(this->unsigned_){
        str += " #[unsigned]";
    }
    return str;
}


AddSubInst::AddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                       std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt,destination,fast_math_attr){
    this->lhs = lhs;
    this->rhs = rhs;  
}
IR::LiteralExprPtr AddSubInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr AddSubInst::get_rhs() const{
    return this->rhs;
}
IR::TypeExprPtr AddSubInst::get_element_type() const{
    return this->destination->get_type();
}
size_t AddSubInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType AddSubInst::get_inst_type() const{
    return InstType::AddSubInst;
}


IntAddSubInst::IntAddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                             bool nuw, bool nsw, bool unsigned_, bool saturating):AddSubInst(instruction_stmt,destination,lhs,rhs,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntAddSubInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntAddSubInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool IntAddSubInst::is_nuw() const{
    return this->nuw;
}
bool IntAddSubInst::is_nsw() const{
    return this->nsw;
}
bool IntAddSubInst::is_unsigned() const{
    return this->unsigned_;
}
bool IntAddSubInst::is_saturating() const{
    return this->saturating;
}
TypeVariant IntAddSubInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntAddSubInst::to_string() const{
    std::string str = "let " + this->destination->to_string() + " = .int_addsub(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        str += " #[nuw]";
    }
    if(this->nsw){
        str += " #[nsw]";
    }
    if(this->unsigned_){
        str += " #[unsigned]";
    }
    if(this->saturating){
        str += " #[saturating]";
    }
    return str;
}


FloatAddSubInst::FloatAddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                 FastMathAttr fast_math_attr):AddSubInst(instruction_stmt,destination,lhs,rhs,std::nullopt){}
std::shared_ptr<IR::FloatTypeExpr> FloatAddSubInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatAddSubInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatAddSubInst::is_element_brain_float_type() const{
    return this->get_casted_element_type()->is_brain_float();
}
TypeVariant FloatAddSubInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatAddSubInst::to_string() const{
    std::string res =  "let " + this->destination->to_string() + " = .float_addsub(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}


//----------------------- Reduce Arithmetic SIMD Instructions -----------------------
ReduceArithmeticSIMDInst::ReduceArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                                    IR::LiteralExprPtr mask, std::size_t vector_size, std::optional<FastMathAttr> fast_math_attr):
                                                    Inst(instruction_stmt,destination,fast_math_attr){
    this->vector = vector;
    this->mask = mask;
    this->vector_size = vector_size;
}
IR::LiteralExprPtr ReduceArithmeticSIMDInst::get_vector() const{
    return this->vector;
}
IR::LiteralExprPtr ReduceArithmeticSIMDInst::get_mask() const{
    return this->mask;
}
std::size_t ReduceArithmeticSIMDInst::get_vector_size() const{
    return this->vector_size;
}
IR::TypeExprPtr ReduceArithmeticSIMDInst::get_element_type() const{
    return this->destination->get_type();
}
InstType ReduceArithmeticSIMDInst::get_inst_type() const{
    return InstType::ReduceArithmeticSIMDInst;
}


//--------------------------------- Int Reduce Arithmetic SIMD Instructions ---------------------------------
IntReduceArithmeticSIMDInst::IntReduceArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                                        IR::LiteralExprPtr mask, std::size_t vector_size, bool nuw, bool nsw, bool unsigned_, bool saturating, bool floor)
                                                        :ReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
    this->floor = floor;    
}
std::string IntReduceArithmeticSIMDInst::to_string_helper(const std::string op_name) const{
    std::string vec_type = "<" + this->get_element_type()->to_string() + "," + std::to_string(this->vector_size) + ">:";
    std::string mask_type = "<i64," + std::to_string(this->vector_size) + ">:";
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + vec_type + this->vector->to_string();
    if(this->mask!= nullptr){
        str += ", " + mask_type + this->mask->to_string();
    }
    str += ")";
    if(this->nuw){
        str += " #[nuw]";
    }
    if(this->nsw){
        str += " #[nsw]";
    }
    if(this->unsigned_){
        str += " #[unsigned]";
    }
    if(this->saturating){
        str += " #[saturating]";
    }
    if(this->floor){
        str += " #[floor]";
    }
    return str;
}
std::shared_ptr<IR::IntTypeExpr> IntReduceArithmeticSIMDInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntReduceArithmeticSIMDInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool IntReduceArithmeticSIMDInst::is_nuw() const{
    return this->nuw;
}
bool IntReduceArithmeticSIMDInst::is_nsw() const{
    return this->nsw;
}
bool IntReduceArithmeticSIMDInst::is_unsigned() const{
    return this->unsigned_;
}
bool IntReduceArithmeticSIMDInst::is_saturating() const{
    return this->saturating;
}
bool IntReduceArithmeticSIMDInst::is_floor() const{
    return this->floor;
}
TypeVariant IntReduceArithmeticSIMDInst::get_element_type_variant() const{
    return TypeVariant::Int;
}


IntReduceAddInst::IntReduceAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                   IR::LiteralExprPtr mask, std::size_t vector_size, bool nuw, bool nsw, bool unsigned_, bool saturating)
                                   :IntReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,nuw,nsw,unsigned_,saturating,false){}
ReduceArithmeticSIMDInst::OpType IntReduceAddInst::get_op_type() const{
    return OpType::REDUCE_ADD;
}
std::string IntReduceAddInst::to_string() const{
    return this->to_string_helper("int_reduce_add");
}


IntReduceMulInst::IntReduceMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                   IR::LiteralExprPtr mask, std::size_t vector_size, bool nuw, bool nsw, bool unsigned_, bool saturating)
                                   :IntReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,nuw,nsw,unsigned_,saturating,false){}
ReduceArithmeticSIMDInst::OpType IntReduceMulInst::get_op_type() const{
    return OpType::REDUCE_MUL;
}
std::string IntReduceMulInst::to_string() const{
    return this->to_string_helper("int_reduce_mul");
}


IntReduceAvgInst::IntReduceAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                    IR::LiteralExprPtr mask, std::size_t vector_size, bool nuw, bool nsw, bool unsigned_, bool floor)
                                   :IntReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,nuw,nsw,unsigned_,false,floor){}
ReduceArithmeticSIMDInst::OpType IntReduceAvgInst::get_op_type() const{
    return OpType::REDUCE_AVG;
}
std::string IntReduceAvgInst::to_string() const{
    return this->to_string_helper("int_reduce_avg");
}


IntReduceMinInst::IntReduceMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                   IR::LiteralExprPtr mask, std::size_t vector_size, bool unsigned_)
                                   :IntReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,false,false,unsigned_,false,false){}
ReduceArithmeticSIMDInst::OpType IntReduceMinInst::get_op_type() const{
    return OpType::REDUCE_MIN;
}
std::string IntReduceMinInst::to_string() const{
    return this->to_string_helper("int_reduce_min");
}


//--------------------------------- Float Reduce Arithmetic SIMD Instructions ---------------------------------
FloatReduceArithmeticSIMDInst::FloatReduceArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                                             IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                                                             :ReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,fast_math_attr){
    this->ieee754_2019 = ieee754_2019;
    this->unordered = unordered;
}
std::string FloatReduceArithmeticSIMDInst::to_string_helper(const std::string op_name) const{
    std::string vec_type = "<" + this->get_element_type()->to_string() + "," + std::to_string(this->vector_size) + ">:";
    std::string mask_type = "<i64," + std::to_string(this->vector_size) + ">:";
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + vec_type + this->vector->to_string();
    if(this->mask!= nullptr){
        str += ", " + mask_type + this->mask->to_string();
    }
    str += ")";
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    if(this->ieee754_2019){
        str += " #[ieee754_2019]";
    }
    if(this->unordered){
        str += " #[unordered]";
    }
    return str;
}
std::shared_ptr<IR::FloatTypeExpr> FloatReduceArithmeticSIMDInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatReduceArithmeticSIMDInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatReduceArithmeticSIMDInst::is_element_brain_float_type() const{
    return this->get_casted_element_type()->is_brain_float();
}
bool FloatReduceArithmeticSIMDInst::is_ieee754_2019() const{
    return this->ieee754_2019;
}
bool FloatReduceArithmeticSIMDInst::is_unordered() const{
    return this->unordered;
}
TypeVariant FloatReduceArithmeticSIMDInst::get_element_type_variant() const{
    return TypeVariant::Float;
}

FloatReduceAddInst::FloatReduceAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr)
                                         :FloatReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,fast_math_attr,false,false){}
ReduceArithmeticSIMDInst::OpType FloatReduceAddInst::get_op_type() const{
    return OpType::REDUCE_ADD;
}
std::string FloatReduceAddInst::to_string() const{
    return this->to_string_helper("float_reduce_add");
}


FloatReduceMulInst::FloatReduceMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr)
                                         :FloatReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,fast_math_attr,false,false){}
ReduceArithmeticSIMDInst::OpType FloatReduceMulInst::get_op_type() const{
    return OpType::REDUCE_MUL;
}
std::string FloatReduceMulInst::to_string() const{
    return this->to_string_helper("float_reduce_mul");
}


FloatReduceAvgInst::FloatReduceAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr)
                                         :FloatReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,fast_math_attr,false,false){}
ReduceArithmeticSIMDInst::OpType FloatReduceAvgInst::get_op_type() const{
    return OpType::REDUCE_AVG;
}
std::string FloatReduceAvgInst::to_string() const{
    return this->to_string_helper("float_reduce_avg");
}


FloatReduceMinInst::FloatReduceMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                                         :FloatReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,fast_math_attr,ieee754_2019,unordered){}
ReduceArithmeticSIMDInst::OpType FloatReduceMinInst::get_op_type() const{
    return OpType::REDUCE_MIN;
}
std::string FloatReduceMinInst::to_string() const{
    return this->to_string_helper("float_reduce_min");
}


FloatReduceMaxInst::FloatReduceMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                                         :FloatReduceArithmeticSIMDInst(instruction_stmt,destination,vector,mask,vector_size,fast_math_attr,ieee754_2019,unordered){}
ReduceArithmeticSIMDInst::OpType FloatReduceMaxInst::get_op_type() const{
    return OpType::REDUCE_MAX;
}
std::string FloatReduceMaxInst::to_string() const{
    return this->to_string_helper("float_reduce_max");
}


//--------------------------------- Int Reduce Bitwise SIMD Instructions ---------------------------------
IntReduceBitwiseSIMDInst::IntReduceBitwiseSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                                   IR::LiteralExprPtr mask, std::size_t vector_size, bool disjoint)
                                                   :Inst(instruction_stmt,destination,std::nullopt){
    this->vector = vector;
    this->mask = mask;
    this->vector_size = vector_size;
    this->disjoint = disjoint;
}
std::string IntReduceBitwiseSIMDInst::to_string_helper(const std::string op_name) const{
    std::string vec_type = this->destination->get_type()->to_string() + ":";
    std::string mask_type = "<i64," + std::to_string(this->vector_size) + ">:";
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + vec_type + this->vector->to_string();
    if(this->mask!= nullptr){
        str += ", " + mask_type + this->mask->to_string();
    }
    str += ")";
    if(this->disjoint){
        str += " #[disjoint]";
    }
    return str;
}
IR::LiteralExprPtr IntReduceBitwiseSIMDInst::get_vector() const{
    return this->vector;
}
IR::LiteralExprPtr IntReduceBitwiseSIMDInst::get_mask() const{
    return this->mask;
}
std::size_t IntReduceBitwiseSIMDInst::get_vector_size() const{
    return this->vector_size;
}
std::shared_ptr<IR::IntTypeExpr> IntReduceBitwiseSIMDInst::get_casted_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t IntReduceBitwiseSIMDInst::get_element_bitwidth() const{
    return get_casted_element_type()->get_bits();
}
bool IntReduceBitwiseSIMDInst::is_disjoint() const{
    return this->disjoint;
}
InstType IntReduceBitwiseSIMDInst::get_inst_type() const{
    return InstType::IntReduceBitwiseSIMDInst;
}


IntReduceAndInst::IntReduceAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                    IR::LiteralExprPtr mask, std::size_t vector_size)
                                    :IntReduceBitwiseSIMDInst(instruction_stmt,destination,vector,mask,vector_size,false){}
IntReduceBitwiseSIMDInst::OpType IntReduceAndInst::get_op_type() const{
    return OpType::REDUCE_AND;
}
std::string IntReduceAndInst::to_string() const{
    return this->to_string_helper("int_reduce_and");
}


IntReduceOrInst::IntReduceOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                    IR::LiteralExprPtr mask, std::size_t vector_size, bool disjoint)
                                    :IntReduceBitwiseSIMDInst(instruction_stmt,destination,vector,mask,vector_size,disjoint){}
IntReduceBitwiseSIMDInst::OpType IntReduceOrInst::get_op_type() const{
    return OpType::REDUCE_OR;
}
std::string IntReduceOrInst::to_string() const{
    return this->to_string_helper("int_reduce_or");
}


IntReduceXorInst::IntReduceXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                    IR::LiteralExprPtr mask, std::size_t vector_size)
                                    :IntReduceBitwiseSIMDInst(instruction_stmt,destination,vector,mask,vector_size,false){}
IntReduceBitwiseSIMDInst::OpType IntReduceXorInst::get_op_type() const{
    return OpType::REDUCE_XOR;
}
std::string IntReduceXorInst::to_string() const{
    return this->to_string_helper("int_reduce_xor");
}


IntReduceXnorInst::IntReduceXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                    IR::LiteralExprPtr mask, std::size_t vector_size)
                                    :IntReduceBitwiseSIMDInst(instruction_stmt,destination,vector,mask,vector_size,false){}
IntReduceBitwiseSIMDInst::OpType IntReduceXnorInst::get_op_type() const{
    return OpType::REDUCE_XNOR;
}
std::string IntReduceXnorInst::to_string() const{
    return this->to_string_helper("int_reduce_xnor");
}


//---------------- Horizontal Arithmetic SIMD Instructions ----------------
HArithmeticSIMDInst::HArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                       std::optional<FastMathAttr> fast_math_attr)
                       :Inst(instruction_stmt, destination, fast_math_attr){
    this->lhs = lhs;
    this->rhs = rhs;
}
IR::LiteralExprPtr HArithmeticSIMDInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr HArithmeticSIMDInst::get_rhs() const{
    return this->rhs;
}
IR::TypeExprPtr HArithmeticSIMDInst::get_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::size_t HArithmeticSIMDInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType HArithmeticSIMDInst::get_inst_type() const{
    return InstType::HArithmeticSIMDInst;
}


//---------------- Int Horizontal Arithmetic SIMD Instructions ----------------
IntHArithmeticSIMDInst::IntHArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                               bool nuw, bool nsw, bool unsigned_, bool saturating, bool floor)
                                               :HArithmeticSIMDInst(instruction_stmt, destination, lhs, rhs, std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
    this->floor = floor;
}
std::string IntHArithmeticSIMDInst::to_string_helper(const std::string op_name) const{
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw){
        str += " #[nuw]";
    }
    if(this->nsw){
        str += " #[nsw]";
    }
    if(this->unsigned_){
        str += " #[unsigned]";
    }
    if(this->saturating){
        str += " #[saturating]";
    }
    if(this->floor){
        str += " #[floor]";
    }
    return str;
}
std::shared_ptr<IR::IntTypeExpr> IntHArithmeticSIMDInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntHArithmeticSIMDInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool IntHArithmeticSIMDInst::is_nuw() const{
    return this->nuw;
}
bool IntHArithmeticSIMDInst::is_nsw() const{
    return this->nsw;
}
bool IntHArithmeticSIMDInst::is_unsigned() const{
    return this->unsigned_;
}
bool IntHArithmeticSIMDInst::is_saturating() const{
    return this->saturating;
}
bool IntHArithmeticSIMDInst::is_floor() const{
    return this->floor;
}
TypeVariant IntHArithmeticSIMDInst::get_element_type_variant() const{
    return TypeVariant::Int;
}


IntHorizontalAddInst::IntHorizontalAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                           bool nuw, bool nsw, bool unsigned_, bool saturating)
                                           :IntHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,nuw,nsw,unsigned_,saturating,false){}
IntHArithmeticSIMDInst::OpType IntHorizontalAddInst::get_op_type() const{
    return OpType::HADD;
}
std::string IntHorizontalAddInst::to_string() const{
    return this->to_string_helper("int_horizontal_add");
}


IntHorizontalSubInst::IntHorizontalSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                           bool nuw, bool nsw, bool unsigned_, bool saturating)
                                           :IntHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,nuw,nsw,unsigned_,saturating,false){}
IntHArithmeticSIMDInst::OpType IntHorizontalSubInst::get_op_type() const{
    return OpType::HSUB;
}
std::string IntHorizontalSubInst::to_string() const{
    return this->to_string_helper("int_horizontal_sub");
}


IntHorizontalAbsDiffInst::IntHorizontalAbsDiffInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    bool nuw, bool nsw, bool unsigned_, bool saturating)
                                                    :IntHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,nuw,nsw,unsigned_,saturating,false){}
IntHArithmeticSIMDInst::OpType IntHorizontalAbsDiffInst::get_op_type() const{
    return OpType::HABSDIFF;
}
std::string IntHorizontalAbsDiffInst::to_string() const{
    return this->to_string_helper("int_horizontal_abs_diff");
}


IntHorizontalAddSubInst::IntHorizontalAddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                               bool nuw, bool nsw, bool unsigned_, bool saturating)
                                               :IntHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,nuw,nsw,unsigned_,saturating,false){}
IntHArithmeticSIMDInst::OpType IntHorizontalAddSubInst::get_op_type() const{
    return OpType::HADDSUB;
}
std::string IntHorizontalAddSubInst::to_string() const{
    return this->to_string_helper("int_horizontal_addsub");
}


IntHorizontalMulInst::IntHorizontalMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                            bool nuw, bool nsw, bool unsigned_, bool saturating)
                                            :IntHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,nuw,nsw,unsigned_,saturating,false){}
IntHArithmeticSIMDInst::OpType IntHorizontalMulInst::get_op_type() const{
    return OpType::HMUL;
}
std::string IntHorizontalMulInst::to_string() const{
    return this->to_string_helper("int_horizontal_mul");
}


IntHorizontalAvgInst::IntHorizontalAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                            bool nuw, bool nsw, bool unsigned_, bool floor)
                                            :IntHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,nuw,nsw,unsigned_,false,floor){}
IntHArithmeticSIMDInst::OpType IntHorizontalAvgInst::get_op_type() const{
    return OpType::HAVG;
}
std::string IntHorizontalAvgInst::to_string() const{
    return this->to_string_helper("int_horizontal_avg");
}


IntHorizontalMinInst::IntHorizontalMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                            bool unsigned_)
                                            :IntHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,false,false,unsigned_,false,false){}
IntHArithmeticSIMDInst::OpType IntHorizontalMinInst::get_op_type() const{
    return OpType::HMIN;
}
std::string IntHorizontalMinInst::to_string() const{
    return this->to_string_helper("int_horizontal_min");
}


IntHorizontalMaxInst::IntHorizontalMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                            bool unsigned_)
                                            :IntHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,false,false,unsigned_,false,false){}
IntHArithmeticSIMDInst::OpType IntHorizontalMaxInst::get_op_type() const{
    return OpType::HMAX;
}
std::string IntHorizontalMaxInst::to_string() const{
    return this->to_string_helper("int_horizontal_max");
}


//---------------- Float Horizontal Arithmetic SIMD Instructions ----------------
FloatHArithmeticSIMDInst::FloatHArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                     FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                                                     :HArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,fast_math_attr){
    this->ieee754_2019 = ieee754_2019;
    this->unordered = unordered;
}
std::string FloatHArithmeticSIMDInst::to_string_helper(const std::string op_name) const{
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    if(this->ieee754_2019){
        str += " #[ieee754_2019]";
    }
    if(this->unordered){
        str += " #[unordered]";
    }
    return str;
}
std::shared_ptr<IR::FloatTypeExpr> FloatHArithmeticSIMDInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatHArithmeticSIMDInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatHArithmeticSIMDInst::is_element_brain_float_type() const{
    return this->get_casted_element_type()->is_brain_float();
}
bool FloatHArithmeticSIMDInst::is_ieee754_2019() const{
    return this->ieee754_2019;
}
bool FloatHArithmeticSIMDInst::is_unordered() const{
    return this->unordered;
}
TypeVariant FloatHArithmeticSIMDInst::get_element_type_variant() const{
    return TypeVariant::Float;
}


FloatHorizontalAddInst::FloatHorizontalAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                               FastMathAttr fast_math_attr)
                                               :FloatHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,fast_math_attr,false,false){}
HArithmeticSIMDInst::OpType FloatHorizontalAddInst::get_op_type() const{
    return OpType::HADD;
}
std::string FloatHorizontalAddInst::to_string() const{
    return this->to_string_helper("float_horizontal_add");
}


FloatHorizontalSubInst::FloatHorizontalSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                               FastMathAttr fast_math_attr)
                                               :FloatHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,fast_math_attr,false,false){}
HArithmeticSIMDInst::OpType FloatHorizontalSubInst::get_op_type() const{
    return OpType::HSUB;
}
std::string FloatHorizontalSubInst::to_string() const{
    return this->to_string_helper("float_horizontal_sub");
}


FloatHorizontalAbsDiffInst::FloatHorizontalAbsDiffInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                    FastMathAttr fast_math_attr)
                                                    :FloatHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,fast_math_attr,false,false){}
HArithmeticSIMDInst::OpType FloatHorizontalAbsDiffInst::get_op_type() const{
    return OpType::HABSDIFF;
}
std::string FloatHorizontalAbsDiffInst::to_string() const{
    return this->to_string_helper("float_horizontal_abs_diff");
}


FloatHorizontalAddSubInst::FloatHorizontalAddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                                     FastMathAttr fast_math_attr)
                                                     :FloatHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,fast_math_attr,false,false){}
HArithmeticSIMDInst::OpType FloatHorizontalAddSubInst::get_op_type() const{
    return OpType::HADDSUB;
}
std::string FloatHorizontalAddSubInst::to_string() const{
    return this->to_string_helper("float_horizontal_addsub");
}


FloatHorizontalMulInst::FloatHorizontalMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                               FastMathAttr fast_math_attr)
                                               :FloatHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,fast_math_attr,false,false){}
HArithmeticSIMDInst::OpType FloatHorizontalMulInst::get_op_type() const{
    return OpType::HMUL;
}
std::string FloatHorizontalMulInst::to_string() const{
    return this->to_string_helper("float_horizontal_mul");
}


FloatHorizontalAvgInst::FloatHorizontalAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                               FastMathAttr fast_math_attr)
                                               :FloatHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,fast_math_attr,false,false){}
HArithmeticSIMDInst::OpType FloatHorizontalAvgInst::get_op_type() const{
    return OpType::HAVG;
}
std::string FloatHorizontalAvgInst::to_string() const{
    return this->to_string_helper("float_horizontal_avg");
}


FloatHorizontalMinInst::FloatHorizontalMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                               FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                                               :FloatHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,fast_math_attr,ieee754_2019,unordered){}
HArithmeticSIMDInst::OpType FloatHorizontalMinInst::get_op_type() const{
    return OpType::HMIN;
}
std::string FloatHorizontalMinInst::to_string() const{
    return this->to_string_helper("float_horizontal_min");
}


FloatHorizontalMaxInst::FloatHorizontalMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                               FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                                               :FloatHArithmeticSIMDInst(instruction_stmt,destination,lhs,rhs,fast_math_attr,ieee754_2019,unordered){}
HArithmeticSIMDInst::OpType FloatHorizontalMaxInst::get_op_type() const{
    return OpType::HMAX;
}
std::string FloatHorizontalMaxInst::to_string() const{
    return this->to_string_helper("float_horizontal_max");
}


//---------------- Int Horizontal Bitwise SIMD Instructions ----------------
IntHBitwiseSIMDInst::IntHBitwiseSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                         bool disjoint)
                                         :Inst(instruction_stmt,destination,std::nullopt){
    this->lhs = lhs;
    this->rhs = rhs;
    this->disjoint = disjoint;
}
std::string IntHBitwiseSIMDInst::to_string_helper(const std::string op_name) const{
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->disjoint){
        str += " #[disjoint]";
    }
    return str;
}
IR::LiteralExprPtr IntHBitwiseSIMDInst::get_lhs() const{
    return this->rhs;
}
IR::LiteralExprPtr IntHBitwiseSIMDInst::get_rhs() const{
    return this->rhs;
}
std::size_t IntHBitwiseSIMDInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
std::shared_ptr<IR::IntTypeExpr> IntHBitwiseSIMDInst::get_casted_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t IntHBitwiseSIMDInst::get_element_bitwidth() const{
    return get_casted_element_type()->get_bits();
}
bool IntHBitwiseSIMDInst::is_disjoint() const{
    return this->disjoint;
}
InstType IntHBitwiseSIMDInst::get_inst_type() const{
    return InstType::IntHBitwiseSIMDInst;
}


IntHorizontalAndInst::IntHorizontalAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                                           :IntHBitwiseSIMDInst(instruction_stmt,destination,lhs,rhs,false){}
IntHBitwiseSIMDInst::OpType IntHorizontalAndInst::get_op_type() const{
    return OpType::HAND;
}
std::string IntHorizontalAndInst::to_string() const{
    return this->to_string_helper("int_horizontal_and");
}


IntHorizontalNandInst::IntHorizontalNandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                                            :IntHBitwiseSIMDInst(instruction_stmt,destination,lhs,rhs,false){}
IntHBitwiseSIMDInst::OpType IntHorizontalNandInst::get_op_type() const{
    return OpType::HNAND;
}
std::string IntHorizontalNandInst::to_string() const{
    return this->to_string_helper("int_horizontal_nand");
}


IntHorizontalOrInst::IntHorizontalOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, bool disjoint)
                                          :IntHBitwiseSIMDInst(instruction_stmt,destination,lhs,rhs,disjoint){}
IntHBitwiseSIMDInst::OpType IntHorizontalOrInst::get_op_type() const{
    return OpType::HOR;
}
std::string IntHorizontalOrInst::to_string() const{
    return this->to_string_helper("int_horizontal_or");
}


IntHorizontalNorInst::IntHorizontalNorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, bool disjoint)
                                           :IntHBitwiseSIMDInst(instruction_stmt,destination,lhs,rhs,disjoint){}
IntHBitwiseSIMDInst::OpType IntHorizontalNorInst::get_op_type() const{
    return OpType::HNOR;
}
std::string IntHorizontalNorInst::to_string() const{
    return this->to_string_helper("int_horizontal_nor");
}


IntHorizontalXorInst::IntHorizontalXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                                            :IntHBitwiseSIMDInst(instruction_stmt,destination,lhs,rhs,false){}
IntHBitwiseSIMDInst::OpType IntHorizontalXorInst::get_op_type() const{
    return OpType::HXOR;
}
std::string IntHorizontalXorInst::to_string() const{
    return this->to_string_helper("int_horizontal_xor");
}


IntHorizontalXnorInst::IntHorizontalXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs)
                                             :IntHBitwiseSIMDInst(instruction_stmt,destination,lhs,rhs,false){}
IntHBitwiseSIMDInst::OpType IntHorizontalXnorInst::get_op_type() const{
    return OpType::HXNOR;
}
std::string IntHorizontalXnorInst::to_string() const{
    return this->to_string_helper("int_horizontal_xnor");
}


//--------------------------------- Dot Product Instructions ---------------------------------
DotInst::DotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::LiteralExprPtr acc,
                 IR::TypeExprPtr input_vector_type, std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt,destination,fast_math_attr){
    this->lhs = lhs;
    this->rhs = rhs;
    this->acc = acc;
    this->input_vector_type = input_vector_type;
}
std::string DotInst::to_string_helper(const std::string op_name) const{
    std::string vec_type = this->input_vector_type->to_string() + ":";
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + vec_type + this->lhs->to_string() + ", " + vec_type + this->rhs->to_string();
    if(this->acc != nullptr){
        auto acc_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type())->get_basetype()->to_string() + ":";
        str += ", "  + acc_type + this->acc->to_string();
    }
    str += ")";
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr DotInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr DotInst::get_rhs() const{
    return this->rhs;
}
IR::LiteralExprPtr DotInst::get_acc() const{
    return this->acc;
}
IR::TypeExprPtr DotInst::get_input_basetype() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_vector_type);
    return simd_type->get_basetype();
}
std::size_t DotInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_vector_type);
    return simd_type->get_size();
}
IR::TypeExprPtr DotInst::get_output_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
InstType DotInst::get_inst_type() const{
    return InstType::DotInst;
}


IntDotInst::IntDotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::LiteralExprPtr acc, 
                       IR::TypeExprPtr input_vector_type, bool nuw, bool nsw, bool unsigned_,  bool saturating)
                       :DotInst(instruction_stmt,destination,lhs,rhs,acc,input_vector_type,std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
}
bool IntDotInst::is_nuw() const{
    return this->nuw;
}
bool IntDotInst::is_nsw() const{
    return this->nsw;
}
bool IntDotInst::is_unsigned() const{
    return this->unsigned_;
}
bool IntDotInst::is_saturating() const{
    return this->saturating;
}
std::shared_ptr<IR::IntTypeExpr> IntDotInst::get_casted_input_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_input_basetype());
}
std::size_t IntDotInst::get_input_basetype_bitwidth() const{
    return this->get_casted_input_basetype()->get_bits();
}
std::shared_ptr<IR::IntTypeExpr> IntDotInst::get_casted_output_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_output_type());
}
std::size_t IntDotInst::get_output_bitwidth() const{
    return this->get_casted_output_type()->get_bits();
}
TypeVariant IntDotInst::get_basetype_variant() const{
    return TypeVariant::Int;
}
std::string IntDotInst::to_string() const{
    std::string res = this->to_string_helper("int_dot");
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


FloatDotInst::FloatDotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::LiteralExprPtr acc, 
                           IR::TypeExprPtr input_vector_type, FastMathAttr fast_math_attr)
                            :DotInst(instruction_stmt,destination,lhs,rhs,acc,input_vector_type,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatDotInst::get_casted_input_basetype() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_input_basetype());
}
std::size_t FloatDotInst::get_input_basetype_bitwidth() const{
    return this->get_casted_input_basetype()->get_bits();
}
bool FloatDotInst::is_input_basetype_brain_float() const{
    return this->get_casted_input_basetype()->is_brain_float();
}
std::shared_ptr<IR::FloatTypeExpr> FloatDotInst::get_casted_output_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_output_type());
}
std::size_t FloatDotInst::get_output_bitwidth() const{
    return this->get_casted_output_type()->get_bits();
}
bool FloatDotInst::is_output_brain_float() const{
    return this->get_casted_output_type()->is_brain_float();
}
TypeVariant FloatDotInst::get_basetype_variant() const{
    return TypeVariant::Float;
}
std::string FloatDotInst::to_string() const{
    return this->to_string_helper("float_dot");
}


//--------------------------------- Absolute Difference Instructions ---------------------------------
SADInst::SADInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::LiteralExprPtr acc,
                 IR::TypeExprPtr input_vector_type, std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt,destination,fast_math_attr){
    this->lhs = lhs;
    this->rhs = rhs;
    this->acc = acc;
    this->input_vector_type = input_vector_type;
}
std::string SADInst::to_string_helper(const std::string op_name) const{
    std::string vec_type = this->input_vector_type->to_string() + ":";
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + vec_type + this->lhs->to_string() + ", " + this->rhs->to_string();
    if(this->acc != nullptr){
        auto acc_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type())->get_basetype()->to_string() + ":";
        str += ", "  + acc_type + this->acc->to_string();
    }
    str += ")";
    if(this->fast_math_attr.has_value()){
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr SADInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr SADInst::get_rhs() const{
    return this->rhs;
}
IR::TypeExprPtr SADInst::get_input_basetype() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_vector_type);
    return simd_type->get_basetype();
}
std::size_t SADInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_vector_type);
    return simd_type->get_size();
}
IR::TypeExprPtr SADInst::get_output_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
InstType SADInst::get_inst_type() const{
    return InstType::SADInst;
}


IntSADInst::IntSADInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::LiteralExprPtr acc,
                       IR::TypeExprPtr input_vector_type, bool nuw, bool nsw, bool unsigned_,  bool saturating)
                       :SADInst(instruction_stmt,destination,lhs,rhs,acc,input_vector_type,std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->unsigned_ = unsigned_;
    this->saturating = saturating;
}

bool IntSADInst::is_nuw() const{
    return this->nuw;
}
bool IntSADInst::is_nsw() const{
    return this->nsw;
}
bool IntSADInst::is_unsigned() const{
    return this->unsigned_;
}
bool IntSADInst::is_saturating() const{
    return this->saturating;
}
std::shared_ptr<IR::IntTypeExpr> IntSADInst::get_casted_input_basetype() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_input_basetype());
}
std::size_t IntSADInst::get_input_basetype_bitwidth() const{
    return this->get_casted_input_basetype()->get_bits();
}
std::shared_ptr<IR::IntTypeExpr> IntSADInst::get_casted_output_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_output_type());
}
std::size_t IntSADInst::get_output_bitwidth() const{
    return this->get_casted_output_type()->get_bits();
}
TypeVariant IntSADInst::get_basetype_variant() const{
    return TypeVariant::Int;
}
std::string IntSADInst::to_string() const{
    std::string res = this->to_string_helper("int_sad");
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


FloatSADInst::FloatSADInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::LiteralExprPtr acc,
                           IR::TypeExprPtr input_vector_type, FastMathAttr fast_math_attr)
                           :SADInst(instruction_stmt,destination,lhs,rhs,acc,input_vector_type,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatSADInst::get_casted_input_basetype() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_input_basetype());
}
std::size_t FloatSADInst::get_input_basetype_bitwidth() const{
    return this->get_casted_input_basetype()->get_bits();
}
bool FloatSADInst::is_input_basetype_brain_float() const{
    return this->get_casted_input_basetype()->is_brain_float();
}
std::shared_ptr<IR::FloatTypeExpr> FloatSADInst::get_casted_output_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_output_type());
}
std::size_t FloatSADInst::get_output_bitwidth() const{
    return this->get_casted_output_type()->get_bits();
}
bool FloatSADInst::is_output_brain_float() const{
    return this->get_casted_output_type()->is_brain_float();
}
TypeVariant FloatSADInst::get_basetype_variant() const{
    return TypeVariant::Float;
}
std::string FloatSADInst::to_string() const{
    return this->to_string_helper("float_sad");
}


//--------------------------------- Pack / Unpack Instructions ---------------------------------
PackSatInst::PackSatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                         IR::TypeExprPtr input_vector_type, bool unsigned_):Inst(instruction_stmt,destination,std::nullopt){
    this->lhs = lhs;
    this->rhs = rhs;
    this->input_vector_type = input_vector_type;
    this->unsigned_ = unsigned_;
}
bool PackSatInst::is_unsigned() const{
    return this->unsigned_;
}
IR::LiteralExprPtr PackSatInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr PackSatInst::get_rhs() const{
    return this->rhs;
}
std::size_t PackSatInst::get_input_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_vector_type);
    return simd_type->get_size();
}
std::size_t PackSatInst::get_output_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
std::shared_ptr<IR::IntTypeExpr> PackSatInst::get_casted_input_basetype() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_vector_type);
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t PackSatInst::get_input_basetype_bitwidth() const{
    return this->get_casted_input_basetype()->get_bits();
}
std::shared_ptr<IR::IntTypeExpr> PackSatInst::get_casted_output_basetype() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t PackSatInst::get_output_basetype_bitwidth() const{
    return this->get_casted_output_basetype()->get_bits();
}
InstType PackSatInst::get_inst_type() const{
    return InstType::PackSatInst;
}
std::string PackSatInst::to_string() const{
    std::string res = "let " + this->destination->to_string() + " = .pack_sat(" + this->input_vector_type->to_string() + ":" + this->lhs->to_string() + ", " + this->input_vector_type->to_string() + ":" + this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}


UnpackLoInst::UnpackLoInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                           IR::TypeExprPtr input_vector_type, bool unsigned_):Inst(instruction_stmt,destination,std::nullopt){
    this->lhs = lhs;
    this->rhs = rhs;
    this->input_vector_type = input_vector_type;
    this->unsigned_ = unsigned_;
};
bool UnpackLoInst::is_unsigned() const{
    return this->unsigned_;
}
IR::LiteralExprPtr UnpackLoInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr UnpackLoInst::get_rhs() const{
    return this->rhs;
}
std::size_t UnpackLoInst::get_input_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_vector_type);
    return simd_type->get_size();
}
std::size_t UnpackLoInst::get_output_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
std::shared_ptr<IR::IntTypeExpr> UnpackLoInst::get_casted_input_basetype() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_vector_type);
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t UnpackLoInst::get_input_basetype_bitwidth() const{
    return this->get_casted_input_basetype()->get_bits();
}
std::shared_ptr<IR::IntTypeExpr> UnpackLoInst::get_casted_output_basetype() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t UnpackLoInst::get_output_basetype_bitwidth() const{
    return this->get_casted_output_basetype()->get_bits();
}
InstType UnpackLoInst::get_inst_type() const{
    return InstType::UnpackLoInst;
}
std::string UnpackLoInst::to_string() const{
    std::string res = "let " + this->destination->to_string() + " = .unpack_lo(" + this->input_vector_type->to_string() + ":" + this->lhs->to_string() + ", " + this->input_vector_type->to_string() + ":" + this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}


UnpackHiInst::UnpackHiInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                           IR::TypeExprPtr input_vector_type, bool unsigned_):Inst(instruction_stmt,destination,std::nullopt){
    this->lhs = lhs;
    this->rhs = rhs;
    this->input_vector_type = input_vector_type;
    this->unsigned_ = unsigned_;
};
bool UnpackHiInst::is_unsigned() const{
    return this->unsigned_;
}
IR::LiteralExprPtr UnpackHiInst::get_lhs() const{
    return this->lhs;
}
IR::LiteralExprPtr UnpackHiInst::get_rhs() const{
    return this->rhs;
}
std::size_t UnpackHiInst::get_input_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_vector_type);
    return simd_type->get_size();
}
std::size_t UnpackHiInst::get_output_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
std::shared_ptr<IR::IntTypeExpr> UnpackHiInst::get_casted_input_basetype() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->input_vector_type);
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t UnpackHiInst::get_input_basetype_bitwidth() const{
    return this->get_casted_input_basetype()->get_bits();
}
std::shared_ptr<IR::IntTypeExpr> UnpackHiInst::get_casted_output_basetype() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(simd_type->get_basetype());
}
std::size_t UnpackHiInst::get_output_basetype_bitwidth() const{
    return this->get_casted_output_basetype()->get_bits();
}
InstType UnpackHiInst::get_inst_type() const{
    return InstType::UnpackHiInst;
}
std::string UnpackHiInst::to_string() const{
    std::string res = "let " + this->destination->to_string() + " = .unpack_hi(" + this->input_vector_type->to_string() + ":" + this->lhs->to_string() + ", " + this->input_vector_type->to_string() + ":" + this->rhs->to_string() + ")";
    if(this->unsigned_){
        res += " #[unsigned]";
    }
    return res;
}


//--------------------------------- Vector Layout Instructions ---------------------------------
CompressInst::CompressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask,
                           bool poison_inactive, std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt,destination,fast_math_attr){
    this->src = src;
    this->mask = mask;
    this->poison_inactive = poison_inactive;
}
std::string CompressInst::to_string_helper(std::string op_name) const{
    std::string src_type = this->destination->get_type()->to_string() + ":";
    std::string mask_type = "<i1,"+std::to_string(this->get_vector_size()) + ">";
    std::string res = "let " + this->destination->to_string() + "= ." + op_name + "(" + src_type + ":" + this->src->to_string() + ", " + mask_type + ":" + this->mask->to_string() + ")";
    if(this->poison_inactive){
        res += " #[poison_inactive]";
    }
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
IR::LiteralExprPtr CompressInst::get_src() const{
    return this->src;
}
IR::LiteralExprPtr CompressInst::get_mask() const{
    return this->mask;
}
bool CompressInst::is_poison_inactive() const{ 
    return this->poison_inactive;
}
IR::TypeExprPtr CompressInst::get_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::size_t CompressInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType CompressInst::get_inst_type() const{
    return InstType::CompressInst;
}


IntCompressInst::IntCompressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask,
                                 bool poison_inactive)
                                 :CompressInst(instruction_stmt,destination,src,mask,poison_inactive,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntCompressInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntCompressInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntCompressInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntCompressInst::to_string() const{
    return this->to_string_helper("int_compress");
}


PtrCompressInst::PtrCompressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask,
                                 bool poison_inactive)
                                 :CompressInst(instruction_stmt,destination,src,mask,poison_inactive,std::nullopt){}
std::size_t PtrCompressInst::get_element_bitwidth() const{
    return 64;
}
TypeVariant PtrCompressInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrCompressInst::to_string() const{
    return this->to_string_helper("ptr_compress");
}


FloatCompressInst::FloatCompressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask,
                                     bool poison_inactive, FastMathAttr fast_math_attr)
                                     :CompressInst(instruction_stmt,destination,src,mask,poison_inactive,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatCompressInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatCompressInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatCompressInst::is_element_brain_float_type() const{
    return get_casted_element_type()->is_brain_float();
}
TypeVariant FloatCompressInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatCompressInst::to_string() const{   
    return this->to_string_helper("float_compress");
}


ExpandInst::ExpandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask, IR::LiteralExprPtr passthru,
                       bool zeropassthru, std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt,destination,fast_math_attr){
    this->src = src;
    this->mask = mask;
    this->passthru = passthru;
    this->zeropassthru = zeropassthru;
}
std::string ExpandInst::to_string_helper(std::string op_name) const{
    std::string src_type = this->destination->get_type()->to_string() + ":";
    std::string mask_type = "<i1,"+std::to_string(this->get_vector_size()) + ">";
    std::string passthru_type = this->destination->get_type()->to_string() + ":";
    std::string res = "let " + this->destination->to_string() + " = ." + op_name + "(" + src_type + this->src->to_string() + ", " + mask_type + this->mask->to_string();
    if(this->passthru!=nullptr){
        res += ", " + passthru_type + this->passthru->to_string();
    }
    res += ")";
    if(this->zeropassthru){
        res += " #[zeropassthru]";
    }
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
IR::LiteralExprPtr ExpandInst::get_src() const{
    return this->src;
}
IR::LiteralExprPtr ExpandInst::get_mask() const{
    return this->mask;
}
IR::LiteralExprPtr ExpandInst::get_passthru() const{
    return this->passthru;
}
bool ExpandInst::is_zeropassthru() const{
    return this->zeropassthru;
}
IR::TypeExprPtr ExpandInst::get_element_type() const{
    return this->destination->get_type();
}
std::size_t ExpandInst::get_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType ExpandInst::get_inst_type() const{
    return InstType::ExpandInst;
}


IntExpandInst::IntExpandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask, IR::LiteralExprPtr passthru,
                             bool zeropassthru)
                             :ExpandInst(instruction_stmt,destination,src,mask,passthru,zeropassthru,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntExpandInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntExpandInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntExpandInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntExpandInst::to_string() const{
    return this->to_string_helper("int_expand");
}


PtrExpandInst::PtrExpandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask, IR::LiteralExprPtr passthru,
                             bool zeropassthru)
                             :ExpandInst(instruction_stmt,destination,src,mask,passthru,zeropassthru,std::nullopt){}
std::size_t PtrExpandInst::get_element_bitwidth() const{
    return 64;
}
TypeVariant PtrExpandInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrExpandInst::to_string() const{
    return this->to_string_helper("ptr_expand");
}


FloatExpandInst::FloatExpandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask, IR::LiteralExprPtr passthru,
                                 bool zeropassthru, FastMathAttr fast_math_attr)
                                 :ExpandInst(instruction_stmt,destination,src,mask,passthru,zeropassthru,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatExpandInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatExpandInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatExpandInst::is_element_brain_float_type() const{
    return get_casted_element_type()->is_brain_float();
}
TypeVariant FloatExpandInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatExpandInst::to_string() const{
    return this->to_string_helper("float_expand");  
}


InterleaveInst::InterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::vector<IR::LiteralExprPtr> args, 
                               std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt,destination,fast_math_attr){
    this->args = args;
}
std::string InterleaveInst::to_string_helper(const std::string op_name) const{
    std::string vec_type = "<" + this->get_element_type()->to_string() + ", " + std::to_string(this->get_input_vector_size()) + ">:";
    std::string res = "let " + this->destination->to_string() + " = ." + op_name + std::to_string(this->get_interleave_kind()) + "(";
    for(std::size_t i=0; i<this->args.size(); i++){
        res += vec_type + this->args[i]->to_string();
        if(i!=this->args.size()-1){
            res += ", ";
        }
    }
    res += ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
std::vector<IR::LiteralExprPtr> InterleaveInst::get_args() const{
    return this->args;
}
std::size_t InterleaveInst::get_interleave_kind() const{
    return this->args.size();
}
IR::TypeExprPtr InterleaveInst::get_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::size_t InterleaveInst::get_input_vector_size() const{
    return get_output_vector_size() / this->get_interleave_kind();
}
std::size_t InterleaveInst::get_output_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType InterleaveInst::get_inst_type() const{
    return InstType::InterleaveInst;
}


IntInterleaveInst::IntInterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::vector<IR::LiteralExprPtr> args)
                                   :InterleaveInst(instruction_stmt,destination,args,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntInterleaveInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntInterleaveInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntInterleaveInst::get_element_type_variant() const{
    return TypeVariant::Int;
} 
std::string IntInterleaveInst::to_string() const{
    return this->to_string_helper("int_interleave");
}


PtrInterleaveInst::PtrInterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::vector<IR::LiteralExprPtr> args)
                                   :InterleaveInst(instruction_stmt,destination,args,std::nullopt){}
std::size_t PtrInterleaveInst::get_element_bitwidth() const{
    return 64;
}
TypeVariant PtrInterleaveInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrInterleaveInst::to_string() const{
    return this->to_string_helper("ptr_interleave");
}


FloatInterleaveInst::FloatInterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::vector<IR::LiteralExprPtr> args, FastMathAttr fast_math_attr)
                                         :InterleaveInst(instruction_stmt,destination,args,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatInterleaveInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatInterleaveInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatInterleaveInst::is_element_brain_float_type() const{
    return get_casted_element_type()->is_brain_float();
}
TypeVariant FloatInterleaveInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatInterleaveInst::to_string() const{
    return this->to_string_helper("float_interleave");
}


DeinterleaveInst::DeinterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg, IR::TypeExprPtr arg_type, IR::LiteralExprPtr channel,
                                   std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt,destination,fast_math_attr){
    this->arg = arg;
    this->arg_type = arg_type;
    this->channel = channel;
}
std::string DeinterleaveInst::to_string_helper(const std::string op_name) const{
    std::string vec_type = this->arg_type->to_string() + ":";
    std::string res = "let " + this->destination->to_string() + " = ." + op_name + std::to_string(this->get_deinterleave_kind()) + "(" + vec_type + this->arg->to_string() + ", i8:" + this->channel->to_string() + ")";
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
IR::LiteralExprPtr DeinterleaveInst::get_arg() const{
    return this->arg;
}
IR::LiteralExprPtr DeinterleaveInst::get_channel() const{
    return this->channel;
}
std::size_t DeinterleaveInst::get_deinterleave_kind() const{
    return get_input_vector_size() / get_output_vector_size();
}
IR::TypeExprPtr DeinterleaveInst::get_element_type() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->arg_type);
    return simd_type->get_basetype();
}
std::size_t DeinterleaveInst::get_input_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->arg_type);
    return simd_type->get_size();
}
std::size_t DeinterleaveInst::get_output_vector_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType DeinterleaveInst::get_inst_type() const{
    return InstType::DeinterleaveInst;
}


IntDeinterleaveInst::IntDeinterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg, IR::TypeExprPtr arg_type, IR::LiteralExprPtr channel)
                                         :DeinterleaveInst(instruction_stmt,destination,arg,arg_type,channel,std::nullopt){}
std::shared_ptr<IR::IntTypeExpr> IntDeinterleaveInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntDeinterleaveInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
TypeVariant IntDeinterleaveInst::get_element_type_variant() const{
    return TypeVariant::Int;
}
std::string IntDeinterleaveInst::to_string() const{
    return this->to_string_helper("int_deinterleave");
}


PtrDeinterleaveInst::PtrDeinterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg, IR::TypeExprPtr arg_type, IR::LiteralExprPtr channel)
                                         :DeinterleaveInst(instruction_stmt,destination,arg,arg_type,channel,std::nullopt){}
std::size_t PtrDeinterleaveInst::get_element_bitwidth() const{
    return 64;
}
TypeVariant PtrDeinterleaveInst::get_element_type_variant() const{
    return TypeVariant::Ptr;
}
std::string PtrDeinterleaveInst::to_string() const{
    return this->to_string_helper("ptr_deinterleave");
}


FloatDeinterleaveInst::FloatDeinterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg, IR::TypeExprPtr arg_type, IR::LiteralExprPtr channel, FastMathAttr fast_math_attr)
                                             :DeinterleaveInst(instruction_stmt,destination,arg,arg_type,channel,fast_math_attr){}
std::shared_ptr<IR::FloatTypeExpr> FloatDeinterleaveInst::get_casted_element_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatDeinterleaveInst::get_element_bitwidth() const{
    return this->get_casted_element_type()->get_bits();
}
bool FloatDeinterleaveInst::is_element_brain_float_type() const{
    return this->get_casted_element_type()->is_brain_float();
}
TypeVariant FloatDeinterleaveInst::get_element_type_variant() const{
    return TypeVariant::Float;
}
std::string FloatDeinterleaveInst::to_string() const{
    return this->to_string_helper("float_deinterleave");
}


//--------------------------------- Lane Mask Conversion Instructions --------------------------------
MaskToIntInst::MaskToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr mask, IR::TypeExprPtr mask_type)
                             :Inst(instruction_stmt,destination,std::nullopt){
    this->mask = mask;
    this->mask_type = mask_type;
}
IR::LiteralExprPtr MaskToIntInst::get_mask() const{
    return this->mask;
}
std::size_t MaskToIntInst::get_mask_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->mask_type);
    return simd_type->get_size();
}
std::size_t MaskToIntInst::get_output_int_bitwidth() const{
    auto int_type = std::dynamic_pointer_cast<IR::IntTypeExpr>(this->destination->get_type());
    return int_type->get_bits();
}
InstType MaskToIntInst::get_inst_type() const{
    return InstType::MaskToIntInst;
}
std::string MaskToIntInst::to_string() const{
    return "let " + this->destination->to_string() + " = .mask_to_int(" + this->mask->to_string() + ")";
}


IntToMaskInst::IntToMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr input, IR::TypeExprPtr input_type)
                             :Inst(instruction_stmt,destination,std::nullopt){
    this->input = input;
    this->input_type = input_type;
}
IR::LiteralExprPtr IntToMaskInst::get_input() const{
    return this->input;
}
std::size_t IntToMaskInst::get_input_int_bitwidth() const{
    auto int_type = std::dynamic_pointer_cast<IR::IntTypeExpr>(this->input_type);
    return int_type->get_bits();
}
std::size_t IntToMaskInst::get_output_mask_size() const{
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType IntToMaskInst::get_inst_type() const{
    return InstType::IntToMaskInst;
}
std::string IntToMaskInst::to_string() const{
    return "let " + this->destination->to_string() + " = .int_to_mask(" + this->input->to_string() + ")";
}
}
}
