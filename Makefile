CXX = g++
CXXFLAGS = -std=c++17 -Wall
# Add your implementation files here, replacing .cpp with .o
OBJECTS = member.o provider.o services.o digits.o session.o
# Add you test files here, replacing .cpp with .o
TESTOBJECTS = csvTests.o digitsTests.o
# Don't modify this line, it adds the directory to the test objects
TESTOBJECTS := $(addprefix tests/,$(TESTOBJECTS))

.PHONY: all run clean

all: tests chocan

chocan: main.cpp $(OBJECTS) defs.h csvParser.h
	$(CXX) $(CXXFLAGS) $< $(OBJECTS) -o $@

$(OBJECTS): defs.h

test: tests/testMain.o $(TESTOBJECTS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./test

$(TESTOBJECTS): tests/catch.hpp defs.h csvParser.h $(OBJECTS)
tests/testMain.o: tests/catch.hpp
digits.o: defs.h

run:
	./chocan

clean:
	-rm $(TESTOBJECTS) $(OBJECTS) tests/testMain.o chocan


