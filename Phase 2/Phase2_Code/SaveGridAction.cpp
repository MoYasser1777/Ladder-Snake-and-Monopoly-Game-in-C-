#include "SaveGridAction.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"

SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{
	
}
void SaveGridAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces from Grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pGrid->PrintErrorMessage("Enter the name of the file to save grid...");
	FileName = pIn->GetSrting(pOut) + ".txt";   //Taking the name of file from the user

	pGrid->PrintErrorMessage("The Grid is saved , Click to continue...");
	//Clearing the status bar
	pOut->ClearStatusBar();
}

void SaveGridAction::Execute()
{
	//first read action parameters
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();

	// Object from ofstream to write in the file
	ofstream SaveGrid(FileName);


	SaveGrid << Ladder::GetLadderCount() << endl;
	pGrid->SaveAll(SaveGrid, LADDER);

	SaveGrid <<Snake::GetSnakeCount() << endl;
	pGrid->SaveAll(SaveGrid, SNAKE);

	SaveGrid << Card::GetCardCount() << endl;
	pGrid->SaveAll(SaveGrid, CARD);

	SaveGrid.close();
}
SaveGridAction::~SaveGridAction()
{

}
