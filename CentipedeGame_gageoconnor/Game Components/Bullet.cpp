/* Bullet.cpp - Gage O'Connor, October 2017 */

#include "Bullet.h"
#include "BulletFactory.h"
#include "PlayerManager.h"
#include "bulletExplosionFactory.h"

Bullet::Bullet(Player *player)
	: SPEED(700)
{
	// Initialize variables
	this->player = player;

	// Grab the bitmap and assign it to MainSprite
	bitmap = ResourceManager::GetTextureBitmap("bullet");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("bullet"), 1, 1);

	// Sets the origin(center) of MainSprite
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(1,1);

	// Sets and registers collision
	SetCollider(MainSprite, bitmap);
}

void Bullet::Initialize(sf::Vector2f pos)
{
	// Set position and register collision
	Pos = pos;
	strtPos = pos;

	BulletFactory::PlaySound();
	RegisterCollision<Bullet>(*this);
}

/* METHODS */
void Bullet::Update()
{
	MainSprite.Update();

	// Travels along y-axis
	Pos.y -= Game::FrameTime() * SPEED;

	// If it goes off top of screen, destroy
	if (Pos.y <= OFFSCREEN)
		MarkForDestroy();

	MainSprite.setPosition(Pos);
}

int Bullet::getStrtPos()
{
	return int(this->strtPos.y);
}

void Bullet::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Bullet::Destroy()
{
	// Allows player to fire another bullet
	PlayerManager::GetCurrPlayer()->setBulletActive();
	DeregisterCollision<Bullet>(*this);
}

/* COLLISIONS */
void Bullet::Collision(GameObject *go)
{
	ConsoleMsg::WriteLine("Colliding with GAMEOBJECT: ");
	bulletExplosionFactory::createbulletExplosion(Pos);
	MarkForDestroy();
}