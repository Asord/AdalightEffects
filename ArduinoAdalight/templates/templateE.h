#pragma once
#include <VirtualTemplate.h>
#include "../tools/templateReader.h"

namespace Asemco
{
	#define isInstance(Type, ptr) dynamic_cast<Type*>(ptr) != nullptr

	/* TODO: test this template */
	class TemplateE : public VirtualTemplate
	{
	public:
		INT speed;

	private:
		TemplateReader fileData;

		UINT framePos;

		UINT8* data;
		Color* colors;

	public:
		TemplateE(Controller*, std::string file);
		VOID Update();
	};


}