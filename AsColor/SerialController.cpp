#include "SerialController.h"

namespace Asemco
{

	SerialController::SerialController(LPCSTR port, UINT8 headerSize)
	#ifdef _SINGLESERIAL
	{
		this->serial = SingletonSerial::getInstance(port);
	#else
		: serial(port)
	{
	#endif

		this->headerSize = headerSize;
		this->nbLeds = NBLEDS;
		this->bufferSize = headerSize + 3 * NBLEDS;
		this->y_buffer = new byte[this->bufferSize];

		this->clear();
	}

	SerialController::SerialController(LPCSTR port, UINT8 nbLeds, UINT8 headerSize)	
	#ifdef _SINGLESERIAL
	{
		this->serial = SingletonSerial::getInstance(port);
	#else
		: serial(port)
	{
	#endif
		this->headerSize = headerSize;
		this->nbLeds = nbLeds;
		this->bufferSize = headerSize + 3 * nbLeds;
		this->y_buffer = new byte[this->bufferSize];

		this->clear();
	}

	SerialController::~SerialController()
	{
		this->clear();
		this->send();
		delete[this->bufferSize] this->y_buffer;
		#ifdef _SINGLESERIAL
		SingletonSerial::delInstance();
		#endif
	}

	VOID SerialController::setColorA(UINT idx, const PUINT8 uint8_array)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;
		memcpy(&this->y_buffer[this->headerSize + idx * 3], uint8_array, 3);
	}

	VOID SerialController::getColorA(UINT idx, PUINT8 uint8_array)
	{

		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;
		memcpy(uint8_array, &this->y_buffer[this->headerSize + idx * 3], 3);
	}


	VOID SerialController::setColorC(UINT idx, const Color& color)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;

		UINT buff = color.toInt();
		memcpy(&this->y_buffer[this->headerSize + idx * 3], (void*)&buff, 3);
	}

	VOID SerialController::getColorC(UINT idx, Color& color)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;

		UINT buff;
		memcpy((void*)&buff, &this->y_buffer[this->headerSize + idx * 3], 3);
		color.fromInt(buff);
	}

	VOID SerialController::moderate(FLOAT cR, FLOAT cG, FLOAT cB)
	{
		for (UINT8 i = this->headerSize; i < this->bufferSize; i += 3)
		{
			this->y_buffer[i + 0] = (UINT8)(this->y_buffer[i + 0] * cR);
			this->y_buffer[i + 1] = (UINT8)(this->y_buffer[i + 1] * cG);
			this->y_buffer[i + 2] = (UINT8)(this->y_buffer[i + 2] * cB);
		}
	}

	INT SerialController::send()
	{

		#ifdef _SINGLESERIAL
		INT result = serial->writeSerialPort(y_buffer, this->bufferSize);
		#else
		INT result = serial.writeSerialPort(y_buffer, this->bufferSize);
		#endif
		return result;
	}

	VOID SerialController::clear()
	{
		memset(this->y_buffer + this->headerSize, 0, this->bufferSize - this->headerSize);
	}
}