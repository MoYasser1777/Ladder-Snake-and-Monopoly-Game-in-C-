#include "CardSeven.h"


CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (7 here)
}

CardSeven::~CardSeven()
{
}



void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{



	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);

	//2-print a message explains the card to the user
	pGrid->PrintErrorMessage("This Card Restarts the game for the first player whose cell is after the current player in the grid,click to continue ...");

	// 3- Get the the first player whose cell is after the current player in the grid.
	Player* NextPlayer = pGrid->GetNextPlayer(pPlayer, pPlayer->GetCell()->GetCellPosition());
	//4-Restarting the game for the next player( makes him go to cell number 1).
	if (NextPlayer != NULL)
	{
		CellPosition Firstcell(NumVerticalCells - 1, 0);
		pGrid->UpdatePlayerCell(NextPlayer, Firstcell);
	}




}
void CardSeven::Save(ofstream Outfile, Type GOtype)
{
	if (GOtype != CARD)
		return;
	else
	{
		Card::Save(Outfile, GOtype);
		Outfile << endl;
	}
}
void CardSeven::Load(ifstream& Infile, Grid* pGrid)
{
	pGrid->AddObjectToCell(this);
}
