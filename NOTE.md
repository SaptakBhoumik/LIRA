- Alignment is set to be 0 by default if aligment is not specified
- i1 is not supported by any instruction. It is only used for control flow and comparisons. In struct it is i8 basically. Same in array. Keep it in mind when u do pointer arithmetic on i1. For SIMD it depends. Can be a literal mask if supported by the instruction, otherwise it is i32(Or something like that)
- ptr:123 is valid syntax. It simply means a pointer whose address is 123. More generally, writing ptr: followed by a constant expression treats that integer constant as a pointer value.
- In many places in the instruction.md docs, I mention compile-time/run-time variants. The reason is that x86_64 has dedicated instructions for compile-time constants, but we can also generate equivalent behavior at run-time using loops, if-else logic, etc. That is why both variants are allowed.
In MIR, instructions like these must have two variants: one for compile-time and one for run-time. These variants exist because certain x86_64 instructions can only be used with compile-time constants; for run-time, we must generate code using more general instructions or conditional logic to achieve the same effect.
Note that not all instructions have this distinction. Some instructions share the same underlying x86_64 instruction for both compile-time and run-time. For these, we can apply constant folding at compile-time, but there is no separate x86_64 instruction dedicated to the compile-time case.
- Function type literals are only permitted in call instructions, where they specify the signature of the function being invoked. Function pointers are stored as opaque pointers (ptr), which can be implicitly converted to and from any function pointer type. This means ptr can hold a function pointer without carrying type information - the type is only required at the call site.

```
; Pseudo code example of function type literals and opaque pointers
; --- Declaration ---
func add(a: i32, b: i32) -> i32 { ... }
func sub(a: i32, b: i32) -> i32 { ... }

; --- Storing function pointers as opaque ptr ---
let fp: ptr = add        ; implicit conversion: fn(i32, i32) -> i32  →  ptr
let fp2: ptr = sub       ; same, different function

; --- Passing around as opaque ptr (no type info needed) ---
let alias: ptr = fp      ; just a pointer, no signature attached

; --- Call: function type MUST be specified here ---
let result = call fn(i32, i32) -> i32 : alias (1, 2)    ; valid
let result = call fn(i32, i32) -> i32 : fp2  (10, 3)    ; valid
let result = call fn(i32, i32) -> i32 : sub  (10, 3)    ; valid
let result = call fn(i32, i32) -> i32 : add  (10, 3)    ; valid

; --- This would be INVALID (no type literal outside call) ---
let typed: fn(i32, i32) -> i32 = add    ;  not allowed as a variable type
```