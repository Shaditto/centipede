/* BulletFactory.h - Gage O'Connor, October 2017 */

#ifndef _BulletFactory
#define _BulletFactory

#include <stack>
#include "Bullet.h"

// Forward declaration
class Player;
class CommandSound;

/* Set up as a Singleton */
class BulletFactory
{
public:
	// Static services
	static void createBullet(sf::Vector2f pos, Player *player) { Instance().privateCreateBullet(pos, player); };
	static void recycleBullet(GameObject *bullet) { Instance().privateRecycleBullet(bullet); };

	// Reporting sound to SoundManager
	static void PlaySound();

	static void Terminate();

private:
	static BulletFactory *pInstance;	// Set up as Singleton

	BulletFactory();
	BulletFactory(const BulletFactory &) = delete;					// Prevents copy-construction
	BulletFactory & operator = (const BulletFactory &) = delete;	// Prevents assignment
	~BulletFactory();												// Only this can delete

	static BulletFactory & Instance()	// Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new BulletFactory;
		return *pInstance;
	};

	std::stack<Bullet *> recycledBullets;	// Non-static

	void privateCreateBullet(sf::Vector2f pos, Player *player);
	void privateRecycleBullet(GameObject *bullet);

	
	Player *player;			// Tracking amount of bullets
	CommandSound* pSound;	// Sound
};
#endif _BulletFactory