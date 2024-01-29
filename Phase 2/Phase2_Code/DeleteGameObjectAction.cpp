#include "DeleteGameObjectAction.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{

}
DeleteGameObjectAction::~DeleteGameObjectAction()
{

}
void DeleteGameObjectAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces from Grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Delete Game Object , Click on a object to delete it : ");

	// Object from CellPosition Class has the cell position of the cell clicked from thr user
	cellpos = pIn->GetCellClicked();

	//Clear the status bar
	pOut->ClearStatusBar();
}
void DeleteGameObjectAction::Execute()
{
	// first read action parameters
	ReadActionParameters();

	// Get a Pointer to the Output Interface from Grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	//Check if the cell has object or not
	if (pGrid->emptyCell(&cellpos))
		pOut->PrintMessage("This Cell has no object");
	else
	{
		pGrid->RemoveObjectFromCell(cellpos);
		pOut->PrintMessage("Object is deleted");
	}
}
