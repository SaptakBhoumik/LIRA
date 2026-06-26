#include "mir/instruction/fetch_arithmetic_bin_inst.hpp"

namespace LIRA {
namespace MIR {
FetchArithmeticBinInst::FetchArithmeticBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                           CommonFetchInstAttrs common_fetch_inst_attrs, std::optional<FastMathAttr> fast_math_attr)
                           :Inst(instruction_stmt, destination, fast_math_attr){
    this->pointer = pointer;
    this->value = value;
    this->common_fetch_inst_attrs = common_fetch_inst_attrs;
}
IR::TypeExprPtr FetchArithmeticBinInst::get_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr FetchArithmeticBinInst::get_pointer() const{
    return this->pointer;
}
IR::LiteralExprPtr FetchArithmeticBinInst::get_value() const{
    return this->value;
}
CommonFetchInstAttrs FetchArithmeticBinInst::get_common_fetch_inst_attrs() const{
    return this->common_fetch_inst_attrs;
}
InstType FetchArithmeticBinInst::get_inst_type() const{
    return InstType::FetchArithmeticBinInst;
}


// --------------------------- Integer read modify operations ---------------------------
IntFetchArithmeticBinInst::IntFetchArithmeticBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                     CommonFetchInstAttrs common_fetch_inst_attrs, bool nuw, bool nsw, bool saturating, bool exact, bool unsigned_, bool floor)
                     :FetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->saturating = saturating;
    this->exact = exact;
    this->unsigned_ = unsigned_;
    this->floor = floor;
}
std::string IntFetchArithmeticBinInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(ptr:" + this->pointer->to_string() + ", " + this->destination->get_type()->to_string() + ":" + this->value->to_string() + ")";
    res += this->common_fetch_inst_attrs.to_string();
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
    if(this->floor){
        res += " #[floor]";
    }
    if(this->exact){
        res += " #[exact]";
    }
    return res;
}
bool IntFetchArithmeticBinInst::is_nuw() const{
    return this->nuw;
}
bool IntFetchArithmeticBinInst::is_nsw() const{
    return this->nsw;
}
bool IntFetchArithmeticBinInst::is_saturating() const{
    return this->saturating;
}
bool IntFetchArithmeticBinInst::is_exact() const{
    return this->exact;
}
bool IntFetchArithmeticBinInst::is_unsigned() const{
    return this->unsigned_;
}
bool IntFetchArithmeticBinInst::is_floor() const{
    return this->floor;
}
std::shared_ptr<IR::IntTypeExpr> IntFetchArithmeticBinInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_type());
}
std::size_t IntFetchArithmeticBinInst::get_bitwidth() const{
    return this->get_casted_type()->get_bits();
}
TypeVariant IntFetchArithmeticBinInst::get_type_variant() const{
    return TypeVariant::Int;
}


IntXchgInst::IntXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                         CommonFetchInstAttrs common_fetch_inst_attrs)
                        :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false, false, false){}
FetchArithmeticBinInst::OpType IntXchgInst::get_op_type() const{
    return OpType::FETCH_XCHG;
}
std::string IntXchgInst::to_string() const{
    return this->to_string_helper("int_fetch_xchg");
}


IntFetchAddInst::IntFetchAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool nuw, bool nsw, bool saturating, bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, nuw, nsw, saturating, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchAddInst::get_op_type() const{
    return OpType::FETCH_ADD;
}
std::string IntFetchAddInst::to_string() const{
    return this->to_string_helper("int_fetch_add");
}


IntFetchSubInst::IntFetchSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool nuw, bool nsw, bool saturating, bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, nuw, nsw, saturating, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchSubInst::get_op_type() const{
    return OpType::FETCH_SUB;
}
std::string IntFetchSubInst::to_string() const{
    return this->to_string_helper("int_fetch_sub");
}


IntFetchAbsDiffInst::IntFetchAbsDiffInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool nuw, bool nsw, bool saturating, bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, nuw, nsw, saturating, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchAbsDiffInst::get_op_type() const{
    return OpType::FETCH_ABSDIFF;
}
std::string IntFetchAbsDiffInst::to_string() const{
    return this->to_string_helper("int_fetch_absdiff");
}


IntFetchMulInst::IntFetchMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool nuw, bool nsw, bool saturating, bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, nuw, nsw, saturating, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchMulInst::get_op_type() const{
    return OpType::FETCH_MUL;
}
std::string IntFetchMulInst::to_string() const{
    return this->to_string_helper("int_fetch_mul");
}


IntFetchDivInst::IntFetchDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool unsigned_, bool exact)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, exact, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchDivInst::get_op_type() const{
    return OpType::FETCH_DIV;
}
std::string IntFetchDivInst::to_string() const{
    return this->to_string_helper("int_fetch_div");
}


IntFetchRemInst::IntFetchRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchRemInst::get_op_type() const{
    return OpType::FETCH_REM;
}
std::string IntFetchRemInst::to_string() const{
    return this->to_string_helper("int_fetch_rem");
}


