# Function, Return-Value, and Parameter Attributes

Target: x86_64, Linux and freestanding, compiled (maybe JIT), no C++-style exceptions, no inline assembly, C-style / custom calling conventions as declared per-function.

---

## Grammar

```
fn #[func_attrs...] $name(
    let T1:%arg1 #[param_attrs...],
    let T2:%arg2 #[param_attrs...],
    ...
) -> T_ret #[ret_attrs...] ! "file":line:col 
```

Rules:

- `fn #[func_attrs...] $name(...)` - function attributes sit right after `fn`, before the name.
- `let T:%arg #[param_attrs...]` - each parameter is declared with `let`, and its attributes trail after the binding.
- `-> T_ret #[ret_attrs...]` - return-value attributes trail the return type, before the debug-location suffix.
- `! "file":line:col` - debug location; legal on the function header and on any individual instruction.

### Definitions vs Declarations

A function with a body is a **definition**:

```
fn $add(let i32:%a, let i32:%b) -> i32 ! "math.c":10:1 {
    label @entry {
        let i32:%r = .add(i32:%a, i32:%b);
        .ret(i32:%r);
    }
}
```

A function with **no body** is a **declaration**: the header ends in `;` instead of `{...}`.
This is exactly how you spell "the body lives in some other object file / shared library,
here is only the signature and its ABI contract":

```
fn #[linkage(str:"extern_weak")] $optional_hook(let i32:%code) -> i32;

fn $memcpy(let ptr:%dest #[noalias][nonnull], let ptr:%src #[noalias][nonnull], let i64:%n) -> ptr #[returned];
```

The second example is the normal case: a symbol resolved by the linker at link time (a libc
function, a sibling translation unit, a `.a`/`.so` you link against). Its default linkage is
already `"external"`, so nothing needs to be written for the common case:

```
fn $memcpy(let ptr:%dest, let ptr:%src, let i64:%n) -> ptr;
```

All function-level attributes (`#[cc(...)]`, `#[nounwind]`, return attributes, parameter
attributes, and so on) are still meaningful and still checked on a declaration, since they
describe the calling convention and contract the caller must honor even though the compiler
never sees the callee's body.

---

## A Note on `#[naked]`

Classically `#[naked]` exists so a function body can be pure inline assembly with no
compiler-generated prologue/epilogue getting in the way. Since this language has no inline
assembly, that specific motivation does not apply.

The attribute still earns its place here for a different reason. The MIR body is not
restricted to "normal" code; it has `.alloca`, `.stacksave` / `.stackrestore`, `.syscall`,
raw `.ret`, `.fshl` / `.fshr`, and so on. A function can itself be a hand-rolled entry point
(`_start`, a raw `.syscall`-based exit thunk, a custom-calling-convention trampoline for an
interrupt-adjacent stub) without ever touching assembly. In that case the compiler's automatic
frame setup/teardown should still be suppressed so it does not fight with manual stack
management. So `#[naked]` is kept, but its job is "do not emit a prologue/epilogue around my
MIR body," not "let me write assembly."

---

## Function-Level Attributes

`fn #[...] $name(...) -> T ... { }`

### Linkage and Symbol Visibility

