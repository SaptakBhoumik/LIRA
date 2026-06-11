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

- `let T:%output_var = .copysign(T:%input_var1, T:%input_var2)` - Copies the sign of `input_var2` onto `input_var1`. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat/integer. For integer, signed is assumed (unsigned integers have no sign bit).

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .min(T:%input_var1, T:%input_var2)` - Minimum of 2 values. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[unsigned]` - unsigned minimum; default is signed

    If `T0` is float/bfloat:
    - `#[unordered]` - if either input is NaN, return the other operand (IEEE "minNum" semantics). Default (no attribute) returns NaN if either input is NaN (ordered semantics).
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .max(T:%input_var1, T:%input_var2)` - Maximum of 2 values. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[unsigned]` - unsigned maximum; default is signed

    If `T0` is float/bfloat:
    - `#[unordered]` - if either input is NaN, return the other operand (IEEE "maxNum" semantics). Default (no attribute) returns NaN if either input is NaN (ordered semantics).
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

---

## Trinary Arithmetic Instructions

- `let T:%output_var = .fma(T:%input_var1, T:%input_var2, T:%input_var3)` - Fused multiply-add: `(input_var1 * input_var2) + input_var3` with a single rounding step. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .fms(T:%input_var1, T:%input_var2, T:%input_var3)` - Fused multiply-subtract: `(input_var1 * input_var2) - input_var3` with a single rounding step. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .fnma(T:%input_var1, T:%input_var2, T:%input_var3)` - Fused negative multiply-add: `-(input_var1 * input_var2) + input_var3` with a single rounding step. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .fnms(T:%input_var1, T:%input_var2, T:%input_var3)` - Fused negative multiply-subtract: `-(input_var1 * input_var2) - input_var3` with a single rounding step. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat.

    Attributes: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .clamp(T:%input_var, T:%min, T:%max)` - Clamps `input_var` to `[min, max]`. Returns `min` if below, `max` if above, otherwise the value itself. T must be of the form `T0` or `<T0,M>` where T0 is some float/bfloat/integer.

    If `T0` is integer:
    - `#[unsigned]` - unsigned clamp; default is signed

    If `T0` is float/bfloat:
    - `#[unordered]` - NaN-ignoring clamp (IEEE "minNum/maxNum" semantics). Default propagates NaN.
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .fshl(T:%input_var1, T:%input_var2, T:%shift)` - Funnel shift left. Conceptually concatenates `input_var1:input_var2`, shifts left by `shift mod bitwidth`, and returns the high T-sized bits. T must be of the form `T0` or `<T0,M>` where T0 is some integer. No attributes.

- `let T:%output_var = .fshr(T:%input_var1, T:%input_var2, T:%shift)` - Funnel shift right. Conceptually concatenates `input_var1:input_var2`, shifts right by `shift mod bitwidth`, and returns the low T-sized bits. T must be of the form `T0` or `<T0,M>` where T0 is some integer. No attributes.

---

## Overflow-Detecting Arithmetic Instructions

These return `{T, i1}` - the result paired with an overflow flag (1 if overflow occurred). T must be of the form `T0` or `<T0,M>` where T0 is some integer.

- `let {T,i1}:%output_var = .add_overflow(T:%input_var1, T:%input_var2)` - Addition with overflow detection.
    - `#[unsigned]` - detect unsigned overflow; default detects signed overflow

- `let {T,i1}:%output_var = .sub_overflow(T:%input_var1, T:%input_var2)` - Subtraction with overflow/underflow detection.
    - `#[unsigned]` - detect unsigned underflow; default detects signed overflow

- `let {T,i1}:%output_var = .mul_overflow(T:%input_var1, T:%input_var2)` - Multiplication with overflow detection.
    - `#[unsigned]` - detect unsigned overflow; default detects signed overflow

---

## Bitwise Instructions

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

---

## Conversion Instructions

