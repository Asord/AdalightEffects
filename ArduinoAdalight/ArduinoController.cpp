#include "ArduinoController.h"

namespace Asemco
{
	ArduinoController::ArduinoController(char* port)
		: serial(port)
	{
		this->clear();
		this->setHeader();
	}

	ArduinoController::~ArduinoController()
	{
		this->clear();
		this->send();
	}

	void ArduinoController::setColor(size_t pos, byte* data)
	{
		memcpy(&this->y_buffer[6 + pos * 3], data, 3);
	}

	void ArduinoController::getColor(size_t pos, byte* data)
	{
		data[0] = this->y_buffer[6 + 3 * pos];
		data[1] = this->y_buffer[6 + 3 * pos + 2];
		data[2] = this->y_buffer[6 + 3 * pos + 1];
	}

	bool ArduinoController::isBlackAt(size_t pos)
	{
		byte b = 0;
		b |= this->y_buffer[6 + 3 * pos];
		b |= this->y_buffer[6 + 3 * pos + 2];
		b |= this->y_buffer[6 + 3 * pos + 1];
		return (bool)b;
	}


	void ArduinoController::setHeader()
	{
		this->y_buffer[3] = (NBLEDS - 1) >> 8;
		this->y_buffer[4] = (NBLEDS - 1) & 0xff;
		this->y_buffer[5] = this->y_buffer[3] ^ this->y_buffer[4] ^ 0x55;
	}

	void ArduinoController::moderate(float cr, float cg, float cb)
	{
		for (int i = 6; i < 6 + BUFFERSIZE; i += 3)
		{
			// TODO: vérifier si ca fonctionne avec byte
			byte r = (byte)y_buffer[i];
			byte b = (byte)y_buffer[i + 1];
			byte g = (byte)y_buffer[i + 2];

			y_buffer[i] = (char)(r*cr);
			y_buffer[i + 1] = (char)(b*cb);
			y_buffer[i + 2] = (char)(g*cg);
		}
	}

	int ArduinoController::send()
	{
		int result = serial.writeSerialPort(y_buffer, 6 + BUFFERSIZE);
		return result;
	}

	void ArduinoController::clear()
	{
		memset(this->y_buffer + 6, 0, BUFFERSIZE);
	}
	int ArduinoController::getNbLeds()
	{
		return this->nbLeds;
	}
}