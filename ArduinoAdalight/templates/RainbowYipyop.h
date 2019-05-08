#pragma once
#include <VirtualTemplate.h>

namespace Asemco
{
	/* TODO: test this template */
	class RainbowYipyop :public VirtualTemplate
	{
	private:
		FLOAT f_currentHue;
		FLOAT f_step;
		SHORT n_positionHue;
		SHORT n_directionHue;

		Color color;

	public:
		RainbowYipyop(Controller*);
		VOID Update();

	private:
		VOID initEffect();
	};
}