#include "mir/instruction/fetch_arithmetic_bin_inst.hpp"
#include <memory>

namespace LIRA {
namespace MIR {
FetchArithmeticBinInst::FetchArithmeticBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                           std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info)
                           :Inst(instruction_stmt, destination){
    this->pointer = pointer;
    this->value = value;
    this->alignment = alignment;
    this->volatile_ = volatile_;
    this->atomic_info = atomic_info;
}
IR::TypeExprPtr FetchArithmeticBinInst::get_type() const {
    return this->destination->get_type();
}
IR::LiteralExprPtr FetchArithmeticBinInst::get_pointer() const {
    return this->pointer;
}
IR::LiteralExprPtr FetchArithmeticBinInst::get_value() const {
    return this->value;
}
std::size_t FetchArithmeticBinInst::get_alignment() const {
    return this->alignment;
}
bool FetchArithmeticBinInst::is_volatile() const {
    return this->volatile_;
}
std::optional<std::pair<SyncScope,AtomicOrdering>> FetchArithmeticBinInst::get_atomic_info() const {
    return this->atomic_info;
}
InstType FetchArithmeticBinInst::get_inst_type() const {
    return InstType::FetchArithmeticBinInst;
}


// --------------------------- Integer read modify operations ---------------------------
IntFetchArithmeticBinInst::IntFetchArithmeticBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                     std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                     bool nuw, bool nsw, bool saturating, bool exact, bool unsigned_, bool floor)
                     :FetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info){
    this->nuw = nuw;
    this->nsw = nsw;
    this->saturating = saturating;
    this->exact = exact;
    this->unsigned_ = unsigned_;
    this->floor = floor;
}
std::string IntFetchArithmeticBinInst::to_string_helper(const std::string op_name) const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(ptr:" + this->pointer->to_string() + ", " + this->destination->get_type()->to_string() + ":" + this->value->to_string() + ")";
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
bool IntFetchArithmeticBinInst::is_nuw() const {
    return this->nuw;
}
bool IntFetchArithmeticBinInst::is_nsw() const {
    return this->nsw;
}
bool IntFetchArithmeticBinInst::is_saturating() const {
    return this->saturating;
}
bool IntFetchArithmeticBinInst::is_exact() const {
    return this->exact;
}
bool IntFetchArithmeticBinInst::is_unsigned() const {
    return this->unsigned_;
}
bool IntFetchArithmeticBinInst::is_floor() const {
    return this->floor;
}
std::shared_ptr<IR::IntTypeExpr> IntFetchArithmeticBinInst::get_casted_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(this->get_type());
}
std::size_t IntFetchArithmeticBinInst::get_bitwidth() const{
    return this->get_casted_type()->get_bits();
}
InstOperandTypeVarient IntFetchArithmeticBinInst::get_type_varient() const{
    return InstOperandTypeVarient::Int;
}


IntXchgInst::IntXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                         std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info)
                        :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, false, false, false){}
FetchArithmeticBinInst::OpType IntXchgInst::get_op_type() const {
    return OpType::FETCH_XCHG;
}
std::string IntXchgInst::to_string() const {
    return this->to_string_helper("int_fetch_xchg");
}


IntFetchAddInst::IntFetchAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool nuw, bool nsw, bool saturating, bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, nuw, nsw, saturating, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchAddInst::get_op_type() const {
    return OpType::FETCH_ADD;
}
std::string IntFetchAddInst::to_string() const {
    return this->to_string_helper("int_fetch_add");
}


IntFetchSubInst::IntFetchSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool nuw, bool nsw, bool saturating, bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, nuw, nsw, saturating, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchSubInst::get_op_type() const {
    return OpType::FETCH_SUB;
}
std::string IntFetchSubInst::to_string() const {
    return this->to_string_helper("int_fetch_sub");
}


IntFetchMulInst::IntFetchMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool nuw, bool nsw, bool saturating, bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, nuw, nsw, saturating, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchMulInst::get_op_type() const {
    return OpType::FETCH_MUL;
}
std::string IntFetchMulInst::to_string() const {
    return this->to_string_helper("int_fetch_mul");
}


IntFetchDivInst::IntFetchDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool unsigned_, bool exact)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, exact, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchDivInst::get_op_type() const {
    return OpType::FETCH_DIV;
}
std::string IntFetchDivInst::to_string() const {
    return this->to_string_helper("int_fetch_div");
}


IntFetchRemInst::IntFetchRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchRemInst::get_op_type() const {
    return OpType::FETCH_REM;
}
std::string IntFetchRemInst::to_string() const {
    return this->to_string_helper("int_fetch_rem");
}


IntFetchCopySignInst::IntFetchCopySignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool nsw)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, nsw, false, false, false, false){}
FetchArithmeticBinInst::OpType IntFetchCopySignInst::get_op_type() const {
    return OpType::FETCH_COPYSIGN;
}
std::string IntFetchCopySignInst::to_string() const {
    return this->to_string_helper("int_fetch_copysign");
}


