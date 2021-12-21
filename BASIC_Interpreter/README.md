# Aadesh Bajaj - BASIC Interpreter CSCI104 Project

This was a project written for my Data Structures class in C++. It parses a programming language called BASIC by taking the text file ('data.txt'), converting it into objects that represent statement types and arguments, then executing these lines of code in sequence. The program is printed to the terminal along with its results. This project was a good example of the power of Object-Oriented programming and a well defined class structure. What seemed to be an extremely difficult process (Using one language to parse and execute another) turned out to be quite possible and run in extremely small timeframes with high accuracy. 

# The Language

## Variables

- integer variables: each variable stores a (signed) 32-bit integer. If a variable is read without having been initialized, its value is 0.
- one-dimensional arrays of integers: imagine the arrays to have "infinite" size, running from negative infinity to positive infinity. (For practical purposes, they have size equal to the range of a (signed) integer.) All (infinitely many) locations are 0 unless overwritten otherwise. Because the arrays are infinite, there can never be segfaults. If a user tries to read a location they have not written before, the value is 0.

## Expressions

When evaluating an expression, these are the rules to apply:
- a constant: that value is always its numerical value.
- an integer variable name <VAR>: the value is the value currently stored in that variable.
- an array evaluated at an integer position: the value is the array's value at the position, as described in the rules above.
- (<AEXPR1> + <AEXPR2>): the value is the sum of the values of <AEXPR1> and <AEXPR2>.
- (<AEXPR1> - <AEXPR2>): the value is the value of <AEXPR1> minus the value of <AEXPR2>.
- (<AEXPR1> * <AEXPR2>): the value is the value of <AEXPR1> multiplied with the value of <AEXPR2>.
- (<AEXPR1> / <AEXPR2>): the value is the value of <AEXPR1> divided by the value of <AEXPR2>, and rounded down to the nearest integer. (That is, the standard integer division.) If the value of <AEXPR2> is 0, then this is a division-by-0 error. The program will output an error message, including the line number where the error happened, the strings corresponding to <AEXPR1> and <AEXPR2>, and the values when the error happened. Then, the program will terminate. See below for exact format for error messages. For all arithmetic expressions, the calculations should always result in integers that fit into a (signed) 32-bit integer to avoid overflows.
- <AEXPR1> = <AEXPR2>: evaluates to true if <AEXPR1> and <AEXPR2> evaluate to the same number.
- <AEXPR1> < <AEXPR2>: evaluates to true if <AEXPR1> evaluates to a (strictly) smaller number than <AEXPR2>.
- <AEXPR1> > <AEXPR2>: evaluates to true if <AEXPR1> evaluates to a (strictly) larger number than <AEXPR2>.
