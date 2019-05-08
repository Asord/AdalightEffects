#include "halo.h"


namespace Asemco
{
	float Scale(float oMin, float oMax, float nMin, float nMax, float value)
	{
		return ((value - oMin) / (oMax - oMin)) * (nMax - nMin) + nMin;
	}

	Halo::Halo(Controller* controller, const Color & color, size_t startPos)
		: VirtualTemplate(0x04, controller)
	{

		this->effectPos = startPos < saturationSize ? startPos : 0;
		this->effectColor = color;
	}

	void Halo::Update()
	{
		this->controller->clear();

		if (this->effectPos == saturationSize)
			this->effectPos = 0;

		FLOAT scale; INT currentPos; Color col;
		for (int i = 0; i < this->controller->getNbLeds(); ++i)
		{
			currentPos = (this->effectPos + i) % saturationSize;
			scale = Scale(effectRange, saturationData[currentPos]);
			col = this->effectColor * scale;
			this->controller->setColorC(i, col);
		}

		this->effectPos++;

		this->controller->send();
	}
}
