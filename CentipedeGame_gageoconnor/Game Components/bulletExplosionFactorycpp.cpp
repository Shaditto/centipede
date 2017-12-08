/* bulletExplosionFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "bulletExplosionFactory.h"
#include "bulletExplosion.h"

bulletExplosionFactory *bulletExplosionFactory::pInstance = nullptr;

bulletExplosionFactory::bulletExplosionFactory()
{
}

void bulletExplosionFactory::privateCreatebulletExplosion(sf::Vector2f pos)
{
	bulletExplosion *pExp;

	if (recycledbulletExplosions.empty())
	{
		//ConsoleMsg::WriteLine("New bulletExplosion");

		pExp = new bulletExplosion();

		// Object will return here instead of being destroyed
		pExp->SetExternalManagement(recyclebulletExplosion);
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled bulletExplosion");

		pExp = recycledbulletExplosions.top();
		recycledbulletExplosions.pop();

		// Register back to scene
		pExp->RegisterToCurrentScene();
	}
	pExp->Initialize(pos);
}

void bulletExplosionFactory::privateRecyclebulletExplosion(GameObject *bullet)
{
	recycledbulletExplosions.push((bulletExplosion*)bullet);
	//ConsoleMsg::WriteLine("Recycled bulletExplosion Size: " + Tools::ToString(recycledbulletExplosions.size()));
}

void bulletExplosionFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

bulletExplosionFactory::~bulletExplosionFactory()
{
	//ConsoleMsg::WriteLine("Deleting Recycled bulletExplosions (" + Tools::ToString(recycledbulletExplosions.size()) + ")");

	// Forcefully delete Recycled bulletExplosions
	while (!recycledbulletExplosions.empty())
	{
		delete recycledbulletExplosions.top();
		recycledbulletExplosions.pop();
	}
}