- `let T2:%output_var = .trunc(T1:%input_var)` - Truncates from a wider to a narrower type. Base type of T1 and T2 must match in kind (integer→integer, float→float). Bitwidth of T1's base type must be strictly greater than T2's. Both must be vector or both non-vector.

    If base type is integer:
    - `#[nsw]` - poison if the truncated value does not sign-extend back to the original
    - `#[nuw]` - poison if the truncated value does not zero-extend back to the original

- `let T2:%output_var = .ext(T1:%input_var)` - Extends from a narrower to a wider type. Base type of T1 and T2 must match in kind. Bitwidth of T1's base type must be strictly less than T2's. Both must be vector or both non-vector.

    If base type is integer:
    - `#[unsigned]` - zero-extension (equivalent to LLVM `zext`); default is sign-extension
    - `#[nsb]` - only valid with `#[unsigned]`; asserts the source value's sign bit is 0, giving a tighter range (e.g. `i8` range becomes `[0,127]` instead of `[0,255]`)

- `let T2:%output_var = .float_to_int(T1:%input_var)` - Converts float/bfloat (or vector thereof) T1 to integer (or vector thereof) T2. Output type determines the target integer width and kind.

    - `#[unsigned]` - produce an unsigned integer; default is signed
    - `#[nsb]` - only valid with `#[unsigned]`; asserts the result's sign bit is 0

- `let T2:%output_var = .int_to_float(T1:%input_var)` - Converts integer (or vector thereof) T1 to float/bfloat (or vector thereof) T2. Output type determines the target float kind.

    - `#[unsigned]` - treat the source integer as unsigned; default is signed
    - `#[nsb]` - only valid with `#[unsigned]`; asserts the source integer's sign bit is 0

- `let T2:%output_var = .ptr_to_int(T1:%input_var)` - Converts pointer/vector-of-pointer T1 to `i64`/`<i64,M>` T2. Only `i64` is valid (64-bit systems only). Use `.trunc` after if a narrower integer is needed. No attributes.

- `let T2:%output_var = .int_to_ptr(T1:%input_var)` - Converts `i64`/`<i64,M>` T1 to pointer/vector-of-pointer T2. Only `i64` is valid (64-bit systems only). Use `.ext` before if the source is a narrower integer. No attributes.

- `let T2:%output_var = .bitcast(T1:%input_var)` - Reinterprets the bits of T1 as type T2. T1 and T2 must have the same bitwidth. Cannot bitcast between `i64` and `ptr`. No attributes.

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
    - `#[nuw]` - poison if input is negative (asserts value was already non-negative)

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

- `let T:%output_var = .bswap(T:%input_var)` - Reverses byte order. T must be of the form `T0` or `<T0,M>` where T0 is integer/float/bfloat. Bitwidth must be a multiple of 8. Float/bfloat is supported because endianness swaps on floats are common; without this you would need a bitcast. No attributes.

- `let T:%output_var = .bitreverse(T:%input_var)` - Reverses bit order. T must be of the form `T0` or `<T0,M>` where T0 is some integer. No attributes.

---

## Float Classification Instructions

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

    - `#[align(i8:N)]` - alignment of the global in bytes; must be a power of 2

- `let T:%local_var = .local(T:initial_value)` - Defines and initializes a local variable. Value can be anything. Present for parser simplicity; does little in MIR. T can be any type. No attributes.

- `let ptr:%local_var = .alloca(iN:%size)` - Allocates `size` bytes on the stack. Returns a pointer to the allocation.

    - `#[align(i8:N)]` - alignment of the allocation in bytes; must be a power of 2; default is 1

