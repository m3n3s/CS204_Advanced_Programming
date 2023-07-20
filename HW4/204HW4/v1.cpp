#include <iostream> 
#include <fstream>
#include <string>
#include "DynStack.h"

using namespace std;

// MAINI FONKSIYONLARA BOLDUM -> v2.cpp

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

void readFile(char** dmatrix)
{
	
}

int main()
{
	int rows, cols;

	getRowsCols(rows, cols);

	ifstream input;
	string filename;

	do
	{
		cout << "Please enter file name: ";
		cin >> filename;

		input.open(filename);

		if (input.fail())
			cout << "Cannot find a file named " << filename << endl;

	}while(input.fail());

	/* Begin: code taken from matrix.cpp and updated */ 
 	
	//Two dimensional dynamic array creation
	string** dmatrix = new string*[rows];

	for(int i =0; i<rows; i++)
	{
		dmatrix[i] = new string[cols];
	}
	/* End: code taken from matrix.cpp and updated */ 


	while(!input.eof()) // READ THE FILE INTO 2-DIMENTIONAL DYNAMIC ARRAY
	{
		static int rowCount = 0;
		string line;
		getline(input, line);

		for(int c = 0; c < line.length(); c++)
		{
			dmatrix[rowCount][c] = line[c];
		}

		rowCount ++;

	}

	input.close();

	//// PRINT MATRIX
	//for(int i=0; i<rows; i++)
	//{
	//	for(int j=0; j<cols; j++)
	//	{
	//		cout << dmatrix[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	
	// GET THE STARTING COORDINATES

	bool valid = false;
	int startRow, startCol;

	do
	{
		cout << "Enter the starting point: ";

		if(cin >> startRow && startRow >= 0 && startRow <= rows)
		{
			if(cin >> startCol && startCol >= 0 && startCol <= cols)
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

	cout << startRow << "     " << startCol;

	// IF THE STARTING POINT IS NOT EMPTY TERMINATE THE PROGRAM
	if (dmatrix[startRow][startCol] != ' ')
	{
		cout << "Starting point is already occupied." << endl;
		cout << "Terminating..." << endl;
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

	// FILLING PART

	int currentRow = startRow;
	int currentCol = startCol;
	bool filled = false;
	DynStack myStack;

	myStack.push(currentRow, currentCol);

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
			int R, C;
			myStack.pop(R, C);
		}

		if(myStack.isEmpty())
			filled = true;
	}
	

	// DONT FORGET TO DELETE DYNAMICALLY ALLOCATED MEMORY
	return 0;
}