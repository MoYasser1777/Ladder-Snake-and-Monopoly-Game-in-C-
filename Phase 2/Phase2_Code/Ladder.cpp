#include "Ladder.h"
#include "Card.h"
#include "Snake.h"
#include "Grid.h"
#include "CellPosition.h"

int Ladder::LadderCount = 0;

Ladder::Ladder(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;
	///TODO: Do the needed validation
	if (startCellPos.VCell() < endCellPos.VCell() || startCellPos.HCell() != endCellPos.HCell()) //invalid ladder
	{
		CellPosition C;
		position.SetHCell(C.HCell());
		position.SetVCell(C.VCell());
	}

}
void Ladder::SetLadderCount(int LC)
{
	LadderCount = LC;
}

int Ladder::GetLadderCount()
{
	return LadderCount;
}
void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer)
{
	int x = 0, y = 0;
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Output* pOut = pGrid->GetOutput();
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pOut->PrintMessage("You have reached a ladder! Click to continue. . . ");
	// 2- Apply the ladder's effect by moving the player to the endCellPos

	(pGrid->GetInput())->GetPointClicked(x, y);
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	pOut->ClearStatusBar();

	//    Review the "pGrid" functions and decide which function can be used for that
	if (pGrid->hasCard(&endCellPos))
		(pGrid->hasCard(&endCellPos))->Apply(pGrid, pPlayer);
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

bool Ladder::noOverlap(Grid* pGrid)
{
	bool hasNoLadder = true;
	CellPosition LCheck;
	LCheck.SetHCell(position.HCell());
	LCheck.SetVCell(NumVerticalCells - 1);
	int i = 0;

	while (hasNoLadder && i < NumVerticalCells - 1)
	{
		Ladder* L = pGrid->hasLadder(&LCheck);

		if (L)
		{
			int LstartV = (L->GetPosition()).VCell();
			int LendV = (L->endCellPos).VCell();
			if (((position.VCell() <= LstartV) && (position.VCell() >= LendV)) || ((endCellPos.VCell() <= LstartV) && (endCellPos.VCell() >= LendV)) || ((endCellPos.VCell() <= LendV) && (position.VCell() >= LstartV)))
				hasNoLadder = false;
		}

		i++;
		LCheck.SetVCell(NumVerticalCells - i);
	}
	return hasNoLadder;
}

bool Ladder::noGameObject(Grid* pGrid)
{
	bool hasNoSnake = true;
	CellPosition SCheck;
	SCheck.SetHCell(position.HCell());
	SCheck.SetVCell(NumVerticalCells - 1);
	int i = 0;

	while (hasNoSnake && i < NumVerticalCells - 1)
	{
		Snake* S = pGrid->hasSnake(&SCheck);
		if (S)
		{
			if ((S->GetEndPosition()).VCell() == position.VCell())
				hasNoSnake = false;
		}

		i++;
		SCheck.SetVCell(NumVerticalCells - i);
	}

	if ((pGrid->hasSnake(&position)) || (pGrid->hasSnake(&endCellPos)) || !hasNoSnake)
		hasNoSnake = false;

	return hasNoSnake;
}
void Ladder::Save(ofstream& Outfile, Type GOtype)
{
	if (GOtype != LADDER)
		return;
	else
		Outfile << (GetPosition().GetCellNumFromPosition(GetPosition())) << " " << (GetPosition().GetCellNumFromPosition(GetEndPosition())) << endl;
}
void Ladder::Load(ifstream& Infile , Grid*pGrid)
{
	int StartCellNum, EndCellNum;
	Infile >> StartCellNum >> EndCellNum;
	GameObject* pLadder = new Ladder(CellPosition(StartCellNum), CellPosition(EndCellNum));

	pGrid->AddObjectToCell(pLadder);
}
Ladder::~Ladder()
{
}
