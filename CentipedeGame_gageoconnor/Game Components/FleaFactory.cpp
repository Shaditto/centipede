/* FleaFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "FleaFactory.h"
#include "Flea.h"

#include "ScoreManager.h"
#include "SoundManager.h"

#include "CommandScore.h"
#include "CommandSound.h"

FleaFactory *FleaFactory::pInstance = nullptr;

FleaFactory::FleaFactory()
{
	// These commands are created once only and reused every time this game object is active
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::FleaDeath);
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::FleaSnd);
}

void FleaFactory::privateCreateFlea(Grid *pGrid)
{
	Flea* flea;
	spawnLoc = rand() % RAND_CHANCE; // Grab a random location to spawn Flea

	if (recycledFleas.empty())
	{
		ConsoleMsg::WriteLine("New Flea");

		flea = new Flea();

		// Object will return here instead of being destroyed
		flea->SetExternalManagement(recycleFlea);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Flea");

		flea = recycledFleas.top();
		recycledFleas.pop();

		// Register back to scene
		flea->RegisterToCurrentScene();
	}
	flea->Initialize(pGrid->getArr(SPAWN_LOC, spawnLoc));
}

void FleaFactory::privateRecycleFlea(GameObject *flea)
{
	recycledFleas.push((Flea*)flea);
	ConsoleMsg::WriteLine("Recycled Flea Size: " + Tools::ToString(recycledFleas.size()));
}

void FleaFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void FleaFactory::ReportDeath()
{
	ConsoleMsg::WriteLine("Flea Factory: Sending death score command\n");
	ScoreManager::SendScoreCommand(Instance().pDeath);
}

void FleaFactory::PlaySound()
{
	ConsoleMsg::WriteLine("Flea Sound: Sending flea sound command\n");
	SoundManager::SendSoundCommand(Instance().pSound);
}

FleaFactory::~FleaFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Fleas (" + Tools::ToString(recycledFleas.size()) + ")");

	// Forcefully delete Recycled Fleas
	while (!recycledFleas.empty())
	{
		delete recycledFleas.top();
		recycledFleas.pop();
	}
}