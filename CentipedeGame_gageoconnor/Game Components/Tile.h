/*Tile.h - Gage O'Connor, September 2017*/

#ifndef _Tile
#define _Tile

#include "TEAL\CommonElements.h"

class FilledSpace;
class Mushroom;

class Tile : public GameObject
{
public:
	/* BIG FOUR */
	Tile() = default;
	Tile(sf::Vector2f loc);
	Tile(const Tile & tile) = default;
	Tile & operator = (const Tile & tile) = default;
	~Tile() = default;

	/* METHODS */
	void setTile(FilledSpace* object);
	void setUp(Tile *tile);
	void setDown(Tile *tile);
	void setLeft(Tile *tile);
	void setRight(Tile *tile);
	sf::Vector2f getPos();

	float getPosX();
	float getPosY();
	Tile *getUp();
	Tile *getDown();
	Tile *getLeft();
	Tile * getRight();
	FilledSpace* getObject();
	bool hasObject();

private:
	Tile* tileFix = 0;
	Tile *pUp;
	Tile *pDown;
	Tile *pLeft;
	Tile *pRight;

	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

	//lets the tile know what object is in its position
	FilledSpace* object;
};
#endif _Tile
