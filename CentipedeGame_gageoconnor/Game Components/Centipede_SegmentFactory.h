/* CentipedeSegmentFactory.h - Gage O'Connor, October 2017 */

#ifndef _CentipedeSegmentFactory
#define _CentipedeSegmentFactory

#include <stack>
#include "CentipedeSegment.h"

// Forward Declaration
class CommandScore;

/* Set up as a Singleton*/
class CentipedeSegmentFactory
{
public:
	// Static services
	static void createCentipedeSegment(Tile* pTile, sf::Vector2f pos, int index, const HeadMoveState* state, Centipede* body) { Instance().privateCreateCentipedeSegment(pTile, pos, index, state, body); };
	static void recycleCentipedeSegment(GameObject* centi) { Instance().privateRecycleCentipedeSegment(centi); };

	// Reporting death to ScoreManager
	static void ReportDeath();

	static void Terminate();

private:
	static CentipedeSegmentFactory *pInstance;	// Set up as Singleton

	CentipedeSegmentFactory();
	CentipedeSegmentFactory(const CentipedeSegmentFactory &) = delete;					// Prevents copy-constructions
	CentipedeSegmentFactory & operator = (const CentipedeSegmentFactory &) = delete;	// Prevents assignment
	~CentipedeSegmentFactory();															// Only this can delete

	static CentipedeSegmentFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new CentipedeSegmentFactory;
		return *pInstance;
	};

	std::stack<CentipedeSegment *> recycledCentipedeSegments; // Non-static

	void privateCreateCentipedeSegment(Tile* pTile, sf::Vector2f pos, int index, const HeadMoveState* state, Centipede* body);
	void privateRecycleCentipedeSegment(GameObject* centi);

	// Reporting Scores
	CommandScore* pDeath;
};

#endif _CentipedeSegmentFactory

