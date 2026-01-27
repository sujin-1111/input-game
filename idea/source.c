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

int main()
{
	// int key;
	// 
	// while (1)
	// {
	// 	key = _getch();
	// 
	// 	switch (key)
	// 	{
	// 	case 75:
	// 		printf("←");
	// 		break;
	// 
	// 	case 80:
	// 		printf("↓");
	// 		break;
	// 
	// 	case 77:
	// 		printf("→");
	// 		break;
	// 
	// 	case 72:
	// 		printf("↑");
	// 		break;
	// 
	// 	default:
	// 		break;
	// 	}
	// }
	// 

}
