#pragma once
#include "Action.h"
#include "ApplicationManager.h"


class PasteCardAction : public Action
{
	CellPosition cardpos;

public:

	PasteCardAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~PasteCardAction();
};

