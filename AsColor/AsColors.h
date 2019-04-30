#pragma once
#include "AsMath.h"

namespace Asemco
{

	class Color
	{
	public:
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Magenta;
		static const Color White;
		static const Color Black;

	private:
		UINT8 _red;
		UINT8 _green;
		UINT8 _blue;

	public:
		Color();
		Color(UINT8 red, UINT8 green, UINT8 blue);
		Color(PUINT8 uint8_array);
		Color(UINT color, BOOL big_endian=true);

		VOID get(PUINT8 uint8_array) const;
		VOID set(CPUINT8 uint8_array);

		VOID fromInt(CUINTR color, BOOL big_endian=true);
		VOID toIntRef(UINTR color, BOOL big_endian=true);
		UINT toInt(BOOL big_endian = true);

		Color& fromHSV(FLOAT hue, FLOAT saturation, FLOAT value);
		VOID toHSV(PFLOAT hsv);

		Color& random();
		Color& ramdomColor(FLOAT min = 0.0f, FLOAT max = 360.0f);
		Color& black();
		Color& white();
		Color& gray(UINT8 factor);

		Color& coef(FLOAT coefr, FLOAT coefg, FLOAT coefb);

		Color operator+(const Color& other) const;
		Color& operator+=(const Color& other);
		Color operator-(const Color& other) const;
		Color& operator-=(const Color& other);
		Color operator*(const FLOAT& other) const;
		Color& operator*=(const FLOAT& other);
		Color operator/(const FLOAT& other) const;
		Color operator/=(const FLOAT& other);

		BOOL operator==(const Color& other) const;
		BOOL operator!=(const Color& other) const;

		Color& operator++();
		Color& operator--();
	};

}