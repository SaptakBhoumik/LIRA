#pragma once
#include "ast/ast.hpp"
#include "_instruction.hpp"
#include <cstddef>
namespace LIRA {
namespace MIR {
// --------------------------Unclassified other instructions-------------------------------
class ScalarSelectInst:public Inst {
    IR::LiteralExprPtr condition;//The condition to check. Must be of i1
    IR::LiteralExprPtr true_value;//Same type as output
    IR::LiteralExprPtr false_value;//Same type as output
    public:
    ScalarSelectInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr condition, 
                     IR::LiteralExprPtr true_value, IR::LiteralExprPtr false_value, std::optional<FastMathAttr> fast_math_attr);

    IR::LiteralExprPtr get_condition() const;
    IR::LiteralExprPtr get_true_value() const;
    IR::LiteralExprPtr get_false_value() const;
    IR::TypeExprPtr get_type() const;//From the destination

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class LanewiseSelectInst:public Inst {
    IR::LiteralExprPtr condition;//The condition to check. Must be of <i1,N>
    IR::LiteralExprPtr true_value;//Same type as output
    IR::LiteralExprPtr false_value;//Same type as output
    public:
    LanewiseSelectInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr condition, 
                       IR::LiteralExprPtr true_value, IR::LiteralExprPtr false_value, std::optional<FastMathAttr> fast_math_attr);
        
    IR::LiteralExprPtr get_condition() const;
    IR::LiteralExprPtr get_true_value() const;
    IR::LiteralExprPtr get_false_value() const;
    std::shared_ptr<IR::SIMDTypeExpr> get_casted_type() const;//From destination
    IR::TypeExprPtr get_basetype() const;//Returns the base type of the SIMD type. Just a helper function to make life easier
    std::size_t get_num_elements() const;//Returns the number of elements in the SIMD type. Just a helper function to make life easier

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


class FreezeInst:public Inst {
    IR::LiteralExprPtr value;//The value and its type to freeze
    public:
    FreezeInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, std::optional<FastMathAttr> fast_math_attr);

    IR::LiteralExprPtr get_value() const;
    IR::TypeExprPtr get_type() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class VastartInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to the variable argument list. Must be of type ptr
    public:
    VastartInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer);    

    IR::LiteralExprPtr get_pointer() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class VaendInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to the variable argument list. Must be of type ptr
    public:
    VaendInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr pointer);    

    IR::LiteralExprPtr get_pointer() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class VacopyInst:public Inst {
    IR::LiteralExprPtr dest_pointer;//The pointer to the destination variable argument list. Must be of type ptr
    IR::LiteralExprPtr src_pointer;//The pointer to the source variable argument list. Must be of type ptr
    public:
    VacopyInst(IR::InstructionStmtPtr instruction_stmt, IR::LiteralExprPtr dest_pointer, IR::LiteralExprPtr src_pointer);    

    IR::LiteralExprPtr get_dest_pointer() const;
    IR::LiteralExprPtr get_src_pointer() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class VaargInst:public Inst {
    IR::LiteralExprPtr pointer;//The pointer to the variable argument list. Must be of type ptr
    IR::TypeExprPtr type;//The type of the argument to retrieve. Can be any type
    public:
    VaargInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, std::optional<FastMathAttr> fast_math_attr);    

    IR::LiteralExprPtr get_pointer() const;
    IR::TypeExprPtr get_type() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class PtrMaskInst:public Inst {
    protected:
    IR::LiteralExprPtr pointer;//The pointer to mask. Must be of type ptr
    IR::LiteralExprPtr mask;//The value and its type to mask. The type must be of integer type and must have same bit width as pointer i.e i64 for our case
    public:
    PtrMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask);

    virtual IR::LiteralExprPtr get_pointer() const final;
    virtual IR::LiteralExprPtr get_mask() const final;

    virtual TypeVariant get_dest_type_var() const = 0;
    virtual InstType get_inst_type() const override final;
};

class IntPtrMaskInst:public PtrMaskInst {
    public:
    IntPtrMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask);

    TypeVariant get_dest_type_var() const override;
    std::string to_string() const override;
};

class VecIntPtrMaskInst:public PtrMaskInst {
    public:
    VecIntPtrMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr mask);

    std::size_t get_vector_size() const;

    TypeVariant get_dest_type_var() const override;
    std::string to_string() const override;
};

class PauseInst:public Inst {
    public:
    PauseInst(IR::InstructionStmtPtr instruction_stmt);

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


// --------------------------Binding Assumptions-------------------------------
class AssumeInst:public Inst {
    std::vector<IR::LiteralExprPtr> assumed_values;
    IR::TypeExprPtr type;
    std::string varname;
    public:
    AssumeInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, std::vector<IR::LiteralExprPtr> assumed_values, IR::TypeExprPtr type, 
               std::optional<FastMathAttr> fast_math_attr);    
    
