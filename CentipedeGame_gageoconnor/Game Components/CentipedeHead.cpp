/* CentipedeHead.cpp - Gage O'Connor, October 2017 */

#include "CentipedeHead.h"
#include "Centipede_HeadFactory.h"
#include "Centipede_SegmentFactory.h"

#include "Head_MoveFSM.h"

CentipedeHead::CentipedeHead()
	: SCORE(Score::Centipede_Head),
	  pHead(this),
	  MAX_HEALTH(1)	
{
	// Initialize remaining variables
	health = MAX_HEALTH;
	pNext = 0;

	// Grab the bitmap and assign it to MainSprite
	bitmap = ResourceManager::GetTextureBitmap("centipede_head");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("centipede_head"), 8, 2);

	// Set the animation to loop
	MainSprite.SetLoopSpeed(8);
	MainSprite.SetAnimation(0, 7, true, true);

	// Set origin and scale
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(2, 2);

	// Sets and registers collision
	SetCollider(MainSprite, bitmap);
	MainSprite.setPosition(Pos);
}

void CentipedeHead::Initialize(Tile* pTile, sf::Vector2f pos, int index, const HeadMoveState* state, int num, CentipedeSegment* seg)
{
	this->pNext = seg;

	if (seg != 0)
		seg->setPrev(this);

	this->pTile = pTile; //(0, 14)
	this->pOldTile = this->pTile;
	this->index = index;
	this->Pos = pos; 
	this->oldPos = Pos;

	this->pCurrentState = state;
	health = MAX_HEALTH;

	/* Fixes rotation due to recycling */
	if (pCurrentState == &HeadMoveFSM::StateMoveLeftAndDown || pCurrentState == &HeadMoveFSM::StateMoveLeftAndUp)
		MainSprite.setRotation(0);
	if (pCurrentState == &HeadMoveFSM::StateMoveRightAndDown || pCurrentState == &HeadMoveFSM::StateMoveRightAndUp)
		MainSprite.setRotation(-180);

	// Creates new Centipede Segments
	if (num > 0)
		CreateSegments(num);

	WaveManager::SetCenti(this);
	RegisterCollision<CentipedeHead>(*this);
}

/* METHODS */
void CentipedeHead::Update()
{
	MainSprite.Update();

	if (index > int(pCurrentState->GetMoveOffsets().size() - 1)) // If no more moves, check State
	{ 
		pOldTile = pTile; // For segments to grab
		pCurrentState = pCurrentState->GetNextState(this); // Grab next State
		index = 0;
	}

	// Update position and move index
	Pos += sf::Vector2f(pCurrentState->GetMoveOffsets()[index].x, pCurrentState->GetMoveOffsets()[index].y);
	MainSprite.rotate(pCurrentState->GetMoveOffsets()[index].z);
	index++;

	MainSprite.setPosition(Pos);
}

void CentipedeHead::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void CentipedeHead::Destroy()
{
	WaveManager::FreeCenti(this);
	DeregisterCollision<CentipedeHead>(*this);
}

// Assigns Head's current Tile
void CentipedeHead::setTile(Tile *pTile)
{
	this->pTile = pTile;
}

// Returns Head's current Tile 
Tile *CentipedeHead::getTile()
{
	return this->pTile;
}

// Returns Head's last used Tile
Tile *CentipedeHead::getOldTile()
{
	return this->pOldTile;
}

// Creates a given number of Segments for a Head
void CentipedeHead::CreateSegments(int num)
{
	Centipede* traverse = this->pHead;
	for (int i = 0; i < num; i++)
	{
		CentipedeSegmentFactory::createCentipedeSegment(traverse->getTile(), traverse->getPos(), 0, &HeadMoveFSM::StateDoNothing, traverse);
		traverse = traverse->getNext();
	}
}

// Returns the Head's current Move State
const HeadMoveState *CentipedeHead::GetNextState()
{
	return this->pCurrentState;
}

// Returns the Head's current index
int CentipedeHead::GetIndex()
{
	return this->index;
}

void CentipedeHead::ReportHeadRecall()
{
	CentipedeHeadFactory::ReportRecall();
}

void CentipedeHead::Split()
{
	CentipedeSegment* temp1 = this->pHead->getNext(); // Point to adjacent segment
	if (pNext != 0) // If it is a segment
	{
		CentipedeHeadFactory::createCentipedeHead(temp1->getTile(), temp1->getPos(), temp1->GetIndex(), temp1->GetNextState(), 0, temp1->getNext()); // Spawns new Head adjacent

		//Remove the replaced Segment
		temp1->setNext(0);
		temp1->setPrev(0);
		temp1->Delete();
	}
}

void CentipedeHead::PlaceShroom()
{
	// Attempt to spawn mushroom
	if (pTile->hasObject() == false)
	{
		MushroomFactory::createMushroom(pTile->getPos(), pTile);
		ConsoleMsg::WriteLine("New Mushroom at: " + Tools::ToString(pTile->getPos()));
	}
}
/* COLLISIONS */
void CentipedeHead::Collision(Bullet *other)
{
	// Splits head appropriately
	Split();

	// Places a mushroom at current location
	PlaceShroom();

	// Add score and destroy
	CentipedeHeadFactory::ReportDeath();

	MarkForDestroy();
}

void CentipedeHead::Collision(Mushroom *other)
{

}