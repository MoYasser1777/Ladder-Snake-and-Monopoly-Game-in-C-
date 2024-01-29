#include "SwitchToDesignModeAction.h"

SwitchToDesignModeAction::SwitchToDesignModeAction(ApplicationManager* pApp) :Action(pApp)
{
}

void SwitchToDesignModeAction::ReadActionParameters()
{
	// no parameters to read from user
}

void SwitchToDesignModeAction::Execute()
{
	pManager->GetGrid()->GetOutput()->CreateDesignModeToolBar();
	pManager->GetGrid()->ClearAll();

}

SwitchToDesignModeAction::~SwitchToDesignModeAction()
{
}
