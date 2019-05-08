#pragma once
#include <VirtualTemplate.h>
#include "../tools/ptrArray.h"

typedef unsigned short ushort;

/* TODO: test this template */
namespace Asemco
{
	struct flare_obj
	{
		ushort n_pos;
		ushort n_delta;
		Color color;
		flare_obj(SHORT pos, Color color);
	};

	class Flare : public VirtualTemplate
	{
	private:
		UINT nbLeds;
		USHORT nbFlares;
		Asemco::ptrArray flares;

	public:
		Flare(Controller*, USHORT);
		VOID Update();

	private:
		VOID setColorAt(SHORT, const Color&);
	};


}