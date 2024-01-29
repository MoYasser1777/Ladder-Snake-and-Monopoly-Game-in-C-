#pragma once
#include "Card.h"



// [ CardEight ] Summary:

// Its Apply() Function:The player should choose either to pay specific amount of coins to go out of the prison, or stay in prison and not playing for 3 turns.

// Its Parameters: The amount of coins needed to go out of the prison

class CardEight : public Card
{
	// Parameters:
	static int coinsAmount; // the wallet value to decrease from the player
	static int NumberOfEights;// The number of objects of card Eight

public:
	CardEight(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid, int num = 0); // Reads the parameters of CardEight which is:  coinsAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member
	void Save(ofstream& Outfile, Type GOtype);

	void Load(ifstream& Infile,Grid* pGrid);

	virtual ~CardEight(); // A Virtual Destructor
};



