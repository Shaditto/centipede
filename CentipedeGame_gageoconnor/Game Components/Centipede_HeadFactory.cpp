/* CentipedeHeadFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "Centipede_HeadFactory.h"
#include "CentipedeHead.h"

#include "ScoreManager.h"
#include "SoundManager.h"

#include "CommandScore.h"
#include "CommandSoundLoop.h"

#include "WaveManager.h"

CentipedeHeadFactory *CentipedeHeadFactory::pInstance = nullptr;

CentipedeHeadFactory::CentipedeHeadFactory()
{
	// This command is created once only and reused every time this game object is active
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::CentipedeHeadDeath);
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundLoopStartEvents::CentipedeBeatStrt);

	counter = 0;
}

void CentipedeHeadFactory::privateCreateCentipedeHead(Tile* pTile, sf::Vector2f pos, int index, const HeadMoveState* state, int num, CentipedeSegment* seg)
{
	CentipedeHead* centi;

	if (recycledCentipedeHeads.empty())
	{
		//ConsoleMsg::WriteLine("New CentipedeHead");

		centi = new CentipedeHead();

		// Object will return here instead of being destroyed
		centi->SetExternalManagement(recycleCentipedeHead);
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled CentipedeHead");

		centi = recycledCentipedeHeads.top();
		recycledCentipedeHeads.pop();

		// Register back to scene
		centi->RegisterToCurrentScene();
	}
	centi->Initialize(pTile, pos, index, state, num, seg);

	if (Instance().counter == 0)
		PlaySound();

	Instance().counter++;
}

void CentipedeHeadFactory::privateRecycleCentipedeHead(GameObject* centi)
{
	recycledCentipedeHeads.push((CentipedeHead*)centi);
	//ConsoleMsg::WriteLine("Recycled CentipedeHead Size: " + Tools::ToString(recycledCentipedeHeads.size()));

	if (Instance().counter == 0)
	{
		PauseSound();
	}
		
}

void CentipedeHeadFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void CentipedeHeadFactory::ReportDeath()
{
	// Decrement Centipede Counter
	Instance().counter--;

	// If no more Centipedes, 
	if (Instance().counter == 0)
	{
		WaveManager::ProcessNextWave();
	}

	//ConsoleMsg::WriteLine("CentipedeHead Factory: Sending death score command\n");
	ScoreManager::SendScoreCommand(Instance().pDeath);
}

void CentipedeHeadFactory::ReportRecall()
{
	Instance().counter--;
}

void CentipedeHeadFactory::PlaySound()
{
	//ConsoleMsg::WriteLine("Centipede Sound: Sending Centipede sound command\n");
	SoundManager::SendSoundCommand(Instance().pSound);
}

void CentipedeHeadFactory::PauseSound()
{

	//ConsoleMsg::WriteLine("Centipede Sound: PAUSED");
	SoundManager::SendPauseCommand(Instance().pSound);
}

CentipedeHeadFactory::~CentipedeHeadFactory()
{
	//ConsoleMsg::WriteLine("Deleting Recycled CentipedeHeads (" + Tools::ToString(recycledCentipedeHeads.size()) + ")");

	// Forcefully delete Recycled CentipedeHeads
	while (!recycledCentipedeHeads.empty())
	{
		delete recycledCentipedeHeads.top();
		recycledCentipedeHeads.pop();
	}
}