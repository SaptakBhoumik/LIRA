## Binary Arithmetic instructions

- `` let T:%output_var = .add(T:%input_var1, T:%input_var2)`` :- Adds 2 numbers. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. It has the attribute ``#[saturating]`` to indicate that it is a saturating add which means that if the result overflows then it will be clamped to the maximum or minimum value of the type instead of wrapping around. So if you have #[saturating] then it is a saturating add and if you dont have #[saturating] then it is a normal add that can overflow and wrap around. If ``#[saturating]`` You might wanna specify the signedness of the integer type with the attribute ``#[unsigned]`` to indicate that it is an unsigned saturating add. By default it is a signed saturating add.

    If ``T0`` is integer then it can have 2 attribute. It can have attributes ``#[nsw]`` or ``#[nuw]` or both. Dont care if signed or unsigned, the result is same regardless

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. 

- `` let T:%output_var = .sub(T:%input_var1, T:%input_var2)`` :- Subtracts 2 numbers. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. It has the attribute ``#[saturating]`` to indicate that it is a saturating sub which means that if the result overflows then it will be clamped to the maximum or minimum value of the type instead of wrapping around. So if you have #[saturating] then it is a saturating sub and if you dont have #[saturating] then it is a normal sub that can overflow and wrap around. If ``#[saturating]`` You might wanna specify the signedness of the integer type with the attribute ``#[unsigned]`` to indicate that it is an unsigned saturating sub. By default it is a signed saturating sub.

    If ``T0`` is integer then it can have 2 attribute. It can have attributes ``#[nsw]`` or ``#[nuw]` or both. Dont care if signed or unsigned, the result is same regardless

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. 

- `` let T:%output_var = .mul(T:%input_var1, T:%input_var2)`` :- Multiplies 2 numbers. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. It has the attribute ``#[saturating]`` to indicate that it is a saturating mul which means that if the result overflows then it will be clamped to the maximum or minimum value of the type instead of wrapping around. So if you have #[saturating] then it is a saturating mul and if you dont have #[saturating] then it is a normal mul that can overflow and wrap around. If ``#[saturating]`` You might wanna specify the signedness of the integer type with the attribute ``#[unsigned]`` to indicate that it is an unsigned saturating mul. By default it is a signed saturating mul.

    If ``T0`` is integer then it can have 2 attribute. It can have attributes ``#[nsw]`` or ``#[nuw]` or both. Dont care if signed or unsigned, the result is same regardless

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. 

- `` let T:%output_var = .div(T:%input_var1, T:%input_var2)`` :- Division. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. 

    If ``T0`` is integer then it can have the attribute ``#[exact]``. It also has the attribute ``#[unsigned]`` to indicate that it is unsigned division. By default it is signed division. 

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- `` let T:%output_var = .rem(T:%input_var1, T:%input_var2)`` :- Remainder of division. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. 

    If ``T0`` is integer then it can have the attribute ``#[unsigned]`` to indicate that it is remainder of unsigned division. By default it is remainder of signed division.

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%output_var = .copysign(T:%input_var1, T:%input_var2)`` :-  Copies the sign of input_var2 to input_var1. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/intger. If integer we assume it is signed because invalid for unsigned integer. 

    If T0 is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%output_var = .min(T:%input_var1, T:%input_var2)`` :- Minimum of 2 values. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. 

    If T0 is integer then it can have the attribute ``#[unsigned]`` to indicate that it is unsigned minimum. By default it is signed minimum.

    If T0 is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. It also has the ``#[unordered]`` attribute and by default it is ordered min where if any of the input is NaN then the result is NaN. If you have #[unordered] then it is unordered min where if any of the input is NaN then the result is the other input. So if you do min(5.0, NaN) then the result is 5.0 if you have #[unordered] and the result is NaN if you dont have #[unordered].

- ``let T:%output_var = .max(T:%input_var1, T:%input_var2)`` :- Maximum of 2 values. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. 

    If T0 is integer then it can have the attribute ``#[unsigned]`` to indicate that it is unsigned maximum. By default it is signed maximum.

    If T0 is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. It also has the attribute #[unordered] and by default it is ordered max where if any of the input is NaN then the result is NaN. If you have #[unordered] then it is unordered max where if any of the input is NaN then the result is the other input. So if you do max(5.0, NaN) then the result is 5.0 if you have #[unordered] and the result is NaN if you dont have #[unordered].

## Trinary Arithmetic instructions

- `` let T:%output_var = .fma(T:%input_var1, T:%input_var2, T:%input_var3)`` :- Fused multiply add. It computes (input_var1 * input_var2) + input_var3. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer.

- ``let T:%output_var = .fms(T:%input_var1, T:%input_var2, T:%input_var3)`` :- Fused multiply subtract. It computes (input_var1 * input_var2) - input_var3. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer.

- ``let T:%output_var = .fnma(T:%input_var1, T:%input_var2, T:%input_var3)`` :- Fused negative multiply add. It computes -(input_var1 * input_var2) + input_var3. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer.

- ``let T:%output_var = .fnms(T:%input_var1, T:%input_var2, T:%input_var3)`` :- Fused negative multiply subtract. It computes -(input_var1 * input_var2) - input_var3. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer.

- ``let T:%output_var = .clamp(T:%input_var, T:%min, T:%max)`` :- Clamps a value between a minimum and maximum value. It returns the minimum value if the input value is less than the minimum value, the maximum value if the input value is greater than the maximum value, and the input value itself if it is between the minimum and maximum values. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer.

- ``let T:%output_var = .fshl(T:%input_var1, T:%input_var2, T:%shift) `` :- Funnel shift left. It shifts the bits of input_var1 and input_var2 to the left by the number of bits specified by shift and fills the vacated bits with the bits shifted out from the other input. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer.

- ``let T:%output_var = .fshr(T:%input_var1, T:%input_var2, T:%shift)`` :- Funnel shift right. It shifts the bits of input_var1 and input_var2 to the right by the number of bits specified by shift and fills the vacated bits with the bits shifted out from the other input. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer. 



## Bitwise instructions

