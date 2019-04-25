#pragma once

#define _cast(T, o) ((T*)o)

#define PTR_NONULL -1;
#define PTR_FULL -2;

namespace Asemco
{
	class ptrArray
	{
	private:
		void** pointerList;
		size_t nbPointers;
		size_t maxPointers;

	public:
		ptrArray(size_t maxSize);
		~ptrArray();

		int append(void* ptr);
		void remove(size_t idx);

		size_t size();
		void* operator[](size_t idx);
	};
}