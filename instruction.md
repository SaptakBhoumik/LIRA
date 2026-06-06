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

## Memory instructions 

- ``let ptr:$global_var = .global(T:value)`` :- Defines a global variable. The type of the output variable must be a pointer type. The value can be any constantexpr literal(Not a variable). $global_var contains address of the global variable such that *$global_var is the value of the global variable. Innitialized by the value specified in the instruction. This instruction is not part of MIR. Stored in the global variable section of the module.

- ``let T:%local_var = .local(T:initial_value)`` :- Defines a local variable. The value can be anything. In llvm u can do ``%local_var = initial_value`` but here you need this to keep the parser simpler(Actually the innitial design plan was diffrent but that changed but we still have some leftover from the innitial). This instruction is a part of MIR although doesnt do much. It is just a way to define a local variable and innitialize it with some value. T can be any type

- ``let ptr:%local_var = .alloca(iN:%size)`` :- Allocates memory on the stack. The size is in bytes. It has the attribute ``#[align(i8:N)]`` to specify the alignment of the allocated memory and by default it is 16. The alignment must be a power of 2 and it is in bytes. By default the alignment is 1 byte.

- ``let T:%output_var = .load(ptr:%ptr)`` :- Loads a value from memory of type T. It has the attribute ``#[align(i8:N)]`` to specify the alignment of the load and by default it is 16. The alignment must be a power of 2 and it is in bytes. By default the alignment is 16 byte. It also has the attribute ``#[volatile]`` to indicate that the load is volatile. It has the attribute ``#[invarient.load]`` to indicate that the value loaded is invariant and it will not change during the execution of the program. It has the attribute ``#[nontemporal]`` to indicate that the load is non temporal. It also has the attribute ``#[nonull]`` and ``#[nopoison]``. It has the attribute ``#[dereferenceable(i64:N)]`` to indicate that the pointer is dereferenceable for N bytes. It also has the attribute ``#[atomic(str:ordering)]`` to indicate that the load is atomic with the specified ordering. The ordering can be one of the following: ``acquire``, ``monotonic``, ``unordered`` and ``seq_cst``. If the attribute is not present then it is not an atomic load. If atomic it can also have the attribute ``#[syncscope("singlethreaded")]`` to indicate that the atomic load is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. Note:-If atomic then we require an explicit alignment

- ``.store(T:%value, ptr:%ptr)`` :- Stores a value to memory. It has the attribute ``#[align(i8:N)]`` to specify the alignment of the store and by default it is 16. The alignment must be a power of 2 and it is in bytes. By default the alignment is 16 byte. It also has the attribute ``#[volatile]`` to indicate that the store is volatile. It has the attribute ``#[nontemporal]`` to indicate that the store is non temporal. It also has the attribute ``#[nonull]`` and ``#[nopoison]``. It has the attribute ``#dereferenceable(i64:N)`` to indicate that the pointer is dereferenceable for N bytes. It also has the attribute ``#[atomic(str:ordering)]`` to indicate that the load is atomic with the specified ordering. The ordering can be one of the following: ``acquire``, ``monotonic``, ``unordered`` and ``seq_cst``. If the attribute is not present then it is not an atomic load. If atomic it can also have the attribute ``#[syncscope("singlethreaded")]`` to indicate that the atomic load is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. Note:-If atomic then we require an explicit alignment

- ``let ptr:%output_var = .getaddress(T:%var, i64:%offset)`` :- Gets &var + offset. The type of output variable must be a pointer type. The type of var can be any type. The offset is in bytes. Note:-var is a variable and not a literal/expression. It has the attribute ``#[unsigned]`` to indicate that the offset is unsigned. By default it is signed. It also has ``#[nsw]`` or ``#[nuw]`` or both to indicate that the offset does not cause signed or unsigned overflow. Also has the attribute ``#[inbounds]`` . We dont have blockaddress instruction like llvm. Just use this 

- ``let ptr:%output_var = .ptr_offset(ptr:%input_var, T:%offset)`` :- Gets input_var + offset. The type of output variable must be a pointer type. The input variable must be a pointer type. The offset can be any integer type. The offset is in bytes. It has the attribute ``#[unsigned]`` to indicate that the offset is unsigned. By default it is signed. It also has ``#[nsw]`` or ``#[nuw]`` or both to indicate that the offset does not cause signed or unsigned overflow.  Also has the attribute ``#[inbounds]`` 

