#include "ArduinoController.h"

namespace Asemco
{
	ArduinoController::ArduinoController(char* port)
		: serial(port)
	{
		this->nbLeds = NBLEDS;
		this->bufferSize = 6 + 3 * NBLEDS;
		this->y_buffer = new byte[this->bufferSize];

		this->clear();
		this->setHeader();
	}

	ArduinoController::ArduinoController(char* port, usize nbLeds)
		: serial(port)
	{
		this->nbLeds = nbLeds;
		this->bufferSize = 6 + 3 * nbLeds;
		this->y_buffer = new byte[this->bufferSize];

		this->clear();
		this->setHeader();
	}

	ArduinoController::~ArduinoController()
	{
		this->clear();
		this->send();
		delete[this->bufferSize] this->y_buffer;
	}

	void ArduinoController::setColor(size_t pos, byte* data)
	{
		if (pos > this->nbLeds) throw ERR_OUTOFRANGE;
		memcpy(&this->y_buffer[6 + pos * 3], data, 3);
	}

	void ArduinoController::getColor(size_t pos, byte* data)
	{
		if (pos > this->nbLeds) throw ERR_OUTOFRANGE;
		memcpy(data, &this->y_buffer[6 + pos * 3], 3);
	}

	void ArduinoController::setHeader()
	{
		memcpy(this->y_buffer, "Ada", 3);
		this->y_buffer[3] = (this->nbLeds - 1) >> 8;
		this->y_buffer[4] = (this->nbLeds - 1) & 0xff;
		this->y_buffer[5] = this->y_buffer[3] ^ this->y_buffer[4] ^ 0x55;
	}

	void ArduinoController::moderate(float cr, float cg, float cb)
	{
		for (size_t i = 6; i < this->bufferSize; i += 3)
		{
			byte r = y_buffer[i];
			byte b = y_buffer[i + 1];
			byte g = y_buffer[i + 2];

			y_buffer[i] = (byte)(r*cr);
			y_buffer[i + 1] = (byte)(b*cb);
			y_buffer[i + 2] = (byte)(g*cg);
		}
	}

	int ArduinoController::send()
	{
		int result = serial.writeSerialPort(y_buffer, this->bufferSize);
		return result;
	}

	void ArduinoController::clear()
	{
		memset(this->y_buffer + 6, 0, this->bufferSize);
	}
	size_t ArduinoController::getNbLeds() const
	{
		return this->nbLeds;
	}
}