#pragma once
#include "SerialController.h"


namespace Asemco
{
	class AdalightController: public SerialController
	{
	public:
		AdalightController(LPCSTR port);
		AdalightController(LPCSTR port, UINT8 nbLeds);

	#ifdef _ALLPUBLIC
	public:
	#else
	private:
	#endif
		void setHeader();
	};
}