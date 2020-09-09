#include "GL_Utility.h"

float GL_Utility::GetAngle(Vector2 vec)
{
	float theta = atan2f(vec.x, vec.y);
	return theta;
}

float GL_Utility::GetAngle(Vector2 firstPoint, Vector2 secondPoint)
{
	return GetAngle(secondPoint - firstPoint);
}

Vector2 GL_Utility::GetMoveVector(Vector2 firstPoint, Vector2 secondPoint)
{
	float theta = GL_Utility::GetAngle(firstPoint, secondPoint);
	Vector2 p_BulletPatern = Vector2(sinf(theta), cosf(theta)) * 1.0;
	return p_BulletPatern;
}

Vector2 GL_Utility::GetMoveVector(float angle)
{
	Vector2 p_BulletPatern = Vector2(sinf(angle), cosf(angle)) * 1.0;
	return p_BulletPatern;
}
