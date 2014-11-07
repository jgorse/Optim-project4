#include "board.h"

int numSolutions = 0;

board::board(int sqSize) : value(BoardSize+1,BoardSize+1)
// Board constructor
{
   clear();
   conf_rows.resize(BoardSize+1,BoardSize+1);
	conf_cols.resize(BoardSize+1,BoardSize+1);
	conf_sq.resize(BoardSize+1,BoardSize+1);
}

void board::clear()
// Mark all possible values as legal for each board entry
{
   for (int i = 1; i <= BoardSize; i++)
      for (int j = 1; j <= BoardSize; j++)
      {
         value[i][j] = Blank;
      }
}

void board::clearCell(int i, int j)
{
	if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in setCell");

   

   updateConflicts(i, j, getCell(i, j), false);
   value[i][j] = Blank;
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   
   for (int i = 1; i <= BoardSize; i++)
      for (int j = 1; j <= BoardSize; j++)
	    {
	       fin >> ch;

          // If the read char is not Blank
	      if (ch != '.')
             setCell(i,j,ch-'0');   // Convert char to int
        }

}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.  

   return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
   for (unsigned int i = 0; i < v.size(); i++)
      ostr << v[i] << " ";
   cout << endl;

   return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in setCell");

   return (getCell(i,j) == Blank);
}

void board::print()
// Prints the current board.
{
	for (int i = 1; i <= BoardSize; i++)
	{
		if ((i-1) % SquareSize == 0)
		{
			cout << " -";
			for (int j = 1; j <= BoardSize; j++)
				cout << "---";
			cout << "-";
			cout << endl;
		}
		for (int j = 1; j <= BoardSize; j++)
		{
			if ((j-1) % SquareSize == 0)
			cout << "|";
			if (!isBlank(i,j))
				cout << " " << getCell(i,j) << " ";
			 else
				cout << "   ";
		}
		cout << "|";
			cout << endl;
	}

	cout << " -";
	for (int j = 1; j <= BoardSize; j++)
		cout << "---";
	cout << "-";
	cout << endl;
}

ValueType board::setCell(int i, int j, int k)
{
	value[i][j] = k;
	updateConflicts(i,j,k,true);
	return value[i][j];
}

void board::printConflicts()
{
	cout<<"\n\n---------Conflict Rows---------------\n";
	for(int i = 1; i <= BoardSize; i++)
	{
		cout<<"-------------------------------------\n";
		for(int j = 1; j <= BoardSize; j++)
		{
			cout<< "| ";

			if(conf_rows[i][j])
				cout<<"T ";
			else
				cout<<"F ";
			
			
		}
		cout<<"|\n";

	}
	cout<<"-------------------------------------\n\n";
	
	cout<<"\n\n---------Conflict Columns------------\n";
	for(int i = 1; i <= BoardSize; i++)
	{
		cout<<"-------------------------------------\n";
		for(int j = 1; j <= BoardSize; j++)
		{
			cout<< "| ";

			if(conf_cols[i][j])
				cout<<"T ";
			else
				cout<<"F ";
			
			
		}
		cout<<"|\n";

	}
	cout<<"-------------------------------------\n\n";

	cout<<"\n\n---------Conflict Squares------------\n";
	for(int i = 1; i <= BoardSize; i++)
	{
		cout<<"-------------------------------------\n";
		for(int j = 1; j <= BoardSize; j++)
		{
			cout<< "| ";

			if(conf_sq[i][j])
				cout<<"T ";
			else
				cout<<"F ";
			
			
		}
		cout<<"|\n";

	}
	cout<<"-------------------------------------\n\n";



}

bool board::isSolved()
{
	//Go through all conflicts

	//Go through matrix
	for(int i=0; i<BoardSize; i++)
	{	
		for(int j=0; j<BoardSize; j++)
		{
			if(isBlank(i, j))
				return false;

			//check conflics
		}
	}
}

void board::updateConflicts(int i, int j, int value, bool set)
{
	conf_rows[i][value] = set;
	conf_cols[j][value] = set;
	conf_sq[squareNumber(i,j)][value] = set;
}