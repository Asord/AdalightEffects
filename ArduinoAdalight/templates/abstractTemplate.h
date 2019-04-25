#pragma once
#include "../ArduinoController.h"
#include "../defines.h"

#include "../tools/color.h"

namespace Asemco
{
	class AbstractTemplate
	{
	protected:
		ArduinoController* p_controller;

	public:
		virtual void update() = 0;
	};
}