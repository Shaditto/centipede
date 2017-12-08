/* Grid.cpp - Gage O'Connor, October 2017 */

#include "Grid.h"

#include "Mushroom.h"
#include "MushroomFactory.h"
#include "PlayerManager.h"

Grid::Grid()
	: numPerRow(2),
	  numPlayerArea(1)
{
	// Pixel size of each square/tile
	SQUARE_SIZE = 16.0f;

	// Calculate how many tiles to sapwn
	W_SIZE = WindowManager::MainWindow.getView().getSize().x / SQUARE_SIZE;
	H_SIZE = WindowManager::MainWindow.getView().getSize().y / SQUARE_SIZE;
	PLAYER_AREA = int(H_SIZE - 6);

	posX = SQUARE_SIZE / 2;
	posY = SQUARE_SIZE / 2;

	rowLoc = 0;
	numSpawned = 0;

	// Creates the grid
	Create_Grid();
}

/* METHODS */
void Grid::Create_Grid()
{
	Tile *head = 0;
	Tile *traverse = head;

	// Traverses and creates a grid of tiles 16px apart
	for (int i = 0; i < H_SIZE; i++)
	{
		head = 0;
		posX = SQUARE_SIZE / 2; // Adjustment for yaxis

		for (int j = 0; j < W_SIZE; j++)
		{
			if (head == 0)
			{
				head = new Tile(sf::Vector2f(posX, posY)); // Creates a tile at this location and adds it to the array
				arrT[i][j] = head;

				if (i != 0)
				{
					arrT[i][j]->setUp(arrT[i - 1][j]);
					arrT[i - 1][j]->setDown(arrT[i][j]);
				}
			}
			else
			{
				traverse = new Tile(sf::Vector2f(posX, posY));
				traverse->setLeft(arrT[i][j - 1]);
				arrT[i][j - 1]->setRight(traverse);
				arrT[i][j] = traverse;

				if (i != 0)
				{
					arrT[i][j]->setUp(arrT[i - 1][j]);
					arrT[i - 1][j]->setDown(arrT[i][j]);
				}
			}
			arrT[i][j]->setRight(0);
			posX += SQUARE_SIZE;
		}
		posY += SQUARE_SIZE; // Adjustment for x axis
	}
}

void Grid::CreateMushroomGrid()
{
	// Traverses through tiles and randomly spawns mushrooms up to the SPAWN_AREA
	for (int i = 2; i < PLAYER_AREA; i++)
	{
		numSpawned = 0;

		while (numSpawned < numPerRow)
		{
			rowLoc = rand() % static_cast<int>(W_SIZE);			// Grab a random location

			if (getArr(i, rowLoc)->hasObject() == false) // Only one Mushroom per Tile
			{
				SetMushroom(getArr(i, rowLoc));			// Create a mushroom at that location
				numSpawned++;
			}
		}
	}
}

void Grid::CreatePlayerAreaMushroomGrid()
{
	// Traverses the remaining grid and spawns mushrooms in player area
	for (int i = PLAYER_AREA; i < H_SIZE - 1; i++) //warning
	{
		numSpawned = 0;

		while (numSpawned < numPlayerArea)
		{
			rowLoc = rand() % static_cast<int>(W_SIZE);			// Grab a random location

			if (getArr(i, rowLoc)->hasObject() == false) // Only one Mushroom per Tile
			{
				SetMushroom(getArr(i, rowLoc));			// Create a mushroom at that location
				numSpawned++;
			}
		}
	}
}

// Spawns mushroom and assigns it to the tile
void Grid::SetMushroom(Tile *pTile)
{
	MushroomFactory::createMushroom(pTile->getPos(), pTile);
}

// Returns a * to a specific arr index
Tile * Grid::getArr(int x, int y)
{
	return arrT[x][y];
}

void Grid::RegenMushrooms()
{
	// Won't Regen if there arent any damaged mushrooms
	if (!damagedMushrooms.empty())
	{
		damagedMushrooms.back()->restoreHealth();
		damagedMushrooms.pop_back();
	}
	else
	{
		PlayerManager::Respawn();
	}
}

void Grid::FindDamagedShrooms()
{
	damagedMushrooms.clear(); // In case there's anything left for some reason

	// Goes through Grid and finds damaged 
	for (int i = 0; i < H_SIZE; i++)
	{
		for (int j = 0; j < W_SIZE; j++)
		{
			if ((arrT[i][j]->hasObject() && arrT[i][j]->getObject()->getHealth() < arrT[i][j]->getObject()->getMaxHealth()) || (arrT[i][j]->hasObject() && arrT[i][j]->getObject()->getPoisonStatus() == true))
				damagedMushrooms.push_back(arrT[i][j]->getObject());
		}
	}
}

void Grid::ResetGrid()
{
	// Goes through Grid and finds damaged 
	for (int i = 0; i < H_SIZE; i++)
	{
		for (int j = 0; j < W_SIZE; j++)
		{
			if (arrT[i][j]->hasObject())
			{
				arrT[i][j]->getObject()->MarkForDestroy();
				arrT[i][j]->setTile(0);

			}
		}
	}
}

Grid::~Grid()
{
	/*for (int i = 0; i < H_SIZE; i++)
	{
		for (int j = 0; j < W_SIZE; j++)
		{
			delete arrT[i][j];
		}
	}*/
}