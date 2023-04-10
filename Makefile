CXX=g++
CPPFLAGS=-Wall -Wextra -pedantic -std=c++11 -I/usr/local/include -lgmp -lgmpxx
TARGET=main

all: $(TARGET) test_main

$(TARGET): main.cpp SlothPermutation.o
	$(CXX) $(CXXFLAGS) main.cpp SlothPermutation.o -o $(TARGET)

SlothPermutation.o: SlothPermutation.cpp SlothPermutation.h
	$(CXX) $(CXXFLAGS) -c SlothPermutation.cpp -o SlothPermutation.o

clean:
	rm -f $(TARGET) SlothPermutation.o

# Add this target to compile test_main.cpp
test_main: test_main.cpp SlothPermutation.o
    $(CXX) $(CPPFLAGS) test_main.cpp SlothPermutation.o -o test_main

# Add a new 'test' target to run the tests
test: test_main
    ./test_main
