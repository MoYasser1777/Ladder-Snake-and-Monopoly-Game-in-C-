#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "Snake.h"

AddLadderAction::AddLadderAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	///TODO: Make the needed validations on the read parameters

	//should i force the user to click on the grid or should i just end the operation if he clicked on an invalid one?
	// and if i should force him, how can i end the operation if he decided to? is there any function or icon that could cancle the operation?
	//f the following bolock of code should be implemented, the if condition after the block must be removed and just keep what's inside the if block
	/*if(!startPos.IsValidCell() || !endPos.IsValidCell())
		do
		{
			pOut->PrintMessage("Invalid Cells, Click on a cell in the grid itself . . .");

			pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
			startPos = pIn->GetCellClicked();

			pOut->PrintMessage("New Ladder: Click on its End Cell ...");
			endPos = pIn->GetCellClicked();
		} while (!startPos.IsValidCell() || !endPos.IsValidCell());*/

	if (startPos.IsValidCell() && endPos.IsValidCell())
	{
		//---------------------------------if (this ladder overlaps with another ladder)-------------------------------------------//

		Ladder* L = new Ladder(startPos, endPos);
		bool hasNoLadder = L->noOverlap(pGrid);

		//---------------------------------if(the end cell or the start cell of this ladder has another snake)-------------------------------------------------------//

		bool hasNoSnake = L->noGameObject(pGrid);
		delete L;

		//--------------------------------------- Error Messages -----------------------------------------//

		if (startPos.VCell() < endPos.VCell())
			pGrid->PrintErrorMessage("End cell cannot be lower than the start cell, Click to continue . . .");

		else if (startPos.HCell() != endPos.HCell())
			pGrid->PrintErrorMessage("End cell and start cell are not in the same column, Click to continue . . .");

		else if (startPos.VCell() == endPos.VCell())
			pGrid->PrintErrorMessage("End cell and start cell of a ladder can't be on the same cell, Click to continue . . .");

		else if (!hasNoSnake)
			pGrid->PrintErrorMessage("end cell and start cell of two Game Objets can't be the same, Click to continue . . .");

		else if (!hasNoLadder)
			pGrid->PrintErrorMessage("Two ladders cannot overlap, Click to continue . . .");

		else if (startPos.GetCellNum() == 1)
			pGrid->PrintErrorMessage("You cannot place a ladder in the first cell, Click to continue . . .");

		else if (pGrid->hasCard(&startPos))
			pGrid->PrintErrorMessage("the start Cell of the ladder has a card, Click to continue . . .");

		//-----------------------if (the Ladder should not be added -> set the read Parameters to be invalid)-----------------//

		if (pGrid->hasCard(&startPos) || startPos.HCell() != endPos.HCell() || !hasNoLadder || !hasNoSnake || startPos.GetCellNum() == 1 || startPos.VCell() < endPos.VCell() || startPos.HCell() != endPos.HCell() || startPos.VCell() == endPos.VCell())
		{
			CellPosition C;
			startPos = C; //making it invalid
		}
	}
	else
		pGrid->PrintErrorMessage("Invalid Cells, Click to continue . . .");

	// Clear messages
	pOut->ClearStatusBar();
}

// Execute the action
void AddLadderAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user

	Ladder* pLadder = new Ladder(startPos, endPos);

	pLadder->SetLadderCount(pLadder->GetLadderCount() + 1); // increase count of ladders by 1

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (!added)
	{
		pGrid->RemoveObjectFromCell(pLadder->GetPosition());
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Ladder Couldn't be added ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
