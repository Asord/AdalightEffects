#pragma once
#include "abstractTemplate.h"
#include "../tools/maths.h"
#include "../Resources/haloEffect.h"

#define effectRange 0.0f, 255.0f, 0.2f, 1.0f

namespace Asemco
{
	class Halo : public AbstractTemplate
	{
	private:
		ArduinoController* controller;
		Color effectColor;
		size_t effectPos;

	public:
		Halo(ArduinoController* controller, const Color& color, size_t startPos);
		void update();
	};
}