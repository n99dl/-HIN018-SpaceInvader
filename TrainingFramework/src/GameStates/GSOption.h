#pragma once
#include "GameStates/GameStatebase.h"
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

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;

};

