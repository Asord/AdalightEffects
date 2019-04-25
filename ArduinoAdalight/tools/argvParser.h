#pragma once
#include <string>

namespace Asemco
{
#define param(X) arg.find(X) == 0

#define singleParamBreak(X, object) \
if(param(X)) { \
	object = true;\
	break;\
}

#define singleParamContinue(X, object) \
if(param(X)) { \
	object = true;\
	continue;\
}

#define twoParamConvert(X, object, conv) \
if(param(X)) \
	object = conv(argv[i + 1]); 


struct config
{
	int n_loopCount = 200;
	int n_startupEffect = 0;
	int n_sleepms = 50;

	float f_rainbowStaticHueCoef = 1.0f;
	float f_movingRainbowHueCoef = 2.0f;
	int n_rainbowDirection = 1;

	int n_haloStartPos = 0;

	int n_nbFlares = 5;

	bool b_clearAllLeds = false;
	bool b_doLoopAtEnd = true;

	bool b_doRainbowStatic = false;
	bool b_doMovingRainbow = false;
	bool b_doRainbowYipYop = false;
	bool b_doFlares = false;
	bool b_doTemplate = false;
	bool b_doHalo = false;

	int n_haloColor[3] = { 0xff, 0x0, 0x0 };

	std::string s_templateFile;
	std::string portName = "\\\\.\\COM4";
};

std::string getexepath();


config argvParser(int argc, char* argv[]);

}