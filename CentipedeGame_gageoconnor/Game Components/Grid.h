/*Grid.h - Gage O'Connor, September 2017*/#pragma once

#ifndef _Grid
#define _Grid

#include "TEAL\CommonElements.h"
#include "Tile.h"

class Grid
{
public:
	/* BIG FOUR */
	Grid();
	Grid(const Grid & grid) = default;
	Grid & operator =(const Grid & grid) = default;
	~Grid();

	/* METHODS */
	virtual void Create_Grid();
	Tile * getArr(int x, int y);

	virtual void FindDamagedShrooms();
	virtual void RegenMushrooms();
	virtual void ResetGrid();

	virtual void CreateMushroomGrid();
	virtual void CreatePlayerAreaMushroomGrid();
	virtual void SetMushroom(Tile *pTile);

private:
	float H_SIZE;
	float W_SIZE;
	float SQUARE_SIZE;
	int PLAYER_AREA;

	float posX; //x-position of tile
	float posY; //y-position of tile

	const int numPerRow;		// Number allowed to spawn per row
	const int numPlayerArea;	// Number allowed to spawn in Player Area

	int rowLoc;		// The row location to spawn a mushroom
	int numSpawned;	// Number of mushrooms spawned
	
	Tile *arrT[32][30]; // Array that will keep track of all tiles
	std::vector<FilledSpace*> damagedMushrooms; // Damaged mushrooms
};
#endif _Grid
