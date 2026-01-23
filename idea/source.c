#include <stdio.h>
#include <conio.h>
#include <windows.h>


void SetConsole()
{
	system("input game"); // 콘솔창 이름 설정
	system("mode con:cols=60 lines=100"); // 콘솔창 크기 설정

	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}
