/* CentipedeHeadFactory.h - Gage O'Connor, October 2017 */

#ifndef _CentipedeHeadFactory
#define _CentipedeHeadFactory

#include <stack>
#include "CentipedeHead.h"

// Forward Declaration
class CommandScore;
class CommandSoundLoop;

/* Set up as a Singleton */
class CentipedeHeadFactory
{
public:
	// Static services
	static void createCentipedeHead(Tile* pTile, sf::Vector2f pos, int index, const HeadMoveState* state, int num, CentipedeSegment* seg) { Instance().privateCreateCentipedeHead(pTile, pos, index, state, num, seg); };
	static void recycleCentipedeHead(GameObject* centi) { Instance().privateRecycleCentipedeHead(centi); };

	// Reporting death to ScoreManager
	static void ReportDeath();
	static void ReportRecall();

	static void PlaySound();	//
	static void PauseSound();	// Reporting sound to SoundManager

	static void Terminate();

private:
	static CentipedeHeadFactory *pInstance;	// Set up as Singleton

	CentipedeHeadFactory();
	CentipedeHeadFactory(const CentipedeHeadFactory &) = delete;					// Prevents copy-constructions
	CentipedeHeadFactory & operator = (const CentipedeHeadFactory &) = delete;		// Prevents assignment
	~CentipedeHeadFactory();														// Only this can delete

	static CentipedeHeadFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new CentipedeHeadFactory;
		return *pInstance;
	};

	std::stack<CentipedeHead *> recycledCentipedeHeads; // Non-static

	void privateCreateCentipedeHead(Tile* pTile, sf::Vector2f pos, int index, const HeadMoveState* state, int num, CentipedeSegment* seg);
	void privateRecycleCentipedeHead(GameObject* centi);

	CommandScore* pDeath;		// Reporting Scores
	CommandSoundLoop* pSound;	// Sound

	int counter;
};

#endif _CentipedeHeadFactory