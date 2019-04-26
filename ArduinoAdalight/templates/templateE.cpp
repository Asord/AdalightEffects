#include "templateE.h"

namespace Asemco
{
	TemplateE::TemplateE(ArduinoController * controller, std::string file): fileData(file)
	{
		this->init(controller);

		this->speed = (int)(fileData.getSpeed()*1000);
		this->framePos = 0;
		this->data = fileData.getLedsTemplate();
		this->colors = fileData.getColors();
	}

	void TemplateE::update()
	{
		this->controller->clear();

		if (this->framePos >= fileData.getNbFrames())
		{
			this->framePos = 0;
		}

		size_t frameLen = fileData.getFrameLen();

		char* frame = data + frameLen*this->framePos*sizeof(char);

		if (frameLen > this->nbLeds)
		{
			frameLen = this->nbLeds;
		}

		for (size_t i = 0; i < frameLen; ++i)
		{
			Color col = colors[frame[i]];
			CBytes bytes = col.toBytes();
			this->controller->setColor(i, bytes.color);
		}

		float* coefs = fileData.getCoefs();
		this->controller->moderate(coefs[0], coefs[1], coefs[2]);

		this->controller->send();
		this->framePos += 1;
	}
}
