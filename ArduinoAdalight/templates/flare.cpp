#include "flare.h"

namespace Asemco
{
	flare_obj::flare_obj(SHORT pos, Color color)
	{
		this->n_pos = pos;
		this->n_delta = 0;
		this->color = color;
	}


	Flare::Flare(Controller* controller, USHORT nbFlares) 
		: flares(nbFlares), VirtualTemplate(0x03, controller)
	{
		this->nbLeds = this->controller->getNbLeds();
		this->nbFlares = nbFlares;

	}


	void Flare::Update()
	{
		this->controller->clear();

		Color color;
		USHORT pos, delta;

		for (UINT i = 0; i < this->flares.size(); ++i)
		{

			flare_obj* flare = _cast(flare_obj, this->flares[i]);

			pos = flare->n_pos;
			delta = flare->n_delta;
			color = flare->color;


			if (pos - delta < 0 and pos + delta > this->nbLeds - 1)
				this->flares.remove(i);

			else
			{
				short pos_0 = (pos - delta > 0) ? pos - delta : 0;

				short pos_1 = pos + delta;
				if (pos + delta > this->nbLeds - 1)
					pos_1 = 7 + this->nbLeds - (pos + delta);

				pos_1 = (pos_1 > 0) ? pos_1 : 0;


				setColorAt(pos_0, color);

				if (pos_0 != pos_1)
					setColorAt(pos_1, color);

				flare->n_delta += 1;
			}
		}


		if (flares.size() < this->nbFlares)
		{
			if ((rand() % 100) < 10)
			{
				pos = 5 + rand() % (this->nbLeds - 5);
				color.ramdomColor();

				this->flares.append(new flare_obj(pos, color));
			}
		}

		this->controller->moderate(1.0f, 0.3f, 0.42f);
		this->controller->send();
	}

	void Flare::setColorAt(SHORT pos, const Color& color)
	{
		Color atPos = Color();

		controller->getColorC(pos, atPos);
		atPos += color;

		this->controller->setColorC(pos, atPos);
	}
}