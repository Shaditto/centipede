/* PlayerExplosion.cpp - Gage O'Connor, October 2017 */

#include "PlayerExplosion.h"
#include "PlayerExplosionFactory.h"

PlayerExplosion::PlayerExplosion()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("death"), 8, 2, 16);
	MainSprite.SetAnimation(0, 7);
	MainSprite.scale(1, 1);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
}

void PlayerExplosion::Initialize(sf::Vector2f pos)
{
	// Reset frame and position
	MainSprite.SetFrame(0);
	MainSprite.setPosition(pos);

	PlayerExplosionFactory::PlaySound();
}

void PlayerExplosion::Update()
{
	if (MainSprite.IsLastAnimationFrame())
	{
		MarkForDestroy();
	}
	MainSprite.Update();
}

void PlayerExplosion::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}