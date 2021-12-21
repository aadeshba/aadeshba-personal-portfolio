// IfStatement.cpp:
#include "IfStatement.h"
#include <climits>
using namespace std;

IfStatement::IfStatement(string varName, string comparison, int compare, int lineNum) //possibly make comparison a string!
        : m_varName(varName), sign(comparison), m_compare(compare), m_lineNum (lineNum)
{}

void IfStatement::execute(ProgramState* state, ostream& outf) { 
    if (state->getFromMap(m_varName) == INT_MIN) {  // checks if variable exists -> if not, creates it with 0
        state->addToMap(m_varName, 0);
    }
    
    if (sign == "<") { //if this is the comparison taken in by the ss
        if (state->getFromMap(m_varName) < m_compare) { //obtains the proper variables from map, compares it to the comparison var
            state->setProgramCounter(m_lineNum);  //jumps lines if necessary by setProgramCounter function
            // jump to proper
        }
    }
    if (sign == "<=") {
        if (state->getFromMap(m_varName) <= m_compare) {
            state->setProgramCounter(m_lineNum);  
            // jump to proper
        }
    }
    if (sign == ">") {
        if (state->getFromMap(m_varName) > m_compare) {
            state->setProgramCounter(m_lineNum);
            // jump to proper
        }
    }
    if (sign == ">=") {
        if (state->getFromMap(m_varName) >= m_compare) {
            state->setProgramCounter(m_lineNum);
            // jump to proper
        }
    }
    if (sign == "=") {
        if (state->getFromMap(m_varName) == m_compare) {
            state->setProgramCounter(m_lineNum);
            // jump to proper
        }
    }
    if (sign == "<>") {
        if (state->getFromMap(m_varName) != m_compare) {
            state->setProgramCounter(m_lineNum);
            // jump to proper
        }
    }
    

}

