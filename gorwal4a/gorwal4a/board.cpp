#include "board.h"
#include <algorithm>

int numSolutions = 0;

board::board(int sqSize) : value(BoardSize+1,BoardSize+1)
// Board constructor
{
	numIterations = 0;
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
	for(int i=1; i<=BoardSize; i++)
	{	
		for(int j=1; j<=BoardSize; j++)
		{
			if(isBlank(i, j))
				return false;

		}
	}

	return true;
}

void board::updateConflicts(int i, int j, int value, bool set)
{
	conf_rows[i][value] = set;
	conf_cols[j][value] = set;
	conf_sq[squareNumber(i,j)][value] = set;
}

bool board::solve(int i, int j)
{
	numIterations++;
	if( isSolved() )
		return true;

	else
	{
		getNextBlank(&i, &j);

		vector<int> available = getAvailable(i, j);
		int numAvailable = available.size();
		
		if(numAvailable == 0)
			return false;

		for(int x = 0; x < numAvailable; x++)
		{
			int possible = available[x];
			setCell(i, j, possible);
			print();
			if( solve(i, j) )
				return true;

			clearCell(i, j);
			print();
		}
		return false;
		
	}

}

void board::getNextBlank(int *i, int *j)
{
	int tempi, tempj, leastAvailable = 9;


	for(tempi = 1; tempi < 10; tempi++)
	{
		for(tempj = 1; tempj < 10; tempj++)
		{
			if(isBlank(tempi, tempj))
			{
				vector<int> available = getAvailable(tempi, tempj);
				int numAvailable = available.size();
				if( numAvailable < leastAvailable)
				{
					
					
					leastAvailable = numAvailable;
					*i = tempi;
					*j = tempj;
				}
			}
		}
	}
}

vector<int> board::getAvailable(int i, int j)
{
	//Get 3 vectors (row, Col, Sq) with the available numbers for the cell (i, j)
		vector<int> nonConfRow;

		for(int x = 1; x <= BoardSize; x++)
			if(conf_rows[i][x] == false)
				nonConfRow.push_back(x);

		vector<int> nonConfCol;

		for(int x = 1; x <= BoardSize; x++)
			if(conf_cols[j][x] == false)
				nonConfCol.push_back(x);


		vector<int> nonConfSq;
		int square = getSquareNumber(i, j);
		for(int x = 1; x <= BoardSize; x++)
			if(conf_sq[square][x] == false)
				nonConfSq.push_back(x);

		vector<int> available;
		for(int i=1; i<10; i++)
		{
			if( find(nonConfRow.begin(), nonConfRow.end(), i) != nonConfRow.end() )
				if(	find(nonConfCol.begin(), nonConfCol.end(), i) != nonConfCol.end() )
					if(	find(nonConfSq.begin(),  nonConfSq.end(), i)  != nonConfSq.end() )
						available.push_back(i);
		}
		return available;
}

int board::getSquareNumber(int i, int j)
{
	int square;

	if(i <= 3)
	{
		if(j <= 3)
			return 1;

		if (j <= 6)
			return 2;

		if (j <= 9)
			return 3;
	}
	if(i <= 6)
	{
		if(j <= 3)
			return 4;

		if (j <= 6)
			return 5;

		if (j <= 9)
			return 6;
	}
	if(i <= 9)
	{
		if(j <= 3)
			return 7;

		if (j <= 6)
			return 8;

		if (j <= 9)
			return 9;
	}

	return square;
}