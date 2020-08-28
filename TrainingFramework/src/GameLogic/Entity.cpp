#include "Entity.h"

Entity::Entity()
{
	m_Position = Vector2(0, 0);
	m_id = Entity::GetAvailableID();
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