- `#[linkage(str:kind)]` - controls how this symbol is resolved and merged across
  translation units at link time. `kind` is one of:

  | value | meaning | constraint |
  |---|---|---|
  | `"external"` | Default. Ordinary globally-visible symbol. Exactly one definition must exist across the whole link; a declaration with this linkage must be satisfied by exactly one external definition elsewhere. | none |
  | `"internal"` | Symbol is local to this module/object file only (like C `static`); invisible to the linker, no name collision possible with other translation units. | must be a **definition**; cannot be a declaration, since nothing outside this module could ever supply the body |
  | `"weak"` | Globally visible, but if multiple definitions with this name exist across the link, the linker silently picks one instead of erroring on duplicate-symbol. | must be a definition |
  | `"weak_odr"` | Same as `"weak"`, but additionally asserts (One Definition Rule) that every duplicate the linker might discard is byte-for-byte semantically identical, which permits the optimizer to treat calls to it as if it were non-weak (inline it, etc.) | must be a definition |
  | `"linkonce"` | Like `"weak"`, but signals intent rather than accident: this definition is one of potentially many identical copies emitted per-translation-unit (e.g. a generic/template instantiation), and the linker should keep only one copy, discarding the rest entirely rather than merely tolerating duplicates. | must be a definition |
  | `"linkonce_odr"` | `"linkonce"` + the ODR guarantee, same relationship as `"weak_odr"` to `"weak"`. | must be a definition |
  | `"common"` | Tentative definition merging, primarily a data-linkage concept carried over for completeness; multiple `"common"` symbols of the same name coalesce into one, sized as the largest. Rarely meaningful for a function (no notion of "size" beyond code length); included for symmetry with global-variable linkage. | must be a definition |
  | `"appending"` | Multiple definitions with this name are concatenated into a single array-like symbol at link time rather than merged/deduplicated. Meaningful for constructor/destructor table style globals; not typically used for ordinary callable functions. | must be a definition |
  | `"extern_weak"` | A **declaration only**: the symbol may or may not be supplied by any object being linked in. If nothing provides it, the resulting address is null instead of causing a link error. Any code that takes this function's address or calls through it must first check for null. This is how you express "optional callback hook that a linked-in plugin/library may or may not define." | must be a declaration; illegal on a definition |

- `#[visibility(str:kind)]` - restricts symbol visibility *across shared-object boundaries*
  (orthogonal to `linkage`, which governs *within-link* symbol resolution). `kind` is one of:

  | value | meaning |
  |---|---|
  | `"default"` | Default. Symbol is exported from a shared object and can be interposed (overridden) by another object earlier in the load order, per standard ELF symbol resolution. |
  | `"hidden"` | Symbol is not exported from the shared object; only visible within the same linked component. Enables the compiler to use direct (non-PLT/GOT-indirected) calls/references, since no other DSO can ever override it. |
  | `"protected"` | Exported (visible to other DSOs for lookup) but not interposable: this DSO's own references to it always bind to its own definition rather than being subject to override by another loaded object. |

- `#[comdat(str:group_name)]` - places the function in an ELF section group named
  `group_name`. If multiple translation units emit a function under the same COMDAT group
  name, the linker keeps exactly one and discards the rest. This is the low-level mechanism
  `"linkonce"` / `"linkonce_odr"` linkage is typically lowered to; exposed directly here for
  cases needing manual control of the group key (e.g. grouping a function with an associated
  data symbol so they are kept or discarded together).
- `#[section(str:name)]` - places the function's code in the named ELF section instead of the
  default `.text`. `name` is an arbitrary section name string, e.g. `".text.hot"`,
  `".init.text"` (freestanding init code that must run before normal `.text` is mapped),
  `".text.unlikely"`.
- `#[align(i64:N)]` - alignment of the function's entry address in bytes. Must be a power of 2.
- `#[used]` - prevents the compiler from discarding the symbol even if nothing in this module
  references it (e.g. a function only ever called from a hand-written linker script or found
  by address via a symbol table walk).
- `#[retain]` - like `#[used]`, but additionally asks the *linker* not to garbage-collect the
  containing section under `--gc-sections`-style builds. `#[used]` alone only stops the
  compiler's own dead-code elimination; `#[retain]` is needed if the final link step also
  strips unreferenced sections.

### Calling Convention and ABI

