/* CommandSoundPause.h - Gage O'Connor, October 2017 */

#ifndef _CommandSoundPause
#define _CommandSoundPause

#include "CommandSoundLoop.h"

class CommandSoundPause : public CommandSoundLoop
{
public:
	CommandSoundPause() = delete;
	CommandSoundPause(sf::Sound& snd);

	virtual void Execute() override;

private:
	sf::Sound sound; // Sound
};

#endif _CommandSoundPause


