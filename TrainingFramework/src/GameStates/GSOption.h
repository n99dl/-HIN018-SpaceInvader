#pragma once
#include "GameStates/GameStatebase.h"
#include <GameButton.h>
class GSOption :
    public GameStateBase
{
public:
	GSOption();
	~GSOption();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, int bIsPressed);
	void Update(float deltaTime);
	void Draw();

protected:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<GameButton> m_mute;
	std::shared_ptr<GameButton> m_unmute;
	std::shared_ptr<GameButton> m_mouse;
	std::shared_ptr<GameButton> m_keyboard;
	std::list<std::shared_ptr<Text>> m_listText;
	std::shared_ptr<Text> m_soundText;
	std::shared_ptr<Text> m_controlTypeText;
	void SetStateMuteBtn();
	bool m_isMute;
	int m_ControlType;
};

