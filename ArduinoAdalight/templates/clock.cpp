#include "clock.h"

namespace Asemco
{
	Clock::Clock(ArduinoController * controller)
	{
		this->init(controller);
	}

	void Clock::update()
	{
		this->getClockTime();
		this->p_controller->clear();

		Color hColor = Color(128, 128, 0);
		Color mColor = Color(0, 80, 0);
		Color sColor = Color(40, 128, 128);

		for (int i =0; i < 6; ++i)
		{
			int hpos = i + 41;
			int mpos = 40 - i;
			int spos = i + 29;

			if (this->hour & 1 << i)
				this->setColAtPos(hColor, hpos);

			if (this->min & 1 << i)
				this->setColAtPos(mColor, mpos);

			if (this->sec & 1 << i)
				this->setColAtPos(sColor, spos);
		}

		this->p_controller->moderate(1.0f, 0.42f, 0.3f);
		this->p_controller->send();
	}

	void Clock::getClockTime()
	{

		this->theTime = time(NULL);
		this->aTime = localtime(&theTime);

		this->hour = aTime->tm_hour%12;
		this->min = aTime->tm_min;
		this->sec = aTime->tm_sec;
	}

	void Clock::setColAtPos(Color& color, size_t pos)
	{
		CBytes bytes = color.toBytes();
		this->p_controller->setColor(pos, bytes.color);
	}

}