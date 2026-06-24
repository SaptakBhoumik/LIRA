#include "mir/instruction/simd_inst.hpp"
#include <string>

namespace LIRA {
namespace MIR {
//--------------------------------- Uncategorized SIMD Instructions ---------------------------------
ShuffleVectorInst::ShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                                   std::size_t vec1_elm_count, std::size_t vec2_elm_count, std::optional<FastMathAttr> fast_math_attr)
                                   :Inst(instruction_stmt,destination,fast_math_attr) {
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
    if(this->fast_math_attr.has_value()) {
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
                                         :ShuffleVectorInst(instruction_stmt,destination,vector1,vector2,mask,vec1_elm_count,vec2_elm_count,std::nullopt) {}
std::shared_ptr<IR::IntTypeExpr> IntShuffleVectorInst::get_casted_basetype() const {
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_basetype());
}
std::size_t IntShuffleVectorInst::get_basetype_bitwidth() const {
    return this->get_casted_basetype()->get_bits();
}
TypeVarient IntShuffleVectorInst::get_basetype_varient() const {
    return TypeVarient::Int;
}
std::string IntShuffleVectorInst::to_string() const {
    return this->to_string_helper("int_shuffle_vector");
}


PtrShuffleVectorInst::PtrShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                                         std::size_t vec1_elm_count, std::size_t vec2_elm_count)
                                         :ShuffleVectorInst(instruction_stmt,destination,vector1,vector2,mask,vec1_elm_count,vec2_elm_count,std::nullopt) {}
std::size_t PtrShuffleVectorInst::get_basetype_bitwidth() const {
    return 64;
}
TypeVarient PtrShuffleVectorInst::get_basetype_varient() const {
    return TypeVarient::Ptr;
}
std::string PtrShuffleVectorInst::to_string() const {
    return this->to_string_helper("ptr_shuffle_vector");
}


FloatShuffleVectorInst::FloatShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                                             std::size_t vec1_elm_count, std::size_t vec2_elm_count, FastMathAttr fast_math_attr)
                                             :ShuffleVectorInst(instruction_stmt,destination,vector1,vector2,mask,vec1_elm_count,vec2_elm_count,fast_math_attr) {}
std::shared_ptr<IR::FloatTypeExpr> FloatShuffleVectorInst::get_casted_basetype() const {
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_basetype());
}
std::size_t FloatShuffleVectorInst::get_basetype_bitwidth() const {
    return this->get_casted_basetype()->get_bits();
}
bool FloatShuffleVectorInst::is_basetype_brain_float() const {
    return this->get_casted_basetype()->is_brain_float();
}
TypeVarient FloatShuffleVectorInst::get_basetype_varient() const {
    return TypeVarient::Float;
}
std::string FloatShuffleVectorInst::to_string() const {
    return this->to_string_helper("float_shuffle_vector");
}


