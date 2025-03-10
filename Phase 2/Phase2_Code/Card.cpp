#include "Card.h"

int Card::CardCount = 0;

Card::Card(const CellPosition & pos) : GameObject(pos) // sets the cell position of the GameObject
{
	CardCount++;
}
Card::Card()
{

}
int Card::GetCardCount()
{
	return CardCount;
}
void Card::SetCardNumber(int cnum)
{
	if (cnum > 0 && cnum < 13)
		cardNumber = cnum; // needs validation
	else
	cardNumber = 0;
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(position, cardNumber);
}

void Card::ReadCardParameters(Grid* pGrid, int num)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

void Card::Save(ofstream& Outfile, Type GOtype)
{
	if (GOtype != CARD)
		return;
	else
	Outfile << cardNumber << " " << GetPosition().GetCellNumFromPosition(GetPosition()) << " ";
	
}
void Card:: Load(ifstream& Infile, Grid*pGrid)
{
	
}
Card::~Card()
{
}