IntFetchMaxInst::IntFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchMaxInst::get_op_type() const {
    return OpType::FETCH_MAX;
}
std::string IntFetchMaxInst::to_string() const {
    return this->to_string_helper("int_fetch_max");
}


IntFetchMinInst::IntFetchMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool unsigned_)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, false, false, false, false, unsigned_, false){}
FetchArithmeticBinInst::OpType IntFetchMinInst::get_op_type() const {
    return OpType::FETCH_MIN;
}
std::string IntFetchMinInst::to_string() const {
    return this->to_string_helper("int_fetch_min");
}


IntFetchAvgInst::IntFetchAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    bool nuw, bool nsw, bool unsigned_, bool floor)
                    :IntFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, nuw, nsw, false, false, unsigned_, floor){}
FetchArithmeticBinInst::OpType IntFetchAvgInst::get_op_type() const {
    return OpType::FETCH_AVG;
}
std::string IntFetchAvgInst::to_string() const {
    return this->to_string_helper("int_fetch_avg");
}

// --------------------------- Float read modify operations ---------------------------
FloatFetchArithmeticBinInst::FloatFetchArithmeticBinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr, bool unordered, bool ieee754_2019)
                    :FetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info){
    this->fast_math_attr = fast_math_attr;
    this->unordered = unordered;
    this->ieee754_2019 = ieee754_2019;
}
std::string FloatFetchArithmeticBinInst::to_string_helper(const std::string op_name) const {
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(ptr:" + this->pointer->to_string() + ", " + this->destination->get_type()->to_string() + ":" + this->value->to_string() + ")";
    res += " " + this->fast_math_attr.to_string();
    if(this->unordered){
        res += " #[unordered]";
    }
    if(this->ieee754_2019){
        res += " #[ieee754_2019]";
    }
    return res;
}


FloatXchgInst::FloatXchgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, FastMathAttr{}, false, false){}
FetchArithmeticBinInst::OpType FloatXchgInst::get_op_type() const {
    return OpType::FETCH_XCHG;
}
std::string FloatXchgInst::to_string() const {
    return this->to_string_helper("float_fetch_xchg");
}


FloatFetchAddInst::FloatFetchAddInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchAddInst::get_op_type() const {
    return OpType::FETCH_ADD;
}
std::string FloatFetchAddInst::to_string() const {
    return this->to_string_helper("float_fetch_add");
}


FloatFetchSubInst::FloatFetchSubInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchSubInst::get_op_type() const {
    return OpType::FETCH_SUB;
}
std::string FloatFetchSubInst::to_string() const {
    return this->to_string_helper("float_fetch_sub");
}


FloatFetchMulInst::FloatFetchMulInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchMulInst::get_op_type() const {
    return OpType::FETCH_MUL;
}
std::string FloatFetchMulInst::to_string() const {
    return this->to_string_helper("float_fetch_mul");
}


FloatFetchDivInst::FloatFetchDivInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value, 
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchDivInst::get_op_type() const {
    return OpType::FETCH_DIV;
}
std::string FloatFetchDivInst::to_string() const {
    return this->to_string_helper("float_fetch_div");
}


FloatFetchRemInst::FloatFetchRemInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchRemInst::get_op_type() const {
    return OpType::FETCH_REM;
}
std::string FloatFetchRemInst::to_string() const {
    return this->to_string_helper("float_fetch_rem");
}


FloatFetchCopySignInst::FloatFetchCopySignInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchCopySignInst::get_op_type() const {
    return OpType::FETCH_COPYSIGN;
}
std::string FloatFetchCopySignInst::to_string() const {
    return this->to_string_helper("float_fetch_copysign");
}


FloatFetchMinInst::FloatFetchMinInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr, bool ieee754_2019, bool unordered)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, fast_math_attr, unordered, ieee754_2019){}
FetchArithmeticBinInst::OpType FloatFetchMinInst::get_op_type() const {
    return OpType::FETCH_MIN;
}
std::string FloatFetchMinInst::to_string() const {
    return this->to_string_helper("float_fetch_min");
}


FloatFetchMaxInst::FloatFetchMaxInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr, bool unordered, bool ieee754_2019)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, fast_math_attr, unordered, ieee754_2019){}
FetchArithmeticBinInst::OpType FloatFetchMaxInst::get_op_type() const {
    return OpType::FETCH_MAX;
}
std::string FloatFetchMaxInst::to_string() const {
    return this->to_string_helper("float_fetch_max");
}


FloatFetchAvgInst::FloatFetchAvgInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr pointer, IR::LiteralExprPtr value,
                    std::size_t alignment, bool volatile_, std::optional<std::pair<SyncScope,AtomicOrdering>> atomic_info,
                    FastMathAttr fast_math_attr)
                    :FloatFetchArithmeticBinInst(instruction_stmt, destination, pointer, value, alignment, volatile_, atomic_info, fast_math_attr, false, false){}
FetchArithmeticBinInst::OpType FloatFetchAvgInst::get_op_type() const {
    return OpType::FETCH_AVG;
}
std::string FloatFetchAvgInst::to_string() const {
    return this->to_string_helper("float_fetch_avg");
}
}
}