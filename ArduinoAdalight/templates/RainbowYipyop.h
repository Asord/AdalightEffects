#pragma once
#include "abstractTemplate.h"

namespace Asemco
{
	class RainbowYipyop :public AbstractTemplate
	{
	private:
		float f_currentHue;
		float f_step;
		int n_positionHue;
		int n_directionHue;

	public:
		RainbowYipyop(ArduinoController*);
		void update();

	private:
		void init();
	};
}