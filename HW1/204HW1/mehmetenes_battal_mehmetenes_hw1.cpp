#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

// MEHMET ENES BATTAL - HW1

struct element
{
	char letter;
	bool  isVisited;
};

void print(const vector<vector<element>> & matrix)
{
	// PRINTS THE CONTENTS OF THE MATRIX THAT IS READ FROM FILE

	for (int j=0; j < matrix.size(); j++)
    {   
		for (int k=0; k < matrix[0].size(); k++)
        {   
			cout << setw(4) << matrix[j][k].letter;
        }
        cout << endl;
    }
}

int inputCheck(const vector<vector<element>> & m, string file)
{
	// CHECKS IF THE MATRIX IN THE FILE HAS INVALID CHARACTERS 

	for (int j=0; j < m.size(); j++)
    {   
		for (int k=0; k < m[0].size(); k++)
        {   
			if ((m[j][k].letter != 'x') && (m[j][k].letter != 'o'))
			{
				cout << file << " includes invalid char(s)" << endl;
				return 0;
			}

        }
    }

	// CHECKS IF ALL OF THE ROWS HAS THE SAME AMOUNT OF ELEMENTS

	for (int i=0; i < m.size() ; i++)
	{
		if (m[i].size() != m[0].size())
		{
			cout << file << " is invalid matrix, does not contain same amount of char each row!" << endl;
			return 0;
		}
	}

	return 1;
}

bool checkCoord(int x, int y, const vector<vector<element>> & m)
{
	// CHECKS IF THE ENTERED COORDINATES ARE VALID

	if((0 <= x && x < m.size()) && (0 <= y && y < m[0].size()))
		return true;
	else
	{
		cout << "Invalid Coordinates" << endl << endl;
		return false;
	}

}

void clean(vector<vector<element>> & m)
{
	// RETURNS MATRIX TO THE ORIGINAL STATE AFTER OPERATION

	for (int j=0; j < m.size(); j++)
    {   
		for (int k=0; k < m[0].size(); k++)
        {   
			m[j][k].isVisited = false;
        }
    }
}

bool lookRight(int & x, int & y, vector<vector<element>> & m, vector<vector<int>> & visitedCoord)
{
	// CHECKS IF THE RIGHT OF THE CURRENT ELEMENT IS OCCUPIED AND NOT VISITED

	if(m[x][y+1].letter == 'x' && m[x][y+1].isVisited == false)
	{
		vector<int> temp;
		y = y+1;

		m[x][y].isVisited = true;
		temp.push_back(x);
		temp.push_back(y);

		visitedCoord.push_back(temp);
		return true;
	}
	return false;
}

bool lookDown(int & x, int & y, vector<vector<element>> & m, vector<vector<int>> & visitedCoord)
{
	// CHECKS IF THE DOWN OF THE CURRENT ELEMENT IS OCCUPIED AND NOT VISITED

	if(m[x+1][y].letter == 'x' && m[x+1][y].isVisited == false)
	{
		vector<int> temp;
		x = x+1;

		m[x][y].isVisited = true;
		temp.push_back(x);
		temp.push_back(y);

		visitedCoord.push_back(temp);
		return true;
	}
	return false;
}

bool lookLeft(int & x, int & y, vector<vector<element>> & m, vector<vector<int>> & visitedCoord)
{
	// CHECKS IF THE LEFT OF THE CURRENT ELEMENT IS OCCUPIED AND NOT VISITED

	if(m[x][y-1].letter == 'x' && m[x][y-1].isVisited == false)
	{
		vector<int> temp;
		y = y-1;

		m[x][y].isVisited = true;
		temp.push_back(x);
		temp.push_back(y);

		visitedCoord.push_back(temp);
		return true;
	}
	return false;
}

bool lookUp(int & x, int & y, vector<vector<element>> & m, vector<vector<int>> & visitedCoord)
{
	// CHECKS IF THE UP OF THE CURRENT ELEMENT IS OCCUPIED AND NOT VISITED

	if(m[x-1][y].letter == 'x' && m[x-1][y].isVisited == false)
	{
		vector<int> temp;

		x = x-1;
	
		m[x][y].isVisited = true;
		temp.push_back(x);
		temp.push_back(y);
	
		visitedCoord.push_back(temp);
		return true;
	}
	return false;
}

