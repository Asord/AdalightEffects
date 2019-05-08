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

		if (strcmp(signature, (const char*)this->magic) == 0)
		{
			readFile(myFile, &this->nbColors, 1);
			readFile(myFile, &this->nbFrames, 1);
			readFile(myFile, &this->frameLen, 1);
			readFile(myFile, &this->speed, 4);
			readFile(myFile, &this->coefs, 12);
			
			colors = new Color[this->nbColors]; UINT8 buf[3];
			for (int i = 0; i < this->nbColors; ++i)
			{
				readFile(myFile, buf, 3);
				colors[i] = Color(buf);
			}

			this->nbElements = this->nbFrames*this->frameLen;
			this->ledstemplate = new UINT8[this->nbElements];

			readFile(myFile, this->ledstemplate, this->nbElements);
		}
		myFile.close();
	}
}


Asemco::TemplateReader::~TemplateReader()
{
	delete[this->nbElements] this->ledstemplate;
	delete[this->nbColors] this->colors;
}

UINT8 Asemco::TemplateReader::getNbColors()const 
{
	return (int)this->nbColors;
}

UINT8 Asemco::TemplateReader::getNbFrames() const
{
	return (int)this->nbFrames;
}

UINT8 Asemco::TemplateReader::getFrameLen() const
{
	return (int)this->frameLen;
}

UINT Asemco::TemplateReader::getNbElements() const
{
	return this->nbElements;
}

FLOAT Asemco::TemplateReader::getSpeed() const
{
	return this->speed;
}

VOID Asemco::TemplateReader::getCoefs(FLOATR coefR, FLOATR coefG, FLOATR coefB) const
{
	coefR = this->coefs[0];
	coefG = this->coefs[1];
	coefB = this->coefs[2];
}

Asemco::Color * Asemco::TemplateReader::getColors() const
{
	return colors;
}

PUINT8 Asemco::TemplateReader::getLedsTemplate() const
{
	return this->ledstemplate;
}
