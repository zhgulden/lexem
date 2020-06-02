## Content
* [Definitions and Basics](#basics)
* [Purpose](#purpose)
* [Arithmetic operations](#arithmetic)
  * [Binary operations](#binary)
  * [Bitwise operations](#bit)
   * [Bitwise AND](#bitand)
   * [Bitwise OR](#bitor)
   * [Bitwise XOR](#bitxor)
   * [Shift left and Shift right](#leftright)
* [Assignment](#assign)
 * [How map container works?](#map)
* [How to compile program?](#run)
* [Questions and suggestions](#qa)

# <a name="basics"></a> Definitions and Basics

**An interpreter** is a computer program that directly executes instructions written in a programming or scripting language, without requiring them previously to have been compiled into a machine language program. 

An interpreter generally uses one of the following strategies for program execution:

<li> Parse the source code and perform its behavior directly;
<li> Translate source code into some efficient intermediate representation and immediately execute this;
<li> Explicitly execute stored precompiled code made by a compiler which is part of the interpreter system.

#  <a name="purpose"></a> Purpose

The pupose is to write a program that executes instructions written in a high-level language in interactive mode.

**Interactive mode** is a command line shell which gives immediate feedback for each statement, while running previously fed statements in active memory. As new lines are fed into the interpreter, the fed program is evaluated both in part and in whole. 

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

|     Operation name     |   Operation symbol     |
| ---------------------- | ---------------------- |
|       bitwise and      |          `&`           |
|       bitwise or       |          ` | `         |
|       bitwise xor      |          `^`           |
|       shift right      |          `>>`          |
|       shift left       |          `<<`          |

### <a name="bitand"></a> Bitwise AND

A bitwise AND is a binary operation that takes two equal-length binary representations and performs the logical AND operation on each pair of the corresponding bits, which is equivalent to multiplying them. Thus, if both bits in the compared position are 1, the bit in the resulting binary representation is 1 (1 × 1 = 1); otherwise, the result is 0 (1 × 0 = 0 and 0 × 0 = 0)

#### Examples:
Input: 
``` 5 & 3 ```

Output: 
``` 1 ```

|          |   010**1**   | decimal 5 |
| -------- | ------------ | --------- |
|   `&`    |   001**1**   | decimal 3 |
|   `=`    |   000**1**   | decimal 1 |

Input: 
``` 6 & 1 ```

Output: 
``` 0 ```

|          |   0**11**0   | decimal 6 |
| -------- | ------------ | --------- |
|   `&`    |   000**1**   | decimal 1 |
|   `=`    |   0000       | decimal 0 |

### <a name="bitor"></a> Bitwise OR

A bitwise OR is a binary operation that takes two bit patterns of equal length and performs the logical inclusive OR operation on each pair of corresponding bits. The result in each position is 0 if both bits are 0, while otherwise the result is 1. 

#### Examples:
Input: 
``` 5 & 3 ```

Output: 
``` 7 ```

|          |   010**1**   | decimal 5 |
| -------- | ------------ | --------- |
|   `&`    |   001**1**   | decimal 3 |
|   `=`    |   0**111**   | decimal 7 |

Input: 
``` 6 & 1 ```

Output: 
``` 0 ```

|          |   0**11**0   | decimal 6 |
| -------- | ------------ | --------- |
|   `&`    |   000**1**   | decimal 1 |
|   `=`    |   0**111**   | decimal 7 |

### <a name="bitxor"></a> Bitwise XOR

A bitwise XOR is a binary operation that takes two bit patterns of equal length and performs the logical exclusive OR operation on each pair of corresponding bits. The result in each position is 1 if only one of the bits is 1, but will be 0 if both are 0 or both are 1. In this we perform the comparison of two bits, being 1 if the two bits are different, and 0 if they are the same.

#### Examples:
Input: 
``` 5 & 3 ```

Output: 
``` 6 ```

|          |   010**1**   | decimal 5 |
| -------- | ------------ | --------- |
|   `&`    |   001**1**   | decimal 3 |
|   `=`    |   0**11**0   | decimal 6 |

Input: 
``` 2 & 10 ```

Output: 
``` 8 ```

|          |   00**1**0      | decimal 2  |
| -------- | --------------- | ---------- |
|   `&`    |   **1**0**1**0  | decimal 10 |
|   `=`    |   **1**000      | decimal 8  |

### <a name="leftright"></a> Shift Left and Shift Right

In a shift, zeros are shifted in to replace the discarded bits. Therefore, the logical and arithmetic left-shifts are exactly the same.

However, as the logical right-shift inserts value 0 bits into the most significant bit, instead of copying the sign bit, it is ideal for unsigned binary numbers, while the arithmetic right-shift is ideal for signed two's complement binary numbers

#### Examples:
Input:
``` 5 >> 1 ```

Output:
``` 2 ```

```
0101 >> 1  →  0010

0101 is 5
0010 is 2
```

Input:
``` 2 >> 2 ```

Output:
``` 8 ```

```
0010 >> 2  →  1000

0010 is 2
1000 is 8
```

# <a name="assign"></a> Assignment

**An assignment** statement sets and/or re-sets the value stored in the storage location(s) denoted by a variable name; in other words, it copies a value into the variable.

**Variables** are containers for values. It is possible to put a value into a variable and later replace it with a new one. An assignment operation modifies the current state of the executing program. Consequently, assignment is dependent on the concept of variables. In an assignment:

* The expression is evaluated in the current state of the program.
* The variable is assigned the computed value, replacing the prior value of that variable.

The name of the variables and their values are stored in the program using the `std::map<std::string, int> varTable;`.

## <a name="map"></a> How map container works?

Maps are associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order.

In a map, the key values are generally used to sort and uniquely identify the elements, while the mapped values store the content associated to this key. The types of key and mapped value may differ, and are grouped together in member type `value_type` , which is a pair type combining both:

```typedef pair<const Key, T> value_type;```

Internally, the elements in a map are always sorted by its key following a specific strict weak ordering criterion indicated by its internal comparison object.

Map containers are generally slower than unordered_map containers to access individual elements by their key, but they allow the direct iteration on subsets based on their order. The mapped values in a map can be accessed directly by their corresponding key using the bracket operator.

Maps are typically implemented as binary search trees.

#  <a name="depend"></a> Dependencies

The program was written in the C ++ programming language, so for its compilation and further launch, you must install the **g++ compiler**

### Debian/Ubuntu/Mint

``` sudo apt-get update ```

``` sudo apt-get install g++ ```

### Fedora/CentOS

``` sudo dnf update ```

``` sudo dnf install g++ ```

# <a name="run"></a> How to compile program?

```
make
```

# <a name="qa"></a> Questions and suggestions

If you have any questions or suggestions, write to the email zhanmukanbetova.gulden@gmail.com


