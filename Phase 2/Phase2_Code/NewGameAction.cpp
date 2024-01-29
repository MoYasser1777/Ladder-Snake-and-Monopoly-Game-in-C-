#include "NewGameAction.h"
#include "Player.h"
#include "Grid.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) :Action(pApp)
{
}

void NewGameAction::ReadActionParameters()
{
}

void NewGameAction::Execute()
{
	pManager->GetGrid()->Resetplayers();
	pManager->GetGrid()->setcurrPlayerNumber(0);
}

NewGameAction::~NewGameAction()
{
}