- `` let T:%output_var = .and(T:%input_var1, T:%input_var2)`` :- Bitwise and. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` .
- `` let T:%output_var = .or(T:%input_var1, T:%input_var2)`` :- Bitwise or. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` . It can have the attribute ``#[disjoint]``
- `` let T:%output_var = .xor(T:%input_var1, T:%input_var2)`` :- Bitwise xor. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` .
- `` let T:%output_var = .nand(T:%input_var1, T:%input_var2)`` :- Bitwise nand. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` . 
- `` let T:%output_var = .nor(T:%input_var1, T:%input_var2)`` :- Bitwise nor. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` .It can have the attribute ``#[disjoint]``
- `` let T:%output_var = .xnor(T:%input_var1, T:%input_var2)`` :- Bitwise xnor. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` .
- `` let T:%output_var = .shl(T:%input_var1, T:%input_var2)`` :- Bitwise shift left. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` . It can have the attribute ``#[nuw]`` or ``#[nsw]`` or both.
- `` let T:%output_var = .lshr(T:%input_var1, T:%input_var2)`` :- Logical shift right. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` . It can have the attribute ``#[exact]``.
- `` let T:%output_var = .ashr(T:%input_var1, T:%input_var2)`` :- Arithmetic shift right. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` . It can have the attribute ``#[exact]``.
- ``let T:%output_var = .rotl(T:%input_var1, T:%input_var2)`` :- Rotate left of an integer value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer. It rotates the bits of input_var1 to the left by the number of bits specified by input_var2. The bits that are rotated out on the left are rotated back in on the right. The bitwidth can be any integer type.
- ``let T:%output_var = .rotr(T:%input_var1, T:%input_var2)`` :- Rotate right of an integer value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer. It rotates the bits of input_var1 to the right by the number of bits specified by input_var2. The bits that are rotated out on the right are rotated back in on the left. The bitwidth can be any integer type.
  
## Comparison instructions

- `` let T1:%output_var = .eq(T:%input_var1, T:%input_var2)`` :- Compares 2 values for equality. T can be any type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer/ptr. The output is of type i1/<i1,M> based on if input type is vector or not

    If ``T0`` is float/brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. It can also have the attribute ``#[unordered]`` to indicate that if any of the input is NaN then the result is true. By default it is ordered comparison where if any of the input is NaN then the result is false.

- `` let T1:%output_var = .neq(T:%input_var1, T:%input_var2)`` :- Compares 2 values for inequality. T can be any type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer/ptr. The output is of type i1/<i1,M> based on if input type is vector or not

    If ``T0`` is float/brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. It can also have the attribute ``#[unordered]`` to indicate that if any of the input is NaN then the result is true. By default it is ordered comparison where if any of the input is NaN then the result is false.

- `` let T1:%output_var = .gt(T:%input_var1, T:%input_var2)`` :- Compares if input_var1 is greater than input_var2. T can be any type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer/ptr. The output is of type i1/<i1,M> based on if input type is vector or not

    If ``T0`` is integer then it can have the attribute ``#[unsigned]`` to indicate that it is unsigned comparison. By default it is signed comparison.

    If ``T0`` is ptr then it is always unsigned comparison. It has no attribute for signedness.

    If ``T0`` is float/brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. It can also have the attribute ``#[unordered]`` to indicate that if any of the input is NaN then the result is true. By default it is ordered comparison where if any of the input is NaN then the result is false.

- `` let T1:%output_var = .lt(T:%input_var1, T:%input_var2)`` :- Compares if input_var1 is less than input_var2. T can be any type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer/ptr. The output is of type i1/<i1,M> based on if input type is vector or not

    If ``T0`` is integer then it can have the attribute ``#[unsigned]`` to indicate that it is unsigned comparison. By default it is signed comparison.

    If ``T0`` is ptr then it is always unsigned comparison. It has no attribute for signedness.

    If ``T0`` is float/brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. It can also have the attribute ``#[unordered]`` to indicate that if any of the input is NaN then the result is true. By default it is ordered comparison where if any of the input is NaN then the result is false.

- `` let T1:%output_var = .ge(T:%input_var1, T:%input_var2)`` :- Compares if input_var1 is greater than or equal to input_var2. T can be any type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer/ptr. The output is of type i1/<i1,M> based on if input type is vector or not

    If ``T0`` is integer then it can have the attribute ``#[unsigned]`` to indicate that it is unsigned comparison. By default it is signed comparison.

    If ``T0`` is ptr then it is always unsigned comparison. It has no attribute for signedness.

    If ``T0`` is float/brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. It can also have the attribute ``#[unordered]`` to indicate that if any of the input is NaN then the result is true. By default it is ordered comparison where if any of the input is NaN then the result is false.

- `` let T1:%output_var = .le(T:%input_var1, T:%input_var2)`` :- Compares if input_var1 is less than or equal to input_var2. T can be any type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer/ptr. The output is of type i1/<i1,M> based on if input type is vector or not

    If ``T0`` is integer then it can have the attribute ``#[unsigned]`` to indicate that it is unsigned comparison. By default it is signed comparison.

    If ``T0`` is ptr then it is always unsigned comparison. It has no attribute for signedness.

    If ``T0`` is float/brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. It can also have the attribute ``#[unordered]`` to indicate that if any of the input is NaN then the result is true. By default it is ordered comparison where if any of the input is NaN then the result is false.

- `` let T1:%output_var = .either_nan(T:%input_var1, T:%input_var2)`` :- Compares if either of the input is NaN. T can be any type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. The output is of type i1/<i1,M> based on if input type is vector or not

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- `` let T1:%output_var = .neither_nan(T:%input_var1, T:%input_var2)`` :- Compares if neither of the input is NaN. T can be any type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. The output is of type i1/<i1,M> based on if input type is vector or not

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. 

 
## Conversion instructions

- `` let T2:%output_var = .trunc(T1:%input_var)`` :- Truncates a float/brain float/integer/vector of float/brain float/integer from T1 to a smaller float/brain float/integer type/vector of float/brain float/integer T2. Note base type of T1 must be integer if base type of T2 is integer and base type of T1 must be float/brain float if base type of T2 is float/brain float. Also error if bitwidth of base type of T1 is <= than  bitwidth of base type of T2. Both T1 and T2 must be vector or both must be non vector. No mixing allowed.

    It relies on the type T2 to determine the kind of truncation and how the value is truncated. So no need to seperately specify the type of output/output bitwidth in the .trunc instruction. The type of output variable is enough to determine the type of truncation and how the value is truncated.

    If the base type is integer then it can have the attribute ``#[nuw]`` or ``#[nsw]`` or both for the trunc instruction..

- `` let T2:%output_var = .ext(T1:%input_var)`` :- Extends a float/brain float/integer/vector of float/brain float/integer from T1 to a larger float/brain float/integer type/vector of float/brain float/integer T2. Note base type of T1 must be integer if base type of T2 is integer and base type of T1 must be float/brain float if base type of T2 is float/brain float. Also error if bitwidth of base type of T1 is >= than  bitwidth of base type of T2. Both T1 and T2 must be vector or both must be non vector. No mixing allowed.

    It relies on the type T2 to determine the kind of extension and how the value is extended. So no need to seperately specify the type of output/output bitwidth in the .ext instruction. The type of output variable is enough to determine the type of extension and how the value is extended.

    If the base type is integer then it can have the attribute ``#[unsigned]`` to indicate that it is zero extension. By default it is sign extension. If you have
    ``#[unsigned]`` then it is equivalent to zext of llvm. You can also have the attribute ``#[nsb]``(stands for no signed bits) to indicate the same thing as nneg on llvm. ``#[nsb]`` is only valid when you also have ``#[unsigned]``. If you have both ``#[unsigned]`` and ``#[nsb]`` then it is zero extension with the additional assumption that the value's sign bit is 0(Gives a tighter range. Like for i8 the usual range is 0 to 255 but with #[nsb] the range is 0 to 127).


- `` let T2:%output_var = .float_to_int(T1:%input_var)`` :- Converts a float/brain float/vector of float of type T1 to an integer/vector of integer pf type T2. 

    It relies on the type T2 to determine how the value is converted. So no need to seperately specify the type of output/output bitwidth in the .float_to_int instruction. The type of output variable is enough to determine how the value is converted.

    It can have the attribute ``#[unsigned]`` to indicate that it is unsigned conversion(The int is unsigned). By default it is signed conversion.

- `` let T2:%output_var = .int_to_float(T1:%input_var)`` :- Converts an integer/vector of integer of type T1 to a float/brain float/vector of float of type T2.

    It relies on the type T2 to determine how the value is converted. So no need to seperately specify the type of output/output bitwidth in the .int_to_float instruction. The type of output variable is enough to determine how the value is converted.

    It can have the attribute ``#[unsigned]`` to indicate that it is unsigned conversion(The int is unsigned). By default it is signed conversion.

- `` let T2:%output_var = .ptr_to_int(T1:%input_var)`` :- Converts a pointer/vector of pointer of type T1 to an integer/vector of i64 of type T2. Yes the int must be of type i64 or vector of i64(Because only supporting 64 bit systems). Use .trunc after ptr_to_int if you want to convert to a smaller integer type.
Unlikely but in future if we support other bit system like 32 bit then we have to modify the type constraint of T2 a bit

- `` let T2:%output_var = .int_to_ptr(T1:%input_var)`` :- Converts an integer/vector of i64 of type T1 to a pointer/vector of pointer of type T2. Yes the int must be of type i64 or vector of i64(Because only supporting 64 bit systems). Use .ext before int_to_ptr if you want to convert from a smaller integer type.
Unlikely but in future if we support other bit system like 32 bit then we have to modify the type constraint of T1 a bit

- `` let T2:%output_var = .bitcast(T1:%input_var)`` :- Bitcast from T1 to T2. T1 and T2 must be of the same bitwidth and can be any type as long as same bit width. It just reinterprets the bits of the value of T1 as a value of type T2. So it does not change the bits of the value, it just changes how the bits are interpreted. You cant bitcast between i64 and ptr
    
## Unary instructions

- ``let T:%output_var = .neg(T:%input_var)`` :- Negates a float/brain float/integer value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. 

    If T0 is float/brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. Not same as ``.sub(T:0,%input_var)`` because .sub will give you a positive zero if input_var is a positive zero but fneg will give you a negative zero. So they are different when it comes to signed zeros. Also for some fast math attribute combination fneg might be able to give you a better optimization than sub and vice versa. So they are not the same instruction and they can have different optimizations.

- ``let T:%output_var = .not(T:%input_var)`` :- Bitwise not of an integer value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer. 

- ``let T:%output_var = .abs(T:%input_var)`` :- Absolute value of a float/brain float/integer value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. For int it assumes signed

    If T0 is integer then it can have the attribute ``#[nsw]`` or ``#[nuw]`` or both for the abs instruction.

    If T0 is float/brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%output_var = .ceil(T:%input_var)`` :- Ceil of a float/brain float value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. 

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%output_var = .floor(T:%input_var)`` :- Floor of a float/brain float value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float.

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%output_var = .integral_part(T:%input_var)`` :- Get integral part of a float/brain float value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float.

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%output_var = .fractional_part(T:%input_var)`` :- Get fractional part of a float/brain float value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float.

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%output_var = .roundnearest(T:%input_var)`` :- Round of a float/brain float value to the nearest integer. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float.

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%output_var = .roundeven(T:%input_var)`` :- Roundeven of a float/brain float value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float.

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%output_var = .sqrt(T:%input_var)`` :- Square root of a float/brain float value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float.

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%output_var = .reciprocal(T:%input_var)`` :- Reciprocal of a float/brain float value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float.

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

    It has the attribute ``#[approx]`` to indicate that it is an approximate reciprocal which might be faster than the exact reciprocal but less accurate. So if you have #[approx] then it is an approximate reciprocal and if you dont have #[approx] then it is an exact reciprocal.

- ``let T:%output_var = .rsqrt(T:%input_var)`` :- Reciprocal square root of a float/brain float value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float.

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

    It has the attribute ``#[approx]`` to indicate that it is an approximate reciprocal square root which might be faster than the exact reciprocal square root but less accurate. So if you have #[approx] then it is an approximate reciprocal square root and if you dont have #[approx] then it is an exact reciprocal square root.

- ``let T:%output_var = .popcount(T:%input_var)`` :- Population count of an integer value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer. The output is of type iN/<iN,M> where N is the bitwidth of the input type.

- ``let T:%output_var = .ctz(T:%input_var)`` :- Count trailing zeros of an integer value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer. The output is of type iN/<iN,M> where N is the bitwidth of the input type. It has #[zero_poison] attribute which if present, result is poison when input is zero 

- ``let T:%output_var = .clz(T:%input_var)`` :- Count leading zeros of an integer value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer. The output is of type iN/<iN,M> where N is the bitwidth of the input type. It has #[zero_poison] attribute which if present, result is poison when input is zero 

- ``let T:%output_var = .parity(T:%input_var)`` :- Parity of an integer value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer. The output is of type i1/<i1,M> based on if input type is vector or not. It returns 1 if the number of set bits in the input is odd and 0 if the number of set bits in the input is even.

- ``let T:%output_var = .bswap(T:%input_var)`` :- Byte swap of an integer/float value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer/float/brain float. It reverses the order of bytes in the input value. So for example if the input is 0x12345678 then the output will be 0x78563412. The bitwidth but be multile of 8. The only reason it works for float is because the operation is kinda common for float(endians swap). Without float support, u would need bit case. Which works but no need to do it

- ``let T:%output_var = .bitreverse(T:%input_var)`` :- Bit reverse of an integer value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some integer. It reverses the order of bits in the input value. So for example if the input is 0b00000000000000000000000000001011 (32 bit) then the output will be 0b11010000000000000000000000000000 (32 bit). The bitwidth can be any integer type.

## Float Classification unary instructions

- ``let T0:%output_var = .isnan(T:%input_var)`` :- Checks if a float/brain float value is NaN. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. The output is of type i1/<i1,M> based on if input type is vector or not

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T0:%output_var = .isinf(T:%input_var)`` :- Checks if a float/brain float value is infinity. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. The output is of type i1/<i1,M> based on if input type is vector or not

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. 

- ``let T0:%output_var = .isfinite(T:%input_var)`` :- Checks if a float/brain float value is finite. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. The output is of type i1/<i1,M> based on if input type is vector or not

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T0:%output_var = .issubnormal(T:%input_var)`` :- Checks if a float/brain float value is subnormal. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. The output is of type i1/<i1,M> based on if input type is vector or not

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T0:%output_var = .isnormal(T:%input_var)`` :- Checks if a float/brain float value is normal. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. The output is of type i1/<i1,M> based on if input type is vector or not

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T0:%output_var = .iszero(T:%input_var)`` :- Checks if a float/brain float value is +0/-0. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. The output is of type i1/<i1,M> based on if input type is vector or not

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T0:%output_var = .isnegative(T:%input_var)`` :- Checks if a float/brain float value is negative. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. The output is of type i1/<i1,M> based on if input type is vector or not

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T0:%output_var = .ispositive(T:%input_var)`` :- Checks if a float/brain float value is positive. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. The output is of type i1/<i1,M> based on if input type is vector or not

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

## Memory instructions 

- ``let ptr:$global_var = .global(T:value)`` :- Defines a global variable. The type of the output variable must be a pointer type. The value can be any constantexpr literal(Not a variable). $global_var contains address of the global variable such that *$global_var is the value of the global variable. Innitialized by the value specified in the instruction. This instruction is not part of MIR. Stored in the global variable section of the module. It has the ``#[align(i8:N)]`` attribute also

- ``let T:%local_var = .local(T:initial_value)`` :- Defines a local variable. The value can be anything. In llvm u can do ``%local_var = initial_value`` but here you need this to keep the parser simpler(Actually the innitial design plan was diffrent but that changed but we still have some leftover from the innitial). This instruction is a part of MIR although doesnt do much. It is just a way to define a local variable and innitialize it with some value. T can be any type

- ``let ptr:%local_var = .alloca(iN:%size)`` :- Allocates memory on the stack. The size is in bytes. It has the attribute ``#[align(i8:N)]`` to specify the alignment of the allocated memory and by default it is 16. The alignment must be a power of 2 and it is in bytes. By default the alignment is 1 byte.

- ``let T:%output_var = .load(ptr:%ptr)`` :- Loads a value from memory of type T. It has the attribute ``#[align(i8:N)]`` to specify the alignment of the load and by default it is 16. The alignment must be a power of 2 and it is in bytes. By default the alignment is 16 byte. It also has the attribute ``#[volatile]`` to indicate that the load is volatile. It has the attribute ``#[invarient.load]`` to indicate that the value loaded is invariant and it will not change during the execution of the program. It has the attribute ``#[nontemporal]`` to indicate that the load is non temporal. It also has the attribute ``#[nonull]`` and ``#[nopoison]``. It has the attribute ``#[dereferenceable(i64:N)]`` to indicate that the pointer is dereferenceable for N bytes. It also has the attribute ``#[atomic(str:ordering)]`` to indicate that the load is atomic with the specified ordering. The ordering can be one of the following: ``acquire``, ``monotonic``, ``unordered`` and ``seq_cst``. If the attribute is not present then it is not an atomic load. If atomic it can also have the attribute ``#[syncscope("singlethreaded")]`` to indicate that the atomic load is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. Note:-If atomic then we require an explicit alignment

- ``.store(T:%value, ptr:%ptr)`` :- Stores a value to memory. It has the attribute ``#[align(i8:N)]`` to specify the alignment of the store and by default it is 16. The alignment must be a power of 2 and it is in bytes. By default the alignment is 16 byte. It also has the attribute ``#[volatile]`` to indicate that the store is volatile. It has the attribute ``#[nontemporal]`` to indicate that the store is non temporal. It also has the attribute ``#[nonull]`` and ``#[nopoison]``. It has the attribute ``#[dereferenceable(i64:N)]`` to indicate that the pointer is dereferenceable for N bytes. It also has the attribute ``#[atomic(str:ordering)]`` to indicate that the load is atomic with the specified ordering. The ordering can be one of the following: ``acquire``, ``monotonic``, ``unordered`` and ``seq_cst``. If the attribute is not present then it is not an atomic load. If atomic it can also have the attribute ``#[syncscope("singlethreaded")]`` to indicate that the atomic load is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. Note:-If atomic then we require an explicit alignment

- ``.memcpy(ptr:%dest, ptr:%src, iN:%size)`` :- Memory copy instruction for non overlaping region. Copies size bytes from the memory location pointed to by src to the memory location pointed to by dest. It has the attribute ``#[volatile]`` to indicate that the copy is volatile. It also has the attribute ``#[nontemporal(iN:0,iN:1)]`` to indicate that the ptr is non temporal. It also has the attribute ``#[nonull(iN:0,iN:1)]`` and ``#[nopoison(iN:0,iN:1)]``. It has the attribute ``#[dereferenceable(i64:N,iN:0,iN:1)]`` to indicate that the src and dest pointers are dereferenceable for N bytes. It also has the attribute ``#[align(i8:N, iN:0,iN:1)]`` to specify the alignment of the pointer and by default it is 16. The alignment must be a power of 2 and it is in bytes. The ``iN:0`` and ``iN:1`` in the attributes are used to specify which pointer the attribute is for. For example if you have ``#[nonull(iN:0)]`` then it means that the src pointer is non aull and if you have ``#[nonull(iN:1)]`` then it means that the dest pointer is nonull. You must specify atleast one idx if u use the attribute

- ``.memmove(ptr:%dest, ptr:%src, iN:%size)`` :- Memory move instruction for overlaping region. Copies size bytes from the memory location pointed to by src to the memory location pointed to by dest. It has the attribute ``#[volatile]`` to indicate that the copy is volatile. It also has the attribute ``#[nontemporal(iN:0,iN:1)]`` to indicate that the ptr is non temporal. It also has the attribute ``#[nonull(iN:0,iN:1)]`` and ``#[nopoison(iN:0,iN:1)]``. It has the attribute ``#[dereferenceable(i64:N,iN:0,iN:1)]`` to indicate that the src and dest pointers are dereferenceable for N bytes. It also has the attribute ``#[align(i8:N, iN:0,iN:1)]`` to specify the alignment of the pointer and by default it is 16. The alignment must be a power of 2 and it is in bytes. The ``iN:0`` and ``iN:1`` in the attributes are used to specify which pointer the attribute is for. For example if you have ``#[nonull(iN:0)]`` then it means that the src pointer is non aull and if you have ``#[nonull(iN:1)]`` then it means that the dest pointer is nonull. You must specify atleast one idx if u use the attributealignment must be a power of 2 and it is in bytes.

- ``.memset(ptr:%dest, i8:%value, iN:%size)`` :- Memory set instruction. Sets size bytes at the memory location pointed to by dest to the value specified by value. It has the attribute ``#[volatile]`` to indicate that the set is volatile. It also has the attribute ``#[nontemporal]`` to indicate that the set is non temporal. It also has the attribute ``#[nonull]`` and ``#[nopoison]``. It has the attribute ``#[dereferenceable(i64:N)]`` to indicate that the dest pointer is dereferenceable for N bytes. It has the attribute ``#[align(i8:N)]`` to specify the alignment of the dest pointer and by default it is 16. 

- ``let i1:%output_var = .memcmp(ptr:%ptr1, ptr:%ptr2, iN:%size)`` :- Memory compare instruction. Compares size bytes at the memory location pointed to by ptr1 and ptr2. Returns an integer value less than, equal to, or greater than zero if the first size bytes of ptr1 is found, respectively, to be less than, to match, or be greater than the first size bytes of ptr2. It has the attribute ``#[volatile]`` to indicate that the compare is volatile. It also has the attribute ``#[nontemporal]`` to indicate that the compare is non temporal. It also has the attribute ``#[nonull]`` and ``#[nopoison]``. It has the attribute ``#[dereferenceable(i64:N)]`` to indicate that the ptr1 and ptr2 pointers are dereferenceable for N bytes. It also has the attribute ``#[nontemporal(iN:0,iN:1)]`` to indicate that the ptr is non temporal. It also has the attribute ``#[nonull(iN:0,iN:1)]`` and ``#[nopoison(iN:0,iN:1)]``. It has the attribute ``#[dereferenceable(i64:N,iN:0,iN:1)]`` to indicate that the src and dest pointers are dereferenceable for N bytes. It also has the attribute ``#[align(i8:N, iN:0,iN:1)]`` to specify the alignment of the pointer and by default it is 16. The alignment must be a power of 2 and it is in bytes. The ``iN:0`` and ``iN:1`` in the attributes are used to specify which pointer the attribute is for. For example if you have ``#[nonull(iN:0)]`` then it means that the src pointer is non aull and if you have ``#[nonull(iN:1)]`` then it means that the dest pointer is nonull. You must specify atleast one idx if u use the attributealignment must be a power of 2 and it is in bytes.

- ``let ptr:%output_var = .getaddress(T:%var, iN:%offset)`` :- Gets &var + offset. The type of output variable must be a pointer type. The type of var can be any type. The offset is in bytes. Note:-var is a variable and not a literal/expression. It has the attribute ``#[unsigned]`` to indicate that the offset is unsigned. By default it is signed. It also has ``#[nsw]`` or ``#[nuw]`` or both to indicate that the offset does not cause signed or unsigned overflow. Also has the attribute ``#[inbounds]`` . We dont have blockaddress instruction like llvm. Just use this 

- ``let ptr:%output_var = .ptroffset(ptr:%input_var, T:%offset)`` :- Gets input_var + offset. The type of output variable must be a pointer type. The input variable must be a pointer type. The offset can be any integer type. The offset is in bytes. It has the attribute ``#[unsigned]`` to indicate that the offset is unsigned. By default it is signed. It also has ``#[nsw]`` or ``#[nuw]`` or both to indicate that the offset does not cause signed or unsigned overflow.  Also has the attribute ``#[inbounds]`` 

- ``let ptr:%stack_ptr = .stacksave()`` :- Saves the current stack ptr and returns it. The type of output variable must be a pointer type. 

- ``.stackrestore(ptr:%stack_ptr)`` :- Restores the stack ptr to the value saved by stacksave. The input variable must be a pointer type and it must be the value returned by stacksave. stacksave and stackrestore can be used to create dynamic alloca which is an alloca that is not in the entry block of the function. You can use stacksave to save the stack pointer before the dynamic alloca and then use stackrestore to restore the stack pointer after the dynamic alloca. This way you can effectively free the memory allocated by the dynamic alloca. Useful in loops when u want to allocate some memory in each iteration and free it at the end of the iteration. Note that you should not use the stack pointer returned by stacksave for anything other than passing it to stackrestore. It is just an opaque value that represents the state of the stack and it should not be manipulated or dereferenced in any way.

- `` let T3:%output_var = .extractelement(T1:%input, T2:%index)`` :- Extracts an element from a vector/array/struct. ``T1`` is a vector/array/struct. The index type ``T2`` must be some integer of type ``iN``. ``T3`` is the type of the extracted element. For struct, the index must be a integer literal. But for array and vector it can be literal or variable. It can have the attribute ``#[inbounds]`` for array and vector but not for struct cuz struct index is always in bounds.

- `` let T1:%output_var = .insertelement(T1:%input, T2:%element, T3:%index)`` :- Inserts an element into a vector/array/struct. ``T1`` is a vector/array/struct. The index type ``T3`` must be some integer of type ``iN``. The element type ``T2`` must be of the same type as the element of the vector/array/struct at that index. For struct, the index must be a integer literal. But for array and vector it can be literal or variable. It can have the attribute ``#[inbounds]`` for array and vector but not for struct cuz struct index is always in bounds. The output is the same type as the input vector/array/struct and is the same as the input except the element at the index is replaced by the new element.

- ``.fence(str:ordering)`` :- Fence instruction. Both ordering and syncscope must be constexpr. Valid values for ordering are ``acquire``, ``release``, ``acq_rel`` and ``seq_cst``. It also has the attribute ``#[syncscope("singlethreaded")]`` to indicate that the fence is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. Note:-A fence instruction does not have any output variable and it does not have any input variable. It just acts as a memory barrier to ensure ordering of memory operations.

- ``let {T,i1}:%output_var = .cmpxchg(ptr:%ptr, T:%expected, T:%desired, str:success_ordering,str:failure_ordering)`` :- Compare and exchange instruction. It atomically compares the value at the memory location pointed to by ptr with the expected value. If they are equal then it atomically replaces the value at the memory location with the desired value and returns the original value and true. If they are not equal then it does not modify the memory location and returns the original value and false. The type of output variable is a struct of form {T, i1} where T is the type of the value at the memory location and i1 is a boolean indicating whether the exchange was successful or not. It has the compulsory attribute ``#[align(i8:N)]`` to specify the alignment of the operation and by default it is 16. The alignment must be a power of 2 and it is in bytes. It also has the attribute ``#[volatile]`` and ``#[weak]`` to indicate that the operation is volatile or weak.It can also have the attribute ``#[syncscope("singlethreaded")]`` to indicate that the atomic operation is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. ``success_ordering`` and ``failure_ordering`` must be const expr and ``success_ordering`` must be one of the following: monotonic, acquire, release, acq_rel, seq_cst but ``failure_ordering`` can only be one of the following: monotonic, acquire, seq_cst and it must not be release or acq_rel. 

## Binary Fetch instructions

The following are fetch instruction and can also have a atomic Read-Modify-Write version only if u specify the atomic attribute( #[atomic(str:<ordering>)]). If you specify it then. Atomically reads a value from memory, applies a binary operation with a given operand, and writes the result back. Returns the original value. All of them have the attribute ``#[align(i8:N)]`` to specify the alignment of the operation and by default it is 16. The alignment must be a power of 2 and it is in bytes. They also have the attribute ``#[volatile]`` to indicate that the operation is volatile.If it is a atomic then you must specify with #[atomic(str:<ordering>)]. By default it is not atomic. For atomic they can also have the attribute ``#[syncscope("singlethreaded")]`` to indicate that the atomic operation is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. It supports the following ordering monotonic, acquire, release, acq_rel, seq_cst

- ``let T:%old = .fetch_xchg(ptr:%ptr, T:%value)`` :- Replaces the value at the memory location pointed to by ptr with the given value and returns the original value. T can be integer or float

- ``let T:%old = .fetch_add(ptr:%ptr, T:%value)`` :- Adds the given value to the value at the memory location pointed to by ptr and returns the original value. T can be integer or float. IT can have the attribute ``#[saturating]`` to indicate that the addition is saturating. So if you have #[saturating] then it is a saturating addition and if you dont have #[saturating] then it is a normal addition. If saturating then you may wanna specify #[unsigned] for unsigned saturation given T is integer. By default it is signed saturation.

    If T is an integer type then it can have the attribute ``#[nsw]`` or ``#[nuw]`` or both to indicate that the addition does not cause signed or unsigned overflow.

    If T is a float type then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_sub(ptr:%ptr, T:%value)`` :- Subtracts the given value from the value at the memory location pointed to by ptr and returns the original value. T can be integer or float. It can have the attribute ``#[saturating]`` to indicate that the subtraction is saturating. So if you have #[saturating] then it is a saturating subtraction and if you dont have #[saturating] then it is a normal subtraction. If saturating then you may wanna specify #[unsigned] for unsigned saturation given T is integer. By default it is signed saturation.

    If T is an integer type then it can have the attribute ``#[nsw]`` or ``#[nuw]`` or both to indicate that the addition does not cause signed or unsigned overflow.

    If T is a float type then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_mul(ptr:%ptr, T:%value)`` :- Multiplies the given value with the value at the memory location pointed to by ptr and returns the original value. T can be integer or float. It can have the attribute ``#[saturating]`` to indicate that the multiplication is saturating. So if you have #[saturating] then it is a saturating multiplication and if you dont have #[saturating] then it is a normal multiplication. If saturating then you may wanna specify #[unsigned] for unsigned saturation given T is integer. By default it is signed saturation.

    If T is an integer type then it can have the attribute ``#[nsw]`` or ``#[nuw]`` or both to indicate that the multiplication does not cause signed or unsigned overflow.

    If T is a float type then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_div(ptr:%ptr, T:%value)`` :- Divides the value at the memory location pointed to by ptr by the given value and returns the original value.

- ``let T:%old = .fetch_rem(ptr:%ptr, T:%value)`` :- Computes the remainder of the division of the value at the memory location pointed to by ptr by the given value and returns the original value.

- ``let T:%old = .fetch_copysign(ptr:%ptr, T:%value)`` :- Copies the sign of the given value to the value at the memory location pointed to by ptr and returns the original value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/int.

     It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_max(ptr:%ptr, T:%value)`` :- Compares the given value with the value at the memory location pointed to by ptr and replaces the value at the memory location with the maximum of the two values. Returns the original value. T can be integer or float. For integer it can be signed or unsigned based on the presence of ``#[unsigned]`` attribute. By default it is signed

- ``let T:%old = .fetch_min(ptr:%ptr, T:%value)`` :- Compares the given value with the value at the memory location pointed to by ptr and replaces the value at the memory location with the minimum of the two values. Returns the original value. T can be integer or float. For integer it can be signed or unsigned based on the presence of ``#[unsigned]`` attribute. By default it is signed

- ``let T:%old = .fetch_and(ptr:%ptr, T:%value)`` :- Performs a bitwise and operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_nand(ptr:%ptr, T:%value)`` :-  performs a bitwise nand operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_or(ptr:%ptr, T:%value)`` :-  performs a bitwise or operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_nor(ptr:%ptr, T:%value)`` :-  performs a bitwise nor operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_xor(ptr:%ptr, T:%value)`` :-  performs a bitwise xor operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_xnor(ptr:%ptr, T:%value)`` :-  performs a bitwise xnor operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_shl(ptr:%ptr, T:%value)`` :-  performs a left shift operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_ashr(ptr:%ptr, T:%value)`` :-  performs a right arithmatic shift operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_lshr(ptr:%ptr, T:%value)`` :-  performs a right logical shift operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_rotl(ptr:%ptr, T:%value)`` :-  performs a rotate left operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_rotr(ptr:%ptr, T:%value)`` :-  performs a rotate right operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.


## Unary fetch instructions

The following are fetch instruction and can also have a atomic Read-Modify-Write version only if u specify the atomic attribute( #[atomic(str:<ordering>)]). If you specify it then. Atomically reads a value from memory, applies a binary operation with a given operand, and writes the result back. Returns the original value. All of them have the attribute ``#[align(i8:N)]`` to specify the alignment of the operation and by default it is 16. The alignment must be a power of 2 and it is in bytes. They also have the attribute ``#[volatile]`` to indicate that the operation is volatile.If it is a atomic then you must specify with #[atomic(str:<ordering>)]. By default it is not atomic. For atomic they can also have the attribute ``#[syncscope("singlethreaded")]`` to indicate that the atomic operation is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. It supports the following ordering monotonic, acquire, release, acq_rel, seq_cst

- ``let T:%old = .fetch_neg(ptr:%ptr)`` :-  negates the value at the memory location pointed to by ptr and returns the original value. T can be integer or float

    If T is an integer type then it can have the attribute ``#[nsw]`` or ``#[nuw]`` or both to indicate that the negation does not cause signed or unsigned overflow.

    If T is a float type then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_not(ptr:%ptr)`` :-  performs a bitwise not operation on the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_abs(ptr:%ptr)`` :-  computes the absolute value of the value at the memory location pointed to by ptr and returns the original value. T can be integer or float

    If T is an integer type then it can have the attribute ``#[nsw]`` or ``#[nuw]`` or both to indicate that the absolute value does not cause signed or unsigned overflow.

    If T is a float type then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_ceil(ptr:%ptr)`` :-  computes the ceiling of the value at the memory location pointed to by ptr and returns the original value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. 

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_floor(ptr:%ptr)`` :-  computes the floor of the value at the memory location pointed to by ptr and returns the original value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. 

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_integral_part(ptr:%ptr)`` :-  rounds the value at the memory location pointed to by ptr to the nearest integer and returns the original value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. 

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_fractional_part(ptr:%ptr)`` :-  rounds the value at the memory location pointed to by ptr to the nearest integer and returns the original value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. 

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_roundnearest(ptr:%ptr)`` :-  rounds the value at the memory location pointed to by ptr to the nearest integer and returns the original value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. 

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_roundeven(ptr:%ptr)`` :-  even rounds the value at the memory location pointed to by ptr and returns the original value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. 

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_sqrt(ptr:%ptr)`` :-  computes the square root of the value at the memory location pointed to by ptr and returns the original value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. 

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T:%old = .fetch_reciprocal(ptr:%ptr)`` :-  computes the reciprocal the value at the memory location pointed to by ptr and returns the original value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. 

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

    It has the attribute ``#[approx]`` to indicate that it is an approximate reciprocal and it may not be accurate. It can be used for performance optimization when the accuracy is not critical.

- ``let T:%old = .fetch_rsqrt(ptr:%ptr)`` :-  computes the approx reciprocal of the square root of the value at the memory location pointed to by ptr and returns the original value. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float. 

    It can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

    It has the attribute ``#[approx]`` to indicate that it is an approximate reciprocal and it may not be accurate. It can be used for performance optimization when the accuracy is not critical.

- ``let T:%old = .fetch_popcount(ptr:%ptr)`` :-  counts the number of set bits in the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_ctz(ptr:%ptr)`` :-  counts the number of trailing zeros in the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_clz(ptr:%ptr)`` :-  counts the number of leading zeros in the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .fetch_parity(ptr:%ptr)`` :-  computes the parity of the value at the memory location pointed to by ptr and returns the original value. The parity is 1 if the number of set bits in the value is odd and 0 if it is even. T must be an integer type.

- ``let T:%old = .fetch_bswap(ptr:%ptr)`` :-  swaps the byte order of the value at the memory location pointed to by ptr and returns the original value. T must be an integer type/float. IT works for float because this endianness swap is common for float also. Without float support, u would need bit case. Which works but no need to do it

- ``let T:%old = .fetch_bitreverse(ptr:%ptr)`` :-  reverses the bits in the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

## Terminator instructions 

A terminator statement must be present at the end of a instruction. If no terminator then error. We dont go from one block to next without a .br or similar instruction

- ``.ret`` or ``.ret(T:%return_value)`` :- Return from a function. If the function return type is void then use ``.ret`` with no return value. If the function return type is not void then. It has the attribute ``#[noreturn]`` to indicate that the function does not return. In that case you can also use ``.ret`` with no return value even if the function return type is not void. But if you have a return value then it must be of the same type as the function return type.

- ``.unreachable`` :- Indicates that the code is unreachable. Maybe when u call exit() u can used ``.unreachable`` after the call. Used when you dont jump to a diffrent block but you also dont want to return from the function. 

- ``.trap`` :-  Emits a hardware trap instruction. Distinct from ``.unreachable`` which is a compiler hint about dead code with no guaranteed runtime effect. ``.trap`` is observable and guaranteed to halt execution. It has the ``#[breakpoint]`` attribute to indicate that it is a breakpoint trap which can be used for debugging.

- ``.br(T0:@dest,T1:{...})`` :- Unconditional branch to the destination block.T0 is some label type. T1 is the input argument type as a struct. i.e if %dest takes in i32 and i64 then T1 = {i32, i64}. If it takes no arguments then T1 = {} and so on. T1 must be an ananomous struct of form {...}. Note you must write the arguments are {...} so u cant do T1:%x just because %x has same type as T1. You have to write T1:{...}. Because this is more of a parser trick to make it easier to parse the instruction. Actually we wanted %dest(...) but that is a bit harder to parse. So going with this. 

- ``.br(i1:%condition, T0:@true_dest, T1:{...}, T2:@false_dest, T3:{...})`` :- Conditional branch to the destination block based on the condition. If condition is true then branch to true_dest otherwise branch to false_dest. The condition must be of type i1. T1:{...} is argument for true_dest and T3:{...} is argument for false_dest. Same parsing rule regarding from before apply here.

    It has the #[freq(i32:10,i32:20,...)] attribute to indicate the frequency of branching to each destination block. So in the example above it indicates that the frequency of branching to true_dest is 10 and the frequency of branching to false_dest is 20. The frequencies are just hints for the optimizer and they dont have to be accurate. They can be used by the optimizer to optimize the code better. For example if the frequency of branching to true_dest is much higher than the frequency of branching to false_dest then the optimizer can optimize the code better by putting the code for true_dest in a hot path and putting the code for false_dest in a cold path. The branching is unpredictable if all the frequencies are the same. It also has ``#[unpredictable]`` attribute to indicate that the branching is unpredictable. If unpredictable u cant set the frequencies because if you have frequencies then it is not unpredictable. So if you have ``#[unpredictable]`` then error if you also have #[freq(i32:10,i32:20,...)] attribute and vice versa.

    TODO: In future have loop and vectorization hint attributes

- ``.switch(T:%condition, T0:@default_dest, T1:{...}, T:%case1_value, T2:@case1_dest, T3:{...}, T:%case2_value, T4:@case2_dest, T5:{...}...)`` :- Switch instruction. Branches to the destination block based on the value of the condition. If the condition matches case1_value then branch to case1_dest, if it matches case2_value then branch to case2_dest and so on. If it does not match any of the case values then branch to default_dest. The condition must be integer. The case values must be of the same type as the condition. T1:{...} is argument for default_dest, T3:{...} is argument for case1_dest, T5:{...} is argument for case2_dest and so on. Same parsing rule regarding from before apply here. NOTE:-.switch is more of a syntactic sugar that helps the optimizer optimize better. You can always use multiple .br instructions to achieve the same thing as .switch but .switch makes it easier for the optimizer to optimize the code better. So it is recommended to use .switch when you have multiple branches based on the value of a variable. 

    It has the #[freq(i32:10,i32:20,...)] attribute to indicate the frequency of branching to each destination block. So in the example above it indicates that the frequency of branching to default_dest is 10, the frequency of branching to case1_dest is 20 and so on. The frequencies are just hints for the optimizer and they dont have to be accurate. They can be used by the optimizer to optimize the code better. For example if the frequency of branching to case1_dest is much higher than the frequency of branching to case2_dest then the optimizer can optimize the code better by putting the code for case1_dest in a hot path and putting the code for case2_dest in a cold path. The branching is unpredictable if all the frequencies are the same.  It also has ``#[unpredictable]`` attribute to indicate that the branching is unpredictable. If unpredictable u cant set the frequencies because if you have frequencies then it is not unpredictable. So if you have ``#[unpredictable]`` then error if you also have #[freq(i32:10,i32:20,...)] attribute and vice versa.

- ``.indirectbr(ptr:%dest_ptr, label:@label1, label:@label2...)`` :- Indirect branch to the destination block based on the value of the destination pointer. The destination pointer must be of type ptr and it must point to a block label(Or else UB). If the value of the destination pointer matches label1 then branch to label1, if it matches label2 then branch to label2 and so on. Note:-The labels here cant have any argument because indirectbr is more of a syntactic sugar for the optimizer. It just jumps to the address pointed by the destination pointer

    It has the #[freq(i32:10,i32:20,...)] attribute to indicate the frequency of branching to each destination block. So in the example above it indicates that the frequency of branching to label1 is 10, the frequency of branching to label2 is 20 and so on. The frequencies are just hints for the optimizer and they dont have to be accurate. They can be used by the optimizer to optimize the code better. For example if the frequency of branching to label1 is much higher than the frequency of branching to label2 then the optimizer can optimize the code better by putting the code for label1 in a hot path and putting the code for label2 in a cold path. The branching is unpredictable if all the frequencies are the same. It also has ``#[unpredictable]`` attribute to indicate that the branching is unpredictable. If unpredictable u cant set the frequencies because if you have frequencies then it is not unpredictable. So if you have ``#[unpredictable]`` then error if you also have #[freq(i32:10,i32:20,...)] attribute and vice versa.

## Call instruction

Seperate category cuz this instruction is big and complex enough to deserve its own category. Also it has some unique attributes that other instructions dont have.

- ``let T:%output_var = .call(T:%func, T1:%arg1, T2:%arg2...)`` :- Calls a function. T must be a function type containing the signature. Note:%func is technically a ptr also so treating %func as ptr is valid but you must specify the function signature in T and not write ptr. so you can do ``let ptr:%func = .some_func`` and then do ``let T:%output_var = .call(T:%func, T1:%arg1, T2:%arg2...)`` where T is the function type of some_func and T cant be ptr. You can also do ``let fn(...)->...:func = some_func`` but in MIR level we translate it to ``type ptr:%func = .some_func`` 

    It has the attribute ``#[tail]`` , ``#[musttail]`` or ``#[notail]``. IT can take only one of these attributes. We also have ``#[cold]`` attribute that his partiqular call is cold(Even if not mentioned at function defination. It can be used to mark a call site as cold even if the function itself is not marked as cold. This can be useful when you know that a particular call site is unlikely to be executed and you want to optimize for the common case ). We also have the attribute ``#[noreturn]`` to indicate that the function being called does not return(Even if not mentioned at function defination. It can be used to mark a call site to not return for this particular case of arguments). In that case you can also use ``.call`` with no output variable even if the function return type is not void. But if you have an output variable then it must be of the same type as the function return type. If it returns a float or vector of float then it can also have fast math attributes like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

    It also has the ``[nosideeffect]`` attribute to indicate that the function being called does not have any side effect. This means that the function does not read or write any memory and it does not have any observable effect on the program other than returning a value. This can be used by the optimizer to optimize the code better. For example if a call instruction has the ``[nosideeffect]`` attribute then the optimizer can remove the call instruction if its return value is not used because it has no side effect and it does not affect the program in any way. THis attribute overrides the attributes specified at the function definition for this particular call site. If not mentioned for a partiqular call site then we do whatever the function defination says for that call site.

    Attributes like noalias,readonly,returned,nonnull,align <n>,dereferenceable(<n>),nopoison,nnan,ninf,readnone,writeonly,writable,returned, or nocapture can be used like ``[#noalias(i64:1,.....)]`` and same for the other attributes to specify the argument index that the attribute applies to. So for example if you have ``[#noalias(i64:1, i64:3)]`` then it means that the first and third argument of the function call are noalias. This will override the attributes specified at the function definition for these particular arguments. If not mentioned for a partiqular argument then we do whatever the function defination says for that argument. Why we allow it here? Because sometimes we want to call a function with different attributes for different call sites + if you are dealing with function ptrs/lambdas, there is no way to specify the attributes at the function definition because it is a variable. Like consider the following
    ```
    fn name(x:i32){
        if x>1{
            return some_func1
        }
        return some_func2
    }
    ```
    When you call name() you dont know which function ptr it will return so you cant specify the attributes at the function definition. So you have to specify the attributes at the call site. This is one of the main reasons why we allow it here.

    The above rule also applies to byval, byref, inalloca(<ty>), preallocated(<ty>), sret, zeroext and signext. Just remember for byval and other similar argument you have ``#[byref(type:T0, i64:arg_index0,type:T1, i64:arg_index1,....)]``. If defination is given then attribute specified at call site must match with defination if defination is available. If not we assume that the function can take any attribute for that argument and we just follow whatever is specified at the call site.

    Unlike llvm, there are a limited number of calling convention  mainly because we only support x86_64. So we have the following calling conventions: ccc, fastcc, coldcc and tailcc. You can specify the calling convention like ``#[cc(str:calling_convention)]`` where calling_convention is one of the calling conventions mentioned before. If not specified then it is the default calling convention which is ccc. 

    We can set the extension of the return value can be set by applyiny the attribute ``#[return_extension(str:extension_type)]`` to the call instruction where extension_type can be either "zero" or "sign" or "no". 

    ``let T:%output_var #[noalias] = .call(T:%func, T1:%arg1, T2:%arg2...)``
    You can do this if you want to mark the return value as noalias. This is allowed because you cant mark noalias on the function return type. nonnull,dereferenceable(<bytes>),nopoison,align(<alignment>),nnan,ninf can also be applied like this to the returned value. In MIR, the LocalDestRegister should store these attributes. Note these attribute are not unique to call instruction

    Reference :- https://claude.ai/share/47c8d0b7-d632-462a-b757-a8f81499862c


- ``.call(T:%func, T1:%arg1, T2:%arg2...)`` :- Same as above but for functions that return void.

## SIMD instruction 

- `` let <T, M>:%output_var = .shufflevector(<T, N2>:%input1, <T, N3>:%input2, <i16, M>:%mask)`` :- Shuffles the elements of 2 vectors according to a mask. Mask is compile time not run time

- ``let T0:%output_var = .reduce_add(<T0, N>:%input_vector)`` :- Reduces a vector by adding all its elements together. The result is a scalar value of type T. It can have the attribute ``#[saturating]`` to indicate that the addition is saturating. You can also specify ``#[unsigned]`` for unsigned saturation.

    If ``T0`` is integer then it can have 2 attribute. It can have attributes ``#[nsw]`` or ``#[nuw]` or both. Dont care if signed or unsigned, the result is same regardless

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. 

