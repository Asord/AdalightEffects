#include "RainbowYipyop.h"

namespace Asemco
{
	RainbowYipyop::RainbowYipyop(Controller* controller)
		: VirtualTemplate(0x07, controller)
	{
		this->color = Color();

		this->f_currentHue = 0.0f;
		this->f_step = 0.0f;
		this->n_positionHue = 0;
		this->n_directionHue = 1;

		this->initEffect();

		this->controller->clear();
	}


	void RainbowYipyop::initEffect()
	{
		FLOAT leds = (FLOAT)this->controller->getNbLeds();

		FLOAT hue = this->f_currentHue;
		FLOAT stop;

		do {
			stop = (rand() % 36000) / 100.0f;
		} while (stop == hue);

		if (hue < stop)
			if (stop - hue > 60)
				this->f_step = (stop - hue) / leds;
			else
				this->f_step = (360.0f + (stop - hue)) / leds;
		else
			if (hue - stop > 60)
				this->f_step = (hue - stop) / leds;
			else
				this->f_step = (360.0f + (hue - stop)) / leds;
	}


	void RainbowYipyop::Update()
	{
		if (this->n_positionHue == this->controller->getNbLeds() || this->n_positionHue == -1)
		{
			this->initEffect();
			this->n_directionHue *= -1;
		}
		else
		{
			this->f_currentHue = ufmodf(this->f_currentHue + this->f_step, 360.0f);

			color.fromHue(this->f_currentHue).coef(1.0f, 0.42f, 0.3f);
			this->controller->setColorC(this->n_positionHue, color);
		}
		this->n_positionHue += this->n_directionHue;

		this->controller->send();
	}
}