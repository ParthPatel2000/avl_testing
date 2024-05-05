cxx = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O1 -fprofile-arcs -ftest-coverage
LDFLAGS = -ldeepstate -lgcov

targets = coverage

.PHONY: test fuzz coverage

test: harness.cpp AVLTree.cpp
	$(cxx) $(CXXFLAGS) harness.cpp AVLTree.cpp -o test  $(LDFLAGS)

coverage:
	make clean
	rm -rf coverage_report
	make test
	make fuzz
	gcov AVLTree.cpp
	lcov --capture --directory . --output-file coverage.info 
	lcov --remove coverage.info '/usr/include/*' '/usr/local/include/*'  -o filtered_coverage.info
	genhtml filtered_coverage.info --output-directory coverage_report
	

main: main.cpp AVLTree.cpp
	$(cxx) $(CXXFLAGS) main.cpp AVLTree.cpp -o main

fuzz:
	./test --fuzz --timeout 10

clean:
	rm -f test main *.gcda *.gcno *.info