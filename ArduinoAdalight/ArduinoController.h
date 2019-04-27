#pragma once
#include "Serial.h"

typedef unsigned char usize;

constexpr usize NBLEDS = 28;
#define ERR_OUTOFRANGE 0x20;

namespace Asemco
{
	class ArduinoController
	{
	private:
		byte* y_buffer;
		Serial serial;

		usize nbLeds;
		size_t bufferSize;

	public:
		ArduinoController(char*);
		ArduinoController(char*, usize);
		~ArduinoController();

		void setColor(size_t, byte*);
		void getColor(size_t, byte*);

		size_t getNbLeds() const;

		void moderate(float, float, float);
		void clear();
		int send();

	private:
		void setHeader();
	};
}