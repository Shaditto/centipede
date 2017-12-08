/*Mushroom.cpp - Gage O'Connor, September 2017*/

#include "Mushroom.h"
#include "MushroomFactory.h"
#include "MushroomRegenFactory.h"
#include "FleaSpawn.h"

Mushroom::Mushroom()
	: MAXHEALTH(4)
{
	// Initializes variables
	health = MAXHEALTH;
	isPoisoned = false;

	// Grab the bitmap and assign it to MainSprite
	bitmap = &ResourceManager::GetTextureBitmap("mushroom");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("mushroom"), 4, 2);

	// Sets animation
	MainSprite.SetAnimation(0, 7, false, false);

	// Sets the origin(center) of MainSprite
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.scale(1,1);

	// Sets and registers collision
	SetCollider(MainSprite, *bitmap);
}

void Mushroom::Initialize(sf::Vector2f loc, Tile * pTile)
{
	// Assign Tile
	this->pTile = pTile;
	this->pTile->setTile(this);

	//Re-Initialize variables
	health = MAXHEALTH;
	isPoisoned = false;
	MainSprite.SetFrame(0);

	// Sets position and registers collision for Mushroom
	Pos = loc;
	MainSprite.setPosition(Pos);
	RegisterCollision<Mushroom>(*this);

	if (Pos.y >= FLEA_POS)
	{
		FleaSpawner::UpdateMushroomCount(1);
	}
}

/* METHODS */
void Mushroom::Update()
{
	MainSprite.Update();
}

void Mushroom::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Mushroom::restoreHealth()
{
	health = MAXHEALTH;
	MushroomRegenFactory::createMushroomRegen(this->Pos);
	MainSprite.SetFrame(0);
	isPoisoned = false;
	MushroomFactory::ReportRegen();
}

void Mushroom::setPoison()	// Changes mushroom sprite to poisoned
{
	isPoisoned = true;
	MainSprite.SetFrame(MainSprite.GetFrame() + SPRITEFIX);
}

const bool Mushroom::getPoisonStatus()	// Returns poison status
{
	return isPoisoned;
}

const int Mushroom::getHealth() // Returns current health
{
	return int(health);
}

const int Mushroom::getMaxHealth() // Returns max health
{
	return int(MAXHEALTH);
}

const sf::Vector2f Mushroom::getPos()	// Returns the Mushrooms position
{
	return Pos;
}

void Mushroom::Destroy()
{
	// ConsoleMsg::WriteLine("Tile freed at: " + Tools::ToString(tile->getPos()));

	// Frees up the tile corresponding with the mushroom
	if (pTile != nullptr)
		pTile->setTile(0);

	// Alerts Flea if it needs to spawn
	if (Pos.y >= FLEA_POS)
		FleaSpawner::UpdateMushroomCount(-1);
	else
		FleaSpawner::UpdateMushroomCount(0);

	DeregisterCollision<Mushroom>(*this);
}

/* COLLISIONS */
void Mushroom::Collision(Bullet *other)
{
	health -= 1;

	// If health <= 0, destroy mushroom otherwise update frame
	if (health <= 0)
	{ 
		// Update Score
		if (isPoisoned) 
			MushroomFactory::ReportPoisonDeath(); // Poison Death
		else			
			MushroomFactory::ReportDeath();		  // Regular Death

		MarkForDestroy();
	}
	else
		MainSprite.NextFrame(); 
}