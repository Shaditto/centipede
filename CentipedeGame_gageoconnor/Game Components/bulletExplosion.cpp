/* bulletExplosion.cpp - Gage O'Connor, October 2017 */

#include "bulletExplosion.h"
#include "bulletExplosionFactory.h"

bulletExplosion::bulletExplosion()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("spawn"), 3, 2);
	MainSprite.SetAnimation(0, 2);
	MainSprite.scale(1, 1);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
}

void bulletExplosion::Initialize(sf::Vector2f pos)
{
	// Reset frame and position
	MainSprite.SetFrame(0);
	MainSprite.setPosition(pos);
}

void bulletExplosion::Update()
{
	if (MainSprite.IsLastAnimationFrame())
	{
		MarkForDestroy();
	}
	MainSprite.Update();
}

void bulletExplosion::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}