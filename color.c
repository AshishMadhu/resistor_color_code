#include <stdio.h>
#include <windows.h>

enum colors {
	BLUE_1 = 1,
	BLACK = 240,
	BROWN = 192,
	RED = 64,
	ORANGE = 108,
	YELLOW = 96,
	GREEN = 32,
	BLUE = 16,
	VIOLET = 208,
	GREY = 143,
	WHITE = 112,
	GOLD = 224,
	SILVER = 8
};

void reset(HANDLE *hConsole, WORD reset_value) {
	SetConsoleTextAttribute(*hConsole, reset_value);
}

void set_console_color(HANDLE *hConsole, int color, char text[50], WORD reset_value) {
	SetConsoleTextAttribute(*hConsole, color);
	printf("%s", text);
	reset(hConsole, reset_value);	
}


void color(char text[50], enum colors c) {

	WORD currentConsoleAttr;
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO   csbi;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if(GetConsoleScreenBufferInfo(hConsole, &csbi))
		currentConsoleAttr = csbi.wAttributes;


	set_console_color(&hConsole, c, text, currentConsoleAttr);
}
