#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
namespace LIRA {
namespace MIR {
// --------------------------- Conversion operations ---------------------------
class ConversionInst:public Inst {
    protected:
    IR::LiteralExprPtr value;
    IR::TypeExprPtr in_type;//Reduced in type. 
    IR::TypeExprPtr out_type;//Reduced out type. 
    public:
    enum class OpType:std::uint32_t{
        TRUNC = 1 << 6,
        EXT = 1 << 7,
        FLOAT_TO_INT = 1 << 8,
        INT_TO_FLOAT = 1 << 9,
        PTR_TO_INT = 1 << 10,
        INT_TO_PTR = 1 << 11,
        BITCAST = 1 << 12
    };
    ConversionInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, IR::TypeExprPtr out_type);

    virtual ~ConversionInst() = default;

    virtual InstOperandTypeVarient get_in_type_varient() const final;//Can be calculated easily from ``in_type``. Just a helper function
    virtual InstOperandTypeVarient get_out_type_varient() const final;//Can be calculated easily from ``out_type``. Just a helper function
    // NOTE: get_in_type_varient and  get_out_type_varient is ignored for BitCastInst because it can be any type as long as the bit width is same + dont make sense
    virtual IR::TypeExprPtr get_in_type() const final;
    virtual IR::TypeExprPtr get_out_type() const final;
    virtual IR::LiteralExprPtr get_value() const final;
    virtual OpType get_op_type() const = 0;//Whether it is trunc,ext,float_to_int,int_to_float etc.

    virtual InstType get_inst_type() const override final;
};

// --------------------------- Scalar conversion operations ---------------------------
class ScalarConversionInst:public ConversionInst{
    // When the instruction doesnt act lane wise
    bool nuw;
    bool nsw;
    bool nsb;
    bool unsigned_;
    // Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.
    public:
    ScalarConversionInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                         IR::TypeExprPtr out_type, bool nuw, bool nsw, bool nsb, bool unsigned_);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_nsb() const final;
    virtual bool is_unsigned() const final;

    virtual std::size_t get_in_type_bit_width() const final;//Returns the bit width of the in type. Calculated automatically
    virtual std::size_t get_out_type_bit_width() const final;//Returns the bit width of the out type. Calculated automatically
};

