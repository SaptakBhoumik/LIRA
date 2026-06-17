#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <memory>
namespace LIRA {
namespace MIR {
// --------------------------- Conversion operations ---------------------------
class ConvInst:public Inst {
    protected:
    IR::LiteralExprPtr value;
    IR::TypeExprPtr in_type;//Reduced in type. 

    // When the instruction doesnt act lane wise
    bool nuw;
    bool nsw;
    bool nsb;
    bool unsigned_;
    bool saturating;

    virtual std::string to_string_helper(std::string op_name) const final;
    public:
    enum class OpType:std::uint64_t{
        TRUNC = 1 << 6,
        EXT = 1 << 7,
        FLOAT_TO_INT = 1 << 8,
        INT_TO_FLOAT = 1 << 9,
        PTR_TO_INT = 1 << 10,
        INT_TO_PTR = 1 << 11,
        BITCAST = 1 << 12
    };
    ConvInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type,
             bool nuw, bool nsw, bool nsb, bool unsigned_, bool saturating);

    virtual ~ConvInst() = default;
    
    virtual std::optional<InstOperandTypeVarient> get_in_type_varient() const final;//Can be calculated easily from ``in_type``. Just a helper function
    virtual std::optional<InstOperandTypeVarient> get_out_type_varient() const final;//Can be calculated easily from ``out_type``. Just a helper function
    // NOTE: get_in_type_varient and  get_out_type_varient is ignored for BitCastInst because it can be any type as long as the bit width is same + dont make sense
    virtual IR::TypeExprPtr get_in_type() const final;
    virtual IR::TypeExprPtr get_out_type() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual OpType get_op_type() const = 0;//Whether it is trunc,ext,float_to_int,int_to_float etc.

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_nsb() const final;
    virtual bool is_unsigned() const final;
    virtual bool is_saturating() const final;

    virtual InstType get_inst_type() const override final;
};

// --------------------------- Scalar conversion operations ---------------------------
class ScalarConvInst:public ConvInst{
    public:
    ScalarConvInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                   bool nuw, bool nsw, bool nsb, bool unsigned_, bool saturating);

    virtual std::size_t get_in_type_bitwidth() const = 0;
    virtual std::size_t get_out_type_bitwidth() const = 0;
};

class IntTruncInst:public ScalarConvInst{
    public:
    IntTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                 bool nuw, bool nsw, bool unsigned_, bool saturating);

    //I can implement casted integer type helper here but I doubt it will be useful because we can get the width from get_in_type_bitwidth and get_out_type_bitwidth anyways
    //But I am implementing it just for consistency 
    std::shared_ptr<IR::IntTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_out_type() const; 
    std::size_t get_in_type_bitwidth() const override;
    std::size_t get_out_type_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatTruncInst:public ScalarConvInst{
    public:
    FloatTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type);

    //I can implement casted integer type helper here but I doubt it will be useful because we can get the width from get_in_type_bitwidth and get_out_type_bitwidth anyways
    //But I am implementing it just for consistency 
    std::shared_ptr<IR::FloatTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_out_type() const; 
    bool is_in_bf16() const;//Whether the in type is bf16 or not. Just a helper function to make life easier
    bool is_out_bf16() const;//Whether the out type is bf16 or not. Just a helper function to make life easier
    std::size_t get_in_type_bitwidth() const override;
    std::size_t get_out_type_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntExtInst:public ScalarConvInst{
    public:
    IntExtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type,
                bool nsb, bool unsigned_);

    std::shared_ptr<IR::IntTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_out_type() const; 
    std::size_t get_in_type_bitwidth() const override;
    std::size_t get_out_type_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatExtInst:public ScalarConvInst{
    public:
    FloatExtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_out_type() const; 
    bool is_in_bf16() const;
    bool is_out_bf16() const;
    std::size_t get_in_type_bitwidth() const override;
    std::size_t get_out_type_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatToIntInst:public ScalarConvInst{
    public:
    FloatToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                   bool nsb, bool unsigned_, bool saturating);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_out_type() const; 
    bool is_in_bf16() const;
    std::size_t get_in_type_bitwidth() const override;
    std::size_t get_out_type_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntToFloatInst:public ScalarConvInst{
    public:
    IntToFloatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                   bool nsb, bool unsigned_);

    std::shared_ptr<IR::IntTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_out_type() const; 
    bool is_out_bf16() const;
    std::size_t get_in_type_bitwidth() const override;
    std::size_t get_out_type_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class PtrToIntInst:public ScalarConvInst{
    public:
    //We already know the in type(ptr) and out type(i64). No need to store again
    PtrToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);

    std::shared_ptr<IR::IntTypeExpr> get_casted_out_type() const;
    std::size_t get_in_type_bitwidth() const override;
    std::size_t get_out_type_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntToPtrInst:public ScalarConvInst{
    public:
    //We already know the in type(i64) and out type(ptr). No need to store again
    IntToPtrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type);

    std::shared_ptr<IR::IntTypeExpr> get_casted_in_type() const;
    std::size_t get_in_type_bitwidth() const override;
    std::size_t get_out_type_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class BitCastInst:public ScalarConvInst{
    public:
    //We already know the in type and out type have same bit width. No need to store again
    BitCastInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type);

    std::size_t get_in_type_bitwidth() const override;//Returns 0 as of now but in future must return the actual size. TODO:Implement the size of method for typeexpr
    std::size_t get_out_type_bitwidth() const override;//Returns 0 as of now but in future must return the actual size. TODO:Implement the size of method for typeexpr

    OpType get_op_type() const override final;
    std::string to_string() const override;
};



