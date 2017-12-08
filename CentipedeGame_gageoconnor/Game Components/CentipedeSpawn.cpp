/* CentipedeSpawner.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "CentipedeSpawn.h"
#include "Head_MoveFSM.h"

CentipedeSpawner* CentipedeSpawner::pInstance = nullptr;

CentipedeSpawner::CentipedeSpawner()
{
}

void CentipedeSpawner::privateSpawnCentipede(Tile* pTile, int num)
{
	direction = rand() % SPAWN_CHANCE;

	// Depending on direction, spawns Centipede left or right
	if (direction <= CHANCE)
		CentipedeHeadFactory::createCentipedeHead(pTile, pTile->getLeft()->getPos(), 0, &HeadMoveFSM::StateMoveRightAndDown, num, 0);
	else
		CentipedeHeadFactory::createCentipedeHead(pTile, pTile->getRight()->getPos(), 0, &HeadMoveFSM::StateMoveLeftAndDown, num, 0);
}

void CentipedeSpawner::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}