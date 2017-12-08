/* Wavedata.h - Gage O'Connor, October 2017 */

#include "TEAL\CommonElements.h"

#ifndef _WaveData
#define _WaveData

struct WaveData
{
	std::vector<float> currentWave;

	std::vector<float> centiLength;
	std::vector<float> centiSpeed;
	std::vector<float> centiHeads;

	std::vector<float> fleaPresent;
	std::vector<float> fleaRate;

	std::vector<float> scorpPresent;
	std::vector<float> scorpRate;
	std::vector<float> scorpSpeed;

	std::vector<float> spiderPresent;
	std::vector<float> spiderRate;
	std::vector<float> spiderSpeed;
};

#endif _WaveData