#include "police.h"
#include "policetpl.h"

char port[] = "\\\\.\\COM4";

Police::Police(): serial(port)
{
	/* local init*/

	this->speed = tplspeed;
	this->frameLen = tplframelen;
	this->data = policetpl;

	this->framePos = 0;

	/* serial init */
	this->y_buffer = new byte[6+ this->frameLen];

	// header
	memcpy(this->y_buffer, "Ada", 3);
	this->y_buffer[3] = (22 - 1) >> 8;
	this->y_buffer[4] = (22 - 1) & 0xff;
	this->y_buffer[5] = this->y_buffer[3] ^ this->y_buffer[4] ^ 0x55;
}

void Police::update()
{
	// compute data shift
	int shift = this->frameLen*this->framePos;

	memcpy(&this->y_buffer[6], &this->data[shift], this->frameLen);

	this->framePos++;
	if (this->framePos == tplnbFrames) this->framePos = 0;

	serial.writeSerialPort(this->y_buffer, 6 + this->frameLen);
}
