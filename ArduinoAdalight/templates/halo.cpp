#include "halo.h"

namespace Asemco
{

	Halo::Halo(ArduinoController * controller, const Color & color, size_t startPos)
	{
		this->effectPos = startPos < saturationSize ? startPos : 0;
		this->controller = controller;
		this->effectColor = color;
	}

	void Halo::update()
	{
		this->controller->clear();

		if (this->effectPos == saturationSize)
			this->effectPos = 0;

		for (int i = 0; i < NBLEDS; ++i)
		{
			int currentPos = (this->effectPos + i) % saturationSize;
			float scale = Scale(effectRange, saturationData[currentPos]);
			Color col = this->effectColor * scale;

			CBytes bytes = col.toBytes();
			controller->setColor(i, bytes.color);
		}

		this->effectPos++;

		controller->send();
	}
}
