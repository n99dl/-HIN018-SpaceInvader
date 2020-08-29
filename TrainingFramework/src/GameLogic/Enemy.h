#pragma once
#include "Entity.h"
#include <GameLogic\Bullet.h>
class Enemy :
    public Entity
{
protected:
    int m_Hp;
    int m_Speed;
    void CheckAlive();
public:
    Enemy();
    Enemy(Vector2 Position);
    ~Enemy();
    void Draw();
    void Update(float dt);
    void SetPosition(Vector2 Position);
    void Move(float delta);
    void DamageBy(std::shared_ptr<Bullet> _Bullet);
};

