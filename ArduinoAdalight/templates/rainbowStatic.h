#pragma once

#include <VirtualTemplate.h>

namespace Asemco
{
	class RainbowStatic :public VirtualTemplate
	{
	private:
		FLOAT f_step;
		FLOAT f_hue = 0.0f;

	public:
		RainbowStatic(Controller*, FLOAT);
		VOID Update();
	};
}