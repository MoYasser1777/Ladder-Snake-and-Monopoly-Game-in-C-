#include "CardFour.h"

CardFour::CardFour(const CellPosition& pos) : Card(pos)
{
	cardNumber = 4;
}
CardFour::~CardFour()
{
}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pPlayer->setIsStopped(true);
	pPlayer->setNumOfStops(1);
}
void CardFour::Save(ofstream& Outfile, Type GOtype)
{
	if (GOtype != CARD)
		return;
	else
	{
		Card::Save(Outfile, GOtype);
		Outfile << endl;
	}
}
void CardFour::Load(ifstream& Infile, Grid* pGrid)
{
	pGrid->AddObjectToCell(this);
}