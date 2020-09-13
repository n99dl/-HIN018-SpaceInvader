#include "Entity.h"
#include <GameLogic\HitBox.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

Entity::Entity()
{
	m_Position = Vector2(0, 0);
	m_id = Entity::GetAvailableID();
	m_HitBox = std::make_shared<HitBox>();
	//std::cout << "Entity created "<<m_id<<"\n";
}

Entity::~Entity()
{
	//std::cout << "Entity " << m_id << " destroyed!\n";
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
	int offsetX = 300;
	int offsetY = 300;
	if (Position.x < 0 || Position.x > screenWidth 
		|| Position.y < -offsetY || Position.y > screenHeight)
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
	{
		m_isActive = false;
		RemoveFromScreen();
	}
}

std::shared_ptr<HitBox> Entity::GetHitBox()
{
	return m_HitBox;
}

bool Entity::IsCollide(std::shared_ptr<Entity> _Entity)
{
	if (!_Entity->isActive()) return false;
	return m_HitBox->IsCollide(_Entity->GetHitBox());
}

Vector2 Entity::GetPosition()
{
	return m_Position;
}

void Entity::RemoveFromScreen()
{
	m_Position = Vector2(-100, -100);
	m_Sprite->Set2DPosition(m_Position);
}
