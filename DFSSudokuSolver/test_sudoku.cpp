// FILE: test_sudoku.cpp
// NAME: Gavin McClure-Coleman
// DATE: Nov 11, 2026
// DESC: Unit tests and solution checks for the HW-3 Sudoku solver.
//
// USAGE: ./test_sudoku                       runs the unit tests
//        ./test_sudoku <puzzle> <solution>   checks a solved board

#include <iostream>
#include <stdexcept>
#include <string>
#include "sudoku.h"

// Throws an exception with the given message if condition is false.
void check(bool condition, const std::string& message)
{
  if (!condition)
    throw std::runtime_error(message);
}

// number of unit tests that passed and failed
int passed = 0;
int failed = 0;

// Runs one test, prints PASS or FAIL with its name, and updates the
// counts.
void run_test(const std::string& name, void (*test)())
{
  try {
    test();
    std::cout << "PASS " << name << "\n";
    ++passed;
  }
  catch (const std::exception& e) {
    std::cout << "FAIL " << name << ": " << e.what() << "\n";
    ++failed;
  }
}

// made this helper for creating a valid fully solved board for testing
Board make_valid_solved_board(){
  Board board{};
  for (int r = 0; r < N; ++r){
    for (int c = 0; c < N; ++c){
      board[r][c] = ((r * 3 + r / 3 + c) % 9) + 1;
    }
  }
  return board;
}

//----------------------------------------------------------------------
// Unit tests
//----------------------------------------------------------------------

// example test: any value is legal in any cell of an empty board
void test_is_legal_value_empty_board()
{
  Board board{};   // every cell is 0
  check(is_legal_value(board, 0, 0, 5), "5 should fit in an empty board");
}

// core rule tests

void test_is_legal_value_row(){
  Board board{};
  board[0][0] = 5;
  check(!is_legal_value(board, 0, 4, 5), "5 should be illegal due to a row rule break.");
}

void test_is_legal_value_col(){
  Board board{};
  board[0][0] = 6;
  check(!is_legal_value(board, 4, 0, 6), "6 should be illeal due to a column rule break.");
}

void test_is_legal_value_box(){
  Board board{};
  board[1][1] = 7;
  check(!is_legal_value(board, 2, 2, 7), "7 should be illegal due to a 3x3 box rule break.");
}

void test_solve_simple(){
  Board board{};
  for (int r = 0; r < 9; ++r){
    for (int c = 0; c < 9; ++c){
      board[r][c] = ((r * 3 + r / 3 + c) % 9) + 1;
    }
  }
  board[8][8] = 0;
  board[8][7] = 0;

  check(solve(board, 0, 0), "Solver should solve a nearly complete board");
}

void test_solve_unsolveable(){
  Board board{};
  // fill row 0 with 1 - 8 leaving the final cell open for just 9
  for (int c = 0; c < 8; ++c){
    board[0][c] = c + 1;
  }
  // put 9 in last column in a diff row so that (0,8) has no valid candidates
  board[4][8] = 9;
  check(!solve(board, 0, 0), "Solver should return false for unsolveable board");
}

// read and write unit tests

void test_read_board_missing_file(){
  Board board{};
  check(!read_board("nonexistent_file.txt", board), "read_board should return false for missing file");
}

void test_write_and_read_board_roundtrip(){
  const std::string temp_file = "temp_roundtrip.txt";
  Board original = make_valid_solved_board();
  original[0][0] = 0; // this just adds an empty cell to the board

  check(write_board(temp_file, original), "write_board should succeed");

  Board loaded{};
  check(read_board(temp_file, loaded), "read_board should read written file");
  std::remove(temp_file.c_str());

  check(original == loaded, "loaded board should match written board");
}

// test is_solution
void test_is_solution_valid(){
  Board solved = make_valid_solved_board();
  Board puzzle = solved;
  puzzle[0][0] = 0;
  puzzle[4][4] = 0;
  check(is_solution(puzzle, solved), "Valid solved board should pass is_solution");
}

void test_is_solution_changed_clue(){
  Board solved = make_valid_solved_board();
  Board puzzle = solved;

  puzzle[0][0] = (solved[0][0] % 9) + 1;

  check(!is_solution(puzzle, solved), "Board violating original puzzle clue should fail");
}


//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  // check a solved board against its puzzle
  if (argc == 3) {
    Board puzzle;
    Board board;
    bool ok = read_board(argv[1], puzzle) && read_board(argv[2], board)
      && is_solution(puzzle, board);
    std::cout << (ok ? "PASS " : "FAIL ") << argv[2] << " solves "
              << argv[1] << "\n";
    return ok ? 0 : 1;
  }

  // run the unit tests
  run_test("is_legal_value on an empty board", test_is_legal_value_empty_board);
  run_test("is_legal_value row conflict", test_is_legal_value_row);
  run_test("is_legal_value column conflict", test_is_legal_value_col);
  run_test("is_legal_value box conflict", test_is_legal_value_box);
  run_test("solve nearly complete board", test_solve_simple);
  run_test("read_board missing file", test_read_board_missing_file);
  run_test("write_board and read_board rountrip", test_write_and_read_board_roundtrip);
  run_test("solve unsolvable board", test_solve_unsolveable);
  run_test("is_solution valid board", test_is_solution_valid);
  run_test("is solution modified clue", test_is_solution_changed_clue);

  // print the totals
  std::cout << passed << " passed, " << failed << " failed\n";
  return failed == 0 ? 0 : 1;
}
