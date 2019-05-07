#include "Adalightcontroller.h"

namespace Asemco
{
	AdalightController::AdalightController(LPCSTR port)
		: SerialController(port, 6)
	{
		this->setHeader();
	}

	AdalightController::AdalightController(LPCSTR port, UINT8 nbLeds)
		: SerialController(port, nbLeds, 6)
	{
		this->setHeader();
	}

	VOID AdalightController::setHeader()
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