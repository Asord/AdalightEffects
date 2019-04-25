#include "ptrArray.h"

namespace Asemco
{

	ptrArray::ptrArray(size_t maxSize)
	{
		this->pointerList = new void*[maxSize];

		for (size_t i = 0; i < maxSize; ++i)
			this->pointerList[i] = nullptr;

		this->maxPointers = maxSize;
	}

	ptrArray::~ptrArray()
	{
		for (size_t i = 0; i < this->nbPointers; ++i)
		{
			delete this->pointerList[i];
			this->pointerList[i] = nullptr;
		}

		delete[] this->pointerList;
	}

	int ptrArray::append(void * ptr)
	{
		if (this->nbPointers < this->maxPointers)
		{
			if (this->pointerList[this->nbPointers] == nullptr)
			{
				this->pointerList[this->nbPointers] = ptr;
				this->nbPointers += 1;

				return this->nbPointers - 1;
			}
			return PTR_NONULL;
		}
		return PTR_FULL;
	}


	void ptrArray::remove(size_t idx)
	{
		if (idx < this->nbPointers)
		{
			delete this->pointerList[idx];

			this->nbPointers -= 1;
			if (this->nbPointers > 0)
				this->pointerList[idx] = this->pointerList[this->nbPointers];

			this->pointerList[this->nbPointers] = nullptr;

		}

		if (this->nbPointers == 1)
			int a = 0;
	}

	size_t ptrArray::size()
	{
		return this->nbPointers;
	}

	void* ptrArray::operator[](size_t idx)
	{
		if (idx < this->nbPointers)
			return this->pointerList[idx];

		return nullptr;
	}
}