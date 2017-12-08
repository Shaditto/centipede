/* Mushroom.h - Gage O'Connor, October 2017 */

#ifndef _Mushroom
#define _Mushroom

#include "TEAL\CommonElements.h"
#include "FilledSpace.h"
#include "Tile.h"

// Forward declarations
class Bullet;
class Scorpion;

class Mushroom : public FilledSpace
{
public:
	/* BIG FOUR */
	Mushroom();
	Mushroom(const Mushroom & mush) = default;
	Mushroom & operator =(const Mushroom & mush) = default;
	~Mushroom() = default;

	/* INITIALIZER */
	void Initialize(sf::Vector2f loc, Tile * pTile);

	/* METHODS */
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void restoreHealth() override;
	virtual void setPoison() override;
	const bool virtual getPoisonStatus() override;
	const int virtual getHealth() override;
	const int virtual getMaxHealth() override;

	const sf::Vector2f virtual getPos();

	/* COLLISIONS */
	virtual void Collision(GameObject *go) {};
	virtual void Collision(Bullet *other);

private:
	Tile *pTile; // Points to the tile associated with the mush

	const float MAXHEALTH;
	float health;

	const int FLEA_POS = 424;
	const int SPRITEFIX = 4;

	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

	bool isPoisoned;
};

#endif _Mushroom