- ``let T0:%output_var = .reduce_mul(<T0, N>:%input_vector)`` :- Reduces a vector by multiplying all its elements together. The result is a scalar value of type T. It can have the attribute ``#[saturating]`` to indicate that the multiplication is saturating. You can also specify ``#[unsigned]`` for unsigned saturation.

    If ``T0`` is integer then it can have 2 attribute. It can have attributes ``#[nsw]`` or ``#[nuw]` or both. Dont care if signed or unsigned, the result is same regardless

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- ``let T0:%output_var = .reduce_and(<T0, N>:%input_vector)`` :- Reduces a vector by performing bitwise and operation on all its elements together. The result is a scalar value of type T. T must be an integer type.

- ``let T0:%output_var = .reduce_or(<T0, N>:%input_vector)`` :- Reduces a vector by performing bitwise or operation on all its elements together. The result is a scalar value of type T. T must be an integer type.

- ``let T0:%output_var = .reduce_xor(<T0, N>:%input_vector)`` :- Reduces a vector by performing bitwise xor operation on all its elements together. The result is a scalar value of type T. T must be an integer type.

- ``let T0:%output_var = .reduce_xnor(<T0, N>:%input_vector)`` :- Reduces a vector by performing bitwise xnor operation on all its elements together. The result is a scalar value of type T. T must be an integer type.

