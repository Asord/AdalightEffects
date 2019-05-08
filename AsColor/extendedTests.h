#pragma once
#define _ALLPUBLIC

#include <iostream>
#include "VirtualTemplate.h"
#include "AsColors.h"

using namespace Asemco;
using namespace std;

namespace Asemco
{
	class testTemplate : public VirtualTemplate
	{
	private:
		PFLOAT hueArray;
		FLOAT hueCoef;

	public:
		testTemplate(Controller* controller, FLOAT hueCoef);
		~testTemplate();

		VOID Update();
	};

	template<typename T>
	bool cmpArr(T* arr1, T* arr2, UINT8 size)
	{
		bool result = true;
		for (UINT8 i = 0; i < size; ++i)
			result &= (arr1[i] == arr2[i]);

		return result;
	}

	bool testRGB_arr(PUINT8 arr, UINT8 red, UINT8 gre, UINT8 blu);

	bool testRGB(Color color, UINT8 red, UINT8 gre, UINT8 blu);

	bool testCol(Color color, UINT val);

	bool isInDom(Color col);

	bool isInDomDeg(Color col, FLOAT min, FLOAT max);

	char userInput();

}