#pragma once

#include "CardSix.h"


int CardSix::CellToMove = 0;
int CardSix::NumberOfSix = 0;

CardSix::CardSix(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (6 here)
	NumberOfSix++;
}

CardSix::~CardSix(void)
{
}

void CardSix::ReadCardParameters(Grid* pGrid, int num)
{


	if (NumberOfSix == 1)
	{
		// 1- Get a Pointer to the Input / Output Interfaces from the Grid

		Input* pIn = pGrid->GetInput();
		Output* pOut = pGrid->GetOutput();


		// 2- Reads the Cell data member from the user
		pOut->PrintMessage("Enter the Cell number that the player will move to");
		CellToMove = pIn->GetInteger(pOut);

		if (CellToMove < 1 || CellToMove>99 || CellToMove == position.GetCellNum())
		{
			while (CellToMove < 1 || CellToMove>99 || CellToMove == position.GetCellNum())
			{
				pOut->PrintMessage("invalid cell, please Enter the cell number again");
				CellToMove = pIn->GetInteger(pOut);
			}

		}




		// 3- Clear the status bar
		pOut->ClearStatusBar();
	}

}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{



	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);

	//2-print a message explains the card to the user

	pGrid->PrintErrorMessage("This Card moves you to cell " + to_string(CellToMove) + ",click to continue ...");

	// 3- Move the current player to the cell
	Player* currentplayer = pGrid->GetCurrentPlayer();
	CellPosition NewPosition = CellPosition::GetCellPositionFromNum(CellToMove);
	pGrid->UpdatePlayerCell(currentplayer, NewPosition);
	//4-checks if the cell has a gameobject (if yes ,take it)
	if (currentplayer->GetCell()->GetGameObject())
	{

		currentplayer->GetCell()->GetGameObject()->Apply(pGrid, currentplayer);

	}




}
void CardSix::Save(ofstream& Outfile, Type GOtype)
{
	if (GOtype != CARD)
		return;
	else
		Outfile << cardNumber << " " << GetPosition().GetCellNumFromPosition(GetPosition()) << " " << CellToMove << endl;
}
void CardSix::Load(ifstream& Infile, Grid* pGrid)
{
	int c;
	Infile >> c;
	CellToMove = c;
	pGrid->AddObjectToCell(this);
}