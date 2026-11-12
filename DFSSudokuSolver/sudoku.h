// FILE: sudoku.h
// NAME: Gavin McClure-Coleman
// DATE: Nov 11, 2026
// DESC: Board type and function declarations for the HW-3 Sudoku
//       solver.

#ifndef SUDOKU_H
#define SUDOKU_H

#include <array>
#include <string>

// number of rows and columns in a board
const int N = 9;

// board[row][col] holds 1 to 9, or 0 for an empty cell
using Board = std::array<std::array<int, N>, N>;

// Read a board from the given file. Returns false if the file cannot
// be opened or is not in the expected format.
bool read_board(const std::string& filename, Board& board);

// Write the board to the given file, one row per line. Returns false
// if the file cannot be written.
bool write_board(const std::string& filename, const Board& board);

// Returns true if value can go in the cell at (row, col) without
// repeating a value in the cell's row, column, or 3x3 box.
bool is_legal_value(const Board& board, int row, int col, int value);

// Recursive DFS. Fills the empty cells starting at (row, col), in row
// order. Returns true if the board is solved, leaving the solution in
// board.
bool solve(Board& board, int row, int col);

// Returns true if the board is full, follows the Sudoku rules, and
// has each clue from the puzzle.
bool is_solution(const Board& puzzle, const Board& board);

#endif
