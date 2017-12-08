/* PlayerExplosionFactory.h - Gage O'Connor, October 2017 */

#ifndef _PlayerExplosionFactory
#define _PlayerExplosionFactory

#include <stack>
#include "PlayerExplosion.h"

// Forward declaration
class CommandSound;

/* Set up as a Singleton */
class PlayerExplosionFactory
{
public:
	// Static services
	static void createPlayerExplosion(sf::Vector2f pos) { Instance().privateCreatePlayerExplosion(pos); };
	static void recyclePlayerExplosion(GameObject *pExp) { Instance().privateRecyclePlayerExplosion(pExp); };

	// Reporting sound to SoundManager
	static void PlaySound();

	static void Terminate();

private:
	static PlayerExplosionFactory *pInstance;	// Set up as Singleton

	PlayerExplosionFactory();
	PlayerExplosionFactory(const PlayerExplosionFactory &) = delete;					// Prevents copy-constructions
	PlayerExplosionFactory & operator = (const PlayerExplosionFactory &) = delete;		// Prevents assignment
	~PlayerExplosionFactory();															// Only this can delete

	static PlayerExplosionFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new PlayerExplosionFactory;
		return *pInstance;
	};

	std::stack<PlayerExplosion *> recycledPlayerExplosions; // Non-static

	void privateCreatePlayerExplosion(sf::Vector2f pos);
	void privateRecyclePlayerExplosion(GameObject *pExp);

	CommandSound* pSound;	// Sound
};

#endif _PlayerExplosionFactory