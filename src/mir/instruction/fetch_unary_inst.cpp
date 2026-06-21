#include "mir/instruction/fetch_unary_inst.hpp"

namespace LIRA {
namespace MIR {
FetchUnaryInst::FetchUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                               std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                               std::optional<FastMathAttr> fast_math_attr)
                    :Inst(instruction_stmt, destination, fast_math_attr){
    this->value = value;
    this->alignment = alignment;
    this->volatile_ = volatile_;
    this->atomic_info = atomic_info;
}
IR::TypeExprPtr FetchUnaryInst::get_type() const{
    return this->destination->get_type();
}
IR::LiteralExprPtr FetchUnaryInst::get_value() const{
    return this->value;
}
std::size_t FetchUnaryInst::get_alignment() const{
    return this->alignment;
}
bool FetchUnaryInst::is_volatile() const{
    return this->volatile_;
}
std::optional<std::pair<AtomicOrdering,SyncScope>> FetchUnaryInst::get_atomic_info() const{
    return this->atomic_info;
}
InstType FetchUnaryInst::get_inst_type() const{
    return InstType::FetchUnaryInst;
}
// --------------------------- Int Fetch Unary operations ---------------------------
IntFetchUnaryInst::IntFetchUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                    std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info, 
                                    bool nuw, bool nsw, bool zero_poison)
                                    :FetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, std::nullopt){
    this->nuw = nuw;
    this->nsw = nsw;
    this->zero_poison = zero_poison;
}
std::string IntFetchUnaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(ptr:" + this->value->to_string() + ")";
    if(this->alignment != 0){
        res += " #[align(i64:" + std::to_string(this->alignment) + ")]";
    }
    if(this->volatile_){
        res += " #[volatile]";
    }
    if(this->atomic_info.has_value()){
        res += " #[atomic(str:\"" + MIR::to_string(this->atomic_info.value().first) + "\")]";
        res += " #[syncscope(str:\"" + MIR::to_string(this->atomic_info.value().second) + "\")]";
    }
    if(this->nuw){
        res += " #[nuw]";
    }
    if(this->nsw){
        res += " #[nsw]";
    }
    if(this->zero_poison){
        res += " #[zero_poison]";
    }
    return res;
}
bool IntFetchUnaryInst::is_nuw() const{
    return this->nuw;
}
bool IntFetchUnaryInst::is_nsw() const{
    return this->nsw;
}
bool IntFetchUnaryInst::is_zero_poison() const{
    return this->zero_poison;
}
std::shared_ptr<IR::IntTypeExpr> IntFetchUnaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::IntTypeExpr>(get_type());
}
std::size_t IntFetchUnaryInst::get_bitwidth() const{
    return get_casted_operand_type()->get_bits();
}
InstOperandTypeVarient IntFetchUnaryInst::get_type_varient() const{
    return InstOperandTypeVarient::Int;
}


IntFetchNegInst::IntFetchNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                 std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                 bool nsw)
                                :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, nsw, false){}
FetchUnaryInst::OpType IntFetchNegInst::get_op_type() const{
    return OpType::FETCH_NEG;
}
std::string IntFetchNegInst::to_string() const{
    return to_string_helper("int_fetch_neg");
}


IntFetchNotInst::IntFetchNotInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                 std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info)
                                 :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, false){}
FetchUnaryInst::OpType IntFetchNotInst::get_op_type() const{
    return OpType::FETCH_NOT;
}
std::string IntFetchNotInst::to_string() const{
    return to_string_helper("int_fetch_not");
}


IntFetchAbsInst::IntFetchAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                 std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info, 
                                 bool nsw)
                                 :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, nsw, false){}
FetchUnaryInst::OpType IntFetchAbsInst::get_op_type() const{
    return OpType::FETCH_ABS;
}
std::string IntFetchAbsInst::to_string() const{
    return to_string_helper("int_fetch_abs");
}


IntFetchPopcountInst::IntFetchPopcountInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                           std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info)
                                           :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, false){}
FetchUnaryInst::OpType IntFetchPopcountInst::get_op_type() const{
    return OpType::FETCH_POPCOUNT;
}
std::string IntFetchPopcountInst::to_string() const{
    return to_string_helper("int_fetch_popcount");
}


IntFetchCLZInst::IntFetchCLZInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                 std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info, 
                                 bool zero_poison)
                                 :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, zero_poison){}
FetchUnaryInst::OpType IntFetchCLZInst::get_op_type() const{
    return OpType::FETCH_CLZ;
}
std::string IntFetchCLZInst::to_string() const{
    return to_string_helper("int_fetch_clz");
}


IntFetchCTZInst::IntFetchCTZInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                 std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                 bool zero_poison)
                                 :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, zero_poison){}
FetchUnaryInst::OpType IntFetchCTZInst::get_op_type() const{
    return OpType::FETCH_CTZ;
}
std::string IntFetchCTZInst::to_string() const{
    return to_string_helper("int_fetch_ctz");
}


