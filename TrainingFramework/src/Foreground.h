#pragma once
#include <iostream>
#include <Sprite2D.h>
#include "Text.h"

class Foreground
{
protected:
	std::shared_ptr<Sprite2D> m_hpBarBackGround;
	std::vector<std::shared_ptr<Sprite2D> > m_hpDots;
	std::shared_ptr<Sprite2D> m_powerBarBackGround;
	std::shared_ptr<Sprite2D> m_bossHpBg;
	std::shared_ptr<Sprite2D> m_bossHp;
	std::shared_ptr<Text>  m_Text_wave;
	std::shared_ptr<Text>  m_Text_phase;
	std::vector<std::shared_ptr<Sprite2D> > m_powerDots;
	int m_Hp, m_Power;
public:
	Foreground();
	~Foreground();
	void Draw();
	void Update(float dt);
};

