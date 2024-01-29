#include "PasteCardAction.h"
#include "Card.h"

PasteCardAction::PasteCardAction(ApplicationManager* pApp) : Action(pApp)
{	                                                                                                                                   
}

PasteCardAction ::~PasteCardAction()
{
}
void PasteCardAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces from Grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	
	pOut->PrintMessage("Paste Card , Click on a cell to paste card : ");
	cardpos= pIn->GetCellClicked();

	//Clear the status bar
	pOut->ClearStatusBar();
}
void PasteCardAction::Execute()
{
	// first read action parameters
	ReadActionParameters();

	// Get a Pointer to the Input / Output Interfaces from Grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	if (pGrid->GetClipboard())
	{
		// get the copied card from clipboard and store it in pCard pointer
		Card* pCard = pGrid->GetClipboard();
		 
		//Change the position of the card
		pCard->setPosition(cardpos);
		

		bool added = pGrid->AddObjectToCell(pCard);
		if (!added)
		{
			pGrid->PrintErrorMessage("Can't paste card , This cell has an object ! click to continue...");
		}
	}
	else
	{
		pGrid->PrintErrorMessage("There isn't a copied card...");
	}
}
