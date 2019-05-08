#pragma once
#include "AsSerial.h"
#include "Controller.h"


namespace Asemco
{
	constexpr UINT8 NBLEDS = 28;
	#define ERR_OUTOFRANGE 0x20;

	class SerialController: public Controller
	{
	#ifdef _ALLPUBLIC
	public:
	#else
	protected:
	#endif
		byte* y_buffer;

		#ifdef _SINGLESERIAL
		SingletonSerial* serial;
		#else
		Serial serial;
		#endif

		UINT bufferSize;

		UINT8 headerSize;

	public:
		SerialController(LPCSTR port, UINT8 headerSize);
		SerialController(LPCSTR port, UINT8 nbLeds, UINT8 headerSize);
		~SerialController();

		VOID setColorA(UINT idx, const PUINT8 uint8_array);
		VOID getColorA(UINT idx, PUINT8 uint8_array);
		VOID setColorC(UINT idx, const Color& color);
		VOID getColorC(UINT idx, Color& color);

		VOID moderate(FLOAT, FLOAT, FLOAT);
		VOID clear();

		INT send();
	};
}