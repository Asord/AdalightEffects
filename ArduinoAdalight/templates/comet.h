#pragma once
#include <VirtualTemplate.h>

namespace Asemco
{
	enum Step {COMET, BLINK, VANISH};


	class Comet : public VirtualTemplate
	{
	public:
		USHORT limit;
		USHORT cPos;
		USHORT cSize;
		SHORT cDir;

		Color cColor;
		Step step;

		UINT8 nbLeds;

	public:
		Comet(Controller* controller);
		VOID Update();

	private:
		VOID comet();
		VOID blink();
		VOID vanish();

		VOID switchEffect();
		VOID randomColor();
	};
}