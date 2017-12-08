/* HUD.h - Gage O'Connor, October 2017 */

#ifndef _HUD
#define _HUD

#include "TEAL\CommonElements.h"

class HUD : public GameObject
{
public:

	HUD();
	virtual void Update();
	virtual void Draw();
	static void UpdateScore(int val);	// Updates Score

private:

	/*sf::Font ScoreFont;
	int pointsize;

	static std::string Label;
	static sf::Color ScoreColor;
	static sf::Text ScoreDisplay;
	static sf::Sound ScoreSnd;*/
};
#endif _HUD