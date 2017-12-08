/* Glyph.h - Gage O'Connor, October 2017 */

#ifndef _Glyph
#define _Glyph

#include "SFML\Graphics.hpp"
#include "TEAL\CommonElements.h"
#include "FilledSpace.h"

// Forward Declarations
class SpriteSheet;

class Glyph : public FilledSpace
{
public:
	Glyph();

	/* METHODS */
	void Draw();
	virtual void Destroy();

	/* INITIALIZER */
	void Initialize(SpriteSheet* sheet, int cellInd, sf::Vector2f pos);

private:
	SpriteSheet* pSprsheet;

	int cellIndex;
	sf::Vector2f position;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;
};

#endif _Glyph
