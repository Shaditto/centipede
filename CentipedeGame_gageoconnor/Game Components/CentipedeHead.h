/* CentipedeHead.h - Gage O'Connor, October 2017 */
#ifndef _CentipedeHead
#define _CentipedeHead

#include "CentipedeSegment.h"

class CentipedeHead : public Centipede
{
public:
	/* BIG FOUR */
	CentipedeHead();
	CentipedeHead(const CentipedeHead & centiHead) = default;
	CentipedeHead & operator =(const CentipedeHead &) = default;
	~CentipedeHead() = default;

	/* INITIALIZER */
	void Initialize(Tile* pTile, sf::Vector2f pos, int index, const HeadMoveState* state, int num, CentipedeSegment* seg);

	/* METHODS */
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void PlaceShroom();
	virtual void Split();

	virtual Tile* getOldTile();
	virtual Tile* getTile() override;
	virtual void setTile(Tile *pTile) override;
	virtual const HeadMoveState * GetNextState() override;
	virtual int GetIndex() override;

	virtual CentipedeHead * getHead() { return pHead; };

	virtual CentipedeSegment * getNext() { return pNext; };
	virtual CentipedeSegment * setNext(CentipedeSegment * centi) { pNext = centi; return 0; };
	
	virtual sf::Vector2f getPos() { return Pos; };

	virtual void CreateSegments(int num);
	virtual void ReportHeadRecall() override;

	/* COLLISIONS */
	virtual void Collision(GameObject *go) {};
	virtual void Collision(Bullet *other);
	virtual void Collision(Mushroom *other);

private:
	CentipedeHead *pHead;
	CentipedeSegment *pNext;

	const HeadMoveState *pCurrentState;
	const Score SCORE;

	Tile *pTile;
	Tile *pOldTile;
	const int MAX_HEALTH;

	int health;	
	int index;

	sf::Vector2f Pos;
	sf::Vector2f oldPos;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;
};
#endif _CentipedeHead