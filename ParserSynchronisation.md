# The problem

Currently, when the parser encounters a malformed series of tokens, it panics, outputs the error and quits. Ideally, though, it should make a note of the error, find its place again, and continue parsing, repeating the process for any more errors it encounters and reporting them to the user at the end.

This is a process called synchronisation - the parser has a list of structures, eg function definitions, class definitions, return statements, that it assumes will be the start of a new block of code. When it encounters an error, it enters 'panic mode' - skipping over tokens until it finds one of these 'safe bets' from which it can start parsing again.

Entering panic mode, though, isn't as simple as it sounds. The parser is implemented as a deep chain of functions, each recognising a particular grammar rule. On encountering an error we need to unwind this chain, returning to the base level to start synchronising. In any other language this would be easy - simply throw an exception and the language will do the unwinding for us. However, in C, there's no such thing, so we need a DIY method of unwinding our call tree.

# The solutions

## Error propagation with return codes

Traditional 'exceptions' in C are implemented by functions returning an error value, eg -1. Currently, though, every parser function returns a value which represents the AST node it's parsed. This means that if we want to use return codes we've got two options:

Option|Pros|Cons
-|-|-
Create a new return type for every function, representing either the AST node or an error value. This could be done with a macro, as could handling them from the caller.|- Works w/ existing code structure<br />- Relatively easy to implement|- Spaghetti macro hell<br />- Probably not very future-proof
Store the AST in a global/separate object, so that instead of being constructed from function return values it gets constructed procedurally. Functions are then free to return error codes.|- Sexy & follows existing C design patterns<br />- Having a separate AST object might allow for cool asynchronous buildtime feedback later down the line|- Huge refactor needed<br />- Do we really need this much flexibility with return codes?
<br />

But what if we don't want to use 'traditional' C exceptions at all? There's a couple more strategies we could use.
<br />

## Dedicated error-handling structure

A global/separate structure is used to handle errors - functions return complete or incomplete AST nodes, and the structure is checked before continuing, so errors can be propagated up. Checking here could again be done with a macro.

Pros|Cons
-|-
|- Modular error handling<br />- Easy to give errors back at the end<br />- Function returns stay the same|- Still need to check the error handler, still a chance of macro hell

## `setjmp` and `longjmp`

The final option is to use the `setjmp` and `longjmp` functions (which are incidentally how C++ exceptions work behind the scenes). They allow the programmer to jump non-linearly within code, including for our intended purpose - unwinding many levels up the callstack.

Pros|Cons
-|-
|- Code structure is a good representation of the design intention: the obvious implication of a `longjmp` like this is to unwind the callstack when the program is in an unusual state<br />- Little changes required in existing code - most of the legwork can be done by the already-existing `panic()` function<br />- I actually get to learn something new|- Unsafe? cleanup & default values need to be formalised<br />- Very abusable feature - need to be careful and precise about its usage
