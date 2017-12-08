/* FleaSpawner.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "FleaSpawn.h"

FleaSpawner* FleaSpawner::pInstance = nullptr;

FleaSpawner::FleaSpawner()
	: pGrid(0),
	  numShrooms(5),
	  numShroomsActive(0),
	  isActive(false)
{
	isFlea = false;
}

void FleaSpawner::privateSpawnFlea()
{
	if (Instance().isFlea == false)
	{
		FleaFactory::createFlea(pGrid);
		Instance().isFlea = true;
	}
}

void FleaSpawner::privateUpdateMushroomCount(int val)
{
	numShroomsActive += val;

	ConsoleMsg::WriteLine("Mushrooms in Player Area: " + Tools::ToString(numShroomsActive));

	// Needs to be active
	if (isActive && numShroomsActive < numShrooms)
		privateSpawnFlea();
}

void FleaSpawner::privateSetActive(bool isActive)
{
	this->isActive = isActive;
}

void FleaSpawner::privateSetFlea(bool isFlea)
{
	this->isFlea = isFlea;
}

void FleaSpawner::privateSetGrid(Grid* pGrid)
{
	this->pGrid = pGrid;
}

void FleaSpawner::privateSetNumShroom(float numShroom)
{
	this->numShrooms = numShroom;
}

void FleaSpawner::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}