/* Bullet.h - Gage O'Connor, October 2017 */

#ifndef _Bullet
#define _Bullet

#include "TEAL\CommonElements.h"
#include "Player.h"

// Forward Declaration
class Glyph;

class Bullet : public GameObject
{
public:
	/* BIG FOUR */
	Bullet(Player *player);
	Bullet(const Bullet &) = default;
	Bullet & operator =(const Bullet &) = default;
	~Bullet() = default;

	/* INITIALIZER */
	void Initialize(sf::Vector2f pos);

	/* METHODS */
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual int getStrtPos();

	/* COLLISIONS */
	virtual void Collision(GameObject *go);

private:
	const float SPEED;
	const float OFFSCREEN = 0;

	Player *player;

	sf::Vector2f Pos;
	sf::Vector2f strtPos;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;
};
#endif _Bullet