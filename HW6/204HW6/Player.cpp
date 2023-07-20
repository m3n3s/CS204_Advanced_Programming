#include "Player.h"
#include "Board.h"

using namespace std;

Player::Player(Board &b, char idChar, int direction)
	: myBoard(b), 
	id(idChar),
	dir(direction),
	currentRow(0),
	currentColumn(0)
{}

void Player::move(int a)
{
	int move = 0;

	if(dir == 1) // Clockwise
	{
		while(move < a)
		{
			if(currentRow == 0 && currentColumn == 0)
				currentColumn++;

			else if(currentRow == 0 && currentColumn == 5)
				currentRow++;

			else if(currentRow == 1 && currentColumn == 5)
				currentColumn--;

			else if(currentRow == 1 && currentColumn == 0)
				currentRow--;

			else if(currentRow == 0)
				currentColumn++;

			else if(currentRow == 1)
				currentColumn--;

			move++;
		}

	}

	else if(dir == 0) // Counter-clockwise
	{
		while(move < a)
		{
			if(currentRow == 0 && currentColumn == 0)
				currentRow++;

			else if(currentRow == 0 && currentColumn == 5)
				currentColumn--;

			else if(currentRow == 1 && currentColumn == 5)
				currentRow--;

			else if(currentRow == 1 && currentColumn == 0)
				currentColumn++;

			else if(currentRow == 0)
				currentColumn--;

			else if(currentRow == 1)
				currentColumn++;

			move++;
		}
	}
}

void Player::claimOwnership()
{
	if(myBoard.getOwner(currentRow, currentColumn) == '-')
		myBoard.setOwner(currentRow, currentColumn, id);
}

bool Player::wins() const
{
	if(myBoard.countOwnedCells(id) > 6)
		return true;
	return false;
}

int Player::getRow() const
{
	return currentRow;
}

int Player::getCol() const
{
	return currentColumn;
}