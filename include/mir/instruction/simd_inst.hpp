#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <cstddef>
namespace LIRA {
namespace MIR {
//--------------------------------- Uncategorized SIMD Instructions ---------------------------------
class ShuffleVectorInst:public Inst {
    protected:
    IR::LiteralExprPtr vector1;
    IR::LiteralExprPtr vector2;
    IR::LiteralExprPtr mask;
    std::size_t vec1_elm_count;
    std::size_t vec2_elm_count;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    ShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                      std::size_t vec1_elm_count, std::size_t vec2_elm_count, std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_vector1() const final;
    virtual IR::LiteralExprPtr get_vector2() const final;
    virtual IR::LiteralExprPtr get_mask() const final;

    virtual IR::TypeExprPtr get_basetype() const final;//Base type of vector1,vector2 and output
    virtual TypeVariant get_basetype_variant() const = 0;
    virtual std::size_t get_vec1_elm_count() const final;
    virtual std::size_t get_vec2_elm_count() const final;
    virtual std::size_t get_mask_elm_count() const final;


    virtual InstType get_inst_type() const override final;
};

class IntShuffleVectorInst:public ShuffleVectorInst {
    public:
    IntShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                           std::size_t vec1_elm_count, std::size_t vec2_elm_count);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_basetype() const;
    std::size_t get_basetype_bitwidth() const;

    TypeVariant get_basetype_variant() const override;
    std::string to_string() const override;
};

class PtrShuffleVectorInst:public ShuffleVectorInst {
    public:
    PtrShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                           std::size_t vec1_elm_count, std::size_t vec2_elm_count);
    
    std::size_t get_basetype_bitwidth() const;

    TypeVariant get_basetype_variant() const override;
    std::string to_string() const override;
};

class FloatShuffleVectorInst:public ShuffleVectorInst {
    public:
    FloatShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                             std::size_t vec1_elm_count, std::size_t vec2_elm_count, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_basetype() const;
    std::size_t get_basetype_bitwidth() const;
    bool is_basetype_brain_float() const;

    TypeVariant get_basetype_variant() const override;
    std::string to_string() const override;
};

class TernLogInst:public Inst {
    IR::LiteralExprPtr a;
    IR::LiteralExprPtr b;
    IR::LiteralExprPtr c;
    IR::LiteralExprPtr imm;

