/* CentipedeSegment.cpp - Gage O'Connor, October 2017 */

#include "CentipedeSegment.h"
#include "Centipede_HeadFactory.h"
#include "Centipede_SegmentFactory.h"
#include "Head_MoveFSM.h"

CentipedeSegment::CentipedeSegment()
	: SCORE(Score::Centipede_Segment),
	  MAX_HEALTH(1)
{
	// Initialize remaining variables
	health = MAX_HEALTH;
	pNext = 0;

	// Grab the bitmap and assign it to MainSprite
	bitmap = ResourceManager::GetTextureBitmap("centipede_segment");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("centipede_segment"), 8, 2);

	// Set the animation to loop
	MainSprite.SetLoopSpeed(4);
	MainSprite.SetAnimation(0, 7, true, true);

	// Set origin and scale
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(2, 2);

	// Sets and registers collision
	SetCollider(MainSprite, bitmap);

	// Sets position and registers collision for bullet
	MainSprite.setPosition(Pos);
}

void CentipedeSegment::Initialize(Tile* pTile, sf::Vector2f pos, int index, const HeadMoveState* state, Centipede* body)
{
	this->pPrev = body;
	body->setNext(this);

	this->pNext = 0;
	this->pTile = pTile;
	this->pNextTile = pTile;
	this->index = index;
	this->Pos = pos; 
	this->pCurrentState = state;
	this->pNextState = pCurrentState;

	health = MAX_HEALTH;

	/* Fixes rotation due to recycling */
	if (pCurrentState == &HeadMoveFSM::StateMoveLeftAndDown || pCurrentState == &HeadMoveFSM::StateMoveLeftAndUp)
		MainSprite.setRotation(0);
	if (pCurrentState == &HeadMoveFSM::StateMoveRightAndDown || pCurrentState == &HeadMoveFSM::StateMoveRightAndUp)
		MainSprite.setRotation(-180);

	WaveManager::SetCenti(this);
	RegisterCollision<CentipedeSegment>(*this);
}

void CentipedeSegment::Update()
{
	MainSprite.Update();

	if (index > int(pCurrentState->GetMoveOffsets().size() - 1)) // If no more moves, check State
	{
		pTile = pNextTile;
		pCurrentState = pNextState;
		index = 0;
	}

	pNextState = pPrev->GetNextState();
	pNextTile = pPrev->getTile();

	Pos += sf::Vector2f(pCurrentState->GetMoveOffsets()[index].x, pCurrentState->GetMoveOffsets()[index].y);
	MainSprite.rotate(pCurrentState->GetMoveOffsets()[index].z);
	index++;

	MainSprite.setPosition(Pos);
}

void CentipedeSegment::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void CentipedeSegment::Destroy()
{
	WaveManager::FreeCenti(this);
	DeregisterCollision<CentipedeSegment>(*this);
}

Tile *CentipedeSegment::getTile()
{
	return this->pTile;
}

const HeadMoveState *CentipedeSegment::GetNextState()
{
	return this->pCurrentState;
}

int CentipedeSegment::GetIndex()
{
	return this->index;
}

void CentipedeSegment::Delete()
{
	MarkForDestroy();
}

void CentipedeSegment::PlaceShroom()
{
	// Attempts to spawn a Mushroom
	if (pTile->hasObject() == false)
	{
		MushroomFactory::createMushroom(pTile->getPos(), pTile);
		ConsoleMsg::WriteLine("New Mushroom at: " + Tools::ToString(pTile->getPos()));
	}
}

void CentipedeSegment::Split()
{
	CentipedeSegment* temp1 = this->getNext();
	CentipedeHeadFactory::createCentipedeHead(temp1->getTile(), temp1->getPos(), temp1->GetIndex(), temp1->GetNextState(), 0, temp1->getNext()); // Spawns new Head adjacent

	this->getPrev()->setNext(0); // Free end of orig centipede

	// Remove the Segment that was replaced with a Head
	temp1->setNext(0);
	temp1->setPrev(0);
	temp1->Delete();
}

/* COLLISIONS */
void CentipedeSegment::Collision(Bullet *other)
{
	if (pNext == 0 && pPrev != 0) // Tail split
	{
		pPrev->setNext(0);
	}
	else if (pNext != 0)		 // Mid split, Behind head split, 2nd to last split
	{
		Split();
	}

	// Attempts to spawn a Mushroom
	PlaceShroom();

	// Add score and destroy
	CentipedeSegmentFactory::ReportDeath();
	MarkForDestroy();
}