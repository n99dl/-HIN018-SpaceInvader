#pragma once
#include <U_Math.h>
#include <iostream>
#include <Sprite2D.h>
class Entity
{
public:
	Entity();
	~Entity();
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	int GetID();
	void SetID(int id);

	static int availaible_id;
	static int GetAvailableID();
	static bool OutOfWindow(Vector2 Position);
	bool isActive();
protected:
	bool m_isActive;
	Vector2 m_Position;
	int m_id;
	std::shared_ptr<Sprite2D> m_Sprite;
	void CheckActive();
};

