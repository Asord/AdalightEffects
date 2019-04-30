#include "halo.h"


namespace Asemco
{
	float Scale(float oMin, float oMax, float nMin, float nMax, float value)
	{
		return ((value - oMin) / (oMax - oMin)) * (nMax - nMin) + nMin;
	}


	Halo::Halo(ArduinoController * controller, const Color & color, size_t startPos)
	{
		this->init(controller);

		this->effectPos = startPos < saturationSize ? startPos : 0;
		this->effectColor = color;
	}

	void Halo::update()
	{
		this->p_controller->clear();

		if (this->effectPos == saturationSize)
			this->effectPos = 0;

		for (int i = 0; i < this->nbLeds; ++i)
		{
			int currentPos = (this->effectPos + i) % saturationSize;
			float scale = Scale(effectRange, saturationData[currentPos]);
			Color col = this->effectColor * scale;
			p_controller->setColor(i, col);
		}

		this->effectPos++;

		p_controller->send();
	}
}
