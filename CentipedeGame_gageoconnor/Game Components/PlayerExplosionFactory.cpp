/* PlayerExplosionFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "PlayerExplosionFactory.h"
#include "PlayerExplosion.h"

#include "SoundManager.h"
#include "CommandSound.h"

PlayerExplosionFactory *PlayerExplosionFactory::pInstance = nullptr;

PlayerExplosionFactory::PlayerExplosionFactory()
{
	// This command is created once only and reused every time this game object is active
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::PlayerDeathSnd);
}

void PlayerExplosionFactory::privateCreatePlayerExplosion(sf::Vector2f pos)
{
	PlayerExplosion *pExp;

	if (recycledPlayerExplosions.empty())
	{
		ConsoleMsg::WriteLine("New PlayerExplosion");

		pExp = new PlayerExplosion();

		// Object will return here instead of being destroyed
		pExp->SetExternalManagement(recyclePlayerExplosion);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled PlayerExplosion");

		pExp = recycledPlayerExplosions.top();
		recycledPlayerExplosions.pop();

		// Register back to scene
		pExp->RegisterToCurrentScene();
	}
	pExp->Initialize(pos);
}

void PlayerExplosionFactory::privateRecyclePlayerExplosion(GameObject *player)
{
	recycledPlayerExplosions.push((PlayerExplosion*)player);
	ConsoleMsg::WriteLine("Recycled PlayerExplosion Size: " + Tools::ToString(recycledPlayerExplosions.size()));
}

void PlayerExplosionFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void PlayerExplosionFactory::PlaySound()
{
	ConsoleMsg::WriteLine("PlayerExplosion Sound: Sending PlayerExplosion sound command\n");
	SoundManager::SendSoundCommand(Instance().pSound);
}

PlayerExplosionFactory::~PlayerExplosionFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled PlayerExplosions (" + Tools::ToString(recycledPlayerExplosions.size()) + ")");

	// Forcefully delete Recycled PlayerExplosions
	while (!recycledPlayerExplosions.empty())
	{
		delete recycledPlayerExplosions.top();
		recycledPlayerExplosions.pop();
	}
}