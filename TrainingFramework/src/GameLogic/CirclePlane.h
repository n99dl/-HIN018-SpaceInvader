#pragma once
#include "Enemy.h"
class CirclePlane :
    public Enemy
{
private:
    void Die();
public:
    CirclePlane();
    CirclePlane(float vPosition);
    CirclePlane(float vPosition, int type);
    ~CirclePlane();
    void Update(float dt);
    void Shoot();
    void CreateBulletAt(Vector2 Position);
};