- `let T:%output_var = .load(ptr:%ptr)` - Loads a value of type T from memory.

    - `#[align(i8:N)]` - alignment of the pointer; must be a power of 2; required if atomic
    - `#[volatile]` - volatile load; not elided or reordered
    - `#[invariant.load]` - the loaded value will not change during program execution
    - `#[nontemporal]` - non-temporal (cache-bypassing) load
    - `#[nonnull]` - asserts the pointer is not null
    - `#[nopoison]` - asserts the loaded value is not poison
    - `#[nsb]` - asserts the loaded integer's sign bit is 0 (tighter range for optimizer)
    - `#[dereferenceable(i64:N)]` - asserts the pointer is dereferenceable for N bytes
    - `#[atomic(str:ordering)]` - atomic load; ordering must be one of: `acquire`, `monotonic`, `unordered`, `seq_cst`
    - `#[syncscope("singlethreaded")]` - only valid with `#[atomic]`; synchronizes only with atomic ops in the same thread; default is global

- `.store(T:%value, ptr:%ptr)` - Stores a value to memory.

    - `#[align(i8:N)]` - alignment of the pointer; must be a power of 2; required if atomic
    - `#[volatile]` - volatile store
    - `#[nontemporal]` - non-temporal (cache-bypassing) store
    - `#[nonnull]` - asserts the pointer is not null
    - `#[nopoison]` - asserts the value being stored is not poison
    - `#[dereferenceable(i64:N)]` - asserts the pointer is dereferenceable for N bytes
    - `#[atomic(str:ordering)]` - atomic store; ordering must be one of: `release`, `monotonic`, `unordered`, `seq_cst`
    - `#[syncscope("singlethreaded")]` - only valid with `#[atomic]`; default is global

- `.memcpy(ptr:%dest, ptr:%src, iN:%size)` - Copies `size` bytes from `src` to `dest`. Regions must not overlap; use `.memmove` if they may. The index `0` refers to `src` and `1` refers to `dest` in per-pointer attributes.

    - `#[volatile]` - volatile copy
    - `#[align(i8:N, iN:idx...)]` - alignment of the specified pointer(s); must be a power of 2; at least one index required
    - `#[nontemporal(iN:idx...)]` - non-temporal access for the specified pointer(s); at least one index required
    - `#[nonnull(iN:idx...)]` - asserts the specified pointer(s) are not null; at least one index required
    - `#[nopoison(iN:idx...)]` - asserts the memory at the specified pointer(s) contains no poison; at least one index required
    - `#[dereferenceable(i64:N, iN:idx...)]` - asserts the specified pointer(s) are dereferenceable for N bytes; at least one index required

- `.memmove(ptr:%dest, ptr:%src, iN:%size)` - Copies `size` bytes from `src` to `dest`. Correct even if regions overlap. Same attributes as `.memcpy` with the same per-pointer index convention.

- `.memset(ptr:%dest, i8:%value, iN:%size)` - Fills `size` bytes at `dest` with `value`.

    - `#[volatile]` - volatile set
    - `#[align(i8:N)]` - alignment of `dest`; must be a power of 2
    - `#[nontemporal]` - non-temporal stores
    - `#[nonnull]` - asserts `dest` is not null
    - `#[nopoison]` - asserts the region contains no poison
    - `#[dereferenceable(i64:N)]` - asserts `dest` is dereferenceable for N bytes

- `let i32:%output_var = .memcmp(ptr:%ptr1, ptr:%ptr2, iN:%size)` - Compares `size` bytes at `ptr1` and `ptr2`. Returns a negative, zero, or positive integer if the region at `ptr1` is respectively less than, equal to, or greater than the region at `ptr2`. The index `0` refers to `ptr1` and `1` refers to `ptr2` in per-pointer attributes.

    - `#[volatile]` - volatile compare
    - `#[align(i8:N, iN:idx...)]` - alignment of the specified pointer(s); at least one index required
    - `#[nontemporal(iN:idx...)]` - non-temporal access for the specified pointer(s); at least one index required
    - `#[nonnull(iN:idx...)]` - asserts the specified pointer(s) are not null; at least one index required
    - `#[nopoison(iN:idx...)]` - asserts the memory at the specified pointer(s) contains no poison; at least one index required
    - `#[dereferenceable(i64:N, iN:idx...)]` - asserts the specified pointer(s) are dereferenceable for N bytes; at least one index required

