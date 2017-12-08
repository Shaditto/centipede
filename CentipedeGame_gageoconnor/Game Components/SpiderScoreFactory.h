/* SpiderScoreFactory.h - Gage O'Connor, October 2017 */

#ifndef _SpiderScoreFactory
#define _SpiderScoreFactory

#include <stack>
#include "SpiderScore.h"

/* Set up as a Singleton */
class SpiderScoreFactory
{
public:
	// Static services
	static void createSpiderScore(sf::Vector2f pos) { Instance().privateCreateSpiderScore(pos); };
	static void recycleSpiderScore(GameObject *pExp) { Instance().privateRecycleSpiderScore(pExp); };

	static void Terminate();

private:
	static SpiderScoreFactory *pInstance;	// Set up as Singleton

	SpiderScoreFactory() = default;
	SpiderScoreFactory(const SpiderScoreFactory &) = delete;					// Prevents copy-constructions
	SpiderScoreFactory & operator = (const SpiderScoreFactory &) = delete;		// Prevents assignment
	~SpiderScoreFactory();															// Only this can delete

	static SpiderScoreFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new SpiderScoreFactory;
		return *pInstance;
	};

	std::stack<SpiderScore *> recycledSpiderScores; // Non-static

	void privateCreateSpiderScore(sf::Vector2f pos);
	void privateRecycleSpiderScore(GameObject *pExp);
};

#endif _SpiderScoreFactory



