
#include "ProgramState.h"
#include "Statement.h"
using namespace std;

class IfStatement : public Statement {
public:
    IfStatement(string varName, string comparison, int compare, int lineNum);

    virtual void execute(ProgramState* state, std::ostream& outf);


private:
    string m_varName;
    string sign;
    int m_compare;
    int m_lineNum;

};

