#include "rainbowStatic.h"

namespace Asemco
{
	RainbowStatic::RainbowStatic(Controller* controller, FLOAT step)
		: VirtualTemplate(0x06, controller)
	{
		this->f_step = step;
		this->f_hue = 0.0f;
	}

	void RainbowStatic::Update()
	{
		this->controller->clear();
		Color col;
		for (int i = 0; i < this->controller->getNbLeds(); ++i)
		{
			col.fromHue(this->f_hue);
			this->controller->setColorC(i, col);
		}

		this->f_hue = ufmodf(this->f_hue + this->f_step, 360.0f);

		this->controller->moderate(1.0f, 0.42f, 0.3f);
		this->controller->send();
	}
}