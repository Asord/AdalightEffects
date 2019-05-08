#pragma once
#include <AsColors.h>
#include <string>

namespace Asemco
{
	#define readFile(file, buff, size) file.read((char*)buff, size)

	class TemplateReader
	{
	private:
		const UINT8 magic[3] = "At";
		UINT8 nbColors;
		UINT8 nbFrames;
		UINT8 frameLen;

		UINT nbElements;

		FLOAT speed;
		FLOAT coefs[3];

		Color* colors;


		PUINT8 ledstemplate;

	public:
		TemplateReader(std::string file);
		~TemplateReader();

		UINT8 getNbColors() const;
		UINT8 getNbFrames() const;
		UINT8 getFrameLen() const;
		UINT getNbElements() const;

		FLOAT getSpeed() const;
		VOID getCoefs(FLOATR, FLOATR, FLOATR) const;

		Color* getColors() const;

		PUINT8 getLedsTemplate() const;
	};
}