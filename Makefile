CXX = g++
CPPFLAGS = -g -Wall 

all: interpreter
	
interpreter: Interpreter.cpp EndStatement.o LetStatement.o PrintStatement.o PrintAllStatement.o ProgramState.o ReturnStatement.o IfStatement.o GoToStatement.o GoSubStatement.o ReturnStatement.o ArithmeticStatement.o
	$(CXX) $(CPPFLAGS) $^ -o $@

EndStatement.o: EndStatement.cpp EndStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

LetStatement.o: LetStatement.cpp LetStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

PrintStatement.o: PrintStatement.cpp PrintStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

PrintAllStatement.o: PrintAllStatement.cpp PrintAllStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

ArithmeticStatement.o: ArithmeticStatement.cpp ArithmeticStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

ReturnStatement.o: ReturnStatement.cpp ReturnStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

IfStatement.o: IfStatement.cpp IfStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

GoSubStatement.o: GoSubStatement.cpp GoSubStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

GoToStatement.o: GoToStatement.cpp GoToStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

ProgramState.o: ProgramState.cpp ProgramState.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm *.o -rf