#include "templateReader.h"
#include <fstream>

Asemco::TemplateReader::TemplateReader(std::string file)
{
	std::ifstream myFile(file, std::ios::in | std::ios::binary);
	if (myFile.is_open())
	{
		char signature[3]; 
		memset(signature, 0, 3);

		myFile.seekg(0, std::ios::beg);
		myFile.read(signature, 2);

		if (strcmp(signature, this->magic) == 0)
		{
			myFile.read(&this->nbColors, 1);
			myFile.read(&this->nbFrames, 1);
			myFile.read(&this->frameLen, 1);
			myFile.read((char*)&this->speed, 4);
			myFile.read((char*)&this->coefs, 12);
			
			colors = new Color[this->nbColors];
			for (int i = 0; i < this->nbColors; ++i)
			{
				char buf[3];
				myFile.read(buf, 3);
				colors[i] = Color((PUINT8)buf);
			}

			this->nbElements = this->nbFrames*this->frameLen;
			this->ledstemplate = new char[this->nbElements];

			myFile.read(this->ledstemplate, this->nbElements);
		}
		myFile.close();
	}
}


Asemco::TemplateReader::~TemplateReader()
{
	delete[this->nbElements] this->ledstemplate;
	delete[this->nbColors] this->colors;
}

int Asemco::TemplateReader::getNbColors()
{
	return (int)this->nbColors;
}

int Asemco::TemplateReader::getNbFrames()
{
	return (int)this->nbFrames;
}

int Asemco::TemplateReader::getFrameLen()
{
	return (int)this->frameLen;
}

int Asemco::TemplateReader::getNbElements()
{
	return this->nbElements;
}

float Asemco::TemplateReader::getSpeed()
{
	return this->speed;
}

float* Asemco::TemplateReader::getCoefs()
{
	return this->coefs;
}

Asemco::Color * Asemco::TemplateReader::getColors()
{
	return colors;
}

char* Asemco::TemplateReader::getLedsTemplate()
{
	return this->ledstemplate;
}
