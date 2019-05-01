#ifdef _DEVELOPPEMENT
#include "AsColors.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

using namespace Asemco;
	Color colors[] = {
		Color::Black,
		Color::White,
		Color::Red,
		Color::Green,
		Color::Blue,
		Color::Yellow,
		Color::Cyan,
		Color::Magenta
	};


int main(void)
{
	//colors[i % 8].coef(1.0f, 0.5f, 0.25f);
	unsigned char precomputed_g[256];
	unsigned char precomputed_b[256];

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (size_t k = 0; k < 10000; ++k)
	{
		for (UINT8 i = 0; i < 8; ++i)
		{
			colors[i].coef(1.0f, 0.42f, 0.3f);
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << duration;
	


	return 0;
}
#endif
