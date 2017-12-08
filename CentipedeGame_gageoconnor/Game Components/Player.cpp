/*Player.cpp - Gage O'Connor, September 2017*/

#include "Player.h"
#include "PlayerManager.h"
#include "BulletFactory.h"
#include "WaveManager.h"

#include "PlayerExplosionFactory.h"

Player::Player()
	:	X_CLAMP(8, 472),
		Y_CLAMP(424, 488),
		SPEED(5),
		MAX_LIVES(3),
		X_BOUNDARY(26), 
		Y_BOUNDARY(15)
{
	// Initialize remaining variables
	score = 0;
	currLives = MAX_LIVES;
	bullet_Offset = sf::Vector2f(0, float(OFFSET));
	bullet_IsActive = false;

	// Grab the bitmap and assign it to MainSprite
	bitmap = ResourceManager::GetTextureBitmap("blaster");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("blaster"), 1, 1);

	// Sets the origin(center) of MainSprite, the scale, and position
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(1,1);
	MainSprite.setPosition(Pos);

	// Sets and registers collision
	SetCollider(MainSprite, bitmap, true);

	SetDrawOrder(1000);
}

void Player::Initialize(Grid *pGrid)
{
	this->pGrid = pGrid;
	this->pTile = this->pGrid->getArr(X_BOUNDARY, Y_BOUNDARY);
	this->currLives = MAX_LIVES;
	this->score = 0;

	// Sets starting point to one of the tiles
	Pos = pGrid->getArr(START_X, START_Y)->getPos();

	RegisterCollision<Player>(*this);
	RegisterInput(InputFlags::KeyPressed);
}

/* METHODS */
void Player::Update()
{
	MainSprite.Update();

	// Clamps so player can't go off screen
	Tools::Clamp<float>(Pos.x, X_CLAMP.x, X_CLAMP.y);
	Tools::Clamp<float>(Pos.y, Y_CLAMP.x, Y_CLAMP.y);

	MainSprite.setPosition(Pos);
}

int Player::getScore()
{
	return score;
}

int Player::getLives()
{
	return currLives;
}

void Player::setScore(int val)
{
	this->score += val;
}

void Player::setLives()
{
	this->currLives--;
}

void Player::setPosition(sf::Vector2f val)
{
	oldPos = Pos;
	Pos += SPEED * val;
}

void Player::setPositionAttractor(sf::Vector2f val)
{
	oldPos = Pos;
	Pos += val;
}

void Player::resetPosition(sf::Vector2f val)
{
	Pos = val;
}

sf::Vector2f Player::getPos()
{
	return Pos;
}

void Player::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Player::Destroy()
{	
	this->bullet_IsActive = false; // Fixes bug where Player can't fire if swapped and bullet is still on screen

	DeregisterInput();
	DeregisterCollision<Player>(*this);
}

void Player::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
}

void Player::fireBullet()
{
	if (!bullet_IsActive)
	{
		BulletFactory::createBullet(Pos + bullet_Offset, this);
		bullet_IsActive = true;	// Cannot fire while bullet is on-screen
	}
}
void Player::setBulletActive()
{
	bullet_IsActive = false;
}

/*COLLISIONS*/
void Player::Collision(Mushroom *other)
{
	//ConsoleMsg::WriteLine("Colliding with Mushroom at: " + Tools::ToString(other->getPos()));
	Pos = oldPos;
	MainSprite.setPosition(Pos);
}

void Player::Collision(Spider *other)
{
	PlayerExplosionFactory::createPlayerExplosion(Pos);

	PlayerManager::SubtractLife();
	PlayerManager::DestroyCurrPlayer();

	WaveManager::ResetCritters();
}

void Player::Collision(CentipedeHead *other)
{
	PlayerExplosionFactory::createPlayerExplosion(Pos);

	PlayerManager::SubtractLife();
	PlayerManager::DestroyCurrPlayer();

	WaveManager::ResetCritters();
}

void Player::Collision(CentipedeSegment *other)
{
	PlayerExplosionFactory::createPlayerExplosion(Pos);

	PlayerManager::SubtractLife();
	PlayerManager::DestroyCurrPlayer();

	WaveManager::ResetCritters();
}

void Player::Collision(Flea *other)
{
	PlayerExplosionFactory::createPlayerExplosion(Pos);

	PlayerManager::SubtractLife();
	PlayerManager::DestroyCurrPlayer();

	WaveManager::ResetCritters();
}