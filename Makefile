cxx = g++
CXXFLAGS = -std=c++11 -Wall -Wextra  -pedantic -O3
LDFLAGS = -ldeepstate

targets = test
test: harness.cpp AVLTree.cpp
	$(cxx) $(CXXFLAGS) harness.cpp AVLTree.cpp -o test  $(LDFLAGS)

main: main.cpp AVLTree.cpp
	$(cxx) $(CXXFLAGS) main.cpp AVLTree.cpp -o main

fuzz:
	./test --fuzz --timeout 1

clean:
	rm -f test main