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
#define PLAYER_HIT 4
#define PLAYER_DEAD 5
#define HP_UP 6
#define GAME_OVER 7

class MediaPlayer : public CSingleton<MediaPlayer>
{
private:
	SoLoud::Soloud soloud;  // SoLoud engine core
	SoLoud::Wav menuMusic, 
				playMusic,
				playerShoot,
				powerUp,
				playerHit,
				playerDead,
				hpUp,
				gameOver;
	bool isMute;
	float volume;
	int musicHandleMap[20];
public:
	MediaPlayer();
	int TestSound();
	int PlaySound(int soundId);
	void StopSound(int soundId);
	int StopAllSound();
	void ToggleMute();
	void Mute();
	void UnMute();
	bool IsMute();
};

