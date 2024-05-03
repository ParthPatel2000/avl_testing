cxx = g++
CXXFLAGS = -std=c++11 -Wall -Wextra  -pedantic -O3
LDFLAGS = -ldeepstate

targets = test

.PHONY: clean mutants check fuzz

test: harness.cpp AVLTree.cpp
	$(cxx) $(CXXFLAGS) harness.cpp AVLTree.cpp -o test  $(LDFLAGS)

mutants:
	mutate AVLTree.cpp --mutantDir mutants --cmd "g++ AVLTree.cpp -c "

check:
	analyze_mutants AVLTree.cpp --mutantDir mutants "g++ harness.cpp AVLTree.cpp -o main -ldeepstate && ./main --fuzz --timeout 1" --timeout 10

fuzz:
	./test --fuzz --timeout 1

clean:
	rm -f test main