#pragma once

#include "Card.h"
#include "SaveGridAction.h"

// [ CardOne ] Summary:
// Its Apply() Function: Decrements the value of the passing player�s wallet by a value
// Its Parameters: The Wallet Value to decrease --> put it as a "data member" and read it in ReadCardParameters()

class CardOne :	public Card
{
	// CardOne Parameters:
	static int walletAmount; // the wallet value to decrease from the player

public:
	CardOne(const CellPosition & pos); // A Constructor takes card position


	virtual void ReadCardParameters(Grid * pGrid , int num=0); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	                                                  // by decrementing the player's wallet by the walletAmount data member
	
	void Save(ofstream &Outfile, Type GOtype);

	void Load(ifstream& Infile, Grid* pGrid);

	virtual ~CardOne(); // A Virtual Destructor
};

