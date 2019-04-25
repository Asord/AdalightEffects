#include "RainbowYipyop.h"

namespace Asemco
{
	RainbowYipyop::RainbowYipyop(ArduinoController* controller)
	{
		this->p_controller = controller;

		this->f_currentHue = 0.0f;
		this->f_step = 0.0f;
		this->n_positionHue = 0;
		this->n_directionHue = 1;

		this->init();
		this->p_controller->clear();
	}


	void RainbowYipyop::init()
	{
		float nbLeds = (float)NBLEDS;

		float hue = this->f_currentHue;
		float stop;

		do {
			stop = (rand() % 36000) / 100.0f;
		} while (stop == hue);

		if (hue < stop)
			if (stop - hue > 60)
				this->f_step = (stop - hue) / nbLeds;
			else
				this->f_step = (360.0f + (stop - hue)) / nbLeds;
		else
			if (hue - stop > 60)
				this->f_step = (hue - stop) / nbLeds;
			else
				this->f_step = (360.0f + (hue - stop)) / nbLeds;
	}


	void RainbowYipyop::update()
	{
		if (this->n_positionHue == NBLEDS || this->n_positionHue == -1)
		{
			this->init();
			this->n_directionHue *= -1;
		}
		else
		{
			this->f_currentHue = ufmodf(this->f_currentHue + this->f_step, 360.0f);
			Color col(this->f_currentHue, 1.0, 1.0);
			col.coef(1.0f, 0.42f, 0.3f);
			CBytes bytes = col.toBytes();
			this->p_controller->setColor(this->n_positionHue, bytes.color);
		}
		this->n_positionHue += this->n_directionHue;

		this->p_controller->send();
	}
}