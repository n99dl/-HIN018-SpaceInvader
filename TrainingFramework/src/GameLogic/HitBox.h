#pragma once
#include <U_Math.h>
#include <iostream>
class HitBox
{
private:
	Vector2 m_Position;
	Vector2 m_BoxSize;
public:
	HitBox();
	~HitBox();
	HitBox(Vector2 Position, Vector2 BoxSize);
	bool IsCollide(std::shared_ptr<HitBox> _HitBox);
	void SetPosition(Vector2 Position);
	Vector2 GetPosition();
	Vector2 GetBoxSize();
};

