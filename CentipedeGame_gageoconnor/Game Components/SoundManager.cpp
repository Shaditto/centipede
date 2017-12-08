/* SoundManager.h - Gage O'Connor, October 2017 */

#include "SoundManager.h"

#include "TEAL/CommonElements.h"
#include "CommandSound.h"
#include "CommandSoundLoop.h"

SoundManager* SoundManager::pInstance = nullptr;

SoundManager::SoundManager()
{
	FireSnd.setBuffer(ResourceManager::GetSound("fire1"));
	FireSnd.setPitch(PITCH);
	FireSnd.setVolume(VOL2);

	CentipedeBeat.setBuffer(ResourceManager::GetSound("beat"));
	CentipedeBeat.setPitch(PITCH);
	CentipedeBeat.setVolume(VOL);
	CentipedeBeat.setLoop(true);

	ScorpionBeat.setBuffer(ResourceManager::GetSound("scorpion_new"));
	ScorpionBeat.setPitch(PITCH);
	ScorpionBeat.setVolume(VOL);
	ScorpionBeat.setLoop(true);

	SpiderBeat.setBuffer(ResourceManager::GetSound("spider_new"));
	SpiderBeat.setPitch(PITCH);
	SpiderBeat.setVolume(VOL);
	SpiderBeat.setLoop(true);

	FleaSnd.setBuffer(ResourceManager::GetSound("flea_new"));
	FleaSnd.setPitch(PITCH);
	FleaSnd.setVolume(VOL);

	PlayerDeathSnd.setBuffer(ResourceManager::GetSound("death"));
	PlayerDeathSnd.setPitch(PITCH);
	PlayerDeathSnd.setVolume(VOL);

	MushRegenSnd.setBuffer(ResourceManager::GetSound("bonus"));
	MushRegenSnd.setPitch(PITCH);
	MushRegenSnd.setVolume(VOL);
}

CommandSound* SoundManager::GetSoundCommand(SoundEvents event)
{
	CommandSound* pCommand = nullptr;

	switch (event)
	{
	case SoundEvents::FleaSnd:
		pCommand = new CommandSound(Instance().FleaSnd);
		break;
	case SoundEvents::FireSnd:
		pCommand = new CommandSound(Instance().FireSnd);
		break;
	case SoundEvents::PlayerDeathSnd:
		pCommand = new CommandSound(Instance().PlayerDeathSnd);
		break;
	case SoundEvents::MushRegenSnd:
		pCommand = new CommandSound(Instance().MushRegenSnd);
		break;
	default:
		break;
	}

	return pCommand;
}

CommandSoundLoop* SoundManager::GetSoundCommand(SoundLoopStartEvents event)
{
	CommandSoundLoop* pCommand = nullptr;

	switch (event)
	{
	case SoundLoopStartEvents::CentipedeBeatStrt:
		pCommand = new CommandSoundLoop(Instance().CentipedeBeat);
		break;
	case SoundLoopStartEvents::ScorpionBeatStrt:
		pCommand = new CommandSoundLoop(Instance().ScorpionBeat);
		break;
	case SoundLoopStartEvents::SpiderBeatStrt:
		pCommand = new CommandSoundLoop(Instance().SpiderBeat);
		break;
	default:
		break;
	}

	return pCommand;
}

void SoundManager::PlaySound(sf::Sound& snd)
{
	snd.play();
}

void SoundManager::StopSound(sf::Sound& snd)
{
	snd.stop();
}

void SoundManager::SendSoundCommand(CommandSound* command)
{
	Instance().StackCommand.push(command);
}

void SoundManager::SendPauseCommand(CommandSound* command)
{
	Instance().PauseCommand.push(command);
}

void SoundManager::ProcessSounds()
{
	Instance().privateProcessSound();
}

void SoundManager::PauseSounds()
{
	Instance().privatePauseSound();
}

void SoundManager::privateProcessSound()
{
	CommandSound* pCommand;

	while (!StackCommand.empty())
	{
		pCommand = StackCommand.top();
		pCommand->Execute();

		StackCommand.pop();
	}
}

void SoundManager::privatePauseSound()
{
	CommandSound* pCommand;

	while (!PauseCommand.empty())
	{
		pCommand = PauseCommand.top();
		pCommand->Pause();

		PauseCommand.pop();
	}
}