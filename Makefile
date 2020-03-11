CXX = g++
CXXFLAGS = -std=c++17 -Wall
# Add your implementation files here, replacing .cpp with .o
OBJECTS = member.o provider.o services.o

.PHONY: all run clean tests

all: tests chocan

chocan: main.cpp $(OBJECTS) defs.h
	$(CXX) $(CXXFLAGS) $< $(OBJECTS) -o $@

$(OBJECTS): defs.h

run:
	./chocan

clean:
	-rm $(OBJECTS) chocan

tests:
	$(MAKE) -C tests
