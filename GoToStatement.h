
//#ifndef LET_STATEMENT_INCLUDED
//#define LET_STATEMENT_INCLUDED

#include "ProgramState.h"
#include "Statement.h"

class GoToStatement : public Statement {
private:
    int m_lineNum;

public:
    GoToStatement(int lineNum);

    virtual void execute(ProgramState* state, std::ostream& outf);
};

//#endif
