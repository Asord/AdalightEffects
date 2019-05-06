#include "AsSerial.h"

#define SER_UNKNOWN 0x20
#define SER_NOTSETTABLE 0x21
#define SER_NOTGETTABLE 0x22
#define SER_NOTAVALIABLE 0x23

namespace Asemco
{
	BaseSerial::BaseSerial(LPCSTR portName)
	{
		this->b_connected = FALSE;
		this->p_portName = portName;
		connect();
	}

	BaseSerial::~BaseSerial()
	{
		this->disconnect();
	}

	INT BaseSerial::connect()
	{
		this->H_handler = CreateFileA(this->p_portName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (this->H_handler == INVALID_HANDLE_VALUE)
			if (GetLastError() == ERROR_FILE_NOT_FOUND)
				return SER_NOTAVALIABLE;
			else
				return SER_UNKNOWN;

		else
		{
			DCB dcbSerialParameters = { 0 };

			if (!GetCommState(this->H_handler, &dcbSerialParameters))
				return SER_NOTGETTABLE;

			else
			{
				dcbSerialParameters.BaudRate = CBR_115200;
				dcbSerialParameters.ByteSize = 8;
				dcbSerialParameters.StopBits = ONESTOPBIT;
				dcbSerialParameters.Parity = NOPARITY;
				dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

				if (!SetCommState(H_handler, &dcbSerialParameters))
					return SER_NOTSETTABLE;

				else
				{
					this->b_connected = TRUE;
					PurgeComm(this->H_handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
					Sleep(ARDUINO_WAIT_TIME);
					return 0;
				}
			}
		}
		return -1;
	}

	VOID BaseSerial::disconnect()
	{
		if (this->b_connected)
		{
			this->b_connected = FALSE;
			CloseHandle(this->H_handler);
		}
	}

	INT BaseSerial::readSerialPort(PUINT8 buffer, UINT buf_size)
	{
		if (!b_connected)
		{
			int err = this->connect();
			if (err != 0) return 0;
		}


		DWORD bytesRead = 0;
		UINT toRead = 0;

		ClearCommError(this->H_handler, &this->ul_errors, &this->cs_status);

		if (this->cs_status.cbInQue > 0)
		{
			if (this->cs_status.cbInQue > buf_size)
			{
				toRead = buf_size;
			}
			else toRead = this->cs_status.cbInQue;
		}

		if (ReadFile(this->H_handler, buffer, toRead, &bytesRead, NULL))
			return bytesRead;

		else this->disconnect();

		return 0;
	}

	BOOL BaseSerial::writeSerialPort(PUINT8 buffer, UINT buf_size)
	{
		if (!b_connected)
		{
			INT err = this->connect();
			if (err != 0) return FALSE;
		}

		DWORD bytesSend;

		if (!WriteFile(this->H_handler, (void*)buffer, buf_size, &bytesSend, 0))
		{
			ClearCommError(this->H_handler, &this->ul_errors, &this->cs_status);
			this->disconnect();
			return FALSE;
		}

		return TRUE;
	}

	BOOL BaseSerial::isConnected()
	{
		return this->b_connected;
	}
}