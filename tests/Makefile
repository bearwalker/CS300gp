CPP = "g++"
CPPFLAGS = "-std=c++17"

GTEST_CFLAGS = `pkg-config --cflags gtest_main`
GTEST_LIBS = `pkg-config --libs gtest_main`

csvtests: csvtests.o
	$(CPP) $(CPPFLAGS) $< -o $@ $(GTEST_LIBS)

csvtests.o: ../csvParser.h csvTests.cpp
	$(CPP) $(CPPFLAGS) csvTests.cpp -o $@ $(GTEST_CFLAGS)
