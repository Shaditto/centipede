#include "AttractorInput.h"

AttractorInput::AttractorInput()
	: X_CLAMP(8, 472),
	  Y_CLAMP(424, 490)
{
	this->pPlayer = 0;
}

void AttractorInput::AssignPlayer(Player* pPlayer)
{
	this->pPlayer = pPlayer;
	currentMove = AttractorMovement::isDiagRightDown;
}
void AttractorInput::Update()
{
	if (pPlayer != 0)
	{
		checkMove();			// Move according to current movement
		checkEdges();			// Check if Player is at x or y bounds
		pPlayer->fireBullet();
	}

	/*if (currentMove == isDiagRightUp)
		ConsoleMsg::WriteLine("RIGHT UP");
	else if (currentMove == isDiagRightDown)
		ConsoleMsg::WriteLine("RIGHT DOWN");
	else if (currentMove == isDiagLeftUp)
		ConsoleMsg::WriteLine("LEFT UP");
	else if (currentMove == isDiagLeftDown)
		ConsoleMsg::WriteLine("LEFT DOWN");*/
}

void AttractorInput::checkEdges()
{
	if (pPlayer->getPos().x == X_CLAMP.x)		// Left-boundary of Player Area
	{
		if (currentMove == isDiagLeftUp)
			currentMove = isDiagRightUp;
		else if (currentMove == isDiagLeftDown)
			currentMove = isDiagRightDown;
	}
	else if (pPlayer->getPos().x == X_CLAMP.y)	// Right-boundary of Player Area
	{
		if (currentMove == isDiagRightUp)
			currentMove = isDiagLeftUp;
		else if (currentMove == isDiagRightDown)
			currentMove = isDiagLeftDown;
	}
	else if (pPlayer->getPos().y == Y_CLAMP.x)	// Top-boundary of Player Area
	{
		if (currentMove == isDiagLeftUp)
			currentMove = isDiagLeftDown;
		else if (currentMove == isDiagRightUp)
			currentMove = isDiagRightDown;
	}
	else if (pPlayer->getPos().y == Y_CLAMP.y)	// Bottom-boundary of Player Area
	{
		if (currentMove == isDiagLeftDown)
			currentMove = isDiagLeftUp;
		else if (currentMove == isDiagRightDown)
			currentMove = isDiagRightUp;
	}
}

void AttractorInput::checkMove()
{
	// Adjusts Movement based on current movement pattern
	if (currentMove == isDiagRightUp)
		MoveDiagRightUp();
	else if (currentMove == isDiagRightDown)
		MoveDiagRightDown();
	else if (currentMove == isDiagLeftUp)
		MoveDiagLeftUp();
	else if (currentMove == isDiagLeftDown)
		MoveDiagLeftDown();
}

void AttractorInput::MoveDiagRightUp()
{
	pPlayer->setPositionAttractor(sf::Vector2f(2, 0));
	pPlayer->setPositionAttractor(sf::Vector2f(0, -2));
}

void AttractorInput::MoveDiagRightDown()
{
	pPlayer->setPositionAttractor(sf::Vector2f(2, 0));
	pPlayer->setPositionAttractor(sf::Vector2f(0, 2));
}

void AttractorInput::MoveDiagLeftUp()
{
	pPlayer->setPositionAttractor(sf::Vector2f(-2, 0));
	pPlayer->setPositionAttractor(sf::Vector2f(0, -2));
}

void AttractorInput::MoveDiagLeftDown()
{
	pPlayer->setPositionAttractor(sf::Vector2f(-2, 0));
	pPlayer->setPositionAttractor(sf::Vector2f(0, 2));
}