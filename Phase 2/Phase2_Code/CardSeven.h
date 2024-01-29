#pragma once
#include "Card.h"

// [ CardSeven ] Summary:
// Its Apply() Function: Restarts the game for the first player whose cell is after the current player in the grid.
//(Restarting the game for a player makes him go to cell number 1).
// Its Parameters: no parameters
class CardSeven : public Card
{

public:
	CardSeven(const CellPosition& pos); // A Constructor takes card position


	virtual void Apply(Grid* pGrid, Player* pPlayer);
	 void Save(ofstream Outfile, Type GOtype);
	void Load(ifstream& Infile, Grid*pGrid);
	virtual ~CardSeven(); // A Virtual Destructor
};

