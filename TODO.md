# TODO:

- Introduce the ability to define number as hex or binary in source code. Priority: High
- Consider the following after implementing all the current instruction(Especially the gc and async things): https://claude.ai/share/1e37f189-e4dd-4e8c-a8a2-2b789288658e Priority: Low
- ieee754_2019. Consider it for other float instructions as well. Like does it make sense for eq and stuff. Priority: High

- To pass a value from one label to another, it must be threaded explicitly through label parameters:

Old Method:-

```
label @a() {
    let integer:%v = .load(integer:1);
    .br(label:@b);
}
label @b {
    .print(integer:%v);
    .ret();
}
```

New Method:-

```
label @a() {
    let integer:%v = .load(integer:1);
    .br(label(integer):@b(%v));
}
label @b(let integer:%v) {
    .print(integer:%v);
    .ret();
}
```
Function parameters are the one exception: they are visible in every label of the function, since they're bound once at function entry regardless of which label executes first.

Variables defined in a label are local to it. 
