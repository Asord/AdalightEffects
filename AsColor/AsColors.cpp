#include "AsColors.h"

namespace Asemco
{
	const Color Color::Red(255, 0, 0);
	const Color Color::Green(0, 255, 0);
	const Color Color::Blue(0, 0, 255);
	const Color Color::Yellow(255, 255, 0);
	const Color Color::Cyan(0, 255, 255);
	const Color Color::Magenta(255, 0, 255);
	const Color Color::White(255, 255, 255);
	const Color Color::Black(0, 0, 0);

		Color::Color()
		{
			this->_red = 255;
			this->_green = 255;
			this->_blue = 255;

			this->_alpha = 255;
		}

		Color::Color(UINT8 red, UINT8 green, UINT8 blue)
		{
			this->_red = red;
			this->_green = green;
			this->_blue = blue;

			this->_alpha = 255;
		}

		Color::Color(PUINT8 uint8_array)
		{
			UINT* local = (UINT*)uint8_array;
			this->_color = *local;
		}

		Color::Color(UINT color)
		{
			this->_color = color;
		}

		VOID Color::get(PUINT8 uint8_array) const
		{
			UINT* local = (UINT*)uint8_array;
			*local = this->_color;
		}

		VOID Color::set(CPUINT8 uint8_array)
		{
			UINT* local = (UINT*)uint8_array;
			this->_color = *local;
		}

		Color& Color::fromInt(CUINT color)
		{
			this->_color = color;
			return *this;
		}

		UINT Color::toInt() const
		{	
			return this->_color;
		}

		Color & Color::fromHue(FLOAT hue)
		{
			FLOAT h60 = hue / 60.0f;
			UINT8 h60f = (UINT8)h60;

			FLOAT f = h60 - h60f;

			switch (h60f)
			{
			case 0:
				this->_color = 0xff0000ff | (UINT)(f * 255) << 8;
				break;
			case 1:
				this->_color = 0xff00ff00 | (255 - (UINT)(f * 255));
				break;
			case 2:
				this->_color = 0xff00ff00 | (UINT)(f * 255) << 16;
				break;
			case 3:
				this->_color = 0xffff0000 | (255 - (UINT)(f * 255)) << 8;
				break;
			case 4:
				this->_color = 0xffff0000 | (UINT)(f * 255);
				break;
			case 5:
				this->_color = 0xff0000ff | (255 - (UINT)(f * 255)) << 16;
				break;
			default:
				break;
			}

			return *this;
		}
		
		Color & Color::fromHSV(FLOAT h, FLOAT s, FLOAT v)
		{
			FLOAT h60 = h / 60.0f;
			UINT h60f = (UINT)h60;

			FLOAT f = h60 - h60f;

			FLOAT p = v * (1.0f - s);
			FLOAT q = v * (1.0f - f * s);
			FLOAT t = v * (1.0f - (1.0f - f) * s);

			switch (h60f)
			{
			case 0: 
				this->_color = 0xff000000 
					| (UINT8)(v * 255)
					| (UINT8)(t * 255) << 8 
					| (UINT8)(p * 255) << 16;
				break;
			case 1:
				this->_color = 0xff000000 
					| (UINT8)(q * 255)
					| (UINT8)(v * 255) << 8 
					| (UINT8)(p * 255) << 16;
				break;
			case 2:
				this->_color = 0xff000000
					| (UINT8)(p * 255)
					| (UINT8)(v * 255) << 8
					| (UINT8)(t * 255) << 16;
				break;
			case 3:
				this->_color = 0xff000000
					| (UINT8)(p * 255) 
					| (UINT8)(q * 255) << 8 
					| (UINT8)(v * 255) << 16;
				break;
			case 4:
				this->_color = 0xff000000
					| (UINT8)(t * 255)
					| (UINT8)(p * 255) << 8 
					| (UINT8)(v * 255) << 16;
				break;
			case 5:
				this->_color = 0xff000000
					| (UINT8)(v * 255)
					| (UINT8)(p * 255) << 8 
					| (UINT8)(q * 255) << 16;
				break;
			default: break;
			}

			return *this;
		}

		VOID Color::toHSV(PFLOAT hsv)
		{
			FLOATR h = hsv[0];
			FLOATR s = hsv[1];
			FLOATR v = hsv[2];

			FLOAT r = (FLOAT)this->_red / 255.0f;
			FLOAT g = (FLOAT)this->_green / 255.0f;
			FLOAT b = (FLOAT)this->_blue / 255.0f;

			FLOAT mx = f3max(r, g, b);
			FLOAT mn = f3min(r, g, b);

			FLOAT df = mx - mn;

			FLOAT _t;

			if (mx == mn) h = 0;

			else if (mx == r)
			{
				_t = 60.0f * ((g - b) / df) + 360.0f;
				h = (FLOAT)ufmodf(_t, 360.0f);
			}
			else if (mx == g)
			{
				_t = 60.0f * ((b - r) / df) + 120.0f;
				h = (FLOAT)ufmodf(_t, 360.0f);
			}
			else if (mx == b)
			{
				_t = 60.0f * ((r - g) / df) + 240.0f;
				h = (FLOAT)ufmodf(_t, 360.0f);
			}

			if ((UINT)mx == 0) s = 0.0f;
			else s = df / mx;

			v = mx;
		}

