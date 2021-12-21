
#include "ProgramState.h"
#include "Statement.h"

class GoSubStatement : public Statement {
private:
    int m_lineNum;

public:
    GoSubStatement(int lineNum);

    virtual void execute(ProgramState* state, std::ostream& outf);
};
