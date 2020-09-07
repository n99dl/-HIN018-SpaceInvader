#pragma once
#include "Enemy.h"
class Motor :
    public Enemy
{
private:
    void Die();
    Vector2 m_Destination;
    float m_idleTime;
    bool m_IsIdling;
    void GenerateDestination();
public:
    Motor();
    Motor(Vector2 Position);
    ~Motor();
    void Update(float dt);
    void Shoot();

};

