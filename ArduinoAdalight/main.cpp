#include <iostream>
#include <stdio.h>

#include "templates.h"
#include "tools/argumentsParser.h"


using namespace Asemco;

int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));

	config c = argvParser(argc, argv);

	ArduinoController controller((char*)c.portName.c_str(), c.n_nbLeds);

	int baseCounter = c.n_loopCount;
	int loopCounter = baseCounter;
	int effect = 0;

	if (c.b_clearAllLeds)
	{
		controller.clear();
		controller.send();
		exit(0);
	}

	ptrArray effectsArray(6);
	AbstractTemplate* tpl;

	if (c.b_doRainbowStatic)
		effectsArray.append(new RainbowStatic(&controller, c.f_rainbowStaticHueCoef));

	if (c.b_doMovingRainbow)
		effectsArray.append(new Rainbow(&controller, c.f_movingRainbowHueCoef, c.n_rainbowDirection));

	if (c.b_doRainbowYipYop)
		effectsArray.append(new RainbowYipyop(&controller));

	if (c.b_doFlares)
		effectsArray.append(new Flare(&controller, c.n_nbFlares));

	if (c.b_doTemplate)
		effectsArray.append(new TemplateE(&controller, c.s_templateFile));

	if (c.b_doHalo)
		effectsArray.append(new Halo(&controller, Color(c.n_haloColor), c.n_haloStartPos));

	if(c.b_doClock)
		effectsArray.append(new Clock(&controller, c.n_clockIntensity));

	if(c.b_doComet)
		effectsArray.append(new Comet(&controller));


	if (effectsArray.size() == 0)
		return 0;

	tpl = (AbstractTemplate*)effectsArray[0];

	int sleepTime = c.n_sleepms;

	while(1)
	{
		if (loopCounter == 0)
		{
			loopCounter = baseCounter;
			++effect;

			if (effect == effectsArray.size())
			{
				if (c.b_doLoopAtEnd) effect = 0;
				else return 0;
			}

			tpl = (AbstractTemplate*)effectsArray[effect];

			if (isInstance(TemplateE, tpl))
			{
				TemplateE* e = dynamic_cast<TemplateE*>(tpl);
				sleepTime = e->speed;
			}
			else
			{
				sleepTime = c.n_sleepms;
			}
		}

		tpl->update();
		Sleep(sleepTime);
		--loopCounter;
	}
}