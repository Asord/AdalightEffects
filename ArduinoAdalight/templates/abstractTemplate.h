#pragma once
#include "../ArduinoController.h"
#include "../defines.h"

#include "../tools/color.h"

namespace Asemco
{
#define isInstance(Type, ptr) dynamic_cast<Type*>(ptr) != nullptr

	class AbstractTemplate
	{
	protected:
		ArduinoController* p_controller;

	public:
		virtual void update() = 0;
	};
}