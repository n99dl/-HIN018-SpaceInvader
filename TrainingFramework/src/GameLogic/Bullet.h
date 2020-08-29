#pragma once
#include "Entity.h"
class Bullet :
    public Entity
{
protected:
    int m_Speed;
    Vector2 m_BulletPatern;
    int m_Power;
public:
    Bullet();
    Bullet(Vector2 Position);
    ~Bullet();
    void Draw();
    void Update(float dt);
    void SetPosition(Vector2 Position);
    void SetBulletPatern(Vector2 BulletPatern);
    void Move(float dt);
    int GetPower();
    void SelfDestruct();
    static std::shared_ptr<Bullet> Create(Vector2 Position);
};

