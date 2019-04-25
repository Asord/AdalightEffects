#include "Color.h"

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
		case 0: r = v; g = t; b = p; break;
		case 1: r = q; g = v; b = p; break;
		case 2: r = p; g = v; b = t; break;
		case 3: r = p; g = q; b = v; break;
		case 4: r = t; g = p; b = v; break;
		case 5: r = v; g = p; b = q; break;
		}

		CBytes rgb;
		rgb.color[0] = (byte)(r * 255);
		rgb.color[1] = (byte)(g * 255);
		rgb.color[2] = (byte)(b * 255);

		return rgb;
	}


	Color::Color()
	{
		this->y_red = 0;
		this->y_green = 0;
		this->y_blue = 0;
	}

	Color::Color(int r, int g, int b)
	{
		if (r >= 0 && r <= 255)
			this->y_red = r;
		else
			this->y_red = 0;

		if (g >= 0 && g <= 255)
			this->y_green = g;
		else
			this->y_green = 0;

		if (b >= 0 && b <= 255)
			this->y_blue = b;
		else
			this->y_blue = 0;

	}

	Color::Color(float h, float s, float v)
	{
		CBytes rgb = HSVtoRGB(h, s, v);

		this->y_red = rgb.color[0];
		this->y_green = rgb.color[1];
		this->y_blue = rgb.color[2];
	}

	Color::Color(CBytes& buff)
	{
		this->y_red = buff.color[0];
		this->y_green = buff.color[1];
		this->y_blue = buff.color[2];
	}

	Color::Color(int * color)
	{
		int r = color[0];
		int g = color[1];
		int b = color[2];

		if (r >= 0 && r <= 255)
			this->y_red = r;
		else
			this->y_red = 0;

		if (g >= 0 && g <= 255)
			this->y_green = g;
		else
			this->y_green = 0;

		if (b >= 0 && b <= 255)
			this->y_blue = b;
		else
			this->y_blue = 0;

	}

	void Color::fromBytes(char* bytes)
	{
		this->y_red = bytes[0];
		this->y_green = bytes[1];
		this->y_blue = bytes[2];
	}

	Color& Color::random()
	{
		this->y_red = rand() % 256;
		this->y_green = rand() % 256;
		this->y_blue = rand() % 256;

		return *this;
	}

	Color& Color::randomColor()
	{
		int r = rand() % 36000;
		float h = (float)r / 100.0f;

		CBytes rgb = HSVtoRGB(h, 1.0f, 1.0f);

		this->y_red = rgb.color[0];
		this->y_green = rgb.color[1];
		this->y_blue = rgb.color[2];

		return *this;
	}

	Color& Color::zero()
	{
		this->y_red = 0;
		this->y_green = 0;
		this->y_blue = 0;

		return *this;
	}

	void Color::coef(float cr, float cg, float cb)
	{
		byte r = (byte)this->y_red;
		byte b = (byte)this->y_green;
		byte g = (byte)this->y_blue;

		this->y_red = (byte)(r*cr);
		this->y_green = (byte)(b*cb);
		this->y_blue = (byte)(g*cg);
	}

	HSV Color::toHSV()
	{
		float r = (float)this->y_red / 255.0f;
		float g = (float)this->y_green / 255.0f;
		float b = (float)this->y_blue / 255.0f;

		float mx = f3max(r, g, b);
		float mn = f3min(r, g, b);

		float df = mx - mn;

		HSV hsv;
		float _t;

		if (mx == mn)
			hsv.H = 0;
		else if (mx == r)
		{
			_t = 60.0f * ((g - b) / df) + 360.0f;
			hsv.H = (float)ufmodf(_t, 360.0f);
		}
		else if (mx == g)
		{
			_t = 60.0f * ((b - r) / df) + 120.0f;
			hsv.H = (float)ufmodf(_t, 360.0f);
		}
		else if (mx == b)
		{
			_t = 60.0f * ((r - g) / df) + 240.0f;
			hsv.H = (float)ufmodf(_t, 360.0f);
		}


		if ((int)mx == 0)
			hsv.S = 0.0f;
		else
			hsv.S = df / mx;

		hsv.V = mx;

		return hsv;
	}

	int Color::toInt()
	{
		int rgb = this->y_red;
		rgb = (rgb << 8) + this->y_blue;
		rgb = (rgb << 8) + this->y_green;

		return rgb;
	}

	CBytes Color::toBytes()
	{
		CBytes bytes;
		bytes.color[0] = this->y_red;
		bytes.color[1] = this->y_blue;
		bytes.color[2] = this->y_green;

		return bytes;
	}

	Color & Color::operator+=(const Color & other)
	{
		byte r = (this->y_red + other.y_red) % 256;
		byte g = (this->y_green + other.y_green) % 256;
		byte b = (this->y_blue + other.y_blue) % 256;

		this->y_red = r;
		this->y_green = g;
		this->y_blue = b;

		return *this;
	}

	Color Color::operator*(float f)
	{
		if (0.0f <= f && f <= 1.0f)
		{
			float r = (float)this->y_red * f;
			float g = (float)this->y_green * f;
			float b = (float)this->y_blue * f;

			int rc = (unsigned int)r;
			int gc = (unsigned int)g;
			int bc = (unsigned int)b;
			return Color(rc, gc, bc);
		}
		return Color();
	}

}