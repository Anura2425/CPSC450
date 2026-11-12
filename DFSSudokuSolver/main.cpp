// FILE: main.cpp
// NAME: Gavin McClure-Coleman
// DATE: Nov 11, 2026
// DESC: Solves the Sudoku puzzle in the input file and writes the
//       solved board to the output file.
//
// USAGE: ./sudoku <input file> <output file>

#include <iostream>
#include "sudoku.h"

int main(int argc, char* argv[])
{
  if (argc != 3) {
    std::cerr << "usage: " << argv[0] << " <input file> <output file>\n";
    return 1;
  }
  Board puzzle;
  if (!read_board(argv[1], puzzle)) {
    std::cerr << "error: cannot read board from " << argv[1] << "\n";
    return 1;
  }
  Board board = puzzle;
  if (!solve(board, 0, 0)) {
    std::cout << argv[1] << ": no solution\n";
    return 1;
  }
  if (!is_solution(puzzle, board)){
    std::cerr << "error: internal verification failed for " << argv[1] << "\n";
  }
  if (!write_board(argv[2], board)) {
    std::cerr << "error: cannot write board to " << argv[2] << "\n";
    return 1;
  }
  std::cout << argv[1] << ": solved, written to " << argv[2] << "\n";
  return 0;
}
