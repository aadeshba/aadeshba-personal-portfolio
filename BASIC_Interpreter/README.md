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
  
## Commands
Here is some detail on the commands in the language:
- PRINT x: prints the value of the arithmetic expression, evaluated according to the rules above. Always prints a newline after the value.
- LET VAR x: reads in x and stores the resulting value into the variable VAR, overwriting the previous value (if existed).
- GOTO LINE#: Jump to the provided line number. Forgets which line it came from. Just resumes processing at the given line. If there is no line numbered LINE# in the program, it will print an error and terminate. See error messages below.
- IF X THEN LINE#: evaluates the given expression according to the rules given above. If it comes out true, then jumps to the line LINE# (as in the case of GOTO). Otherwise just advances to the next line. As for GOTO, if the target line does not exist, it will output an error. (See error messages below.) If the condition comes out false (so there's no jump), and the target line does not exist, then no error is reported, as the program can safely continue running.
- GOSUB LINE#: Jumps to the line LINE#, and remembers where it came from. As for GOTO/IF, if the line LINE# does not exist, then an error is printed (including the current line number and non-existing target line), and the program terminates. See below for details.
- RETURN: Go back to the line immediately after the line whence the most recent GOSUB jump started. See the more detailed example below. If there has been no applicable GOSUB jump, then an error message is printed; see below for the exact message and format.
- END: Terminate the execution of the program. Nothing can go wrong here.

## Error Messages
Whenever an error happens, the program prints an error message and terminates. Each error message begins with "Error in Line <LINE>: ", where <LINE> is the number of the line where the error occurred. After that, it prints an error-specific message, which will be one of the following:

- "Division by 0: <AEXP1> = <VAL1>, <AEXP2> = <VAL2>." Here, <AEXP1> and <AEXP2> are the pretty-printed text strings for the expressions, and <VAL1> and <VAL2> are the current value. (Presumably, when an error happened, <VAL2> has a value of 0.)
- "GOTO to non-existent line <LINEJ>." Here, <LINEJ> is the line the program was supposed to jump to, but which didn't exist.
- "IF jump to non-existent line <LINEJ>." Again, <LINEJ> is the line the program was supposed to jump to, but which didn't exist.
- "GOSUB to non-existent line <LINEJ>." Here, <LINEJ> is the line the program was supposed to jump to with GOSUB, but which didn't exist.
- "No matching GOSUB for RETURN."
- In all cases, after the error message is printed, the program terminates.
  
An example program can be found in the data.txt file.
  
# High-Level Approach to Implementation
1. Each arithmetic expression was called using the arithmetic statement class and, based on what information was parsed in the initial read-in of the file stream, the proper arithmetic was carried out. These .cpp and .h files can be found in statements.cpp and statements.h directories.
2. A separate class was made for each Command. Each command had a print function that was overriden as well as a way to execute that command. These can be found inside of the statements.cpp and statements.h directories.
3. An overall interpreter class was created to actually parse the input file containing BASIC code. It would then create the appropriate command object and all of the proper expression objects within that command. This can be found in the main directory
4. Finally, the interpreter class would loop through the list of commands in sequence, executing the current command and acting accordingly until either an END command  or a '.' was reached. 
  
## Running the program
  
Run the program in your terminal from this directory and type make to compile. Make sure to provide an input BASIC file in addition to the executable name as a command-line argument. The output should be printed to the terminal.
  