- `#[cc(str:convention)]` - selects the register/stack contract used to pass arguments,
  return values, and which registers are caller-saved vs callee-saved. `convention` is one of:

  | value | meaning | constraint it imposes |
  |---|---|---|
  | `"ccc"` | Default. Standard SysV x86_64 C ABI: integer/pointer args in `rdi, rsi, rdx, rcx, r8, r9` then stack; float args in `xmm0..xmm7` then stack; `rax`/`rdx` (int) or `xmm0`/`xmm1` (float) for return; `rbx, rbp, r12-r15` callee-saved, rest caller-saved. | interoperable with any external C symbol, including libc |
  | `"fastcc"` | Compiler is free to choose a non-standard, possibly per-call-site-optimized register assignment (e.g. pass more arguments in registers than the C ABI allows, reorder which registers are used) to minimize spills. | both caller and callee must be compiled by this toolchain in the same module/link; cannot be used to call an externally-defined (e.g. libc) symbol, since the register assignment is not a fixed, portable contract |
  | `"coldcc"` | Optimized for code-size and correctness on a rarely-taken path rather than call-speed; the compiler may use a register assignment that minimizes prologue/epilogue overhead at the call site at the expense of the callee's own performance. Intended for error-handling/slow-path helper functions. | same as `fastcc`: internal-only, not ABI-stable across compilers |
  | `"tailcc"` | Guarantees every call to this function is eligible to be compiled as a proper tail call (constant stack usage even under deep/unbounded self- or mutual recursion), by fixing a calling convention that makes tail-call lowering always legal regardless of argument count/type. | callee and all its call sites must agree on `"tailcc"`; recommended to pair call sites with `#[musttail]` (see the call instruction's tail-call attributes) so tail-call elimination failure is a compile error rather than a silent stack-growth regression |

- `#[interrupt(str:kind)]` - freestanding only. Marks the function as an x86 interrupt/exception
  handler: the compiler generates the interrupt-frame-aware prologue/epilogue (saving all
  clobbered registers, respecting the CPU-pushed frame layout) and terminates with `IRET`
  instead of a normal `RET`. `kind` is one of:

  | value | meaning |
  |---|---|
  | `"none"` | The corresponding hardware exception/interrupt does **not** push an error code (e.g. `#DE`, `#NMI`, most IRQs). The handler's implicit frame parameter layout omits the error-code slot. |
  | `"error_code"` | The corresponding hardware exception pushes a 64-bit error code before the interrupt frame (e.g. `#PF`, `#GP`, `#TS`, `#SS`). The handler's implicit frame parameter layout includes it. |

  Mutually exclusive with `#[cc(...)]`: the interrupt frame layout is fixed by the CPU, not by
  a chosen software convention.

- `#[naked]` - suppress prologue/epilogue generation; body owns the stack entirely (see the
  dedicated note above).
- `#[nonlazybind]` - calls to this function bypass PLT lazy-binding indirection and load the
  address directly from the GOT instead. Saves a jump on the first (and, depending on
  linker behavior, every) call, at the cost of forcing eager symbol resolution at load time.
  Relevant for hot cross-DSO calls where PLT trampoline overhead is measurable.

### Unwinding / Stack Walking

- `#[nounwind]` - asserts this function never needs to be unwound past by any stack-walking
  consumer (there are no C++-style exceptions in this language, so this is not about
  exception propagation; it is about signal handlers, profilers, and debuggers that walk the
  stack using CFI/unwind tables). Setting it lets the backend omit `.eh_frame`-equivalent
  metadata for this function, shrinking the binary. Violating the assertion, i.e. a stack
  walker actually needing to cross this frame without CFI, produces undefined behavior for
  that walk (it may simply get a corrupted/truncated backtrace).

### Optimization / Codegen Hints

- `#[inline(str:mode)]` - `mode` is one of:

  | value | meaning |
  |---|---|
  | `"always"` | Compiler must inline every call to this function, if at all structurally possible (no indirect calls to it, no recursion through it that would require an infinite expansion). Failure to inline is a compile error rather than a silent fallback. |
  | `"never"` | Compiler must never inline this function under any circumstance, even at the highest optimization level. Useful for keeping a function as a stable symbol for profiling/debugging or to bound code-size growth. |
  | `"hint"` | Default. Soft suggestion in the direction of inlining (roughly, "the author expected this to be small/hot"); the compiler's cost-model heuristics still make the final call. |

- `#[optnone]` - disable optimization for this function entirely, regardless of the module's
  optimization level. Incompatible with `#[inline(str:"always")]`, since an unoptimized
  function cannot also be a mandatory inline candidate.
- `#[optsize]` / `#[minsize]` - bias the optimizer toward smaller code over faster code for
  this function; `#[minsize]` is a stronger version that also forgoes optimizations that are
  size-neutral or slightly size-costly even when they would meaningfully help speed.
- `#[cold]` / `#[hot]` - sets the *default* branch/layout/inlining-priority assumption used
  for every call site of this function that does not locally override it with the call-site
  `#[cold]` / `#[hot]` attribute described under the call instruction.
- `#[noreturn]` - asserts the function never returns control to its caller (it always ends in
  `.trap`, an infinite loop, a `#[noreturn]` `.syscall`, or a call to another `#[noreturn]`
  function). A `.ret` with no value is then legal at the IR level even for a non-void return
  type, since it is understood to be unreachable in practice.
- `#[nosideeffect]` / `#[pure]` - `#[nosideeffect]` asserts the function has no observable
  effect on program state other than through its return value (the optimizer may remove a
  call whose result is unused); `#[pure]` asserts additionally that the return value is a
  deterministic function of the arguments alone (the optimizer may also common-subexpression-
  eliminate repeated calls with identical arguments). Both are the *default* for every call
  site of this function, overridable per call site by the call instruction's own attributes.
- `#[returns_twice]` - the function may transfer control back to the same call site more than
  once for a single call (a `setjmp`-style checkpoint built out of raw register/stack
  capture rather than a language-level exception). Disables call-site optimizations that
  assume a call executes and returns exactly once, such as certain forms of code motion
  across the call.

### Stack and Hardening

- `#[stackprotector(str:level)]` - controls insertion of a stack-canary check in the
  prologue/epilogue. `level` is one of:

  | value | meaning |
  |---|---|
  | `"none"` | Default. No canary. |
  | `"basic"` | Canary inserted only in functions the compiler judges vulnerable by its usual heuristic (e.g. contains a fixed-size local array/buffer that could plausibly be overrun). |
  | `"strong"` | Canary inserted in a broader set of functions using a more aggressive heuristic (any local whose address is taken, any array regardless of size, etc.), trading some codegen overhead for materially better coverage. |
  | `"req"` | Canary inserted unconditionally, regardless of whether the compiler's heuristic thinks it is warranted. |

- `#[noredzone]` - disables the 128-byte SysV "red zone" below `rsp` that leaf functions may
  otherwise use as scratch space without adjusting the stack pointer. Required for any
  function that can be asynchronously re-entered on the same stack while it is using the red
  zone, i.e. signal handlers and interrupt handlers, since the interrupting context's own use
  of the region would otherwise corrupt the interrupted function's temporaries.
- `#[stackalign(i64:N)]` - the required incoming and outgoing stack pointer alignment in
  bytes for this function, if it must be stricter than the SysV ABI default of 16. Must be a
  power of 2, and should be `>= 16`.
- `#[framepointer(str:mode)]` - controls whether `rbp` is maintained as a conventional frame
  pointer. `mode` is one of:

  | value | meaning |
  |---|---|
  | `"none"` | `rbp` is treated as a general-purpose register free for allocation; no frame-pointer chain is maintained. Smallest/fastest, but breaks frame-pointer-based stack walkers. |
  | `"non-leaf"` | Functions that themselves call other functions maintain the `rbp` chain; leaf functions (that make no calls) may still use `rbp` as a general register. |
  | `"all"` | Every function, leaf or not, maintains the `rbp` chain. Required for tools that walk the stack purely via frame pointers rather than CFI (some sampling profilers). |

- `#[safestack]` - places this function's locals whose address is taken (and are therefore
  vulnerable to being corrupted through an unrelated buffer overflow) on a separate,
  segregated "safe stack," leaving the ordinary stack for values that are never referenced by
  pointer.
