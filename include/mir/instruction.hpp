#include "instruction/_instruction.hpp"

#include "instruction/arithmetic_bin_inst.hpp"
#include "instruction/arithmetic_tri_inst.hpp"
#include "instruction/bitwise_tri_inst.hpp"
//## Fixed-Point Arithmetic Instructions
#include "instruction/widening_bin_inst.hpp"
// ## Carrying / Borrow Arithmetic Instructions
// ## Combined Quotient and Remainder (`divmod`)
// ## Overflow-Wrap (Checked Arithmetic) Instructions
// ## High-Half Multiply
// ## N-Bit Carry Shifts
#include "instruction/bitwise_bin_inst.hpp"
// ## Bitwise Trinary Instructions
#include "instruction/cmp_bin_inst.hpp"
#include "instruction/conv_inst.hpp"
#include "instruction/unary_inst.hpp"
#include "instruction/numerical_classify_inst.hpp"
#include "instruction/memory_inst.hpp"
#include "instruction/fetch_arithmetic_bin_inst.hpp"
#include "instruction/fetch_bitwise_bin_inst.hpp"
#include "instruction/fetch_unary_inst.hpp"
#include "instruction/terminator_inst.hpp"
#include "instruction/call_inst.hpp"
#include "instruction/other_inst.hpp"