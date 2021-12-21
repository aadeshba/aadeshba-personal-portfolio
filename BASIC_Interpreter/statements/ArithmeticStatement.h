
#include "Statement.h"
#include "ProgramState.h"

using namespace std;

class ArithmeticStatement: public Statement 
{
public:
    ArithmeticStatement(string operation, string var1, string var2);

    virtual void execute(ProgramState* state, ostream& outf);

    //virtual ~ArithmeticStatement();

private:
    string operationT;
    string variable1;
    string variable2;

};

