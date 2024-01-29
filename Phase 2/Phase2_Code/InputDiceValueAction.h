#pragma once


#include "Action.h"

class InputDiceValueAction : public Action
{
	int dicevalue;
public:
	InputDiceValueAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~InputDiceValueAction();
};

