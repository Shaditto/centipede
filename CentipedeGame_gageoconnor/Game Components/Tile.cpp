/*Tile.cpp - Gage O'Connor, September 2017*/

#include "Tile.h"

Tile::Tile(sf::Vector2f loc)
	:	pUp(0), pDown(0), pLeft(0), pRight(0), object(0)
{
	//grab the bitmap and assign it to MainSprite
	bitmap = &ResourceManager::GetTextureBitmap("tile");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("tile"), 1, 1);

	// sets the origin(center) of MainSprite
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.scale(1, 1);

	Pos = loc;
	MainSprite.setPosition(Pos);
}

/*SET FUNCTIONS*/
void Tile::setTile(FilledSpace* object)
{
	if (tileFix == nullptr)
		this->object = object;
}

void Tile::setUp(Tile * tile)
{
	this->pUp = tile;
}

void Tile::setDown(Tile * tile)
{
	this->pDown = tile;
}

void Tile::setLeft(Tile * tile)
{
	this->pLeft = tile;
}

void Tile::setRight(Tile * tile)
{
	this->pRight = tile;
}

bool Tile::hasObject()
{
	if (this->object != nullptr)
		return true;
	return false;
}

/*GET FUNCTIONS*/
sf::Vector2f Tile::getPos()
{
	return Pos;
}

//return the tiles x position
float Tile::getPosX()
{
	return Pos.x;
}

//return the tiles y position
float Tile::getPosY()
{
	return Pos.y;
}

Tile * Tile::getUp()
{
	return this->pUp;
}

Tile * Tile::getDown()
{
	return this->pDown;
}

Tile * Tile::getLeft()
{
	return this->pLeft;
}

Tile * Tile::getRight()
{
	return this->pRight;
}

FilledSpace* Tile::getObject()
{
	return this->object;
}
