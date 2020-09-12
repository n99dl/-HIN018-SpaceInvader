#pragma once 
#include "Sprite2D.h"

class GameButton : public Sprite2D
{
public:
	GameButton(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~GameButton();
	void	SetOnClick(void	(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, int bIsPressed);
	bool	IsHandle();
	void    SetActive(bool isActive);
	bool IsActive();
private:
	void	(*m_pBtClick)();
	bool	m_isHandle;
	bool    m_isActive;
};
