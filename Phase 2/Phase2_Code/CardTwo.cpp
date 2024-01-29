#include "CardTwo.h"
#include "Ladder.h"

CardTwo::CardTwo(const CellPosition& pos) : Card(pos) 
{
	cardNumber = 2;
}
CardTwo::~CardTwo()
{
}
void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer); 
	Output* pOut = pGrid->GetOutput();

	cellpos = GetPosition();

	Ladder* nextLadder = pGrid->GetNextLadder(cellpos);

	if (nextLadder !=NULL)
		nextLadder->Apply(pGrid, pPlayer);
	else
		pOut->PrintMessage("There isn't a ladder forward to you");
}
void CardTwo::Save(ofstream& Outfile, Type GOtype)
{
	if (GOtype != CARD)
		return;
	else
	{
		Card::Save(Outfile, GOtype);
		Outfile << endl;
	}
	
}
void CardTwo::Load(ifstream& Infile, Grid* pGrid)
{
	pGrid->AddObjectToCell(this);
}