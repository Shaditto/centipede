/* CentipedeSegment.h - Gage O'Connor, October 2017 */

#ifndef _CentipedeSegment
#define _CentipedeSegment

#include "Centipede.h"

class CentipedeSegment : public Centipede
{
public:
	/* BIG FOUR */
	CentipedeSegment();
	CentipedeSegment(const CentipedeSegment &) = default;
	CentipedeSegment & operator =(const CentipedeSegment &) = default;
	~CentipedeSegment() = default;

	/* INITIALIZER */
	void Initialize(Tile* pTile, sf::Vector2f pos, int index, const HeadMoveState* state, Centipede* body);

	/* METHODS */
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void Delete();
	virtual void PlaceShroom();
	virtual void Split();

	virtual const HeadMoveState * GetNextState() override;
	virtual Tile* getTile() override;

	virtual CentipedeSegment * getNext() { return pNext; };
	virtual Centipede * getPrev()		 { return pPrev; };

	virtual Centipede * setNext(CentipedeSegment * centi) override { pNext = centi; return 0; }
	virtual Centipede * setPrev(Centipede * centi)  { pPrev = centi; return 0; }

	virtual sf::Vector2f getPos() { return Pos; };

	virtual int GetIndex() override;
	virtual void ReportHeadRecall() override {}; // Does nothing

	/* COLLISIONS */
	virtual void Collision(GameObject *go) {};
	virtual void Collision(Bullet *bullet);

private:
	CentipedeSegment *pNext;
	Centipede *pPrev;

	Tile *pTile;
	Tile *pNextTile;

	const HeadMoveState *pCurrentState;
	const HeadMoveState *pNextState;
	const Score SCORE;

	const int MAX_HEALTH;

	int health;
	int index;

	sf::Vector2f Pos;
	sf::Sound snd;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;
};

#endif _CentipedeSegment