class IntTruncInst:public ScalarConversionInst{
    bool nuw;
    bool nsw;
    public:
    IntTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                 IR::TypeExprPtr out_type, bool nuw, bool nsw);

    //I can implement casted integer type helper here but I doubt it will be useful because we can get the width from get_in_type_bit_width and get_out_type_bit_width anyways
    //But I am implementing it just for consistency 
    std::shared_ptr<IR::IntTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_out_type() const; 

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatTruncInst:public ScalarConversionInst{
    public:
    FloatTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                    IR::TypeExprPtr out_type);

    //I can implement casted integer type helper here but I doubt it will be useful because we can get the width from get_in_type_bit_width and get_out_type_bit_width anyways
    //But I am implementing it just for consistency 
    std::shared_ptr<IR::FloatTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_out_type() const; 
    bool is_in_bf16() const;//Whether the in type is bf16 or not. Just a helper function to make life easier
    bool is_out_bf16() const;//Whether the out type is bf16 or not. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntExtInst:public ScalarConversionInst{
    bool nsb;
    bool unsigned_;
    public:
    IntExtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
              IR::TypeExprPtr out_type, bool nsb, bool unsigned_);

    std::shared_ptr<IR::IntTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_out_type() const; 

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatExtInst:public ScalarConversionInst{
    public:
    FloatExtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                    IR::TypeExprPtr out_type);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_out_type() const; 
    bool is_in_bf16() const;
    bool is_out_bf16() const;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class FloatToIntInst:public ScalarConversionInst{
    bool unsigned_;
    public:
    FloatToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                    IR::TypeExprPtr out_type, bool unsigned_);

    std::shared_ptr<IR::FloatTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::IntTypeExpr> get_casted_out_type() const; 
    bool is_in_bf16() const;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntToFloatInst:public ScalarConversionInst{
    bool unsigned_;
    public:
    IntToFloatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                    IR::TypeExprPtr out_type, bool unsigned_);

    std::shared_ptr<IR::IntTypeExpr> get_casted_in_type() const;
    std::shared_ptr<IR::FloatTypeExpr> get_casted_out_type() const; 
    bool is_out_bf16() const;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class PtrToIntInst:public ScalarConversionInst{
    public:
    //We already know the in type(ptr) and out type(i64). No need to store again
    PtrToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class IntToPtrInst:public ScalarConversionInst{
    public:
    //We already know the in type(i64) and out type(ptr). No need to store again
    IntToPtrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class BitCastInst:public ScalarConversionInst{
    public:
    //We already know the in type and out type have same bit width. No need to store again
    BitCastInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, IR::TypeExprPtr out_type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};



// --------------------------- Vector conversion operations ---------------------------
class LaneWiseConversionInst:public ConversionInst{
    protected:
    // When the instruction act lanewise
    bool nuw;
    bool nsw;
    bool nsb;
    bool unsigned_;
    // Few instructions dont have all these attributes. For that we return false and in typechecker we make sure unsupported attributes are not used.
    public:
    LaneWiseConversionInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                           IR::TypeExprPtr out_type, bool nuw, bool nsw, bool nsb, bool unsigned_);

    virtual bool is_nuw() const final;
    virtual bool is_nsw() const final;
    virtual bool is_nsb() const final;
    virtual bool is_unsigned() const final;

    virtual std::size_t get_in_basetype_bit_width() const final;//Returns the bit width of the in type. Calculated automatically
    virtual std::size_t get_out_basetype_bit_width() const final;//Returns the bit width of the out type. Calculated automatically
    virtual std::size_t get_num_elements() const final;//Returns the number of elements in the vector. Calculated automatically
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_in_type() const final;//Returns the in type casted to SIMDTypeExpr.
    virtual std::shared_ptr<IR::SIMDTypeExpr> get_casted_out_type() const final;//Returns the out type casted to SIMDTypeExpr. 
};

class LaneWiseIntTruncInst:public LaneWiseConversionInst{
    public:
    LaneWiseIntTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                        IR::TypeExprPtr out_type, bool nuw, bool nsw);


    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWiseFloatTruncInst:public LaneWiseConversionInst{
    public:
    LaneWiseFloatTruncInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                        IR::TypeExprPtr out_type);

    bool is_in_bf16() const;//Whether the in type is bf16 or not. Just a helper function to make life easier
    bool is_out_bf16() const;//Whether the out type is bf16 or not. Just a helper function to make life easier

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWiseIntExtInst:public LaneWiseConversionInst{
    public:
    LaneWiseIntExtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                    IR::TypeExprPtr out_type, bool nsb, bool unsigned_);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWiseFloatExtInst:public LaneWiseConversionInst{
    public:
    LaneWiseFloatExtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                    IR::TypeExprPtr out_type);

    bool is_in_bf16() const;
    bool is_out_bf16() const;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWiseFloatToIntInst:public LaneWiseConversionInst{
    public:
    LaneWiseFloatToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                        IR::TypeExprPtr out_type, bool unsigned_);

    bool is_in_bf16() const;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWiseIntToFloatInst:public LaneWiseConversionInst{
    public:
    LaneWiseIntToFloatInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                        IR::TypeExprPtr out_type, bool unsigned_);

    bool is_out_bf16() const;

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWisePtrToIntInst:public LaneWiseConversionInst{
    public:
    //We already know the in type(<ptr,N>) and out type(<i64,N>). But we need to know N. That is why we take the type here
    //Why not just the number? No partiqular reason. It works. Thought it will make the code cleaner(It doesnt. It is the same either way)
    LaneWisePtrToIntInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                        IR::TypeExprPtr out_type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};

class LaneWiseIntToPtrInst:public LaneWiseConversionInst{
    public:
    //We already know the in type(<i64,N>) and out type(<ptr,N>). But we need to know N. That is why we take the type here
    //Why not just the number? No partiqular reason. It works. Thought it will make the code cleaner(It doesnt. It is the same either way)
    LaneWiseIntToPtrInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, IR::TypeExprPtr in_type, 
                        IR::TypeExprPtr out_type);

    OpType get_op_type() const override final;
    std::string to_string() const override;
};
}
}