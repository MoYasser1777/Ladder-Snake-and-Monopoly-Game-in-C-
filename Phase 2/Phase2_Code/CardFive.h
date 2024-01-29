#pragma once
#include "Card.h"

class CardFive : public Card
{
public:
	CardFive(const CellPosition& pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual ~CardFive();

	void Load(ifstream& Infile, Grid*pGrid);

	void Save(ofstream& Outfile, Type GOtype);

};

