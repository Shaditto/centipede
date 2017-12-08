/* CommandSoundLoop.h - Gage O'Connor, October 2017 */

#ifndef _CommandSoundLoop
#define _CommandSoundLoop

#include "CommandSound.h"

class CommandSoundLoop : public CommandSound
{
public:
	CommandSoundLoop() = delete;
	CommandSoundLoop(sf::Sound& snd);

	virtual void Execute() override;
	virtual void Pause();

private:
	sf::Sound sound; // Sound
};

#endif _CommandSoundLoop

