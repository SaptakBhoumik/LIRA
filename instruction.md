# Current instruction set

## Binary Arithmetic Instructions

- `let T:%output_var = .add(T:%input_var1, T:%input_var2)` - Adds 2 numbers. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp to type range instead of wrapping. Pair with `#[unsigned]` for unsigned saturation; default is signed saturation.

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .sub(T:%input_var1, T:%input_var2)` - Subtracts 2 numbers. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp to type range instead of wrapping. Pair with `#[unsigned]` for unsigned saturation; default is signed saturation.

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .mul(T:%input_var1, T:%input_var2)` - Multiplies 2 numbers. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp to type range instead of wrapping. Pair with `#[unsigned]` for unsigned saturation; default is signed saturation.

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .div(T:%input_var1, T:%input_var2)` - Division. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[exact]` - poison if the division is not exact (i.e. has a remainder)
    - `#[unsigned]` - unsigned division; default is signed

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .rem(T:%input_var1, T:%input_var2)` - Remainder of division. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[unsigned]` - remainder of unsigned division; default is signed

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .copysign(T:%input_var1, T:%input_var2)` - Copies the sign of `input_var2` onto `input_var1`. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat/integer. For integer, signed is assumed (unsigned integers sign bit but make no sense).

    If `T0` is integer: `#[nsw]` - poison if the result overflows (i.e. input is `INT_MIN`)

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .min(T:%input_var1, T:%input_var2)` - Minimum of 2 values. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[unsigned]` - unsigned minimum; default is signed

    If `T0` is float/bfloat:
    - `#[unordered]` - if either input is NaN, return the other operand (IEEE "minNum" semantics). Default (no attribute) returns NaN if either input is NaN (ordered semantics).
    - `#[ieee754_2019]` - get correct signed-zero ordering (`-0.0 < +0.0`) under the NaN-propagating (default ordered) path; when combined with `#[unordered]`, gets 754-2019 `minimumNumber` semantics (NaN-ignoring and correctly ordered for signed zero). Combining with `#[nsz]` is a compile error. Only valid when T0 is float or bfloat.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .max(T:%input_var1, T:%input_var2)` - Maximum of 2 values. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[unsigned]` - unsigned maximum; default is signed

    If `T0` is float/bfloat:
    - `#[unordered]` - if either input is NaN, return the other operand (IEEE "maxNum" semantics). Default (no attribute) returns NaN if either input is NaN (ordered semantics).
    - `#[ieee754_2019]` - get correct signed-zero ordering (`-0.0 < +0.0`) under the NaN-propagating (default ordered) path; when combined with `#[unordered]`, gets 754-2019 `maximumNumber` semantics (NaN-ignoring and correctly ordered for signed zero). Combining with `#[nsz]` is a compile error. Only valid when T0 is float or bfloat.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%out = .avg(T:%a, T:%b)` - Returns the average of `a` and `b`. `T` must be of the form `T0` or `<T0,M>` where `T0` is integer, float, or bfloat. For vectors, the operation is lanewise.

    **If `T0` is integer:** Computes `(a + b + 1) >> 1` (rounds toward positive infinity, matching `PAVGB`/`PAVGW`). Default is signed.
    - `#[unsigned]` - treat `a` and `b` as unsigned; default is signed
    - `#[floor]` - round toward negative infinity (`(a + b) >> 1`) instead of the default ceiling
    - `#[nsw]` - poison if the intermediate sum `a + b` overflows before the shift
    - `#[nuw]` - poison on unsigned intermediate overflow; only valid with `#[unsigned]`

    **If `T0` is float/bfloat:** Computes `(a + b) * 0.5` exactly.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

---

## Trinary Arithmetic Instructions

- `let T:%output_var = .fma(T:%input_var1, T:%input_var2, T:%input_var3)` - Fused multiply-add: `(input_var1 * input_var2) + input_var3` with a single rounding step. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp to type range instead of wrapping. Pair with `#[unsigned]` for unsigned saturation; default is signed saturation.

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .fms(T:%input_var1, T:%input_var2, T:%input_var3)` - Fused multiply-subtract: `(input_var1 * input_var2) - input_var3` with a single rounding step. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp to type range instead of wrapping. Pair with `#[unsigned]` for unsigned saturation; default is signed saturation.

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .fnma(T:%input_var1, T:%input_var2, T:%input_var3)` - Fused negative multiply-add: `-(input_var1 * input_var2) + input_var3` with a single rounding step. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp to type range instead of wrapping. Pair with `#[unsigned]` for unsigned saturation; default is signed saturation.

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .fnms(T:%input_var1, T:%input_var2, T:%input_var3)` - Fused negative multiply-subtract: `-(input_var1 * input_var2) - input_var3` with a single rounding step. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp to type range instead of wrapping. Pair with `#[unsigned]` for unsigned saturation; default is signed saturation.

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .clamp(T:%input_var, T:%min, T:%max)` - Clamps `input_var` to `[min, max]`. Returns `min` if below, `max` if above, otherwise the value itself. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[unsigned]` - unsigned clamp; default is signed

    If `T0` is float/bfloat:
    - `#[unordered]` - NaN-ignoring clamp (IEEE "minNum/maxNum" semantics). Default propagates NaN.
    - `#[ieee754_2019]` - correct signed-zero ordering on the boundary; when combined with `#[unordered]`, gets 754-2019 `minimumNumber`/`maximumNumber` semantics for the internal min/max operations. Combining with `#[nsz]` is a compile error. Only valid when T0 is float or bfloat.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

---

## Fixed-Point Arithmetic Instructions

- `let T:%out = .mulfix(T:%a, T:%b, i32:%scale)` - Fixed-point multiply. Multiplies `a` and `b` as if they were fixed-point values with `scale` fractional bits, returning the correctly rounded result in the same type. Concretely: computes `(a * b) >> scale` with the intermediate product computed at double width to avoid overflow. Scale must be a compile-time/run-time constant.

    T must be of the form `T0` or `<T0,M>` where T0 is an integer type. `i32:%scale` must be a compile-time/run-time; must satisfy `0 <= scale <= bitwidth(T0)`.

    - `#[unsigned]` - treat `a` and `b` as unsigned fixed-point values; default is signed
    - `#[saturating]` - if the shifted result does not fit in T, clamp to the type range instead of producing poison; pair with `#[unsigned]` for unsigned saturation; default is signed saturation when this flag is set
    - `#[nsw]` - only valid without `#[saturating]`; poison on signed overflow
    - `#[nuw]` - only valid without `#[saturating]` and with `#[unsigned]`; poison on unsigned overflow

---

## Widening Binary Instructions

Widening instructions compute `a OP b` at the full precision of the *output* type - the inputs are sign- or zero-extended to the output width before the operation. The output type `T2` must be at least as wide as the input type `T1` (strictly wider is the normal case; equal width is permitted and behaves identically to the non-widening form). Both scalar and vector forms are supported; for vectors, the lane count stays the same and only the element width widens.

- `let T2:%out = .widening_add(T1:%a, T1:%b)` - Adds `a` and `b`, returning the result in the wider type `T2`. For integers, inputs are sign-extended (default) or zero-extended (`#[unsigned]`) to the output width before addition. For floats, inputs are precision-extended before the addition.

    `T1` and `T2` must share the same kind (integer->integer, float/bfloat->float, or `<T0,M>`->`<T0,M>`). `bitwidth(T2) >= bitwidth(T1)`.

    **If `T1`/`T2` base type is integer:**
    - `#[unsigned]` - zero-extend inputs; default is sign-extend
    - `#[nsw]` - poison on signed overflow of the *widened* result (rarely needed since widening usually prevents overflow)
    - `#[nuw]` - poison on unsigned overflow of the widened result; only valid with `#[unsigned]`

    **If `T1`/`T2` base type is float/bfloat:** `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T2:%out = .widening_sub(T1:%a, T1:%b)` - Subtracts `b` from `a`, returning the result in the wider type `T2`. Same extension and attribute rules as `.widening_add`.

- `let T2:%out = .widening_mul(T1:%a, T1:%b)` - Multiplies `a` and `b`, returning the full-width product in `T2`. Same extension rules as `.widening_add`.

    `T1` and `T2` must share the same kind (integer->integer, float/bfloat->float, or `<T0,M>`->`<T0,M>`). `bitwidth(T2) >= bitwidth(T1)`.

    **If `T1`/`T2` base type is integer:**
    - `#[unsigned]` - treat both inputs as unsigned before extension
    - `#[nsw]` - poison if the result does not fit in the *input* type range (i.e. overflow would have occurred at the narrow width)
    - `#[nuw]` - same but unsigned; only valid with `#[unsigned]`

    **If `T1`/`T2` base type is float/bfloat:** `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

---

## Carrying / Borrow Arithmetic Instructions

These instructions thread a carry or borrow bit in and out, enabling multi-word arithmetic. All inputs and outputs are scalar; the carry/borrow is always `i1`. There are no direct vector forms - carry semantics are inherently sequential across words, so a carry chain over a vector is expressed as a loop over scalar words. Lanewise application is valid and expected: apply the instruction to one lane (word) per loop iteration, feeding the carry-out of iteration `i` as the carry-in of iteration `i+1`. The carry-in `%cin` must be `i1`; typically `0i1` for the least-significant word and the carry-out of the previous word for higher words. NOTE: You can use vector types also. We just convert it to a loop of scalar ops or to unrolled loops of scalar ops under the hood. This allows you to write more natural code when dealing with vectors of multi-word integers

- `let {T, i1}:%out = .carry_add(T:%a, T:%b, i1:%cin)` - Add with carry. Computes `a + b + cin`, returning the sum and carry-out as a struct `{T, i1}`. `T` must be `i<N>`. No overflow attributes - the carry-out is the mechanism for propagating overflow.

    - `#[unsigned]` - carry-out reflects unsigned overflow; default is signed carry semantics

- `let {T, i1}:%out = .carry_sub(T:%a, T:%b, i1:%bin)` - Subtract with borrow. Computes `a - b - bin`, returning the difference and borrow-out as a struct `{T, i1}`. `T` must be `i<N>`. Borrow-out is `1` if the subtraction underflowed (i.e., borrowed from the next word).

    - `#[unsigned]` - borrow-out reflects unsigned underflow; default is signed

- `let {T, i1}:%out = .carry_shl(T:%a, i1:%cin)` - Shift left by one bit with carry in/out. The incoming carry (`%cin`) fills the vacated LSB; the outgoing carry is the bit shifted out of the MSB. Equivalent to `(a << 1) | cin` with carry-out = `a >> (bitwidth-1)`. `T` must be `i<N>`. No attributes.

- `let {T, i1}:%out = .carry_lshr(T:%a, i1:%cin)` - Logical shift right by one bit with carry in/out. The incoming carry fills the vacated MSB; the outgoing carry is the bit shifted out of the LSB. `T` must be `i<N>`. No attributes.

- `let {T, i1}:%out = .carry_ashr(T:%a, i1:%cin)` - Arithmetic shift right by one bit with carry out. The MSB is filled by the sign bit; `%cin` is unused for the fill but included for API uniformity. Carry-out is the bit shifted out of the LSB. `T` must be `i<N>`. No attributes.

- `let {T, T}:%out = .mac_wide(T:%a, T:%b, T:%acc)` - Widening multiply-accumulate. Computes `(a * b) + acc` at double width, returning a struct `{high_word: T, low_word: T}`. `T` must be `i<N>`.

    - `#[unsigned]` - unsigned widening multiply; default is signed

- `let {T, T}:%out = .widening_div(T:%dividend_hi, T:%dividend_lo, T:%divisor)` - Widening division. Divides a double-width dividend `(dividend_hi:dividend_lo)` by `divisor`, returning `{quotient: T, remainder: T}`. Equivalent to x86 `DIV`/`IDIV` with a `2N`-bit dividend. `T` must be `i<N>`. Poison if divisor is zero or if the quotient overflows `T`.

    - `#[unsigned]` - unsigned division; default is signed
    - `#[exact]` - poison if the remainder is non-zero

---

## Combined Quotient and Remainder (`divmod`)

- `let {T, T}:%out = .divmod(T:%a, T:%b)` - Returns both quotient and remainder from a single division, avoiding two separate hardware divides. `T` must be of the form `T0` or `<T0,M>` where `T0` is an integer. For vectors, the operation is lanewise.

    - `#[unsigned]` - unsigned division and remainder; default is signed

- `let {T, T}:%out = .divmod(T:%a, T:%b)` - Float variant: returns `{quotient: T, remainder: T}` where `quotient = integral_part(a / b)` and `remainder = a - quotient * b` (i.e. IEEE 754 remainder with truncation toward zero). `T` must be of the form `T0` or `<T0,M>` where `T0` is float/bfloat. For vectors, the operation is lanewise.

    Float-specific attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

