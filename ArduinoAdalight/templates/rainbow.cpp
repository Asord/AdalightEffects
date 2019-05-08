
#include "Rainbow.h"
namespace Asemco
{
	Rainbow::Rainbow(Controller* controller, FLOAT step, INT dir)
		: VirtualTemplate(0x05, controller)
	{
		this->nbLeds = this->controller->getNbLeds();

		this->f_step = step;

		this->n_dir = dir;

		this->hueBuffer = new FLOAT[this->nbLeds];

		float coef = 360.0f / (float)this->nbLeds;
		for (UINT i = 0; i < this->nbLeds; ++i)
			hueBuffer[i] = i* coef;
	}

	void Rainbow::Update()
	{
		this->controller->clear();

		Color col;
		FLOAT hue;

		for (int i = 0; i < this->nbLeds; ++i)
		{
			hue = this->hueBuffer[i] + this->f_step*this->n_dir;

			if (hue > 359.99f) hue -= 360.0f;
			else if (hue < 0.00f) hue += 360.0f;

			this->hueBuffer[i] = hue;

			col.fromHue(hue);
			this->controller->setColorC(i, col);
		}

		this->controller->moderate(1.0f, 0.42f, 0.3f);
		this->controller->send();
	}
}