- `` let T3:%output_var = .extractelement(T1:%input, T2:%index)`` :- Extracts an element from a vector/array/struct. ``T1`` is a vector/array/struct. The index type ``T2`` must be some integer of type ``iN``. ``T3`` is the type of the extracted element. For struct, the index must be a integer literal. But for array and vector it can be literal or variable. It can have the attribute ``#[inbounds]`` for array and vector but not for struct cuz struct index is always in bounds.

- `` let T1:%output_var = .insertelement(T1:%input, T2:%element, T3:%index)`` :- Inserts an element into a vector/array/struct. ``T1`` is a vector/array/struct. The index type ``T3`` must be some integer of type ``iN``. The element type ``T2`` must be of the same type as the element of the vector/array/struct at that index. For struct, the index must be a integer literal. But for array and vector it can be literal or variable. It can have the attribute ``#[inbounds]`` for array and vector but not for struct cuz struct index is always in bounds. The output is the same type as the input vector/array/struct and is the same as the input except the element at the index is replaced by the new element.

- ``.fence(str:ordering)`` :- Fence instruction. Both ordering and syncscope must be constexpr. Valid values for ordering are ``acquire``, ``release``, ``acq_rel`` and ``seq_cst``. It also has the attribute ``#[syncscope("singlethreaded")]`` to indicate that the fence is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. Note:-A fence instruction does not have any output variable and it does not have any input variable. It just acts as a memory barrier to ensure ordering of memory operations.

- ``let {T,i1}:%output_var = .cmpxchg(ptr:%ptr, T:%expected, T:%desired, str:success_ordering,str:failure_ordering)`` :- Compare and exchange instruction. It atomically compares the value at the memory location pointed to by ptr with the expected value. If they are equal then it atomically replaces the value at the memory location with the desired value and returns the original value and true. If they are not equal then it does not modify the memory location and returns the original value and false. The type of output variable is a struct of form {T, i1} where T is the type of the value at the memory location and i1 is a boolean indicating whether the exchange was successful or not. It has the compulsory attribute ``#[align(i8:N)]`` to specify the alignment of the operation and by default it is 16. The alignment must be a power of 2 and it is in bytes. It also has the attribute ``#[volatile]`` and ``#[weak]`` to indicate that the operation is volatile or weak.It can also have the attribute ``#[syncscope("singlethreaded")]`` to indicate that the atomic operation is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. ``success_ordering`` and ``failure_ordering`` must be const expr and ``success_ordering`` must be one of the following: monotonic, acquire, release, acq_rel, seq_cst but ``failure_ordering`` can only be one of the following: monotonic, acquire, seq_cst and it must not be release or acq_rel. 

## Atomic Read-Modify-Write instructions

The following are atomic Read-Modify-Write. Atomically reads a value from memory, applies a binary operation with a given operand, and writes the result back. Returns the original value. All of them have the attribute ``#[align(i8:N)]`` to specify the alignment of the operation and by default it is 16. The alignment must be a power of 2 and it is in bytes. They also have the attribute ``#[volatile]`` to indicate that the operation is volatile. They can also have the attribute ``#[syncscope("singlethreaded")]`` to indicate that the atomic operation is only synchronized with other atomic operations in the same thread. By default it is synchronized with atomic operations in all threads i.e "global". We supporting only x86_64 so only these 2 we can have. It supports the following ordering monotonic, acquire, release, acq_rel, seq_cst

- ``let T:%old = .atomic_xchg(ptr:%ptr, T:%value)`` :- Atomically replaces the value at the memory location pointed to by ptr with the given value and returns the original value. T can be integer or float

- ``let T:%old = .atomic_fetchadd(ptr:%ptr, T:%value)`` :- Atomically adds the given value to the value at the memory location pointed to by ptr and returns the original value. T can be integer or float

- ``let T:%old = .atomic_fetchsub(ptr:%ptr, T:%value)`` :- Atomically subtracts the given value from the value at the memory location pointed to by ptr and returns the original value. T can be integer or float

- ``let T:%old = .atomic_fetchand(ptr:%ptr, T:%value)`` :- Atomically performs a bitwise and operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .atomic_fetchnand(ptr:%ptr, T:%value)`` :- Atomically performs a bitwise nand operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .atomic_fetchor(ptr:%ptr, T:%value)`` :- Atomically performs a bitwise or operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .atomic_fetchxor(ptr:%ptr, T:%value)`` :- Atomically performs a bitwise xor operation between the given value and the value at the memory location pointed to by ptr and returns the original value. T must be an integer type.

- ``let T:%old = .atomic_fetchmax(ptr:%ptr, T:%value)`` :- Atomically compares the given value with the value at the memory location pointed to by ptr and replaces the value at the memory location with the maximum of the two values. Returns the original value. T can be integer or float. For integer it can be signed or unsigned based on the presence of ``#[unsigned]`` attribute. By default it is signed

