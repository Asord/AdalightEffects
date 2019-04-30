#pragma once
#include <AsColors.h>
#include "abstractTemplate.h"
#include "../Resources/haloEffect.h"

#define effectRange 0.0f, 255.0f, 0.2f, 1.0f

namespace Asemco
{
	float Scale(float oMin, float oMax, float nMin, float nMax, float value);

	class Halo : public AbstractTemplate
	{
	private:
		Color effectColor;
		size_t effectPos;

	public:
		Halo(ArduinoController* controller, const Color& color, size_t startPos);
		void update();
	};
}