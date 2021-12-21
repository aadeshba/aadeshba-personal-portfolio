//EndStatement.cpp
#include "EndStatement.h"
using namespace std;

EndStatement::EndStatement() 
{}

void EndStatement::execute(ProgramState* state, ostream& outf) { 
    return; 
    exit(EXIT_SUCCESS);
}
