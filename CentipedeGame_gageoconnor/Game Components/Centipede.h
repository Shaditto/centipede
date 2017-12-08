/* Centipede.h - Gage O'Connor, October 2017 */
#ifndef _Centipede
#define _Centipede

#include "TEAL\CommonElements.h"
#include "Grid.h"
#include "Mushroom.h"
#include "MushroomFactory.h"
#include "Scores.h"
#include "WaveManager.h"

// Forward declaration
class Bullet;
class Player;
class HeadMoveState;
class CentipedeSegment;

class Centipede : public GameObject
{
public:
	virtual const HeadMoveState * GetNextState() { return 0; };

	virtual void setTile(Tile *pTile) {return;};
	virtual Tile * getTile() { return 0; };

	virtual Centipede * getHead() { return 0; };
	virtual Centipede * getNext() { return 0; };
	virtual Centipede * getPrev() { return 0; };

	virtual Centipede * setHead(Centipede * centi) { return 0; };
	virtual Centipede * setPrev(Centipede * centi) { return 0; };
	virtual Centipede * setNext(CentipedeSegment * centi) { return 0; }

	virtual sf::Vector2f getPos() { return sf::Vector2f(0,0); };

	virtual int GetIndex() { return 0; };
	virtual void ReportHeadRecall() { return; };

	static const int FRAMES_PER_MOVEMENT = 8;
	static const int PIXELS_PER_MOVEMENT = 16;
	static const int SPEED = PIXELS_PER_MOVEMENT / FRAMES_PER_MOVEMENT;
};
#endif _Centipede