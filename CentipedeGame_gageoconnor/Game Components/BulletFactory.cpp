/* BulletFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "BulletFactory.h"
#include "Bullet.h"

#include "SoundManager.h"
#include "CommandSound.h"

BulletFactory *BulletFactory::pInstance = nullptr;

BulletFactory::BulletFactory()
{
	// This command is created once only and reused every time this game object is active
	pSound = SoundManager::GetSoundCommand(SoundManager::SoundEvents::FireSnd);
}


void BulletFactory::privateCreateBullet(sf::Vector2f pos, Player *player)
{
	Bullet *bullet;

	if (recycledBullets.empty())
	{
		ConsoleMsg::WriteLine("New Bullet");

		bullet = new Bullet(player);

		// Object will return here instead of being destroyed
		bullet->SetExternalManagement(recycleBullet);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Bullet");

		bullet = recycledBullets.top();
		recycledBullets.pop();

		// Register back to scene
		bullet->RegisterToCurrentScene();
	}
	bullet->Initialize(pos);
}

void BulletFactory::privateRecycleBullet(GameObject *bullet)
{
	recycledBullets.push((Bullet*)bullet);
	ConsoleMsg::WriteLine("Recycled Stack Size: " + Tools::ToString(recycledBullets.size()));
}

void BulletFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void BulletFactory::PlaySound()
{
	//ConsoleMsg::WriteLine("Bullet Sound: Sending bullet sound command\n");
	SoundManager::SendSoundCommand(Instance().pSound);
}

BulletFactory::~BulletFactory()
{
	//ConsoleMsg::WriteLine("Deleting Recycled Bullet (" + Tools::ToString(recycledBullets.size()) + ")");

	// Forcefully delete Recycled Bullets
	while (!recycledBullets.empty())
	{
		delete recycledBullets.top();
		recycledBullets.pop();
	}
}