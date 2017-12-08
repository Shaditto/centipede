/* SpiderScore.h - Gage O'Connor, October 2017 */

#ifndef _SpiderScore
#define _SpiderScore

#include "TEAL\CommonElements.h"

class SpiderScore : public GameObject
{
public:
	SpiderScore();
	virtual void Update();
	virtual void Draw();

	/* INITIALIZER */
	void Initialize(sf::Vector2f pos);

private:
	AnimatedSprite MainSprite;
	sf::Sound snd;
};

#endif _SpiderScore