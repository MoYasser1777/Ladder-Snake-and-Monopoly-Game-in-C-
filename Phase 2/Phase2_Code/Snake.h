#pragma once
#include "GameObject.h"
#include "SaveGridAction.h"
#include "DEFS.h"
class Snake : public GameObject
{
	static int SnakeCount;
	CellPosition endCellPos;
public:
	Snake(const CellPosition& startCellPos, const CellPosition& endCellPos);
	
	void SetSnakeCount(int SC);
	static int GetSnakeCount();
	virtual void Draw(Output* pOut) const;
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	CellPosition GetEndPosition() const;
	bool noOverlap(Grid* pGrid);
	bool noGameObject(Grid* pGrid);
	void Save(ofstream& Outfile, Type GOtype);
	static void Load(ifstream& Infile, Grid* pGrid);
	virtual ~Snake();
};
