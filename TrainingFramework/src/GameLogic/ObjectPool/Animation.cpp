#include "Animation.h"

Animation::Animation(): m_IsActive(true)
{
}

Animation::Animation(std::shared_ptr<AnimationSprite> sprite, Vector2 Position)
{
	m_Sprite = sprite;
	m_Sprite->Set2DPosition(Position);
}

void Animation::Draw()
{
	m_Sprite->Draw();
}

void Animation::Update(float dt)
{
	m_Sprite->Update(dt);
	if (!(m_Sprite->IsActive()))
		Destroy();
}

void Animation::Destroy()
{
	m_Sprite->Set2DPosition(-100, -100);
	m_Sprite->Destroy();
	m_IsActive = false;
}

bool Animation::IsActive()
{
	return m_IsActive;
}

void Animation::Reset()
{
	m_IsActive = true;
	m_Sprite->Reset();
}

void Animation::SetPosition(Vector2 Position)
{
	m_Sprite->Set2DPosition(Position);
}
