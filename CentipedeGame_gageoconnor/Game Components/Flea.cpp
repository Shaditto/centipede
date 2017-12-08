/*Flea.cpp - Gage O'Connor, September 2017*/

#include "Flea.h"
#include "FleaFactory.h"
#include "FleaSpawn.h"
#include "MushroomFactory.h"
#include "WaveManager.h"

Flea::Flea()
	: MAXHEALTH(2)
{
	// Initializer rest of variables
	speed = 210;
	baseSpeed = speed;
	health = MAXHEALTH;
	clock = 0;

	// Grab the bitmap and assign it to MainSprite
	bitmap = ResourceManager::GetTextureBitmap("flea");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("flea"), 2, 2);

	// Set the animation to loop
	MainSprite.SetLoopSpeed(4);
	MainSprite.SetAnimation(0, 3, true, true);

	// Sets origin and scale
	MainSprite.setOrigin((MainSprite.getTextureRect().width / 2.0f) - 7, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(1, 1);

	// Sets and registers collision
	SetCollider(MainSprite, bitmap);

	// Flea sound effects
	snd.setBuffer(ResourceManager::GetSound("flea_new"));
	snd.setPitch(1);
	snd.setVolume(2);
}

void Flea::Initialize(Tile * pTile)
{
	// Sets position to passed tile
	this->pTile = pTile;
	Pos = pTile->getPos();
	

	FleaFactory::PlaySound();

	WaveManager::SetFlea(this);
	RegisterCollision<Flea>(*this);
}

/*METHODS*/
void Flea::Update()
{
	MainSprite.Update();

	// Travels along y-axis
	clock += Game::FrameTime() * speed;
	Pos.y += Game::FrameTime() * speed;

	// Spawns mushroom after interval
	if (clock >= CLOCK_SPEED && health > BASE_HEALTH && pTile->getDown() != 0)
	{
		willSpawn = rand() % RAND_CHANCE;	// Random chance of spawning a mushroom

		if (willSpawn <= SPAWN_CHANCE)
			spawnMushroom();		// Attempts to spawns mushroom
		else
			pTile = pTile->getDown();	// Otherwise continue down Grid

		clock = 0;
	}

	// If it goes off the bottom of the screen
	if (Pos.y >= WindowManager::MainWindow.getView().getSize().y + WINDOW_SIZE)
		MarkForDestroy();

	MainSprite.setPosition(Pos);
}

void Flea::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Flea::Destroy()
{
	//FleaSpawner::UpdateMushroomCount(0);
	// Resets attributes
	health = MAXHEALTH;
	speed = baseSpeed;

	WaveManager::FreeFlea(this);
	FleaSpawner::SetFlea(false);
	DeregisterCollision<Flea>(*this);
}

void Flea::spawnMushroom()
{
	// If tile doesn't have mushroom associated with it
	if (pTile->hasObject() == false)
	{
		MushroomFactory::createMushroom(pTile->getPos(), pTile);
		//tile->setTile(new Mushroom(tile->getPos(), tile));	// Spawn and assign a new mushroom to the tile
		ConsoleMsg::WriteLine("New Mushroom at: " + Tools::ToString(pTile->getPos()));
	}
	else
		ConsoleMsg::WriteLine("MUSHROOM ALREADY THERE");

	pTile = pTile->getDown();
}

/* COLLISIONS */
void Flea::Collision(Bullet *other)
{
	health -= BASE_HEALTH;

	if (health <= 0)
	{
		// Update score 
		FleaFactory::ReportDeath();
		MarkForDestroy();
	}
	else
		speed *= SPEED_INCREASE;
}