#pragma once
#include "Serial.h"
#include <AsColors.h>

typedef unsigned char usize;

constexpr usize NBLEDS = 28;
#define ERR_OUTOFRANGE 0x20;

namespace Asemco
{
	enum ColOrder { RGB, RBG, GRB, GBR, BRG, BGR };

	class ArduinoController
	{
	private:
		byte* y_buffer;
		Serial serial;

		usize nbLeds;
		size_t bufferSize;

		ColOrder colorOrder;

		void swampOrderI(const PUINT8 in, PUINT8 out);
		void swampOrderI(PUINT8 inout);

		void swampOrderO(const PUINT8 in, PUINT8 out);
		void swampOrderO(PUINT8 inout);

	public:
		ArduinoController(char*, ColOrder order=ColOrder::RGB);
		ArduinoController(char*, usize, ColOrder order = ColOrder::RGB);
		~ArduinoController();

		void setColorB(size_t idx, const PUINT8 uint8_array);
		void getColorB(size_t idx, PUINT8 uint8_array);
		void setColor(size_t idx, /*const*/ Color& color);
		void getColor(size_t idx, Color& color);

		unsigned short getNbLeds() const;

		void moderate(float, float, float);
		void clear();
		int send();

	private:
		void setHeader();
	};
}