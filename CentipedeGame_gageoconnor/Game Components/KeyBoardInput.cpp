#include "KeyBoardInput.h"

KeyboardInput::KeyboardInput()
{
	this->pPlayer = 0;
}

void KeyboardInput::AssignPlayer(Player* pPlayer)
{
	this->pPlayer = pPlayer;
}

void KeyboardInput::Update()
{
	if (pPlayer != 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			pPlayer->setPosition(sf::Vector2f(0, -1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			pPlayer->setPosition(sf::Vector2f(-1, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			pPlayer->setPosition(sf::Vector2f(0, 1));;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			pPlayer->setPosition(sf::Vector2f(1, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			pPlayer->fireBullet();
		}
	}
}