- ``let T0:%output_var = .reduce_min(<T0, N>:%input_vector)`` :- Reduces a vector by finding the minimum value among all its elements. The result is a scalar value of type T. T can be integer or float. For integer it can be signed or unsigned based on the presence of ``#[unsigned]`` attribute. By default it is signed

- ``let T0:%output_var = .reduce_max(<T0, N>:%input_vector)`` :- Reduces a vector by finding the maximum value among all its elements. The result is a scalar value of type T. T can be integer or float. For integer it can be signed or unsigned based on the presence of ``#[unsigned]`` attribute. By default it is signed

No reduce sub,nand,nor,div,rem because they are not associativity or commutative or both

- ``let <T,N>:%output_var = .splat(T:%input_scalar)`` :- Splat a scalar value to all elements of a vector. T can be integer or float or ptr.

- ``let <T,N>:%output_var = .step_vector(T:%start, T:%step)`` :- Create a vector where the first element is start and each subsequent element is incremented by step. So the vector will be [start, start+step, start+2*step, ...]. T can be integer or float.

## Other instructions

- ``let T0:%m = .select(T1:%condition, T0:%true_value, T0:%false_value)`` :- If T1 is of type i1 then we select %true_value if condition is true and select %false_value if condition is false. T0 can be any type. If T1 is of type <i1,M> then we select element wise from true_value and false_value based on the condition. So if the first element of condition is true then we select the first element of true_value otherwise we select the first element of false_value and so on for all elements. In this case T0 must be a vector type and the output is also a vector where each element is selected based on the corresponding element in the condition vector.

