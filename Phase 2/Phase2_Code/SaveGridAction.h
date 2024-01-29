#pragma once
#include "Action.h"
#include"ApplicationManager.h"
#include "DEFS.h"
#include <fstream>
class SaveGridAction : public Action
{
	string FileName;
public:

	SaveGridAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~SaveGridAction();
};

