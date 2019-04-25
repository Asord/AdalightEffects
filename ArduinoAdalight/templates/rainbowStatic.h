#pragma once

#include "abstractTemplate.h"

namespace Asemco
{
	class RainbowStatic :public AbstractTemplate
	{
	private:
		float f_step;
		float f_hue = 0.0f;

	public:
		RainbowStatic(ArduinoController*, float);
		void update();
	};
}