/* SpiderScore.cpp - Gage O'Connor, October 2017 */

#include "SpiderScore.h"

SpiderScore::SpiderScore()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("spiderScore"), 1, 3, 8);
	MainSprite.SetAnimation(0, 2);
	MainSprite.scale(2, 2);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
}

void SpiderScore::Initialize(sf::Vector2f pos)
{
	// Reset frame and position
	MainSprite.SetFrame(0);
	MainSprite.setPosition(pos);
}

void SpiderScore::Update()
{
	if (MainSprite.IsLastAnimationFrame())
	{
		MarkForDestroy();
	}
	MainSprite.Update();
}

void SpiderScore::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}