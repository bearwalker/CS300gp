CPP = "g++"
CPPFLAGS = "-std=c++17"

csvtests: csvTests.cpp ../csvParser.h ../csvParser.cpp catch.hpp
	$(CPP) $(CPPFLAGS) $< ../csvParser.cpp -o $@ 

