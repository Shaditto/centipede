/* MushroomRegen.h - Gage O'Connor, October 2017 */

#ifndef _MushroomRegen
#define _MushroomRegen

#include "TEAL\CommonElements.h"

class MushroomRegen : public GameObject
{
public:
	MushroomRegen();
	virtual void Update();
	virtual void Draw();

	/* INITIALIZER */
	void Initialize(sf::Vector2f pos);

private:
	AnimatedSprite MainSprite;
	sf::Sound snd;
};

#endif _MushroomRegen
