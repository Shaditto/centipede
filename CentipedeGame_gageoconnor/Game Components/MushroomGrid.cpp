/* MushroomGrid.cpp - Gage O'Connor, October 2017 */

#include "MushroomGrid.h"
#include "MushroomFactory.h"

MushroomGrid::MushroomGrid(Grid * pGrid)
	: numPerRow(2),
	  numPlayerArea(1)
{
	W_SIZE = int(WindowManager::MainWindow.getView().getSize().x / 16);
	H_SIZE = int(WindowManager::MainWindow.getView().getSize().y / 16);
	PLAYER_AREA = H_SIZE - 6;
	rowLoc = 0;
	numSpawned = 0;

	CreateMushroomGrid(pGrid);
	CreatePlayerAreaMushroomGrid(pGrid);
}

void MushroomGrid::CreateMushroomGrid(Grid *pGrid)
{
	// Traverses through tiles and randomly spawns mushrooms up to the SPAWN_AREA
	for (int i = 2; i < PLAYER_AREA; i++)
	{
		numSpawned = 0;

		while (numSpawned < numPerRow)
		{
			rowLoc = rand() % static_cast<int>(W_SIZE);			// Grab a random location

			if (pGrid->getArr(i, rowLoc)->hasObject() == false) // Only one Mushroom per Tile
			{
				SetMushroom(pGrid->getArr(i, rowLoc));			// Create a mushroom at that location
				numSpawned++;
			}
		}
	}
}

void MushroomGrid::CreatePlayerAreaMushroomGrid(Grid *pGrid)
{
	// Traverses the remaining grid and spawns mushrooms in player area
	for (int i = PLAYER_AREA; i < H_SIZE - 1; i++) //warning
	{
		numSpawned = 0;

		while (numSpawned < numPlayerArea)
		{
			rowLoc = rand() % static_cast<int>(W_SIZE);			// Grab a random location

			if (pGrid->getArr(i, rowLoc)->hasObject() == false) // Only one Mushroom per Tile
			{
				SetMushroom(pGrid->getArr(i, rowLoc));			// Create a mushroom at that location
				numSpawned++;
			}
		}
	}
}

// Spawns mushroom and assigns it to the tile
void MushroomGrid::SetMushroom(Tile *pTile)
{
	MushroomFactory::createMushroom(pTile->getPos(), pTile);
}