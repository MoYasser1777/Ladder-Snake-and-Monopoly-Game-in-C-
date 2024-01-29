#include "Player.h"

#include "GameObject.h"
#include "Cards9_11.h"

Player::Player(Cell* pCell, int playerNum) :stepCount(1), wallet(100), playerNum(playerNum)
{

	this->pCell = pCell;

	this->turnCount = 0;

	// Make all the needed initialization or validations
	IsStopped = false;
	NumOfStops = 0;
	CountOfStops = 0;
	numOfstationOwned = 0;
	stationsOwned[0] = 0;
	stationsOwned[1] = 0;
	stationsOwned[2] = 0;
}

// ====== Setters and Getters ======

void Player::SetCell(Cell* cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	if (wallet >= 0)
		this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

void Player::setIsStopped(bool Stopped)
{
	IsStopped = Stopped;
}



void Player::setNumOfStops(int num)
{
	NumOfStops = num;
}

void Player::setstepCount(int step)
{
	stepCount = step;
}

int Player::getJustRolledDiceNum()
{
	return justRolledDiceNum;
}

int Player::getPlayerNumber() const
{
	return playerNum;
}





void Player::SetturnCount(int turncount)
{
	if (turncount >= 0 && turncount <= 3)
		this->turnCount = turncount;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];



	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	turnCount++;
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (turnCount == 3)
	{
		pGrid->PrintErrorMessage("This is your third turn,your wallet will incresese " + to_string(10 * diceNumber) + " click to continue ...");

		wallet += 10 * diceNumber;
		turnCount = 0;
		return;


	}
	if (!IsStopped)
	{
		if (wallet > 0)//The player can only move if there is at least 1 coin in his wallet

		{// 3- Set the justRolledDiceNum with the passed diceNumber
			justRolledDiceNum = diceNumber;
			// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
			//    Using the appropriate function of CellPosition class to update "pos"
			CellPosition pos = pCell->GetCellPosition();

			if (pos.GetCellNum() + diceNumber <= NumVerticalCells * NumHorizontalCells)
			{
				pos.AddCellNum(diceNumber);


				pGrid->PrintErrorMessage("you got " + to_string(diceNumber) + " click to move ...");


				// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
				//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
				pGrid->UpdatePlayerCell(this, pos);
				stepCount = pos.GetCellNum();

				// 6- Apply() the game object of the reached cell (if any)

				if (pCell->GetGameObject())
				{

					pCell->GetGameObject()->Apply(pGrid, this);

				}


				// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)

				if (pCell->GetCellPosition().GetCellNum() == NumVerticalCells * NumHorizontalCells)
				{
					pGrid->SetEndGame(true);

					pGrid->GetOutput()->PrintMessage("Player " + to_string(playerNum) + " is the winner ");
				}
			}

			else
			{
				pGrid->PrintErrorMessage("you got " + to_string(diceNumber) + ", you cannot move ,click to continue ...");

			}
		}
		else
		{
			pGrid->PrintErrorMessage("your wallet is empty,you cannot move ,click to continue");
		}
	}
	else if (NumOfStops == 1)//if the player is stopped for 1 turn 
	{
		pGrid->PrintErrorMessage("you are stopped ,click to continue...");

		IsStopped = false;
		NumOfStops = 0;
	}
	else//if the player is stopped for 3 turns(prison)
	{
		pGrid->PrintErrorMessage("you are stopped ,click to continue...");

		CountOfStops++;
		if (CountOfStops == 3)
		{
			IsStopped = false;
			NumOfStops = 0;
			CountOfStops = 0;


		}
	}

}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

void Player::addStation(int num)
{
	if (num > 8 && num < 12) //station cards
	{
		stationsOwned[numOfstationOwned] = num;
		numOfstationOwned++;
	}
}

bool Player::removeStation(int num)
{
	for (int i = 0; i < numOfstationOwned; i++)
		if (stationsOwned[i] == num)
		{
			stationsOwned[i] = 0;
			numOfstationOwned--;
			return true; //he owns the station and now it's removed
		}
	return false; //he doesn't own the station
}

Player* Player::compareWallet(Player* anotherPlayer)
{
	if (wallet < anotherPlayer->wallet)
		return this;
	return anotherPlayer;
}

int Player::expensiveStationOwned()
{
	int cardNum = 0;
	int highestPrice = 0;

	for (int i = 0; i < numOfstationOwned; i++)
	{
		int price = Cards9_11::getPrice(stationsOwned[i]);
		if (price > highestPrice)
		{
			highestPrice = price;
			cardNum = stationsOwned[i];
		}
	}
	return cardNum; // (9 / 10 / 11) and if he doesn't own any stations, returns 0
}
