#include "maths.h"

namespace Asemco
{
	CBytes HSVtoRGB(float h, float s, float v)
	{
		float h60 = h / 60.0f;
		float h60f = (float)floor(h60);

		int hi = (int)h60f % 6;

		float f = h60 - h60f;

		float p = v * (1.0f - s);
		float q = v * (1.0f - f * s);
		float t = v * (1.0f - (1.0f - f) * s);

		float r = 0.0f, g = 0.0f, b = 0.0f;

		switch (hi)
		{
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		case 5:
			r = v;
			g = p;
			b = q;
			break;
		}

		CBytes rgb;
		rgb.color[0] = (char)(r * 255);
		rgb.color[1] = (char)(g * 255);
		rgb.color[2] = (char)(b * 255);

		return rgb;
	}

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