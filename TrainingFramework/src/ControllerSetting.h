#pragma once

#define MOUSE 0
#define KEYBOARD 1
class ControllerSetting
{
public:
	static int ControlType;
	static void SetControlType(int type);
	static int GetControlType();
};

