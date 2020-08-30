#pragma once
#include "Enemy.h"
class DarkPlane :
    public Enemy
{
private:
    void Die();
public:
    DarkPlane();
    DarkPlane(float hPosition);
    ~DarkPlane();
    void Update(float dt);
};

