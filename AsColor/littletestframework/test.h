//Copyright 2010-2019 Benjamin ALBOUY-KISSI
/*
    This file is part of LittleTestFramework.

    LittleTestFramework is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    LittleTestFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LittleTestFramework. If not, see <http://www.gnu.org/licenses/>.
*/
/*!
 * \file  "Test.h"
 *
 * \brief Déclaration des fonctions du framework de test. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2015
 * \version 1.1
 */
#pragma once

/*!
 * \if TestHelp
 * \mainpage
 * \tableofcontents
 * \section secTitre Utilisation
 * 
\code{.cpp}
#include "test.h"
void main()
{
  BEGIN_TESTS
    int a = 2;
    int b = 3;
    NOTICE("Début des tests"<<std::endl<<std::endl);
    TEST("Vérification de la valeur de a", a, 2);
    TEST("Vérification de l'inégalité entre a et b", a==b, false);
    TEST("Ce test doit échouer", a==b, true);
  END_TESTS
}
\endcode
 * \see BEGIN_TESTS | NOTICE | TEST | END_TESTS
 * 
 * \section secAutre Utilisation avancée
 * D'autres macros sont définies pour permettre d'écrire des tests qui compilent et s'exécutent (en échouant) même si la classe ou la fonction testée n'est pas encore implémentée :
 *
 * \subsection secConstr Conctruction d'objet
 * La macro \ref CONSTRUCT_VERIF_IMP permet de créer des objets. Si les classes des objets ne sont pas encore définie, alors le test échoue. Exemple :
 *
\code{.cpp}
  CONSTRUCT_VERIF_IMP(CMaClasse, monObjet); // <=> CMaClasse monObjet;
  CONSTRUCT_VERIF_IMP(CMaClasse, monObjet(param1)); // <=> CMaClasse monObjet(param1);
  CONSTRUCT_VERIF_IMP(CMaClasse, *pMonObjet = new CMaClasse(param1)); // <=> CMaClasse *pMonObjet = new CMaClasse(param1);
\endcode
 * 
 * \subsection secImp Vérification d'implémentation
 * La macro \ref TEST_IMP permet de tester si un symbole est implémenté. Le symbole pet être une classe, une fonction, une variable globale, etc... Exemple :
 * 
\code{.cpp}
  TEST_IMP(CMaClasse); 
  TEST_IMP(CMaClasse::MonMembre);
  TEST_IMP(MaFonction);
\endcode
 *
 * \subsection secTestImp Tests avec vérification d'implémentation
 * Les macros \ref TEST_VERIF_IMP_1 à \ref TEST_VERIF_IMP_3 permettent de réaliser un test si un à troi symbole sont effectivement implémentés.
 *
\code{.cpp}
  CONSTRUCT_VERIF_IMP(CMaClasse, monObjet); // <=> CMaClasse monObjet;
  TEST_VERIF_IMP_1(CMaClasse::GetX, "Vérification de la valeur de x", monObjet.GetX(), 0);
  TEST_VERIF_IMP_2(CMaClasse::GetAlpha, CMaClasse::GetBeta, "Vérification de la valeur de (alpha, beta)", monObjet.GetAplha()==0 && monObjet.GetBeta()==0, true);
\endcode
 * \endif
 */

#include <iostream>
#include <Windows.h>