IntFetchCopySignInst::IntFetchCopySignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool nsw)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, nsw, false, false, false, false){}
FetchArithmeticBinInst::OpType IntFetchCopySignInst::get_op_type() const{
    return OpType::FETCH_COPYSIGN;
}
std::string IntFetchCopySignInst::to_string() const{
    return this->to_string_helper("int_fetch_copysign");
}


IntFetchMaxInst::IntFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchMaxInst::get_op_type() const{
    return OpType::FETCH_MAX;
}
std::string IntFetchMaxInst::to_string() const{
    return this->to_string_helper("int_fetch_max");
}


IntFetchMinInst::IntFetchMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, false, false, false, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchMinInst::get_op_type() const{
    return OpType::FETCH_MIN;
}
std::string IntFetchMinInst::to_string() const{
    return this->to_string_helper("int_fetch_min");
}


IntFetchAvgInst::IntFetchAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    CommonFetchInstAttrs common_fetch_inst_attrs, bool nuw, bool nsw, bool unsigned_, bool floor)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, nuw, nsw, false, false, unsigned_, floor){}
FetchArithmeticBinInst::OpType IntFetchAvgInst::get_op_type() const{
    return OpType::FETCH_AVG;
}
std::string IntFetchAvgInst::to_string() const{
    return this->to_string_helper("int_fetch_avg");
}

// --------------------------- Float read modify operations ---------------------------
FloatFetchArithmeticBinInst::FloatFetchArithmeticBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr, bool unordered, bool ieee754_2019)
                    :FetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr){
    this->unordered = unordered;
    this->ieee754_2019 = ieee754_2019;
}
std::string FloatFetchArithmeticBinInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(ptr:" + this->pointer->to_string() + ", " + this->destination->get_type()->to_string() + ":" + this->value->to_string() + ")";
    res+= this->common_fetch_inst_attrs.to_string();
    if(this->fast_math_attr.has_value()){
        res += " " + this->fast_math_attr->to_string();
    }
    if(this->unordered){
        res += " #[unordered]";
    }
    if(this->ieee754_2019){
        res += " #[ieee754_2019]";
    }
    return res;
}


FloatXchgInst::FloatXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatXchgInst::get_op_type() const{
    return OpType::FETCH_XCHG;
}
std::string FloatXchgInst::to_string() const{
    return this->to_string_helper("float_fetch_xchg");
}


FloatFetchAddInst::FloatFetchAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchAddInst::get_op_type() const{
    return OpType::FETCH_ADD;
}
std::string FloatFetchAddInst::to_string() const{
    return this->to_string_helper("float_fetch_add");
}


FloatFetchSubInst::FloatFetchSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchSubInst::get_op_type() const{
    return OpType::FETCH_SUB;
}
std::string FloatFetchSubInst::to_string() const{
    return this->to_string_helper("float_fetch_sub");
}


FloatFetchAbsDiffInst::FloatFetchAbsDiffInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchAbsDiffInst::get_op_type() const{
    return OpType::FETCH_ABSDIFF;
}
std::string FloatFetchAbsDiffInst::to_string() const{
    return this->to_string_helper("float_fetch_absdiff");
}


FloatFetchMulInst::FloatFetchMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchMulInst::get_op_type() const{
    return OpType::FETCH_MUL;
}
std::string FloatFetchMulInst::to_string() const{
    return this->to_string_helper("float_fetch_mul");
}


FloatFetchDivInst::FloatFetchDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchDivInst::get_op_type() const{
    return OpType::FETCH_DIV;
}
std::string FloatFetchDivInst::to_string() const{
    return this->to_string_helper("float_fetch_div");
}


FloatFetchRemInst::FloatFetchRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchRemInst::get_op_type() const{
    return OpType::FETCH_REM;
}
std::string FloatFetchRemInst::to_string() const{
    return this->to_string_helper("float_fetch_rem");
}


FloatFetchCopySignInst::FloatFetchCopySignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchCopySignInst::get_op_type() const{
    return OpType::FETCH_COPYSIGN;
}
std::string FloatFetchCopySignInst::to_string() const{
    return this->to_string_helper("float_fetch_copysign");
}


FloatFetchMinInst::FloatFetchMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, unordered, ieee754_2019){}
FetchArithmeticBinInst::OpType FloatFetchMinInst::get_op_type() const{
    return OpType::FETCH_MIN;
}
std::string FloatFetchMinInst::to_string() const{
    return this->to_string_helper("float_fetch_min");
}


FloatFetchMaxInst::FloatFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    CommonFetchInstAttrs common_fetch_inst_attrs, FastMathAttr fast_math_attr, bool unordered, bool ieee754_2019)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, unordered, ieee754_2019){}
FetchArithmeticBinInst::OpType FloatFetchMaxInst::get_op_type() const{
    return OpType::FETCH_MAX;
}
std::string FloatFetchMaxInst::to_string() const{
    return this->to_string_helper("float_fetch_max");
}


FloatFetchAvgInst::FloatFetchAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    CommonFetchInstAttrs common_fetch_inst_attrs,
                    FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, common_fetch_inst_attrs, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchAvgInst::get_op_type() const{
    return OpType::FETCH_AVG;
}
std::string FloatFetchAvgInst::to_string() const{
    return this->to_string_helper("float_fetch_avg");
}
}
}