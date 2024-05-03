cxx = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O3 -fprofile-arcs -ftest-coverage
LDFLAGS = -ldeepstate -lgcov

targets = test

test: harness.cpp AVLTree.cpp
	$(cxx) $(CXXFLAGS) harness.cpp AVLTree.cpp -o test  $(LDFLAGS)

coverage:
	make clean
	make test
	rm -rf coverage_report
	./test --fuzz --timeout 1
	gcov AVLTree.cpp
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report

main: main.cpp AVLTree.cpp
	$(cxx) $(CXXFLAGS) main.cpp AVLTree.cpp -o main

fuzz:
	./test --fuzz --timeout 1

clean:
	rm -f test main *.gcda *.gcno 