/* Scorpion.cpp - Gage O'Connor, October 2017 */

#include "Scorpion.h"
#include "ScorpionFactory.h"
#include "WaveManager.h"

Scorpion::Scorpion()
{
	// Negative side means right, positive means left
	SPEED = 100;
	baseSpeed = SPEED;

	// Assign health value and initialize other variables
	MAXHEALTH = 1;
	health = MAXHEALTH;
	clock = 16;
	clockSPEED = 100;

	// Grab the bitmap and assign it to MainSprite
	bitmap = ResourceManager::GetTextureBitmap("scorpion");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("scorpion"), 4, 1);

	// Set the animation to loop
	MainSprite.SetLoopSpeed(4);
	MainSprite.SetAnimation(0, 3, true, true);

	// Sets origin
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);

	// Sets collision
	SetCollider(MainSprite, bitmap);
}

void Scorpion::Initialize(Tile *tile, float side, float speed)
{
	// Negative means facing right, otherwise left
	MainSprite.setScale(-side, 1);

	// Re-Initialize variables
	SPEED = speed;
	SPEED *= -side;
	this->tile = tile;
	Pos = tile->getPos();

	WaveManager::SetScorp(this);
	RegisterCollision<Scorpion>(*this);
}

/* METHODS */
void Scorpion::Update()
{
	MainSprite.Update();

	// Travels along y axis
	clock += Game::FrameTime() * clockSPEED;
	Pos.x -= Game::FrameTime() * SPEED;

	if (clock >= SPEEDCHECK && tile != 0)
	{
		// Moves right
		if (SPEED < 0 && tile->hasObject())
		{
			poisonShroom(tile);
			tile = tile->getRight();
		}
		else if (SPEED < 0 && !tile->hasObject())
		{
			tile = tile->getRight();
			clock = 0;
		}
		// Moves left
		else if (SPEED > 0 && tile->hasObject())
		{
			poisonShroom(tile);
			tile = tile->getLeft();
		}
		else
		{
			tile = tile->getLeft();
			clock = 0;
		}
	}

	if (Pos.x <= POS_X)		// Destroys when offscreen on left
		MarkForDestroy();
	else if (Pos.x >= WindowManager::MainWindow.getView().getSize().x + SPEEDCHECK) // Destroys when offscreen on right
		MarkForDestroy();

	MainSprite.setPosition(Pos);
}

void Scorpion::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Scorpion::Destroy()
{
	// Reset attributes
	SPEED = baseSpeed;

	WaveManager::FreeScorp(this);
	DeregisterCollision<Scorpion>(*this);
}

void Scorpion::poisonShroom(Tile *tile)
{
	// Poison mushroom if not posioned
	if (tile->getObject()->getPoisonStatus() == false)
		tile->getObject()->setPoison();
}

/* COLLISIONS */
void Scorpion::Collision(Bullet *other)
{
	// Update score 
	ScorpionFactory::ReportDeath();
	MarkForDestroy();
}