#pragma once
#include "Card.h"
class Cards9_11 : public Card
{
	// [0]-> CardNine, [1]-> CardTen, [2]-> CardEleven
	static int price[3];
	static int fees[3];
	static bool bought[3]; //to check if the card's been already sold to a certain player
	static int numOfCard[3]; //to check if the readParameters's been called previously or not for each card
	static Player* Owner[3];  //to know which player should we increase his wallet when a certain player stands in this cell
public:
	Cards9_11(const CellPosition& pos, int cardNum);
	virtual void ReadCardParameters(Grid* pGrid, int num = 0);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	Player* getOwner(int cardIndex);
	static int getPrice(int cardNum);
	static void setOwner(Player* player, int cardNum);
	virtual ~Cards9_11();

		void Load(ifstream& Infile,Grid*pGrid);
		void Save(ofstream& Outfile, Type GOtype);
};
