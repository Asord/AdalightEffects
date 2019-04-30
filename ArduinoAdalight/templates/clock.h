#pragma once
#include "abstractTemplate.h"
#include <time.h>

namespace Asemco
{
	class Clock : public AbstractTemplate
	{
	private:
		time_t theTime;
		struct tm* aTime;

		int hour;
		int min;
		int sec;

		Color hColor;
		Color mColor;
		Color sColor;

		int updateType = 0;

	public:
		Clock(ArduinoController* controller, UINT8 lightPercent);

		void update();
		void updateBinary();
		void updateShade();

		void getClockTime();


		void setShadeAtPos(UINT8 decade, UINT8 pos);
		void setColAtPos(Color& color, UINT8 pos);
	};

}