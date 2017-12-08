#include "CommandSoundLoop.h"
#include "SoundManager.h"

CommandSoundLoop::CommandSoundLoop(sf::Sound& snd)
	: CommandSound(snd)
{

}

void CommandSoundLoop::Execute()
{
	CommandSound::Execute();
}

void CommandSoundLoop::Pause()
{
	CommandSound::Pause();
}