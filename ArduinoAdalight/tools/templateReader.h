#pragma once
#include "../defines.h"
#include "../tools/color.h"

namespace Asemco
{
class TemplateReader
{
private:
	char magic[3] = "At";
	char nbColors;
	char nbFrames;
	char frameLen;
	float speed;
	float coefs[3];
	Color* colors;

	int nbElements;

	char* ledstemplate;

public:
	TemplateReader(std::string file);
	~TemplateReader();

	int getNbColors();
	int getNbFrames();
	int getFrameLen();
	int getNbElements();
	float getSpeed();
	float* getCoefs();
	Color* getColors();

	char* getLedsTemplate();
};
}