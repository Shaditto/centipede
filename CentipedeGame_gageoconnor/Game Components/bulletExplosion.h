/* bulletExplosion.h - Gage O'Connor, October 2017 */

#ifndef _bulletExplosion
#define _bulletExplosion

#include "TEAL\CommonElements.h"

class bulletExplosion : public GameObject
{
public:
	/* BIG FOUR */
	bulletExplosion();
	bulletExplosion(const bulletExplosion &) = default;
	bulletExplosion & operator =(const bulletExplosion &) = default;
	~bulletExplosion() = default;

	/* INITIALIZER */
	void Initialize(sf::Vector2f pos);

	/* INITIALIZER */
	virtual void Update();
	virtual void Draw();

private:
	AnimatedSprite MainSprite;
};

#endif _bulletExplosion
