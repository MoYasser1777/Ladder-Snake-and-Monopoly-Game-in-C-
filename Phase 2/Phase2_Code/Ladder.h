#pragma once

#include "GameObject.h"
#include "SaveGridAction.h"
#include "DEFS.h"

class Ladder : public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"
	static int LadderCount;
	CellPosition endCellPos; // here is the ladder's End Cell Position

public:

	Ladder(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization
	void SetLadderCount(int LC);
	static int GetLadderCount();

	virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to ladder's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member

	bool noOverlap(Grid* pGrid);

	bool noGameObject(Grid* pGrid);

	void Save(ofstream& Outfile, Type GOtype);

	static void Load(ifstream& Infile,Grid* pGrid);

	virtual ~Ladder(); // Virtual destructor
};

