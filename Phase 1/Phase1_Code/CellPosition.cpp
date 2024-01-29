#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}
bool CellPosition::SetVCell(int v)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (v >= 0 && v <= 8)
	{
		vCell = v;
		return true;
	}

	return false; // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (h >= 0 && h <= 10)
	{
		hCell = h;
		return true;
	}

	return false; // this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	///TODO: Implement this function as described in the .h file
	if (vCell == -1 || hCell == -1)
		return false;

	return true; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
	bool b = cellPosition.IsValidCell();
	int cellnum;
	if (b)
	{

		int v, h;
		int term = 100;
		int gridarray[9][11];
		for (int i = 0; i < 9; i++)
		{
			for (int j = 10; j >= 0; j--)
			{
				term--;
				gridarray[i][j] = term;

			}
		}
		v = cellPosition.VCell();
		h = cellPosition.HCell();
		cellnum = gridarray[v][h];
	}
	else
		cellnum = -1;

	return cellnum;   // this line should be changed with your implementation




}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;
	int v, h;
	/// TODO: Implement this function as described in the .h file

	if (cellNum >= 1 && cellNum <= 99)

	{
		int term = 100;
		int gridarray[9][11];
		for (int i = 0; i < 9; i++)
		{
			for (int j = 10; j >= 0; j--)
			{
				term--;
				gridarray[i][j] = term;

			}
		}
		bool found = true;
		for (int i = 0; i < 9; i++)
		{
			int j = 0;

			while (j < 11 && found)
			{

				if (gridarray[i][j] == cellNum)
				{
					v = i;
					h = j;
					found = false;
				}
				j++;


			}
		}
		position.SetVCell(v);
		position.SetHCell(h);
	}



	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum(int addedNum)
{

	/// TODO: Implement this function as described in the .h file

	int cellNum = GetCellNumFromPosition(*this);
	cellNum = cellNum + addedNum;
	(*this) = GetCellPositionFromNum(cellNum);


	// Note: this function updates the data members (vCell and hCell) of the calling object


}