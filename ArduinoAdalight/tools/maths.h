#pragma once
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../defines.h"


namespace Asemco
{

	#define chance(x) rand() % 100 < x

	struct CBytes
	{
		byte color[3];
	};

	CBytes HSVtoRGB(float, float, float);
	float f3min(float, float, float);
	float f3max(float, float, float);

	float ufmodf(float, float);

	float Scale(float oMin, float oMax, float nMin, float nMax, float value);
}