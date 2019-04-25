#pragma once
#include "abstractTemplate.h"

namespace Asemco
{
	class Rainbow :public AbstractTemplate
	{
	private:
		float f_step;
		float f_hue;
		int n_dir;

	public:
		Rainbow(ArduinoController*, float, int);
		void update();
	};
}