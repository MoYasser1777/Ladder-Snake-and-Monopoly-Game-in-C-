#include "CardEight.h"



int CardEight::coinsAmount = 0;
int CardEight::NumberOfEights = 0;
CardEight::CardEight(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 8; // set the inherited cardNumber data member with the card number (8 here)
	NumberOfEights++;
}
CardEight::~CardEight()
{

}


void CardEight::ReadCardParameters(Grid* pGrid, int num)
{


	if (NumberOfEights == 1)
	{
		// 1- Get a Pointer to the Input / Output Interfaces from the Grid

		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		// 2- Read an Integer from the user using the Input class and set the coinsAmount parameter with it

		pOut->PrintMessage("New card Eight:Enter the coins amount :");

		coinsAmount = pIn->GetInteger(pOut);


		// 3- Clear the status bar
		pOut->ClearStatusBar();
	}

}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{



	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- ask the player to pay or not to play for 3 turns

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("You are in prison ,Enter 0 to pay " + to_string(coinsAmount) + " or 1 to stop playing for 3 turns ");

	int choise = pIn->GetInteger(pOut);
	if (choise != 0 && choise != 1)
	{
		while (choise != 0 && choise != 1)
		{
			pOut->PrintMessage("invalid choise please,Enter 0 to pay " + to_string(coinsAmount) + " or 1 to stop playing for 3 turns ");

			choise = pIn->GetInteger(pOut);
		}
	}
	if (choise == 0)//pay
	{
		int wallet = pPlayer->GetWallet();
		if (coinsAmount <= wallet)
			pPlayer->SetWallet(wallet - coinsAmount);
		else
			choise = 1;

	}
	if (choise == 1)//stop palying for 3 turns
	{

		pPlayer->setIsStopped(true);
		pPlayer->setNumOfStops(3);

	}
	pOut->ClearStatusBar();


}
void CardEight::Save(ofstream& Outfile, Type GOtype)
{
	if (GOtype != CARD)
		return;
	else
	{
		Card::Save(Outfile, GOtype);
		Outfile << coinsAmount << endl;
	}
}
void CardEight::Load(ifstream& Infile, Grid* pGrid)
{
	int cA;
	Infile >> cA;
	coinsAmount = cA;
	pGrid->AddObjectToCell(this);
}