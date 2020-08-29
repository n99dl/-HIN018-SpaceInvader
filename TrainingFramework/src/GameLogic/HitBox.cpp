#include "HitBox.h"

HitBox::HitBox(): m_Position(Vector2(0,0) ), m_BoxSize(Vector2(0,0) )
{
}

HitBox::~HitBox()
{
	
}

HitBox::HitBox(Vector2 Position, Vector2 BoxSize) : m_Position(Position), m_BoxSize(BoxSize)
{
}

bool HitBox::IsCollide(std::shared_ptr<HitBox> _HitBox)
{
	Vector2 Position1 = m_Position;
	Vector2 Position2 = _HitBox->GetPosition();	
	Vector2 BoxSize1 = m_BoxSize;
	Vector2 BoxSize2 = _HitBox->GetBoxSize();

	if (abs(Position1.x - Position2.x) < BoxSize1.x + BoxSize2.x &&
		abs(Position1.y - Position2.y) < BoxSize1.y + BoxSize2.y)
	{
		return true;
	}
	return false;
}

void HitBox::SetPosition(Vector2 Position)
{
	m_Position = Position;
}

Vector2 HitBox::GetPosition()
{
	return m_Position;
}

Vector2 HitBox::GetBoxSize()
{
	return m_BoxSize;
}
