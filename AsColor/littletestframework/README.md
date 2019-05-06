# LittleTestFramework

## What is it?

It's a very simple unit test framework for C++ under Visual Studio.

## How to install

Simply copy `test.h` and `test.cpp` to your source code. Include `test.h` to use it.

*Note:* These files are encoded using Unicode. To have correct french output in Windows' console, you must set it in Unicode output. This is done by Calling `SetConsoleOutputCP(65001);` at program start. `SetConsoleOutputCP` is declared in `<Windows.h>`.

## License

LittleTestFramework is released Under GNU GPL v3 license.
