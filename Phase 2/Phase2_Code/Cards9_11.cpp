#include "Cards9_11.h"

int Cards9_11::price[3]{ 0 };
int Cards9_11::fees[3]{ 0 };
bool Cards9_11::bought[3]{ 0 };
Player* Cards9_11::Owner[3]{ NULL };
int Cards9_11::numOfCard[3]{ 0 };


Cards9_11::Cards9_11(const CellPosition& pos, int cardNum) : Card(pos)
{
	numOfCard[cardNum - 9]++;
}

void Cards9_11::ReadCardParameters(Grid* pGrid, int num) //card index represents the card number in the parameter list but inside the function i will use it as an index
{
	cardNumber = num;
	int cardIndex = num - 9;
	if (numOfCard[cardIndex] == 1) //if it's the first time to place the card on the grid, read its parameters
	{
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();

		pOut->PrintMessage("New Card " + to_string(num) + ": Enter its price ...");
		price[cardIndex] = pIn->GetInteger(pOut);
		if (price[cardIndex] <= 0)
			do {
				pOut->PrintMessage("invalid price: Enter another number ...");
				price[cardIndex] = pIn->GetInteger(pOut);
			} while (price[cardIndex] <= 0);

			pOut->PrintMessage("New Card" + to_string(num) + ":Enter its fees ...");
			fees[cardIndex] = pIn->GetInteger(pOut);
			if (fees[cardIndex] <= 0)
				do {
					pOut->PrintMessage("invalid fees: Enter another number ...");
					fees[cardIndex] = pIn->GetInteger(pOut);
				} while (fees[cardIndex] <= 0);
	}

	(pGrid->GetOutput())->ClearStatusBar();
}

void Cards9_11::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	int buy = 0;
	int x = 0, y = 0;
	int cardIndex = cardNumber - 9;
	if (!bought[cardIndex])
	{
		pOut->PrintMessage("This card makes any other player who stops at the cell containg the card pays you " + to_string(fees[cardIndex]) + " coins!, Click to continue");
		pIn->GetPointClicked(x, y);
		pOut->PrintMessage("Card price is " + to_string(price[cardIndex]) + ", Do you want to buy it? enter \"1\" for Yes, other number for NO");
		buy = pIn->GetInteger(pOut);
		if (buy == 1)
			if (pPlayer->GetWallet() >= price[cardIndex]) //if the player has enough money
			{
				pOut->PrintMessage(to_string(price[cardIndex]) + " coins will be deducted from your wallet, Click to continue . . .");
				pPlayer->SetWallet(pPlayer->GetWallet() - price[cardIndex]);
				bought[cardIndex] = true;
				Owner[cardIndex] = pPlayer;
				pPlayer->addStation(cardNumber);
				pIn->GetPointClicked(x, y);
				pOut->PrintMessage("Now the owner of card " + to_string(cardNumber) + " 's cells is the player P" + to_string((Owner[cardIndex])->getPlayerNumber()) + " !");
				pIn->GetPointClicked(x, y);
			}

			else
			{
				pOut->PrintMessage("You don't have enough money. Selling operation is cancelled, Click to continue . . .");
				pIn->GetPointClicked(x, y);
			}
		else
		{
			pOut->PrintMessage("You refused to buy Card " + to_string(cardNumber) + " cells, Click to continue . . .");
			pIn->GetPointClicked(x, y);
		}
	}
	else if (bought && pPlayer != Owner[cardIndex])
	{
		pOut->PrintMessage("You have to pay the player \"P" + to_string((Owner[cardIndex])->getPlayerNumber()) + "\" " + to_string(fees[cardIndex]) + " coins!, Click to continue . . .");
		pIn->GetPointClicked(x, y);

		if (pPlayer->GetWallet() > fees[cardIndex]) //if he has enough money to pay the fees
		{
			pPlayer->SetWallet(pPlayer->GetWallet() - fees[cardIndex]); //deduct the fees from his wallet
			(Owner[cardIndex])->SetWallet((Owner[cardIndex])->GetWallet() + fees[cardIndex]); //and add the fees coins to the owner's wallet
		}
		else //if he doesn't
		{
			(Owner[cardIndex])->SetWallet((Owner[cardIndex]->GetWallet()) + pPlayer->GetWallet()); //take all the coins he has and add it into the owners wallet
			pPlayer->SetWallet(0); //and set his wallet to zero
		}
	}
	pOut->ClearStatusBar();
}

Player* Cards9_11::getOwner(int cardIndex)
{
	return Owner[cardIndex];
}

int Cards9_11::getPrice(int cardNum)
{
	return price[cardNum - 9];
}

void Cards9_11::setOwner(Player* player, int cardNum)
{
	Owner[cardNum - 9] = player;
}

Cards9_11::~Cards9_11()
{
	Owner[0]->removeStation(9);
	Owner[1]->removeStation(10);
	Owner[2]->removeStation(11);

	Owner[0] = NULL;
	Owner[1] = NULL;
	Owner[2] = NULL;
}



void Cards9_11::Load(ifstream& Infile,Grid*pGrid)
{
	int CardNum, CellNum, Price, Fees, NumberOfCardsInGrid, Bought, Owner;

	for (int i = 0;i < 3;i++)
	{
		Infile >> CardNum >> CellNum >> Price >> Fees >> Bought >> NumberOfCardsInGrid >> Owner;
		pGrid->AddObjectToCell(this);
	}
	
}

void Cards9_11::Save(ofstream& Outfile, Type GOtype)
{
	if (GOtype != CARD)
		return;
	else
	{
		for (int i = 0;i < 3;i++) //info of card 9, then 10, then 11
		{
			Card::Save(Outfile, GOtype);
			Outfile << price[i] << fees[i]; 
		}
	}
}

