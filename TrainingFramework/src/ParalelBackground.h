#pragma once
#include <iostream>
#include <Sprite2D.h>

class ParalelBackground
{
protected:
	std::shared_ptr<Sprite2D> m_Sprite1;
	std::shared_ptr<Sprite2D> m_Sprite2;
public:
	ParalelBackground();
	~ParalelBackground();
	void Draw();
	void Update(float dt);
};

