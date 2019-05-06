#ifdef _DEVELOPPEMENT
#define _ALLPUBLIC

#include "littletestframework/test.h"
#include "AsColors.h"

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace Asemco;

Color colors[] = {
	Color::Black, // 0
	Color::White, // 1
	Color::Red, // 2
	Color::Green, // 3
	Color::Blue, // 4
	Color::Yellow, // 5
	Color::Cyan, // 6
	Color::Magenta // 7
};


bool testRGB(Color color, UINT8 red, UINT8 gre, UINT8 blu)
{
	return color._red == red && color._green == gre && color._blue == blu;
}

bool testCol(Color color, UINT val)
{
	return color._color == val;
}

template<typename T>
bool cmpArr4(T* arr1, T* arr2)
{
	return 
		arr1[0] == arr2[0] &&
		arr1[1] == arr2[1] &&
		arr1[2] == arr2[2] &&
		arr1[3] == arr2[3];
}

template<typename T>
bool cmpArr3(T* arr1, T* arr2)
{
	return
		arr1[0] == arr2[0] &&
		arr1[1] == arr2[1] &&
		arr1[2] == arr2[2];
}

bool isInDom(Color col)
{
	bool r = col._red >= 0 && col._red <= 255;
	bool g = col._green >= 0 && col._green <= 255;
	bool b = col._blue >= 0 && col._blue <= 255;
	return r && g && b;
}

bool isInDomDeg(Color col, FLOAT min, FLOAT max)
{
	FLOAT HSV[3];
	col.toHSV(HSV);
	return HSV[0] > min && HSV[0] < max;
}

