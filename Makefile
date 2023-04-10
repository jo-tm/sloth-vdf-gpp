CXX=g++
CXXFLAGS=-std=c++11 -O3 -lgmp -lgmpxx
TARGET=main

all: $(TARGET) test_main

$(TARGET): main.cpp SlothPermutation.o
	$(CXX) $(CXXFLAGS) main.cpp SlothPermutation.o -o $(TARGET)

SlothPermutation.o: SlothPermutation.cpp SlothPermutation.h
	$(CXX) $(CXXFLAGS) -c SlothPermutation.cpp -o SlothPermutation.o

clean:
	rm -f $(TARGET) SlothPermutation.o

test_main: test_main.cpp SlothPermutation.o
	$(CXX) $(CXXFLAGS) test_main.cpp SlothPermutation.o -o test_main

test: test_main
	./test_main