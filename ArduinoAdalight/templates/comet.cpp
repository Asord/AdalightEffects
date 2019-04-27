#include "comet.h"

namespace Asemco
{
	Comet::Comet(ArduinoController* controller)
	{
		this->init(controller);

		this->step = Step::VANISH;
		this->switchEffect(); // init to comet effect
	}

	void Asemco::Comet::update()
	{
		this->p_controller->clear();

		switch (this->step)
		{
		case(Step::COMET):
			this->comet();
			break;
		case(Step::BLINK):
			this->blink();
			break;
		case(Step::VANISH):
			this->vanish();
			break;
		}

		this->p_controller->send();


	}

	void Comet::comet()
	{
		if (this->cDir > 0){

			this->limit = max(this->cPos - this->cSize, 0);
			for (int i = this->cPos; i > limit; --i)
				this->p_controller->setColor(i, this->bytes.color);

		}else{

			this->limit = min(this->cPos + this->cSize, this->nbLeds);
			for (int i = this->cPos; i < limit; ++i)
				this->p_controller->setColor(i, this->bytes.color);
		}


		this->cPos += this->cDir;
		if (this->cPos == 0 || this->cPos >= this->nbLeds)
		{
			this->cSize++;
			if (this->cSize >= this->nbLeds)
			{
				this->switchEffect();
				return;
			}
			else cDir *= -1;

			this->randomColor();

			if (this->limit == 0)	  this->cPos = 0;
			else if (this->limit >= this->nbLeds) this->cPos = this->nbLeds;
		}
	}

	void Comet::blink()
	{
		/*
		limit: nb frame before blink (--L0)
		cPos: nb remaining blinks (--L0)
		cSize: base nb of limit (const)
		cDir: bool < 0: light (!=<0)
		*/

		if (this->limit == 0)
		{
			if (this->cPos == 0)
			{
				switchEffect();
				return;
			}
			else
			{
				this->cPos--;
				this->limit = this->cSize;
				this->cDir *= -1;
			}
		}
		
		if (this->cDir < 0)
		{
			for (int i = 0; i < this->nbLeds; ++i)
			{
				this->p_controller->setColor(i, bytes.color);
			}
		}
		this->limit--;

	}

	void Comet::vanish()
	{
		if (this->limit == 0)
		{
			this->switchEffect();
			return;
		}

		for (int i = 0; i < this->limit; ++i)
			this->p_controller->setColor(i, bytes.color);

		this->limit--;
	}

	void Comet::switchEffect()
	{
		switch (this->step)
		{
		case(Step::COMET):
			this->cSize = 5; // Base Frame before blink
			this->limit = this->cSize; // Frames before blink
			this->cPos = 10; // Nb Blinks

			this->cDir = 1; // 1: blank | -1: colored

			this->step = Step::BLINK;
			break;

		case(Step::BLINK):
			this->limit = this->nbLeds; // limit decremented

			this->step = Step::VANISH;
			break;

		case(Step::VANISH):
			this->limit = 0; // nb leds on comet tail
			this->cPos = 0; // pos of comet head
			this->cDir = 1; // direction (1: counter, -1: clock)
			this->cSize = 1; // comet tail size

			this->randomColor();

			this->step = Step::COMET;
			break;
		}
	}

	void Comet::randomColor()
	{
		this->cColor = Color().randomColor();
		this->cColor.coef(1.0f, 0.42f, 0.3f);
		this->bytes = this->cColor.toBytes();
	}

}