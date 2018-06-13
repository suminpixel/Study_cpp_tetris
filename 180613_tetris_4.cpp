#include<iostream>
#include<windows.h>
#include<cstdlib> //랜덤
#include<conio.h> //키입력

using namespace std;

#define BOARD_X 20 
#define BOARD_Y 20
#define LEFT 75
#define RIGHT 77
#define UP 72

int board[BOARD_Y][BOARD_X]; // 보드 선언

int block[7][4][4] = { //블럭종류 및 형태선언
	{
		{ 0,0,0,0 },
{ 0,1,1,0 },
{ 0,1,1,0 },
{ 0,0,0,0 }
	},
	{
		{ 0,1,0,0 },
{ 0,1,0,0 },
{ 0,1,0,0 },
{ 0,1,0,0 }
	},
	{
		{ 0,0,0,0 },
{ 0,0,0,0 },
{ 0,1,0,0 },
{ 1,1,1,0 }
	},
	{
		{ 0,0,0,0 },
{ 0,1,0,0 },
{ 0,1,1,0 },
{ 0,0,1,0 }
	},
	{
		{ 0,0,0,0 },
{ 0,0,1,0 },
{ 0,1,1,0 },
{ 0,1,0,0 }
	},
	{
		{ 0,0,0,0 },
{ 0,1,0,0 },
{ 0,1,0,0 },
{ 0,1,1,0 }
	},
	{
		{ 0,0,0,0 },
{ 0,0,1,0 },
{ 0,0,1,0 },
{ 0,1,1,0 }
	},
};

void ioSetCursorPosition(int x, int y) { // 커서위치 읽기

	COORD pos = { 2 * x, y }; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

void ioHideCursor() { //커서숨김

	CONSOLE_CURSOR_INFO cur_info;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);
	cur_info.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);
}

/*
void clearBoard() { //보드 초기화

	ioSetCursorPosition(0, 0);
	for (int i = 0; i < BOARD_Y; i++) {
		for (int j = 0; j < BOARD_X; j++) {
			cout << "  ";
		}
		cout << "\n";
	}
	ioSetCursorPosition(0, 0);
}
*/

void printBoard() { // 쌓인 블럭 묘사

	ioSetCursorPosition(0, 0);
	for (int y = 0; y < BOARD_Y; y++) {
		for (int x = 0; x < BOARD_X; ++x) {
			if (board[y][x] == 1) {
				cout << "■";
			}
			else
				cout << "  ";
		}
		cout << "\n";
	}
}

void render(int x, int y, int shape) { //블럭 출력

	for (int i = 0; i < 4; i++) {
		ioSetCursorPosition(x, y + i); //커서의 포지션을 잡아서 4x4만큼 출력해줌
		for (int j = 0; j < 4; j++) {

			if (block[shape][i][j] == 1) {
				cout << "■";
			}
			else
				cout << "□";
		}
		cout << "\n";
	}
}

// 블럭을 체크하는 로직 128`136

// 모양을 대입하는 부분이 있음
// 144 ~ 148

bool canNotMove(int x, int y, int shape) { //블럭 충돌 체크 

	bool bBlocked = false;

	for (int i = 0; i < 4; ++i) { 
		for (int j = 0; j < 4; ++j) {
			if (board[y + i][x + j] == 1 && block[shape][i][j] == 1) { 
				bBlocked = true;
				break;
			}
		}
		if (true == bBlocked) break;
	}

	return bBlocked;
}

bool drawBlock(int x, int y, int shape) { //블

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[y - 1 + i][x + j] |= block[shape][i][j];
		}
	}
	return true;
}

int main() {

	ioHideCursor();

	for (int i = 0; i < BOARD_X; i++) { // 밑판 깔기
		board[BOARD_Y - 1][i] = 1;
	}
	for (int i = 0; i < BOARD_Y; i++) { // 옆판 깔기
		board[i][0] = board[i][BOARD_X - 1] = 1;
	}

	bool bGameOver = false;

	while (false == bGameOver) { // 드롭 반복
		int x = 8; // 초기위치
		int y = 0;
		int shape = rand() % 7; //랜덤 블럭 숫자
		while (false == bGameOver) { // 첫번째 싸이클 시작 (조건: 게임오버)

			printBoard();
			render(x, y, shape); //지 정된 좌표에 대한 블럭출력하기
			//★블럭한칸 지우기

								 // x <==>  움직임 체크 및 그림그리기
			if (_kbhit()) { // 
				char a;
				a = _getch();

				switch (a) {
				case LEFT:
					// left면
					// 왼쪽으로 옮길 예정
					// 옮기기 전에 왼쪽으로 옮겨도 되는지 체크를 해야함
					if (false == canNotMove(x - 1, y, shape)) { // canNotMove에 x-1을 넣어준 것은 x= x-1을 수행한 것은 아니고, 미리 체크만 하는 부분
						x--; // 왼쪽으로 옮겼다. have + p.p. I have moved // 옮길 수 있어서, 옮겨버림
						render(x, y, shape); //4. 지정된 좌표에 대한 블럭출력하기
					}
					break;

				case RIGHT:
					// 옮기기 전에 오른쪽으로 옮겨도 되는지 체크를 해야함

					if (false == canNotMove(x + 1, y, shape)) {

						x++;
						render(x, y, shape);
					}

					break;




				default:
					break;
				}
				continue;
			}

			Sleep(200);

			y++; // 5. 값 +




			if (canNotMove(x, y, shape)) { 내려갈 수 있는지 체크 
				drawBlock(x, y, shape);
				y--;
				if (y == 0)
					bGameOver = true;
				break;
			}
		}
	}

	getchar();
	getchar();
	return 0;


}