#pragma once
#include "VirtualTemplate.h"
#include "../Resources/haloEffect.h"

#define effectRange 0.0f, 255.0f, 0.2f, 1.0f

/* TODO: test this template */
namespace Asemco
{
	float Scale(float oMin, float oMax, float nMin, float nMax, float value);

	class Halo : public VirtualTemplate
	{
	private:
		Color effectColor;
		size_t effectPos;

	public:
		Halo(Controller* controller, const Color& color, size_t startPos);
		VOID Update();
	};
}