void enclosedArea(int sx, int sy, vector<vector<element>> & m)
{
	// FINDS THE ENCLOSED AREA IF THERE IS ONE

	vector<vector<int>> visitedCoord;
	int x = sx, y = sy;
	bool found = false, flag = false; 
	vector<int> temp;

	m[x][y].isVisited = true;
	temp.push_back(x);
	temp.push_back(y);

	visitedCoord.push_back(temp); // ADDS STARTING POINT TO VISITED COORDINATES
	
	while(!flag)
	{
		bool occupiedNeighbor = false;	

		// THERE ARE 9 CASES OF PLACES WHERE AN ELEMENT MAY BE SO I HAD TO 
		// CHECK EACH CASE

		if(x == 0 && y == 0) // TOP LEFT CORNER
		{
			if(lookRight(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookDown(x, y, m, visitedCoord))
				occupiedNeighbor = true;
		}

		else if(x == 0 && y == m[0].size()-1) // TOP RIGHT CORNER
		{
			if(lookDown(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookLeft(x, y, m, visitedCoord))
				occupiedNeighbor = true;
		}

		else if(x == m.size()-1 && y == m[0].size()-1) // BOTTOM RIGHT CORNER
		{
			if(lookLeft(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookUp(x, y, m, visitedCoord))
				occupiedNeighbor = true;
		}

		else if(x == m.size()-1 && y == 0) // BOTTOM LEFT CORNER
		{
			if(lookRight(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookUp(x, y, m, visitedCoord))
				occupiedNeighbor = true;
		}

		else if(x == 0) // TOP SIDE
		{
			if(lookRight(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookDown(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookLeft(x, y, m, visitedCoord))
				occupiedNeighbor = true;
		}

		else if(x == m.size()-1) // BOTTOM SIDE
		{
			if(lookRight(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookLeft(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookUp(x, y, m, visitedCoord))
				occupiedNeighbor = true;
		}

		else if(y == 0) // LEFT SIDE
		{
			if(lookRight(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookDown(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookUp(x, y, m, visitedCoord))
				occupiedNeighbor = true;
		}

		else if(y == m[0].size()-1) // RIGHT SIDE
		{
			if(lookDown(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookLeft(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookUp(x, y, m, visitedCoord))
				occupiedNeighbor = true;
		}

		else // MIDDLE OF THE MATRIX
		{
			if(lookRight(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookDown(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookLeft(x, y, m, visitedCoord))
				occupiedNeighbor = true;
			else if(lookUp(x, y, m, visitedCoord))
				occupiedNeighbor = true;
		}

		// AFTER EACH ITERATION I CHECK IF THERE IS AN OCCUPIED NEIGHBOR
		// IF THERE IS NOT IT MEANS THAT THE LOOP SHOULD END

		if(!occupiedNeighbor && sqrt((x-sx)*(x-sx)+(y-sy)*(y-sy)) == 1 && visitedCoord.size() > 2)
		{
			// SINCE THE STARTING POINT IS ALSO MARKED AS VISITED WHEN AN ENCLOSED AREA FORMS,
			// CURRENT ELEMENT WON'T BE THE SAME AS THE STARTING POINT BUT THE COORDINATE DISTANCE BETWEEN THEM
			// WILL ALWAYS BE 1. THATS WHY I USED SQRT() FUNCTION FROM <CMATH>. AND SINCE THE SMALLEST ENCLOSED
			// AREA WILL CONSIST 4 COORDINATES, THE THIRD CONDITIONS IS A SAFETY CHECK AND IT ELIMINATES
			// THE CASE WHEN THERE IS ONLY ONE OCCUPIED CELL.

			flag = true;
			found = true;
		}
		else if(!occupiedNeighbor)
			flag = true;		
	}

	if(found)
	{
		// WHEN AN ENCLOSED AREA IS FOUND IT IS DISPLAYED AS WELL AS THE VISITED COORDINATES TO FORM THAT AREA.

		cout << "Found an enclosed area. The coordinates of the followed path: " << endl;

		for (int j=0; j < visitedCoord.size() ; j++)
		{   
			for (int k=0; k < visitedCoord[0].size(); k++)
			{   
				cout << setw(4) << visitedCoord[j][k];
			}
			cout << endl;
		}
	}

	else
	{
		// IF THERE IS NO ENCLOSED AREA FOUND IT DISPLAYS

		cout << "Cannot found an enclosed area starting with given coordinate. The " << endl << "coordinates of the followed path: " << endl;
		
		for (int j=0; j < visitedCoord.size() ; j++)
		{   
			for (int k=0; k < visitedCoord[0].size(); k++)
			{   
				cout << setw(4) << visitedCoord[j][k];
			}
			cout << endl;
		}
	}

}



int main()
{
	string filename;
	ifstream inputfile;
	bool flag1 = true;

	// TAKES THE FILE NAME AND CHECKS IF IT IS VALID

	do
	{
		cout << "Please enter file name: ";
		cin >> filename;

		inputfile.open(filename);

		if (inputfile.fail()){
			cout << "Cannot find a file named " << filename << endl;
			flag1 = false;
		}
		else
			flag1 = true;

	}while(!flag1);

	// IF IT IS VALID IT IS READ INTO A MATRIX.

	vector<vector<element>> matrix;
	string line;

	while( !inputfile.eof())
	{
		getline(inputfile, line);

		stringstream  ss(line);		
		element box;
		vector<element> temp;

		while(ss >> box.letter)
		{
			box.isVisited = false;
			temp.push_back(box);
		}

		matrix.push_back(temp);		
	}

	if(inputCheck(matrix, filename) == 0)
		return 0;
	cout << "Input Matrix: " << endl;
	print(matrix);

	int startX, startY;
	bool flag2 = true; // can delete

	// TAKES THE COORDINATES FROM THE USER AND DISPLAYS THE RESULT.

	do
	{
		cout << "Please enter starting coordinates, first row X then column Y: ";		

		if(cin >> startX >> startY)
		{
			if(startX == -1 && startY == -1)
			{
				cout << "Terminating..." << endl;
				return 0;
			}
						
			else if(checkCoord(startX, startY, matrix))
			{
				if(matrix[startX][startY].letter != 'x')
					cout << "This cell is not occupied!" << endl << endl;				

				else 
				{
					enclosedArea(startX, startY, matrix);
					clean(matrix);					
				}

			}				

		}

		else
		{
			// IF THERE IS AN INVALID COORDINATES IT CLEARS THE CIN.
			string trash1, trash2;
			
			cin.clear();
			cin >> trash1 >> trash2;

			cout << "Invalid Coordinates" << endl << endl;
		}

	} while(true); 

	return 0;
}