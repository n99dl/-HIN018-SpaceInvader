#pragma once
#include "Enemy.h"
class DarkPlane :
    public Enemy
{
private:
    void Move(float delta);
public:
    DarkPlane();
    DarkPlane(float hPosition);
    ~DarkPlane();
    void Update(float dt);
};

