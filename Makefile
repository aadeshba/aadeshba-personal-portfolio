CXX = g++
CPPFLAGS = -g -Wall 

	
doublet: doublet.cpp MinHeap.h
	$(CXX) $(CPPFLAGS) $^ -o $@