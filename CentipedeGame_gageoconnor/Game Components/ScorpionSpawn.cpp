/* ScorpionSpawner.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "ScorpionSpawn.h"

ScorpionSpawner* ScorpionSpawner::pInstance = nullptr;

ScorpionSpawner::ScorpionSpawner()
	:left(-1),
	 right(1),
	 side(0),
	 isActive(false)
{
}

void ScorpionSpawner::privateSpawnScorpion(float speed)
{
	// Needs to be active
	if (isActive)
	{
		side = rand() % SPAWN_CHANCE;

		// Depending on direction, spawns Scorpion left or right
		if (side <= CHANCE)
			ScorpionFactory::createScorpion(pGrid, left, speed);
		else
			ScorpionFactory::createScorpion(pGrid, right, speed);
	}
	else
	{
		ConsoleMsg::WriteLine("SCORPION not Activated!");
	}
}

void ScorpionSpawner::privateSetGrid(Grid* pGrid)
{
	this->pGrid = pGrid;
}

void ScorpionSpawner::privateSetActive(bool isActive)
{
	this->isActive = isActive;
}

void ScorpionSpawner::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}