## Content
* [Definitions and Basics](#basics)
* [Purpose](#purpose)
* [Arithmetic operations](#arithmetic)
  * [Binary operations](#binary)


# <a name="basics"></a> Definitions and Basics

**An interpreter** is a computer program that directly executes instructions written in a programming or scripting language, without requiring them previously to have been compiled into a machine language program. 

An interpreter generally uses one of the following strategies for program execution:

<li> Parse the source code and perform its behavior directly;
<li> Translate source code into some efficient intermediate representation and immediately execute this;
<li> Explicitly execute stored precompiled code made by a compiler which is part of the interpreter system.

# <a name="arithmetics"></a> Arithmetic operations

The main purpose of arithmetic operations is to perform certain arithmetic operations on numerical data: add, subtract, multiply, divide, etc. This means that for arithmetic operations, all operands are calculated in a numerical scalar context. In this case, strings containing the correct numeric literals will be automatically converted to numeric values: if the string does not contain the correct numeric literal, the interpreter will try to extract a number from it, starting with the left character, and use it as an operand.

## <a name="binary"></a> Binary operations

The operations for performing basic arithmetic operations are binary, since they require two operands. Everything said about converting strings to numbers relates precisely to such operations.

The language defines six binary arithmetic operations, which are presented in the table below:
|     Operation name     |   Operation symbol   |
| ---------------------- | -------------------- |
|          plus          |          '+'         |
|          minus         |          '-'         |
|     multiplication     |          '*'         |
|         division       |          '/'         |
| division with remainder|          '%'         |





Можно управлять выравниванием сто
