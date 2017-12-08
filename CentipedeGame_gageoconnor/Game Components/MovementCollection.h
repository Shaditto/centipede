/* MovementCollection.h - Gage O'Connor, October 2017 */
#ifndef _MovementCollection
#define _MovementCollection

#include "TEAL\CommonElements.h"
#include "CentipedeHead.h"

class MovementCollection
{
public:
	static const std::vector<sf::Vector2f> OffsetsStraightRight;
	static const std::vector<sf::Vector2f> OffsetsTurnUpEndRight;
	static const std::vector<sf::Vector2f> OffsetsTurnDownEndRight;
	static const std::vector<sf::Vector2f> OffsetsStraightLeft;
	static const std::vector<sf::Vector2f> OffsetsTurnUpEndLeft;
	static const std::vector<sf::Vector2f> OffsetsTurnDownEndLeft;
};

#endif _MovementCollection