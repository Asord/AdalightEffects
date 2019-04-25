#include "Rainbow.h"
namespace Asemco
{
	Rainbow::Rainbow(ArduinoController* controller, float step, int dir)
	{
		this->p_controller = controller;
		this->f_step = step;

		this->f_hue = 0.0f;
		this->n_dir = dir;
	}

	void Rainbow::update()
	{
		this->p_controller->clear();

		float hue = this->f_hue;

		for (int i = 0; i < NBLEDS; ++i)
		{
			hue = ufmodf(hue + this->f_step, 360.0f);
			Color col(hue, 1.0, 1.0);
			CBytes bytes = col.toBytes();
			this->p_controller->setColor(i, bytes.color);
		}

		this->f_hue = ufmodf(this->f_hue + this->f_step*this->n_dir, 360.0f);
		this->p_controller->moderate(1.0f, 0.42f, 0.3f);
		this->p_controller->send();
	}
}