- `let ptr:%output_var = .getaddress(T:%var, iN:%offset)` - Returns `&var + offset`. Output must be a pointer. `var` must be a variable (not a literal). Offset is in bytes.

    - `#[unsigned]` - offset is unsigned; default is signed
    - `#[nsw]` - poison if the offset causes signed overflow
    - `#[nuw]` - poison if the offset causes unsigned overflow
    - `#[inbounds]` - asserts the result pointer is within the bounds of the underlying object

- `let ptr:%output_var = .ptroffset(ptr:%input_var, T:%offset)` - Returns `input_var + offset`. Output and input must be pointers. Offset can be any integer type. Offset is in bytes.

    - `#[unsigned]` - offset is unsigned; default is signed
    - `#[nsw]` - poison if the offset causes signed overflow
    - `#[nuw]` - poison if the offset causes unsigned overflow
    - `#[inbounds]` - asserts the result pointer is within the bounds of the underlying object

- `let ptr:%stack_ptr = .stacksave()` - Saves and returns the current stack pointer as an opaque pointer value. Used before a dynamic `.alloca` inside a loop to allow reclaiming the stack later. Do not dereference or manipulate the returned pointer; it is only valid as input to `.stackrestore`. No attributes.

- `.stackrestore(ptr:%stack_ptr)` - Restores the stack pointer to the value saved by `.stacksave`, effectively freeing any dynamic allocations made since the save. The input must be a value previously returned by `.stacksave`. No attributes.

- `let T3:%output_var = .extractelement(T1:%input, T2:%index)` - Extracts element at `index` from a vector/array/struct. `T1` is the aggregate, `T2` is integer index type `iN`, `T3` is the element type. For structs, index must be an integer literal. For arrays and vectors, index can be a literal or variable.

    - `#[inbounds]` - valid for array and vector only; asserts index is within bounds; not valid for struct (struct access is always in bounds)

- `let T1:%output_var = .insertelement(T1:%input, T2:%element, T3:%index)` - Returns a copy of the aggregate with the element at `index` replaced by `element`. Output type equals input aggregate type. `T3` is integer index type `iN`. For structs, index must be an integer literal. For arrays and vectors, index can be a literal or variable.

    - `#[inbounds]` - valid for array and vector only; not valid for struct

- `.fence(str:ordering)` - Memory fence. Ordering and syncscope must be constant expressions. Valid orderings: `acquire`, `release`, `acq_rel`, `seq_cst`. Has no input or output; acts purely as a barrier.

    - `#[syncscope("singlethreaded")]` - synchronizes only with atomic ops in the same thread; default is global

- `let {T,i1}:%output_var = .cmpxchg(ptr:%ptr, T:%expected, T:%desired, str:success_ordering, str:failure_ordering)` - Atomically compares `*ptr` with `expected`. If equal, stores `desired` and returns `{original, true}`; otherwise leaves memory unchanged and returns `{original, false}`. `success_ordering` must be one of: `monotonic`, `acquire`, `release`, `acq_rel`, `seq_cst`. `failure_ordering` must be one of: `monotonic`, `acquire`, `seq_cst` (not `release` or `acq_rel`).

    - `#[align(i8:N)]` - required; alignment of the operation; must be a power of 2
    - `#[volatile]` - volatile operation
    - `#[weak]` - weak CAS; permitted to spuriously fail even when `*ptr == expected`
    - `#[syncscope("singlethreaded")]` - synchronizes only with atomic ops in the same thread; default is global

---

## Binary Fetch Instructions

Read-modify-write instructions that read a value from memory, apply a binary operation with a given operand, write the result back, and return the original value. Can optionally be made atomic with `#[atomic]`.

