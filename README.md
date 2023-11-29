# Orlets
My stack-based programming language.

# Documentation

## Syntax
* Tokens must be separated by space or newline.
* Most tokens perform operations with stack, so you need to pass argument before a token. Ex. `. ("Hello, world!")` -> `("Hello, world!") .`.
* Tokens doesn't need to be aligned, you can put them where ever you want.
* Tokens like `if` must be 'closed' by `endif` for them to work.

## PushInt
PushInt pushes an integer to the top of the stack.
```
(<Integer to push>)
```
Examples: `(1)`, `( 100 )`, `(69)`.

## PushFloat
PushFloat pushes an float to the top of the stack.
```
(<Float to push>)
```
Examples: `(3.14)`, `( -100.69 )`, `(69.5)`.

## PushString
PushString pushes an string to the top of the stack.
```
("<String to push>")
```
Examples: `("Hello, world!")`, `( "-100.69" )`, `("")`.

## Plus
Pops last two element from the stack, sums them, and pushed the result back.
Supports ints, floats, and strings.
Note! Two elements on the stack will get removed!
```
+
```

## Minus
Pops last two element from the stack, subtracks latest one from the older one, and pushed the result back.'
Supports ints, floats.
Note! Two elements on the stack will get removed!
```
-
```

## Multiply
Pops last two element from the stack, multiplies them, and pushed the result back.
Supports ints, floats.
Note! Two elements on the stack will get removed!
```
*
```

## Divide
Pops last two element from the stack, divides latest one from the older one, and pushed the result back.
Supports ints, floats.
Note! Two elements on the stack will get removed!
```
/
```

## Power
Pops last two element from the stack, calculates latest one to the power of the older one, and pushed the result back.
Supports ints, floats.
Note! Two elements on the stack will get removed!
```
^
```

## Modulo
Pops last two element from the stack, modules latest one from the older one, and pushed the result back.
Supports ints.
Note! Two elements on the stack will get removed!
```
%
```

## Swap
Swaps last two elemets of the stack
```
swp
```

## LSwap
Swaps last three elemets of the stack
```
lswp
```

## Dump
Removes last element from the stack and prints it to the cout.
```
.
```

## Print
Prints last element from the stack without removing it.
```
,
```

## Less
Removes last two elements from the stack and pushes `1` if first is less then second, `0` otherwise.
```
<
```

## More
Removes last two elements from the stack and pushes `1` if first is more then second, `0` otherwise.
```
>
```

## Equal
Removes last two elements from the stack and pushes `1` if they are equal, `0` otherwise.
```
=
```

## Debug
TOKEN IS ONLY FOR DEBUGING PURPOSES. DO NOT USE IT AS <br>!
Debugs stuck's contents.
```
`
```

## Endl
Returns to the new line and pushes the std::cout buffer.
```
endl
```

## Dup
Duplicates last element on the stack
```
dup
```

## Jeg
Pops one string from the stack, and registers it as a valid location (itself) to use `jmp`
```
jeg
```

## Jmp
Pops one string from the stack, and jumps to location, if this tring is registered by `jeg`
```
jmp
```

## If
Falls through if last element on the stack is Int 1, Float 1.0, or String "true", Jumps to else or endif otherwise.
```
if
```

## Endlif
Part of `if` token statement.
```
endif
```

## Else
Part of `if` token statement.
```
else
```
