#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <cstddef>
namespace LIRA {
namespace MIR {
//--------------------------------- Uncategorized SIMD Identification ---------------------------------
class CTShuffleVectorInst:public Inst {
    protected:
    //Compile time varient
    protected:
    IR::LiteralExprPtr vector1;
    IR::LiteralExprPtr vector2;
    std::uint64_t mask;
    std::size_t vec1_elm_count;
    std::size_t vec2_elm_count;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    CTShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, std::uint64_t mask, 
                        std::size_t vec1_elm_count, std::size_t vec2_elm_count, std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_vector1() const final;
    virtual IR::LiteralExprPtr get_vector2() const final;
    virtual std::uint64_t get_mask() const final;

    virtual IR::TypeExprPtr get_basetype() const final;//Base type of vector1,vector2 and output
    virtual TypeVarient get_basetype_varient() const = 0;
    virtual std::size_t get_vec1_elm_count() const final;
    virtual std::size_t get_vec2_elm_count() const final;


    virtual InstType get_inst_type() const override final;
};

class IntCTShuffleVectorInst:public CTShuffleVectorInst {
    public:
    IntCTShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, std::uint64_t mask, 
                           std::size_t vec1_elm_count, std::size_t vec2_elm_count);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_basetype() const;
    std::size_t get_basetype_bitwidth() const;

    TypeVarient get_basetype_varient() const override;
    std::string to_string() const override;
};

class PtrCTShuffleVectorInst:public CTShuffleVectorInst {
    public:
    PtrCTShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, std::uint64_t mask, 
                           std::size_t vec1_elm_count, std::size_t vec2_elm_count);
    
    std::size_t get_basetype_bitwidth() const;

    TypeVarient get_basetype_varient() const override;
    std::string to_string() const override;
};

class FloatCTShuffleVectorInst:public CTShuffleVectorInst {
    public:
    FloatCTShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, std::uint64_t mask, 
                             std::size_t vec1_elm_count, std::size_t vec2_elm_count, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_basetype() const;
    std::size_t get_basetype_bitwidth() const;
    bool is_basetype_brain_float() const;

    TypeVarient get_basetype_varient() const override;
    std::string to_string() const override;
};

class RTShuffleVectorInst:public Inst {
    //Run time varient
    protected:
    IR::LiteralExprPtr vector1;
    IR::LiteralExprPtr vector2;
    IR::LiteralExprPtr mask;
    std::size_t vec1_elm_count;
    std::size_t vec2_elm_count;

    virtual std::string to_string_helper(const std::string op_name) const final;
    public:
    RTShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                        std::size_t vec1_elm_count, std::size_t vec2_elm_count, std::optional<FastMathAttr> fast_math_attr);

    virtual IR::LiteralExprPtr get_vector1() const final;
    virtual IR::LiteralExprPtr get_vector2() const final;
    virtual IR::LiteralExprPtr get_mask() const final;

    virtual IR::TypeExprPtr get_basetype() const final;//Base type of vector1,vector2 and output
    virtual TypeVarient get_basetype_varient() const = 0;
    virtual std::size_t get_vec1_elm_count() const final;
    virtual std::size_t get_vec2_elm_count() const final;


    virtual InstType get_inst_type() const override final;
};

class IntRTShuffleVectorInst:public RTShuffleVectorInst {
    public:
    IntRTShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                           std::size_t vec1_elm_count, std::size_t vec2_elm_count);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_basetype() const;
    std::size_t get_basetype_bitwidth() const;

    TypeVarient get_basetype_varient() const override;
    std::string to_string() const override;
};

class PtrRTShuffleVectorInst:public RTShuffleVectorInst {
    public:
    PtrRTShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                           std::size_t vec1_elm_count, std::size_t vec2_elm_count);
    
    std::size_t get_basetype_bitwidth() const;

    TypeVarient get_basetype_varient() const override;
    std::string to_string() const override;
};

class FloatRTShuffleVectorInst:public RTShuffleVectorInst {
    public:
    FloatRTShuffleVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector1, IR::LiteralExprPtr vector2, IR::LiteralExprPtr mask, 
                             std::size_t vec1_elm_count, std::size_t vec2_elm_count, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_basetype() const;
    std::size_t get_basetype_bitwidth() const;
    bool is_basetype_brain_float() const;

    TypeVarient get_basetype_varient() const override;
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

    std::size_t get_vector_size() const;//Operates on <i1,N> vectors

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
    
    virtual TypeVarient get_element_type_varient() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntSplatInst:public SplatInst {
    public:
    IntSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    
    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class PtrSplatInst:public SplatInst {
    public:
    PtrSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);
    
    std::size_t get_element_bitwidth() const;
    
    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class FloatSplatInst:public SplatInst {
    public:
    FloatSplatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_brain_float() const;
    
    TypeVarient get_element_type_varient() const override;
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
    
    virtual TypeVarient get_element_type_varient() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntStepVectorInst:public StepVectorInst {
    public:
    IntStepVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr start, IR::LiteralExprPtr step, 
                      std::optional<FastMathAttr> fast_math_attr);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    
    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class FloatStepVectorInst:public StepVectorInst {
    public:
    FloatStepVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr start, IR::LiteralExprPtr step, 
                        FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_brain_float() const;
    
    TypeVarient get_element_type_varient() const override;
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

    virtual std::size_t get_vector_size() const final;//From destination. Size of destination and original vector
    virtual std::size_t get_subvector_size() const final;

    virtual TypeVarient get_element_type_varient() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntInsertSubVectorInst:public InsertSubVectorInst {
    public:
    IntInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                           IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size, std::optional<FastMathAttr> fast_math_attr);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class PtrInsertSubVectorInst:public InsertSubVectorInst {
    public:
    PtrInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                           IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size, std::optional<FastMathAttr> fast_math_attr);
    
    std::size_t get_element_bitwidth() const;

    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class FloatInsertSubVectorInst:public InsertSubVectorInst {
    public:
    FloatInsertSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                             IR::LiteralExprPtr subvector, IR::LiteralExprPtr index, std::size_t subvector_size, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_brain_float() const;

    TypeVarient get_element_type_varient() const override;
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
    
    virtual std::size_t get_vector_size() const final;
    virtual std::size_t get_subvector_size() const final;//From destination. Size of extracted subvector

    virtual TypeVarient get_element_type_varient() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntExtractSubVectorInst:public ExtractSubVectorInst {
    public:
    IntExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                            IR::LiteralExprPtr index, std::size_t vector_size, std::optional<FastMathAttr> fast_math_attr);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;

    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class PtrExtractSubVectorInst:public ExtractSubVectorInst {
    public:
    PtrExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                            IR::LiteralExprPtr index, std::size_t vector_size, std::optional<FastMathAttr> fast_math_attr);
    
    std::size_t get_element_bitwidth() const;

    TypeVarient get_element_type_varient() const override;
    std::string to_string() const override;
};

class FloatExtractSubVectorInst:public ExtractSubVectorInst {
    public:
    FloatExtractSubVectorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr vector, 
                              IR::LiteralExprPtr index, std::size_t vector_size, FastMathAttr fast_math_attr);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_element_type() const;
    std::size_t get_element_bitwidth() const;
    bool is_brain_float() const;

    TypeVarient get_element_type_varient() const override;
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
}
}