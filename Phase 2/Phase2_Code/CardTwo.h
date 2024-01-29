#pragma once
#include "Card.h"

class CardTwo : public Card
{
	CellPosition cellpos;
public:
	CardTwo(const CellPosition& pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	void Save(ofstream& Outfile, Type GOtype);
	void Load(ifstream& Infile, Grid* pGrid);
	virtual ~CardTwo();
};