- ``let T:%old = .atomic_fetchmin(ptr:%ptr, T:%value)`` :- Atomically compares the given value with the value at the memory location pointed to by ptr and replaces the value at the memory location with the minimum of the two values. Returns the original value. T can be integer or float. For integer it can be signed or unsigned based on the presence of ``#[unsigned]`` attribute. By default it is signed

- ``let T:%old = .atomic_uinc_wrap(ptr:%ptr, T:%value)`` :- Returns ``(*ptr >= value) ? 0 : *ptr + 1``. T must be integer

- ``let T:%old = .atomic_idec_wrap(ptr:%ptr, T:%value)`` :- Returns ``(*ptr <= value) ? 0 : *ptr - 1``. T must be integer


## Terminator instructions 

A terminator statement must be present at the end of a instruction. If no terminator then error. We dont go from one block to next without a .br or similar instruction

- ``.ret`` or ``.ret(T:%return_value)`` :- Return from a function. If the function return type is void then use ``.ret`` with no return value. If the function return type is not void then. It has the attribute ``#[noreturn]`` to indicate that the function does not return. In that case you can also use ``.ret`` with no return value even if the function return type is not void. But if you have a return value then it must be of the same type as the function return type.

- ``.unreachable`` :- Indicates that the code is unreachable. Maybe when u call exit() u can used ``.unreachable`` after the call. Used when you dont jump to a diffrent block but you also dont want to return from the function. 

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

    The above rule also applies to byval, byref, inalloca(<ty>), preallocated(<ty>), sret, zeroext, inreg and signext. Just remember for byval and other similar argument you have ``#[byref(type:T, i64:arg_index0,....)]``. If defination is given then attribute specified at call site must match with defination if defination is available. If not we assume that the function can take any attribute for that argument and we just follow whatever is specified at the call site.

    Unlike llvm, there are a limited number of calling convention  mainly because we only support x86_64. So we have the following calling conventions: ccc, fastcc, coldcc and tailcc. You can specify the calling convention like ``#[cc(str:calling_convention)]`` where calling_convention is one of the calling conventions mentioned before. If not specified then it is the default calling convention which is ccc. 

    ``let T:%output_var #[noalias] = .call(T:%func, T1:%arg1, T2:%arg2...)``
    You can do this if you want to mark the return value as noalias. This is allowed because you cant mark noalias on the function return type. zeroext,signext,noext,inreg,nonnull,dereferenceable(<bytes>),nopoison,align(<alignment>),nnan,ninf can also be applied like this to the returned value. In MIR, the DestinationVar should store these attributes

    Reference :- https://claude.ai/share/47c8d0b7-d632-462a-b757-a8f81499862c

## Other instructions

- ``let T0:%m = .select(T1:%condition, T0:%true_value, T0:%false_value)`` :- If T1 is of type i1 then we select %true_value if condition is true and select %false_value if condition is false. T0 can be any type. If T1 is of type <i1,M> then we select element wise from true_value and false_value based on the condition. So if the first element of condition is true then we select the first element of true_value otherwise we select the first element of false_value and so on for all elements. In this case T0 must be a vector type and the output is also a vector where each element is selected based on the corresponding element in the condition vector.

- ``let T:%output_var = .freeze(T:%input_var)`` :- Freezes the value of input_var. It is used to prevent certain optimizations that can lead to undefined behavior. It can be used when you have some value that is undef or poison and you want to use it in a way that does not cause undefined behavior. By freezing it, you are telling the compiler that the value can be any value of the type and it should not make any assumptions about it. So it can be used to safely use undef or poison values without causing undefined behavior.

- ``let T:%output_var = .va_arg(ptr:%input_var)`` :- Used to access the variable arguments in a function that takes variable arguments. The input_var is of type ptr and T is the type of the variable argument that we want to access

- ``.call(T:%func, T1:%arg1, T2:%arg2...)`` :- Same as above but for functions that return void.

- ``let T:%output_var = .ptrmask(T:%input_var,T1:%mask)`` :- Masks a pointer with a mask. T is a ptr or vector of ptr. Mask is an integer or vector of integer. If T1 is vector then T must also be a vector of same size

- `` let <T, M>:%output_var = .shufflevector(<T, N2>:%input1, <T, N3>:%input2, <i16, M>:%mask)`` :- Shuffles the elements of 2 vectors according to a mask. Mask is compile time not run time

- ``let type:%type_name = .assign_type(type:<type defination>)`` :- USed to create a typedef. Note:-This is not an actual instruction. Just to make the parser simpler. Ignored by MIR