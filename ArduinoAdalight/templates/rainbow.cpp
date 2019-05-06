
#include "Rainbow.h"
namespace Asemco
{
	Rainbow::Rainbow(ArduinoController* controller, float step, int dir)
	{
		this->init(controller);

		this->f_step = step;

		this->f_hue = 0.0f;
		this->n_dir = dir;

		this->hueBuffer = new float[this->nbLeds];
		float diff = 360.0f / (float)this->nbLeds;
		float hue = diff;
		for (int i = 0; i < this->nbLeds; ++i)
		{
			hueBuffer[i] = hue;
			hue += diff;
		}



	}

	void Rainbow::update()
	{
		this->p_controller->clear();

		Color col;
		float hue;

		for (int i = 0; i < this->nbLeds; ++i)
		{
			hue = this->hueBuffer[i] + this->f_step*this->n_dir;

			if (hue > 359.99f) hue -= 360.0f;
			else if (hue < 0.00f) hue += 360.0f;

			this->hueBuffer[i] = hue;

			col.fromHue(hue);
			this->p_controller->setColor(i, col);
		}

		this->p_controller->moderate(1.0f, 0.42f, 0.3f);
		this->p_controller->send();
	}
}