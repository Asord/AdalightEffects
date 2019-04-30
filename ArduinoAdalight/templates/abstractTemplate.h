#pragma once
#include "../ArduinoController.h"
#include "../defines.h"

#include <AsColors.h>

namespace Asemco
{
#define isInstance(Type, ptr) dynamic_cast<Type*>(ptr) != nullptr

	class AbstractTemplate
	{
	protected:
		ArduinoController* p_controller;
		unsigned short nbLeds;

	public:
		virtual void update() = 0;

		void init(ArduinoController* controller) 
		{ 
			this->p_controller = controller;
			this->nbLeds = this->p_controller->getNbLeds();
		}
	};
}