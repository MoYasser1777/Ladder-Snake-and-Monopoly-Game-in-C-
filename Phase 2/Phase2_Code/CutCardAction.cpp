#include "CutCardAction.h"

CutCardAction::CutCardAction(ApplicationManager* pApp) : Action(pApp)
{
	
}

CutCardAction ::~CutCardAction()
{
}

void CutCardAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces from Grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Cut Card , Click on a card to cut it : ");

	// Object from CellPosition Class has the cell position of the cell clicked from thr user
	cellpos = pIn->GetCellClicked();

	// Pointer from Card Class has a card if the clicked cell has a card , and this pointer is equal to NULL if the clicked cell doesn't have a card
	pCard = pGrid->hasCard(&cellpos);

	//Clear the statusbar
	pOut->ClearStatusBar();
}
void CutCardAction::Execute()
{
	// First read action parameters
	ReadActionParameters();

	// Get a Pointer to Grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	// Check if the cell clicked has a card or not
	if (pCard == NULL)
		pOut->PrintMessage("This cell has no card");

	else
	{
		// Set the clipboard to the cutted card and delete card from the cell
		pGrid->SetClipboard(pCard);
		pOut->PrintMessage("Card is cutted");
		pGrid->RemoveObjectFromCell(cellpos);
	}
}
