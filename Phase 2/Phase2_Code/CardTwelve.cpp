#include "CardTwelve.h"
#include "Cards9_11.h"

CardTwelve::CardTwelve(const CellPosition& pos) : Card(pos) { cardNumber = 12; }

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	//since it's not mentioned the case in which two players having the same amount of coins(least amount in the game) what should be done 
	//the first player in the list that have the least amount is given the station

	Player* leastPlayer = pGrid->leastPlayer();
	int stationToBeMoved = pPlayer->expensiveStationOwned();

	if (pPlayer == leastPlayer)
		pGrid->PrintErrorMessage("You have the least amount of coins in the game, Card 12 effect is skipped!, click to continue . . .");

	if (pPlayer != leastPlayer) //if the current player is not the player having the least amount of coins in his wallet
	{
		if (stationToBeMoved == 0)
		{
			pGrid->PrintErrorMessage("You don't own any stations, Card 12 effect is skipped!, Click to continue . . .");
			return;
		}

		pGrid->PrintErrorMessage("You should give the ownership of card " + to_string(stationToBeMoved) + " to the Player P" + to_string(leastPlayer->getPlayerNumber()) + "! ");

		pPlayer->removeStation(stationToBeMoved);
		pPlayer->addStation(stationToBeMoved);
		Cards9_11::setOwner(leastPlayer, stationToBeMoved);


		if (stationToBeMoved != 0)
			pGrid->PrintErrorMessage("Now the owner of card " + to_string(stationToBeMoved) + " is the player P" + to_string(leastPlayer->getPlayerNumber()));
	}
}

void CardTwelve::Load(ifstream& Infile,Grid*pGrid)
{
		pGrid->AddObjectToCell(this);
}

void CardTwelve::Save(ofstream& Outfile, Type GOtype)
{
	if (GOtype != CARD)
		return;
	else
	{
		Card::Save(Outfile, GOtype);
		Outfile << endl;
	}
}

