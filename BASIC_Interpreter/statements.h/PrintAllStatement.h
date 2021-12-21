
#include "Statement.h"
#include "ProgramState.h"


class PrintAllStatement : public Statement {

public:
    PrintAllStatement();

    virtual void execute(ProgramState* state, std::ostream& outf);

    virtual ~PrintAllStatement();
};
