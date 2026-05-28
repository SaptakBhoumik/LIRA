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

```llvm
#[module(triple=*i8:"x86_64-unknown-linux-gnu")];
#[module(source=*i8:"demo.c")];

let *i8:$fmt #[linkage(linkage_type:private)] #[const] = .copy(*i8:"result = %d\n\0");

fn #[extern] $malloc(let i64:%size) -> *i8;
fn #[extern] $free(let *i8:%ptr) -> void;
fn #[extern] $printf(let *i8 #[nonull]:%fmt, ...) -> i32;

fn #[nounwind] $main() -> i32 ! "demo.c":10:1 {
    @entry {
        let *i8:%raw = .call(fn(i64)->*i8:$malloc, i64:4) ! "demo.c":11:5;
        let i1:%is_null = .i_eq(*i8:%raw, *i8:null);
        .br(i1:%is_null, label:@fail, label:@ok);
    }
    @fail {
        .ret(i32:-1);
    }
    @ok {
        let *i32:%slot = .bitcast(*i8:%raw, type:*i32) ! "demo.c":17:5;
        .store(i32:21, *i32:%slot) #[align(i8:4)];
        let i32:%v = .load(*i32:%slot) #[align(i8:4)];
        let i32:%r = .add(i32:%v, i32:%v) #[nsw];
        .call(fn(*i8, i32)->i32:$printf, *i8:$fmt, i32:%r) ! "demo.c":21:5;
        .call(fn(*i8)->void:$free, *i8:%raw);
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