#pragma once
#include "gamestatebase.h"
#include "GameLogic/GameController.h"
#include "Foreground.h"

class Sprite2D;
class Sprite3D;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, int bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();

private:
	int m_frames;
	float m_totalFrameTime;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Foreground> m_Foreground;
	std::shared_ptr<GameController> m_GameController;
};

