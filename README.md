# LIRA :- Legible Intermediate Representation Assembly

My attempt at making an IR that's more legible than LLVM IR, but still low-level enough to be a good target for code generation. The syntax is inspired by LLVM IR, but with some twists to make it more readable and writable by humans. Atleast that is the goal. Lets see how it goes. 
I also made it to be easier to parse

# Goal

My goal is to make an IR that is more legible than LLVM IR, focus on only linux x86_64(and at max arm) as code generation. Make the syntax and everything unchanged as much as possible. I also want to make it easier to parse and generate code for.

# Why?

No partiqular reason. I want it to be my own personal IR that I can use for my own projects. 

# Reason behind the name

Well there is the full form but also thought it was a cute name so.... I think it will go well with my other project "Luna" which is a programming language and I plan to use LIRA as the IR for Luna.



# Code example

Note:This is the rough syntax but things are changing fast so even if the syntax is same, the instructions and semantics might be different. I will update the code example as the syntax and semantics stabilizes.

```llvm
#[module(triple=str:"x86_64-unknown-linux-gnu")];
#[module(source=str:"demo.c")];

let str:$fmt #[linkage(str:"private")] #[const] = .assign_value(str:"result = %d\n\0");

fn #[extern] $malloc(let i64:%size) -> ptr;
fn #[extern] $free(let ptr:%ptr) -> void;
fn #[extern] $printf(let ptr #[nonull]:%fmt, ...) -> i32;

fn #[nounwind] $main() -> i32 ! "demo.c":10:1 {
    label @entry {
        let ptr:%slot = .call(fn(i64)->str:$malloc, i64:4) ! "demo.c":11:5;
        let i1:%is_null = .i_eq(ptr:%slot, ptr:null);
        .br(i1:%is_null, label:@fail, label:@ok);
    }
    label @fail {
        .ret(i32:-1);
    }
    label @ok {
        .store(i32:21, ptr:%slot) #[align(i8:4)];
        let i32:%v = .load(ptr:%slot) #[align(i8:4)];
        let i32:%r = .add(ptr:%v, i32:%v) #[nsw];
        .call(fn(ptr, i32)->i32:$printf, ptr:$fmt, i32:%r) ! "demo.c":21:5;
        .call(fn(ptr)->void:$free, ptr:%slot);
        .ret(i32:0);
    }
}
```


# Current progress
 - [x] Error lib
 - [x] Test error lib
 - [x] Lexer
 - [x] Test Lexer
 - [x] Ast
 - [x] Parser
 - [x] Test Parser
 - [ ] MIR classes for all instructions
 - [ ] Semantic analysis
 - [ ] Test Semantic analysis
 - [ ] Expand this list when I start working on codegen and optimizations

# Compiling and running

```sh
git clone https://github.com/SaptakBhoumik/LIRA.git
cd LIRA
meson builddir
cd builddir
ninja
./LIRA.elf <path_to_lira_file>
```
 
After running ``./LIRA.elf <path_to_lira_file>`` it will print out the LIRA file reconstruted from the ast and also the token stream. Yes the compiler is not mature enough to do anything useful yet

# Contributing note

Note:-Not accepting contributions at the moment. I will be accepting contributions in the future when the project is more stable and has more features. For now, I only made it public to keep myself accountable 


# Contact 

- 💌 Reach me at: `saptakbhoumik.acad@gmail.com`
- 📢 Follow me on [X](https://x.com/saptakbhoumik)