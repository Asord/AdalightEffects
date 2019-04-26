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
		int nbLeds;

	public:
		virtual void update() = 0;

		void init(ArduinoController* controller) 
		{ 
			this->p_controller = controller;
			this->nbLeds = this->p_controller->getNbLeds();
		}
	};
}