//Macro d'aides pour ce fichier
#define HELP_VERIF_IMP(symbole) \
  __if_not_exists(symbole) { \
    nNbFailedTests++; \
    std::cout<<"Test ligne "<<__LINE__<<" : "; \
    std::cout<<colored("Echec - Le symbole \"" #symbole "\" n'est pas implémenté.", FOREGROUND_RED | FOREGROUND_INTENSITY)<<std::endl; \
    colored("", g_wDefaultColor); \
  } \

/*!
 * \brief Affiche une notification au cours des tests
 * 
 * \param text
 * Texte à afficher dans la notification.
 * 
 * Affiche la notification "text" en cyan brillant dans la console à l'aide de l'objet \c cout. 
 *
 */
#define NOTICE(text) \
  colored("", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); \
  std::cout<<text; \
  colored("", g_wDefaultColor);

/*!
 * \brief Macro de vérification de prérequis d'implémentation
 *
 * \param symbole
 * Symbole dont l'implémentation est requise.
 *
 * \param operation
 * Opération à réaliser.
 *
 * Vérifie que le "symbole" soit implémenté puis, si oui, réalise l'opération demandée.
 *
 * \see BEGIN_TESTS | END_TESTS | TEST_IMP(symbole)
 */
#define VERIF_IMP_1(symbole, operation) \
  HELP_VERIF_IMP(symbole) \
  __if_exists(symbole){ operation; } \
  colored("", g_wDefaultColor);

/*!
 * \brief Macro de vérification de prérequis d'implémentation
 *
 * \param symbole1
 * Symbole dont l'implémentation est requise.
 *
 * \param symbole2
 * Symbole dont l'implémentation est requise.
 *
 * \param operation
 * Opération à réaliser.
 *
 * Vérifie que les "symbole1" et "symbole2" soient implémentés puis, si oui, réalise l'opération demandée.
 *
 * \see BEGIN_TESTS | END_TESTS | TEST_IMP(symbole)
 */
#define VERIF_IMP_2(symbole1, symbole2, operation) \
  HELP_VERIF_IMP(symbole1) \
  HELP_VERIF_IMP(symbole2) \
  __if_exists(symbole1){ \
    __if_exists(symbole2){ \
      operation; \
    } \
  } \
  colored("", g_wDefaultColor);

/*!
 * \brief Macro de vérification de prérequis d'implémentation
 *
 * \param symbole1
 * Symbole dont l'implémentation est requise.
 *
 * \param symbole2
 * Symbole dont l'implémentation est requise.
 *
 * \param symbole3
 * Symbole dont l'implémentation est requise.
 *
 * \param operation
 * Opération à réaliser.
 *
 * Vérifie que les "symbole1", "symbole2" et "symbole3" soient implémentés puis, si oui, réalise l'opération demandée.
 *
 * \see BEGIN_TESTS | END_TESTS | TEST_IMP(symbole)
 */
#define VERIF_IMP_3(symbole1, symbole2, symbole3, operation) \
  HELP_VERIF_IMP(symbole1) \
  HELP_VERIF_IMP(symbole2) \
  HELP_VERIF_IMP(symbole3) \
  __if_exists(symbole1){ \
    __if_exists(symbole2){ \
      __if_exists(symbole3){ \
        operation; \
      } \
    } \
  } \
  colored("", g_wDefaultColor);

/*!
 * \brief Macro de vérification d'implémentation d'un symbole
 * 
 * \param symbole
 * Symbole dont la présence doit être vérifiée.
 * 
 * Teste que le "symbole" est bien défini. En cas d'échec, incrémente la variable 
 * \c nNbFailedTests, en cas de succès, incrémente la variable \c nNbSucceededTests.
 *
 * \remark
 * Les variables \c nNbSucceededTests et \c nNbFailedTests sont déclarées et initialisées par la 
 * macro BEGIN_TESTS. La macro TEST ne peut être utilisée qu'entre les macros BEGIN_TESTS et 
 * END_TESTS.
 *
 * \see BEGIN_TESTS | END_TESTS | VERIF_IMP_1(symbole, operation)
 */
#define TEST_IMP(symbole) \
  std::cout<<"Test ligne "<<__LINE__<<" : "; \
  __if_exists(symbole) { std::cout<<(nNbSucceededTests++, colored("Ok", FOREGROUND_GREEN | FOREGROUND_INTENSITY)); } \
  __if_not_exists(symbole) { std::cout<<(nNbFailedTests++, colored("Echec", FOREGROUND_RED | FOREGROUND_INTENSITY)); } \
  std::cout<<colored(" : Vérification de l'implémentation du symbole " #symbole, g_wDefaultColor)<<std::endl; 

/*!
 * \brief Macro de test
 * 
 * \param text
 * Texte d'explication du test. Est affiché en début de ligne de test.
 * 
 * \param operation
 * Opération à tester.
 * 
 * \param resultat
 * Résultat attendu de l'opération.
 *
 * Teste que l'"operation" obtient bien le bon "resultat". En cas d'échec, incrémente la variable 
 * \c nNbFailedTests, en cas de succès, incrémente la variable \c nNbSucceededTests.
 *
 * \remark
 * Les variables \c nNbSucceededTests et \c nNbFailedTests sont déclarées et initialisées par la 
 * macro BEGIN_TESTS. La macro TEST ne peut être utilisée qu'entre les macros BEGIN_TESTS et 
 * END_TESTS.
 *
 * \see BEGIN_TESTS | END_TESTS
 */
#define TEST(text, operation, resultat) \
{\
  std::cout<<"Test ligne "<<__LINE__<<" : "; \
  std::cout<<(((operation) == resultat) ? (nNbSucceededTests++, colored("Ok", FOREGROUND_GREEN | FOREGROUND_INTENSITY)) : (nNbFailedTests++, colored("Echec", FOREGROUND_RED | FOREGROUND_INTENSITY))); \
  std::cout<<colored(" : ", g_wDefaultColor)<<text<<" : "<<"Teste que \"" #operation "\" soit égal à \"" #resultat "\""<<std::endl; \
}

/*!
 * \brief Macro de test avec vérification de prérequis d'implémentation
 * 
 * \param symbole1
 * Symbole dont l'implémentation est requise.
 * 
 * \param text
 * Texte d'explication du test. Est affiché en début de ligne de test.
 * 
 * \param operation
 * Opération à tester.
 * 
 * \param resultat
 * Résultat attendu de l'opération.
 *
 * Teste que le "symbole" est implémenté puis applique le test demandé à l'aide de la macro TEST(text, operation, resultat)
 *
 * \see BEGIN_TESTS | END_TESTS | TEST(text, operation, resultat)
 */
#define TEST_VERIF_IMP_1(symbole1, text, operation, resultat) \
{\
  HELP_VERIF_IMP(symbole1) \
  __if_exists(symbole1){ TEST(text,operation,resultat) } \
  colored("", g_wDefaultColor); \
}

/*!
 * \brief Macro de test avec vérification de prérequis d'implémentation
 * 
 * \param symbole1
 * Symbole dont l'implémentation est requise.
 * \param symbole2
 * Symbole dont l'implémentation est requise.
 * 
 * \param text
 * Texte d'explication du test. Est affiché en début de ligne de test.
 * 
 * \param operation
 * Opération à tester.
 * 
 * \param resultat
 * Résultat attendu de l'opération.
 *
 * Teste que les symboles sont implémentés puis applique le test demandé à l'aide de la macro TEST(text, operation, resultat)
 *
 * \see BEGIN_TESTS | END_TESTS | TEST(text, operation, resultat)
 */
#define TEST_VERIF_IMP_2(symbole1, symbole2, text, operation, resultat) \
{\
  HELP_VERIF_IMP(symbole1) \
  HELP_VERIF_IMP(symbole2) \
  __if_exists(symbole1){ \
    __if_exists(symbole2){ \
      TEST(text,operation,resultat) \
    } \
  } \
  colored("", g_wDefaultColor); \
}

/*!
 * \brief Macro de test avec vérification de prérequis d'implémentation
 * 
 * \param symbole1
 * Symbole dont l'implémentation est requise.
 * \param symbole2
 * Symbole dont l'implémentation est requise.
 * \param symbole3
 * Symbole dont l'implémentation est requise.
 * 
 * \param text
 * Texte d'explication du test. Est affiché en début de ligne de test.
 * 
 * \param operation
 * Opération à tester.
 * 
 * \param resultat
 * Résultat attendu de l'opération.
 *
 * Teste que les symboles sont implémentés puis applique le test demandé à l'aide de la macro TEST(text, operation, resultat)
 *
 * \see BEGIN_TESTS | END_TESTS | TEST(text, operation, resultat)
 */
#define TEST_VERIF_IMP_3(symbole1, symbole2, symbole3, text, operation, resultat) \
{\
  HELP_VERIF_IMP(symbole1) \
  HELP_VERIF_IMP(symbole2) \
  HELP_VERIF_IMP(symbole3) \
  __if_exists(symbole1){ \
    __if_exists(symbole2){ \
      __if_exists(symbole3){ \
        TEST(text,operation,resultat) \
      } \
    } \
  } \
  colored("", g_wDefaultColor); \
}

/*!
 * \brief Macro de construction d'objet avec vérification de prérequis d'implémentation
 *
 * \param classname
 * Nom de la classe à instancier.
 *
 * \param objname
 * Nom de l'objet instancié.
 *
 * Vérifie que la classe \c classname est implémentée puis l'instancie par l'objet \c objname.
 *
 * \see BEGIN_TESTS | END_TESTS | TEST(text, operation, resultat)
 */
#define CONSTRUCT_VERIF_IMP(classname, objname) \
  HELP_VERIF_IMP(classname) \
  __if_exists(classname) { classname objname ; }

/*!
 * \brief Macro de destruction d'objet pointé avec vérification de prérequis d'implémentation
 *
 * \param ptrname
 * Nom du pointeur à supprimer.
 *
 * Vérifie que la variable \c ptrname existe puis la détruit à l'aide de l'opérateur \c delete.
 *
 * \see BEGIN_TESTS | END_TESTS | TEST(text, operation, resultat)
 */
#define DELETE_VERIF_IMP(ptrname) \
  HELP_VERIF_IMP(ptrname) \
  __if_exists(ptrname) { delete ptrname ; }

/*!
 * \def BEGIN_TESTS
 * \brief Démarrage des tests
 * 
 * Doit être utilisée avant de commencer les tests à l'aide de la macro \c TEST .
 *
 * \see TEST | END_TESTS
 */
#ifdef _DEBUG
#define BEGIN_TESTS \
  { \
    _CrtMemState mem1, mem2, memdiff; \
    _CrtMemCheckpoint(&mem1); \
    { \
      int nNbFailedTests = 0; \
      int nNbSucceededTests = 0; \
      try {
#else
#define BEGIN_TESTS \
  { \
    int nNbFailedTests = 0; \
    int nNbSucceededTests = 0; \
    try { 
#endif //def _DEBUG

/*!
 * \def END_TESTS
 * \brief Termine les tests
 * 
 * Doit être utilisée à la fin de la liste de tests. La macro affiche un récapitulatif sur le nombre de tests effectués et le nombre de tests échoués.
 *
 * \remark 
 * En mode DEBUG, cette macro vérifie qu'il n'y a pas eu de fuites mémoire depuis l'utilisation de BEGIN_TESTS. 
 *
 * \see TEST | BEGIN_TESTS
 */
#ifdef _DEBUG
#define END_TESTS \
      } catch(...) { \
        nNbFailedTests++; \
        std::cout<<std::endl<<colored("Une exception non gérée a été rencontrée", FOREGROUND_RED | FOREGROUND_INTENSITY)<<std::endl; \
        colored("", g_wDefaultColor); \
      } \
      std::cout<<std::endl; \
      std::cout<<"Nombre de tests réalisés : "<<nNbSucceededTests+nNbFailedTests<<std::endl; \
      std::cout<<colored("Nombre de tests échoués : ", (nNbFailedTests > 0 ? FOREGROUND_RED | FOREGROUND_INTENSITY : FOREGROUND_GREEN | FOREGROUND_INTENSITY))<<nNbFailedTests<<std::endl; \
    } \
    _CrtMemCheckpoint(&mem2); \
    if(_CrtMemDifference(&memdiff, &mem1, &mem2)) \
    { \
      _CrtMemDumpAllObjectsSince(&mem1); \
      std::cout<<colored("Des fuites mémoires ont été détectées, vérifiez vos allocations et désallocations !", \
        FOREGROUND_RED | FOREGROUND_INTENSITY)<<std::endl; \
    } \
    else \
      std::cout<<colored("Aucune fuite mémoire détectée.", FOREGROUND_GREEN | FOREGROUND_INTENSITY)<<std::endl; \
    colored("", g_wDefaultColor); \
  }
#else
#define END_TESTS \
    } catch(...) { \
      nNbFailedTests++; \
      std::cout<<std::endl<<colored("Une exception non gérée a été rencontrée", FOREGROUND_RED | FOREGROUND_INTENSITY)<<std::endl; \
      colored("", g_wDefaultColor); \
    } \
    std::cout<<std::endl; \
    std::cout<<"Nombre de tests réalisés : "<<nNbSucceededTests+nNbFailedTests<<std::endl; \
    std::cout<<colored("Nombre de tests échoués : ", (nNbFailedTests > 0 ? FOREGROUND_RED | FOREGROUND_INTENSITY : FOREGROUND_GREEN | FOREGROUND_INTENSITY))<<nNbFailedTests<<std::endl; \
  } \
  std::cout<<colored("Détection des fuites mémoires impossible en mode Release.", FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)<<std::endl; \
  colored("", g_wDefaultColor);
#endif //def _DEBUG

/*!
 * \brief
 * Définit la couleur du texte de la console.
 * 
 * \param text
 * Texte à colorer.
 * 
 * \param color
 * Couleur du texte.
 * 
 * \returns
 * Write description of return value here.
 * 
 * Définit la couleur du texte de la console à l'aide du paramètre \c color. 
 * Le paramètre \c text est directement retourné.
 * 
 * \remarks
 * Le paramètre \c text est ignoré par la fonction et est directement retourné.
 * 
 */
const char* colored(const char* text, WORD color);

/*!
 * \brief
 * Récupère la couleur du texte de la console.
 * 
 * \returns
 * La couleur du texte de la console.
 * 
 */
WORD GetDefaultColor();

/*!
 * \brief
 * La couleur par défaut du texte.
 */
extern const WORD g_wDefaultColor;

