#include "InputDiceValueAction.h"
#include "Grid.h"
#include "Player.h"


InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) :Action(pApp)
{
}

void InputDiceValueAction::ReadActionParameters()
{

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the dicevalue parameter
	pOut->PrintMessage("  Enter the Dice value(a number between 1 & 6) ");

	dicevalue = pIn->GetInteger(pOut);
	while (dicevalue < 1 || dicevalue>6)
	{
		pOut->PrintMessage(" invalid Dice value ,please Enter the Dice value(a number between 1 & 6) agian ");

		dicevalue = pIn->GetInteger(pOut);
	}




}

void InputDiceValueAction::Execute()
{

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	bool endgame = pManager->GetGrid()->GetEndGame();


	// -- If not ended, do the following --:
	if (!endgame)

	{
		ReadActionParameters();
		// 2- Get the "current" player from pGrid
		Player* currentPlayer = pManager->GetGrid()->GetCurrentPlayer();

		// 3- Move the currentPlayer using function Move of class player
		currentPlayer->Move(pManager->GetGrid(), dicevalue);


		// 4- Advance the current player number of pGrid
		pManager->GetGrid()->AdvanceCurrentPlayer();
	}
}

InputDiceValueAction::~InputDiceValueAction()
{
}


