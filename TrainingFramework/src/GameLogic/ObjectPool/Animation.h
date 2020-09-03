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
protected:
	bool m_IsActive;
	std::shared_ptr<AnimationSprite> m_Sprite;
};

