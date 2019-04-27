#pragma once
#include "abstractTemplate.h"

namespace Asemco
{
	enum Step {COMET, BLINK, VANISH};


	class Comet : public AbstractTemplate
	{
	public:

		unsigned short limit;
		unsigned short cPos;
		unsigned short cSize;
		short cDir;

		Color cColor;
		CBytes bytes;
		Step step;

	public:
		Comet(ArduinoController* controller);

		void update();

	private:
		void comet();
		void blink();
		void vanish();

		void switchEffect();

		void randomColor();
	};
}