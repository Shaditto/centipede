/* MushroomRegenFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "MushroomRegenFactory.h"
#include "MushroomRegen.h"

#include "SoundManager.h"
#include "CommandSound.h"

MushroomRegenFactory *MushroomRegenFactory::pInstance = nullptr;

MushroomRegenFactory::MushroomRegenFactory()
{
	// This command is created once only and reused every time this game object is active
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::MushRegenSnd);
}

void MushroomRegenFactory::privateCreateMushroomRegen(sf::Vector2f pos)
{
	MushroomRegen *pScore;

	if (recycledMushroomRegens.empty())
	{
		ConsoleMsg::WriteLine("New MushroomRegen");

		pScore = new MushroomRegen();

		// Object will return here instead of being destroyed
		pScore->SetExternalManagement(recycleMushroomRegen);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled MushroomRegen");

		pScore = recycledMushroomRegens.top();
		recycledMushroomRegens.pop();

		// Register back to scene
		pScore->RegisterToCurrentScene();
	}
	pScore->Initialize(pos);
}

void MushroomRegenFactory::privateRecycleMushroomRegen(GameObject *mush)
{
	recycledMushroomRegens.push((MushroomRegen*)mush);
	ConsoleMsg::WriteLine("Recycled MushroomRegen Size: " + Tools::ToString(recycledMushroomRegens.size()));
}

void MushroomRegenFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void MushroomRegenFactory::PlaySound()
{
	ConsoleMsg::WriteLine("Regen Sound: Sending regen sound command\n");
	SoundManager::SendSoundCommand(Instance().pSound);
}

void MushroomRegenFactory::privateSetGrid(Grid* pGrid)
{
	Instance().pGrid = pGrid;
}

void MushroomRegenFactory::privateRegenerate()
{
	Instance().pGrid->RegenMushrooms();
}

MushroomRegenFactory::~MushroomRegenFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled MushroomRegens (" + Tools::ToString(recycledMushroomRegens.size()) + ")");

	// Forcefully delete Recycled MushroomRegens
	while (!recycledMushroomRegens.empty())
	{
		delete recycledMushroomRegens.top();
		recycledMushroomRegens.pop();
	}
}