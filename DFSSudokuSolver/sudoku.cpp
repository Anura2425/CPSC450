// FILE: sudoku.cpp
// NAME: Gavin McClure-Coleman
// DATE: Nov 11, 2026
// DESC: Function definitions for the HW-3 Sudoku solver.

#include <fstream>
#include "sudoku.h"

bool read_board(const std::string& filename, Board& board)
{
  std::ifstream file(filename);
  if (!file.is_open()){
    return false;
  }

  for(int r = 0; r < N; ++r){
    for(int c = 0; c < N; ++c){
      if (!(file >> board[r][c])){
        return false;
      }
    }
  }
  return true;
}

bool write_board(const std::string& filename, const Board& board)
{
  std::ofstream file(filename);
  if (!file.is_open()){
    return false;
  }

  for(int r = 0; r < N; ++r){
    for(int c = 0; c < N; ++c){
      file << board[r][c] << (c == N - 1 ? "" : " "); // f
    }
    file << "\n";
  }
  return true;
}

bool is_legal_value(const Board& board, int row, int col, int value)
{
  // checks row and column rules
  for (int i = 0; i < N; ++i){
    if (board[row][i] == value) return false;
    if (board[i][col] == value) return false;
  }

  // check subgrid constraing (3x3 areas)
  int box_row_start = (row/3) * 3;
  int box_col_start = (col/3) * 3;

  for (int r = box_row_start; r < box_row_start + 3; ++r){
    for (int c = box_col_start; c < box_col_start + 3; ++c){
      if (board[r][c] == value) return false;
    }
  }

  return true;
}

bool solve(Board& board, int row, int col)
{
  
  // base case: if row reaches N we have reached the end of the board (fully filled so its solved)
  if (row == N){
    return true;
  }

  // find next cell coords 
  int next_row = (col == N - 1) ? row + 1 : row;
  int next_col = (col == N - 1) ? 0 : col + 1;
  
  // recursive call to proceed if the cell alr is filled
  if (board[row][col] != 0){
    return solve(board, next_row, next_col);
  }

  // attempt candidates 1-9 (try placing)
  for (int val = 1; val <= 9; ++val){
    if (is_legal_value(board, row, col, val)){
      board[row][col] = val;

      // recurse to solve the rest of the board (keep going deeper because dfs)
      if (solve(board, next_row, next_col)){
        return true;
      }

      // backtrack if deadend
      board[row][col] = 0;
    }
  }

  return false;
}

bool is_solution(const Board& puzzle, const Board& board)
{
  // verify all initial numbered cells match the solved board and that cells contain valid 1-9 numbers
  for(int r = 0; r < N; ++r){
    for(int c = 0; c < N; ++c){
      if (puzzle[r][c] != 0 && puzzle[r][c] != board[r][c]){
        return false;
      }
      if (board[r][c] < 1 || board[r][c] > 9){
        return false;
      }
    }
  }

  // check rows and columns to make sure that all digits in them are unique (no doubled up same numbers in the same row/col)
  for (int i = 0; i < N; ++i){
    bool seen_row[10] = {false};
    bool seen_col[10] = {false};
    for (int j = 0; j < N; ++j){
      int row_val = board[i][j];
      if(seen_row[row_val]) return false;
      seen_row[row_val] = true;

      int col_val = board[j][i];
      if (seen_col[col_val]) return false;
      seen_col[col_val] = true;
    }
  }

  // check all 3x3 sub grid boxes for unique digits aswell
  for (int box_row = 0; box_row < 3; ++box_row){
    for (int box_col = 0; box_col < 3; ++box_col){
      bool seen_box[10] = {false};
      for(int r = 0; r < 3; ++r){
        for(int c = 0; c < 3; ++c){
          int val = board[box_row * 3 + r][box_col * 3 + c];
          if (seen_box[val]) return false;
          seen_box[val] = true;
        }
      }
    }
  }

  return true;
}
