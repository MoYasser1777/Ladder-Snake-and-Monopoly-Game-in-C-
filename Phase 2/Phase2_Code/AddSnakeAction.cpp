#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"
#include "Ladder.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) :Action(pApp)
{
}

void AddSnakeAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	if (startPos.IsValidCell() && endPos.IsValidCell())
	{
		//---------------------------------if (this snake overlaps with another snake)-------------------------------------------//

		Snake* S = new Snake(startPos, endPos);
		bool hasNoSnake = S->noOverlap(pGrid);

		//---------------------------------if (the end cell or the start cell of the snake has another ladder)-------------------------------------------//

		bool hasNoLadder = S->noGameObject(pGrid);
		delete S;

		//--------------------------------------- Error Messages -----------------------------------------//

		if (startPos.VCell() > endPos.VCell())
			pGrid->PrintErrorMessage("End cell cannot be higher than start cell, Click to continue . . .");

		else if (startPos.HCell() != endPos.HCell())
			pGrid->PrintErrorMessage("End cell and start cell are not in the same column, Click to continue . . .");

		else if (startPos.VCell() == endPos.VCell())
			pGrid->PrintErrorMessage("End cell and start cell can't hold the same positions, Click to continue . . .");

		else if (!hasNoSnake)
			pGrid->PrintErrorMessage("Two Snakes cannot overlap, Click to continue . . .");

		else if (!hasNoLadder)
			pGrid->PrintErrorMessage("end cell and start cell of two Game Objets can't be the same, Click to continue . . .");

		else if (pGrid->hasCard(&startPos))
			pGrid->PrintErrorMessage("the start Cell of the ladder has a card, Click to continue . . .");

		//-----------------------if (the Snake should not be added -> set the read Parameters to be invalid)-----------------//

		if (pGrid->hasCard(&startPos) || !hasNoSnake || !hasNoLadder || startPos.VCell() > endPos.VCell() || startPos.HCell() != endPos.HCell() || startPos.VCell() == endPos.VCell())
		{
			CellPosition C;
			startPos = C; //making it invalid
		}
	}
	else
		pGrid->PrintErrorMessage("Invalid Cells, Click to continue . . .");

	pOut->ClearStatusBar();

}

void AddSnakeAction::Execute()
{

	ReadActionParameters();

	// Create a Snake object with the parameters read from the user

	Snake* pSnake = new Snake(startPos, endPos);
	pSnake->SetSnakeCount(pSnake->GetSnakeCount() + 1); // increase count of snakes by 1
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Snake Couldn't be added ! Click to continue ...");
	}

}

AddSnakeAction::~AddSnakeAction()
{
}
