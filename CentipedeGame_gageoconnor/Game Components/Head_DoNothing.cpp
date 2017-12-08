/* HeadDoNothing.h - Gage O'Connor, October 2017 */

#include "Head_DoNothing.h"
#include "Head_MoveFSM.h"

const HeadDoNothing HeadMoveFSM::StateDoNothing;

HeadDoNothing::HeadDoNothing()
{
	grabOffsets();
}
void HeadDoNothing::Show() const
{
	std::cout << "HeadDoNothing";
}

void HeadDoNothing::grabOffsets()
{
	for (int i = 0; i < CentipedeHead::FRAMES_PER_MOVEMENT; i++)
	{
		offsets.push_back(sf::Vector3f(0.0f, 0.0f, 0.0f));
	}
}