#pragma once
#include "AsColors.h"

namespace Asemco
{
	class Controller
	{

	#ifdef _ALLPUBLIC
	public:
	#else
	protected:
	#endif

		UINT8 nbLeds;

	public:
		virtual VOID setColorA(UINT idx, const PUINT8 uint8_array) = 0;
		virtual VOID getColorA(UINT idx, PUINT8 uint8_array) = 0;
		virtual VOID setColorC(UINT idx, const Color& color) = 0;
		virtual VOID getColorC(UINT idx, Color& color) = 0;

		virtual VOID moderate(FLOAT, FLOAT, FLOAT) = 0;
		virtual VOID clear() = 0;

		virtual INT send() = 0;

		USHORT getNbLeds() const { return this->nbLeds; };
	};
}