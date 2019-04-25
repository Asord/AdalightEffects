#pragma once
#include "Serial.h"

#define NBLEDS 29
#define BUFFERSIZE 3*NBLEDS

namespace Asemco
{
	class ArduinoController
	{
	private:
		byte y_buffer[6 + BUFFERSIZE] = "Ada";
		Serial serial;
		int nbLeds = NBLEDS;

	public:
		ArduinoController(char*);
		~ArduinoController();

		void setColor(size_t, byte*);
		void getColor(size_t, byte*);

		bool isBlackAt(size_t);

		void setHeader();

		void moderate(float, float, float);
		int send();
		void clear();
		int getNbLeds();
	};
}