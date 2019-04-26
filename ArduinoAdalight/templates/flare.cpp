#include "flare.h"

namespace Asemco
{
	flare_obj::flare_obj(short pos, Color color)
	{
		this->n_pos = pos;
		this->n_delta = 0;
		this->color = color;
	}


	Flare::Flare(ArduinoController* controller, ushort nbFlares) : flares(nbFlares)
	{
		this->init(controller);

		this->p_controller = controller;
		this->nbFlares = nbFlares;

	}


	void Flare::update()
	{
		this->p_controller->clear();

		for (size_t i = 0; i < this->flares.size(); ++i)
		{

			flare_obj* flare = _cast(flare_obj, this->flares[i]);

			ushort pos = flare->n_pos;
			ushort delta = flare->n_delta;
			Color color = flare->color;


			if (pos - delta < 0 and pos + delta > this->nbLeds - 1)
				this->flares.remove(i);

			else
			{
				short pos_0 = (pos - delta > 0) ? pos - delta : 0;

				short pos_1 = pos + delta;
				if (pos + delta > this->nbLeds - 1)
					pos_1 = 7 + this->nbLeds - (pos + delta);

				pos_1 = (pos_1 > 0) ? pos_1 : 0;


				setColorAt(pos_0, &color);

				if (pos_0 != pos_1)
					setColorAt(pos_1, &color);

				flare->n_delta += 1;
			}
		}


		if (flares.size() < this->nbFlares)
		{
			if (chance(10))
			{
				ushort pos = 5 + rand() % (this->nbLeds - 5);
				Color color = Color();
				color.randomColor();

				this->flares.append(new flare_obj(pos, color));
			}
		}

		this->p_controller->moderate(1.0f, 0.3f, 0.42f);
		this->p_controller->send();
	}

	void Flare::setColorAt(short pos, Color* color)
	{
		CBytes buff;
		p_controller->getColor(pos, buff.color);
		Color col = Color(buff);
		col += *color;

		CBytes bytes = col.toBytes();
		this->p_controller->setColor(pos, bytes.color);
	}
}