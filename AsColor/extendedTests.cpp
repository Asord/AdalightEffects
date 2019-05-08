#include "extendedTests.h"
#ifdef _DEVELOPPEMENT

namespace Asemco
{
	bool testRGB_arr(PUINT8 arr, UINT8 red, UINT8 gre, UINT8 blu)
	{
		return arr[0] == red && arr[1] == gre && arr[2] == blu;
	}

	bool testRGB(Color color, UINT8 red, UINT8 gre, UINT8 blu)
	{
		return color._red == red && color._green == gre && color._blue == blu;
	}

	bool testCol(Color color, UINT val)
	{
		return color._color == val;
	}

	bool isInDom(Color col)
	{
		bool r = col._red >= 0 && col._red <= 255;
		bool g = col._green >= 0 && col._green <= 255;
		bool b = col._blue >= 0 && col._blue <= 255;
		return r && g && b;
	}

	bool isInDomDeg(Color col, FLOAT min, FLOAT max)
	{
		FLOAT HSV[3];
		col.toHSV(HSV);
		return HSV[0] > min && HSV[0] < max;
	}

	char userInput()
	{
		char BUFFER[250];
		do { cin >> BUFFER; } while (BUFFER[0] != 'y' && BUFFER[0] != 'n');
		return BUFFER[0];
	}

	testTemplate::testTemplate(Controller * controller, FLOAT hueCoef)
		: VirtualTemplate(0x01, controller)
	{
		UINT8 nbLeds = this->controller->nbLeds;
		FLOAT coef = 360.0f / (FLOAT)nbLeds;

		this->hueArray = new FLOAT[nbLeds];
		for (UINT i = 0; i < nbLeds; ++i)
			this->hueArray[i] = coef * i;

		this->hueCoef = hueCoef;
	}

	testTemplate::~testTemplate()
	{
		delete[this->controller->nbLeds] this->hueArray;
	}

	VOID testTemplate::Update()
	{
		this->controller->clear();

		FLOAT newHue;
		Color hueColor;
		for (UINT i = 0; i < this->controller->nbLeds; ++i)
		{
			newHue = this->hueArray[i] + this->hueCoef;
			if (newHue > 360.0f) newHue -= 360.0f;

			hueColor.fromHue(newHue);
			this->controller->setColorC(i, hueColor);
			this->hueArray[i] = newHue;
		}

		this->controller->moderate(1.0f, 0.43f, 0.3f);
		this->controller->send();


	}
}
#endif