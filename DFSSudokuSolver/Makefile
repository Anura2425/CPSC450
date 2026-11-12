# FILE: Makefile
# DESC: Builds the HW-3 Sudoku solver and its tests.
#
#   make        build, then run the solver with no arguments
#   make test   run the unit tests, then solve and check each board
#   make clean  remove built and generated files

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# input boards are sudoku_<level>.txt, one per difficulty level
LEVELS = easy medium hard expert master extreme

all: sudoku
	@./sudoku || true

sudoku: main.o sudoku.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_sudoku: test_sudoku.o sudoku.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp sudoku.h
	$(CXX) $(CXXFLAGS) -c $<

test: sudoku test_sudoku
	-./test_sudoku > test_results.txt
	@cat test_results.txt
	-@for level in $(LEVELS); do \
	  rm -f sudoku_$${level}_solved.txt; \
	  ./sudoku sudoku_$$level.txt sudoku_$${level}_solved.txt; \
	  ./test_sudoku sudoku_$$level.txt sudoku_$${level}_solved.txt \
	    > sudoku_$${level}_log.txt; \
	  cat sudoku_$${level}_log.txt; \
	done

clean:
	rm -f sudoku test_sudoku *.o sudoku_*_solved.txt sudoku_*_log.txt \
	  test_results.txt

.PHONY: all test clean
