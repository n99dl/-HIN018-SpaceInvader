#pragma once
#include "Entity.h"
#include <GameLogic\Bullet.h>
class Enemy :
    public Entity
{
protected:
    bool m_IsBoss;
    int m_Hp;
    int m_Speed;
    int m_itemOdd;
    float m_As;
    float m_currentTime;
    Vector2 m_MovePatern;
    Vector2 m_BulletPatern;
    void CheckAlive();
    virtual void Die();
    void DropItem();
public:
    Enemy();
    Enemy(Vector2 Position);
    ~Enemy();
    void Draw();
    void Update(float dt);
    void SetPosition(Vector2 Position);
    void Move(float delta);
    void DamageBy(std::shared_ptr<Bullet> _Bullet);
    int getHp();
    void InstaDie();
    virtual void Shoot();
};

