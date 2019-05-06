#pragma once
#include "AsSerial.h"
#include "AsColors.h"

constexpr UINT8 NBLEDS = 28;
#define ERR_OUTOFRANGE 0x20;

namespace Asemco
{
	class AdalightBase
	{
	#ifdef _ALLPUBLIC
	public:
	#else
	private:
	#endif
		byte* y_buffer;
		BaseSerial serial;

		UINT8 nbLeds;
		UINT bufferSize;

	public:
		AdalightBase(LPCSTR port);
		AdalightBase(LPCSTR port, UINT8 nbLeds);
		~AdalightBase();

		VOID setColorA(UINT idx, const PUINT8 uint8_array);
		VOID getColorA(UINT idx, PUINT8 uint8_array);
		VOID setColorC(UINT idx, const Color& color);
		VOID getColorC(UINT idx, Color& color);

		USHORT getNbLeds() const;

		VOID moderate(FLOAT, FLOAT, FLOAT);
		VOID clear();
		INT send();

	#ifdef _ALLPUBLIC
	public:
	#else
	private:
	#endif
		void setHeader();
	};
}