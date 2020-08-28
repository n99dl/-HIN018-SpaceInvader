#pragma once
#include <U_Math.h>
#include "Sprite2D.h"
#include "Entity.h"
#include "../ControlConfig.h"

class Player : public Entity
{
protected:
	int m_Hp;
	int m_Speed;
	void FixPosition();
public:
	Player();
	~Player();
	void Draw();
	void Update(float dt);
	void Move(int KeyPressed, float dt);
	void MoveByMouse(int x, int y);
};

