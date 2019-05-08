#include "templateE.h"

namespace Asemco
{
	TemplateE::TemplateE(Controller * controller, std::string file)
		: fileData(file), VirtualTemplate(0x08, controller)
	{
		this->speed = (INT)(fileData.getSpeed()*1000);
		this->framePos = 0;
		this->data = fileData.getLedsTemplate();
		this->colors = fileData.getColors();
	}

	VOID TemplateE::Update()
	{
		this->controller->clear();

		Color col;
		UINT frameLen;
		PUINT8 frame_ptr;
		FLOAT coefR, coefG, coefB;

		if (this->framePos >= fileData.getNbFrames())
			this->framePos = 0;

		frameLen = fileData.getFrameLen();

		frame_ptr = data + frameLen*this->framePos*sizeof(char);

		if (frameLen > this->controller->getNbLeds())
			frameLen = this->controller->getNbLeds();

		for (UINT i = 0; i < frameLen; ++i)
		{
			col = colors[frame_ptr[i]];
			this->controller->setColorC(i, col);
		}

		fileData.getCoefs(coefR, coefG, coefB);
		this->controller->moderate(coefR, coefG, coefB);

		this->controller->send();
		this->framePos += 1;
	}
}
