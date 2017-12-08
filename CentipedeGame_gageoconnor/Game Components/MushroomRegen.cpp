/* MushroomRegen.cpp - Gage O'Connor, October 2017 */

#include "MushroomRegen.h"
#include "MushroomRegenFactory.h"

MushroomRegen::MushroomRegen()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("spawn"), 3, 2, 4);
	MainSprite.SetAnimation(0, 1);
	MainSprite.scale(2, 2);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
}

void MushroomRegen::Initialize(sf::Vector2f pos)
{
	// Reset frame and position
	MainSprite.SetFrame(0);
	MainSprite.setPosition(pos);
	MushroomRegenFactory::PlaySound();
}

void MushroomRegen::Update()
{
	if (MainSprite.IsLastAnimationFrame())
	{
		MarkForDestroy();
		MushroomRegenFactory::Regenerate();
	}
	MainSprite.Update();
}

void MushroomRegen::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}