- ``let T:%output_var = .freeze(T:%input_var)`` :- Freezes the value of input_var. It is used to prevent certain optimizations that can lead to undefined behavior. It can be used when you have some value that is undef or poison and you want to use it in a way that does not cause undefined behavior. By freezing it, you are telling the compiler that the value can be any value of the type and it should not make any assumptions about it. So it can be used to safely use undef or poison values without causing undefined behavior.

- ``.va_start(ptr:%input_var)`` :- Used to initialize the variable argument list in a function that takes variable arguments. The input_var is of type ptr and it is a allocated object of {i32,i32,ptr,ptr}. Basically a va_list struct that contains the necessary information. Why not ``let ptr:%input_var = .va_start()``? Because in programming va_start is often implemented after allocating a va_list struct. Although unlikely u may wanna do something with the va_list struct before initializing it with va_start. So we allow it to be separate instruction. Also it is more consistent with llvm IR where va_start is a separate instruction that takes a pointer to a va_list struct as an argument and initializes it. So we follow the same design here. Same reason apply for va_copy

- ``.va_end(ptr:%input_var)`` :- Used to clean up the variable argument list in a function that takes variable arguments. The input_var is of type ptr and it is the same va_list struct that was initialized by va_start.

- ``.va_copy(ptr:%dest, ptr:%src)`` :- Used to copy the variable argument list from src to dest in a function that takes variable arguments. Both dest and src are of type ptr and they are both va_list structs.

- ``let T:%output_var = .va_arg(ptr:%input_var)`` :- Used to access the variable arguments in a function that takes variable arguments. The input_var is of type ptr and T is the type of the variable argument that we want to access

- ``let T:%output_var = .ptrmask(T:%input_var,T1:%mask)`` :- Masks a pointer with a mask. T is a ptr or vector of ptr. Mask is an integer or vector of integer. If T1 is vector then T must also be a vector of same size

- ``let type:%type_name = .assign_type(type:<type defination>)`` :- USed to create a typedef. Note:-This is not an actual instruction. Just to make the parser simpler. Ignored by MIR
