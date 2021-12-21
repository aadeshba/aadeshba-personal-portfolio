// ArithmeticStatement.cpp:
#include "ArithmeticStatement.h"
#include <iostream>
#include <climits>
using namespace std;

ArithmeticStatement::ArithmeticStatement(string operation, string var1, string var2)
    : operationT(operation), variable1(var1), variable2(var2) 
{}


void ArithmeticStatement::execute(ProgramState* state, ostream& outf) 
{     
    if (state->getFromMap(variable1) == INT_MIN) {  // checks if variable exists -> if not, creates it with 0
        state->addToMap(variable1, 0);
    }

    int value = 0;
    value = state->parseStringToInt(variable2); //obtains value from either the var or the given int

    if (operationT == "DIV" && value == 0) {
        outf << "Divide by zero exception." << endl; //divide by zero exception-- terminates program
        exit(EXIT_FAILURE);
    }

    int temp = state->performOperation(operationT, variable1, value);  //programstate function that performs the given operation (operationT) and returns an int
    state->addToMap(variable1, temp); //assigns new value, temp, to the respective variable, variable1.
    state->setProgramCounter(state->getProgramCounter() + 1);//increments the programCounter
    return;
}

//ArithmeticStatement::~ArithmeticStatement() {
//
//}