---

## Overflow-Wrap (Checked Arithmetic) Instructions

These return `{T, i1}` - the wrapped result paired with an overflow flag (`1` if overflow occurred, `0` if not). Useful for implementing checked arithmetic in safe languages. `T` must be `i<N>` or `<i<N>,M>` (vector form is lanewise; each lane produces its own flag bit). For vectors the return type is `{<T,M>, <i1,M>}`.

- `let {T, i1}:%out = .add_wrap(T:%a, T:%b)` - Adds `a` and `b` with wrapping, returning the wrapped result and an overflow flag.

    - `#[unsigned]` - detect unsigned overflow; default detects signed overflow

- `let {T, i1}:%out = .sub_wrap(T:%a, T:%b)` - Subtracts `b` from `a` with wrapping, returning the wrapped result and an underflow/overflow flag.

    - `#[unsigned]` - detect unsigned underflow; default detects signed overflow

- `let {T, i1}:%out = .mul_wrap(T:%a, T:%b)` - Multiplies `a` and `b` with wrapping, returning the wrapped result and an overflow flag.

    - `#[unsigned]` - detect unsigned overflow; default detects signed overflow

---

## High-Half Multiply

- `let T:%out = .mulhi(T:%a, T:%b)` - Returns the **high half** of the full `NxN->2N` product of `a` and `b`. Equivalent to `widening_mul(a, b) >> bitwidth(T)` but does not require a `2xbitwidth(T)` output type - useful when `T` is `i64` and no `i128` type exists(I mean we do emulate i128 but why bother). `T` must be of the form `T0` or `<T0,M>` where `T0` is an integer. For vectors, the operation is lanewise.

    - `#[unsigned]` - unsigned multiply; default is signed

---

## N-Bit Carry Shifts

These extend the 1-bit carry shift instructions to handle a shift count of more than one bit at a time, enabling multi-word arbitrary-amount shifts without a loop of single-bit steps. Each instruction shifts one word by `shift` bits and threads the displaced bits as a full-word carry between words. Only the low `shift` bits of the carry operands are meaningful.

`T` must be `i<N>`. Vector form is allowed and is equivalent to a loop of scalar or unrolled loop of scalar ops

- `let {T, T}:%out = .shl_carry_n(T:%a, T:%shift, T:%carry_in)` - Left shift by N with carry. Shifts `a` left by `shift` bits. The low `shift` bits of `carry_in` fill the vacated LSBs. Returns `{result, carry_out}` where `carry_out` holds the `shift` MSBs that were displaced, positioned in the low bits (ready to pass as `carry_in` to the next word).

    Formally: `result = (a << shift) | (carry_in & mask(shift))`, `carry_out = a >> (bitwidth(T) - shift)`. No attributes.

- `let {T, T}:%out = .lshr_carry_n(T:%a, T:%shift, T:%carry_in)` - Logical right shift by N with carry. Shifts `a` right by `shift` bits logically. The low `shift` bits of `carry_in` fill the vacated MSBs (shifted into the top). Returns `{result, carry_out}` where `carry_out` holds the `shift` LSBs that were displaced, in the low positions.

    Formally: `result = (a >> shift) | (carry_in << (bitwidth(T) - shift))`, `carry_out = a & mask(shift)`. Process words high-to-low, feeding carry-out of word `i` as carry-in of word `i-1`. No attributes.

- `let {T, T}:%out = .ashr_carry_n(T:%a, T:%shift, T:%carry_in)` - Arithmetic right shift by N with carry. Same as `.lshr_carry_n` but the sign bit of `a` propagates into the `shift` vacated MSBs of the **most significant word only**. For all other words in the chain, pass the carry-out of the word above as `carry_in`, just as with `.lshr_carry_n`. Carry-out is the `shift` displaced LSBs in low positions. No attributes.

---

## Bitwise Binary Instructions

- `let T:%output_var = .and(T:%input_var1, T:%input_var2)` - Bitwise AND. T must be `i<N>` or `<i<N>,M>`. No attributes.

- `let T:%output_var = .or(T:%input_var1, T:%input_var2)` - Bitwise OR. T must be `i<N>` or `<i<N>,M>`.
    - `#[disjoint]` - asserts that no bit is set in both inputs (i.e. inputs have no bits in common); poison if violated

- `let T:%output_var = .xor(T:%input_var1, T:%input_var2)` - Bitwise XOR. T must be `i<N>` or `<i<N>,M>`. No attributes.

- `let T:%output_var = .nand(T:%input_var1, T:%input_var2)` - Bitwise NAND. T must be `i<N>` or `<i<N>,M>`. No attributes.

- `let T:%output_var = .nor(T:%input_var1, T:%input_var2)` - Bitwise NOR. T must be `i<N>` or `<i<N>,M>`.
    - `#[disjoint]` - asserts that no bit is set in both inputs; poison if violated

- `let T:%output_var = .xnor(T:%input_var1, T:%input_var2)` - Bitwise XNOR. T must be `i<N>` or `<i<N>,M>`. No attributes.

- `let T:%output_var = .shl(T:%input_var1, T:%input_var2)` - Shift left. T must be `i<N>` or `<i<N>,M>`.
    - `#[nsw]` - poison if the shift causes signed overflow
    - `#[nuw]` - poison if any shifted-out bit is non-zero

- `let T:%output_var = .lshr(T:%input_var1, T:%input_var2)` - Logical shift right. T must be `i<N>` or `<i<N>,M>`.
    - `#[exact]` - poison if any bits shifted out are non-zero

- `let T:%output_var = .ashr(T:%input_var1, T:%input_var2)` - Arithmetic shift right. T must be `i<N>` or `<i<N>,M>`.
    - `#[exact]` - poison if any bits shifted out are non-zero

- `let T:%output_var = .rotl(T:%input_var1, T:%input_var2)` - Rotate left. Bits shifted out on the left are rotated back in on the right. T must be of the form `T0` or `<T0,M>` where T0 is some integer. Shift amount is taken modulo bitwidth. No attributes.

- `let T:%output_var = .rotr(T:%input_var1, T:%input_var2)` - Rotate right. Bits shifted out on the right are rotated back in on the left. T must be of the form `T0` or `<T0,M>` where T0 is some integer. Shift amount is taken modulo bitwidth. No attributes.

- `let T:%out = .pext(T:%src, T:%mask)` - Parallel bit extract. Extracts bits from `src` at positions where `mask` has a 1 bit, compacting them into the contiguous low bits of the result. The number of meaningful result bits equals `popcount(mask)`; remaining high bits are zero. Corresponds to x86 BMI2 `PEXT`. `T` must be `i<N>` or `<i<N>,M>`. No attributes.

- `let T:%out = .pdep(T:%src, T:%mask)` - Parallel bit deposit. Inverse of `.pext`. Deposits bits from the consecutive low bits of `src` into the output at positions where `mask` has a 1 bit. All other output bits are zero. Corresponds to x86 BMI2 `PDEP`. `T` must be `i<N>` or `<i<N>,M>`. No attributes.

---

## Trinary Bitwise Instructions

- `let T:%output_var = .fshl(T:%input_var1, T:%input_var2, T:%shift)` - Funnel shift left. Conceptually concatenates `input_var1:input_var2`, shifts left by `shift mod bitwidth`, and returns the high T-sized bits. T must be of the form `T0` or `<T0,M>` where T0 is some integer. No attributes.

- `let T:%output_var = .fshr(T:%input_var1, T:%input_var2, T:%shift)` - Funnel shift right. Conceptually concatenates `input_var1:input_var2`, shifts right by `shift mod bitwidth`, and returns the low T-sized bits. T must be of the form `T0` or `<T0,M>` where T0 is some integer. No attributes.

- `let T:%out = .bitblend(T:%mask, T:%a, T:%b)` - Bitwise blend / masked merge. Computes `(a & mask) | (b & ~mask)`. For each bit position: if the mask bit is 1, take from `a`; if 0, take from `b`. `T` must be `i<N>` or `<i<N>,M>`. No attributes.


---

## Comparison Instructions

- `let T1:%output_var = .eq(T:%input_var1, T:%input_var2)` - Equality comparison. T can be of the form `T0` or `<T0,M>` where T0 is float/bfloat/integer/ptr. Output is `i1` or `<i1,M>`.

    If `T0` is float/bfloat:
    - `#[unordered]` - result is true if either input is NaN. Default (ordered): result is false if either input is NaN.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T1:%output_var = .neq(T:%input_var1, T:%input_var2)` - Inequality comparison. Same type rules and attributes as `.eq`.

- `let T1:%output_var = .gt(T:%input_var1, T:%input_var2)` - Greater-than comparison. T can be of the form `T0` or `<T0,M>` where T0 is float/bfloat/integer/ptr. Output is `i1` or `<i1,M>`.

    If `T0` is integer:
    - `#[unsigned]` - unsigned comparison; default is signed

    If `T0` is ptr: always unsigned, no signedness attribute.

    If `T0` is float/bfloat:
    - `#[unordered]` - result is true if either input is NaN. Default: false if either input is NaN.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T1:%output_var = .lt(T:%input_var1, T:%input_var2)` - Less-than comparison. Same type rules and attributes as `.gt`.

- `let T1:%output_var = .ge(T:%input_var1, T:%input_var2)` - Greater-than-or-equal comparison. Same type rules and attributes as `.gt`.

- `let T1:%output_var = .le(T:%input_var1, T:%input_var2)` - Less-than-or-equal comparison. Same type rules and attributes as `.gt`.

- `let T1:%output_var = .either_nan(T:%input_var1, T:%input_var2)` - Returns true if either input is NaN. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat. Output is `i1` or `<i1,M>`.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T1:%output_var = .neither_nan(T:%input_var1, T:%input_var2)` - Returns true if neither input is NaN. Same type rules and attributes as `.either_nan`.

- `let T1:%output_var = .both_nan(T:%input_var1, T:%input_var2)` - Returns true if both inputs are NaN. Same type rules and attributes as `.either_nan`.

---

## Conversion Instructions