**Attributes shared by all fetch instructions:**
- `#[align(i8:N)]` - alignment of the pointer; must be a power of 2
- `#[volatile]` - volatile operation
- `#[atomic(str:ordering)]` - makes the operation atomic; ordering must be one of: `monotonic`, `acquire`, `release`, `acq_rel`, `seq_cst`. If absent, the operation is not atomic.
- `#[syncscope("singlethreaded")]` - only valid with `#[atomic]`; synchronizes only within the same thread; default is global

---

- `let T:%old = .fetch_xchg(ptr:%ptr, T:%value)` - Replaces `*ptr` with `value`; returns the original. T can be integer or float. No additional attributes beyond the shared set.

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

- `let T:%old = .fetch_copysign(ptr:%ptr, T:%value)` - Copies the sign of `value` onto `*ptr`; returns the original. T must be of the form `T0` or `<T0,M>` where T0 is float/bfloat/integer (signed assumed for integer).

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_max(ptr:%ptr, T:%value)` - Replaces `*ptr` with `max(*ptr, value)`; returns the original. T can be integer or float.

    If T is integer:
    - `#[unsigned]` - unsigned max; default is signed

    If T is float/bfloat:
    - `#[unordered]` - if either operand is NaN, use the other (IEEE "maxNum"); default propagates NaN
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%old = .fetch_min(ptr:%ptr, T:%value)` - Replaces `*ptr` with `min(*ptr, value)`; returns the original. T can be integer or float.

    If T is integer:
    - `#[unsigned]` - unsigned min; default is signed

    If T is float/bfloat:
    - `#[unordered]` - if either operand is NaN, use the other (IEEE "minNum"); default propagates NaN
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

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

---

## Unary Fetch Instructions

Read-modify-write instructions that apply a unary operation to the value at a memory location and return the original value. Can optionally be made atomic with `#[atomic]`.

**Attributes shared by all unary fetch instructions:** same as Binary Fetch - `#[align(i8:N)]`, `#[volatile]`, `#[atomic(str:ordering)]`, `#[syncscope("singlethreaded")]`.

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

- `let T:%old = .fetch_bswap(ptr:%ptr)` - Reverses byte order of `*ptr`; returns the original. T must be integer or float/bfloat. Float/bfloat supported for endianness swaps (avoids needing a bitcast). Bitwidth must be a multiple of 8. No additional attributes.

- `let T:%old = .fetch_bitreverse(ptr:%ptr)` - Reverses bit order of `*ptr`; returns the original. T must be integer. No additional attributes.

---

## Terminator Instructions

A terminator must be the final instruction of every block. Falling through to the next block without an explicit branch is an error.

- `.ret` / `.ret(T:%return_value)` - Returns from the function. Use `.ret` with no value for void functions. For non-void functions, the return value must match the function's return type.
    - `#[noreturn]` - indicates the function never actually returns; `.ret` with no value is then permitted even for non-void functions

- `.unreachable` - Marks a point in the code that is statically known to never be reached. A hint to the compiler; has no guaranteed runtime effect. Use after calls to functions like `exit()` that never return.

- `.trap` - Emits a hardware trap instruction (`UD2` on x86_64). Observable and guaranteed to halt execution. Distinct from `.unreachable`.
    - `#[breakpoint]` - emits a software breakpoint (`INT3`) instead; useful for debugger integration

- `.br(T0:@dest, T1:{...})` - Unconditional branch to `dest`. `T1:{...}` is the anonymous struct of arguments passed to the destination block. If the block takes no arguments, use `T1:{}`.

- `.br(i1:%condition, T0:@true_dest, T1:{...}, T2:@false_dest, T3:{...})` - Conditional branch. Branches to `true_dest` if `condition` is true, else to `false_dest`. `T1:{...}` and `T3:{...}` are arguments for each destination.
    - `#[freq(i32:N, i32:M)]` - hints at relative branching frequencies; used by the optimizer to lay out hot/cold paths. Mutually exclusive with `#[unpredictable]`.
    - `#[unpredictable]` - hints that the branch is unpredictable. Mutually exclusive with `#[freq]`.

