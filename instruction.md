## Binary instructions

- `` let T:%output_var = .add(T:%input_var1, T:%input_var2)`` :- Adds 2 numbers. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. 

    If ``T0`` is integer then it can have 2 attribute. It can have attributes ``#[nsw]`` or ``#[nuw]` or both. Dont care if signed or unsigned, the result is same regardless

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. 

- `` let T:%output_var = .sub(T:%input_var1, T:%input_var2)`` :- Subtracts 2 numbers. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. 

    If ``T0`` is integer then it can have 2 attribute. It can have attributes ``#[nsw]`` or ``#[nuw]` or both. Dont care if signed or unsigned, the result is same regardless

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. 

- `` let T:%output_var = .mul(T:%input_var1, T:%input_var2)`` :- Multiplies 2 numbers. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. 

    If ``T0`` is integer then it can have 2 attribute. It can have attributes ``#[nsw]`` or ``#[nuw]` or both. Dont care if signed or unsigned, the result is same regardless

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these. 

- `` let T:%output_var = .div(T:%input_var1, T:%input_var2)`` :- Division. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. 

    If ``T0`` is integer then it can have the attribute ``#[exact]``. It also has the attribute ``#[unsigned]`` to indicate that it is unsigned division. By default it is signed division. 

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.

- `` let T:%output_var = .rem(T:%input_var1, T:%input_var2)`` :- Remainder of division. T must be some type of form ``T0`` or ``<T0,M>`` where T0 is some float/brain float/integer. 

    If ``T0`` is integer then it can have the attribute ``#[unsigned]`` to indicate that it is remainder of unsigned division. By default it is remainder of signed division.

    If ``T0`` is float or brain float then it can have the fast math attribute like ``#[fast]`` or ``#[nnan]`` or ``#[ninf]`` or ``#[nsz]`` or ``#[arcp]`` or ``#[contract]`` or ``#[afn]`` or ``#[reassoc]`` or any combination of these.



## Bitwise instructions

- `` let T:%output_var = .and(T:%input_var1, T:%input_var2)`` :- Bitwise and. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` .
- `` let T:%output_var = .or(T:%input_var1, T:%input_var2)`` :- Bitwise or. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` . It can have the attribute ``#[disjoint]``
- `` let T:%output_var = .xor(T:%input_var1, T:%input_var2)`` :- Bitwise xor. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` .
- `` let T:%output_var = .shl(T:%input_var1, T:%input_var2)`` :- Bitwise shift left. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` . It can have the attribute ``#[nuw]`` or ``#[nsw]`` or both.
- `` let T:%output_var = .lshr(T:%input_var1, T:%input_var2)`` :- Logical shift right. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` . It can have the attribute ``#[exact]``.
- `` let T:%output_var = .ashr(T:%input_var1, T:%input_var2)`` :- Arithmetic shift right. T must be some integer of type ``i<N>`` or ``<i<N> , M>`` . It can have the attribute ``#[exact]``.


## SIMD/Struct/Array element insertion/extraction instructions

- `` let T3:%output_var = .extractelement(T1:%input, T2:%index)`` :- Extracts an element from a vector/array/struct. ``T1`` is a vector/array/struct. The index type ``T2`` must be some integer of type ``iN``. ``T3`` is the type of the extracted element. For struct, the index must be a integer literal. But for array and vector it can be literal or variable. It can have the attribute ``#[inbounds]`` for array and vector but not for struct cuz struct index is always in bounds.

- `` let T1:%output_var = .insertelement(T1:%input, T2:%element, T3:%index)`` :- Inserts an element into a vector/array/struct. ``T1`` is a vector/array/struct. The index type ``T3`` must be some integer of type ``iN``. The element type ``T2`` must be of the same type as the element of the vector/array/struct at that index. For struct, the index must be a integer literal. But for array and vector it can be literal or variable. It can have the attribute ``#[inbounds]`` for array and vector but not for struct cuz struct index is always in bounds. The output is the same type as the input vector/array/struct and is the same as the input except the element at the index is replaced by the new element.


## SIMD other instructions

- `` let <T, M>:%output_var = .shufflevector(<T, N2>:%input1, <T, N3>:%input2, <i16, M>:%mask)`` :- Shuffles the elements of 2 vectors according to a mask. Mask is compile time not run time

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
    ``#[unsigned]`` then it is equivalent to zext of llvm. You can also have the attribute ``#[nsb]`` to indicate the same thing as nneg on llvm. ``#[nsb]`` is only valid when you also have ``#[unsigned]``. If you have both ``#[unsigned]`` and ``#[nsb]`` then it is zero extension with the additional assumption that the value's sign bit is 0(Gives a tighter range. Like for i8 the usual range is 0 to 255 but with #[nsb] the range is 0 to 127).


- `` let T2:%output_var = .float_to_int(T1:%input_var)`` :- Converts a float/brain float/vector of float of type T1 to an integer/vector of integer pf type T2. 

    It relies on the type T2 to determine how the value is converted. So no need to seperately specify the type of output/output bitwidth in the .float_to_int instruction. The type of output variable is enough to determine how the value is converted.

    It can have the attribute ``#[unsigned]`` to indicate that it is unsigned conversion(The int is unsigned). By default it is signed conversion.

- `` let T2:%output_var = .int_to_float(T1:%input_var)`` :- Converts an integer/vector of integer of type T1 to a float/brain float/vector of float of type T2.

    It relies on the type T2 to determine how the value is converted. So no need to seperately specify the type of output/output bitwidth in the .int_to_float instruction. The type of output variable is enough to determine how the value is converted.

    It can have the attribute ``#[unsigned]`` to indicate that it is unsigned conversion(The int is unsigned). By default it is signed conversion.

- `` let T2:%output_var = .ptr_to_int(T1:%input_var)`` :- Converts a pointer/vector of pointer of type T1 to an integer/vector of i64 of type T2. Yes the int must be of type i64 or vector of i64(Because only supporting 64 bit systems). Use .trunc after ptr_to_int if you want to convert to a smaller integer type.

- `` let T2:%output_var = .int_to_ptr(T1:%input_var)`` :- Converts an integer/vector of i64 of type T1 to a pointer/vector of pointer of type T2. Yes the int must be of type i64 or vector of i64(Because only supporting 64 bit systems). Use .ext before int_to_ptr if you want to convert from a smaller integer type.

- `` let T2:%output_var = .bitcast(T1:%input_var)`` :- Bitcast from T1 to T2. T1 and T2 must be of the same bitwidth and can be any type as long as same bit width. It just reinterprets the bits of the value of T1 as a value of type T2. So it does not change the bits of the value, it just changes how the bits are interpreted. You cant bitcast between i64 and ptr
    

    