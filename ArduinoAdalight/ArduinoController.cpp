#include <algorithm>
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

	void ArduinoController::setColorB(size_t idx, const PUINT8 uint8_array)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;
		memcpy(&this->y_buffer[6 + idx * 3], uint8_array, 3);

	}

	void ArduinoController::getColorB(size_t idx, PUINT8 uint8_array)
	{

		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;
		memcpy(uint8_array, &this->y_buffer[6 + idx * 3], 3);
	}


	void ArduinoController::setColor(size_t idx, const Color& color)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;

		UINT8 buff[4];
		color.get(buff);
		memcpy(&this->y_buffer[6 + idx * 3], buff, 3);

	}

	void ArduinoController::getColor(size_t idx, Color& color)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;

		UINT8 buff[4];
		memcpy(buff, &this->y_buffer[6 + idx * 3], 3);
		color.set(buff);
	}


	void ArduinoController::setHeader()
	{
		memcpy(this->y_buffer, "Ada", 3);
		this->y_buffer[3] = (this->nbLeds - 1) >> 8;
		this->y_buffer[4] = (this->nbLeds - 1) & 0xff;
		this->y_buffer[5] = this->y_buffer[3] ^ this->y_buffer[4] ^ 0x55;
	}

	void ArduinoController::moderate(float cR, float cG, float cB)
	{
		for (size_t i = 6; i < this->bufferSize; i += 3)
		{
			this->y_buffer[i + 0] = (UINT8)(this->y_buffer[i + 0] * cR);
			this->y_buffer[i + 1] = (UINT8)(this->y_buffer[i + 1] * cG);
			this->y_buffer[i + 2] = (UINT8)(this->y_buffer[i + 2] * cB);
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
	unsigned short ArduinoController::getNbLeds() const
	{
		return this->nbLeds;
	}
}