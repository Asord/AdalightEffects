#pragma once
#include "SerialController.h"

namespace Asemco
{
	class VirtualTemplate
	{
	protected:
		UINT effectID;
		Controller* controller;

	public:
		VirtualTemplate(UINT effectID, Controller* controller) 
		{ 
			this->effectID = effectID;
			this->controller = controller; 
		};

		virtual VOID Update() = 0;

		UINT getID() { return this->effectID; };
	};
}