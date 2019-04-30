#include "ArduinoController.h"

namespace Asemco
{
	void ArduinoController::swampOrderI(const PUINT8 in, PUINT8 out)
	{
		switch (this->colorOrder)
		{
		case ColOrder::RGB: // beacause in is RGB
			break;
		case ColOrder::RBG:
			out[0] = in[0];
			out[1] = in[2];
			out[2] = in[1];
			break;
		case ColOrder::GRB:
			out[0] = in[1];
			out[1] = in[0];
			out[2] = in[2];
			break;
		case ColOrder::GBR:
			out[0] = in[1];
			out[1] = in[2];
			out[2] = in[0];
			break;
		case ColOrder::BRG:
			out[0] = in[2];
			out[1] = in[0];
			out[2] = in[1];
			break;
		case ColOrder::BGR:
			out[0] = in[2];
			out[1] = in[1];
			out[2] = in[0];
			break;
		}
	}
	void ArduinoController::swampOrderI(PUINT8 inout)
	{
		UINT8 tmp[3];
		memcpy(tmp, inout, 3);
		swampOrderI(tmp, inout);
	}
	void ArduinoController::swampOrderO(const PUINT8 in, PUINT8 out)
	{
		switch (this->colorOrder)
		{
		case ColOrder::RGB: // beacause out is RGB
			break;
		case ColOrder::RBG:
			out[0] = in[0];
			out[2] = in[1];
			out[1] = in[2];
			break;
		case ColOrder::GRB:
			out[1] = in[0];
			out[0] = in[1];
			out[2] = in[2];
			break;
		case ColOrder::GBR:
			out[1] = in[0];
			out[2] = in[1];
			out[0] = in[2];
			break;
		case ColOrder::BRG:
			out[2] = in[0];
			out[0] = in[1];
			out[1] = in[2];
			break;
		case ColOrder::BGR:
			out[2] = in[0];
			out[1] = in[1];
			out[0] = in[2];
			break;
		}
	}
	void ArduinoController::swampOrderO(PUINT8 inout)
	{
		UINT8 tmp[3];
		memcpy(tmp, inout, 3);
		swampOrderO(tmp, inout);
	}
	ArduinoController::ArduinoController(char* port, ColOrder order)
		: serial(port)
	{
		this->nbLeds = NBLEDS;
		this->bufferSize = 6 + 3 * NBLEDS;
		this->y_buffer = new byte[this->bufferSize];
		this->colorOrder = order;

		this->clear();
		this->setHeader();
	}

	ArduinoController::ArduinoController(char* port, usize nbLeds, ColOrder order)
		: serial(port)
	{
		this->nbLeds = nbLeds;
		this->bufferSize = 6 + 3 * nbLeds;
		this->y_buffer = new byte[this->bufferSize];
		this->colorOrder = order;

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
		UINT8 tmpArr[3];
		swampOrderI(uint8_array, tmpArr);

		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;
		memcpy(&this->y_buffer[6 + idx * 3], tmpArr, 3);

	}

	void ArduinoController::getColorB(size_t idx, PUINT8 uint8_array)
	{
		UINT8 tmpArr[3];

		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;
		memcpy(tmpArr, &this->y_buffer[6 + idx * 3], 3);

		swampOrderO(tmpArr, uint8_array);
	}


	void ArduinoController::setColor(size_t idx, /*const*/ Color& color)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;

		UINT8 buff[3];color.get(buff);
		swampOrderI(buff);

		memcpy(&this->y_buffer[6 + idx * 3], buff, 3);

	}

	void ArduinoController::getColor(size_t idx, Color& color)
	{
		if (idx > this->nbLeds) throw ERR_OUTOFRANGE;

		UINT8 buff[3];

		memcpy(buff, &this->y_buffer[6 + idx * 3], 3);
		swampOrderO(buff);

		color.set(buff);
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
		UINT8 color[3];
		Color tmp = Color();

		for (size_t i = 6; i < this->bufferSize; i += 3)
		{
			swampOrderO(&y_buffer[i], color);

			tmp.set(color);
			tmp.coef(cr, cg, cb);
			tmp.get(color);

			swampOrderI(&y_buffer[i], color);
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