#pragma once
#include "Card.h"

class CardTwelve : public Card
{
public:
	CardTwelve(const CellPosition& pos);
	void Apply(Grid* pGrid, Player* pPlayer);
	void Save(ofstream& Outfile, Type GOtype);
    void Load(ifstream& Infile,Grid*pGrid);
	
};


