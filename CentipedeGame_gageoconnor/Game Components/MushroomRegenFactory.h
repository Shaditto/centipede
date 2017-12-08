/* MushroomRegenFactory.h - Gage O'Connor, October 2017 */

#ifndef _MushroomRegenFactory
#define _MushroomRegenFactory

#include <stack>
#include "MushroomRegen.h"
#include "Grid.h"

// Forward Declaration
class CommandSound;

/* Set up as a Singleton */
class MushroomRegenFactory
{
public:
	// Static services
	static void createMushroomRegen(sf::Vector2f pos) { Instance().privateCreateMushroomRegen(pos); };
	static void recycleMushroomRegen(GameObject *pRegen) { Instance().privateRecycleMushroomRegen(pRegen); };
	static void setGrid(Grid* pGrid) { Instance().privateSetGrid(pGrid); }
	static void Regenerate() { Instance().privateRegenerate(); }

	// Reporting sound to SoundManager
	static void PlaySound();

	static void Terminate();

private:
	static MushroomRegenFactory *pInstance;	// Set up as Singleton

	MushroomRegenFactory();
	MushroomRegenFactory(const MushroomRegenFactory &) = delete;					// Prevents copy-constructions
	MushroomRegenFactory & operator = (const MushroomRegenFactory &) = delete;		// Prevents assignment
	~MushroomRegenFactory();															// Only this can delete

	static MushroomRegenFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new MushroomRegenFactory;
		return *pInstance;
	};

	std::stack<MushroomRegen *> recycledMushroomRegens; // Non-static

	void privateCreateMushroomRegen(sf::Vector2f pos);
	void privateRecycleMushroomRegen(GameObject *pRegen);
	void privateSetGrid(Grid* pGrid);
	void privateRegenerate();

	CommandSound* pSound;	// Sound
	Grid* pGrid;
};

#endif _MushroomRegenFactory




