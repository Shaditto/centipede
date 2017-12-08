/* PlayerFactory.h - Gage O'Connor, October 2017 */

#ifndef _PlayerFactory
#define _PlayerFactory

#include <stack>
#include "Player.h"

/* Set up as a Singleton */
class PlayerFactory
{
public:
	// Static services
	static Player* createPlayer(Grid *pGrid) { return Instance().privateCreatePlayer(pGrid); };
	static void recyclePlayer(GameObject *player) { Instance().privateRecyclePlayer(player); };

	static void Terminate();

private:
	static PlayerFactory *pInstance;	// Set up as Singleton

	PlayerFactory() = default;
	PlayerFactory(const PlayerFactory &) = delete;					// Prevents copy-constructions
	PlayerFactory & operator = (const PlayerFactory &) = delete;	// Prevents assignment
	~PlayerFactory();												// Only this can delete

	static PlayerFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new PlayerFactory;
		return *pInstance;
	};

	std::stack<Player *> recycledPlayers; // Non-static

	Player* privateCreatePlayer(Grid *pGrid);
	void privateRecyclePlayer(GameObject *player);
};

#endif _PlayerFactory

