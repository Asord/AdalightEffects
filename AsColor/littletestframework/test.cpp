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
#include "StdAfx.h"
#include "test.h"

/*!
 * \brief
 * La couleur par défaut du texte.
 */
const WORD g_wDefaultColor = GetDefaultColor();

const char* colored(const char* text, WORD color)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
  return text;
}

WORD GetDefaultColor()
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.wAttributes;
}
