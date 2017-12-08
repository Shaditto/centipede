/* ScorpionFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "ScorpionFactory.h"
#include "Scorpion.h"

#include "ScoreManager.h"
#include "SoundManager.h"

#include "CommandScore.h"
#include "CommandSoundLoop.h"

ScorpionFactory *ScorpionFactory::pInstance = nullptr;

ScorpionFactory::ScorpionFactory()
{
	// These commands are created once only and reused every time this game object is active
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::ScorpionDeath);
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundLoopStartEvents::ScorpionBeatStrt);

	counter = 0;
}

void ScorpionFactory::privateCreateScorpion(Grid *pGrid, float side, float speed)
{
	Scorpion *scorpion;
	spawnLoc = rand() % 26; // Grab a random location to spawn Scorpion

	if (recycledScorpions.empty())
	{
		ConsoleMsg::WriteLine("New Scorpion");

		scorpion = new Scorpion();

		// Object will return here instead of being destroyed
		scorpion->SetExternalManagement(recycleScorpion);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Scorpion");

		scorpion = recycledScorpions.top();
		recycledScorpions.pop();

		// Register back to scene
		scorpion->RegisterToCurrentScene();
	}

	// Decides which side to spawn
	if (side > 0)
		scorpion->Initialize(pGrid->getArr(spawnLoc, 0), side, speed);
	else
		scorpion->Initialize(pGrid->getArr(spawnLoc, 29), side, speed);

	if (Instance().counter == 0)
		PlaySound();

	Instance().counter++;
}

void ScorpionFactory::privateRecycleScorpion(GameObject *scorpion)
{
	recycledScorpions.push((Scorpion*)scorpion);
	ConsoleMsg::WriteLine("Recycled Scorpion Size: " + Tools::ToString(recycledScorpions.size()));

	Instance().counter--;

	if (Instance().counter == 0)
	{
		PauseSound();
	}
}

void ScorpionFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void ScorpionFactory::ReportDeath()
{
	ConsoleMsg::WriteLine("Scorpion Factory: Sending death score command\n");
	ScoreManager::SendScoreCommand(Instance().pDeath);
}

void ScorpionFactory::PlaySound()
{
	ConsoleMsg::WriteLine("Scorpion Sound: Sending Scorpion sound command\n");
	SoundManager::SendSoundCommand(Instance().pSound);
}

void ScorpionFactory::PauseSound()
{

	ConsoleMsg::WriteLine("Scorpion Sound: PAUSED");
	SoundManager::SendPauseCommand(Instance().pSound);
}

ScorpionFactory::~ScorpionFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Scorpions (" + Tools::ToString(recycledScorpions.size()) + ")");

	// Forcefully delete Recycled Scorpions
	while (!recycledScorpions.empty())
	{
		delete recycledScorpions.top();
		recycledScorpions.pop();
	}
}