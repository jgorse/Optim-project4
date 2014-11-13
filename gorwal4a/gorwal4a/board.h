// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>


#ifndef BOARD_H
#define BOARD_H

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank
 
const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

class board
// Stores the entire Sudoku board
{
   public:
      board(int);
      void clear();
      void initialize(ifstream &fin);
      void print();
      bool isBlank(int, int);
      ValueType getCell(int, int);
      ValueType setCell(int i, int j, int k);
	  void printConflicts();
	  bool isSolved();
	  void clearCell(int i, int j);
	  void updateConflicts(int i, int j, int value, bool set);
	  bool solve(int i, int j);
	  vector<int> getAvailable(int i, int j);
	  int getSquareNumber(int i, int j);
	  void getNextBlank(int *i, int *j);
	  int numIterations;
   private:

      // The following matrices go from 1 to BoardSize in each
      // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

      matrix<ValueType> value;
	  matrix<bool> conf_rows;
	  matrix<bool> conf_cols;
	  matrix<bool> conf_sq;
};
#endif //BOARD_H