- `#[speculative_load_hardening]` - applies Spectre variant 1 (bounds-check-bypass) load
  hardening to every load in this function's body, at a measurable performance cost.
- `#[retpoline]` - lowers every indirect call and indirect branch within this function through
  a retpoline sequence, mitigating Spectre variant 2 (branch-target-injection) at the cost of
  extra instructions per indirect transfer.
- `#[cet_ss]` - this function participates in Intel CET shadow-stack enforcement: every
  `.ret` is checked against the hardware shadow stack, and an `ENDBR64` is emitted at every
  legal indirect-call entry point into this function.
- `#[nocf_check]` - suppresses `ENDBR64` insertion at this function's entry, for a function
  that is only ever reached by direct call/jump and is therefore not a valid indirect-branch
  target under CET-IBT.

### Target / Machine

- `#[target_cpu(str:name)]` - tunes instruction scheduling/selection for a specific
  microarchitecture without necessarily changing which ISA extensions are assumed available
  (that is `#[target_features]`'s job). `name` is one of:

  `"x86-64"`, `"x86-64-v2"`, `"x86-64-v3"`, `"x86-64-v4"` (the generic microarchitecture
  levels), or a specific microarchitecture: `"nehalem"`, `"westmere"`, `"sandybridge"`,
  `"ivybridge"`, `"haswell"`, `"broadwell"`, `"skylake"`, `"skylake-avx512"`,
  `"cascadelake"`, `"icelake-client"`, `"icelake-server"`, `"tigerlake"`, `"alderlake"`,
  `"sapphirerapids"`, `"znver1"`, `"znver2"`, `"znver3"`, `"znver4"`.

  Code compiled for a given `target_cpu` is not guaranteed to run correctly (may `SIGILL`) on
  an older CPU than the one named; it is a codegen target, not a portability guarantee.

- `#[target_features(str:feature...)]` - vararg (one `str:` argument per feature, not a single
  comma-packed string), enables or disables individual ISA extensions for this function only,
  independent of the module-wide default (function multiversioning). Each entry is prefixed
  `+` to enable or `-` to explicitly disable a feature that the `target_cpu` would otherwise
  imply. Example:

  ```
  #[target_features(str:"+avx2", str:"+fma", str:"-avx512f")]
  ```

  Recognized feature names: `sse`, `sse2`, `sse3`, `ssse3`, `sse4.1`, `sse4.2`, `avx`,
  `avx2`, `avx512f`, `avx512bw`, `avx512dq`, `avx512vl`, `avx512cd`, `fma`, `bmi`, `bmi2`,
  `popcnt`, `lzcnt`, `aes`, `pclmul`, `sha`, `adx`, `rdrnd`, `rdseed`, `cx16`, `movbe`,
  `f16c`, `clflushopt`, `clwb`, `prefetchwt1`, `rtm`, `xsave`, `xsaveopt`, `fsgsbase`,
  `cet_ibt`, `cet_ss`.

  Using an instruction from this spec's SIMD/crypto sections whose backing feature is not
  enabled for the calling function is a compile error (e.g. emitting `.aesenc` without
  `+aes` enabled somewhere in scope).

### Sanitizers

- `#[sanitize(str:tool...)]` - vararg, one `str:` argument per tool, instruments this
  function's body for the named runtime checker(s). `tool` is one of:

  | value | meaning |
  |---|---|
  | `"address"` | AddressSanitizer: detects out-of-bounds accesses, use-after-free, and double-free via redzones and quarantine, at significant memory/CPU overhead. |
  | `"thread"` | ThreadSanitizer: detects data races between concurrent accesses to shared memory (relevant given the atomic/non-atomic memory and fetch-modify instructions in this spec). |
  | `"memory"` | MemorySanitizer: detects reads of uninitialized memory. |
  | `"undefined"` | UndefinedBehaviorSanitizer: inserts runtime checks for UB conditions this spec defines as poison/UB-producing (signed overflow with `#[nsw]`, misaligned access under an asserted `#[align]`, etc.), trapping instead of silently miscompiling. |
  | `"leak"` | LeakSanitizer: detects heap allocations that become unreachable without being freed. |

  Example: `#[sanitize(str:"address", str:"undefined")]`.

- `#[no_sanitize(str:tool...)]` - same vararg form and same `tool` values; explicitly opts
  this function out of a sanitizer that is otherwise enabled module-wide (e.g. a
  hand-tuned bit-twiddling routine that trips UBSan's overflow checks intentionally and
  correctly).

### Allocator Semantics

- `#[allockind(str:kind)]` - describes this function's role in an allocation family so the
  optimizer can reason about pointers it hands back or takes in, similarly to how it reasons
  about a built-in `malloc`/`free` even though this language has no built-ins of its own.
  `kind` is one of:

  | value | meaning |
  |---|---|
  | `"alloc"` | Returns a freshly allocated, uninitialized (or unspecified-content) block; never returns a pointer aliasing anything else already reachable. |
  | `"realloc"` | Takes an existing allocation (typically the first pointer parameter) and returns a block with the same contents (up to the smaller of the two sizes), possibly at a new address; the input pointer must not be used again after the call unless it is confirmed to equal the returned pointer. |
  | `"free"` | Takes an existing allocation and deallocates it; the pointer must not be dereferenced after the call. |
  | `"aligned_alloc"` | Like `"alloc"`, but additionally guarantees the returned pointer satisfies an alignment given by another parameter, see `#[allocalign]`. |

- `#[allocsize(i64:size_arg_idx [, i64:num_arg_idx])]` - identifies which parameter(s)
  determine the size, in bytes, of the block an `"alloc"`/`"aligned_alloc"`-kind function
  returns. `size_arg_idx` is the zero-based index of the parameter holding the element size
  (or total size, if `num_arg_idx` is omitted); `num_arg_idx`, if given, is the index of a
  parameter holding an element count, and the true size is their product. Lets the optimizer
  fold a subsequent `.memset` over the returned pointer, know the buffer's bound for
  `#[dereferenceable]` purposes, etc.
- `#[allocalign(i64:align_arg_idx)]` - identifies which parameter specifies the alignment, in
  bytes, that the returned pointer is guaranteed to satisfy. Only meaningful alongside
  `#[allockind(str:"aligned_alloc")]`.
- `#[nofree]` - also valid as a parameter attribute (see below); at the function level it
  asserts this function frees no pointer reachable from *any* of its arguments, anywhere in
  its body or in anything it calls.

### Debug (function level)

- `#[nodebug]` - exclude this function from debug-info generation entirely; no line table,
  no scope tree, no variable bindings are emitted for it.
- `#[artificial]` - marks the function as compiler-synthesized rather than user-written; a
  debugger stepping through source should step over it rather than into it.
- `#[dbg_name(str:display_name)]` - the source-level display name to show in a
  debugger/backtrace when it differs from the mangled `$name` (e.g. the demangled form of a
  generic/template instantiation).
- `#[dbg_scope(i64:child_id, i64:parent_id)]` - declares one edge of the function's lexical
  scope tree up front, associating nested scope `child_id` with enclosing scope `parent_id`,
  so that per-block `#[dbg_scope(i64:scope_id)]` tags (see below) resolve shadowed/short-lived
  locals to the correct nesting level.

---

## Return-Value Attributes

`-> T_ret #[...] ! "file":line:col`

- `#[noalias]` - returned pointer aliases nothing else visible to the caller.
- `#[nonnull]` - returned pointer is never null.
- `#[dereferenceable(i64:N)]` - valid for at least `N` bytes.
- `#[dereferenceable_or_null(i64:N)]` - as above, or null.
- `#[nopoison]` - never poison.
- `#[align(i64:N)]` - minimum pointer alignment guarantee.
- `#[return_extension(str:kind)]` - describes how a return value narrower than a full
  register is placed within the return register, so callers reading only the narrow width
  know whether the unused high bits are meaningful. `kind` is one of:

  | value | meaning |
  |---|---|
  | `"zero"` | High bits above the logical return width are zero-extended. |
  | `"sign"` | High bits above the logical return width are sign-extended. |
  | `"no"` | Default. High bits above the logical return width are unspecified; the caller must not read past the declared return width. |

  Must agree with the matching `#[return_extension(...)]` given at every call site of this
  function (mismatched extension assumptions between caller and callee is undefined behavior).

- If `T_ret` is float/bfloat/vector-of-float: `#[fast]`, `#[nnan]`, `#[ninf]`, `#[nsz]`,
  `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

---

## Parameter Attributes

`let T:%name #[...]`

### Aliasing / Pointer Semantics

- `#[noalias]` - does not alias any other pointer reachable by the function.
- `#[nocapture]` - no copy of this pointer outlives the call.
- `#[nonnull]` - never null.
- `#[nofree]` - function will not free memory reachable through this pointer.
- `#[readonly]` - function only reads through this pointer.
- `#[writeonly]` - function only writes through this pointer.
- `#[readnone]` - function neither reads nor writes through this pointer.
- `#[writable]` - pointee is mutable and speculatively writable if otherwise legal.
- `#[returned]` - this exact value is what the function returns.
- `#[align(i64:N)]` - guaranteed alignment at every call site.
- `#[dereferenceable(i64:N)]` - valid for `N` bytes on entry.
- `#[dereferenceable_or_null(i64:N)]` - as above, or null.

### Aggregate Passing

- `#[byval(type:T)]` - the pointer parameter is semantically passed by value: the callee
  receives a private copy of the aggregate `T` at this address, lowered per the platform's
  aggregate-passing rules (classified into registers or spilled to the stack per the SysV
  ABI's aggregate classification algorithm, as appropriate for `T`'s size/layout).
- `#[byref(type:T)]` - like `byval`, but no copy is implied; the caller retains ownership of
  the aggregate and the pointer is purely an ABI-lowering hint for how a large `T` is passed
  in memory rather than in registers.
- `#[inalloca(type:T)]` - the argument is materialized directly into caller-allocated
  outgoing-argument stack space ahead of the call sequence. Windows-ABI-style aggregate
  passing, retained for completeness.
- `#[preallocated(type:T)]` - like `byval`, but the storage for the aggregate is allocated by
  the caller before the full call sequence begins, allowing the callee to construct the
  aggregate in place rather than the caller building it and then copying.
- `#[sret(type:T)]` - the pointer parameter is the hidden destination for the function's
  logical (large aggregate) return value. Must be the first parameter if present; the
  function's declared `T_ret` must be `void` at the IR level, with the true return type being
  `T` written through this pointer.

### Scalar / Integer Extension

- `#[zeroext]` - a narrower-than-register integer argument is zero-extended by the caller
  before being placed in its argument register/stack slot.
- `#[signext]` - a narrower-than-register integer argument is sign-extended by the caller
  before being placed in its argument register/stack slot.

### Miscellaneous

- `#[nopoison]` - the incoming value is guaranteed not to be poison.
- `#[artificial]` - compiler-synthesized parameter (e.g. an injected `sret` pointer), hidden
  from a debugger's displayed argument list.
- If the parameter type is float/bfloat/vector-of-float: `#[fast]`, `#[nnan]`, `#[ninf]`,
  `#[nsz]`, `#[arcp]`, `#[contract]`, `#[afn]`, `#[reassoc]`, or any combination.

---
