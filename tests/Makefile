CXX = g++
CXXFLAGS = -std=c++17 -Wall
# Add your test file here, replacing .cpp with .o
OBJECTS = csvTests.o 

tests: testMain.o $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJECTS): catch.hpp ../defs.h
testMain.o: catch.hpp

.PHONY: run clean
run:
	./tests

clean:
	-rm testMain.o $(OBJECTS) tests
