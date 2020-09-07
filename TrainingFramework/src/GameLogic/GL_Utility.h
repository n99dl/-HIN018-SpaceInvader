#pragma once
#include <U_Math.h>
class GL_Utility
{
public:
	static float GetAngle(Vector2 vec);
	static float GetAngle(Vector2 firstPoint, Vector2 secondPoint);
	static Vector2 GetMoveVector(Vector2 firstPoint, Vector2 secondPoint);
};

