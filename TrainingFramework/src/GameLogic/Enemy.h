#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
protected:
    int m_Hp;
    int m_Speed;
public:
    Enemy();
    Enemy(Vector2 Position);
    ~Enemy();
    void Draw();
    void Update(float dt);
    void SetPosition(Vector2 Position);
};

