#pragma once
#include "Enemy.h"
class ImperialSpaceShip :
    public Enemy
{
private:
    void Die();
    Vector2 m_Destination;
    float m_idleTime;
    bool m_IsIdling;
    float m_circleGunTiming;
    float m_circleGunCooldown;
    void GenerateDestination();
    void CreateE1BulletWithPattern(Vector2 Pattern);
    void ShootCircle();
    void CreateBulletAt(Vector2 Position);
    int m_Phase;
public:
    ImperialSpaceShip();
    ImperialSpaceShip(Vector2 Position);
    ~ImperialSpaceShip();
    void Update(float dt);
    void Shoot();
};