IntFetchParityInst::IntFetchParityInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                       std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info)
                                       :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, false){}
FetchUnaryInst::OpType IntFetchParityInst::get_op_type() const{
    return OpType::FETCH_PARITY;
}
std::string IntFetchParityInst::to_string() const{
    return to_string_helper("int_fetch_parity");
}


IntFetchBswapInst::IntFetchBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                     std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info)
                                     :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, false){}
FetchUnaryInst::OpType IntFetchBswapInst::get_op_type() const{
    return OpType::FETCH_BSWAP;
}
std::string IntFetchBswapInst::to_string() const{
    return to_string_helper("int_fetch_bswap");
}


IntFetchBitreverseInst::IntFetchBitreverseInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                               std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info )
                                               :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, false){}
FetchUnaryInst::OpType IntFetchBitreverseInst::get_op_type() const{
    return OpType::FETCH_BITREVERSE;
}
std::string IntFetchBitreverseInst::to_string() const{
    return to_string_helper("int_fetch_bitreverse");
}


IntFetchCLRSBInst::IntFetchCLRSBInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                     std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info)
                                     :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, false){}
FetchUnaryInst::OpType IntFetchCLRSBInst::get_op_type() const{
    return OpType::FETCH_CLRSB;
}
std::string IntFetchCLRSBInst::to_string() const{
    return to_string_helper("int_fetch_clrsb");
}


IntFetchBLSIInst::IntFetchBLSIInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                   std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info)
                                   :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, false){}
FetchUnaryInst::OpType IntFetchBLSIInst::get_op_type() const{
    return OpType::FETCH_BLSI;
}
std::string IntFetchBLSIInst::to_string() const{
    return to_string_helper("int_fetch_blsi");
}


IntFetchBLSRInst::IntFetchBLSRInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                   std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info)
                                   :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, false){}
FetchUnaryInst::OpType IntFetchBLSRInst::get_op_type() const{
    return OpType::FETCH_BLSR;
}
std::string IntFetchBLSRInst::to_string() const{
    return to_string_helper("int_fetch_blsr");
}


IntFetchBLSMaskInst::IntFetchBLSMaskInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value,
                                        std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info)
                                        :IntFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, false, false, false){}
FetchUnaryInst::OpType IntFetchBLSMaskInst::get_op_type() const{
    return OpType::FETCH_BLSMASK;
}
std::string IntFetchBLSMaskInst::to_string() const{
    return to_string_helper("int_fetch_blsmask");
}


// --------------------------- Float Fetch Unary operations ---------------------------
FloatFetchUnaryInst::FloatFetchUnaryInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                         std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                         FastMathAttr fast_math_attr,bool approx)
                                         :FetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr){
    this->approx = approx;
}
std::string FloatFetchUnaryInst::to_string_helper(const std::string op_name) const{
    std::string res = "let " + this->destination->get_dest_register_name() + " = ." + op_name + "(ptr:" + this->value->to_string() + ")";
    if(this->alignment != 0){
        res += " #[align(i64:" + std::to_string(this->alignment) + ")]";
    }
    if(this->volatile_){
        res += " #[volatile]";
    }
    if(this->atomic_info.has_value()){
        res += " #[atomic(str:\"" + MIR::to_string(this->atomic_info.value().first) + "\")]";
        res += " #[syncscope(str:\"" + MIR::to_string(this->atomic_info.value().second) + "\")]";
    }
    if(this->fast_math_attr.has_value()){
        res+= " " + this->fast_math_attr.value().to_string();
    }
    if(this->approx){
        res += " #[approx]";
    }
    return res;
}
bool FloatFetchUnaryInst::is_approx() const{
    return this->approx;
}
std::shared_ptr<IR::FloatTypeExpr> FloatFetchUnaryInst::get_casted_operand_type() const{
    return std::dynamic_pointer_cast<IR::FloatTypeExpr>(get_type());
}
std::size_t FloatFetchUnaryInst::get_bitwidth() const{
    return get_casted_operand_type()->get_bits();
}
bool FloatFetchUnaryInst::is_brain_float() const{
    return get_casted_operand_type()->is_brain_float();
}
InstOperandTypeVarient FloatFetchUnaryInst::get_type_varient() const{
    return InstOperandTypeVarient::Float;
}


FloatFetchNegInst::FloatFetchNegInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                     std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,                                 
                                     FastMathAttr fast_math_attr)
                                     :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,false){}
FetchUnaryInst::OpType FloatFetchNegInst::get_op_type() const{
    return OpType::FETCH_NEG;
}
std::string FloatFetchNegInst::to_string() const{
    return to_string_helper("float_fetch_neg");
}


FloatFetchAbsInst::FloatFetchAbsInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                     std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,                                 
                                     FastMathAttr fast_math_attr)
                                     :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,false){}
