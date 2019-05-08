#pragma once
#include <time.h>
#include <VirtualTemplate.h>

/* TODO: test this template */
namespace Asemco
{
	class Clock : public VirtualTemplate
	{
	private:
		time_t theTime;
		struct tm* aTime;

		INT hour, min, sec;
		Color hColor, mColor, sColor;

		UINT8 updateType = 0;

	public:
		Clock(Controller* controller, UINT8 lightPercent);

		VOID Update();
		VOID updateBinary();
		VOID updateShade();

		VOID getClockTime();


		VOID setShadeAtPos(UINT8 decade, UINT8 pos);
		VOID setColAtPos(Color& color, UINT8 pos);
	};

}