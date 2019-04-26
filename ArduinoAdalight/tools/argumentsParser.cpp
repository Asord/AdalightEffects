#include "argumentsParser.h"
#include <iostream>
#include <windows.h>

namespace Asemco {
	config argvParser(int argc, char* argv[])
	{
		config c;

		std::string param = "";
		for (int i = 1; i < argc; ++i)
		{
			std::string arg = argv[i];

			singleParamBreak("-clearleds", c.b_clearAllLeds);

			singleParamContinue("-rainbow", c.b_doMovingRainbow);
			singleParamContinue("-yipyop", c.b_doRainbowYipYop);
			singleParamContinue("-rainbowstatic", c.b_doRainbowStatic);
			singleParamContinue("-flares", c.b_doFlares);
			singleParamContinue("-clock", c.b_doClock);

			twoParamConvert("-steps", c.n_loopCount, std::stoi);
			twoParamConvert("-sleep", c.n_sleepms, std::stoi);
			twoParamConvert("-dir", c.n_rainbowDirection, std::stoi);
			twoParamConvert("-coefstatic", c.f_rainbowStaticHueCoef, std::stof);
			twoParamConvert("-coefrainbow", c.f_movingRainbowHueCoef, std::stof);
			twoParamConvert("-nbflares", c.n_nbFlares, std::stoi);
			twoParamConvert("-offsethalo", c.n_haloStartPos, std::stoi);
			twoParamConvert("-nbleds", c.n_nbLeds, std::stoi);

			if (param("-halo"))
			{
				c.b_doHalo = true;

				char* color = argv[i + 1]+1;
				if (color[0] == '#' && color[7] == '\x0') // only right sized data
					sscanf(color, "%02x%02x%02x", &c.n_haloColor[0], &c.n_haloColor[1], &c.n_haloColor[2]);
			}

			if (param("-template"))
			{
				c.b_doTemplate = true;

				std::string path = getexepath();
				size_t exePos = path.find_last_of("/\\");
				c.s_templateFile = path.substr(0, exePos + 1);
				c.s_templateFile += argv[i + 1];
			}

			if (param("-port"))
				c.portName = std::string("\\\\.\\") + argv[i + 1];

			if (param("-loop"))
			{
				char p = argv[i + 1][0];
				if (p == 'y' or p == 'Y')
					c.b_doLoopAtEnd = true;
				else
					c.b_doLoopAtEnd = false;
			}

			if (param("-help"))
			{
				std::cout << "Avaliable parametters: " << std::endl;
				std::cout << "-clearleds to clear all leds (black)\n";
				std::cout << " -flares -rainbow -rainbowstatic -yipyop\n\n";
				std::cout << "-halo  (#RRGGBB)00:FF            Display halo effect with given color\n";
				std::cout << "-offsethalo (int)0:1199          Shade start point of halo effect\n\n";
				std::cout << "-port COM[0-99]                  Change port (default: COM4)\n";
				std::cout << "-nbleds (int)1:255               Number of leds to use\n";
				std::cout << "-steps (int)1:999                How many steps per templates\n";
				std::cout << "-sleep (int)1:2000               Sleep time in ms per step\n\n";
				std::cout << "-coefstatic (float)0.01:360.0    Shade coef of rainbowStatic\n";
				std::cout << "-coefrainbow (float)0.01:360.0   Shade coef of rainbow\n\n";
				std::cout << "-nbflares (int)1:20              How many flares max to display\n\n";
				std::cout << "-dir 1 or -1                     Direction of the rainbow\n";
				std::cout << "-loop y or n                     Do loop at the end of all templates ?\n" << std::endl;
				exit(0);
			}

			++i;
		}
		return c;
	}

	std::string Asemco::getexepath()
	{
		char result[MAX_PATH];
		return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
	}
}