/* SoundManager.h - Gage O'Connor, October 2017 */

#ifndef _SoundManager
#define _SoundManager

#include "TEAL\CommonElements.h"
#include <stack>

// Forward Declarations
class CommandSound;
class CommandSoundLoop;

class SoundManager
{
public:
	// Sound Events
	enum class SoundEvents { FleaSnd, FireSnd, PlayerDeathSnd, MushRegenSnd };
	enum class SoundLoopStartEvents { CentipedeBeatStrt, ScorpionBeatStrt, SpiderBeatStrt };

	static void PlaySound(sf::Sound& snd);
	static void StopSound(sf::Sound& snd);

	static CommandSound* GetSoundCommand(SoundEvents event);
	static CommandSoundLoop* GetSoundCommand(SoundLoopStartEvents event);

	static void SendSoundCommand(CommandSound * command);
	static void SendPauseCommand(CommandSound * command);

	static void ProcessSounds();
	static void PauseSounds();

private:
	SoundManager();
	float PITCH = 1;
	float VOL = 4;
	float VOL2 = 2;

	// Sounds
	sf::Sound CentipedeBeat;
	sf::Sound ScorpionBeat;
	sf::Sound SpiderBeat;

	sf::Sound FleaSnd;
	sf::Sound FireSnd;
	sf::Sound PlayerDeathSnd;
	sf::Sound MushRegenSnd;

	std::stack<CommandSound *> StackCommand;
	std::stack<CommandSound *> PauseCommand;

	static SoundManager* pInstance;

	static SoundManager& Instance()	// Access reference (all public methods will be static)
	{
		if (!pInstance)
			pInstance = new SoundManager;
		return *pInstance;
	};

	void privateProcessSound();
	void privatePauseSound();
};

#endif _SoundManager
