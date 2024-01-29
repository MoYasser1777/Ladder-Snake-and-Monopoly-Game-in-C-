#include "Card.h"
#include"Cell.h"

// [ CardSix ] Summary:
// Its Apply() Function: Instructs the player to go to a specific cell.If the destination cell contains a ladder, snake, or card, take it. 
// Its Parameters: Cell to move to

class CardSix : public Card
{
	// CardSix Parameters:
	static int CellToMove;// the cell number that the player will move to
	static int NumberOfSix;

public:
	CardSix(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid, int num = 0); // Reads the parameters of CardSix which is: CellToMove

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	void Save(ofstream &Outfile, Type GOtype);
	void Load(ifstream& Infile, Grid* pGrid);
	virtual ~CardSix(); // A Virtual Destructor
};
