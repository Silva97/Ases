# Ases
Ases is an esoteric programming language developed by me with the objective of be the more functional as possible.


## Characteristics
* 256 Bytes of data memory
* 256 Bytes of maximum size of the code
* Registers A, B, C and D with the size of 1 Byte
* Data Pointer of 1 Byte to point the data memory location
* Stack of 1 Byte for work with instructions and functions
* Any characters that is not a instruction is ignored

## Instructions
|        Command       | Description                                                                                    |
|         :---:        | :---                                                                                           |
| `a`, `b`, `c` or `d` | Stores the value of the stack to correspondent register                                        |
| `A`, `B`, `C` or `D` | Gets the value of the correspondent register and stores in the stack                           |
|         `p`          | Stores the value of the stack in the **Data Pointer**                                          |
|         `P`          | Gets the value of the **Data Pointer** and stores in the stack                                 |
|         `$`          | Stores the address of the actual instruction in D register                                     |
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
|         `#`          | Only executes the next instruction if the value of the stack is zero                           |
|         `%`          | Only executes the next instruction if the value of the stack **not** is zero                   |
|         `;`          | Comment of one line                                                                            |

## Functions
| Function | Description |
|  :---:   | :---        |
|   `0`    | Gets input of one character and stores in the stack |
|   `1`    | Prints a character stored in the stack        |
|   `2`    | Prints the message "ERROR!" and stops the program |
|   `3`    | Exits the program with the status code defined by the value of the stack |
|   `4`    | Adds the value of the A register with the value of the stack |
|   `5`    | Subtracts the value of the A register with the value of the stack |
|   `6`    | Saves a copy of the data memory |
|   `7`    | Restores the copy of the data memory saved by the `6` function |
|   `8`    | If a copy of the data memory is saved, set the value of the stack to 1. Otherwise to 0 |
|   `9`    | Compares the value of the A and B registers. |
* If A > B  : Sets the value of the stack for 2  
* If A == B : Sets the value of the stack for 1  
* If A < B  : Sets the value of the stack for 0
