/* SpiderSpawner.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "SpiderSpawn.h"

SpiderSpawner* SpiderSpawner::pInstance = nullptr;

SpiderSpawner::SpiderSpawner()
	:left(-1),
	right(1),
	side(0),
	isActive(false)
{
}

void SpiderSpawner::privateSpawnSpider()
{
	if (isActive)
	{
		side = rand() % SPAWN_CHANCE;

		// Depending on direction, spawns Spider left or right
		if (side <= CHANCE)
			SpiderFactory::createSpider(pGrid, left);
		else
			SpiderFactory::createSpider(pGrid, right);
	}
	else
	{
		ConsoleMsg::WriteLine("SPIDER not Activated!");
	}
}

void SpiderSpawner::privateSetGrid(Grid* pGrid)
{
	this->pGrid = pGrid;
}

void SpiderSpawner::privateSetActive(bool isActive)
{
	this->isActive = isActive;
}

void SpiderSpawner::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}