    std::string get_varname() const;
    std::vector<IR::LiteralExprPtr> get_assumed_values() const;
    IR::TypeExprPtr get_type() const;
    bool is_nopoison() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class AssumeRangeInst:public Inst {
    IR::LiteralExprPtr min_value;
    IR::LiteralExprPtr max_value;
    IR::TypeExprPtr type;
    bool unsigned_;
    std::string varname;
    public:
    AssumeRangeInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, IR::LiteralExprPtr min_value, IR::LiteralExprPtr max_value, 
                    IR::TypeExprPtr type, bool unsigned_, std::optional<FastMathAttr> fast_math_attr);  

    std::string get_varname() const;
    IR::LiteralExprPtr get_min_value() const;
    IR::LiteralExprPtr get_max_value() const;
    IR::TypeExprPtr get_type() const;
    bool is_unsigned() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class AssumeNotInst:public Inst {
    std::vector<IR::LiteralExprPtr> assumed_values;
    IR::TypeExprPtr type;
    std::string varname;
    public:
    AssumeNotInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, std::vector<IR::LiteralExprPtr> assumed_values, IR::TypeExprPtr type, 
               std::optional<FastMathAttr> fast_math_attr);    
    
    std::string get_varname() const;
    std::vector<IR::LiteralExprPtr> get_assumed_values() const;
    IR::TypeExprPtr get_type() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class AssumeNotRangeInst:public Inst {
    IR::LiteralExprPtr min_value;
    IR::LiteralExprPtr max_value;
    IR::TypeExprPtr type;
    bool unsigned_;
    std::string varname;
    public:
    AssumeNotRangeInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, IR::LiteralExprPtr min_value, IR::LiteralExprPtr max_value, 
                       IR::TypeExprPtr type, bool unsigned_, std::optional<FastMathAttr> fast_math_attr);  

    std::string get_varname() const;
    IR::LiteralExprPtr get_min_value() const;
    IR::LiteralExprPtr get_max_value() const;
    IR::TypeExprPtr get_type() const;
    bool is_unsigned() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


// --------------------------Non-Binding Expectation Hints-------------------------------
class ExpectInst:public Inst {
    std::vector<IR::LiteralExprPtr> assumed_values;
    IR::TypeExprPtr type;
    std::optional<double> probability;
    std::string varname;
    public:
    ExpectInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, std::vector<IR::LiteralExprPtr> assumed_values, IR::TypeExprPtr type, 
               std::optional<double> probability, std::optional<FastMathAttr> fast_math_attr);    
    
    std::string get_varname() const;
    std::vector<IR::LiteralExprPtr> get_assumed_values() const;
    std::optional<double> get_probability() const;
    IR::TypeExprPtr get_type() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class ExpectRangeInst:public Inst {
    IR::LiteralExprPtr min_value;
    IR::LiteralExprPtr max_value;
    IR::TypeExprPtr type;
    std::optional<double> probability;
    bool unsigned_;
    std::string varname;
    public:
    ExpectRangeInst(IR::InstructionStmtPtr instruction_stmt, std::string varname, IR::LiteralExprPtr min_value, IR::LiteralExprPtr max_value, 
                    IR::TypeExprPtr type, std::optional<double> probability, bool unsigned_, std::optional<FastMathAttr> fast_math_attr);  

    std::string get_varname() const;
    IR::LiteralExprPtr get_min_value() const;
    IR::LiteralExprPtr get_max_value() const;
    std::optional<double> get_probability() const;
    IR::TypeExprPtr get_type() const;
    bool is_unsigned() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


// --------------------------Metadata and Machine Instructions-------------------------------
class NopInst:public Inst {
    std::uint8_t size;
    bool multi_byte;
    public:
    NopInst(IR::InstructionStmtPtr instruction_stmt, std::uint8_t size, bool multi_byte);
    
    std::uint8_t get_size() const;
    bool is_multi_byte() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class AnnotationInst:public Inst {
    std::string message;
    public:
    AnnotationInst(IR::InstructionStmtPtr instruction_stmt, std::string message);
    
    std::string get_message() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class Endbr64Inst:public Inst {
    public:
    Endbr64Inst(IR::InstructionStmtPtr instruction_stmt);    

    InstType get_inst_type() const override;
    std::string to_string() const override;
};


// --------------------------Pointer Provenance Instructions-------------------------------
class LaunderInst:public Inst {
    IR::LiteralExprPtr ptr;
    public:
    LaunderInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr ptr);

    IR::LiteralExprPtr get_ptr() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};

class StripInvariantGroupInst:public Inst {
    IR::LiteralExprPtr ptr;
    public:
    StripInvariantGroupInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr ptr);

    IR::LiteralExprPtr get_ptr() const;

    InstType get_inst_type() const override;
    std::string to_string() const override;
};
}
}