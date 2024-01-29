#pragma once
#include "Action.h"
#include "ApplicationManager.h"
#include <fstream>
#include "DEFS.h"
class OpenGridAction : public Action
{
	string FileName;
public:

	OpenGridAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~OpenGridAction();
};