		Color & Color::random()
		{
			this->_color = rand();
			return *this;
		}

		Color & Color::ramdomColor(FLOAT min, FLOAT max)
		{
			UINT n_min = 0;
			UINT n_max = 36000;

			if (min > 0.0f && min < 360.0f) n_min = (UINT)(min * 100.0f);
			if (max > 0.0f && max < 360.0f) n_max = (UINT)(max * 100.0f);

			UINT r = randRange(n_min, n_max);
			FLOAT h = (FLOAT)r / 100.0f;

			this->fromHue(h);
			return *this;
		}

		Color & Color::black()
		{
			this->_color = 0xff000000;
			return *this;
		}

		Color & Color::white()
		{
			this->_color = 0xffffffff;
			return *this;
		}

		Color & Color::gray(UINT8 factor)
		{
			this->_red = factor;
			this->_green = factor;
			this->_blue = factor;
			return *this;
		}

		Color & Color::coef(FLOAT coefr, FLOAT coefg, FLOAT coefb)
		{
			if (_color == 0xffffff00 || _color == 0xff00ffff || _color == 0xffff00ff)
				return *this;

			this->_red   = (UINT8)(this->_red   * coefr);
			this->_green = (UINT8)(this->_green * coefg);
			this->_blue  = (UINT8)(this->_blue  * coefb);

			return *this;
		}

		
		Color Color::operator+(const Color & other) const
		{
			UINT red = (this->_red + other._red);
			UINT green = (this->_green + other._green);
			UINT blue = (this->_blue + other._blue);

			if (red > 255) red = 255;
			if (green > 255) green = 255;
			if (blue > 255) blue = 255;

			return Color((UINT8)red, (UINT8)green, (UINT8)blue);
		}

		Color & Color::operator+=(const Color & other)
		{
			*this = *this + other;
			return *this;
		}

		Color Color::operator-(const Color & other) const
		{
			short red = (this->_red - other._red);
			short green = (this->_green - other._green);
			short blue = (this->_blue - other._blue);

			if (red < 0) red = 0;
			if (green < 0) green = 0;
			if (blue < 0) blue = 0;

			return Color((UINT8)red, (UINT8)green, (UINT8)blue);
		}

		Color & Color::operator-=(const Color & other)
		{
			*this = *this - other;
			return *this;
		}

		Color Color::operator*(const FLOAT & other) const
		{
			if (other > 0)
			{
				UINT red = (UINT)(this->_red * other);
				UINT green = (UINT)(this->_green * other);
				UINT blue = (UINT)(this->_blue * other);

				if (red > 255) red = 255;
				if (green > 255) green = 255;
				if (blue > 255) blue = 255;

				return Color((UINT8)red, (UINT8)green, (UINT8)blue);
			}
			return Color::Black;
		}

		Color & Color::operator*=(const FLOAT & other)
		{
			*this = *this * other;
			return *this;
		}

		Color Color::operator/(const FLOAT & other) const
		{
			if (other > 0)
			{
				UINT red = (UINT)(this->_red / other);
				UINT green = (UINT)(this->_green / other);
				UINT blue = (UINT)(this->_blue / other);

				if (red > 255) red = 255;
				if (green > 255) green = 255;
				if (blue > 255) blue = 255;

				return Color((UINT8)red, (UINT8)green, (UINT8)blue);
			}
			return Color::Black;
		}

		Color Color::operator/=(const FLOAT & other)
		{
			*this = *this / other;
			return *this;
		}

		BOOL Color::operator==(const Color & other) const
		{
			return (
				this->_red == other._red && 
				this->_green == other._green && 
				this->_blue == other._blue
			);
		}

		BOOL Color::operator!=(const Color & other) const
		{
			return (
				this->_red != other._red ||
				this->_green != other._green ||
				this->_blue != other._blue
				);
		}

		Color & Color::operator++()
		{
			if (this->_red < 255)
				this->_red++;
			if(this->_green < 255)
				this->_green++;
			if(this->_blue < 255)
				this->_blue++;

			return *this;
		}

		Color & Color::operator--()
		{
			if (this->_red > 0)
				this->_red--;
			if (this->_green > 0)
				this->_green--;
			if (this->_blue > 0)
				this->_blue--;

			return *this;
		}

}