#ifdef _DEVELOPPEMENT
#define _ALLPUBLIC

#define COMPORT "COM4"

#define _fPORT "\\\\.\\" COMPORT // DO NOT EDIT

#include <iostream>
#include <chrono>

#include "littletestframework/test.h"
#include "AdalightController.h"


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

bool testRGB_arr(PUINT8 arr, UINT8 red, UINT8 gre, UINT8 blu)
{
	return arr[0] == red && arr[1] == gre && arr[2] == blu;
}

bool testRGB(Color color, UINT8 red, UINT8 gre, UINT8 blu)
{
	return color._red == red && color._green == gre && color._blue == blu;
}

bool testCol(Color color, UINT val)
{
	return color._color == val;
}

template<typename T>
bool cmpArr(T* arr1, T* arr2, UINT8 size)
{
	bool result = true;
	for (UINT8 i = 0; i < size; ++i)
		result &= (arr1[i] == arr2[i]);

	return result;
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

char userInput()
{
	char BUFFER[250];
	do { cin >> BUFFER; } while (BUFFER[0] != 'y' && BUFFER[0] != 'n');
	return BUFFER[0];
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
		TEST("Test get(uint8_arr)", cmpArr<UINT8>(g_arr, g_arrN, 4), true);

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
		TEST("Test toHSV", cmpArr<FLOAT>(f_arr, t_arr, 3), true);
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
	cout << "Attention: les tests suivants nécessitent que vous ayez bien connecter votre ordinateur à un système Adalight (Arduino+leds)";
	cout << "Le port utilisé sera le " << COMPORT << ". Pensez a vérifier votre configuration en cas d'échecs... Voir: #define COMPORT";
	{

		NOTICE("\nTest AdalightBase constructeurs\n\n");
		#pragma warning( push )
		#pragma warning( disable : 4838) // int to UINT warning in tab initialization
		{
			NOTICE("\nLes tests 4 tests suivants vont avoir besoins d'un petit temps avant de démarer, relatif à l'ouverture d'un socket\n\n");
			UINT8 base5Header[] = 
			{
				'A', 'd', 'a',
				(4) >> 8,
				(4) & 0xff,
				base5Header[3] ^ base5Header[4] ^ 0x55
			};

			CONSTRUCT_VERIF_IMP(AdalightController, base5(_fPORT, 5));
			TEST("Test nbLeds pour base5", base5.getNbLeds() == 5, true);
			TEST("Test header pour base5", cmpArr(base5.y_buffer, base5Header, 6), true);
			TEST("Test header pour base5", base5.serial.isConnected(), true);
		}
		{
			UINT8 basedHeader[] = 
			{
				'A', 'd', 'a',
				(NBLEDS - 1) >> 8,
				(NBLEDS - 1) & 0xff,
				basedHeader[3] ^ basedHeader[4] ^ 0x55
			};

			CONSTRUCT_VERIF_IMP(AdalightController, based(_fPORT));
			TEST("Test nbLeds pour based", based.getNbLeds() == NBLEDS, true);
			TEST("Test header pour based", cmpArr(based.y_buffer, basedHeader, 6), true);
			TEST("Test serial bien connecté", based.serial.isConnected(), true);


			CONSTRUCT_VERIF_IMP(AdalightController, basenc(_fPORT));
			TEST("Test serial non connecté si déjà utilisé", basenc.serial.isConnected(), false);

		}
		#pragma warning( pop ) 

		NOTICE("\nTest AdalightBase getColor, setColor, moderate\n\n");
		{
			UINT8 arr[] = { 0xff, 0x00, 0x00 };
			UINT8 arr_col[] = { 0xff, 0x80, 0x40 };

			CONSTRUCT_VERIF_IMP(Color, col(255, 128, 64));
			CONSTRUCT_VERIF_IMP(AdalightController, base5(_fPORT, 5));

			VERIF_IMP_1(AdalightController::setColorA, base5.setColorA(0, arr));
			TEST_VERIF_IMP_1(AdalightController::setColorA, "Vérification de AdalightBase::setColorA", cmpArr(&base5.y_buffer[6], arr, 3), true);

			VERIF_IMP_1(AdalightController::setColorC, base5.setColorC(1, col));
			TEST_VERIF_IMP_1(AdalightController::setColorC, "Vérification de AdalightBase::setColorC", cmpArr(&base5.y_buffer[6+3], arr_col, 3), true);

			VERIF_IMP_1(AdalightController::getColorA, base5.getColorA(1, arr));
			TEST_VERIF_IMP_1(AdalightController::setColorA, "Vérification de AdalightBase::getColorA", testRGB_arr(arr, 255, 128, 64), true);

			VERIF_IMP_1(AdalightController::getColorC, base5.getColorC(0, col));
			TEST_VERIF_IMP_1(AdalightController::setColorC, "Vérification de AdalightBase::getColorC", testRGB(col, 255, 0, 0), true);
			// HH EE AA DD EE RR ff 00 00 ff 80 40 00 00 00 [...]

			UINT8 arr_mod[] = { 0x3f, 0x0, 0x0, 0x3f, 0x40, 0x40 };
			VERIF_IMP_1(AdalightController::moderate, base5.moderate(0.25f, 0.5f, 1.0f));
			TEST_VERIF_IMP_1(AdalightController::moderate, "Vérification de AdalightBase::moderate", cmpArr(&base5.y_buffer[6], arr_mod, 6), true);
		}
		{
			NOTICE("\nTest AdalightBase rendu visuel\n\n");
			NOTICE("\nLes tests suivants sont relatifs au rendu visuel... Vous devez confirmer manuellement le résultat...\n");
			NOTICE("Pour confirmer le résultat du test, entrez 'y', pour l'infirmer entrez 'n'.\n");
			
			
			CONSTRUCT_VERIF_IMP(AdalightController, base(_fPORT));

			Color RGB[] = { Color::Red, Color::Green, Color::Blue };
			Color YCM[] = { Color::Yellow, Color::Cyan, Color::Magenta };
			Color WBG[] = { Color::White, Color::Black, Color().gray(80) };
			UINT tier = NBLEDS / 3;

			for(int x = 0; x < 3; ++x) 
				for (int i = 0; i < tier; ++i)
					base.setColorC(x*tier + i, RGB[x]);

			base.moderate(1.0f, 0.42f, 0.3f);
			base.send();

			TEST_VERIF_IMP_1(AdalightController::send, "Vérification de AdalightBase::send avec couleurs Red, Green, Blue (1/3)", userInput() == 'y', true);
			
			for (int x = 0; x < 3; ++x)
				for (int i = 0; i < tier; ++i)
					base.setColorC(x*tier + i, YCM[x]);

			base.moderate(1.0f, 0.42f, 0.3f);
			base.send();
			
			TEST_VERIF_IMP_1(AdalightController::send, "Vérification de AdalightBase::send avec couleurs Yellow, Cyan, Magenta (2/3)", userInput() == 'y', true);


			for (int x = 0; x < 3; ++x)
				for (int i = 0; i < tier; ++i)
					base.setColorC(x*tier + i, WBG[x]);

			base.moderate(1.0f, 0.42f, 0.3f);
			base.send();

			TEST_VERIF_IMP_1(AdalightController::send, "Vérification de AdalightBase::send avec couleurs White, Black, Gray(50%) (3/3)", userInput() == 'y', true);
		}
		TEST_VERIF_IMP_1(AdalightController::~AdalightController, "Vérification que le destructeur efface les couleurs", userInput() == 'y', true);
	}

	END_TESTS
	system("pause");
	return 0;
}
#endif
