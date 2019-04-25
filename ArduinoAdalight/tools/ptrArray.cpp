#include "ptrArray.h"

namespace Asemco
{

	ptrArray::ptrArray(size_t max)
	{
		this->lst = new void*[max];

		for (size_t i = 0; i < max; ++i)
			this->lst[i] = nullptr;

		this->max = max;
	}

	ptrArray::~ptrArray()
	{
		for (size_t i = 0; i < this->cnt; ++i)
		{
			delete this->lst[i];
			this->lst[i] = nullptr;
		}

		delete[] this->lst;
	}

	int ptrArray::append(void * ptr)
	{
		if (this->cnt < this->max)
		{
			if (this->lst[this->cnt] == nullptr)
			{
				this->lst[this->cnt] = ptr;
				this->cnt += 1;

				return this->cnt - 1;
			}
			return PTR_NONULL;
		}
		return PTR_FULL;
	}


	void ptrArray::remove(size_t idx)
	{
		if (idx < this->cnt)
		{
			delete this->lst[idx];

			this->cnt -= 1;
			if (this->cnt > 0)
				this->lst[idx] = this->lst[this->cnt];

			this->lst[this->cnt] = nullptr;

		}

		if (this->cnt == 1)
			int a = 0;
	}

	size_t ptrArray::size()
	{
		return this->cnt;
	}

	void* ptrArray::operator[](size_t idx)
	{
		if (idx < this->cnt)
			return this->lst[idx];

		return nullptr;
	}
}