FetchUnaryInst::OpType FloatFetchAbsInst::get_op_type() const{
    return OpType::FETCH_ABS;
}
std::string FloatFetchAbsInst::to_string() const{
    return to_string_helper("float_fetch_abs");
}


FloatFetchCeilInst::FloatFetchCeilInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                       std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                       FastMathAttr fast_math_attr)
                                       :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,false){}
FetchUnaryInst::OpType FloatFetchCeilInst::get_op_type() const{
    return OpType::FETCH_CEIL;
}
std::string FloatFetchCeilInst::to_string() const{
    return to_string_helper("float_fetch_ceil");
}


FloatFetchFloorInst::FloatFetchFloorInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                         std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                         FastMathAttr fast_math_attr)
                                         :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,false){}
FetchUnaryInst::OpType FloatFetchFloorInst::get_op_type() const{
    return OpType::FETCH_FLOOR;
}
std::string FloatFetchFloorInst::to_string() const{
    return to_string_helper("float_fetch_floor");
}


FloatFetchIntregralPartInst::FloatFetchIntregralPartInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                                         std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                                         FastMathAttr fast_math_attr)
                                                         :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,false){}
FetchUnaryInst::OpType FloatFetchIntregralPartInst::get_op_type() const{
    return OpType::FETCH_INTEGRAL_PART;
}
std::string FloatFetchIntregralPartInst::to_string() const{
    return to_string_helper("float_fetch_integral_part");
}


FloatFetchFractionalPartInst::FloatFetchFractionalPartInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                                           std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                                           FastMathAttr fast_math_attr)
                                                           :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,false){}
FetchUnaryInst::OpType FloatFetchFractionalPartInst::get_op_type() const{
    return OpType::FETCH_FRACTIONAL_PART;
}
std::string FloatFetchFractionalPartInst::to_string() const{
    return to_string_helper("float_fetch_fractional_part");
}


FloatFetchRoundNearestInst::FloatFetchRoundNearestInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                                       std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                                       FastMathAttr fast_math_attr)
                                                       :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,false){}
FetchUnaryInst::OpType FloatFetchRoundNearestInst::get_op_type() const{
    return OpType::FETCH_ROUND_NEAREST;
}
std::string FloatFetchRoundNearestInst::to_string() const{
    return to_string_helper("float_fetch_roundnearest");
}


FloatFetchRoundEvenInst::FloatFetchRoundEvenInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                                std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                                FastMathAttr fast_math_attr)
                                                :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,false){}
FetchUnaryInst::OpType FloatFetchRoundEvenInst::get_op_type() const{
    return OpType::FETCH_ROUND_EVEN;
}
std::string FloatFetchRoundEvenInst::to_string() const{
    return to_string_helper("float_fetch_roundeven");
}


FloatFetchSqrtInst::FloatFetchSqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                       std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                       FastMathAttr fast_math_attr)
                                       :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,false){}
FetchUnaryInst::OpType FloatFetchSqrtInst::get_op_type() const{
    return OpType::FETCH_SQRT;
}
std::string FloatFetchSqrtInst::to_string() const{
    return to_string_helper("float_fetch_sqrt");
}


FloatFetchReciprocalInst::FloatFetchReciprocalInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                                   std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                                   FastMathAttr fast_math_attr, bool approx)
                                                   :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,approx){}
FetchUnaryInst::OpType FloatFetchReciprocalInst::get_op_type() const{
    return OpType::FETCH_RECIPROCAL;
}
std::string FloatFetchReciprocalInst::to_string() const{
    return to_string_helper("float_fetch_reciprocal");
}


FloatFetchRsqrtInst::FloatFetchRsqrtInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                         std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                         FastMathAttr fast_math_attr, bool approx)
                                         :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,approx){}
FetchUnaryInst::OpType FloatFetchRsqrtInst::get_op_type() const{
    return OpType::FETCH_RSQRT;
}
std::string FloatFetchRsqrtInst::to_string() const{
    return to_string_helper("float_fetch_rsqrt");
}


FloatFetchBswapInst::FloatFetchBswapInst(IR::InstructionStmtPtr instruction_stmt, LocalDestRegisterPtr destination, IR::LiteralExprPtr value, 
                                         std::size_t alignment, bool volatile_, std::optional<std::pair<AtomicOrdering,SyncScope>> atomic_info,
                                         FastMathAttr fast_math_attr)
                                         :FloatFetchUnaryInst(instruction_stmt, destination, value, alignment, volatile_, atomic_info, fast_math_attr,false){}
FetchUnaryInst::OpType FloatFetchBswapInst::get_op_type() const{
    return OpType::FETCH_BSWAP;
}
std::string FloatFetchBswapInst::to_string() const{
    return to_string_helper("float_fetch_bswap");
}
}
}