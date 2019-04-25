#pragma once

#define _cast(T, o) ((T*)o)

#define PTR_NONULL -1;
#define PTR_FULL -2;

namespace Asemco
{
	class ptrArray
	{
	private:
		void** lst;
		size_t cnt;
		size_t max;

	public:
		ptrArray(size_t);
		~ptrArray();

		int append(void*);
		void remove(size_t);

		size_t size();
		void* operator[](size_t);
	};
}