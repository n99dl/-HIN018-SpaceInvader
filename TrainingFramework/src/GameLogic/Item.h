#pragma once
#include "Entity.h"
#include "ResourceManagers.h"
#include "GameLogicConfig.h"

class Item :
    public Entity
{
private:
    int m_Type;
    int m_Speed;
    Vector2 m_MovePatern;
public:
    Item();
    Item(int type, Vector2 Position);
    void Draw();
    void Update(float dt);
    void Move(float dt);
    void Destroy();
    int GetType();
    ~Item();
};

