/* MushroomFactory.h - Gage O'Connor, October 2017 */

#ifndef _MushroomFactory
#define _MushroomFactory

#include <stack>
#include "Mushroom.h"

// Forward Declaration
class CommandScore;

/* Set up as a Singleton*/
class MushroomFactory
{
public:
	// Static services
	static void createMushroom(sf::Vector2f pos, Tile *pTile) { Instance().privateCreateMushroom(pos, pTile); };
	static void recycleMushroom(GameObject *pMush) { Instance().privateRecycleMushroom(pMush); };

	// Reporting death to ScoreManager
	static void ReportDeath();
	static void ReportPoisonDeath();
	static void ReportRegen();

	static void Terminate();

private:
	static MushroomFactory *pInstance;	// Set up as Singleton

	MushroomFactory();
	MushroomFactory(const MushroomFactory &) = delete;					// Prevents copy-constructions
	MushroomFactory & operator = (const MushroomFactory &) = delete;	// Prevents assignment
	~MushroomFactory();													// Only this can delete

	static MushroomFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new MushroomFactory;
		return *pInstance;
	};

	std::stack<Mushroom *> recycledMushrooms; // Non-static

	void privateCreateMushroom(sf::Vector2f pos, Tile *pTile);
	void privateRecycleMushroom(GameObject *Mushroom);

	// Reporting Scores
	CommandScore* pRegularDeath;
	CommandScore* pPoisonDeath;
	CommandScore* pRegen;
};

#endif _MushroomFactory

