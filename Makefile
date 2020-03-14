CXX = g++
CXXFLAGS = -std=c++17 -Wall
LINKFLAGS = 
CXXVERSION = $(shell $(CXX) -dumpversion | sed 's/\..*//g')
# Header files go here
HEADERS = csvParser.h defs.h digits.h member.h provider.h service.h session.h
# Add your implementation files here, replacing .cpp with .o
OBJECTS = member.o provider.o service.o digits.o session.o
# Add you test files here, replacing .cpp with .o
TESTOBJECTS = csvTests.o digitsTests.o memberTests.o serviceTests.o providerTests.o 
# Don't modify this line, it adds the directory to the test objects
TESTOBJECTS := $(addprefix tests/,$(TESTOBJECTS))

# Add flags based on g++ version
ifeq ($(shell echo ${CXXVERSION}\<8 | bc), 1)
	CXXFLAGS += -lstdc++fs -DGCC_OLD
	LINKFLAGS += -lstdc++fs
endif

.PHONY: all run clean

all: test chocan

chocan: main.cpp $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $< $(OBJECTS) -o $@ $(LINKFLAGS)

$(OBJECTS): $(HEADERS)

test: tests/testMain.o $(TESTOBJECTS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./test

$(TESTOBJECTS): tests/catch.hpp $(OBJECTS) $(HEADERS)
tests/testMain.o: tests/catch.hpp

run:
	./chocan

clean:
	-rm $(TESTOBJECTS) $(OBJECTS) test tests/testMain.o chocan


