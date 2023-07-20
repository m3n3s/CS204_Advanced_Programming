#include "Board.h"
#include <iostream>

using namespace std;

Board::Board()
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			theBoard[i][j] = '-';
		}
	}
}

void Board::displayBoard() const
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			cout << theBoard[i][j] << " ";
		}
		cout << endl;
	}
}

char Board::getOwner(int r, int c) const
{
	return theBoard[r][c];
}

void Board::setOwner(int r, int c, char ch)
{
	theBoard[r][c] = ch;
}

bool Board::isFull() const
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			if(theBoard[i][j] == '-')
				return false;
		}
	}
	return true;
}

int Board::countOwnedCells(char ch) const
{
	int count = 0;
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			if(theBoard[i][j] == ch)
				count++;
		}
	}
	return count;
}