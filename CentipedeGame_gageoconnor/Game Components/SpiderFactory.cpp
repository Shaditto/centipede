/* SpiderFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "SpiderFactory.h"
#include "Spider.h"

#include "ScoreManager.h"
#include "SoundManager.h"

#include "CommandScore.h"
#include "CommandScoreByDistance.h"
#include "CommandSoundLoop.h"

SpiderFactory *SpiderFactory::pInstance = nullptr;

SpiderFactory::SpiderFactory()
{
	//These commands are created once only and reused every time this game object is active
	pDeathClose = ScoreManager::GetScoreCommand(ScoreManager::ScoreDistanceEvents::SpiderDeathClose);
	pDeathMedium = ScoreManager::GetScoreCommand(ScoreManager::ScoreDistanceEvents::SpiderDeathMedium);
	pDeathFar = ScoreManager::GetScoreCommand(ScoreManager::ScoreDistanceEvents::SpiderDeathFar);

	pSound = SoundManager::GetSoundCommand(SoundManager::SoundLoopStartEvents::SpiderBeatStrt);

	counter = 0;
}

void SpiderFactory::privateCreateSpider(Grid *pGrid, float side)
{
	Spider *spider;

	if (recycledSpiders.empty())
	{
		ConsoleMsg::WriteLine("New Spider");

		spider = new Spider();

		// Object will return here instead of being destroyed
		spider->SetExternalManagement(recycleSpider);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Spider");

		spider = recycledSpiders.top();
		recycledSpiders.pop();

		// Register back to scene
		spider->RegisterToCurrentScene();
	}

	// Decides which side to spawn
	if (side > 0)
		spider->Initialize(pGrid->getArr(spawnLoc, LEFT_SIDE), side);
	else
		spider->Initialize(pGrid->getArr(spawnLoc, RIGHT_SIDE), side);

	if (Instance().counter == 0)
		PlaySound();

	Instance().counter++;
}

void SpiderFactory::privateRecycleSpider(GameObject *spider)
{
	recycledSpiders.push((Spider*)spider);
	ConsoleMsg::WriteLine("Recycled Spider Size: " + Tools::ToString(recycledSpiders.size()));

	Instance().counter--;

	if (Instance().counter == 0)
		PauseSound();
}

void SpiderFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void SpiderFactory::ReportSpiderDeath(int dist)
{
	Instance().privateReportSpiderDeath(dist);
}

void SpiderFactory::PlaySound()
{
	ConsoleMsg::WriteLine("Spider Sound: Sending Scorpion sound command\n");
	SoundManager::SendSoundCommand(Instance().pSound);
}

void SpiderFactory::PauseSound()
{

	ConsoleMsg::WriteLine("Spider Sound: PAUSED");
	SoundManager::SendPauseCommand(Instance().pSound);
}


void SpiderFactory::privateReportSpiderDeath(int dist)
{
	// Processing distance to score:
	if (dist <= pDeathClose->GetDistance())
	{
		ConsoleMsg::WriteLine("Spider Factory: Sending CLOSE death score command\n");
		ScoreManager::SendScoreCommand(Instance().pDeathClose);
	}
	else if (dist <= pDeathMedium->GetDistance())
	{
		ConsoleMsg::WriteLine("Spider Factory: Sending MEDIUM death score command\n");
		ScoreManager::SendScoreCommand(Instance().pDeathMedium);
	}
	else
	{
		ConsoleMsg::WriteLine("Spider Factory: Sending FAR death score command\n");
		ScoreManager::SendScoreCommand(Instance().pDeathFar);
	}
}

SpiderFactory::~SpiderFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Spiders (" + Tools::ToString(recycledSpiders.size()) + ")");

	// Forcefully delete Recycled Spiders
	while (!recycledSpiders.empty())
	{
		delete recycledSpiders.top();
		recycledSpiders.pop();
	}
}