/* Glyph.cpp - Gage O'Connor, October 2017 */

#include "Glyph.h"
#include "SpriteSheet.h"
#include "TEAL\ResourceManager.h"

Glyph::Glyph()
{
	pSprsheet = 0;
	cellIndex = 0;
	position = sf::Vector2f(0, 0);

	// Dummy values for collision with Bullet
	bitmap = ResourceManager::GetTextureBitmap("blaster");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("blaster"), 1, 1);
}

void Glyph::Initialize(SpriteSheet* sheet, int cellInd, sf::Vector2f pos)
{
	pSprsheet = sheet;
	position = pos;
	cellIndex = cellInd;

	// Sets the origin(center) of MainSprite, the scale, and position
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(1, 1);
	MainSprite.setPosition(position);

	SetCollider(MainSprite, bitmap, true);

	RegisterCollision<Glyph>(*this);
}

void Glyph::Draw()
{
	pSprsheet->Draw(cellIndex, position);
}

void Glyph::Destroy()
{
	DeregisterCollision<Glyph>(*this);
}