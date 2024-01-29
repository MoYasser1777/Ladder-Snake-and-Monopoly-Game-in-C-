#pragma once
#include "Action.h"
#include "ApplicationManager.h"
#include "Grid.h"

class CutCardAction : public Action
	{
		CellPosition cellpos;
		Card* pCard;

	public:

		CutCardAction(ApplicationManager * pApp);

		virtual void ReadActionParameters();

		virtual void Execute();

		virtual ~CutCardAction();
	};

