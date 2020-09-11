#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "MediaPlayer.h"
#include <AnimationSprite.h>

class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();
	
	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, int bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_Text_gameName;
	std::shared_ptr<AnimationSprite>  m_AnimationTest;
	SoLoud::Wav m_MenuSound;
};

