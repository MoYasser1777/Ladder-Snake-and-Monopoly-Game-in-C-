#pragma once
#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "Cards9_11.h"
#include "CardTwelve.h"

AddCardAction::AddCardAction(ApplicationManager* pApp) : Action(pApp), cardNumber(0), cardPosition(-1, -1)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("New Card:Type the card number ...");
	cardNumber = pIn->GetInteger(pOut);

	// 3- Read the "cardPosition" parameter (its cell position) and set its data member

	pOut->PrintMessage("New Card:Click on the card cell . . .");
	cardPosition = pIn->GetCellClicked();

	// 4- Make the needed validations on the read parameters
	bool shouldBeAdded = true;

	//---------------------------------------------------cardNumber validation--------------------------------------------------------//

	if (cardNumber <= 0 || cardNumber > 12)
	{
		pGrid->PrintErrorMessage("invalid cardNumber, Click to continue . . .");
		shouldBeAdded = false;
	}

	//--------------------------------------------------cardPosition validation------------------------------------------------------//

	if (cardPosition.IsValidCell())
	{
		if (!(pGrid->emptyCell(&cardPosition)))
		{
			pGrid->PrintErrorMessage("The card can't be added, the cell has another game object, Click to continue ");
			shouldBeAdded = false;
		}
		else if (cardPosition.GetCellNum() == 1)
		{
			pGrid->PrintErrorMessage("You cannot place a card in the first cell, Click to continue");
			shouldBeAdded = false;
		}
	}
	else if (!(cardPosition.IsValidCell()))
	{
		pGrid->PrintErrorMessage("Invalid Cell, Click to continue . . .");
		shouldBeAdded = false;
	}

	//-----------------------if (the Card should not be added -> set the read Parameters to be invalid)-----------------//
	if (!shouldBeAdded)
	{
		CellPosition C;
		cardPosition = C;
		cardNumber = -1;
	}

	// 5- Clear status bar
	pOut->ClearStatusBar();

}

void AddCardAction::Execute()
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();

	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card* pCard = NULL; // will point to the card object type

	switch (cardNumber)
	{
	case 1:
			pCard = new CardOne(cardPosition);
		break;
	case 2:
			pCard = new CardTwo(cardPosition);
		break;
	case 3:
			pCard = new CardThree(cardPosition);
		break;
	case 4:
			pCard = new CardFour(cardPosition);
		break;
	case 5:
		pCard = new CardFive(cardPosition);
		break;
	case 6:
			pCard = new CardSix(cardPosition);
		break;
	case 7:
			pCard = new CardSeven(cardPosition);
		break;
	case 8:
			pCard = new CardEight(cardPosition);
		break;
	case 9:
	case 10:
	case 11:
		pCard = new Cards9_11(cardPosition, cardNumber);
		break;
	case 12:
		pCard = new CardTwelve(cardPosition);
		break;
	}

	// i moved that line here to be able to print a message if the pCard is NULL (no card is created)
	// A- We get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		//only for the cards that have parameters
		switch (cardNumber)
		{
			case 1:  pCard->ReadCardParameters(pGrid);
			break;
			case 6:  pCard->ReadCardParameters(pGrid);
			break;
			case 8:  pCard->ReadCardParameters(pGrid);
			break;
		case 9:
		case 10:
		case 11:
			pCard->ReadCardParameters(pGrid, cardNumber);
			break;
		}

		// C- Add the card object to the GameObject of its Cell:
		bool added = false;
		added = pGrid->AddObjectToCell(pCard);

		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if (!added)
			pGrid->PrintErrorMessage("Error: Card Couldn't be added ! Click to continue ...");

	}
	else
		pGrid->PrintErrorMessage("Error: Card Couldn't be added ! Click to continue ...");

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}