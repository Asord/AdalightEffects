#pragma once
#include <cmath>
#include <random>

typedef unsigned char UINT8;
typedef unsigned char* PUINT8;
typedef const unsigned char* CPUINT8;
typedef unsigned int UINT;
typedef const unsigned int CUINT;
typedef unsigned int& UINTR;
typedef const unsigned int& CUINTR;
typedef float FLOAT;
typedef float& FLOATR;
typedef float* PFLOAT;
typedef bool BOOL;
typedef void VOID;

namespace Asemco
{
	#define randRange(n_min, n_max) rand() % (n_max - n_min + 1) + n_min

	VOID normalize(FLOATR num1, FLOATR num2);

	FLOAT f3min(FLOAT f1, FLOAT f2, FLOAT f3);

	FLOAT f3max(FLOAT f1, FLOAT f2, FLOAT f3);

	FLOAT ufmodf(FLOAT fnum, FLOAT fmod);
}