- `.switch(T:%condition, T0:@default_dest, T1:{...}, T:%case1_value, T2:@case1_dest, T3:{...}, ...)` - Branches to the destination matching `condition`. Falls through to `default_dest` if no case matches. Condition must be integer; case values must be the same type as the condition.
    - `#[freq(i32:N, i32:M, ...)]` - one frequency per destination in order (default first). Mutually exclusive with `#[unpredictable]`.
    - `#[unpredictable]` - hints that the branch is unpredictable. Mutually exclusive with `#[freq]`.

- `.indirectbr(ptr:%dest_ptr, label:@label1, label:@label2, ...)` - Branches to the address stored in `dest_ptr`. The address must point to one of the listed labels; otherwise UB. Labels listed here cannot take arguments.
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
    - `#[noreturn]` - marks this call site as non-returning even if the function definition does not say so; `.call` with no output variable is then permitted even for non-void functions
    - `#[nosideeffect]` - asserts this call has no observable side effects; the optimizer may remove the call if its return value is unused; overrides the function definition for this call site
    - `#[cc(str:calling_convention)]` - calling convention; one of `ccc`, `fastcc`, `coldcc`, `tailcc`; default is `ccc`
    - `#[return_extension(str:extension_type)]` - how the return value is extended; one of `"zero"`, `"sign"`, `"no"`

    **Float return value:**
    - If the function returns float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

    **Per-argument attributes** (override function definition for this call site; useful for function pointers where no definition is available):
    - `#[noalias(i64:idx...)]`, `#[readonly(i64:idx...)]`, `#[nonnull(i64:idx...)]`, `#[align(i64:N, i64:idx...)]`, `#[dereferenceable(i64:N, i64:idx...)]`, `#[nopoison(i64:idx...)]`, `#[readnone(i64:idx...)]`, `#[writeonly(i64:idx...)]`, `#[writable(i64:idx...)]`, `#[returned(i64:idx...)]`, `#[nocapture(i64:idx...)]`
    - `#[byval(type:T0, i64:idx...)]`, `#[byref(type:T0, i64:idx...)]`, `#[inalloca(type:T0, i64:idx...)]`, `#[preallocated(type:T0, i64:idx...)]`, `#[sret(type:T0, i64:idx...)]`
    - `#[zeroext(i64:idx...)]`, `#[signext(i64:idx...)]`

    **Return value attributes** (applied to the output variable):
    ```
    let T:%output_var #[noalias] = .call(...)
    ```
    Valid return-value attributes: `#[noalias]`, `#[nonnull]`, `#[dereferenceable(i64:N)]`, `#[nopoison]`, `#[align(i64:N)]`, `#[nnan]`, `#[ninf]`

- `.call(T:%func, T1:%arg1, T2:%arg2...)` - Same as above for void-returning functions.

---

## SIMD Instructions

- `let <T,M>:%output_var = .shufflevector(<T,N2>:%input1, <T,N3>:%input2, <i16,M>:%mask)` - Shuffles elements of two vectors according to a compile-time mask. No attributes.

- `let T0:%output_var = .reduce_add(<T0,N>:%input_vector)` - Sums all elements of the vector; result is scalar.

    If `T0` is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp instead of wrap; pair with `#[unsigned]` for unsigned saturation

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T0:%output_var = .reduce_mul(<T0,N>:%input_vector)` - Multiplies all elements of the vector; result is scalar.

    If `T0` is integer:
    - `#[nsw]` - poison on signed overflow
    - `#[nuw]` - poison on unsigned overflow
    - `#[saturating]` - clamp instead of wrap; pair with `#[unsigned]` for unsigned saturation

    If `T0` is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T0:%output_var = .reduce_and(<T0,N>:%input_vector)` - Bitwise AND of all elements; result is scalar. T0 must be integer. No attributes.

- `let T0:%output_var = .reduce_or(<T0,N>:%input_vector)` - Bitwise OR of all elements; result is scalar. T0 must be integer.
    - `#[disjoint]` - asserts no bit is set in more than one element; poison if violated

