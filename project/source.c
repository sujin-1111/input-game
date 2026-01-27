#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define TOTAL 20   // 총 상자 개수
#define VISIBLE 6  // 화면에 보이는 상자 개수

// 커서 이동
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 색 설정
void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 박스 모델
int box[5][8] =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1}
};

// 박스 출력
void drawBox(int x, int y, int color)
{
	setColor(color);

	for (int i = 0; i < 5; i++) {
		gotoxy(x, y + i);

		for (int j = 0; j < 8; j++) {
			printf("■");
		}
	}

	setColor(7);
}

// 박스 없애기
void clearBox(int x, int y)
{
	for (int i = 0; i < 5; i++) {
		gotoxy(x, y + i);
		printf("                ");
	}
}

// 반향키 입력
int getDirection()
{
	int ch = _getch();
	if (ch == 224) ch = _getch();

	if (ch == 75) return 0; // 왼쪽
	if (ch == 77) return 1; // 오른쪽
	if (ch == 72) return 2; // 위

	return -1;
}

// 랜덤 상자 생성
void makeBox(int* answer, int* color)
{
	*answer = rand() % 3;

	if (*answer == 0) *color = 11;  // 하늘
	if (*answer == 1) *color = 13;  // 보라
	if (*answer == 2) *color = 14;  // 노랑
}
int main()
{
	setlocale(LC_ALL, "");
	srand((unsigned)time(NULL));
	system("cls");

	int startX = 10;
	int startY = 5;

	int answers[VISIBLE];  //  상자 정답 반향
	int colors[VISIBLE];   //  상자 색

	int cleared = 0;  // 지금까지 깬 개수

	// 상자 6개 생성
	for (int i = 0; i < VISIBLE; i++) 
	{
		makeBox(&answers[i], &colors[i]);
		drawBox(startX, startY + i * 6, colors[i]);
	}

	// 게임 루프
	while (cleared < TOTAL)
	{
		int input = getDirection();
		int bottomY = startY + (VISIBLE - 1) * 6;

		// 판정
		if (input == answers[VISIBLE - 1])
		{
			drawBox(startX, bottomY, 10);   // 초록
		}
		else
		{
			drawBox(startX, bottomY, 12);   // 빨강
		}
		
		Sleep(200);
		clearBox(startX, bottomY);

		// 배열 이동 (색유지)
		for (int i = VISIBLE - 1; i > 0; i--)
		{
			answers[i] = answers[i - 1];
			colors[i] = colors[i - 1];
		}

		// 새 상자 생성
		makeBox(&answers[0], &colors[0]);

		// 화면 다시
		for (int i = 0; i < VISIBLE; i++)
		{
			clearBox(startX, startY + i * 6);
		}

		for (int i = 0; i < VISIBLE; i++)
		{
			drawBox(startX, startY + i * 6, colors[i]);
		}

		cleared++;
	}
	
	// 클리어
	gotoxy(0, startY + 40);
	printf("you win!!");
	_getch();
	return 0;
}