#pragma once
#include "maths.h"

namespace Asemco
{
	struct HSV
	{
		float H;
		float S;
		float V;
	};

	class Color
	{
	private:
		byte y_red;
		byte y_green;
		byte y_blue;

	public:
		Color();
		Color(int, int, int);
		Color(float, float, float);
		Color(CBytes);
		Color(int*);

		void fromBytes(char* bytes);

		Color random();
		Color randomColor();
		Color zero();

		void coef(float, float, float);

		HSV toHSV();
		int toInt();
		CBytes toBytes();

		Color& operator+=(const Color&);
		Color operator*(float);
	};
}