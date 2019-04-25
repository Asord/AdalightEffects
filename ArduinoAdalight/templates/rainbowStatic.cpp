#include "rainbowStatic.h"

namespace Asemco
{
	RainbowStatic::RainbowStatic(ArduinoController* controller, float step)
	{
		this->p_controller = controller;
		this->f_step = step;

		this->f_hue = 0.0f;
	}

	void RainbowStatic::update()
	{
		this->p_controller->clear();

		for (int i = 0; i < NBLEDS; ++i)
		{
			Color col(this->f_hue, 1.0, 1.0);
			CBytes bytes = col.toBytes();
			this->p_controller->setColor(i, bytes.color);
		}

		this->f_hue = ufmodf(this->f_hue + this->f_step, 360.0f);
		this->p_controller->moderate(1.0f, 0.42f, 0.3f);
		this->p_controller->send();
	}
}