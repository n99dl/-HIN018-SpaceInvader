#pragma once
#include "gamestatebase.h"

class GSIntro :
	public GameStateBase
{
public:
	GSIntro();
	~GSIntro();

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
	std::shared_ptr<Sprite2D> m_bg;
	std::shared_ptr<Text>  m_Text_loading;
	float m_time;
};

