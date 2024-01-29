#include "CardThree.h"
#include "Player.h"

CardThree::CardThree(const CellPosition& pos) : Card(pos)
{
	cardNumber = 3;
}
CardThree::~CardThree()
{
}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
   	
	for (int i = 0; i < 3; i++)
	{
		pGrid->AdvanceCurrentPlayer();
    }
	pGrid->PrintErrorMessage("You have an extra dice roll , Click to continue...");
}
void CardThree::Save(ofstream &Outfile, Type GOtype)
{
	if (GOtype != CARD)
		return;
	else
	{
		Card::Save(Outfile, GOtype);
		Outfile << endl;
	}

}
void CardThree::Load(ifstream& Infile, Grid* pGrid)
{
	pGrid->AddObjectToCell(this);
}

