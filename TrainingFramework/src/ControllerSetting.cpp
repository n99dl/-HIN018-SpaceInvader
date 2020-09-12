#include "ControllerSetting.h"

int ControllerSetting::ControlType = MOUSE;

void ControllerSetting::SetControlType(int type)
{
	ControllerSetting::ControlType = type;
}

int ControllerSetting::GetControlType()
{
	return ControllerSetting::ControlType;
}
