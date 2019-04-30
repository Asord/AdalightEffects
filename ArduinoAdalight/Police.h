#pragma once
#include "Serial.h"

class Police
{
public:
	int speed;

private:
	Serial serial;

	int framePos;
	int frameLen;
	unsigned char* data;

	byte* y_buffer;

public:
	Police();
	void update();
};
