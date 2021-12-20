CXX = g++ -g --std=c++11

all: scheduling	

scheduling: scheduling.o
	$(CXX) $^ -o $@

scheduling.o: scheduling.cpp
	$(CXX) -c $< -o $@

.PHONY: clean
clean:
	rm -rf