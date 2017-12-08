/* bulletExplosionFactory.h - Gage O'Connor, October 2017 */

#ifndef _bulletExplosionFactory
#define _bulletExplosionFactory

#include <stack>
#include "bulletExplosion.h"

/* Set up as a Singleton */
class bulletExplosionFactory
{
public:
	// Static services
	static void createbulletExplosion(sf::Vector2f pos) { Instance().privateCreatebulletExplosion(pos); };
	static void recyclebulletExplosion(GameObject *pExp) { Instance().privateRecyclebulletExplosion(pExp); };

	static void Terminate();

private:
	static bulletExplosionFactory *pInstance;	// Set up as Singleton

	bulletExplosionFactory();
	bulletExplosionFactory(const bulletExplosionFactory &) = delete;					// Prevents copy-constructions
	bulletExplosionFactory & operator = (const bulletExplosionFactory &) = delete;		// Prevents assignment
	~bulletExplosionFactory();															// Only this can delete

	static bulletExplosionFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new bulletExplosionFactory;
		return *pInstance;
	};

	std::stack<bulletExplosion *> recycledbulletExplosions; // Non-static

	void privateCreatebulletExplosion(sf::Vector2f pos);
	void privateRecyclebulletExplosion(GameObject *pExp);
};

#endif _bulletExplosionFactory
