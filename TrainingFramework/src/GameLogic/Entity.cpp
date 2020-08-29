#include "Entity.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

Entity::Entity()
{
	m_Position = Vector2(0, 0);
	m_id = Entity::GetAvailableID();
	std::cout << "Entity created "<<m_id<<"\n";
}

Entity::~Entity()
{
	std::cout << "Entity " << m_id << " destroyed!\n";
}

int Entity::GetID()
{
	return m_id;
}

void Entity::SetID(int id)
{
	m_id = id;
}

int Entity::availaible_id = 0;

int Entity::GetAvailableID()
{
	return ++availaible_id;
}

bool Entity::OutOfWindow(Vector2 Position)
{
	if (Position.x < 0 || Position.x > screenWidth || Position.y < 0 || Position.y > screenHeight)
		return true;
	return false;
}


bool Entity::isActive()
{
	return m_isActive;
}

void Entity::CheckActive()
{
	if (Entity::OutOfWindow(m_Position))
		m_isActive = false;
}
