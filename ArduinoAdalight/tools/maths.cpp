#include "maths.h"

namespace Asemco
{
	float f3min(float f1, float f2, float f3)
	{
		float tmp = (float)fmin(f1, f2);
		return (float)fmin(tmp, f3);
	}

	float f3max(float f1, float f2, float f3)
	{
		float tmp = (float)fmax(f1, f2);
		return (float)fmax(tmp, f3);
	}

	float ufmodf(float fnum, float fmod)
	{
		float r = fmodf(fnum, fmod);
		return r = (r < 0) ? (fmod - r * -1.0f) : r;
	}
	float Scale(float oMin, float oMax, float nMin, float nMax, float value)
	{
		return ((value - oMin) / (oMax - oMin)) * (nMax - nMin) + nMin;
	}
}