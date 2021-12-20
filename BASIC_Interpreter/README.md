I basically made every new class as a subclass of statement, and then combined the four 
arithmetic classes into one ArithmeticStatement class. Everything in the vector is called
in a while loop in the interpreter.cpp driver. I used a private data member of my 
ProgramState class called ProgramCounter to keep track of where I am in the program
at any given moment. Type make to compile.