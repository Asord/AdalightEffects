#include <iostream>
#include <stdio.h>

#include "templates.h"
#include "tools/argvParser.h"


using namespace Asemco;

int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));

	config c = argvParser(argc, argv);

	ArduinoController controller((char*)c.portName.c_str());

	int baseSwitcher = c.n_loopCount;
	int effectSwitcher = baseSwitcher;
	int effect = c.n_startupEffect;

	RainbowStatic rs = RainbowStatic(&controller, c.f_rainbowStaticHueCoef);
	Rainbow ra = Rainbow(&controller, c.f_movingRainbowHueCoef, c.n_rainbowDirection);
	RainbowYipyop ry = RainbowYipyop(&controller);
	Flare fl = Flare(&controller, c.n_nbFlares);
	TemplateE te = TemplateE(&controller, c.s_templateFile);
	Halo ha = Halo(&controller, Color(c.n_haloColor), c.n_haloStartPos);

	if (c.b_clearAllLeds)
	{
		controller.clear();
		controller.send();
		exit(0);
	}



	while(1)
	{

		if (effectSwitcher == 0)
		{
			effectSwitcher = baseSwitcher;
			++effect;
		}

		switch (effect)
		{
		case 0:
			if (c.b_doRainbowStatic) 
			{
				rs.update();
				Sleep(c.n_sleepms);
			}
			else ++effect;
			break;

		case 1:
			if (c.b_doMovingRainbow) 
			{
				ra.update();
				Sleep(c.n_sleepms);
			}
			else ++effect;
			break;

		case 2:
			if (c.b_doRainbowYipYop) 
			{
				ry.update();
				Sleep(c.n_sleepms);
			}
			else ++effect;
			break;

		case 3:
			if (c.b_doFlares) 
			{
				fl.update();
				Sleep(c.n_sleepms);
			}
			else ++effect;
			break;
		case 4:
			if (c.b_doTemplate)
			{
				te.update();
				Sleep((DWORD)te.speed);
			}
			else ++effect;
			break;
		case 5:
			if (c.b_doHalo)
			{
				ha.update();
				Sleep(c.n_sleepms);
			}
			else ++effect;
			break;
		default:
			if (c.b_doLoopAtEnd)
			{
				effect = 0;
				break;
			}
			else exit(0);
		}
		--effectSwitcher;
	}
}