// --------------------------- Vector conversion operations ---------------------------
class VecConvInst:public ConvInst{
    public:
    VecConvInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                bool nuw, bool nsw, bool nsb, bool unsigned_, bool saturating);

    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_in_type() const final;//Returns the in type casted to SIMDTypeExpr.
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_out_type() const final;//Returns the out type casted to SIMDTypeExpr. 
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Calculated automatically
    virtual std::size_t get_in_basetype_bitwidth() const = 0;
    virtual std::size_t get_out_basetype_bitwidth() const = 0;
};

class VecIntTruncInst:public VecConvInst{
    public:
    VecIntTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                    bool nuw, bool nsw, bool unsigned_, bool saturating);

    std::shared_ptr<IR::IntTypeExpr> get_casted_in_basetype() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_out_basetype() const; 
    std::size_t get_in_basetype_bitwidth() const override;
    std::size_t get_out_basetype_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatTruncInst:public VecConvInst{
    public:
    VecFloatTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_in_basetype() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_out_basetype() const;
    bool is_in_basetype_bf16() const;//Whether the in type is bf16 or not. Just a helper function to make life easier
    bool is_out_basetype_bf16() const;//Whether the out type is bf16 or not. Just a helper function to make life easier
    std::size_t get_in_basetype_bitwidth() const override;
    std::size_t get_out_basetype_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntExtInst:public VecConvInst{
    public:
    VecIntExtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                  bool nsb, bool unsigned_);

    std::shared_ptr<IR::IntTypeExpr> get_casted_in_basetype() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_out_basetype() const; 
    std::size_t get_in_basetype_bitwidth() const override;
    std::size_t get_out_basetype_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatExtInst:public VecConvInst{
    public:
    VecFloatExtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_in_basetype() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_out_basetype() const;
    bool is_in_basetype_bf16() const;
    bool is_out_basetype_bf16() const;
    std::size_t get_in_basetype_bitwidth() const override;
    std::size_t get_out_basetype_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecFloatToIntInst:public VecConvInst{
    public:
    VecFloatToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                      bool nsb, bool unsigned_, bool saturating);
    
    std::shared_ptr<IR::FloatTypeExpr> get_casted_in_basetype() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_out_basetype() const; 
    bool is_in_basetype_bf16() const;
    std::size_t get_in_basetype_bitwidth() const override;
    std::size_t get_out_basetype_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntToFloatInst:public VecConvInst{
    public:
    VecIntToFloatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                      bool nsb, bool unsigned_);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_in_basetype() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_out_basetype() const;
    bool is_out_basetype_bf16() const;
    std::size_t get_in_basetype_bitwidth() const override;
    std::size_t get_out_basetype_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecPtrToIntInst:public VecConvInst{
    public:
    //We already know the in type(<i64,N>) and out type(<ptr,N>). But we need to know N. That is why we take the type here
    //Why not just the number? No partiqular reason. It works. Thought it will make the code cleaner(It doesnt. It is the same either way)
    VecPtrToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type);
    
    std::shared_ptr<IR::IntTypeExpr> get_casted_out_basetype() const;
    std::size_t get_in_basetype_bitwidth() const override;
    std::size_t get_out_basetype_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class VecIntToPtrInst:public VecConvInst{
    public:
    //We already know the in type(<ptr,N>) and out type(<i64,N>). But we need to know N. That is why we take the type here
    //Why not just the number? No partiqular reason. It works. Thought it will make the code cleaner(It doesnt. It is the same either way)
    VecIntToPtrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type);

    std::shared_ptr<IR::IntTypeExpr> get_casted_in_basetype() const;
    std::size_t get_in_basetype_bitwidth() const override;
    std::size_t get_out_basetype_bitwidth() const override;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}