#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define VISIBLE 6  // 화면에 보이는 상자 개수

#define BOX_W 8
#define BOX_H 5
#define BOX_GAP 6

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

	for (int i = 0; i < BOX_H; i++) {
		gotoxy(x, y + i);

		for (int j = 0; j < BOX_W; j++) {
			if (box[i][j] == 1)
				printf("■");
			else printf(" ");
		}
	}

	setColor(7);
}

// 박스 없애기
void clearBox(int x, int y)
{
	for (int i = 0; i < BOX_H; i++) {
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

// 점수 출력
void drawScore(int score)
{
	gotoxy(2, 2);
	setColor(7);
	printf("score : %d ", score);
}

// 목숨 출력
void drawLife(int life)
{
	gotoxy(2, 3);
	printf("Life : ");
	for (int i = 0; i < life; i++) printf("♥");
	printf("  ");
}

// 분류 기준 표시
void drawRule(int startX, int bottomY)
{
	int ruleX = startX - 1;
	int ruleY = bottomY + BOX_H + 3;

	gotoxy(ruleX, ruleY);
	setColor(11); printf("← 파랑  ");
	setColor(13); printf("→ 보라  ");
	setColor(14); printf("↑ 노랑  ");
	setColor(7);
}

// GAME OVER 화면
void drawGameOver(int centerX, int centerY, int score)
{
	system("cls");

	setColor(12);
	gotoxy(centerX - 9, centerY - 1);
	printf("GAME OVER");

	setColor(7);
	gotoxy(centerX - 9, centerY + 1);
	printf("SCORE : %d", score);

}

int main()
{
	setlocale(LC_ALL, "");
	srand((unsigned)time(NULL));
	system("cls");

// 기준선 방식
	int centerX = 40;
	int centerY = 20;

	int startX = centerX - (BOX_W / 2);

	int answers[VISIBLE];
	int colors[VISIBLE];

	int score = 0;
	int life = 3;

	// 상자 6개 생성
	for (int i = 0; i < VISIBLE; i++) 
	{
		makeBox(&answers[i], &colors[i]);
	}

	// 게임 루프
	while (1)
	{
		for (int i = 0; i < VISIBLE; i++)
		{
			int y = centerY - (VISIBLE / 2 - i) * BOX_GAP;
			drawBox(startX, y, colors[i]);
		}

		drawScore(score);
		drawLife(life);

		

		int bottomIndex = VISIBLE - 1;
		int bottomY = centerY - (VISIBLE / 2 - bottomIndex) * BOX_GAP;

		// 분류기준
		drawRule(startX, bottomY);

		int input = getDirection();

		// 판정
		if (input == answers[bottomIndex])
		{
			
			// 점수 계산
			if (answers[bottomIndex] == 0) score += 2;
			if (answers[bottomIndex] == 1) score += 3;
			if (answers[bottomIndex] == 2) score += 5;

			drawBox(startX, bottomY, 10);   // 초록
		}
		else
		{
			life--;
			drawBox(startX, bottomY, 12);   // 빨강
		}
	
		Sleep(200);
		clearBox(startX, bottomY);

		if (life == 0)
		{
			drawGameOver(centerX, centerY, score);
			break;
		}

		// 배열 이동 (색유지)
		for (int i = VISIBLE - 1; i > 0; i--)
		{
			answers[i] = answers[i - 1];
			colors[i] = colors[i - 1];
		}

		// 새 상자 생성
		makeBox(&answers[0], &colors[0]);

		// 화면 정리
		for (int i = 0; i < VISIBLE; i++)
		{
			int y = centerY - (VISIBLE / 2 - i) * BOX_GAP;
			clearBox(startX, y);
		}
	}

	(void)_getch();
	return 0;
}