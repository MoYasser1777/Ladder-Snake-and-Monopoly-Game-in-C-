#include "CardFive.h"
#include "Snake.h"
#include "Ladder.h"

CardFive::CardFive(const CellPosition& pos) : Card(pos)
{
	cardNumber = 5;
}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pGrid->PrintErrorMessage("You should move backward " + to_string(pPlayer->getJustRolledDiceNum()) + " steps! Click to Move. . .");
	int moveBackward = -1 * (pPlayer->getJustRolledDiceNum());

	CellPosition toCell(1);

	if (((pPlayer->GetCell())->GetCellPosition()).GetCellNum() < -moveBackward)
		pGrid->UpdatePlayerCell(pPlayer, toCell); //if he is in a cell number less than the number of cells he should move, make him go to the very first cell
	else
	{
		//moving the player to the new cell

		toCell = ((pPlayer->GetCell())->GetCellPosition()).GetCellNum() + moveBackward;
		pGrid->UpdatePlayerCell(pPlayer, toCell);

		//if that cell has a game object, take it
		if (pGrid->hasCard(&toCell))
			(pGrid->hasCard(&toCell))->Apply(pGrid, pPlayer);
		else if (pGrid->hasLadder(&toCell))
			(pGrid->hasLadder(&toCell))->Apply(pGrid, pPlayer);
		else if (pGrid->hasSnake(&toCell))
			(pGrid->hasSnake(&toCell))->Apply(pGrid, pPlayer);
	}

}

CardFive::~CardFive()
{
}



void CardFive::Load(ifstream& Infile, Grid* pGrid)
{
	pGrid->AddObjectToCell(this);
}

void CardFive::Save(ofstream& Outfile, Type GOtype)
{
	if (GOtype != CARD)
		return;
	else
	{
		Card::Save(Outfile, GOtype);
		Outfile << endl;
	}


}

