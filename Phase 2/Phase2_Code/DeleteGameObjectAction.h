#pragma once
#include "Action.h"
#include "ApplicationManager.h"
#include "Grid.h"

class DeleteGameObjectAction : public Action
{
	CellPosition cellpos;

public:
	DeleteGameObjectAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~DeleteGameObjectAction();
};

