#pragma once
#include "Card.h"
class CardFour : public Card
{
public:
	CardFour(const CellPosition& pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
    void Save(ofstream &Outfile, Type GOtype);
	void Load(ifstream& Infile, Grid*pGrid);
	virtual ~CardFour();
};


