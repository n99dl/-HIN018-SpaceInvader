#pragma once
#include "Sprite2D.h"

class AnimationSprite : public Sprite2D
{
public:
	AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> 
		shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, bool isRepeating);
	~AnimationSprite();
	void Init();
	void Draw();
	void Update(GLfloat deltatime);
	void Destroy();
	bool IsActive();
protected:
	int m_numFrames;
	float m_frameTime;
	int m_currentFrame;
	float m_currentTime;
	bool m_IsRepeating;
	bool m_IsActive;
};
