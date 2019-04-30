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
		}

		Color::Color(UINT8 red, UINT8 green, UINT8 blue)
		{
			this->_red = red;
			this->_green = green;
			this->_blue = blue;
		}

		Color::Color(PUINT8 uint8_array)
		{
			this->_red = uint8_array[0];
			this->_green = uint8_array[1];
			this->_blue = uint8_array[2];
		}

		Color::Color(UINT color, BOOL big_endian)
		{
			if (big_endian)
			{
				this->_red =   (color & 0xff000000) >> 24;
				this->_green = (color & 0x00ff0000) >> 16;
				this->_blue =  (color & 0x0000ff00) >> 8;
			}
			else
			{
				this->_red =   (color & 0x000000ff);
				this->_green = (color & 0x0000ff00) << 8;
				this->_blue =  (color & 0x00ff0000) << 16;
			}

		}

		VOID Color::get(PUINT8 uint8_array) const
		{
			uint8_array[0] = this->_red;
			uint8_array[1] = this->_green;
			uint8_array[2] = this->_blue;
		}

		VOID Color::set(CPUINT8 uint8_array)
		{
			this->_red = uint8_array[0];
			this->_green = uint8_array[1];
			this->_blue = uint8_array[2];
		}

		VOID Color::fromInt(CUINTR color, BOOL big_endian)
		{
			if (big_endian)
			{
				this->_red = (color & 0xff000000) >> 24;
				this->_green = (color & 0x00ff0000) >> 16;
				this->_blue = (color & 0x0000ff00) >> 8;
			}
			else
			{
				this->_red = (color & 0x000000ff);
				this->_green = (color & 0x0000ff00) << 8;
				this->_blue = (color & 0x00ff0000) << 16;
			}
		}

		VOID Color::toIntRef(UINTR color, BOOL big_endian)
		{
			if (big_endian)
			{
				color = this->_red << 24 | this->_green << 16 | this->_blue << 8;
			}
			else
			{
				color = this->_red | this->_green << 8 | this->_blue  << 16;
			}
		}

		UINT Color::toInt(BOOL big_endian)
		{	
			if (big_endian)
			{
				return this->_red << 24 | this->_green << 16 | this->_blue << 8;
			}
			else
			{
				return this->_red | this->_green << 8 | this->_blue << 16;
			}
		}

		Color & Color::fromHSV(FLOAT h, FLOAT s, FLOAT v)
		{
			{
				FLOAT h60 = h / 60.0f;
				FLOAT h60f = (FLOAT)floor(h60);

				UINT hi = (UINT)h60f % 6;

				FLOAT f = h60 - h60f;

				FLOAT p = v * (1.0f - s);
				FLOAT q = v * (1.0f - f * s);
				FLOAT t = v * (1.0f - (1.0f - f) * s);

				FLOAT r = 0.0f, g = 0.0f, b = 0.0f;

				switch (hi)
				{
				case 0: r = v; g = t; b = p; break;
				case 1: r = q; g = v; b = p; break;
				case 2: r = p; g = v; b = t; break;
				case 3: r = p; g = q; b = v; break;
				case 4: r = t; g = p; b = v; break;
				case 5: r = v; g = p; b = q; break;
				}

				this->_red = (UINT8)(r * 255);
				this->_green = (UINT8)(g * 255);
				this->_blue = (UINT8)(b * 255);

				return *this;
			}
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
			this->_red = rand() % 256;
			this->_green = rand() % 256;
			this->_blue = rand() % 256;

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

			this->fromHSV(h, 1.0f, 1.0f);
			return *this;
		}

		Color & Color::black()
		{
			this->_red = 0;
			this->_green = 0;
			this->_blue = 0;
			return *this;
		}

		Color & Color::white()
		{
			this->_red = 255;
			this->_green = 255;
			this->_blue = 255;
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
			/* COLOR IS 00???? */
			if (this->_red == 0)
			{
				// COLOR IS 0000?? OR 00??00
				if (this->_green == 0 || this->_blue == 0)
					return *this;

				FLOAT cg = coefg; FLOAT cb = coefb;
				normalize(cg, cb);

				this->_green = (UINT8)((FLOAT)this->_green * cg);
				this->_blue = (UINT8)((FLOAT)this->_blue * cb);
			}
			/* COLOR IS ??00?? */
			else if (this->_green == 0)
			{
				/* COLOR IS ??0000 */
				if (this->_blue == 0)
					return *this;

				FLOAT cr = coefr; FLOAT cb = coefb;
				normalize(cr, cb);

				this->_red = (UINT8)((FLOAT)this->_red * cr);
				this->_blue = (UINT8)((FLOAT)this->_blue * cb);

			}
			/* COLOR IS ????00 */
			else if (this->_blue == 0)
			{
				FLOAT cr = coefr; FLOAT cg = coefg;
				normalize(cr, cg);

				this->_red = (UINT8)((FLOAT)this->_red * cr);
				this->_green = (UINT8)((FLOAT)this->_green * cg);
			}
			/* COLOR IS ?????? */
			else 
			{
				this->_red = (UINT8)((FLOAT)this->_red * coefr);
				this->_green = (UINT8)((FLOAT)this->_green * coefg);
				this->_blue = (UINT8)((FLOAT)this->_blue * coefb);
			}

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
			UINT red = (this->_red + other._red);
			UINT green = (this->_green + other._green);
			UINT blue = (this->_blue + other._blue);

			if (red < 255) red = 0;
			if (green < 255) green = 0;
			if (blue < 255) blue = 0;

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