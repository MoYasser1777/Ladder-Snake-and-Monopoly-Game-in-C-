#include "SwitchToPlayModeAction.h"

SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp) :Action(pApp)
{
}

void SwitchToPlayModeAction::ReadActionParameters()
{
	// no parameters to read from user
}

void SwitchToPlayModeAction::Execute()
{
	pManager->GetGrid()->GetOutput()->CreatePlayModeToolBar();
}

SwitchToPlayModeAction::~SwitchToPlayModeAction()
{
}
