/* Spider.cpp - Gage O'Connor, October 2017 */

#include "Spider.h"
#include "SpiderFactory.h"
#include "SpiderScoreFactory.h"
#include "WaveManager.h"
#include "Bullet.h"

Spider::Spider()
	: MAXHEALTH(1)
{
	// Initialize other variables
	health = MAXHEALTH; //warbubg
	SPEED = 1;
	frameCounter = 0;
	pickMove = rand() % 2;
	currentMove = isMovingUp;

	// Grab the bitmap and assign it to MainSprite
	bitmap = ResourceManager::GetTextureBitmap("spider");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("spider"), 4, 2);

	// Set the animation to loop
	MainSprite.SetLoopSpeed(4);
	MainSprite.SetAnimation(0, 3, true, true);

	// Sets origin
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);

	//Sets collision
	SetCollider(MainSprite, bitmap);
}

void Spider::Initialize(Tile *tile, float side)
{
	// Negative means facing right, otherwise left
	MainSprite.setScale(float(-side*randChance), 2);
	SPEED = -side; //warning

	this->tile = tile;
	Pos = tile->getPos();
	tile = tile->getUp();
	currentMove = isMovingUp;
	frameCounter = 0;

	WaveManager::SetSpider(this);
	RegisterCollision<Spider>(*this);
}

/* METHODS */
void Spider::Update()
{
	MainSprite.Update();
	++frameCounter; // Our frame counter

	if (frameCounter % FRAMES_PER_MOVEMENT == 0) // Every 'x' frames do a movement check
	{
		if (tile!= 0)
			EatShroom(tile); // Attempts to eat mushroom
		CheckMovement();
	}

	if (currentMove == isMovingUp)
		MoveUp();
	else if (currentMove == isMovingDown)
		MoveDown();
	else if (currentMove == isDiagUpRight)
		MoveDiagUpRight();
	else if (currentMove == isDiagDownRight)
		MoveDiagDownRight();
	else if (currentMove == isDiagUpLeft)
		MoveDiagUpLeft();
	else if (currentMove == isDiagDownLeft)
		MoveDiagDownLeft();

	//Destroys when offscreen on left
	if (Pos.x <= -offset)
	{
		MarkForDestroy();
	}
	//destroys when offscreen on right
	else if (Pos.x >= WindowManager::MainWindow.getView().getSize().x + FRAMES_PER_MOVEMENT)
	{
		MarkForDestroy();
	}
	else if (Pos.y >= WindowManager::MainWindow.getView().getSize().y + offset_Y)
		MarkForDestroy();
	MainSprite.setPosition(Pos);
}

void Spider::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Spider::Destroy()
{
	WaveManager::FreeSpider(this);
	DeregisterCollision<Spider>(*this);
}

void Spider::EatShroom(Tile *tile)
{
	// If tile doesn't have mushroom associated with it
	if (tile->hasObject() == true)
	{
		tile->getObject()->MarkForDestroy();
		tile->setTile(0);
	}
	else
		ConsoleMsg::WriteLine("No Object");

}

// Check Movement Methods
void Spider::CheckMovement()
{
	if (currentMove == isMovingUp)
		CheckUp();
	else if (currentMove == isMovingDown)
		CheckDown();
	else if (currentMove == isDiagDownRight || currentMove == isDiagDownLeft)
		CheckDiagDown();
	else if (currentMove == isDiagUpRight || currentMove == isDiagUpLeft)
		CheckDiagUp();
}

void Spider::CheckDiagUp()
{
	pickMove = rand() % randChance;

	if (pickMove == 0)
	{
		currentMove = isMovingDown;

		if (tile != 0)
			tile = tile->getDown();
	}
	else
	{
		if (SPEED < 0)	// If moving left->right
		{
			currentMove = isDiagDownRight;
			if (tile != 0 && tile->getDown() != 0 && tile->getDown()->getRight() != 0)
				tile = tile->getDown()->getRight();
		}
		else			// Moving Right -> Left
		{
			currentMove = isDiagDownLeft;
			if (tile != 0 && tile->getDown() != 0 && tile->getDown()->getRight() != 0)
				tile = tile->getDown()->getRight();
		}
	}
}

void Spider::CheckDiagDown()
{
	pickMove = rand() % randChance;

	if (pickMove == 0)
	{
		currentMove = isMovingUp;
		if (tile != 0)
			tile = tile->getUp();
	}
	else
	{
		if (SPEED < 0)	// If moving left->right
		{
			currentMove = isDiagUpRight;
			if (tile != 0 &&  tile->getUp() != 0 && tile->getUp()->getRight() != 0)
				tile = tile->getUp()->getRight();
		}
		else			// Moving Right -> Left
		{
			currentMove = isDiagUpLeft;
			if (tile != 0 &&  tile->getUp() != 0 && tile->getUp()->getLeft() != 0)
				tile = tile->getUp()->getLeft();
		}
	}
}

void Spider::CheckUp()
{
	pickMove = rand() % randChance;

	if (pickMove == 0)
	{
		currentMove = isMovingDown;
		if (tile != 0)
			tile = tile->getDown();
	}
	else
	{
		if (SPEED < 0)	// If moving left->right
		{
			currentMove = isDiagDownRight;
			if (tile != 0 && tile->getDown() != 0 && tile->getDown()->getRight() != 0)
				tile = tile->getDown()->getRight();
		}
		else			// Moving Right -> Left
		{
			currentMove = isDiagDownLeft;
			if (tile != 0 && tile->getDown() != 0 && tile->getDown()->getRight() != 0)
				tile = tile->getDown()->getRight();
		}
		
	}
}

void Spider::CheckDown()
{
	pickMove = rand() % randChance;

	if (pickMove == 0)
	{
		currentMove = isMovingUp;
		if (tile != 0)
			tile = tile->getUp();
	}
	else
	{
		if (SPEED < 0)	// If moving left->right
		{
			currentMove = isDiagUpRight;
			if (tile != 0 && tile->getUp() != 0 && tile->getDown()->getRight() != 0)
				tile = tile->getUp()->getRight();
		}
		else			// Moving Right -> Left
		{
			currentMove = isDiagUpLeft;
			if (tile != 0 && tile->getUp() != 0 && tile->getUp()->getLeft() != 0)
				tile = tile->getUp()->getLeft();
		}
	}
}

// Actual Movement
void Spider::MoveDiagUpRight()
{
	Pos.x -= SPEED;
	Pos.y += SPEED;
}

void Spider::MoveDiagDownRight()
{
	Pos.x -= SPEED;
	Pos.y -= SPEED;
}

void Spider::MoveDiagUpLeft()
{
	Pos.x -= SPEED;
	Pos.y += SPEED;
}

void Spider::MoveDiagDownLeft()
{
	Pos.x -= SPEED;
	Pos.y -= SPEED;
}

void Spider::MoveUp()
{
	Pos.y += SPEED;
}
void Spider::MoveDown()
{
	Pos.y -= SPEED;
}

/* COLLISIONS */
void Spider::Collision(Bullet* other)
{
	SpiderScoreFactory::createSpiderScore(Pos);

	// Update score based on distance
	SpiderFactory::ReportSpiderDeath(int(other->getStrtPos() - this->Pos.y));
	MarkForDestroy();
}