#include "MediaPlayer.h"
#include <iostream>

MediaPlayer::MediaPlayer()
{
	soloud.init();
	volume = soloud.getGlobalVolume();

	std::string SoundPath = "..\\Data\\Sounds\\";

	//Load Menu Music

	for (int i = 0; i < 20; i++)
	{
		musicHandleMap[i] = -1;
	}
	std::string filePathString = SoundPath + "menu_music.mp3";
	const char* filePath = filePathString.c_str();
	FILE* p = fopen(filePath, "r");

	SoLoud::DiskFile* f = new SoLoud::DiskFile(p);
	menuMusic.loadFile(f);

	//Load Play Music

	filePathString = SoundPath + "play_music.mp3";
	filePath = filePathString.c_str();
	p = fopen(filePath, "r");

	f = new SoLoud::DiskFile(p);
	playMusic.loadFile(f);	

	//Load Player Shoot Sound

	filePathString = SoundPath + "player_shoot.wav";
	filePath = filePathString.c_str();
	playerShoot.load(filePath);

	//Load Player Shoot Sound

	filePathString = SoundPath + "power_up.wav";
	filePath = filePathString.c_str();
	powerUp.load(filePath);

	//load Player Hit

	filePathString = SoundPath + "player_hit.mp3";
	filePath = filePathString.c_str();
	p = fopen(filePath, "r");

	f = new SoLoud::DiskFile(p);
	playerHit.loadFile(f);

	//load Player Dead

	filePathString = SoundPath + "player_dead.mp3";
	filePath = filePathString.c_str();
	p = fopen(filePath, "r");

	f = new SoLoud::DiskFile(p);
	playerDead.loadFile(f);

	//load Hp UP

	filePathString = SoundPath + "hp_up.mp3";
	filePath = filePathString.c_str();
	p = fopen(filePath, "r");

	f = new SoLoud::DiskFile(p);
	hpUp.loadFile(f);

	//load GameOver

	filePathString = SoundPath + "GameOver.mp3";
	filePath = filePathString.c_str();
	p = fopen(filePath, "r");

	f = new SoLoud::DiskFile(p);
	gameOver.loadFile(f);
}

int MediaPlayer::TestSound()
{
	std::string SoundPath = "..\\Data\\Sounds\\";
	std::string filePathString = SoundPath + "test.mp3";
	const char* filePath = filePathString.c_str();
	FILE* p = fopen(filePath, "r");

	if (!p)
	{
		return -1;
	}
	SoLoud::DiskFile* f = new SoLoud::DiskFile(p);
	SoLoud::Wav newWav;
	newWav.loadFile(f);
	//m_wavList.push_back(newWav);
	soloud.play(newWav);
	std::cout << "Sound Played!\n";
	return 0;
}

int MediaPlayer::PlaySound(int soundId)
{
	int channel = 0;
	float v = 1.0f;
	//m_wavList.push_back(newWav);
	switch (soundId)
	{
	case MENU_MUSIC_ID:
		channel = soloud.play(menuMusic);
		soloud.setLooping(channel, true);
		break;
	case PLAY_MUSIC_ID:
		channel = soloud.play(playMusic);
		soloud.setLooping(channel, true);
		break;
	case PLAYER_SHOOT_ID:
		channel = soloud.play(playerShoot);
		v = soloud.getVolume(channel);
		soloud.setVolume(channel, v / 3.0f);
		break;
	case POWER_UP_ID:
		channel = soloud.play(powerUp);
		v = soloud.getVolume(channel);
		soloud.setVolume(channel, v / 0.2f);
		break;
	case PLAYER_HIT:
		channel = soloud.play(playerHit);
		v = soloud.getVolume(channel);
		soloud.setVolume(channel, v / 1.0f);
		break;
	case PLAYER_DEAD:
		channel = soloud.play(playerDead);
		v = soloud.getVolume(channel);
		soloud.setVolume(channel, v / 0.8f);
		break;
	case HP_UP:
		channel = soloud.play(hpUp);
		v = soloud.getVolume(channel);
		soloud.setVolume(channel, v / 1.0f);
		break;
	case GAME_OVER:
		channel = soloud.play(gameOver);
		v = soloud.getVolume(channel);
		soloud.setVolume(channel, v / 1.0f);
	}
	musicHandleMap[soundId] = channel;
	return 0;
}

void MediaPlayer::StopSound(int soundId)
{
	soloud.stop(musicHandleMap[soundId]);
}

int MediaPlayer::StopAllSound()
{
	soloud.stopAll();
	return 1;
}

void MediaPlayer::ToggleMute()
{
	isMute = !isMute;
	float fl = 1.0 - isMute;
	soloud.setGlobalVolume(fl * volume);
}

void MediaPlayer::Mute()
{
	isMute = true;
	soloud.setGlobalVolume(0.0f * volume);
	std::cout << "muting\n";
}

void MediaPlayer::UnMute()
{
	isMute = false;
	soloud.setGlobalVolume(1.0f * volume);
	std::cout << "unmuting\n";
}

bool MediaPlayer::IsMute()
{
	return isMute;
}
