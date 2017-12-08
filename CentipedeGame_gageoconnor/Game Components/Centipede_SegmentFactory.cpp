/* CentipedeSegmentFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "Centipede_SegmentFactory.h"
#include "CentipedeSegment.h"

#include "ScoreManager.h"
#include "CommandScore.h"

CentipedeSegmentFactory *CentipedeSegmentFactory::pInstance = nullptr;

CentipedeSegmentFactory::CentipedeSegmentFactory()
{
	// This command is created once only and reused every time this game object is active
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::CentipedeSegmentDeath);
}

void CentipedeSegmentFactory::privateCreateCentipedeSegment(Tile* pTile, sf::Vector2f pos, int index, const HeadMoveState* state, Centipede* body)
{
	CentipedeSegment* centi;

	if (recycledCentipedeSegments.empty())
	{
		ConsoleMsg::WriteLine("New CentipedeSegment");

		centi = new CentipedeSegment();

		// Object will return here instead of being destroyed
		centi->SetExternalManagement(recycleCentipedeSegment);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled CentipedeSegment");

		centi = recycledCentipedeSegments.top();
		recycledCentipedeSegments.pop();

		// Register back to scene
		centi->RegisterToCurrentScene();
	}
	centi->Initialize(pTile, pos, index, state, body);
}

void CentipedeSegmentFactory::privateRecycleCentipedeSegment(GameObject* centi)
{
	recycledCentipedeSegments.push((CentipedeSegment*)centi);
	ConsoleMsg::WriteLine("Recycled CentipedeSegment Size: " + Tools::ToString(recycledCentipedeSegments.size()));
}

void CentipedeSegmentFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void CentipedeSegmentFactory::ReportDeath()
{
	ConsoleMsg::WriteLine("CentipedeSegment Factory: Sending death score command\n");
	ScoreManager::SendScoreCommand(Instance().pDeath);
}

CentipedeSegmentFactory::~CentipedeSegmentFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled CentipedeSegments (" + Tools::ToString(recycledCentipedeSegments.size()) + ")");

	// Forcefully delete Recycled CentipedeSegments
	while (!recycledCentipedeSegments.empty())
	{
		delete recycledCentipedeSegments.top();
		recycledCentipedeSegments.pop();
	}
}