int main()
{
	BEGIN_TESTS
	SetConsoleOutputCP(65001);

	{
		NOTICE("Tests des constructeurs\n\n");

		TEST_IMP(Color);
		CONSTRUCT_VERIF_IMP(Color, white);

		CONSTRUCT_VERIF_IMP(Color, col(255, 0, 0));
		TEST("constructeur avec args 3*UINT8", testRGB(col, 255, 0, 0), true);

		CONSTRUCT_VERIF_IMP(Color, col2(0xff00ff00));
		TEST("constructeur avec arg 1*UINT", testCol(col2, 0xff00ff00), true);

		UINT8 tmparr[] = { 0, 0, 255, 255};
		CONSTRUCT_VERIF_IMP(Color, col3(tmparr));
		TEST("constructeur avec 1*UINT8_arr", testRGB(col3, 0, 0, 255), true);
	}
	{
		NOTICE("\nTest get/set\n\n");

		UINT8 g_arrN[] = { 255, 128, 64, 255 };

		UINT8 g_arr[] = { 0, 0, 0, 0 };
		UINT8 s_arr[] = { 32, 16, 8, 0};

		CONSTRUCT_VERIF_IMP(Color, col(255, 128, 64));


		VERIF_IMP_1(Color::get, col.get(g_arr));
		TEST("Test get(uint8_arr)", cmpArr4<UINT8>(g_arr, g_arrN), true);

		VERIF_IMP_1(Color::set, col.set(s_arr));
		TEST("TEST set(uint8_arr)", testRGB(col, 32, 16, 8), true);

		TEST("Test Color::toInt()", col.toInt() == 0x00081020, true);

		VERIF_IMP_1(Color::fromInt, col.fromInt(0xff00ff00));
		TEST("Test Color::fromInt(uint)", testCol(col, 0xff00ff00), true);
	}
	{
		NOTICE("\nTest HSV\n\n");

		CONSTRUCT_VERIF_IMP(Color, col(0, 0, 0));
		FLOAT f_arr[3];
		FLOAT t_arr[] = { 240.000000f, 0.000000000f, 0.498039216f };

		VERIF_IMP_1(Color::fromHue, col.fromHue(120.0f));
		TEST("Test FromHue", testRGB(col, 0, 255, 0), true);

		VERIF_IMP_1(Color::fromHSV, col.fromHSV(240.0f, 1.0f, 0.5f));
		TEST("Test fromHSV", testRGB(col, 0, 0, 127), true);

		VERIF_IMP_1(Color::toHSV, col.toHSV(f_arr));
		TEST("Test toHSV", cmpArr3<FLOAT>(f_arr, t_arr), true);
	}
	{
		NOTICE("\nTest initializers\n\n");
		CONSTRUCT_VERIF_IMP(Color, colG(0, 0, 0));
		CONSTRUCT_VERIF_IMP(Color, colG12(12, 12, 12));
		CONSTRUCT_VERIF_IMP(Color, colR(0, 0, 0));
		CONSTRUCT_VERIF_IMP(Color, colRC(0, 0, 0));
		CONSTRUCT_VERIF_IMP(Color, colB(255, 255, 255));
		CONSTRUCT_VERIF_IMP(Color, colW(0, 0, 0));

		VERIF_IMP_1(Color::black, colB.black());
		TEST("Test black", testCol(colB, 0xff000000), true);

		VERIF_IMP_1(Color::white, colW.white());
		TEST("test white()", testCol(colW, 0xffffffff), true);

		VERIF_IMP_1(Color::gray, colG12.gray(12));
		TEST("test gray(12)", testRGB(colG12, 12, 12, 12), true);

		VERIF_IMP_1(Color::random, colR.random());
		TEST("Test random()", isInDom(colR), true);

		NOTICE("TEST 5 FOIS:\n")
		for(int i = 0; i < 5; ++i)
		{
			VERIF_IMP_1(Color::ramdomColor, colRC.ramdomColor(50.0f, 150.0f));
			TEST("\tTest randomColor n " << i, isInDomDeg(colRC, 50.0f, 150.0f), true);
		}
	}
	{
		NOTICE("\nTest Coef\n\n");
		CONSTRUCT_VERIF_IMP(Color, col(255, 128, 64));


		VERIF_IMP_1(Color::coef, col.coef(0.25f, 0.5f, 1.0f));
		TEST("Test Coef(0.25f, 0.5f, 1.0f)", testRGB(col, 63, 64, 64), true);
	}
	{
		NOTICE("\nTest Operateurs\n\n");
		CONSTRUCT_VERIF_IMP(Color, col(255, 0, 0));
		CONSTRUCT_VERIF_IMP(Color, col2(0, 255, 0));

		Color col3;
		Color* colptr = new Color(255, 255, 255); // destructor

		#pragma warning( push )
		#pragma warning( disable : 4805) // BOOL is integer, Warn4805: risky operation between int & bool in equality
		TEST_VERIF_IMP_1(Color::operator==, "Vérification de l'égalité entre col et col2", col == col2, false);
		TEST_VERIF_IMP_1(Color::operator==, "Vérification de l'égalité entre col et red", col == colors[2], true);

		TEST_VERIF_IMP_1(Color::operator==, "Vérification de l'inégalité entre col et col2", col != col2, true);
		TEST_VERIF_IMP_1(Color::operator==, "Vérification de l'inégalité entre col et red", col != colors[2], false);

		VERIF_IMP_1(Color::operator+, col3 = col + col2);
		TEST_VERIF_IMP_1(Color::operator+, "Vérification de l'addition entre col et col2", col3 == Color(255, 255, 0), true);

		VERIF_IMP_1(Color::operator+=, col += col2);
		TEST_VERIF_IMP_1(Color::operator+=, "Vérification de l'addition assignation  col += col2", col == Color(255, 255, 0), true);

		VERIF_IMP_1(Color::operator-, col3 = col - col2);
		TEST_VERIF_IMP_1(Color::operator-, "Vérification de la soustraction entre col et col2", col3 == Color(255, 0, 0), true);

		VERIF_IMP_1(Color::operator-=, col3 -= col);
		TEST_VERIF_IMP_1(Color::operator-=, "Vérification de la soustraction assignation col3 -= col", col3 == Color(0, 0, 0), true);

		VERIF_IMP_1(Color::operator*, col3 = col * 0.5f);
		TEST_VERIF_IMP_1(Color::operator*, "Vérification de la multiplication  col * 0.5f", col3 == Color(127, 127, 0), true);

		VERIF_IMP_1(Color::operator*=, col3 *= 2.0f);
		TEST_VERIF_IMP_1(Color::operator*=, "Vérification de la multiplication assignation col3 *= 2.0f", col3 == Color(254, 254, 0), true);

		VERIF_IMP_1(Color::operator/, col3 = col / 2.0f);
		TEST_VERIF_IMP_1(Color::operator/, "Vérification de la division col / 2.0f", col3 == Color(127, 127, 0), true);

		VERIF_IMP_1(Color::operator/=, col3 /= 0.5f);
		TEST_VERIF_IMP_1(Color::operator/=, "Vérification de la division assignation col3 /= 0.5f", col3 == Color(254, 254, 0), true);

		VERIF_IMP_1(Color::operator++, ++col3);
		TEST_VERIF_IMP_1(Color::operator/=, "Vérification de l'incrémentation de col3", col3 == Color(255, 255, 1), true);

		VERIF_IMP_1(Color::operator--, --col3);
		TEST_VERIF_IMP_1(Color::operator/=, "Vérification de la décrémentation de col3", col3 == Color(254, 254, 0), true);
		#pragma warning( pop ) 

		DELETE_VERIF_IMP(colptr);
	}

	END_TESTS
	system("pause");
	return 0;
}
#endif
