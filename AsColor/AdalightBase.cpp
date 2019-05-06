#include <algorithm>
#include "AdalightBase.h"

namespace Asemco
{
	AdalightBase::AdalightBase(LPCSTR port)
		: serial(port)
	{
		this->nbLeds = NBLEDS;
		this->bufferSize = 6 + 3 * NBLEDS;
		this->y_buffer = new byte[this->bufferSize];

		this->clear();
		this->setHeader();
	}

	AdalightBase::AdalightBase(LPCSTR port, UINT8 nbLeds)
		: serial(port)
	{
		this->nbLeds = nbLeds;
		this->bufferSize = 6 + 3 * nbLeds;
		this->y_buffer = new byte[this->bufferSize];

		this->clear();
		this->setHeader();
	}

	AdalightBase::~AdalightBase()
	{
		this->clear();
		this->send();
		delete[this->bufferSize] this->y_buffer;
	}

	VOID AdalightBase::setColorA(UINT idx, const PUINT8 uint8_array)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;
		memcpy(&this->y_buffer[6 + idx * 3], uint8_array, 3);
	}

	VOID AdalightBase::getColorA(UINT idx, PUINT8 uint8_array)
	{

		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;
		memcpy(uint8_array, &this->y_buffer[6 + idx * 3], 3);
	}


	VOID AdalightBase::setColorC(UINT idx, const Color& color)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;

		UINT buff = color.toInt();
		memcpy(&this->y_buffer[6 + idx * 3], (void*)&buff, 3);
	}

	VOID AdalightBase::getColorC(UINT idx, Color& color)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;

		UINT buff;
		memcpy((void*)&buff, &this->y_buffer[6 + idx * 3], 3);
		color.fromInt(buff);
	}

	USHORT AdalightBase::getNbLeds() const
	{
		return this->nbLeds;
	}

	VOID AdalightBase::moderate(FLOAT cR, FLOAT cG, FLOAT cB)
	{
		for (UINT8 i = 6; i < this->bufferSize; i += 3)
		{
			this->y_buffer[i + 0] = (UINT8)(this->y_buffer[i + 0] * cR);
			this->y_buffer[i + 1] = (UINT8)(this->y_buffer[i + 1] * cG);
			this->y_buffer[i + 2] = (UINT8)(this->y_buffer[i + 2] * cB);
		}
	}

	INT AdalightBase::send()
	{
		INT result = serial.writeSerialPort(y_buffer, this->bufferSize);
		return result;
	}

	VOID AdalightBase::clear()
	{
		memset(this->y_buffer + 6, 0, this->bufferSize-6);
	}

	VOID AdalightBase::setHeader()
	{
		UINT8 header[] = {
			'A', 'd', 'a',
			(this->nbLeds - 1) >> 8,
			(this->nbLeds - 1) & 0xff,
			header[3] ^ header[4] ^ 0x55
		};

		memcpy(this->y_buffer, header, 6);
	}
}