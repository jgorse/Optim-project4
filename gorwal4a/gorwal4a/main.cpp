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
	ifstream fin, fin2, fin3;
   
	// Read the sample grid from the file.
	string fileName1 = "sudoku1.txt";
	string fileName2 = "sudoku2.txt";
	string fileName3 = "sudoku3.txt";

	fin.open(fileName1.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName1 << endl;
		exit(1);
	}


	board b1(SquareSize);

	while (fin && fin.peek() != 'Z')
	{
		b1.initialize(fin);
		b1.solve(1, 1);
		b1.print();
		cout<<"This took "<<b1.numIterations<<" calls to solve()\n\n";

	}
	/************************************************************************/
	fin2.open(fileName2.c_str());
	if (!fin2)
	{
		cerr << "Cannot open " << fileName2 << endl;
		exit(1);
	}


	board b2(SquareSize);

	while (fin2 && fin2.peek() != 'Z')
	{
		b2.initialize(fin2);
		b2.solve(1, 1);
		b2.print();
		cout<<"This took "<<b2.numIterations<<" calls to solve()\n\n";

	}


	/************************************************************************/
	fin3.open(fileName3.c_str());
	if (!fin3)
	{
		cerr << "Cannot open " << fileName3 << endl;
		exit(1);
	}


	board b3(SquareSize);

	while (fin3 && fin3.peek() != 'Z')
	{
		b3.initialize(fin3);
		b3.solve(1, 1);
		b3.print();
		cout<<"This took "<<b3.numIterations<<" calls to solve()\n\n";

	}
	

	cout<<"Total recursive calls for all 3 puzzles: "<<b1.numIterations + b2.numIterations + b3.numIterations<<endl;
	cout<<"Average number of recursive calls: "<< (b1.numIterations + b2.numIterations + b3.numIterations) / 3 <<endl;

	system("pause");
}