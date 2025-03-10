#pragma once
#include "Action.h"
class AddSnakeAction : public Action
{
	CellPosition startPos; // 1- The start position of the snake
	CellPosition endPos;   // 2- The end position of the snake

public:
	AddSnakeAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~AddSnakeAction();
};


