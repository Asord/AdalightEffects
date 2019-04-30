#include "clock.h"

namespace Asemco
{
	Clock::Clock(ArduinoController * controller, UINT8 lightPercent)
	{
		this->init(controller);

		hColor = Color(255, 255, 0)*(lightPercent / 100.0f);
		mColor = Color(0,   255, 0)*(lightPercent / 100.0f);
		sColor = Color(255,   0, 0)*(lightPercent / 100.0f);
	}

	void Clock::update()
	{
		this->getClockTime();
		this->p_controller->clear();

		switch (this->updateType)
		{
		case 0:
			this->updateBinary();
			break;
		case 1:
			this->updateShade();
			break;
		}

		this->p_controller->moderate(1.0f, 0.42f, 0.3f);
		this->p_controller->send();
	}

	void Clock::updateBinary()
	{
		for (UINT8 i = 0; i < 6; ++i)
		{
			UINT8 hpos = i + 41;
			UINT8 mpos = 40 - i;
			UINT8 spos = i + 29;

			if (this->hour & 1 << i)
				this->setColAtPos(hColor, hpos);

			if (this->min & 1 << i)
				this->setColAtPos(mColor, mpos);

			if (this->sec & 1 << i)
				this->setColAtPos(sColor, spos);
		}

	}

	void Clock::updateShade()
	{
		UINT8 unit;
		UINT8 decade;

		UINT8 hpos = 41; // ++
		UINT8 mpos = 40; // --
		UINT8 spos = 29; // ++

		// hour
		unit = this->hour % 10;
		decade = (this->hour - unit) / 10;
		this->setShadeAtPos(decade, hpos + decade);
		this->setShadeAtPos(unit, hpos);

		unit = this->min % 10;
		decade = (this->min - unit) / 10;
		this->setShadeAtPos(decade, mpos - decade);
		this->setShadeAtPos(unit, mpos);

		unit = this->sec % 10;
		decade = (this->sec - unit) / 10;
		this->setShadeAtPos(decade, spos + decade);
		this->setShadeAtPos(unit, spos);
	}

	void Clock::getClockTime()
	{

		this->theTime = time(NULL);
		this->aTime = localtime(&theTime);

		this->hour = aTime->tm_hour%12;
		this->min = aTime->tm_min;
		this->sec = aTime->tm_sec;
	}	
	
	void Clock::setShadeAtPos(UINT8 shade, UINT8 pos)
	{
		float hue;

		hue = 120.0f / 10.0f * shade;
		hColor = Color().fromHSV(hue, 1.0f, 1.0f);

		this->setColAtPos(hColor, pos);
	}

	void Clock::setColAtPos(Color& color, UINT8 pos)
	{
		this->p_controller->setColor(pos, color);
	}



}