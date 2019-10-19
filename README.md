# Ases
Ases is an esoteric programming language developed with the objective of be
more useful as possible. You can see examples of code [clicking here](examples/).

To install, just run:
```
$ make
$ sudo make install
```

For see help about usage, run:
```
$ ases -h
```

## Documentation
The documentation is generated with [Doxygen](http://www.doxygen.nl/). For see it online, [click here](https://silva97.github.io/Ases/html/index.html).

## Characteristics
* Registers A, B, C and D with the size of 2 bytes.
* Data Pointer of 2 bytes to point the data memory location.
* Stack of 2 bytes for work with instructions and functions.
* Any characters that is not a instruction is ignored.

## Instructions
|        Command       | Description                                                                                    |
|         :---:        | :---                                                                                           |
| `a`, `b`, `c` or `d` | Stores the value of the stack to correspondent register                                        |
| `A`, `B`, `C` or `D` | Gets the value of the correspondent register and stores in the stack                           |
|         `p`          | Stores the value of the stack in the **Data Pointer**                                          |
|         `P`          | Gets the value of the **Data Pointer** and stores in the stack                                 |
|         `$`          | Stores the address of the next instruction in D register                                       |
|         `*`          | Jumps for the instruction pointed by the value of D register                                   |
|         `(`          | Jumps for the address of the symbol `@` matched in the right                                   |
|         `)`          | Jumps for the address of the symbol `@` matched in the left                                    |
|         `@`          | Does nothing                                                                                   |
|         `!`          | Stores the value of the stack in the data memory location pointed by **Data Pointer**          |
|         `=`          | Gets the value in the data memory location pointed by **Data Pointer** and stores in the stack |
|         `>`          | Increments the value of **Data Pointer**                                                       |
|         `<`          | Decrements the value of **Data Pointer**                                                       |
|         `+`          | Increments the value of the stack                                                              |
|         `-`          | Decrements the value of the stack                                                              |
|         `.`          | Clears the value of the stack                                                                  |
|         `?`          | Only executes the next instruction if the value of the stack is zero                           |
|         `~`          | Only executes the next instruction if the value of the stack **not** is zero                   |
|         `#`          | Commentary of one line                                                                         |

## Functions
| Function | Description                                                                    |
|  :---:   | :---                                                                           |
|   `0`    | Gets input of one character and stores in the stack                            |
|   `1`    | Prints a character stored in the stack                                         |
|   `2`    | Prints the message "ERROR!" and stops the program (exit status = 255)          |
|   `3`    | Exits the program with the status code defined by the value of the stack       |
|   `4`    | Adds the value of the A register with the value of the stack                   |
|   `5`    | Subtracts the value of the A register with the value of the stack              |
|   `6`    | Adds 10 to the stack                                                           |
|   `7`    | Subtracts 10 of the stack                                                      |
|   `8`    | Prints the state of the machine                                                |
|   `9`    | If A > B, sets stack to zero. One otherwise                                    |