TernLogInst::TernLogInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr a, IR::LiteralExprPtr b, IR::LiteralExprPtr c, 
                         IR::LiteralExprPtr imm):Inst(instruction_stmt, destination, std::nullopt){
    this->a = a;
    this->b = b;
    this->c = c;
    this->imm = imm;
}
IR::LiteralExprPtr TernLogInst::get_a() const {
    return this->a;
}
IR::LiteralExprPtr TernLogInst::get_b() const {
    return this->b;
}
IR::LiteralExprPtr TernLogInst::get_c() const {
    return this->c;
}
IR::LiteralExprPtr TernLogInst::get_imm() const {
    return this->imm;
}
std::size_t TernLogInst::get_vector_size() const {
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType TernLogInst::get_inst_type() const {
    return InstType::TernLogInst;
}
std::string TernLogInst::to_string() const {
    std::string vec_type = this->destination->get_type()->to_string() + ":";
    std::string str = "let " + this->destination->to_string() + " = .tern_log(" + vec_type + this->a->to_string() + ", " 
                                                                                   + this->b->to_string() + ", " 
                                                                                   + this->c->to_string() + ", i8:"
                                                                                   + this->imm->to_string() + ")";
    return str;
}


SplatInst::SplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, std::optional<FastMathAttr> fast_math_attr)
                     :Inst(instruction_stmt,destination,fast_math_attr) {
    this->value = value;
}
std::string SplatInst::to_string_helper(const std::string op_name) const{
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + this->get_element_type()->to_string() + ":" + this->value->to_string() + ")";
    if(this->fast_math_attr.has_value()) {
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr SplatInst::get_value() const {
    return this->value;
}
IR::TypeExprPtr SplatInst::get_element_type() const {
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::size_t SplatInst::get_vector_size() const {
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType SplatInst::get_inst_type() const {
    return InstType::SplatInst;
}

IntSplatInst::IntSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                     :SplatInst(instruction_stmt,destination,value,std::nullopt) {}
std::shared_ptr<IR::IntTypeExpr> IntSplatInst::get_casted_element_type() const {
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntSplatInst::get_element_bitwidth() const {
    return this->get_casted_element_type()->get_bits();
}
TypeVarient IntSplatInst::get_element_type_varient() const  {
    return TypeVarient::Int;
}
std::string IntSplatInst::to_string() const {
    return this->to_string_helper("int_splat");
}


PtrSplatInst::PtrSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value)
                     :SplatInst(instruction_stmt,destination,value,std::nullopt) {}
std::size_t PtrSplatInst::get_element_bitwidth() const {
    return 64;
}
TypeVarient PtrSplatInst::get_element_type_varient() const  {
    return TypeVarient::Ptr;
}
std::string PtrSplatInst::to_string() const {
    return this->to_string_helper("ptr_splat");
}


FloatSplatInst::FloatSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr)
                     :SplatInst(instruction_stmt,destination,value,fast_math_attr) {}
std::shared_ptr<IR::FloatTypeExpr> FloatSplatInst::get_casted_element_type() const {
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatSplatInst::get_element_bitwidth() const {
    return this->get_casted_element_type()->get_bits();
}
bool FloatSplatInst::is_brain_float() const {
    return this->get_casted_element_type()->is_brain_float();
}
TypeVarient FloatSplatInst::get_element_type_varient() const  {
    return TypeVarient::Float;
}
std::string FloatSplatInst::to_string() const {
    return this->to_string_helper("float_splat");
}


StepVectorInst::StepVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr start, IR::LiteralExprPtr step, 
                               std::optional<FastMathAttr> fast_math_attr)
                               :Inst(instruction_stmt,destination,fast_math_attr) {
    this->start = start;
    this->step = step;
}
std::string StepVectorInst::to_string_helper(const std::string op_name) const{
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + this->get_element_type()->to_string() + ":" + this->start->to_string() + ", " 
                                                                                       + this->get_element_type()->to_string() + ":" + this->step->to_string() + ")";
    if(this->fast_math_attr.has_value()) {
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
                         :StepVectorInst(instruction_stmt,destination,start,step,std::nullopt) {}
std::shared_ptr<IR::IntTypeExpr> IntStepVectorInst::get_casted_element_type() const {
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntStepVectorInst::get_element_bitwidth() const {
    return this->get_casted_element_type()->get_bits();
}
TypeVarient IntStepVectorInst::get_element_type_varient() const  {
    return TypeVarient::Int;
}
std::string IntStepVectorInst::to_string() const {
    return this->to_string_helper("int_step_vector");
}


FloatStepVectorInst::FloatStepVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr start, IR::LiteralExprPtr step, 
                             FastMathAttr fast_math_attr)
                             :StepVectorInst(instruction_stmt,destination,start,step,fast_math_attr) {}
std::shared_ptr<IR::FloatTypeExpr> FloatStepVectorInst::get_casted_element_type() const {
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatStepVectorInst::get_element_bitwidth() const {
    return this->get_casted_element_type()->get_bits();
}
bool FloatStepVectorInst::is_brain_float() const {
    return this->get_casted_element_type()->is_brain_float();
}
TypeVarient FloatStepVectorInst::get_element_type_varient() const  {
    return TypeVarient::Float;
}
std::string FloatStepVectorInst::to_string() const {
    return this->to_string_helper("float_step_vector");
}


InsertSubVectorInst::InsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size, std::optional<FastMathAttr> fast_math_attr)
                                         :Inst(instruction_stmt,destination,fast_math_attr) {
    this->vector = vector;
    this->subvector = subvector;
    this->index = index;
    this->subvector_size = subvector_size;
}
std::string InsertSubVectorInst::to_string_helper(const std::string op_name) const {
    std::string vec_type = this->destination->get_type()->to_string() + ":";
    std::string subvec_type = "<" + this->get_element_type()->to_string() + "," + std::to_string(this->subvector_size) + ">:";
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + this->vector->to_string() + ", " 
                                                                                       + this->subvector->to_string() + ", i64" 
                                                                                       + this->index->to_string() + ")";
    if(this->fast_math_attr.has_value()) {
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
IR::TypeExprPtr InsertSubVectorInst::get_element_type() const {
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
InstType InsertSubVectorInst::get_inst_type() const {
    return InstType::InsertSubVectorInst;
}


IntInsertSubVectorInst::IntInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size)
                                         :InsertSubVectorInst(instruction_stmt,destination,vector,subvector,index,subvector_size,std::nullopt) {}
std::shared_ptr<IR::IntTypeExpr> IntInsertSubVectorInst::get_casted_element_type() const {
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntInsertSubVectorInst::get_element_bitwidth() const {
    return this->get_casted_element_type()->get_bits();
}
TypeVarient IntInsertSubVectorInst::get_element_type_varient() const  {
    return TypeVarient::Int;
}
std::string IntInsertSubVectorInst::to_string() const {
    return this->to_string_helper("int_insert_subvector");
}


PtrInsertSubVectorInst::PtrInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size)
                                         :InsertSubVectorInst(instruction_stmt,destination,vector,subvector,index,subvector_size,std::nullopt) {}
std::size_t PtrInsertSubVectorInst::get_element_bitwidth() const {
    return 64;
}
TypeVarient PtrInsertSubVectorInst::get_element_type_varient() const  {
    return TypeVarient::Ptr;
}
std::string PtrInsertSubVectorInst::to_string() const {
    return this->to_string_helper("ptr_insert_subvector");
}

FloatInsertSubVectorInst::FloatInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size, FastMathAttr fast_math_attr)
                                         :InsertSubVectorInst(instruction_stmt,destination,vector,subvector,index,subvector_size,fast_math_attr) {}
std::shared_ptr<IR::FloatTypeExpr> FloatInsertSubVectorInst::get_casted_element_type() const {
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatInsertSubVectorInst::get_element_bitwidth() const {
    return this->get_casted_element_type()->get_bits();
}
bool FloatInsertSubVectorInst::is_brain_float() const {
    return this->get_casted_element_type()->is_brain_float();
}
TypeVarient FloatInsertSubVectorInst::get_element_type_varient() const  {
    return TypeVarient::Float;
}
std::string FloatInsertSubVectorInst::to_string() const {
    return this->to_string_helper("float_insert_subvector");
}


ExtractSubVectorInst::ExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr index, std::size_t vector_size, std::optional<FastMathAttr> fast_math_attr)
                                         :Inst(instruction_stmt,destination,fast_math_attr) {
    this->vector = vector;
    this->index = index;
    this->vector_size = vector_size;
}
std::string ExtractSubVectorInst::to_string_helper(const std::string op_name) const{
    std::string vec_type = "<" + this->get_element_type()->to_string() + "," + std::to_string(this->vector_size) + ">:";
    std::string str = "let " + this->destination->to_string() + " = ." + op_name + "(" + vec_type + this->vector->to_string() + ", i64:" 
                                                                                       + this->index->to_string() + ")";
    if(this->fast_math_attr.has_value()) {
        str += " " + this->fast_math_attr.value().to_string();
    }
    return str;
}
IR::LiteralExprPtr ExtractSubVectorInst::get_vector() const {
    return this->vector;
}
IR::LiteralExprPtr ExtractSubVectorInst::get_index() const {
    return this->index;
}
std::size_t ExtractSubVectorInst::get_vector_size() const {
    return this->vector_size;
}
IR::TypeExprPtr ExtractSubVectorInst::get_element_type() const {
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_basetype();
}
std::size_t ExtractSubVectorInst::get_subvector_size() const {
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType ExtractSubVectorInst::get_inst_type() const {
    return InstType::ExtractSubVectorInst;
}


IntExtractSubVectorInst::IntExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr index, std::size_t vector_size)
                                         :ExtractSubVectorInst(instruction_stmt,destination,vector,index,vector_size,std::nullopt) {}
std::shared_ptr<IR::IntTypeExpr> IntExtractSubVectorInst::get_casted_element_type() const {
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntExtractSubVectorInst::get_element_bitwidth() const {
    return this->get_casted_element_type()->get_bits();
}
TypeVarient IntExtractSubVectorInst::get_element_type_varient() const  {
    return TypeVarient::Int;
}
std::string IntExtractSubVectorInst::to_string() const {
    return this->to_string_helper("int_extract_subvector");
}


PtrExtractSubVectorInst::PtrExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr index, std::size_t vector_size)
                                         :ExtractSubVectorInst(instruction_stmt,destination,vector,index,vector_size,std::nullopt) {}
std::size_t PtrExtractSubVectorInst::get_element_bitwidth() const {
    return 64;
}
TypeVarient PtrExtractSubVectorInst::get_element_type_varient() const  {
    return TypeVarient::Ptr;
}
std::string PtrExtractSubVectorInst::to_string() const {
    return this->to_string_helper("ptr_extract_subvector");
}


FloatExtractSubVectorInst::FloatExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                         IR::LiteralExprPtr index, std::size_t vector_size, FastMathAttr fast_math_attr)
                                         :ExtractSubVectorInst(instruction_stmt,destination,vector,index,vector_size,fast_math_attr) {}
std::shared_ptr<IR::FloatTypeExpr> FloatExtractSubVectorInst::get_casted_element_type() const {
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatExtractSubVectorInst::get_element_bitwidth() const {
    return this->get_casted_element_type()->get_bits();
}
bool FloatExtractSubVectorInst::is_brain_float() const {
    return this->get_casted_element_type()->is_brain_float();
}
TypeVarient FloatExtractSubVectorInst::get_element_type_varient() const  {
    return TypeVarient::Float;
}
std::string FloatExtractSubVectorInst::to_string() const {
    return this->to_string_helper("float_extract_subvector");
}


ActiveLaneMaskInst::ActiveLaneMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr base, IR::LiteralExprPtr count, 
                                        IR::TypeExprPtr type, bool unsigned_):Inst(instruction_stmt,destination,std::nullopt) {
    this->base = base;
    this->count = count;
    this->type = type;
    this->unsigned_ = unsigned_;
}
IR::LiteralExprPtr ActiveLaneMaskInst::get_base() const {
    return this->base;
}
IR::LiteralExprPtr ActiveLaneMaskInst::get_count() const {
    return this->count;
}
std::shared_ptr<IR::IntTypeExpr> ActiveLaneMaskInst::get_casted_type() const {
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->type);
}
std::size_t ActiveLaneMaskInst::get_type_bitwidth() const {
    return this->get_casted_type()->get_bits();
}
std::size_t ActiveLaneMaskInst::get_vector_size() const {
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size(); 
}
bool ActiveLaneMaskInst::is_unsigned() const {
    return this->unsigned_;
}
InstType ActiveLaneMaskInst::get_inst_type() const {
    return InstType::ActiveLaneMaskInst;
}
std::string ActiveLaneMaskInst::to_string() const {
    std::string type_str = this->type->to_string() + ":";
    std::string str = "let " + this->destination->to_string() + " = .active_lane_mask(" + type_str + this->base->to_string() + ", "
                                                                                             + type_str + this->count->to_string() + ")";
    if(this->unsigned_) {
        str += " #[unsigned]";
    }
    return str;
}


AddSubInst::AddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                       std::optional<FastMathAttr> fast_math_attr):Inst(instruction_stmt,destination,fast_math_attr) {
    this->lhs = lhs;
    this->rhs = rhs;  
}
IR::LiteralExprPtr AddSubInst::get_lhs() const {
    return this->lhs;
}
IR::LiteralExprPtr AddSubInst::get_rhs() const {
    return this->rhs;
}
IR::TypeExprPtr AddSubInst::get_element_type() const{
    return this->destination->get_type();
}
size_t AddSubInst::get_vector_size() const {
    auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(this->destination->get_type());
    return simd_type->get_size();
}
InstType AddSubInst::get_inst_type() const {
    return InstType::AddSubInst;
}


IntAddSubInst::IntAddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                             bool nuw, bool nsw, bool unsigned_, bool saturating):AddSubInst(instruction_stmt,destination,lhs,rhs,std::nullopt) {}
std::shared_ptr<IR::IntTypeExpr> IntAddSubInst::get_casted_element_type() const {
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_element_type());
}
std::size_t IntAddSubInst::get_element_bitwidth() const {
    return this->get_casted_element_type()->get_bits();
}
bool IntAddSubInst::is_nuw() const {
    return this->nuw;
}
bool IntAddSubInst::is_nsw() const {
    return this->nsw;
}
bool IntAddSubInst::is_unsigned() const {
    return this->unsigned_;
}
bool IntAddSubInst::is_saturating() const {
    return this->saturating;
}
TypeVarient IntAddSubInst::get_element_type_varient() const {
    return TypeVarient::Int;
}
std::string IntAddSubInst::to_string() const {
    std::string str = "let " + this->destination->to_string() + " = .int_addsub(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->nuw) {
        str += " #[nuw]";
    }
    if(this->nsw) {
        str += " #[nsw]";
    }
    if(this->unsigned_) {
        str += " #[unsigned]";
    }
    if(this->saturating) {
        str += " #[saturating]";
    }
    return str;
}


FloatAddSubInst::FloatAddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                                 FastMathAttr fast_math_attr):AddSubInst(instruction_stmt,destination,lhs,rhs,std::nullopt) {}
std::shared_ptr<IR::FloatTypeExpr> FloatAddSubInst::get_casted_element_type() const {
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(this->get_element_type());
}
std::size_t FloatAddSubInst::get_element_bitwidth() const {
    return this->get_casted_element_type()->get_bits();
}
bool FloatAddSubInst::is_brain_float_type() const {
    return this->get_casted_element_type()->is_brain_float();
}
TypeVarient FloatAddSubInst::get_element_type_varient() const {
    return TypeVarient::Float;
}
std::string FloatAddSubInst::to_string() const {
    std::string res =  "let " + this->destination->to_string() + " = .float_addsub(" + this->lhs->to_string() + ", " + this->rhs->to_string() + ")";
    if(this->fast_math_attr.has_value()) {
        res += " " + this->fast_math_attr.value().to_string();
    }
    return res;
}
}
}
