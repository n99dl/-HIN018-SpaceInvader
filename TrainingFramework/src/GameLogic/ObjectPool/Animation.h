#pragma once
#include <AnimationSprite.h>
class Animation
{
public:
	Animation();
	Animation(std::shared_ptr<AnimationSprite> sprite, Vector2 Position);
	void Draw();
	void Update(float dt);
	void Destroy();
	bool IsActive();
	void Reset();
	void SetPosition(Vector2 Position);
protected:
	bool m_IsActive;
	std::shared_ptr<AnimationSprite> m_Sprite;
};

