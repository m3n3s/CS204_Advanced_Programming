#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct element
{
	char letter;
	bool isVisited;
};

void print(const vector<vector<element>> & matrix)
{
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
	// RETURNS MATRIX TO THE ORIGINAL STATE

	for (int j=0; j < m.size(); j++)
    {   
		for (int k=0; k < m[0].size(); k++)
        {   
			m[j][k].isVisited = false;
        }
    }
}

/*

print visitedCoord:

cout << "Found an enclosed area. The coordinates of the followed path: " << endl;

for (int j=0; j < visitedCoord.size() ; j++)
					{   
						for (int k=0; k < visitedCoord[0].size(); k++)
						{   
							cout << setw(4) << visitedCoord[j][k];
						}
						cout << endl;
					}

*/

bool lookRight(int x, int y, vector<vector<element>> & m, vector<vector<int>> visitedCoord)
{
	if(m[x][y+1].letter == 'x' && !m[x][y+1].isVisited)
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

bool lookDown(int x, int y, vector<vector<element>> & m, vector<vector<int>> visitedCoord)
{
	if(m[x+1][y].letter == 'x' && !m[x+1][y].isVisited)
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

bool lookLeft(int x, int y, vector<vector<element>> & m, vector<vector<int>> visitedCoord)
{
	if(m[x][y-1].letter == 'x' && !m[x][y-1].isVisited)
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

bool lookUp(int x, int y, vector<vector<element>> & m, vector<vector<int>> visitedCoord)
{
	if(m[x-1][y].letter == 'x' && !m[x-1][y].isVisited)
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
	vector<vector<int>> visitedCoord;
	int x = sx, y = sy;
	bool found = false;
	vector<int> temp;

	m[x][y].isVisited = true;
	temp.push_back(x);
	temp.push_back(y);

	visitedCoord.push_back(temp); // ADDS STARTING POINT TO VISITED COORDINATES

	while(!found)
	{
		bool occupiedNeighbor = false;

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

		if(x == sx && y == sy && occupiedNeighbor == false && visitedCoord.size() > 1)
			found = true;


		// structtaki bool u stringe çevirip deniycem v5

	}





}



int main()
{
	string filename;
	ifstream inputfile;
	bool flag1 = true;

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

	// READ FILE INTO matrix :

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

	do
	{
		cout << "Please enter starting coordinates, first row X then column Y: ";
		
		

		if(cin >> startX >> startY)
		{

			if(startX == -1 && startY == -1)
				return 0;
			
			
			else if(checkCoord(startX, startY, matrix))
			{
				if(matrix[startX][startY].letter != 'x')
					cout << "This cell is not occupied!" << endl;				

				else 
				{
					enclosedArea(startX, startY, matrix);	// !!!!!!!!!!!!!		

					clean(matrix);					
				}

			}				

		}

		else
		{
			string trash1, trash2;
			
			cin.clear();
			cin >> trash1 >> trash2;

			cout << "Invalid Coordinates" << endl << endl;
			
			// ilk sayý sonra harf girilince çalýþmýyo.
		}

	} while(!(startX == -1 && startY == -1)); 

	cout << "Terminating...";

	return 0;
}