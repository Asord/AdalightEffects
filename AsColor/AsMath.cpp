#include "AsMath.h"

namespace Asemco
{

	VOID normalize(FLOATR num1, FLOATR num2)
	{
		if (num1 > num2)
		{
			num2 = (1.0f / num1)*num2;
			num1 = 1.0f;
		}
		else
		{
			num1 = (1.0f / num2)*num1;
			num2 = 1.0f;
		}
	}

	FLOAT f3min(FLOAT f1, FLOAT f2, FLOAT f3)
	{
		FLOAT tmp = (FLOAT)fmin(f1, f2);
		return (FLOAT)fmin(tmp, f3);
	}

	FLOAT f3max(FLOAT f1, FLOAT f2, FLOAT f3)
	{
		FLOAT tmp = (FLOAT)fmax(f1, f2);
		return (FLOAT)fmax(tmp, f3);
	}

	FLOAT ufmodf(FLOAT fnum, FLOAT fmod)
	{
		FLOAT r = fmodf(fnum, fmod);
		return r = (r < 0) ? (fmod - r * -1.0f) : r;
	}

}