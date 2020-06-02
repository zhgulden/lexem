## Content
* [Definitions and Basics](#basics)
* [Purpose](#purpose)
* [Arithmetic operations](#arithmetic)
  * [Binary operations](#binary)
  * [Bitwise operations](#bit)
   * [Bitwise AND](#bitand)
   * [Bitwise OR](#bitor)
   * [Bitwise XOR](#bitxor)
   * [Shift left](#left)
   * [Shift right](#right)

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

The language defines six binary arithmetic operations and brackets, which are presented in the table below:

|     Operation name     |   Operation symbol   |
| ---------------------- | -------------------- |
|          plus          |          `+`         |
|          minus         |          `-`         |
|     multiplication     |          `*`         |
|         division       |          `/`         |
| division with remainder|          `%`         |
|         brackets       |          `()`        |

Operations for the four basic arithmetic operations — addition, subtraction, multiplication, and division are performed in the same way as in mathematics, taking into account the conversion of the values of string operands to numbers. The binary arithmetic operation — the remainder of division require some explanation. It is the remainder of dividing the number entirely. 

Examples of the remainder of division operation: 
``` 14 % 4 = 3 ```
``` 101 % 10 = 1 ```
``` 44 % 2 = 0 ```
``` 34 % 12 = 6 ```

#### Example:
Input:
``` ((123 + 24) / (34 % 12)) - (2 * 10) ```

Output:
``` -6 ```

## <a name="bit"></a> Bitwise operations

A bitwise operation operates on one or more bit patterns or binary numerals at the level of their individual bits. It is a fast and simple action, directly supported by the processor, and is used to manipulate values for comparisons and calculations.

On simple processors, typically, bitwise operations are substantially faster than division, several times faster than multiplication, and sometimes significantly faster than addition.

The language defines five bitwise arithmetic operations, which are presented in the table below:

|     Operation name     |   Operation symbol   |
| ---------------------- | -------------------- |
|       bitwise and      |          `&`         |
|       bitwise or       |          `|`         |
|       bitwise xor      |          `^`         |
|       shift right      |          `>>`        |
|       shift left       |          `<<`        |

### <a name="bitand"></a> Bitwise AND

A bitwise AND is a binary operation that takes two equal-length binary representations and performs the logical AND operation on each pair of the corresponding bits, which is equivalent to multiplying them. Thus, if both bits in the compared position are 1, the bit in the resulting binary representation is 1 (1 × 1 = 1); otherwise, the result is 0 (1 × 0 = 0 and 0 × 0 = 0)

#### Examples:
Input: ``` 5 & 3 ```
Output: ``` 1 ```

|          |   010**1**   | decimal 5 |
| -------- | ------------ | --------- |
|   `&`    |   001**1**   | decimal 3 |
|   `=`    |   000**1**   | decimal 1 |

Input: ``` 6 & 1 ```
Output: ``` 0 ```

|          |   0**11**0   | decimal 6 |
| -------- | ------------ | --------- |
|   `&`    |   000**1**   | decimal 1 |
|   `=`    |   0000       | decimal 0 |

### <a name="bitor"></a> Bitwise OR

A bitwise OR is a binary operation that takes two bit patterns of equal length and performs the logical inclusive OR operation on each pair of corresponding bits. The result in each position is 0 if both bits are 0, while otherwise the result is 1. 

#### Examples:
Input: ``` 5 & 3 ```
Output: ``` 7 ```

|          |   010**1**   | decimal 5 |
| -------- | ------------ | --------- |
|   `&`    |   001**1**   | decimal 3 |
|   `=`    |   0**111**   | decimal 7 |

Input: ``` 6 & 1 ```
Output: ``` 0 ```

|          |   0**11**0   | decimal 6 |
| -------- | ------------ | --------- |
|   `&`    |   000**1**   | decimal 1 |
|   `=`    |   0**111**   | decimal 7 |

### <a name="bitxor"></a> Bitwise XOR

A bitwise XOR is a binary operation that takes two bit patterns of equal length and performs the logical exclusive OR operation on each pair of corresponding bits. The result in each position is 1 if only one of the bits is 1, but will be 0 if both are 0 or both are 1. In this we perform the comparison of two bits, being 1 if the two bits are different, and 0 if they are the same.

#### Examples:
Input: ``` 5 & 3 ```
Output: ``` 6 ```

|          |   010**1**   | decimal 5 |
| -------- | ------------ | --------- |
|   `&`    |   001**1**   | decimal 3 |
|   `=`    |   0**11**0   | decimal 6 |

Input: ``` 2 & 10 ```
Output: ``` 8 ```

|          |   00**1**0      | decimal 2  |
| -------- | --------------- | ---------- |
|   `&`    |   **1**0**1**0  | decimal 10 |
|   `=`    |   **1**000      | decimal 8  |








