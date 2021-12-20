all: ruinQP probeRate
CXX = g++
CPPFLAGS = -g  

	
ruinQP: ruinQP.cpp Hashtable.h
	$(CXX) $(CPPFLAGS) $^ -o $@

probeRate: probeRate.cpp Hashtable.h
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f ruinQP probeRate

	