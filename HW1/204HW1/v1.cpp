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
		return false;

}

bool foundEncArea(int sx, int sy, vector<vector<element>> & m, vector<vector<int>> & visitedCoord)
{

	int x = sx, y = sy;
	bool found = false;
	vector<int> temp;

	temp.push_back(x);
	temp.push_back(y);

	visitedCoord.push_back(temp); // ADD THE STARTING POINT

	while(!found && (0 < x && x < m.size()) && (0 <= y && y < m[0].size()))
	{
		vector<int> temp;
		/*
		if(m[x][y].letter == 'x' && !m[x][y].isVisited)
		{
			// START POINT
			temp.push_back(x);
			temp.push_back(y);

			visitedCoord.push_back(temp);
		}
		*/

		if(m[x][y+1].letter == 'x' && !m[x][y+1].isVisited)
		{
			// LOOK RIGHT
			// x = x;
			y = y+1;

			m[x][y].isVisited = true;
			temp.push_back(x);
			temp.push_back(y);

			visitedCoord.push_back(temp);
		}

		else if(m[x+1][y].letter == 'x' && !m[x+1][y].isVisited)
		{
			// LOOK DOWN
			x = x+1;
			// y = y;

			m[x][y].isVisited = true;
			temp.push_back(x);
			temp.push_back(y);

			visitedCoord.push_back(temp);
		}

		else if(m[x][y-1].letter == 'x' && !m[x][y-1].isVisited)
		{
			// LOOK LEFT
			// x = x;
			y = y-1;

			m[x][y].isVisited = true;
			temp.push_back(x);
			temp.push_back(y);

			visitedCoord.push_back(temp);
		}

		// x = 0 ken sýkýntý çýkýyo
		else if(m[x-1][y].letter == 'x' && !m[x-1][y].isVisited)
		{
			// LOOK UP
			x = x-1;
			// y = y;

			m[x][y].isVisited = true;
			temp.push_back(x);
			temp.push_back(y);

			visitedCoord.push_back(temp);
		}

		else if(x == sx && y == sy && visitedCoord.size() != 0) // size() to eliminate the only x condition.
			found == true;

	}

	return found;
	/*
	if(!found)
		return false;
	
	return true;
	*/
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
				vector<vector<int>> visitedCoord;

				if(matrix[startX][startY].letter != 'x')
					cout << "This cell is not occupied!" << endl;
				

				else if(foundEncArea(startX, startY, matrix, visitedCoord)) // write this func !!!!
				{
					cout << "Found an enclosed area. The coordinates of the followed path: " << endl;
					
					for (int j=0; j < visitedCoord.size(); j++)
					{   
						for (int k=0; k < visitedCoord[0].size(); k++)
						{   
							cout << setw(4) << matrix[j][k].letter;
						}
						cout << endl;
					}
					
				}

			}				

		}



		else
		{
			string trash1, trash2;
			
			cin.clear();
			cin >> trash1 >> trash2;

			cout << "Invalid Coordinates" << endl;
			
			// ilk sayý sonra harf girilince çalýþmýyo.
		}

	} while(!(startX == -1 && startY == -1)); // çýkýþ þartýný koyarsýn

	return 0;
}