#pragma once
#include "abstractTemplate.h"
#include "../tools/templateReader.h"


namespace Asemco
{
	class TemplateE : public AbstractTemplate
	{
	public:
		int speed;

	private:
		TemplateReader fileData;

		int framePos;

		char* data;
		Color* colors;

	public:
		TemplateE(ArduinoController*, std::string file);
		void update();
	};


}