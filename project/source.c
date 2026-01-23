#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main()
{

	int key;

	while (1)
	{
		key = _getch();

		switch (key)
		{
		case 75:
			printf("ก็");
			break;

		case 80:
			printf("ก้");
			break;

		case 77:
			printf("กๆ");
			break;

		case 72:
			printf("ก่");
			break;

		default:
			break;
		}
	}




}