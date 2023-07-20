#include <iostream> 
#include <fstream>
#include <string>
#include "DynStack.h"

using namespace std;

// MEHMET ENES BATTAL - HW4

void getRowsCols(int & r, int & c)
{
	bool flag1 = false, flag2 = false;

	do
	{
		cout << "Enter the number of rows: ";
		if(cin >> r)
		{
			if(r > 2)
			{				
				// ASK FOR COLS
				flag1 = true;

				do
				{
					cout << "Enter the number of columns: ";
					if(cin >> c)
					{
						if(c > 2)
							flag2 = true;

						else
							cout << c << " is not valid!" << endl;
					}

					else
					{
						cin.clear();
			
						string s1;
						getline(cin,s1);

						cout << s1 << " is not valid!" << endl;
					}

				}while(!flag2);
			}

			else
				cout << r << " is not valid!" << endl;
		}

		else
		{
			cin.clear();
			
			string s1;
			getline(cin,s1);

			cout << s1 << " is not valid!" << endl;
		}

	}while(!flag1);
}

void readFile(string** dmatrix)
{
	ifstream input;
	string filename;

	do
	{
		cout << "Please enter file name: ";
		cin >> filename;

		input.open(filename);

		if (input.fail())
			cout << "Cannot open a file named " << filename << endl;

	}while(input.fail());

	int rowCount = 0;

	while(!input.eof()) // READ THE FILE INTO 2-DIMENTIONAL DYNAMIC ARRAY
	{
		string line;
		getline(input, line);

		for(int c = 0; c < line.length(); c++)
		{
			dmatrix[rowCount][c] = line[c];
		}

		rowCount ++;
	}

	input.close();
}

void fillingFunc(string** dmatrix, const int & startRow, const int & startCol, const string & fillingChar)
{
	// FILLING PART

	int currentRow = startRow;
	int currentCol = startCol;
	bool filled = false;
	DynStack myStack;

	// FILL THE STARTING POINT
	myStack.push(currentRow, currentCol);
	dmatrix[currentRow][currentCol] = fillingChar;

	while(!filled)
	{
		if(dmatrix[currentRow][currentCol+1] == " ")
		{
			currentCol++;
			myStack.push(currentRow, currentCol);
			dmatrix[currentRow][currentCol] = fillingChar;
		}

		else if(dmatrix[currentRow+1][currentCol] == " ")
		{
			currentRow++;
			myStack.push(currentRow, currentCol);
			dmatrix[currentRow][currentCol] = fillingChar;
		}
		
		else if(dmatrix[currentRow][currentCol-1] == " ")
		{
			currentCol--;
			myStack.push(currentRow, currentCol);
			dmatrix[currentRow][currentCol] = fillingChar;
		}
		
		else if(dmatrix[currentRow-1][currentCol] == " ")
		{
			currentRow--;
			myStack.push(currentRow, currentCol);
			dmatrix[currentRow][currentCol] = fillingChar;
		}
		
		else
		{
			int pR, pC, s1, s2;
			myStack.pop(s1, s2); // POPS THE CURRENT LOCATION

			if(!myStack.isEmpty()) // IF STACK IS EMPTY IT MEANS THE FILLING IS COMPLETE
			{
				myStack.pop(pR, pC); // POPS THE PREVIOUS LOCATION TO UPDATE THE CURRENT LOCATION BY ACCESSING COORDINATES
				currentRow = pR;
				currentCol = pC;
				myStack.push(pR, pC); // PUSHES THE PREVIOUS LOCATION BACK BECAUSE IT ALREADY POPPED THE CURRENT LOCATION
			}
		}

		if(myStack.isEmpty())
			filled = true;
	}
}

void DeleteMatrix(string ** dmatrix, int rows)
{
	for(int i=0; i<rows; i++)
	{
		delete [] dmatrix[i];
	}
	delete [] dmatrix;
}

int main()
{
	int rows, cols;

	getRowsCols(rows, cols);

	/* Begin: code taken from matrix.cpp and updated */ 
 	
	//Two dimensional dynamic array creation
	string** dmatrix = new string*[rows];

	for(int i =0; i<rows; i++)
	{
		dmatrix[i] = new string[cols];
	}

	/* End: code taken from matrix.cpp and updated */ 

	readFile(dmatrix);
	
	// GET THE STARTING COORDINATES	
	int startRow, startCol;
	bool valid = false;
	
	do
	{
		cout << "Enter the starting point: ";

		if(cin >> startRow && startRow >= 0 && startRow < rows)
		{
			if(cin >> startCol && startCol >= 0 && startCol < cols)
				valid = true;

			else
			{
				cout << "Invalid coordinate!" << endl;
				cin.clear();
				string s1;
				getline(cin,s1);
			}

		}

		else
		{
			cout << "Invalid coordinate!" << endl;
			cin.clear();
			string s1;
			getline(cin,s1);
		}
		
	}while(!valid);	

	// IF THE STARTING POINT IS NOT EMPTY TERMINATE THE PROGRAM
	if (dmatrix[startRow][startCol] != " ")
	{
		cout << "Starting point is already occupied." << endl;
		cout << "Terminating..." << endl;
		DeleteMatrix(dmatrix, rows);
		return 0;
	}

	string fillingChar;
	bool validFill = false;

	do
	{
		cout << "Enter the filling char: ";		
		cin >> fillingChar;

		if (fillingChar == "X" || fillingChar == "x")
			cout << "Filling char is not valid!" << endl;

		else
			validFill = true;

	}while(!validFill);

	fillingFunc(dmatrix, startRow, startCol, fillingChar);

	// PRINTS THE DYNAMIC MATRIX
	cout << endl;
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			cout << dmatrix[i][j] << " ";
		}
		cout << endl;
	}

	DeleteMatrix(dmatrix, rows);

	return 0;
}