#pragma once
#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>

namespace Asemco
{
	class Serial
	{
	private:
		HANDLE H_handler;
		BOOL b_connected;
		COMSTAT cs_status;
		DWORD ul_errors;

		LPCSTR p_portName;

	public:
		Serial(LPCSTR portName);
		~Serial();

		INT connect();
		VOID disconnect();

		INT readSerialPort(PUINT8 buffer, UINT buf_size);
		BOOL writeSerialPort(PUINT8 buffer, UINT buf_size);
		BOOL isConnected();
	};
}
