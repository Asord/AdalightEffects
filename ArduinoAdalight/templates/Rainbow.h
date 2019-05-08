#pragma once
#include <VirtualTemplate.h>

namespace Asemco
{
	/* TODO: test this template */
	class Rainbow :public VirtualTemplate
	{
	private:
		FLOAT f_step;
		INT n_dir;

		UINT8 nbLeds;

		FLOAT* hueBuffer;

	public:
		Rainbow(Controller*, FLOAT, INT);
		VOID Update();
	};
}