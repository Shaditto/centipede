/* MushroomFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "MushroomFactory.h"
#include "Mushroom.h"

#include "ScoreManager.h"
#include "CommandScore.h"


MushroomFactory *MushroomFactory::pInstance = nullptr;

MushroomFactory::MushroomFactory()
{
	// These commands are created once only and reused every time this game object is active
	pRegularDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::MushroomDeath);
	pPoisonDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::MushroomPoisonDeath);
	pRegen = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::MushroomRegenerate);
}

void MushroomFactory::privateCreateMushroom(sf::Vector2f pos, Tile *pTile)
{
	Mushroom *pMush;

	if (recycledMushrooms.empty())
	{
		ConsoleMsg::WriteLine("New Mushroom");

		pMush = new Mushroom();

		// Object will return here instead of being destroyed
		pMush->SetExternalManagement(recycleMushroom);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Mushroom");

		pMush = recycledMushrooms.top();
		recycledMushrooms.pop();

		// Register back to scene
		pMush->RegisterToCurrentScene();
	}
	pMush->Initialize(pos, pTile);
}

void MushroomFactory::privateRecycleMushroom(GameObject *pMush)
{
	recycledMushrooms.push((Mushroom*)pMush);
	ConsoleMsg::WriteLine("Recycled Mushroom Size: " + Tools::ToString(recycledMushrooms.size()));
}

void MushroomFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void MushroomFactory::ReportDeath()
{
	ConsoleMsg::WriteLine("Mushroom Factory: Sending regular death score command\n");
	ScoreManager::SendScoreCommand(Instance().pRegularDeath);
}

void MushroomFactory::ReportPoisonDeath()
{
	ConsoleMsg::WriteLine("Mushroom Factory: Sending poison death score command\n");
	ScoreManager::SendScoreCommand(Instance().pPoisonDeath);
}

void MushroomFactory::ReportRegen()
{
	ConsoleMsg::WriteLine("Mushroom Factory: Sending regen score command\n");
	ScoreManager::SendScoreCommand(Instance().pRegen);
}

MushroomFactory::~MushroomFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Mushrooms (" + Tools::ToString(recycledMushrooms.size()) + ")");

	// Forcefully delete Recycled Mushrooms
	while (!recycledMushrooms.empty())
	{
		delete recycledMushrooms.top();
		recycledMushrooms.pop();
	}
}