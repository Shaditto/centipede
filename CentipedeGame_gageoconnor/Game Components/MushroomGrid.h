/*MushroomGrid.h - Gage O'Connor, October 2017*/

#ifndef _MushroomGrid
#define _MushroomGrid

#include "TEAL\CommonElements.h"
#include "Grid.h"
#include "Mushroom.h"

class MushroomGrid
{
public:
	/* BIG FOUR */
	MushroomGrid(Grid *pGrid);
	MushroomGrid(const MushroomGrid &mush) = default;
	MushroomGrid & operator =(const MushroomGrid &mush) = default;
	~MushroomGrid() = default;

	/* METHODS */
	virtual void CreateMushroomGrid(Grid *pGrid);
	virtual void CreatePlayerAreaMushroomGrid(Grid *pGrid);
	virtual void SetMushroom(Tile *pTile);

private:
	int H_SIZE;
	int W_SIZE;
	int PLAYER_AREA;

	const int numPerRow;		// Number allowed to spawn per row
	const int numPlayerArea;	// Number allowed to spawn in Player Area

	int rowLoc;		// The row location to spawn a mushroom
	int numSpawned;	// Number of mushrooms spawned
};
#endif _MushroomGrid