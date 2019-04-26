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


		ArduinoController* p_controller;


	public:
		Clock(ArduinoController* controller);

		void update();

		void getClockTime();

		void setColAtPos(Color& color, size_t pos);
	};

}