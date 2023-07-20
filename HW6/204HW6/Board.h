#ifndef BOARD_H
#define BOARD_H

#include<string>
using namespace std;

class Board
{
	public:
		Board(); // Constructer
		void displayBoard() const; 
		char getOwner(int, int) const;
		void setOwner(int, int, char);
		bool isFull() const;
		int countOwnedCells(char) const;
		
	private:
		char theBoard[2][6];

};
#endif