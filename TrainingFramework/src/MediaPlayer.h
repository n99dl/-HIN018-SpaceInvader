#pragma once

#include <iostream>
#include "GameManager/Singleton.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_file.h"
#include <vector>

#define MENU_MUSIC_ID 0
#define PLAY_MUSIC_ID 1
#define PLAYER_SHOOT_ID 2
#define POWER_UP_ID 3

class MediaPlayer : public CSingleton<MediaPlayer>
{
private:
	SoLoud::Soloud soloud;  // SoLoud engine core
	SoLoud::Wav menuMusic, 
				playMusic,
				playerShoot,
				powerUp;
public:
	MediaPlayer();
	int TestSound();
	int PlaySound(int soundId);
	int StopAllSound();
};