    public: 
    TernLogInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr a, IR::LiteralExprPtr b, IR::LiteralExprPtr c, 
                IR::LiteralExprPtr imm);
    
    IR::LiteralExprPtr get_a() const;
    IR::LiteralExprPtr get_b() const;
    IR::LiteralExprPtr get_c() const;
    IR::LiteralExprPtr get_imm() const;

    std::size_t get_vector_size() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class SplatInst:public Inst {
    protected:
    IR::LiteralExprPtr value;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    SplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, std::optional<FastMathAttr> fast_math_attr);
    
    virtual IR::LiteralExprPtr get_value() const final;
    virtual IR::TypeExprPtr get_element_type() const final;//From destination
    virtual std::size_t get_vector_size() const final;//From destination
    
    virtual TypeVariant get_element_type_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntSplatInst:public SplatInst {
    public:
    IntSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    
    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class PtrSplatInst:public SplatInst {
    public:
    PtrSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);
    
    std::size_t get_element_bitwidth() const;
    
    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class FloatSplatInst:public SplatInst {
    public:
    FloatSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_brain_float() const;
    
    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class StepVectorInst:public Inst {
    protected:
    IR::LiteralExprPtr start;
    IR::LiteralExprPtr step;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    StepVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr start, IR::LiteralExprPtr step, 
                   std::optional<FastMathAttr> fast_math_attr);
    
    virtual IR::LiteralExprPtr get_start() const final;
    virtual IR::LiteralExprPtr get_step() const final;
    virtual IR::TypeExprPtr get_element_type() const final;//From destination
    virtual std::size_t get_vector_size() const final;//From destination
    
    virtual TypeVariant get_element_type_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntStepVectorInst:public StepVectorInst {
    public:
    IntStepVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr start, IR::LiteralExprPtr step);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    
    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class FloatStepVectorInst:public StepVectorInst {
    public:
    FloatStepVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr start, IR::LiteralExprPtr step, 
                        FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_brain_float() const;
    
    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class InsertSubVectorInst:public Inst {
    protected:
    IR::LiteralExprPtr vector;
    IR::LiteralExprPtr subvector;
    std::size_t subvector_size;
    IR::LiteralExprPtr index;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    InsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                        IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size, std::optional<FastMathAttr> fast_math_attr);
    
    virtual IR::LiteralExprPtr get_vector() const final;
    virtual IR::LiteralExprPtr get_subvector() const final;
    virtual IR::LiteralExprPtr get_index() const final;
    virtual IR::TypeExprPtr get_element_type() const final;//From destination. Type of elements of vector and subvector
    virtual std::size_t get_vector_size() const final;//From destination. Size of destination and original vector
    virtual std::size_t get_subvector_size() const final;

    virtual TypeVariant get_element_type_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntInsertSubVectorInst:public InsertSubVectorInst {
    public:
    IntInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                           IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class PtrInsertSubVectorInst:public InsertSubVectorInst {
    public:
    PtrInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                           IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size);
    
    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class FloatInsertSubVectorInst:public InsertSubVectorInst {
    public:
    FloatInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                             IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_brain_float() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class ExtractSubVectorInst:public Inst {
    protected:
    IR::LiteralExprPtr vector;
    std::size_t vector_size;
    IR::LiteralExprPtr index;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    ExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                         IR::LiteralExprPtr index, std::size_t vector_size, std::optional<FastMathAttr> fast_math_attr);
    
    virtual IR::LiteralExprPtr get_vector() const final;
    virtual IR::LiteralExprPtr get_index() const final;
    virtual IR::TypeExprPtr get_element_type() const final;//From destination. Type of elements of vector and subvector
    virtual std::size_t get_vector_size() const final;
    virtual std::size_t get_subvector_size() const final;//From destination. Size of extracted subvector

    virtual TypeVariant get_element_type_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntExtractSubVectorInst:public ExtractSubVectorInst {
    public:
    IntExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                            IR::LiteralExprPtr index, std::size_t vector_size);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class PtrExtractSubVectorInst:public ExtractSubVectorInst {
    public:
    PtrExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                            IR::LiteralExprPtr index, std::size_t vector_size);
    
    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class FloatExtractSubVectorInst:public ExtractSubVectorInst {
    public:
    FloatExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                              IR::LiteralExprPtr index, std::size_t vector_size, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_brain_float() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class ActiveLaneMaskInst:public Inst {
    IR::LiteralExprPtr base;
    IR::LiteralExprPtr count;
    IR::TypeExprPtr type;//Type of base and count

    bool unsigned_;
    public:
    ActiveLaneMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr base, IR::LiteralExprPtr count, 
                       IR::TypeExprPtr type, bool unsigned_);
    
    IR::LiteralExprPtr get_base() const;
    IR::LiteralExprPtr get_count() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_type() const;
    std::size_t get_type_bitwidth() const;
    std::size_t get_vector_size() const;//From destination of type <i1,N>. We want N 

    bool is_unsigned() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class AddSubInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;

    public:
    AddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
               std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual IR::TypeExprPtr get_element_type() const final;//From destination
    virtual size_t get_vector_size() const final;//From destination
    
    virtual TypeVariant get_element_type_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntAddSubInst:public AddSubInst{
    bool nuw;
    bool nsw;
    bool unsigned_;
    bool saturating;
    public:
    IntAddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                  bool nuw, bool nsw, bool unsigned_, bool saturating);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    bool is_nuw() const;
    bool is_nsw() const;
    bool is_unsigned() const;
    bool is_saturating() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class FloatAddSubInst:public AddSubInst{
    public:
    FloatAddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                    FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_element_brain_float_type() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};
//--------------------------------- Reduce SIMD Instructions ---------------------------------
//----------------------- Reduce Arithmetic SIMD Instructions -----------------------
class ReduceArithmeticSIMDInst:public Inst {
    protected:
    IR::LiteralExprPtr vector;
    IR::LiteralExprPtr mask;//Optional. May be nullptr if not used
    std::size_t vector_size;

    public:
    enum class OpType:std::uint64_t{
        REDUCE_ADD = 1 << 6,
        REDUCE_MUL = 1 << 7,
        REDUCE_AVG = 1 << 8,
        REDUCE_MIN = 1 << 9,
        REDUCE_MAX = 1 << 10,
    };
    ReduceArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                             IR::LiteralExprPtr mask, std::size_t vector_size, std::optional<FastMathAttr> fast_math_attr);
    
    virtual IR::LiteralExprPtr get_vector() const final;
    virtual IR::LiteralExprPtr get_mask() const final;
    virtual std::size_t get_vector_size() const final;
    virtual IR::TypeExprPtr get_element_type() const final;//From destination

    virtual TypeVariant get_element_type_variant() const = 0;
    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};

//--------------------------------- Int Reduce Arithmetic SIMD Instructions ---------------------------------
class IntReduceArithmeticSIMDInst:public ReduceArithmeticSIMDInst {
    protected:
    bool nuw;
    bool nsw;
    bool unsigned_;
    bool saturating;
    bool floor;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    IntReduceArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                IR::LiteralExprPtr mask, std::size_t vector_size, bool nuw, bool nsw, bool unsigned_, bool saturating, bool floor);
    
    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const final;
    virtual std::size_t get_element_bitwidth() const final;

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_unsigned() const final;
    virtual bool is_saturating() const final;
    virtual bool is_floor() const final;

    virtual TypeVariant get_element_type_variant() const override final;
};

class IntReduceAddInst:public IntReduceArithmeticSIMDInst {
    public:
    IntReduceAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                      IR::LiteralExprPtr mask, std::size_t vector_size, bool nuw, bool nsw, bool unsigned_, bool saturating);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntReduceMulInst:public IntReduceArithmeticSIMDInst {
    public:
    IntReduceMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                      IR::LiteralExprPtr mask, std::size_t vector_size, bool nuw, bool nsw, bool unsigned_, bool saturating);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntReduceAvgInst:public IntReduceArithmeticSIMDInst {
    public:
    IntReduceAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                     IR::LiteralExprPtr mask, std::size_t vector_size, bool nuw, bool nsw, bool unsigned_, bool floor);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntReduceMinInst:public IntReduceArithmeticSIMDInst {
    public:
    IntReduceMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                     IR::LiteralExprPtr mask, std::size_t vector_size, bool unsigned_);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntReduceMaxInst:public IntReduceArithmeticSIMDInst {
    public:
    IntReduceMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                     IR::LiteralExprPtr mask, std::size_t vector_size, bool unsigned_);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

//--------------------------------- Float Reduce Arithmetic SIMD Instructions ---------------------------------
class FloatReduceArithmeticSIMDInst:public ReduceArithmeticSIMDInst {
    protected:
    bool ieee754_2019;
    bool unordered;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    FloatReduceArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                                  IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered);
    
    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const final;
    virtual std::size_t get_element_bitwidth() const final;
    virtual bool is_element_brain_float_type() const final;

    virtual bool is_ieee754_2019() const final;
    virtual bool is_unordered() const final;

    virtual TypeVariant get_element_type_variant() const override final;
};
 
class FloatReduceAddInst:public FloatReduceArithmeticSIMDInst {
    public:
    FloatReduceAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                       IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatReduceMulInst:public FloatReduceArithmeticSIMDInst {
    public:
    FloatReduceMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                       IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatReduceAvgInst:public FloatReduceArithmeticSIMDInst {
    public:
    FloatReduceAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                       IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatReduceMinInst:public FloatReduceArithmeticSIMDInst {
    public:
    FloatReduceMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                       IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatReduceMaxInst:public FloatReduceArithmeticSIMDInst {
    public:
    FloatReduceMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                       IR::LiteralExprPtr mask, std::size_t vector_size, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

    
//--------------------------------- Int Reduce Bitwise SIMD Instructions ---------------------------------
class IntReduceBitwiseSIMDInst:public Inst {
    protected:
    IR::LiteralExprPtr vector;
    IR::LiteralExprPtr mask;//Optional. May be nullptr if not used
    std::size_t vector_size;
    bool disjoint;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    enum class OpType:std::uint64_t{
        REDUCE_AND = 1 << 6,
        REDUCE_OR = 1 << 7,
        REDUCE_XOR = 1 << 8,
        REDUCE_XNOR = 1 << 9,
    };
    IntReduceBitwiseSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                             IR::LiteralExprPtr mask, std::size_t vector_size, bool disjoint);
    
    virtual IR::LiteralExprPtr get_vector() const final;
    virtual IR::LiteralExprPtr get_mask() const final;
    virtual std::size_t get_vector_size() const final;
    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const final;//From destination
    virtual std::size_t get_element_bitwidth() const final;
    virtual bool is_disjoint() const final;

    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntReduceAndInst:public IntReduceBitwiseSIMDInst {
    public:
    IntReduceAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                     IR::LiteralExprPtr mask, std::size_t vector_size);

    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntReduceOrInst:public IntReduceBitwiseSIMDInst {
    public:
    IntReduceOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                    IR::LiteralExprPtr mask, std::size_t vector_size, bool disjoint);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntReduceXorInst:public IntReduceBitwiseSIMDInst {
    public:
    IntReduceXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                     IR::LiteralExprPtr mask, std::size_t vector_size);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntReduceXnorInst:public IntReduceBitwiseSIMDInst {
    public:
    IntReduceXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                      IR::LiteralExprPtr mask, std::size_t vector_size);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

//--------------------------------- Horizontal SIMD Instructions ---------------------------------
//---------------- Horizontal Arithmetic SIMD Instructions ----------------
class HArithmeticSIMDInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;

    public:
    enum class OpType:std::uint64_t{
        HADD = 1 << 6,
        HSUB = 1 << 7,
        HABSDIFF = 1 << 8,
        HADDSUB = 1 << 9,
        HMUL = 1 << 10,
        HAVG = 1 << 11,
        HMIN = 1 << 12,
        HMAX = 1 << 13,
    };
    HArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                       std::optional<FastMathAttr> fast_math_attr);
    
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual IR::TypeExprPtr get_element_type() const final;//From destination
    virtual std::size_t get_vector_size() const final;//From destination

    virtual TypeVariant get_element_type_variant() const = 0;
    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};

//---------------- Int Horizontal Arithmetic SIMD Instructions ----------------
class IntHArithmeticSIMDInst:public HArithmeticSIMDInst {
    protected:
    bool nuw;
    bool nsw;
    bool unsigned_;
    bool saturating;
    bool floor;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    IntHArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                           bool nuw, bool nsw, bool unsigned_, bool saturating, bool floor);
    
    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const final;
    virtual std::size_t get_element_bitwidth() const final;

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_unsigned() const final;
    virtual bool is_saturating() const final;
    virtual bool is_floor() const final;

    virtual TypeVariant get_element_type_variant() const override;
};

class IntHorizontalAddInst:public IntHArithmeticSIMDInst {
    public:
    IntHorizontalAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw, bool unsigned_, bool saturating);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalSubInst:public IntHArithmeticSIMDInst {
    public:
    IntHorizontalSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw, bool unsigned_, bool saturating);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalAbsDiffInst:public IntHArithmeticSIMDInst {
    public:
    IntHorizontalAbsDiffInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                             bool nuw, bool nsw, bool unsigned_, bool saturating);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalAddSubInst:public IntHArithmeticSIMDInst {
    public:
    IntHorizontalAddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                            bool nuw, bool nsw, bool unsigned_, bool saturating);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalMulInst:public IntHArithmeticSIMDInst {
    public:
    IntHorizontalMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                         bool nuw, bool nsw, bool unsigned_, bool saturating);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalAvgInst:public IntHArithmeticSIMDInst {
    public:
    IntHorizontalAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool nuw, bool nsw, bool unsigned_, bool floor);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalMinInst:public IntHArithmeticSIMDInst {
    public:
    IntHorizontalMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool unsigned_);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalMaxInst:public IntHArithmeticSIMDInst {
    public:
    IntHorizontalMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool unsigned_);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

//---------------- Float Horizontal Arithmetic SIMD Instructions ----------------
class FloatHArithmeticSIMDInst:public HArithmeticSIMDInst {
    protected:
    bool ieee754_2019;
    bool unordered;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    FloatHArithmeticSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                             FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered);
    
    virtual std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const final;
    virtual std::size_t get_element_bitwidth() const final;
    virtual bool is_element_brain_float_type() const final;

    virtual bool is_ieee754_2019() const final;
    virtual bool is_unordered() const final;

    virtual TypeVariant get_element_type_variant() const override;
};

class FloatHorizontalAddInst:public FloatHArithmeticSIMDInst {
    public:
    FloatHorizontalAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                           FastMathAttr fast_math_attr);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatHorizontalSubInst:public FloatHArithmeticSIMDInst {
    public:
    FloatHorizontalSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                           FastMathAttr fast_math_attr);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatHorizontalAbsDiffInst:public FloatHArithmeticSIMDInst {
    public:
    FloatHorizontalAbsDiffInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                               FastMathAttr fast_math_attr);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatHorizontalAddSubInst:public FloatHArithmeticSIMDInst {
    public:
    FloatHorizontalAddSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                              FastMathAttr fast_math_attr);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatHorizontalMulInst:public FloatHArithmeticSIMDInst {
    public:
    FloatHorizontalMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                           FastMathAttr fast_math_attr);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatHorizontalAvgInst:public FloatHArithmeticSIMDInst {
    public:
    FloatHorizontalAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                           FastMathAttr fast_math_attr);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatHorizontalMinInst:public FloatHArithmeticSIMDInst {
    public:
    FloatHorizontalMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                            FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class FloatHorizontalMaxInst:public FloatHArithmeticSIMDInst {
    public:
    FloatHorizontalMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                            FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

//---------------- Int Horizontal Bitwise SIMD Instructions ----------------
class IntHBitwiseSIMDInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    bool disjoint;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    enum class OpType:std::uint64_t{
        HAND = 1 << 6,
        HNAND = 1 << 7,
        HOR = 1 << 8,
        HNOR = 1 << 9,
        HXOR = 1 << 10,
        HXNOR = 1 << 11,
    };
    IntHBitwiseSIMDInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                       bool disjoint);
    
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual std::size_t get_vector_size() const final;//From destination
    virtual std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const final;//From destination
    virtual std::size_t get_element_bitwidth() const final;
    virtual bool is_disjoint() const final;

    virtual OpType get_op_type() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntHorizontalAndInst:public IntHBitwiseSIMDInst {
    public:
    IntHorizontalAndInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalNandInst:public IntHBitwiseSIMDInst {
    public:
    IntHorizontalNandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalOrInst:public IntHBitwiseSIMDInst {
    public:
    IntHorizontalOrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                        bool disjoint);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalNorInst:public IntHBitwiseSIMDInst {
    public:
    IntHorizontalNorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                         bool disjoint);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalXorInst:public IntHBitwiseSIMDInst {
    public:
    IntHorizontalXorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

class IntHorizontalXnorInst:public IntHBitwiseSIMDInst {
    public:
    IntHorizontalXnorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs);
    
    OpType get_op_type() const override;
    std::string to_string() const override;
};

//--------------------------------- Dot Product Instructions ---------------------------------
class DotInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::TypeExprPtr input_vector_type;//Type of lhs and rhs. Must be same type

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    DotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr input_vector_type,
            std::optional<FastMathAttr> fast_math_attr);
    
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual IR::TypeExprPtr get_input_basetype() const final;//From input_vector_type
    virtual std::size_t get_vector_size() const final;//From input_vector_type
    virtual IR::TypeExprPtr get_output_type() const final;// From destination

    virtual TypeVariant get_basetype_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntDotInst:public DotInst {
    protected:
    bool nuw;
    bool nsw;
    bool unsigned_;
    bool saturating;
    public:
    IntDotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr input_vector_type,
               bool nuw, bool nsw, bool unsigned_, bool saturating);

    bool is_nuw() const;
    bool is_nsw() const;
    bool is_unsigned() const;
    bool is_saturating() const;
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_input_basetype() const;
    std::size_t get_input_basetype_bitwidth() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_output_type() const;
    std::size_t get_output_bitwidth() const;

    TypeVariant get_basetype_variant() const override;
    std::string to_string() const override;
};

class FloatDotInst:public DotInst {
    public:
    FloatDotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr input_vector_type,
                 FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_input_basetype() const;
    std::size_t get_input_basetype_bitwidth() const;
    bool is_input_basetype_brain_float() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_output_type() const;
    std::size_t get_output_bitwidth() const;
    bool is_output_brain_float() const;

    TypeVariant get_basetype_variant() const override;
    std::string to_string() const override;
};

//--------------------------------- Absolute Difference Instructions ---------------------------------
class SADInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::TypeExprPtr input_vector_type;//Type of lhs and rhs. Must be same type

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    SADInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr input_vector_type,
            std::optional<FastMathAttr> fast_math_attr);
    
    virtual IR::LiteralExprPtr get_lhs() const final;
    virtual IR::LiteralExprPtr get_rhs() const final;
    virtual IR::TypeExprPtr get_input_basetype() const final;//From input_vector_type
    virtual std::size_t get_vector_size() const final;//From input_vector_type
    virtual IR::TypeExprPtr get_output_type() const final;// From destination

    virtual TypeVariant get_basetype_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntSADInst:public SADInst {
    protected:
    bool nuw;
    bool nsw;
    bool unsigned_;
    bool saturating;
    public:
    IntSADInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr input_vector_type,
               bool nuw, bool nsw, bool unsigned_, bool saturating);

    bool is_nuw() const;
    bool is_nsw() const;
    bool is_unsigned() const;
    bool is_saturating() const;
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_input_basetype() const;
    std::size_t get_input_basetype_bitwidth() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_output_type() const;
    std::size_t get_output_bitwidth() const;

    TypeVariant get_basetype_variant() const override;
    std::string to_string() const override;
};

class FloatSADInst:public SADInst {
    public:
    FloatSADInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, IR::TypeExprPtr input_vector_type,
                  FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_input_basetype() const;
    std::size_t get_input_basetype_bitwidth() const;
    bool is_input_basetype_brain_float() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_output_type() const;
    std::size_t get_output_bitwidth() const;
    bool is_output_brain_float() const;

    TypeVariant get_basetype_variant() const override;
    std::string to_string() const override;
};


//--------------------------------- Pack / Unpack Instructions ---------------------------------
class PackSatInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::TypeExprPtr input_vector_type;//Type of lhs and rhs.
    
    bool unsigned_;
    public:
    PackSatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                IR::TypeExprPtr input_vector_type, bool unsigned_);
    
    bool is_unsigned() const;

    IR::LiteralExprPtr get_lhs() const;
    IR::LiteralExprPtr get_rhs() const;
    std::size_t get_input_vector_size() const;//From input_vector_type
    std::size_t get_output_vector_size() const;//From destination
    std::shared_ptr<IR::IntTypeExpr> get_casted_input_basetype() const;//From input_vector_type
    std::size_t get_input_basetype_bitwidth() const;//From input_vector_type
    std::shared_ptr<IR::IntTypeExpr> get_casted_output_basetype() const;//From destination
    std::size_t get_output_basetype_bitwidth() const;//From destination

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class UnpackLoInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::TypeExprPtr input_vector_type;//Type of lhs and rhs.
    
    bool unsigned_;
    public:
    UnpackLoInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                 IR::TypeExprPtr input_vector_type, bool unsigned_);
    
    bool is_unsigned() const;

    IR::LiteralExprPtr get_lhs() const;
    IR::LiteralExprPtr get_rhs() const;
    std::size_t get_input_vector_size() const;//From input_vector_type
    std::size_t get_output_vector_size() const;//From destination
    std::shared_ptr<IR::IntTypeExpr> get_casted_input_basetype() const;//From input_vector_type
    std::size_t get_input_basetype_bitwidth() const;//From input_vector_type
    std::shared_ptr<IR::IntTypeExpr> get_casted_output_basetype() const;//From destination
    std::size_t get_output_basetype_bitwidth() const;//From destination

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class UnpackHiInst:public Inst {
    protected:
    IR::LiteralExprPtr lhs;
    IR::LiteralExprPtr rhs;
    IR::TypeExprPtr input_vector_type;//Type of lhs and rhs.
    
    bool unsigned_;
    public:
    UnpackHiInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr lhs, IR::LiteralExprPtr rhs, 
                 IR::TypeExprPtr input_vector_type, bool unsigned_);
    
    bool is_unsigned() const;

    IR::LiteralExprPtr get_lhs() const;
    IR::LiteralExprPtr get_rhs() const;
    std::size_t get_input_vector_size() const;//From input_vector_type
    std::size_t get_output_vector_size() const;//From destination
    std::shared_ptr<IR::IntTypeExpr> get_casted_input_basetype() const;//From input_vector_type
    std::size_t get_input_basetype_bitwidth() const;//From input_vector_type
    std::shared_ptr<IR::IntTypeExpr> get_casted_output_basetype() const;//From destination
    std::size_t get_output_basetype_bitwidth() const;//From destination

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

//--------------------------------- Vector Layout Instructions ---------------------------------
class CompressInst:public Inst {
    protected:
    IR::LiteralExprPtr src;
    IR::LiteralExprPtr mask;
    bool poison_inactive;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    CompressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask,
                 bool poison_inactive, std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_src() const final;
    virtual IR::LiteralExprPtr get_mask() const final;
    virtual bool is_poison_inactive() const final;
    virtual IR::TypeExprPtr get_element_type() const final;//From destination
    virtual std::size_t get_vector_size() const final;//From destination

    virtual TypeVariant get_element_type_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntCompressInst:public CompressInst {
    public:
    IntCompressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask,
                    bool poison_inactive);

    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class PtrCompressInst:public CompressInst {
    public:
    PtrCompressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask,
                    bool poison_inactive);

    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class FloatCompressInst:public CompressInst {
    public:
    FloatCompressInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask,
                      bool poison_inactive, FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_element_brain_float_type() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class ExpandInst:public Inst {
    protected:
    IR::LiteralExprPtr src;
    IR::LiteralExprPtr mask;
    IR::LiteralExprPtr passthru;//May be nullptr
    bool zeropassthru;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    ExpandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask, IR::LiteralExprPtr passthru,
               bool zeropassthru, std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_src() const final;
    virtual IR::LiteralExprPtr get_mask() const final;
    virtual IR::LiteralExprPtr get_passthru() const final;
    virtual bool is_zeropassthru() const final;
    virtual IR::TypeExprPtr get_element_type() const final;//From destination
    virtual std::size_t get_vector_size() const final;//From destination

    virtual TypeVariant get_element_type_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntExpandInst:public ExpandInst {
    public:
    IntExpandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask, IR::LiteralExprPtr passthru,
                  bool zeropassthru);

    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class PtrExpandInst:public ExpandInst {
    public:
    PtrExpandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask, IR::LiteralExprPtr passthru,
                  bool zeropassthru);

    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class FloatExpandInst:public ExpandInst {
    public:
    FloatExpandInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr src, IR::LiteralExprPtr mask, IR::LiteralExprPtr passthru,
                    bool zeropassthru, FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_element_brain_float_type() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class InterleaveInst:public Inst {
    protected:
    std::vector<IR::LiteralExprPtr> args;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    InterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::vector<IR::LiteralExprPtr> args, 
                   std::optional<FastMathAttr> fast_math_attr);

    virtual std::vector<IR::LiteralExprPtr> get_args() const final;
    virtual std::size_t get_interleave_kind() const final;//interleave2 or interleave3 or interleave4. From args.size()
    virtual IR::TypeExprPtr get_element_type() const final;//From destination
    virtual std::size_t get_input_vector_size() const final;//From destination. N/args.size() where N is the size of the destination vector
    virtual std::size_t get_output_vector_size() const final;//From destination. N

    virtual TypeVariant get_element_type_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntInterleaveInst:public InterleaveInst {
    public:
    IntInterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::vector<IR::LiteralExprPtr> args);

    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class PtrInterleaveInst:public InterleaveInst {
    public:
    PtrInterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::vector<IR::LiteralExprPtr> args);

    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class FloatInterleaveInst:public InterleaveInst {
    public:
    FloatInterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, std::vector<IR::LiteralExprPtr> args, 
                        FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_element_brain_float_type() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class DeinterleaveInst:public Inst {
    protected:
    IR::LiteralExprPtr arg;
    IR::TypeExprPtr arg_type;//Type of src. Must be same type as arg
    IR::LiteralExprPtr channel;
    
    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    DeinterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg, IR::TypeExprPtr arg_type, IR::LiteralExprPtr channel,
                     std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_arg() const final;
    virtual IR::LiteralExprPtr get_channel() const final;
    virtual std::size_t get_deinterleave_kind() const final;//deinterleave2 or deinterleave3 or deinterleave4. N1/N2
    virtual IR::TypeExprPtr get_element_type() const final;//From arg_type
    virtual std::size_t get_input_vector_size() const final;//From arg_type. N1 where N1 is the size of the arg_type
    virtual std::size_t get_output_vector_size() const final;//From arg_type. N2 where N2 is the size of destination vector
    
    virtual TypeVariant get_element_type_variant() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntDeinterleaveInst:public DeinterleaveInst {
    public:
    IntDeinterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg, IR::TypeExprPtr arg_type, IR::LiteralExprPtr channel);

    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class PtrDeinterleaveInst:public DeinterleaveInst {
    public:
    PtrDeinterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg, IR::TypeExprPtr arg_type, IR::LiteralExprPtr channel);

    std::size_t get_element_bitwidth() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

class FloatDeinterleaveInst:public DeinterleaveInst {
    public:
    FloatDeinterleaveInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr arg, IR::TypeExprPtr arg_type, IR::LiteralExprPtr channel,
                          FastMathAttr fast_math_attr);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_element_brain_float_type() const;

    TypeVariant get_element_type_variant() const override;
    std::string to_string() const override;
};

//--------------------------------- Lane Mask Conversion Instructions --------------------------------
class MaskToIntInst:public Inst {
    protected:
    IR::LiteralExprPtr mask;
    IR::TypeExprPtr mask_type;
    public:
    MaskToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr mask, IR::TypeExprPtr mask_type);

    IR::LiteralExprPtr get_mask() const;
    std::size_t get_mask_size() const;
    std::size_t get_output_int_bitwidth() const;

    InstType get_inst_type() const override final;
    std::string to_string() const override;
};

class IntToMaskInst:public Inst {
    protected:
    IR::LiteralExprPtr input;
    IR::TypeExprPtr input_type;
    public:
    IntToMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr input, IR::TypeExprPtr input_type);

    IR::LiteralExprPtr get_input() const;
    std::size_t get_input_int_bitwidth() const;
    std::size_t get_output_mask_size() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};
}
}