#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

using namespace std;

class Player
{
	public:
		Player(Board &b, char idChar, int direction); // Constructer
		void move(int);
		void claimOwnership();
		bool wins() const;
		int getRow() const;
		int getCol() const;

	private:
		Board &myBoard;
		char id;
		int currentRow;
		int currentColumn;
		int dir;

};
#endif