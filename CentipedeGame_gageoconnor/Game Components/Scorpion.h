/* Scorpion.h - Gage O'Connor, October 2017 */

#ifndef _Scorpion
#define _Scorpion

#include "TEAL\CommonElements.h"
#include "Grid.h"
#include "Mushroom.h"

// Forward Declarations
class Bullet;

class Scorpion : public GameObject
{
public:
	/* BIG FOUR */
	Scorpion();
	Scorpion(const Scorpion &) = default;
	Scorpion & operator =(const Scorpion &) = default;
	~Scorpion() = default;

	/* INITIALIZER */
	void Initialize(Tile *tile, float side, float speed);

	/* METHODS */
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void poisonShroom(Tile *tile);

	/* COLLISIONS */
	virtual void Collision(GameObject *go) {};
	virtual void Collision(Bullet *other);

private:
	const int SPEEDCHECK = 16;
	const int POS_X = -24;

	Tile *tile;

	float SPEED;
	float baseSpeed;
	float clock;
	float clockSPEED;

	int MAXHEALTH;
	int health;

	sf::Vector2f Pos;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;
};
#endif _Scorpion