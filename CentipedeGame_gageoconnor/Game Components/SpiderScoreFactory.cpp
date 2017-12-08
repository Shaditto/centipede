/* SpiderScoreFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "SpiderScoreFactory.h"
#include "SpiderScore.h"

SpiderScoreFactory *SpiderScoreFactory::pInstance = nullptr;

void SpiderScoreFactory::privateCreateSpiderScore(sf::Vector2f pos)
{
	SpiderScore *pScore;

	if (recycledSpiderScores.empty())
	{
		ConsoleMsg::WriteLine("New SpiderScore");

		pScore = new SpiderScore();

		// Object will return here instead of being destroyed
		pScore->SetExternalManagement(recycleSpiderScore);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled SpiderScore");

		pScore = recycledSpiderScores.top();
		recycledSpiderScores.pop();

		// Register back to scene
		pScore->RegisterToCurrentScene();
	}
	pScore->Initialize(pos);
}

void SpiderScoreFactory::privateRecycleSpiderScore(GameObject *player)
{
	recycledSpiderScores.push((SpiderScore*)player);
	ConsoleMsg::WriteLine("Recycled SpiderScore Size: " + Tools::ToString(recycledSpiderScores.size()));
}

void SpiderScoreFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

SpiderScoreFactory::~SpiderScoreFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled SpiderScores (" + Tools::ToString(recycledSpiderScores.size()) + ")");

	// Forcefully delete Recycled SpiderScores
	while (!recycledSpiderScores.empty())
	{
		delete recycledSpiderScores.top();
		recycledSpiderScores.pop();
	}
}