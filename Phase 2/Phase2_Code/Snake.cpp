#include "Snake.h"
#include "Card.h"
#include "Ladder.h"

int Snake::SnakeCount = 0;


Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) :GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation

	if (startCellPos.VCell() > endCellPos.VCell() || startCellPos.HCell() != endCellPos.HCell()) //invalid snake
	{
		CellPosition C;
		position.SetHCell(C.HCell());
		position.SetVCell(C.VCell());
	}
}

void Snake::SetSnakeCount(int SC)
{
	SnakeCount = SC;
}

int Snake::GetSnakeCount()
{
	return SnakeCount;
}
void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{
	int x = 0, y = 0;
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("You have reached a snake! Click to continue. . . ");
	(pGrid->GetInput())->GetPointClicked(x, y);
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	pOut->ClearStatusBar();

	if (pGrid->hasCard(&endCellPos))
		(pGrid->hasCard(&endCellPos))->Apply(pGrid, pPlayer);
}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

bool Snake::noOverlap(Grid* pGrid)
{

	CellPosition SCheck;
	SCheck.SetHCell(position.HCell());
	SCheck.SetVCell(NumVerticalCells - 1);
	bool hasNoSnake = true;
	int i = 0;

	while (hasNoSnake && i < NumVerticalCells - 1)
	{
		Snake* S = pGrid->hasSnake(&SCheck);
		if (S)
		{
			int SstartV = (S->GetPosition()).VCell();
			int SendV = (S->GetEndPosition()).VCell();
			if (((position.VCell() >= SstartV) && (position.VCell() <= SendV)) || ((endCellPos.VCell() >= SstartV) && (endCellPos.VCell() <= SendV)) || ((endCellPos.VCell() >= SendV) && (position.VCell() <= SstartV)))
				hasNoSnake = false;
		}
		i++;
		SCheck.SetVCell(NumVerticalCells - i);
	}
	return hasNoSnake;
}

bool Snake::noGameObject(Grid* pGrid)
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
			if ((L->GetEndPosition()).VCell() == position.VCell())
				hasNoLadder = false;
		}

		i++;
		LCheck.SetVCell(NumVerticalCells - i);
	}

	if ((pGrid->hasLadder(&position)) || (pGrid->hasLadder(&endCellPos)) || !hasNoLadder)
		hasNoLadder = false;

	return hasNoLadder;
}
void Snake::Save(ofstream& Outfile, Type GOtype)
{
	if (GOtype != SNAKE)
		return;
	else
		Outfile << (GetPosition().GetCellNumFromPosition(GetPosition())) << " " << (GetPosition().GetCellNumFromPosition(GetEndPosition())) << endl;
}
void Snake::Load(ifstream& Infile,Grid*pGrid)
{
	int StartCellNum, EndCellNum;
	Infile >> StartCellNum >> EndCellNum;
	GameObject* pSnake = new Snake(CellPosition(StartCellNum), CellPosition(EndCellNum));

	pGrid->AddObjectToCell(pSnake);
}
Snake::~Snake()
{
}

