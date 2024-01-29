#include "OpenGridAction.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "Cards9_11.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"



OpenGridAction::OpenGridAction(ApplicationManager* pApp) : Action(pApp)
{
}
void OpenGridAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces from Grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pGrid->PrintErrorMessage("Enter the name of the file to load grid...");
	FileName = pIn->GetSrting(pOut) + ".txt";

	pOut->ClearStatusBar();
}
void OpenGridAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();

	pGrid->ClearAll();

	ifstream OpenGrid(FileName);

	if (OpenGrid.is_open())
	{
		int NumOfLadders;
		OpenGrid >> NumOfLadders;

		for (int i = 0; i < NumOfLadders; i++)
		{
			Ladder::Load(OpenGrid, pGrid);
		}

		int  NumOfSnakes;
		OpenGrid >> NumOfSnakes;

		for (int i = 0; i < NumOfSnakes; i++)
		{
			Snake::Load(OpenGrid, pGrid);
		}

		int  cardnum;
		OpenGrid >> cardnum;
		Card* pCard = NULL;
		for (int i = 0; i < cardnum; i++)
		{
			int num, cellnum;
			OpenGrid >> num >> cellnum;
			switch (num)
			{
			case 1:
				pCard = new CardOne(CellPosition(cellnum));
				pCard->Load(OpenGrid, pGrid);
				break;
			case 2:
				pCard = new CardTwo(CellPosition(cellnum));
				pCard->Load(OpenGrid, pGrid);
				break;
			case 3:
				pCard = new CardThree(CellPosition(cellnum));
				pCard->Load(OpenGrid, pGrid);
				break;
			case 4:
				pCard = new CardFour(CellPosition(cellnum));
				pCard->Load(OpenGrid, pGrid);
				break;
			case 5:
				pCard = new CardFive(CellPosition(cellnum));
				pCard->Load(OpenGrid, pGrid);
				break;
			case 6:
				pCard = new CardSix(CellPosition(cellnum));
				pCard->Load(OpenGrid, pGrid);
				break;
			case 7:
				pCard = new CardSeven(CellPosition(cellnum));
				pCard->Load(OpenGrid, pGrid);
				break;
			case 8:
				pCard = new CardEight(CellPosition(cellnum));
				pCard->Load(OpenGrid, pGrid);
				break;
			case 9:
			case 10:
			case 11:
				pCard = new Cards9_11(CellPosition(cellnum),cellnum);
				pCard->Load(OpenGrid, pGrid);
				break;
			case 12:
				pCard = new CardTwelve(CellPosition(cellnum));
				pCard->Load(OpenGrid, pGrid);
				break;
			}
		}

	}
}
	OpenGridAction::~OpenGridAction()
	{
	}