- `let T2:%output_var = .trunc(T1:%input_var)` - Truncates from a wider to a narrower type. Base type of T1 and T2 must match in kind (integer->integer, float->float). Bitwidth of T1's base type must be strictly greater than T2's. Both must be vector or both non-vector.

    If base type is integer:
    - `#[nsw]` - poison if the truncated value does not sign-extend back to the original
    - `#[nuw]` - poison if the truncated value does not zero-extend back to the original
    - `#[saturating]` - clamp to the integer type range instead of UB when the float value is out of range or NaN; pair with `#[unsigned]` for unsigned saturation; default is signed saturation when this flag is set

    If base type is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T2:%output_var = .ext(T1:%input_var)` - Extends from a narrower to a wider type. Base type of T1 and T2 must match in kind. Bitwidth of T1's base type must be strictly less than T2's. Both must be vector or both non-vector.

    If base type is integer:
    - `#[unsigned]` - zero-extension (equivalent to LLVM `zext`); default is sign-extension
    - `#[nsb]` - only valid with `#[unsigned]`; asserts the source value's sign bit is 0, giving a tighter range (e.g. `i8` range becomes `[0,127]` instead of `[0,255]`)

    If base type is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T2:%output_var = .float_to_int(T1:%input_var)` - Converts float/bfloat (or vector thereof) T1 to integer (or vector thereof) T2. Output type determines the target integer width and kind.

    - `#[unsigned]` - produce an unsigned integer; default is signed
    - `#[nsb]` - only valid with `#[unsigned]`; asserts the result's sign bit is 0
    - `#[saturating]` - clamp to the integer type range instead of UB when the float value is out of range or NaN; pair with `#[unsigned]` for unsigned saturation; default is signed saturation when this flag is set

    If base type is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T2:%output_var = .int_to_float(T1:%input_var)` - Converts integer (or vector thereof) T1 to float/bfloat (or vector thereof) T2. Output type determines the target float kind.

    - `#[unsigned]` - treat the source integer as unsigned; default is signed
    - `#[nsb]` - only valid with `#[unsigned]`; asserts the source integer's sign bit is 0

    If base type is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T2:%output_var = .ptr_to_int(T1:%input_var)` - Converts pointer/vector-of-pointer T1 to `i64`/`<i64,M>` T2. Only `i64` is valid (64-bit systems only). Use `.trunc` after if a narrower integer is needed. No attributes.

- `let T2:%output_var = .int_to_ptr(T1:%input_var)` - Converts `i64`/`<i64,M>` T1 to pointer/vector-of-pointer T2. Only `i64` is valid (64-bit systems only). Use `.ext` before if the source is a narrower integer. No attributes.

- `let T2:%output_var = .bitcast(T1:%input_var)` - Reinterprets the bits of T1 as type T2. T1 and T2 must have the same bitwidth. Cannot bitcast between `i64` and `ptr`.

    If type is float/vector of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

---

## Unary Instructions

- `let T:%output_var = .neg(T:%input_var)` - Negates a value. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat/integer. Note: not the same as `.sub(0, x)` for floats - `.neg` produces `-0.0` when input is `+0.0`, whereas `.sub` produces `+0.0`.

    If `T0` is integer:
    - `#[nsw]` - poison if the result overflows (i.e. input is `INT_MIN`)

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .not(T:%input_var)` - Bitwise NOT. T must be of the form `T0` or `<T0,M>` where T0 is some integer. No attributes.

- `let T:%output_var = .abs(T:%input_var)` - Absolute value. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat/integer. For integer, signed is always assumed (unsigned integers are always non-negative).

    If `T0` is integer:
    - `#[nsw]` - poison if input is `INT_MIN` (whose absolute value overflows)

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .ceil(T:%input_var)` - Rounds up to the nearest integer, same float type. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .floor(T:%input_var)` - Rounds down to the nearest integer, same float type. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .integral_part(T:%input_var)` - Returns the integer part of a float (rounds toward zero), same float type. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .fractional_part(T:%input_var)` - Returns the fractional part of a float (i.e. `x - integral_part(x)`), same float type. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .roundnearest(T:%input_var)` - Rounds to the nearest integer (ties away from zero), same float type. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .roundeven(T:%input_var)` - Rounds to the nearest integer (ties to even / banker's rounding), same float type. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .sqrt(T:%input_var)` - Square root. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .reciprocal(T:%input_var)` - Reciprocal (`1/x`). T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat.

    - `#[approx]` - permits a faster but less accurate approximation (e.g. `RCPSS`); default is exact
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .rsqrt(T:%input_var)` - Reciprocal square root (`1/sqrt(x)`). T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat.

    - `#[approx]` - permits a faster but less accurate approximation (e.g. `RSQRTSS`); default is exact
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .popcount(T:%input_var)` - Count of set bits. T must be of the form `T0` or `<T0,M>` where T0 is some integer. Output type is `iN/<iN,M>` matching the input bitwidth. No attributes.

- `let T:%output_var = .clz(T:%input_var)` - Count leading zeros. T must be of the form `T0` or `<T0,M>` where T0 is some integer. Output type is `iN/<iN,M>` matching the input bitwidth. When input is zero, result is the bitwidth unless `#[zero_poison]` is set.

    - `#[zero_poison]` - result is poison when input is zero

- `let T:%output_var = .ctz(T:%input_var)` - Count trailing zeros. T must be of the form `T0` or `<T0,M>` where T0 is some integer. Output type is `iN/<iN,M>` matching the input bitwidth. When input is zero, result is the bitwidth unless `#[zero_poison]` is set.

    - `#[zero_poison]` - result is poison when input is zero

- `let T:%output_var = .parity(T:%input_var)` - Parity of an integer. Returns `i1/<i1,M>`: 1 if the number of set bits is odd, 0 if even. T must be of the form `T0` or `<T0,M>` where T0 is some integer. No attributes.

- `let T:%output_var = .bswap(T:%input_var)` - Reverses byte order. T must be of the form `T0` or `<T0,M>` where T0 is integer/float/bfloat. Bitwidth must be a multiple of 8. Float/bfloat is supported because endianness swaps on floats are common; without this you would need a bitcast. Fast math attribute if T is float/bfloat. No attributes if T is integer.

- `let T:%output_var = .bitreverse(T:%input_var)` - Reverses bit order. T must be of the form `T0` or `<T0,M>` where T0 is some integer. No attributes.

- `let T:%out = .clrsb(T:%input)` - Count leading redundant sign bits. Returns the number of leading bits equal to the sign bit, **not counting the sign bit itself**. Equivalently: `clz(x >= 0 ? x : ~x) - 1`. `T` must be of the form `T0` or `<T0,M>` where `T0` is a **signed** integer. Output type matches input. No attributes.

- `let T:%out = .blsi(T:%input)` - Isolate lowest set bit. Returns a value with only the lowest set bit of `%input` set; `0` if `%input` is `0`. Equivalent to `x & -x`. `T` must be `i<N>` or `<i<N>,M>`. No attributes.

- `let T:%out = .blsr(T:%input)` - Reset lowest set bit. Returns `%input` with its lowest set bit cleared; `0` if `%input` is `0`. Equivalent to `x & (x-1)`. `T` must be `i<N>` or `<i<N>,M>`. No attributes.

- `let T:%out = .blsmask(T:%input)` - Get mask up to lowest set bit. Returns a mask with all bits set up to and including the lowest set bit of `%input` (e.g. `0b10100 -> 0b00111`); all bits set (`-1`) if `%input` is `0`. Equivalent to `x ^ (x-1)`. `T` must be `i<N>` or `<i<N>,M>`. No attributes.

---

## Numerical Classification Instructions
### Float Classification Instructions

All instructions in this section: T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat. Output is `i1` or `<i1,M>`. All accept: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let i1:%output_var = .isnan(T:%input_var)` - True if the value is NaN.
- `let i1:%output_var = .isinf(T:%input_var)` - True if the value is ±infinity.
- `let i1:%output_var = .isfinite(T:%input_var)` - True if the value is finite (not NaN and not infinity).
- `let i1:%output_var = .isnormal(T:%input_var)` - True if the value is a normal float (not NaN, not infinity, not subnormal, not zero).
- `let i1:%output_var = .issubnormal(T:%input_var)` - True if the value is subnormal/denormal.
- `let i1:%output_var = .iszero(T:%input_var)` - True if the value is +0.0 or -0.0. Distinct from `.eq` with zero due to signed-zero semantics.
- `let i1:%output_var = .isnegative(T:%input_var)` - True if the sign bit is set. Returns true for negative zero and negative NaN.
- `let i1:%output_var = .ispositive(T:%input_var)` - True if the sign bit is clear. Returns true for positive zero.

---

## Memory Instructions

- `let ptr:$global_var = .global(T:value)` - Defines a global variable. Output must be a pointer type; `$global_var` holds the address. Value must be a constant expression (not a variable). Not part of MIR; stored in the module's global section.

    - `#[align(i8:N)]` - alignment of the global in bytes; must be a power of 2; default is 16
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination if T is float/vec of float

- `let T:%local_var = .local(T:initial_value)` - Defines and initializes a local variable. Value can be anything. Present for parser simplicity; does little in MIR. T can be any type. 

    If T is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let ptr:%local_var = .alloca(iN:%size)` - Allocates `size` bytes on the stack. Returns a pointer to the allocation.

    - `#[align(i8:N)]` - alignment of the allocation in bytes; must be a power of 2; default is 16

- `let T:%output_var = .load(ptr:%ptr)` - Loads a value of type T from memory.

    - `#[align(i8:N)]` - alignment of the pointer; must be a power of 2; required if atomic; default is 16
    - `#[volatile]` - volatile load; not elided or reordered
    - `#[invariant.load]` - the loaded value will not change during program execution
    - `#[nontemporal]` - non-temporal (cache-bypassing) load
    - `#[nonnull]` - asserts the pointer is not null
    - `#[nopoison]` - asserts the loaded value is not poison
    - `#[nsb]` - asserts the loaded integer's sign bit is 0 (tighter range for optimizer)
    - `#[dereferenceable(i64:N)]` - asserts the pointer is dereferenceable for N bytes
    - `#[atomic(str:ordering)]` - atomic load; ordering must be one of: `acquire`, `monotonic`, `unordered`, `seq_cst`
    - `#[syncscope("singlethreaded")]` - only valid with `#[atomic]`; synchronizes only with atomic ops in the same thread; default is global

    If T is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.store(T:%value, ptr:%ptr)` - Stores a value to memory.

    - `#[align(i8:N)]` - alignment of the pointer; must be a power of 2; required if atomic; default is 16
    - `#[volatile]` - volatile store
    - `#[nontemporal]` - non-temporal (cache-bypassing) store
    - `#[nonnull]` - asserts the pointer is not null
    - `#[nopoison]` - asserts the value being stored is not poison
    - `#[dereferenceable(i64:N)]` - asserts the pointer is dereferenceable for N bytes
    - `#[atomic(str:ordering)]` - atomic store; ordering must be one of: `release`, `monotonic`, `unordered`, `seq_cst`
    - `#[syncscope("singlethreaded")]` - only valid with `#[atomic]`; default is global

    If T is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T,N>:%out = .masked_load(ptr:%ptr, <i1,N>:%mask, <T,N>:%passthru)` - Loads elements from memory into a vector, but only for lanes where the mask is true. Lanes where the mask is false take their value from `passthru` instead.

    - `ptr:%ptr` - pointer to the base address; must be valid for at least `N * sizeof(T)` bytes for active lanes
    - `<i1,N>:%mask` - per-lane predicate; true = load from memory, false = take from passthru
    - `<T,N>:%passthru` - values used for inactive lanes; T can be any integer, float, bfloat, or ptr

    Attributes:
    - `#[align(i8:N)]` - alignment of `ptr` in bytes; must be a power of 2; default is 1 (unaligned is the safe default since masked loads are often used for tail handling where alignment cannot be guaranteed)
    - `#[volatile]` - volatile load; not elided or reordered
    - `#[nontemporal]` - non-temporal (cache-bypassing) load for active lanes
    - `#[nonnull]` - asserts `ptr` is not null
    - `#[dereferenceable(i64:N)]` - asserts `ptr` is dereferenceable for N bytes across the entire vector range (not just active lanes)
    - `#[zeropassthru]` - shorthand: inactive lanes are zeroed; equivalent to passing a zero vector as passthru but allows the backend to emit a zeroing-masked instruction directly rather than materializing a zero vector

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.masked_store(<T,N>:%val, ptr:%ptr, <i1,N>:%mask)` - Stores elements to memory only for lanes where the mask is true. Inactive lanes do not produce any memory write - not even to a padding location.

    - `<T,N>:%val` - vector of values to store; T can be any integer, float, bfloat, or ptr
    - `ptr:%ptr` - base address
    - `<i1,N>:%mask` - per-lane predicate; true = store to memory, false = no write

    No output.

    Attributes:
    - `#[align(i8:N)]` - alignment of `ptr`; must be a power of 2; default is 1
    - `#[volatile]` - volatile store
    - `#[nontemporal]` - non-temporal stores for active lanes
    - `#[nonnull]` - asserts `ptr` is not null
    - `#[dereferenceable(i64:N)]` - asserts `ptr` is dereferenceable for the full vector range

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T,N>:%out = .gather(<ptr,N>:%ptrs, <i1,N>:%mask, <T,N>:%passthru)` - Loads one scalar element per lane from a distinct pointer. Each lane `i` loads from `ptrs[i]`. Inactive lanes (where mask is false) take their value from `passthru`.

    - `<ptr,N>:%ptrs` - vector of N pointers, one per lane
    - `<i1,N>:%mask` - per-lane predicate; true = load from `ptrs[i]`, false = use `passthru[i]`
    - `<T,N>:%passthru` - fallback values for inactive lanes; T can be any integer, float, or bfloat

    Attributes:
    - `#[align(i8:N)]` - alignment guarantee for each individual pointer in the vector; default is 1
    - `#[volatile]` - volatile gather
    - `#[nonnull]` - asserts all active pointers are non-null
    - `#[dereferenceable(i64:N)]` - asserts all active pointers are dereferenceable for N bytes
    - `#[zeropassthru]` - inactive lanes are zeroed; allows the backend to emit a zeroing-masked instruction directly rather than materializing a zero vector

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.scatter(<T,N>:%val, <ptr,N>:%ptrs, <i1,N>:%mask)` - Stores one scalar element per lane to a distinct pointer. Each lane `i` stores `val[i]` to `ptrs[i]`. Inactive lanes produce no write. If two active lanes write to the same address, the result is undefined (no ordering guarantee). 

    - `<T,N>:%val` - values to scatter; T can be any integer, float, or bfloat
    - `<ptr,N>:%ptrs` - vector of N destination pointers
    - `<i1,N>:%mask` - per-lane predicate

    No output.

    Attributes:
    - `#[align(i8:N)]` - per-pointer alignment guarantee; default is 1
    - `#[volatile]` - volatile scatter
    - `#[nonnull]` - asserts all active pointers are non-null
    - `#[dereferenceable(i64:N)]` - asserts all active pointers are dereferenceable for N bytes

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.prefetch(ptr:%addr)` - Emits a prefetch hint to bring a cache line into the specified cache level before it is needed. Not a memory operation - has no effect on program semantics, cannot fault, and may be ignored by the hardware.

    - `ptr:%addr` - address to prefetch; does not need to be valid (a bad address is silently ignored by the hardware)

    No output.

    Attributes:
    - `#[write]` - prefetch for write (`PREFETCHW`); hints that the line will be modified, so it is fetched in exclusive/modified state to avoid a later RFO (Request For Ownership); default is read-only prefetch
    - `#[locality(i8:N)]` - temporal locality hint, 0–3:
        - `0` - no temporal locality; use `PREFETCHNTA`, pulls into L1 while minimizing cache pollution
        - `1` - low locality; `PREFETCHT2` (L3)
        - `2` - moderate locality; `PREFETCHT1` (L2)
        - `3` - high locality; `PREFETCHT0` (L1); this is the default
    - `#[instruction]` - prefetch into the instruction cache rather than the data cache; `#[write]` is invalid when `#[instruction]` is set; `#[locality]` still applies

- `.memcpy(ptr:%dest, ptr:%src, iN:%size)` - Copies `size` bytes from `src` to `dest`. Regions must not overlap; use `.memmove` if they may. The index `0` refers to `src` and `1` refers to `dest` in per-pointer attributes.

    - `#[volatile]` - volatile copy
    - `#[dest_align(i8:N)]` - alignment of the destination pointer; must be a power of 2; default is 16
    - `#[src_align(i8:N)]` - alignment of the source pointer; must be a power of 2; default is 16
    - `#[nontemporal(iN:idx...)]` - non-temporal access for the specified pointer(s); at least one index required
    - `#[nonnull(iN:idx...)]` - asserts the specified pointer(s) are not null; at least one index required
    - `#[nopoison(iN:idx...)]` - asserts the memory at the specified pointer(s) contains no poison; at least one index required
    - `#[dest_dereferenceable(i64:N)]` - asserts the destination pointer is dereferenceable for N bytes; default is no assertion
    - `#[src_dereferenceable(i64:N)]` - asserts the source pointer is dereferenceable for N bytes; default is no assertion

- `.memmove(ptr:%dest, ptr:%src, iN:%size)` - Copies `size` bytes from `src` to `dest`. Correct even if regions overlap. Same attributes as `.memcpy` with the same per-pointer index convention.

- `.memset(ptr:%dest, i8:%value, iN:%size)` - Fills `size` bytes at `dest` with `value`.

    - `#[volatile]` - volatile set
    - `#[align(i8:N)]` - alignment of `dest`; must be a power of 2; default is 16
    - `#[nontemporal]` - non-temporal stores
    - `#[nonnull]` - asserts `dest` is not null
    - `#[nopoison]` - asserts the region contains no poison
    - `#[dereferenceable(i64:N)]` - asserts `dest` is dereferenceable for N bytes

- `let i32:%output_var = .memcmp(ptr:%ptr1, ptr:%ptr2, iN:%size)` - Compares `size` bytes at `ptr1` and `ptr2`. Returns a negative, zero, or positive integer if the region at `ptr1` is respectively less than, equal to, or greater than the region at `ptr2`. The index `0` refers to `ptr1` and `1` refers to `ptr2` in per-pointer attributes.

    - `#[volatile]` - volatile compare
    - `#[ptr1_align(i8:N)]` - alignment of `ptr1`; must be a power of 2; default is 16
    - `#[ptr2_align(i8:N)]` - alignment of `ptr2`; must be a power of 2; default is 16
    - `#[nontemporal(iN:idx...)]` - non-temporal access for the specified pointer(s); at least one index required
    - `#[nonnull(iN:idx...)]` - asserts the specified pointer(s) are not null; at least one index required
    - `#[nopoison(iN:idx...)]` - asserts the memory at the specified pointer(s) contains no poison; at least one index required
    - `#[ptr1_dereferenceable(i64:N)]` - asserts `ptr1` is dereferenceable for N bytes; default is no assertion
    - `#[ptr2_dereferenceable(i64:N)]` - asserts `ptr2` is dereferenceable for N bytes; default is no assertion
    
- `let ptr:%output_var = .getaddress(T:%var, iN:%offset)` - Returns `&var + offset`. Output must be a pointer. `var` must be a variable (not a literal). Offset is in bytes. Note:-We have no seperate block address. If you want address of label just use this

    - `#[unsigned]` - offset is unsigned; default is signed
    - `#[nsw]` - poison if the offset causes signed overflow
    - `#[nuw]` - poison if the offset causes unsigned overflow
    - `#[inbounds]` - asserts the result pointer is within the bounds of the underlying object

    If T is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let ptr:%output_var = .ptroffset(ptr:%input_var, T:%offset)` - Returns `input_var + offset`. Output and input must be pointers. Offset can be any integer type. Offset is in bytes.

    - `#[unsigned]` - offset is unsigned; default is signed
    - `#[nsw]` - poison if the offset causes signed overflow
    - `#[nuw]` - poison if the offset causes unsigned overflow
    - `#[inbounds]` - asserts the result pointer is within the bounds of the underlying object

- `let ptr:%stack_ptr = .stacksave()` - Saves and returns the current stack pointer as an opaque pointer value. Used before a dynamic `.alloca` inside a loop to allow reclaiming the stack later. Do not dereference or manipulate the returned pointer; it is only valid as input to `.stackrestore`. No attributes.

- `.stackrestore(ptr:%stack_ptr)` - Restores the stack pointer to the value saved by `.stacksave`, effectively freeing any dynamic allocations made since the save. The input must be a value previously returned by `.stacksave`. No attributes.

- `let T3:%output_var = .extractelement(T1:%input, T2:%index)` - Extracts element at `index` from a vector/array/struct. `T1` is the aggregate, `T2` is integer index type `iN`, `T3` is the element type. For structs, index must be an integer literal. For arrays and vectors, index can be a literal or variable.

    - `#[inbounds]` - valid for array and vector only; asserts index is within bounds; not valid for struct (struct access is always in bounds)

    If T3 is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T1:%output_var = .insertelement(T1:%input, T2:%element, T3:%index)` - Returns a copy of the aggregate with the element at `index` replaced by `element`. Output type equals input aggregate type. `T3` is integer index type `iN`. For structs, index must be an integer literal. For arrays and vectors, index can be a literal or variable.

    - `#[inbounds]` - valid for array and vector only; not valid for struct

    If T2 is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.fence(str:ordering)` - Memory fence. Ordering and syncscope must be constant expressions. Valid orderings: `acquire`, `release`, `acq_rel`, `seq_cst`. Has no input or output; acts purely as a barrier.

    - `#[syncscope("singlethreaded")]` - synchronizes only with atomic ops in the same thread; default is global
    - `#[store_only]` - emit `SFENCE` (store fence only); valid orderings: `release`, `seq_cst`. Required after sequences of non-temporal stores to enforce visibility ordering. Mutually exclusive with `#[load_only]`.
    - `#[load_only]` - emit `LFENCE` (load fence only); valid orderings: `acquire`, `seq_cst`. Mutually exclusive with `#[store_only]`. Without either attribute, `.fence` maps to `MFENCE` (full fence).

- `let {T,i1}:%output_var = .atomic_cmpxchg(ptr:%ptr, T:%expected, T:%desired, str:success_ordering, str:failure_ordering)` - Atomically compares `*ptr` with `expected`. If equal, stores `desired` and returns `{original, true}`; otherwise leaves memory unchanged and returns `{original, false}`. `success_ordering` must be one of: `monotonic`, `acquire`, `release`, `acq_rel`, `seq_cst`. `failure_ordering` must be one of: `monotonic`, `acquire`, `seq_cst` (not `release` or `acq_rel`).

    - `#[align(i8:N)]` - required; alignment of the operation; must be a power of 2; default is 16
    - `#[volatile]` - volatile operation
    - `#[weak]` - weak CAS; permitted to spuriously fail even when `*ptr == expected`
    - `#[syncscope("singlethreaded")]` - synchronizes only with atomic ops in the same thread; default is global

    If T is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

### Cache Control Instructions

- `.clflush(ptr:%addr)` - Evicts the cache line containing `addr` from all levels of the CPU cache hierarchy, forcing the next access to reload from main memory. Corresponds to `CLFLUSH`. Has no effect if the address is not cached. Does not wait for the flush to complete; use `.fence` with `seq_cst` afterward if ordering is required. No output.

    - `#[opt]` - emit `CLFLUSHOPT` instead; allows more pipelining of multiple flushes but requires an explicit fence for ordering (the default `CLFLUSH` is self-serializing)

- `.clwb(ptr:%addr)` - Write back any dirty cache line containing `addr` to main memory while optionally retaining the line in cache in a non-dirty state. Corresponds to `CLWB`. More efficient than `.clflush` for persistent-memory write-back patterns where data will be re-read soon. No output. No attributes.

- `.cldemote(ptr:%addr)` - Hint to move the cache line containing `addr` to a more distant cache level (e.g., L1->L3). Corresponds to `CLDEMOTE`. Has no semantic effect; the CPU may ignore it. No output. No attributes.

### Lifetime and Invariant Scope Instructions

- `.lifetime_start(ptr:%ptr, i64:%size)` - Marks the beginning of the live range of a stack allocation. `%ptr` must be the result of an `.alloca`. `%size` is the size in bytes and must be a compile-time constant literal. Between a `lifetime_start` and `lifetime_end`, the memory is considered live; outside this range the optimizer may reuse the stack slot. Reading before start or after end is undefined behavior.

    - No attributes. No output.

- `.lifetime_end(ptr:%ptr, i64:%size)` - Marks the end of the live range of a stack allocation. Must have a matching `.lifetime_start` on all reaching control-flow paths. Same signature and restrictions. No attributes. No output.

- `let ptr:%scope = .invariant_start(ptr:%ptr, i64:%size)` - Asserts that the `%size` bytes of memory at `%ptr` will not be modified between this point and the matching `.invariant_end`. Returns an opaque `%scope` handle for the paired end. The size must be a compile-time constant literal. The optimizer may hoist loads, eliminate redundant reloads, and refine aliasing. Writing to the memory between start and end is undefined behavior. No attributes.

- `.invariant_end(ptr:%scope, ptr:%ptr, i64:%size)` - Ends the invariant scope established by `.invariant_start`. `%scope` must be the handle returned by the paired start. No additional attributes.

---

## Binary Arithmetic Fetch Modify Instructions

Read-modify-write instructions that read a value from memory, apply a binary operation with a given operand, write the result back, and return the original value. Can optionally be made atomic with `#[atomic](Note:If atomic then max size is limited to 128 bytes)

**Attributes shared by all fetch instructions:**
- `#[align(i8:N)]` - alignment of the pointer; must be a power of 2; default is 16
- `#[volatile]` - volatile operation
- `#[atomic(str:ordering)]` - makes the operation atomic; ordering must be one of: `monotonic`, `acquire`, `release`, `acq_rel`, `seq_cst`. If absent, the operation is not atomic.
- `#[syncscope("singlethreaded")]` - only valid with `#[atomic]`; synchronizes only within the same thread; default is global

---

- `let T:%old = .fetch_xchg(ptr:%ptr, T:%value)` - Replaces `*ptr` with `value`; returns the original. T can be integer or float.

    If T is float
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_add(ptr:%ptr, T:%value)` - Adds `value` to `*ptr`; returns the original. T can be integer or float.

    If T is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp instead of wrap; pair with `#[unsigned]` for unsigned saturation

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_sub(ptr:%ptr, T:%value)` - Subtracts `value` from `*ptr`; returns the original. T can be integer or float.

    If T is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp instead of wrap; pair with `#[unsigned]` for unsigned saturation

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_mul(ptr:%ptr, T:%value)` - Multiplies `*ptr` by `value`; returns the original. T can be integer or float.

    If T is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp instead of wrap; pair with `#[unsigned]` for unsigned saturation

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_div(ptr:%ptr, T:%value)` - Divides `*ptr` by `value`; returns the original. T can be integer or float.

    If T is integer:
    - `#[exact]` - poison if division is not exact
    - `#[unsigned]` - unsigned division; default is signed

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_rem(ptr:%ptr, T:%value)` - Computes `*ptr % value`; returns the original. T can be integer or float.

    If T is integer:
    - `#[unsigned]` - unsigned remainder; default is signed

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_copysign(ptr:%ptr, T:%value)` - Copies the sign of `value` onto `*ptr`; returns the original. T can be int or float

    If `T0` is integer: `#[nsw]` - poison if the result overflows (i.e. input is `INT_MIN`)

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_max(ptr:%ptr, T:%value)` - Replaces `*ptr` with `max(*ptr, value)`; returns the original. T can be integer or float.

    If T is integer:
    - `#[unsigned]` - unsigned max; default is signed

    If T is float/bfloat:
    - `#[unordered]` - if either operand is NaN, use the other (IEEE "maxNum"); default propagates NaN
    - `#[ieee754_2019]` - correct signed-zero ordering; when combined with `#[unordered]`, gets 754-2019 `maximumNumber` semantics. Combining with `#[nsz]` is a compile error. Only valid when T is float or bfloat.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_min(ptr:%ptr, T:%value)` - Replaces `*ptr` with `min(*ptr, value)`; returns the original. T can be integer or float.

    If T is integer:
    - `#[unsigned]` - unsigned min; default is signed

    If T is float/bfloat:
    - `#[unordered]` - if either operand is NaN, use the other (IEEE "minNum"); default propagates NaN
    - `#[ieee754_2019]` - correct signed-zero ordering; when combined with `#[unordered]`, gets 754-2019 `minimumNumber` semantics. Combining with `#[nsz]` is a compile error. Only valid when T is float or bfloat.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.
    
- `let T:%old = .fetch_avg(ptr:%ptr, T:%value)` - Fetch and average: reads `*ptr`, computes `avg(*ptr, value)`, writes back, and returns the original. Shared fetch attributes apply.

    **If `T` is integer:** Computes `(a + b + 1) >> 1` (rounds toward positive infinity, matching `PAVGB`/`PAVGW`). Default is signed.
    - `#[unsigned]` - treat `a` and `b` as unsigned; default is signed
    - `#[floor]` - round toward negative infinity (`(a + b) >> 1`) instead of the default ceiling
    - `#[nsw]` - poison if the intermediate sum `a + b` overflows before the shift
    - `#[nuw]` - poison on unsigned intermediate overflow; only valid with `#[unsigned]`

    **If `T` is float/bfloat:** Computes `(a + b) * 0.5` exactly.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

---

## Binary Bitwise Fetch Modify Instructions

Read-modify-write instructions that read a value from memory, apply a binary operation with a given operand, write the result back, and return the original value. Can optionally be made atomic with `#[atomic](Note:If atomic then max size is limited to 128 bytes)

**Attributes shared by all fetch instructions:**
- `#[align(i8:N)]` - alignment of the pointer; must be a power of 2; default is 16
- `#[volatile]` - volatile operation
- `#[atomic(str:ordering)]` - makes the operation atomic; ordering must be one of: `monotonic`, `acquire`, `release`, `acq_rel`, `seq_cst`. If absent, the operation is not atomic.
- `#[syncscope("singlethreaded")]` - only valid with `#[atomic]`; synchronizes only within the same thread; default is global

---

- `let T:%old = .fetch_and(ptr:%ptr, T:%value)` - Bitwise AND of `*ptr` and `value`; returns the original. T must be integer. No additional attributes.

- `let T:%old = .fetch_nand(ptr:%ptr, T:%value)` - Bitwise NAND of `*ptr` and `value`; returns the original. T must be integer. No additional attributes.

- `let T:%old = .fetch_or(ptr:%ptr, T:%value)` - Bitwise OR of `*ptr` and `value`; returns the original. T must be integer.
    - `#[disjoint]` - asserts no bit is set in both operands; poison if violated

- `let T:%old = .fetch_nor(ptr:%ptr, T:%value)` - Bitwise NOR of `*ptr` and `value`; returns the original. T must be integer.
    - `#[disjoint]` - asserts no bit is set in both operands; poison if violated

- `let T:%old = .fetch_xor(ptr:%ptr, T:%value)` - Bitwise XOR of `*ptr` and `value`; returns the original. T must be integer. No additional attributes.

- `let T:%old = .fetch_xnor(ptr:%ptr, T:%value)` - Bitwise XNOR of `*ptr` and `value`; returns the original. T must be integer. No additional attributes.

- `let T:%old = .fetch_shl(ptr:%ptr, T:%value)` - Left-shifts `*ptr` by `value`; returns the original. T must be integer.
    - `#[nsw]` - poison if shift causes signed overflow
    - `#[nuw]` - poison if any shifted-out bit is non-zero

- `let T:%old = .fetch_lshr(ptr:%ptr, T:%value)` - Logical right-shifts `*ptr` by `value`; returns the original. T must be integer.
    - `#[exact]` - poison if any bits shifted out are non-zero

- `let T:%old = .fetch_ashr(ptr:%ptr, T:%value)` - Arithmetic right-shifts `*ptr` by `value`; returns the original. T must be integer.
    - `#[exact]` - poison if any bits shifted out are non-zero

- `let T:%old = .fetch_rotl(ptr:%ptr, T:%value)` - Rotates `*ptr` left by `value`; returns the original. T must be integer. No additional attributes.

- `let T:%old = .fetch_rotr(ptr:%ptr, T:%value)` - Rotates `*ptr` right by `value`; returns the original. T must be integer. No additional attributes.

- `let T:%old = .fetch_pext(ptr:%ptr, T:%mask)` - Does what you would expect.`T` must be `i<N>`. No attributes.

- `let T:%old = .fetch_pdep(ptr:%ptr, T:%mask)` - Does what you would expect.`T` must be `i<N>`. No attributes.

---

## Unary Fetch Modify Instructions

Read-modify-write instructions that apply a unary operation to the value at a memory location and return the original value. Can optionally be made atomic with `#[atomic]`(Note:If atomic then max size is limited to 128 bytes)

**Attributes shared by all unary fetch instructions:** same as Binary Fetch - `#[align(i8:N)]` (default is 16), `#[volatile]`, `#[atomic(str:ordering)]`, `#[syncscope("singlethreaded")]`.

---

- `let T:%old = .fetch_neg(ptr:%ptr)` - Negates `*ptr`; returns the original. T can be integer or float.

    If T is integer:
    - `#[nsw]` - poison if result overflows (input is `INT_MIN`)

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_not(ptr:%ptr)` - Bitwise NOT of `*ptr`; returns the original. T must be integer. No additional attributes.

- `let T:%old = .fetch_abs(ptr:%ptr)` - Absolute value of `*ptr`; returns the original. T can be integer or float. For integer, signed is assumed.

    If T is integer:
    - `#[nsw]` - poison if input is `INT_MIN`
    - `#[nuw]` - poison if input is negative

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_ceil(ptr:%ptr)` - Ceiling of `*ptr`; returns the original. T must be float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_floor(ptr:%ptr)` - Floor of `*ptr`; returns the original. T must be float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_integral_part(ptr:%ptr)` - Integral part (round toward zero) of `*ptr`; returns the original. T must be float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_fractional_part(ptr:%ptr)` - Fractional part of `*ptr`; returns the original. T must be float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_roundnearest(ptr:%ptr)` - Rounds `*ptr` to the nearest integer (ties away from zero); returns the original. T must be float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_roundeven(ptr:%ptr)` - Rounds `*ptr` to the nearest integer (ties to even); returns the original. T must be float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_sqrt(ptr:%ptr)` - Square root of `*ptr`; returns the original. T must be float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_reciprocal(ptr:%ptr)` - Reciprocal of `*ptr`; returns the original. T must be float/bfloat.

    - `#[approx]` - permits a faster but less accurate approximation; default is exact
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_rsqrt(ptr:%ptr)` - Reciprocal square root of `*ptr`; returns the original. T must be float/bfloat.

    - `#[approx]` - permits a faster but less accurate approximation; default is exact
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_popcount(ptr:%ptr)` - Count of set bits in `*ptr`; returns the original. T must be integer. No additional attributes.

- `let T:%old = .fetch_clz(ptr:%ptr)` - Count leading zeros of `*ptr`; returns the original. T must be integer.
    - `#[zero_poison]` - result is poison when `*ptr` is zero

- `let T:%old = .fetch_ctz(ptr:%ptr)` - Count trailing zeros of `*ptr`; returns the original. T must be integer.
    - `#[zero_poison]` - result is poison when `*ptr` is zero

- `let T:%old = .fetch_parity(ptr:%ptr)` - Parity of `*ptr` (1 if odd number of set bits, 0 if even); returns the original. T must be integer. No additional attributes.

- `let T:%old = .fetch_bswap(ptr:%ptr)` - Reverses byte order of `*ptr`; returns the original. T must be integer or float/bfloat. Float/bfloat supported for endianness swaps (avoids needing a bitcast). Bitwidth must be a multiple of 8.

    If T is float/bfloat:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_bitreverse(ptr:%ptr)` - Reverses bit order of `*ptr`; returns the original. T must be integer. No additional attributes.

- `let T:%old = .fetch_clrsb(ptr:%ptr)` - Does what u think it does. T must be integer. No additional attributes.

- `let T:%old = .fetch_blsi(ptr:%ptr)` - Does what u think it does. `T` must be `i<N>`. No attributes.

- `let T:%old = .fetch_blsr(ptr:%ptr)` - Does what u think it does. `T` must be `i<N>`. No attributes.

- `let T:%old = .fetch_blsmask(ptr:%ptr)` - Does what u think it does. `T` must be `i<N>`. No attributes.
 
---

## Terminator Instructions

A terminator must be the final instruction of every block. Falling through to the next block without an explicit branch is an error.
 
- `.ret` / `.ret(T:%return_value)` - Returns from the function. Use `.ret` with no value for void functions. For non-void functions, the return value must match the function's return type.
    - `#[noreturn]` - indicates the function never actually returns; `.ret` with no value is then permitted even for non-void functions

    If T is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.unreachable` - Marks a point in the code that is statically known to never be reached. A hint to the compiler; has no guaranteed runtime effect. Use after calls to functions like `exit()` that never return.

- `.trap` - Emits a hardware trap instruction (`UD2` on x86_64). Observable and guaranteed to halt execution. Distinct from `.unreachable`.
    - `#[breakpoint]` - emits a software breakpoint (`INT3`) instead; useful for debugger integration

- `.br(T0:@dest, T1:{...})` - Unconditional branch to `dest`. `T1:{...}` is the anonymous struct of arguments passed to the destination block. If the block takes no arguments, use `{}:{}`. ``{}:{}`` can be used to pass no arguments

    If any argument of the label is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.br(i1:%condition, T0:@true_dest, T1:{...}, T2:@false_dest, T3:{...})` - Conditional branch. Branches to `true_dest` if `condition` is true, else to `false_dest`. `T1:{...}` and `T3:{...}` are arguments for each destination. ``{}:{}`` can be used to pass no arguments
    - `#[freq(i32:N, i32:M)]` - hints at relative branching frequencies; used by the optimizer to lay out hot/cold paths. Mutually exclusive with `#[unpredictable]`.
    - `#[unpredictable]` - hints that the branch is unpredictable. Mutually exclusive with `#[freq]`.
    
    If any argument of the label is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

    TODO: In future have loop and vectorization hint attributes

- `.switch(T:%condition, T0:@default_dest, T1:{...}, T:%case1_value, T2:@case1_dest, T3:{...}, ...)` - Branches to the destination matching `condition`. Falls through to `default_dest` if no case matches. Condition must be integer; case values must be the same type as the condition. ``{}:{}`` can be used to pass no arguments
    - `#[freq(i32:N, i32:M, ...)]` - one frequency per destination in order (default first). Mutually exclusive with `#[unpredictable]`.
    - `#[unpredictable]` - hints that the branch is unpredictable. Mutually exclusive with `#[freq]`.

    If any argument of the label is float/vec of float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.indirectbr(ptr:%dest_ptr, label:@label1, label:@label2, ...)` - Branches to the address stored in `dest_ptr`. The address must point to one of the listed labels; otherwise UB. Labels listed here cannot take arguments. ``{}:{}`` can be used to pass no arguments
    - `#[freq(i32:N, i32:M, ...)]` - one frequency per label in order. Mutually exclusive with `#[unpredictable]`.
    - `#[unpredictable]` - hints that the branch is unpredictable. Mutually exclusive with `#[freq]`.

---

## Call Instruction

- `let T:%output_var = .call(T:%func, T1:%arg1, T2:%arg2...)` - Calls a function. T must be a function type (not `ptr`) containing the full signature. To call via a function pointer stored as `ptr`, cast it to the appropriate function type first.

    **Tail call attributes** (at most one):
    - `#[tail]` - tail call hint
    - `#[musttail]` - mandatory tail call; error if not possible
    - `#[notail]` - explicitly prohibits tail call optimization

    **Call-site attributes:**
    - `#[cold]` - marks this call site as cold even if the function itself is not
    - `#[hot]` - marks this call site as hot even if the function itself is not
    - `#[noreturn]` - marks this call site as non-returning even if the function definition does not say so; `.call` with no output variable is then permitted even for non-void functions
    - `#[nosideeffect]` - asserts this call has no observable side effects; the optimizer may remove the call if its return value is unused; overrides the function definition for this call site
    - `#[pure]` - asserts this call has no observable side effects and its return value depends only on its arguments; the optimizer may remove the call if its return value is unused or if the same call with the same arguments has already been made; overrides the function definition for this call site
    - `#[cc(str:calling_convention)]` - calling convention; one of `ccc`, `fastcc`, `coldcc`, `tailcc`; default is `ccc`
    - `#[return_extension(str:extension_type)]` - how the return value is extended; one of `"zero"`, `"sign"`, `"no"`

    **Float return value/argument value:** 
    - If the function returns or takes in float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

    **Per-argument attributes** (override function definition for this call site; useful for function pointers where no definition is available):
    - `#[noalias(i64:idx...)]`, `#[readonly(i64:idx...)]`, `#[nonnull(i64:idx...)]`, `#[align(i64:N, i64:idx...)]`, `#[dereferenceable(i64:N, i64:idx...)]`, `#[nopoison(i64:idx...)]`, `#[readnone(i64:idx...)]`, `#[writeonly(i64:idx...)]`, `#[writable(i64:idx...)]`, `#[returned(i64:idx...)]`, `#[nocapture(i64:idx...)]`
    - `#[byval(type:T0, i64:arg_index0, type:T1, i64:arg_index1, ...)]`, `#[byref(type:T0, i64:arg_index0, type:T1, i64:arg_index1, ...)]`, `#[inalloca(type:T0, i64:arg_index0, type:T1, i64:arg_index1, ...)]`, `#[preallocated(type:T0, i64:arg_index0, type:T1, i64:arg_index1, ...)]`, `#[sret(type:T0, i64:arg_index0, type:T1, i64:arg_index1, ...)]`
    - `#[zeroext(i64:idx...)]`, `#[signext(i64:idx...)]`

    **Return value attributes** (applied to the output variable):

    let T:%output_var #[noalias] = .call(...)

    Valid return-value attributes: `#[noalias]`, `#[nonnull]`, `#[dereferenceable(i64:N)]`, `#[nopoison]`, `#[align(i64:N)]`, `#[nnan]`, `#[ninf]`

- `.call(T:%func, T1:%arg1, T2:%arg2...)` - Same as above for void-returning functions.

---

## SIMD Instructions

- `let <T,M>:%output_var = .shufflevector(<T,N2>:%input1, <T,N3>:%input2, <i16,M>:%mask)` - Shuffles elements of two vectors according to a mask(Run time or compile time).

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <i1,N>:%output_var = .ternlog(<i1,N>:%a, <i1,N>:%b, <i1,N>:%c, i8:imm)` - Trinary logic operation on the bitwise representation of `a`, `b`, and `c`. For each bit position, the result is determined by the corresponding bit in `imm` (0-255). For example, if `imm` is 0b11110000, the result bit will be `a` for input 000, `b` for 001, `c` for 010, `a&b` for 011, `a&c` for 100, `b&c` for 101, `a|b|c` for 110, and `0` for 111. No attributes.

- `let T0:%output_var = .reduce_add(<T0,N>:%input_vector [, <i1,N>:%mask])`  
  Sums all elements of the vector where the mask is true (or all elements if no mask); result is scalar.

    If `T0` is integer:
    - `#[nsw]` – poison on signed overflow
    - `#[nuw]` – poison on unsigned overflow
    - `#[saturating]` – clamp instead of wrap; pair with `#[unsigned]` for unsigned saturation

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T0:%output_var = .reduce_mul(<T0,N>:%input_vector [, <i1,N>:%mask])`  
  Multiplies all elements of the vector where the mask is true (or all elements if no mask); result is scalar.

    If `T0` is integer:
    - `#[nsw]` – poison on signed overflow
    - `#[nuw]` – poison on unsigned overflow
    - `#[saturating]` – clamp instead of wrap; pair with `#[unsigned]` for unsigned saturation

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T0:%out = .reduce_avg(<T0,N>:%vec [, <i1,N>:%mask])`  
  Returns the arithmetic mean of all lanes where the mask is true (or all lanes if no mask). Result is scalar. `T0` can be integer or float/bfloat. Same attribute rules as `.avg`.

- `let T0:%output_var = .reduce_and(<T0,N>:%input_vector [, <i1,N>:%mask])`  
  Bitwise AND of all elements where the mask is true (or all elements if no mask); result is scalar. T0 must be integer. No attributes.

- `let T0:%output_var = .reduce_or(<T0,N>:%input_vector [, <i1,N>:%mask])`  
  Bitwise OR of all elements where the mask is true (or all elements if no mask); result is scalar. T0 must be integer.
    - `#[disjoint]` – asserts no bit is set in more than one element; poison if violated

- `let T0:%output_var = .reduce_xor(<T0,N>:%input_vector [, <i1,N>:%mask])`  
  Bitwise XOR of all elements where the mask is true (or all elements if no mask); result is scalar. T0 must be integer. No attributes.

- `let T0:%output_var = .reduce_xnor(<T0,N>:%input_vector [, <i1,N>:%mask])`  
  Bitwise XNOR of all elements where the mask is true (or all elements if no mask); result is scalar. T0 must be integer. No attributes.

- `let T0:%output_var = .reduce_min(<T0,N>:%input_vector [, <i1,N>:%mask])`  
  Minimum element among the lanes where the mask is true (or all lanes if no mask); result is scalar. T0 can be integer or float.

    If `T0` is integer:
    - `#[unsigned]` – unsigned minimum; default is signed

    If `T0` is float/bfloat:
    - `#[unordered]` – NaN-ignoring min (IEEE "minNum"); default propagates NaN
    - `#[ieee754_2019]` – correct signed-zero ordering across the full reduction; when combined with `#[unordered]`, gets 754-2019 `minimumNumber` semantics. Combining with `#[nsz]` is a compile error. Only valid when T0 is float or bfloat.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T0:%output_var = .reduce_max(<T0,N>:%input_vector [, <i1,N>:%mask])`  
  Maximum element among the lanes where the mask is true (or all lanes if no mask); result is scalar. T0 can be integer or float.

    If `T0` is integer:
    - `#[unsigned]` – unsigned maximum; default is signed

    If `T0` is float/bfloat:
    - `#[unordered]` – NaN-ignoring max (IEEE "maxNum"); default propagates NaN
    - `#[ieee754_2019]` – correct signed-zero ordering across the full reduction; when combined with `#[unordered]`, gets 754-2019 `maximumNumber` semantics. Combining with `#[nsz]` is a compile error. Only valid when T0 is float or bfloat.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

Note: `.reduce_sub`, `.reduce_nand`, `.reduce_nor`, `.reduce_div`, `.reduce_rem` are intentionally absent - these operations are neither associative nor commutative (or both), so a well-defined reduction order cannot be assumed.

- `let <T,N>:%output_var = .splat(T:%input_scalar)` - Broadcasts a scalar into every lane of a vector. T can be integer, float, or ptr.

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T,N>:%output_var = .step_vector(T:%start, T:%step)` - Creates a vector `[start, start+step, start+2*step, ...]`. T can be integer or float. 

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T,N>:%out = .insert_subvector(<T,N>:%vec, <T,M>:%sub, i64:%index)` - Inserts a shorter vector into a lane-aligned position within a longer vector, returning the updated longer vector. The other lanes are unchanged. 

    - `<T,N>:%vec` - the destination vector; T can be any integer, float, or bfloat; N is the total lane count
    - `<T,M>:%sub` - the subvector to insert; same element type T; M < N; M must divide N
    - `i64:%index` - the starting lane index in `vec` where insertion begins; must be a compile-time/run-time integer; must be a multiple of M (i.e. aligned to subvector boundaries); must satisfy `index + M <= N`

    Output type: `<T,N>` - same type as `vec`

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T,M>:%out = .extract_subvector(<T,N>:%vec, i64:%index)` - Extracts a contiguous slice of lanes from a vector into a shorter vector. 

    - `<T,N>:%vec` - the source vector; T can be any integer, float, or bfloat
    - `i64:%index` - the starting lane index; must be a compile-time/run-time integer; must be a multiple of M; must satisfy `index + M <= N`

    Output type: `<T,M>` - the element type is the same T; M is determined by the declared output type; M < N; M must divide N

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <i1,N>:%mask = .active_lane_mask(T:%base, T:%count)` - Generates a boolean vector mask where lane `i` is true if and only if `base + i < count`. Used to safely handle loop tail iterations in vectorized loops without out-of-bounds memory access - the mask is passed directly to `.masked_load` / `.masked_store`. 

    - `T:%base` - the starting index for this iteration; T must be an integer type (`i32` or `i64`; `i64` recommended to avoid truncation issues on large arrays)
    - `T:%count` - the total element count (exclusive upper bound); must be the same type as `base`

    Output type: `<i1,N>` - N is determined by the declared output type; reflects the target vector width.

    Attributes:
    - `#[unsigned]` - comparison `base + i < count` is unsigned; this is almost always what you want since indices are non-negative; default is signed

### Horizontal SIMD Instructions

- `let <T0,N>:%out = .hadd(<T0,N>:%a, <T0,N>:%b)` - Pairwise-adds adjacent lanes, consuming two `N`-lane input vectors and producing one `N`-lane output vector. The lower `N/2` output lanes are pairwise sums from `a`; the upper `N/2` output lanes are pairwise sums from `b`. Mirrors `HADDPS`/`PHADDW`/`PHADDD` semantics. `N` must be even. `T0` can be integer or float/bfloat.

    **If `T0` is integer:**
    - `#[unsigned]` - treat lane values as unsigned for overflow semantics
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow; only valid with `#[unsigned]`
    - `#[saturating]` - clamp instead of wrap; pair with `#[unsigned]` for unsigned saturation

    **If `T0` is float/bfloat:** `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T0,N>:%out = .hsub(<T0,N>:%a, <T0,N>:%b)` - Pairwise-subtracts adjacent lanes. Lane `2i` minus lane `2i+1` for each pair. Lower `N/2` from `a`, upper `N/2` from `b`. Mirrors `HSUBPS`/`PHSUBW`/`PHSUBD`. Same type and attribute rules as `.hadd`.

- `let <T0,N>:%out = .havg(<T0,N>:%a, <T0,N>:%b)` - Horizontal (pairwise) average. Lower `N/2` output lanes are pairwise averages from `a`; upper `N/2` are pairwise averages from `b`. `N` must be even. Same attribute rules as `.avg`.

### Dot Product Instruction

- `let T2:%out = .dot(<T1,N>:%a, <T1,N>:%b)` - Computes the dot product of `a` and `b`: sum of `a[i] * b[i]` over all lanes `i`, returning a scalar result in `T2`. When an optional third argument `%acc` is provided (`let T2:%out = .dot(<T1,N>:%a, <T1,N>:%b, T2:%acc)`), it is added to the result (`dot(a, b) + acc`), mapping directly to VNNI-style instructions and fused floating-point MACs. Output is always scalar.

    **If `T1` is integer:** The per-lane multiply is widening (products computed at `2xbitwidth(T1)` internally before accumulation). `T2` must be an integer type with `bitwidth(T2) >= 2 * bitwidth(T1)`. When `%acc` is provided it must be of type `T2`.
    - `#[unsigned]` - treat lane values as unsigned; default is signed
    - `#[nsw]` - poison if the accumulated sum overflows `T2`
    - `#[nuw]` - poison on unsigned overflow; only valid with `#[unsigned]`
    - `#[saturating]` - clamp the accumulator to the `T2` range instead of wrapping

    **If `T1` is float/bfloat:** `T2` must be float/bfloat with `bitwidth(T2) >= bitwidth(T1)`. When `%acc` is provided it must be of type `T2`. Float attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

### Absolute Difference Instructions

- `let T:%out = .absdiff(T:%a, T:%b)` - Returns `|a - b|`. `T` must be of the form `T0` or `<T0,M>` where `T0` is integer, float, or bfloat. For vectors, the operation is lanewise. Equivalent to `abs(a - b)` but expressed as a single instruction so the backend can emit `VABSSUBPS`, `VPABSB`/`VPABSW`/`VPABSD` patterns directly.

    **If `T0` is integer:**
    - `#[unsigned]` - treat values as unsigned (result is always non-negative; equivalent to `max(a,b) - min(a,b)` unsigned); default is signed
    - `#[nsw]` - poison if the subtraction overflows before taking absolute value

    **If `T0` is float/bfloat:** `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T2:%out = .sad(<T1,N>:%a, <T1,N>:%b)` - Sum of absolute differences: returns the sum of `|a[i] - b[i]|` over all lanes, scalar result in `T2`. Default is signed; use `#[unsigned]` for unsigned (natural for pixel data; matches `PSADBW` semantics).

    **If `T1` is integer:** Lane-wise differences are computed without overflow (widened to `2xbitwidth(T1)` internally before summing). `T2` must be an integer type with sufficient width for the full sum.
    - `#[unsigned]` - treat lane values as unsigned before differencing
    - `#[nsw]` / `#[nuw]` - poison on signed/unsigned overflow of the accumulated sum

    **If `T1` is float/bfloat:** Each `|a[i] - b[i]|` is computed as a float absolute difference and then accumulated into `T2`. `T2` must be float/bfloat with `bitwidth(T2) >= bitwidth(T1)`. Float attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

### Pack / Unpack Instructions

The following are defined only on integer

- `let <T2,N2>:%out = .pack_sat(<T1,N>:%a, <T1,N>:%b)` - Narrows both input vectors and concatenates them into one output vector. `bitwidth(T2) < bitwidth(T1)`; `N2 = 2*N`. Each element is clamped to the *signed* range of `T2` before truncation, even if the inputs are unsigned. Mirrors `PACKSSWB`, `PACKSSDW`.
    - `#[unsigned]` - clamp to the *unsigned* range of `T2` instead (e.g., `[0, 255]` for `i8`); mirrors `PACKUSWB`, `PACKUSDW`

- `let <T2,N2>:%out = .unpack_lo(<T1,N>:%a, <T1,N>:%b)` - Interleaves the *lower half* lanes of `a` and `b` into a single output vector. `N2 = N`; each output element is widened from `T1` to `T2` (`bitwidth(T2) = 2 * bitwidth(T1)`). Output order: `a[0], b[0], a[1], b[1], ..., a[N/2-1], b[N/2-1]`. Mirrors `PUNPCKLBW` / `PUNPCKLWD` / `PUNPCKLDQ`.
    - `#[unsigned]` - zero-extend lanes; default is sign-extend

- `let <T2,N2>:%out = .unpack_hi(<T1,N>:%a, <T1,N>:%b)` - Same as `.unpack_lo` but takes the *upper half* lanes. Output order: `a[N/2], b[N/2], ..., a[N-1], b[N-1]`. Mirrors `PUNPCKHBW` / `PUNPCKHWD` / `PUNPCKHDQ`.
    - `#[unsigned]` - zero-extend lanes; default is sign-extend

### Vector Layout Instructions

- `let <T,N>:%out = .compress(<T,N>:%src, <i1,N>:%mask)` - Packs active lanes (where `mask` is true) contiguously into the low lanes of the output. Inactive output lanes are zeroed unless `#[undef_inactive]` is set. Mirrors `VPCOMPRESSPS`/`VPCOMPRESSQ`/`VPCOMPRESSB`. `T` can be any integer, float, or bfloat.
    - `#[undef_inactive]` - inactive output lanes are undefined (allows the backend to skip zeroing)

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T,N>:%out = .expand(<T,N>:%src, <i1,N>:%mask, <T,N>:%passthru)` - Inverse of `.compress`. Reads elements from the consecutive low lanes of `src` and scatters them into the active (mask=true) lanes of the output. Inactive lanes take their value from `passthru`. Mirrors `VPEXPANDPS`/`VPEXPANDQ`/`VPEXPANDB`.
    - `#[zeropassthru]` - inactive lanes are zeroed; avoids materialising a zero `passthru` vector

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T,N>:%out = .broadcast_load(ptr:%ptr)` - Loads a single scalar of type `T` from memory and broadcasts it to every lane. A single instruction on x86 (`VBROADCASTSS`, `VBROADCASTSD`, etc.); the backend guarantees the fusion that a `.load` + `.splat` pair might not. `T` must be a scalar integer, float, or bfloat (not a vector).
    - `#[align(i8:N)]` - alignment of `ptr`; must be a power of 2; default is natural alignment of `T`
    - `#[volatile]` - volatile load
    - `#[nonnull]` - asserts `ptr` is not null
    - `#[nontemporal]` - non-temporal (cache-bypassing) load

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T,N2>:%out = .interleave2(<T,N>:%a, <T,N>:%b)` - Interleaves channels into a single packed vector. `N2 = 2*N`. Output element at position `i*2 + j` equals input `vj[i]` (channel `j`, element `i`). `T` can be any integer, float, or bfloat. 

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T,N3>:%out = .interleave3(<T,N>:%a, <T,N>:%b, <T,N>:%c)` - Interleave three channels. `N3 = 3*N`. Same rules.
- `let <T,N4>:%out = .interleave4(<T,N>:%a, <T,N>:%b, <T,N>:%c, <T,N>:%d)` - Interleave four channels. `N4 = 4*N`. Same rules.

- `let <T,N>:%out = .deinterleave2(<T,N2>:%v, i8:channel)` - Extracts one channel from an interleaved vector. `channel` must be a compile-time/run-time in `[0, 1]`. Extracts elements at positions `channel, channel+2, channel+4, ...`. Output length `N = N2/2`.

    If T is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.
    
- `let <T,N>:%out = .deinterleave3(<T,N3>:%v, i8:channel)` - Same for 3-channel interleaving, `channel` in `[0, 2]`. Output length `N = N3/3`. Allows fast math attribute for float/bfloat T.
- `let <T,N>:%out = .deinterleave4(<T,N4>:%v, i8:channel)` - Same for 4-channel interleaving, `channel` in `[0, 3]`. Output length `N = N4/4`. Allows fast math attribute for float/bfloat T

- `let <T0,N>:%out = .addsub(<T0,N>:%a, <T0,N>:%b)` - Alternates subtraction and addition on adjacent lanes: even-indexed lanes compute `a[i] - b[i]`; odd-indexed lanes compute `a[i] + b[i]`. `N` must be even. Mirrors `ADDSUBPS`/`ADDSUBPD`. Primary use case: complex number multiplication. `T0` can be integer or float/bfloat.

    **If `T0` is integer:**
    - `#[nsw]` - poison on signed overflow in any lane
    - `#[nuw]` - poison on unsigned overflow; only valid with `#[unsigned]`
    - `#[unsigned]` - treat lanes as unsigned
    - `#[saturating]` - clamp instead of wrap

    **If `T0` is float/bfloat:** `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

### Lane Mask Conversion Instructions

- `let iM:%out = .lane_mask_to_int(<i1,N>:%mask)` - Packs the N single-bit lanes of `mask` into the low N bits of a scalar integer of type `iM`. Lane `i` maps to bit `i` of the result; the remaining `M - N` high bits are zeroed. Mirrors `VMOVMSKPS`/`VPMOVMSKB`/`KMOVD` semantics. `M` must satisfy `M >= N`. No attributes.

- `let <i1,N>:%out = .int_to_lane_mask(iM:%bits)` - Inverse of `.lane_mask_to_int`. Unpacks the low N bits of `bits` into an N-lane `i1` vector. Bit `i` of `bits` becomes lane `i` of the output. High bits beyond N are ignored. Mirrors `KMOVD`/`VPMOVM2B` semantics. `M` must satisfy `M >= N`. No attributes.

### Widening Reductions

- `let T2:%out = .reduce_add_wide(<T1,N>:%v [, <i1,N>:%mask])` - Sums all lanes where the mask is true (or all lanes if no mask), accumulating in `T2`.  
    `T1` must be integer/float/bfloat; `T2` must be integer with `bitwidth(T2) >= bitwidth(T1)`.
    - `#[unsigned]` – treat lanes as unsigned; default is signed
    - `#[saturating]` – clamp accumulator to `T2` range instead of wrapping; pair with `#[unsigned]` for unsigned saturation

    If T1 is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T2:%out = .reduce_mul_wide(<T1,N>:%v [, <i1,N>:%mask])` - Multiplies all lanes where the mask is true (or all lanes if no mask), accumulating in `T2`.  
    `T1` must be integer/float/bfloat; `T2` must be integer with `bitwidth(T2) >= bitwidth(T1)`.
    - `#[unsigned]` – treat lanes as unsigned; default is signed
    - `#[saturating]` – clamp accumulator to `T2` range instead of wrapping; pair with `#[unsigned]` for unsigned saturation

    If T1 is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T2:%out = .reduce_avg_wide(<T1,N>:%v [, <i1,N>:%mask])` - Computes the arithmetic mean of all lanes where the mask is true (or all lanes if no mask) with intermediate accumulation in `T2`.  
    `T1` must be integer/float/bfloat; `T2` must be integer with `bitwidth(T2) >= bitwidth(T1)`.
    - `#[unsigned]` – treat lanes as unsigned; default is signed
    - `#[saturating]` – clamp accumulator to `T2` range instead of wrapping; pair with `#[unsigned]` for unsigned saturation
    
    If T1 is float:
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

---

## Other Instructions

- `let T0:%output_var = .select(T1:%condition, T0:%true_value, T0:%false_value)` - Selects between two values. If `T1` is `i1`: returns `true_value` if condition is true, else `false_value`. T0 can be any type. If `T1` is `<i1,M>`: selects element-wise; T0 must be a vector of size M.

    If T0 is float/bfloat/vector of float: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .freeze(T:%input_var)` - Freezes a poison or otherwise indeterminate value. The result is an arbitrary but fixed value of type T; the compiler may not make assumptions about which value. Prevents optimizations that rely on poison semantics from propagating through this point. T can be any type. 

    If T is float/bfloat/vector of float: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.va_start(ptr:%input_var)` - Initializes a variable-argument list. `input_var` must point to an allocated `{i32,i32,ptr,ptr}` struct (the `va_list`). Separated from allocation so the caller can allocate and optionally inspect the struct before initialization.

- `.va_end(ptr:%input_var)` - Cleans up a variable-argument list. `input_var` must be the same `va_list` pointer that was passed to `.va_start`.

- `.va_copy(ptr:%dest, ptr:%src)` - Copies a variable-argument list from `src` to `dest`. Both must be `va_list` pointers.

- `let T:%output_var = .va_arg(ptr:%input_var)` - Retrieves the next variadic argument of type T from the `va_list` pointed to by `input_var`

    If T is float/bfloat/vector of float: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .ptrmask(T:%input_var, T1:%mask)` - Masks a pointer with an integer mask. T must be `ptr` or `<ptr,M>`. T1 must be an integer or vector of integer. If T1 is a vector, T must be a vector of the same size. No attributes.

- `let type:%type_name = .assign_type(type:<type_definition>)` - Creates a type alias. Not a real instruction; ignored by MIR. Present only to simplify the parser.

- `.pause` - Emits the x86 `PAUSE` instruction, which is a hint to the processor that the current thread is in a spin-wait loop. On out-of-order CPUs this prevents the speculative execution pipeline from being flooded with iterations of a tight spin loop, reducing power consumption and improving performance when the lock is released (the pipeline does not need to be flushed). On hyperthreaded cores it also yields the execution resources to the sibling thread. Has no observable effect on program semantics; the CPU may treat it as a no-op on cores that do not support it. No inputs. No output. No attributes.

### Optimizer Hint Instructions

#### Binding Assumptions (May cause UB if violated)

For the following if T is float/bfloat/vector of float: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.assume(T:%var, T:compile_time_value)` - Tells the optimizer that `%var` holds `compile_time_value` at this program point. The compiler may propagate this as a known value. Undefined behavior if the assumption is false. `T` can be any type as long as represented as compile time value. `compile_time_value` must be a literal.
    - `#[noundef]` - additionally asserts that `%var` is not poison or undef

- `.assume(T:%var, T:v0, T:v1, ...)` - Asserts that `%var` is one of the listed compile-time values. Undefined behavior if wrong. `T` can be any type as long as represented as compile time value. At least one value required.
    - `#[noundef]` - additionally asserts `%var` is not poison

- `.assume_range(T:%var, T:compile_time_lo, T:compile_time_hi)` - Asserts that `%var` lies in the closed interval `[lo, hi]`. Undefined behavior if wrong. `T` must be integer or float scalar; `lo` and `hi` must be compile-time literals.
    - `#[unsigned]` - interval interpreted as unsigned (integer only); default is signed
    - `#[noundef]` - additionally asserts the value is not poison

- `.assume_not(T:%var, T:compile_time_value)` - Tells the optimizer that `%var` does not hold `compile_time_value` at this program point. Undefined behavior if the assumption is false. `T` can be any type as long as represented as compile time value. `compile_time_value` must be a literal.
    - `#[noundef]` - additionally asserts that `%var` is not poison or undef

- `.assume_not(T:%var, T:v0, T:v1, ...)` - Asserts that `%var` is not any of the listed compile-time values. Undefined behavior if wrong. `T` can be any type as long as represented as compile time value. At least one value required.
    - `#[noundef]` - additionally asserts `%var` is not poison

- `.assume_not_range(T:%var, T:compile_time_lo, T:compile_time_hi)` - Asserts that `%var` does not lie in the closed interval `[lo, hi]`. Undefined behavior if wrong. `T` must be integer or float scalar; `lo` and `hi` must be compile-time literals.
    - `#[unsigned]` - interval interpreted as unsigned (integer only); default is signed
    - `#[noundef]` - additionally asserts the value is not poison

#### Non-Binding Expectation Hints(No UB if violated. Even if the prob is 100%, the optimizer may still generate code for other cases.)

For the following if T is float/bfloat/vector of float: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `.expect(T:%var, T:compile_time_value)` - Hints that `%var` most commonly holds `compile_time_value`. No UB if wrong. Analogous to `__builtin_expect`. `T` can be any type as long as represented as compile time value.
    - `#[probability(f32:P)]` - probability the value matches (0.0–1.0); default unspecified

- `.expect(T:%var, T:v0, T:v1, ...)` - Hints that `%var` is most likely one of the listed values. `T` can be any type as long as represented as compile time value. No UB if wrong.
    - `#[probability(f32:P)]` - probability the value is in the list

- `.expect_range(T:%var, T:compile_time_lo, T:compile_time_hi)` - Hints that `%var` most commonly falls in `[lo, hi]`. T is integer or float. No UB if wrong.
    - `#[unsigned]` - interval unsigned
    - `#[probability(f32:P)]` - probability the value is in range

There are no expect_not variants, since they are equivalent to the corresponding expect variant with the probability inverted (1 - P).

### Metadata and Machine Instructions

- `.nop(i8:size)` - Emits `size` bytes of NOP instructions. `size` must be a compile-time integer literal in `[1, 15]`. Has no effect on semantics.
    - `#[multi_byte]` - prefer a single multi-byte NOP encoding; default is implementation choice

- `.annotation(str:message)` - Emits `message` as a comment/annotation into the generated assembly. Optimizer-transparent. `message` must be a compile-time string literal. No output. No attributes.

- `.endbr64` - Emits the Intel CET `ENDBR64` instruction. Must be the first instruction of every valid indirect-branch target when CET is enabled. On non-CET hardware executes as NOP. No input, no output, no attributes.

### Pointer Provenance Instructions

- `let ptr:%out = .launder(ptr:%ptr)` - Returns a pointer with the same address as `ptr` but with fresh provenance, severing the alias relationship the optimizer may have established. The returned pointer and the input compare equal at runtime but the optimizer must treat them as potentially aliasing distinct objects. Corresponds to LLVM `llvm.launder.invariant.group`. No attributes.

- `let ptr:%out = .strip_invariant_group(ptr:%ptr)` - Strips the invariant-group annotation from a pointer, allowing the optimizer to see stores through the returned pointer as potentially observable by loads from the original pointer. Corresponds to LLVM `llvm.strip.invariant.group`. No attributes.

---

## Hardware-Specific Instructions

### Processor Identification

- `let {i32, i32, i32, i32}:%out = .cpuid(i32:%leaf, i32:%subleaf)` - Executes the x86 `CPUID` instruction with `EAX = leaf` and `ECX = subleaf`, returning `{eax, ebx, ecx, edx}`. `CPUID` is fully serializing (acts as a barrier). Both `%leaf` and `%subleaf` may be runtime values. No attributes.

### Timestamp Counter Instructions

- `let i64:%out = .rdtsc()` - Returns the current value of the processor's time-stamp counter. Corresponds to `RDTSC`. Not ordered with respect to surrounding instructions by default; pair with a serializing instruction (`lfence; rdtsc` idiom) for a fully serialized timestamp. No attributes. `#[unsigned]` permitted but has no effect.

- `let {i64, i32}:%out = .rdtscp()` - Returns `{timestamp: i64, cpuid_aux: i32}`. `cpuid_aux` is the value of `IA32_TSC_AUX` MSR (typically a core identifier). Corresponds to `RDTSCP`. Partially serializing: waits for prior instructions to execute before reading the counter, but does not prevent subsequent instructions from starting. No attributes.

### Hardware Random Number Instructions

- `let {T, i1}:%out = .rdrand()` - Returns `{value: T, success: i1}`. `value` is a hardware-generated random number from the CSPRNG. `success` indicates whether a valid value was produced; if false, retry. `T` must be `i16`, `i32`, or `i64`. No attributes.

- `let {T, i1}:%out = .rdseed()` - Returns `{value: T, success: i1}` from the true hardware entropy source (lower throughput). `T` must be `i16`, `i32`, or `i64`. Retry semantics same as `.rdrand`. No attributes.
### Floating-Point Environment

These instructions manage the processor's floating-point control and status state. The intrinsics are overloaded on the env token type `T`: `T=i32` selects the SSE `MXCSR` path, `T=i16` selects the x87 `FCW`/`FSW` path. Where a `%env` parameter is present, the type annotation is mandatory
and serves as the overload discriminator - omitting or mismatching it is a compile error. For parameterless intrinsics (`.get_fpenv`, `.get_fpstatus`, `.clear_fpstatus`) where no token is passed in, `#[x87]` must be given explicitly since there is nothing to infer from. `f128` support is TBD.

---

- `let T:%out = .get_fpenv()` - Reads the floating-point control register. Returns an opaque env token of type `T`. No attributes.
    - `T=i32` (default) - reads `MXCSR`.
    - `T=i16` - requires `#[x87]`; reads `FCW` via `FNSTCW`.

- `.set_fpenv(T:%env)` - Writes `%env` to the floating-point control register. The type annotation on `%env` is mandatory and selects the overload. `%env` must be a value obtained from `.get_fpenv` (possibly modified via field accessors); writing arbitrary bit patterns with reserved bits set incorrectly is undefined behavior.
    - `T=i32` (default) - writes `MXCSR`.
    - `T=i16` - writes `FCW` via `FLDCW`. `#[x87]` is not required and is ignored if provided
      since `T` already selects the overload.
    - `#[volatile]` - prevents the optimizer from eliminating, reordering across other FP ops,
      or merging redundant calls. Applies to both overloads.

- `let i32:%out = .fpenv_get_field(T:%env, str:field)` - Extracts a named field from an opaque env token. The type annotation on `%env` is mandatory and selects the overload. `field` must be a compile-time string literal. No attributes.
    - `T=i32` (default) - SSE overload. Valid fields: `"round"` (0=nearest-even, 1=neg-inf,
      2=pos-inf, 3=zero), `"ftz"`, `"daz"`, `"except_mask"` (6-bit packed: bits 0–5 invalid,
      denorm, divzero, overflow, underflow, inexact; 1=masked), `"except_status"` (same 6-bit
      order for sticky flags).
    - `T=i16` - x87 overload. Valid fields: `"round"` (same 4-value encoding), `"precision"`
      (0=single, 2=double, 3=extended; 1=UB), `"except_mask"` (same 6-bit layout). Passing
      `"ftz"`, `"daz"`, or `"except_status"` is a compile error.

- `let T:%out = .fpenv_set_field(T:%env, str:field, i32:%value)` - Returns a copy of `%env` with the named field replaced by `%value`. Return type matches `T`. The type annotation on `%env` is mandatory and selects the overload. Same field restrictions as `.fpenv_get_field` apply. Does not modify processor state; pass the result to `.set_fpenv` to take effect. No attributes.
    - `T=i32` (default) - SSE overload. For `"except_status"`, setting a bit clears the
      corresponding sticky flag (write-1-to-clear semantics).
    - `T=i16` - x87 overload. `"except_status"`, `"ftz"`, and `"daz"` are compile errors; x87
      exception status lives in `FSW` and is not writable via `FCW`. Use `.clear_fpstatus#[x87]`
      instead.

- `let T:%out = .get_fpstatus()` - Reads sticky exception flags. No attributes.
    - `T=i32` (default) - reads `MXCSR` bits 0–5 as a 6-bit value in the same layout as
      `"except_status"`. Equivalent to `.fpenv_get_field(i32:.get_fpenv(), "except_status")`.
    - `T=i16` - requires `#[x87]`; reads `FSW` via `FNSTSW`. Note: `FSW` contains more than
      exception bits (condition codes, stack top pointer, etc.).

- `.clear_fpstatus()` - Clears all sticky exception flags. `#[volatile]` implicit. No inputs/outputs.
    - default - reads-modifies-writes `MXCSR`. Equivalent to
      `.set_fpenv(i32:.fpenv_set_field(i32:.get_fpenv(), "except_status", 0))`.
    - `#[x87]` - issues `FNCLEX` to clear `FSW`.
    
### Crypto Extensions

All instructions are pure functions of their operands; constant-foldable, CSE-able, reorderable freely. They operate on register values and do not fault.

#### AES (operate on `<i8,16>` blocks)
- `let <i8,16>:%out = .aesenc(<i8,16>:%state, <i8,16>:%roundkey)` - AES encrypt round. No attributes.
- `let <i8,16>:%out = .aesenclast(<i8,16>:%state, <i8,16>:%roundkey)` - AES encrypt last round (no MixColumns). No attributes.
- `let <i8,16>:%out = .aesdec(<i8,16>:%state, <i8,16>:%roundkey)` - AES decrypt round. No attributes.
- `let <i8,16>:%out = .aesdeclast(<i8,16>:%state, <i8,16>:%roundkey)` - AES decrypt last round (no InvMixColumns). No attributes.
- `let <i8,16>:%out = .aesimc(<i8,16>:%roundkey)` - AES inverse mix columns on a round key. No attributes.
- `let <i8,16>:%out = .aeskeygenassist(<i8,16>:%a, i8:rcon)` - AES key generation assist. `rcon` must be a compile-time/run-time integer literal. No attributes.

#### Carry-less Multiply
- `let i128:%out = .clmul(i64:%a, i64:%b)` - Carry-less (GF(2)) multiply, 64x64->128. No attributes.

#### SHA (operate on `<i32,4>` state)
- `let <i32,4>:%out = .sha1rnds4(<i32,4>:%abcd, <i32,4>:%msg, i8:func)` - SHA-1 four rounds. `func` compile-time/run-time literal 0–3(For runtime u get UB if func not in range). No attributes. 
- `let <i32,4>:%out = .sha1nexte(<i32,4>:%abcd, <i32,4>:%e)` - SHA-1 next E. No attributes.
- `let <i32,4>:%out = .sha1msg1(<i32,4>:%a, <i32,4>:%b)` - SHA-1 message schedule step 1. No attributes.
- `let <i32,4>:%out = .sha1msg2(<i32,4>:%a, <i32,4>:%b)` - SHA-1 message schedule step 2. No attributes.
- `let <i32,4>:%out = .sha256rnds2(<i32,4>:%abef, <i32,4>:%cdgh, <i32,4>:%wk)` - SHA-256 two rounds. No attributes.
- `let <i32,4>:%out = .sha256msg1(<i32,4>:%a, <i32,4>:%b)` - SHA-256 message schedule step 1. No attributes.
- `let <i32,4>:%out = .sha256msg2(<i32,4>:%a, <i32,4>:%b)` - SHA-256 message schedule step 2. No attributes.

#### CRC32
- `let T2:%out = .crc32(T2:%acc, T1:%data)` - CRC32C checksum update. `T2` accumulator/output must be `i32` or `i64`. `T1` must be `i8`, `i16`, or `i32` when `T2=i32`; or `i8` or `i64` when `T2=i64`. No attributes.

### System Call

- `let i64:%out = .syscall(i64:%nr, i64:%arg1, i64:%arg2, i64:%arg3, i64:%arg4, i64:%arg5, i64:%arg6)` - Issues the x86_64 Linux `SYSCALL` instruction. Arguments map to `rax, rdi, rsi, rdx, r10, r8, r9` in order. The argument list is variadic with 0–6 arguments; unused trailing args are omitted. All operands and the result must be `i64`. Treated as an arbitrary external call with unknown side effects; the optimizer must not reorder relative to memory ops, must not CSE identical calls, and must not eliminate if `%out` is unused, unless `#[nosideeffect]` is given.
    - `#[noreturn]` - for syscalls that never return on success; `.syscall` with no output variable is then permitted. You must use #[noreturn] if syscalls dont return. You cant just skip the ``let i64:%out`` part without it
    - `#[nosideeffect]` - opt-in assertion that this call has no side effects beyond its return value, allowing DCE/CSE.

### CET Shadow Stack

On hardware with CET-SS disabled, every instruction in this section executes as a documented no-op (except `.wrss`, which faults if user-mode WRSS is not enabled). All are opaque side-effecting w.r.t. the shadow stack.

- `let ptr:%out = .rdssp()` - Returns the current shadow stack pointer (`SSP`). On CET-SS-disabled hardware, result is implementation-defined (may be 0). No attributes.

- `.incssp(i64:%count)` - Pops `%count` 8-byte slots off the shadow stack (advances `SSP` by `8*count`). `%count` must be `>= 1`. No output. No attributes.

- `.saveprevssp()` - Pushes a previous-SSP token onto the current shadow stack. No output. No attributes.

- `.rstorssp(ptr:%token_addr)` - Loads `SSP` from the restore-token at `%token_addr` and validates it. No output. No attributes.

- `.setssbsy()` - Sets the "busy" bit on the current shadow-stack's supervisor token. No output. No attributes.

- `.wrss(T:%value, ptr:%addr)` - Writes `%value` directly into shadow-stack memory at `%addr`. `T` must be `i32` or `i64`. Requires user-mode WRSS enable; faults otherwise. `#[volatile]` implicitly. No additional attributes.

---