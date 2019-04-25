#pragma once
#include "abstractTemplate.h"
#include "../tools/ptrArray.h"

namespace Asemco
{
	struct flare_obj
	{
		ushort n_pos;
		ushort n_delta;
		Color color;
		flare_obj(short pos, Color color);
	};

	class Flare : public AbstractTemplate
	{
	private:
		ushort nbFlares;
		Asemco::ptrArray flares;
		void setColorAt(short, Color*);

	public:
		Flare(ArduinoController*, ushort);
		void update();
	};


}