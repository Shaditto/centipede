/* PlayerExplosion.h - Gage O'Connor, October 2017 */

#ifndef _PlayerExplosion
#define _PlayerExplosion

#include "TEAL\CommonElements.h"

class PlayerExplosion : public GameObject
{
public:
	/* BIG FOUR */
	PlayerExplosion();
	PlayerExplosion(const PlayerExplosion &) = default;
	PlayerExplosion & operator =(const PlayerExplosion &) = default;
	~PlayerExplosion() = default;

	/* INITIALIZER */
	void Initialize(sf::Vector2f pos);

	/* INITIALIZER */
	virtual void Update();
	virtual void Draw();

private:
	AnimatedSprite MainSprite;
};

#endif _PlayerExplosion