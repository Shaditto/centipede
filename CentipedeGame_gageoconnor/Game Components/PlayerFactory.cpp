/* PlayerFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "PlayerFactory.h"
#include "Player.h"

PlayerFactory *PlayerFactory::pInstance = nullptr;

Player* PlayerFactory::privateCreatePlayer(Grid *pGrid)
{
	Player *player;

	if (recycledPlayers.empty())
	{
		ConsoleMsg::WriteLine("New Player");

		player = new Player();

		// Object will return here instead of being destroyed
		player->SetExternalManagement(recyclePlayer);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Player");

		player = recycledPlayers.top();
		recycledPlayers.pop();

		// Register back to scene
		player->RegisterToCurrentScene();
	}
	player->Initialize(pGrid);
	return player;
}

void PlayerFactory::privateRecyclePlayer(GameObject *player)
{
	recycledPlayers.push((Player*)player);
	ConsoleMsg::WriteLine("Recycled Player Size: " + Tools::ToString(recycledPlayers.size()));
}

void PlayerFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

PlayerFactory::~PlayerFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Players (" + Tools::ToString(recycledPlayers.size()) + ")");

	// Forcefully delete Recycled Players
	while (!recycledPlayers.empty())
	{
		delete recycledPlayers.top();
		recycledPlayers.pop();
	}
}