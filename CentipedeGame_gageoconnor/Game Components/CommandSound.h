/* CommandSound.h - Gage O'Connor, October 2017 */

#ifndef _CommandSound
#define _CommandSound

#include "CommandBase.h"

class CommandSound : public CommandBase
{
public:
	CommandSound() = delete;
	CommandSound(sf::Sound& snd);

	virtual void Execute() override;
	virtual void Pause();

protected:
	sf::Sound sound; // Sound
};

#endif _CommandSound