- `let T0:%output_var = .reduce_xor(<T0,N>:%input_vector)` - Bitwise XOR of all elements; result is scalar. T0 must be integer. No attributes.

- `let T0:%output_var = .reduce_xnor(<T0,N>:%input_vector)` - Bitwise XNOR of all elements; result is scalar. T0 must be integer. No attributes.

- `let T0:%output_var = .reduce_min(<T0,N>:%input_vector)` - Minimum element of the vector; result is scalar. T0 can be integer or float.

    If `T0` is integer:
    - `#[unsigned]` - unsigned minimum; default is signed

    If `T0` is float/bfloat:
    - `#[unordered]` - NaN-ignoring min (IEEE "minNum"); default propagates NaN
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T0:%output_var = .reduce_max(<T0,N>:%input_vector)` - Maximum element of the vector; result is scalar. T0 can be integer or float.

    If `T0` is integer:
    - `#[unsigned]` - unsigned maximum; default is signed

    If `T0` is float/bfloat:
    - `#[unordered]` - NaN-ignoring max (IEEE "maxNum"); default propagates NaN
    - `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

Note: `.reduce_sub`, `.reduce_nand`, `.reduce_nor`, `.reduce_div`, `.reduce_rem` are intentionally absent - these operations are neither associative nor commutative (or both), so a well-defined reduction order cannot be assumed.

- `let <T,N>:%output_var = .splat(T:%input_scalar)` - Broadcasts a scalar into every lane of a vector. T can be integer, float, or ptr.

    If T is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let <T,N>:%output_var = .step_vector(T:%start, T:%step)` - Creates a vector `[start, start+step, start+2*step, ...]`. T can be integer or float. No attributes.

---

## Other Instructions

- `let T0:%output_var = .select(T1:%condition, T0:%true_value, T0:%false_value)` - Selects between two values. If `T1` is `i1`: returns `true_value` if condition is true, else `false_value`. T0 can be any type. If `T1` is `<i1,M>`: selects element-wise; T0 must be a vector of size M.

    If T0 is float/bfloat: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

- `let T:%output_var = .freeze(T:%input_var)` - Freezes a poison or otherwise indeterminate value. The result is an arbitrary but fixed value of type T; the compiler may not make assumptions about which value. Prevents optimizations that rely on poison semantics from propagating through this point. T can be any type. No attributes.

- `.va_start(ptr:%input_var)` - Initializes a variable-argument list. `input_var` must point to an allocated `{i32,i32,ptr,ptr}` struct (the `va_list`). Separated from allocation so the caller can allocate and optionally inspect the struct before initialization.

- `.va_end(ptr:%input_var)` - Cleans up a variable-argument list. `input_var` must be the same `va_list` pointer that was passed to `.va_start`.

- `.va_copy(ptr:%dest, ptr:%src)` - Copies a variable-argument list from `src` to `dest`. Both must be `va_list` pointers.

- `let T:%output_var = .va_arg(ptr:%input_var)` - Retrieves the next variadic argument of type T from the `va_list` pointed to by `input_var`. No attributes.

- `let T:%output_var = .ptrmask(T:%input_var, T1:%mask)` - Masks a pointer with an integer mask. T must be `ptr` or `<ptr,M>`. T1 must be an integer or vector of integer. If T1 is a vector, T must be a vector of the same size. No attributes.

- `let type:%type_name = .assign_type(type:<type_definition>)` - Creates a type alias. Not a real instruction; ignored by MIR. Present only to simplify the parser.