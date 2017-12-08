#include "CommandSound.h"
#include "SoundManager.h" 

CommandSound::CommandSound(sf::Sound& snd)
	:sound(snd)
{
}

void CommandSound::Execute()
{
	SoundManager::PlaySound(sound);
}

void CommandSound::Pause()
{
	SoundManager::StopSound(sound);
}