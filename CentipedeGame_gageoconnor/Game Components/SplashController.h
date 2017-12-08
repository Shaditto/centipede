/*SplashController.h - Gage O'Connor, September 2017*/

#ifndef _SplashController
#define _SplashController

#include "TEAL\CommonElements.h"

class SplashController: public GameObject
{
public:
	SplashController();

	virtual ~SplashController();
	virtual void Draw();
	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);

private:
	sf::Sprite SplashSprite;
};
#endif _SplashController
