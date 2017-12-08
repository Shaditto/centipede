/* Scorpion.h - Gage O'Connor, October 2017 */

#ifndef _Flea
#define _Flea

#include "TEAL\CommonElements.h"
#include "Grid.h"

// Forward Declarations
class Bullet;

class Flea : public GameObject
{
public:
	/* BIG FOUR */
	Flea();
	Flea(const Flea & scorp) = default;
	Flea & operator =(const Flea &) = default;
	~Flea() = default;

	/* INITIALIZER */
	void Initialize(Tile *tile);

	/* METHODS */
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void spawnMushroom();

	/* COLLISIONS */
	virtual void Collision(GameObject *go) {};
	virtual void Collision(Bullet *other);

private:
	Tile *pTile;

	const float MAXHEALTH;
	const int CLOCK_SPEED = 16;
	const int WINDOW_SIZE = 32;
	const int BASE_HEALTH = 1;
	const int SPAWN_CHANCE = 5;
	const int RAND_CHANCE = 30;
	const int SPEED_INCREASE = 2;

	float speed;
	float baseSpeed;
	float health;
	float clock;

	int willSpawn;

	sf::Vector2f Pos;
	sf::Sound snd;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;
};
#endif _Flea