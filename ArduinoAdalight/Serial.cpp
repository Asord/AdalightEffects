#include "Serial.h"

#define SER_UNKNOWN 0x20
#define SER_NOTSETTABLE 0x21
#define SER_NOTGETTABLE 0x22
#define SER_NOTAVALIABLE 0x23

namespace Asemco
{
	Serial::Serial(char *portName)
	{
		this->b_connected = false;
		this->p_portName = portName;
		connect();
	}

	Serial::~Serial()
	{
		this->disconnect();
	}

	int Serial::connect()
	{
		this->H_handler = CreateFileA(static_cast<LPCSTR>(this->p_portName),
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
					this->b_connected = true;
					PurgeComm(this->H_handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
					Sleep(ARDUINO_WAIT_TIME);
					return 0;
				}
			}
		}
		return -1;
	}

	void Serial::disconnect()
	{
		if (this->b_connected)
		{
			this->b_connected = false;
			CloseHandle(this->H_handler);
		}
	}

	int Serial::readSerialPort(byte *buffer, unsigned int buf_size)
	{
		if (!b_connected)
		{
			int err = this->connect();
			if (err != 0) return 0;
		}


		DWORD bytesRead = 0;
		unsigned int toRead = 0;

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

	bool Serial::writeSerialPort(byte *buffer, unsigned int buf_size)
	{
		if (!b_connected)
		{
			int err = this->connect();
			if (err != 0) return false;
		}

		DWORD bytesSend;

		if (!WriteFile(this->H_handler, (void*)buffer, buf_size, &bytesSend, 0))
		{
			ClearCommError(this->H_handler, &this->ul_errors, &this->cs_status);
			this->disconnect();
			return false;
		}

		return true;
	}

	bool Serial::isConnected()
	{
		return this->b_connected;
	}
}