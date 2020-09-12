#include "MediaPlayer.h"
#include <iostream>

MediaPlayer::MediaPlayer()
{
	soloud.init();
	volume = soloud.getGlobalVolume();

	std::string SoundPath = "..\\Data\\Sounds\\";

	//Load Menu Music

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
	}

	return 0;
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
