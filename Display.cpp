#include "Display.h"

void Display::clearScreen()
{
	COORD top_left = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;
	GetConsoleScreenBufferInfo(console, &screen);

	FillConsoleOutputCharacterA(
		console, ' ',
		screen.dwSize.X * screen.dwSize.Y,
		top_left,
		&written
	);

	SetConsoleCursorPosition(console, top_left);
}
