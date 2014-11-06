#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "board.h"

using namespace std;

int main()
{
	ifstream fin;
   
	// Read the sample grid from the file.
	string fileName = "sudoku1.txt";

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		board b1(SquareSize);

		while (fin && fin.peek() != 'Z')
		{
			b1.initialize(fin);
			b1.print();
			b1.printConflicts();

			cout<<"\n\nTest: remove the '8' in the first row, then update and print board/conflicts\n";
			b1.clearCell(1, 5);
			b1.print();
			b1.printConflicts();
		}
	}
	catch  (indexRangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}

	system("pause");
}