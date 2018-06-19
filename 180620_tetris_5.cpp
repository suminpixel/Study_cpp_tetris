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
//#define SPACE 32 //블록변환

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

void rotateBlock( int shape ) { // ★행과 열을 바꾸는 형태로 출력-45 block[0][y][x]
	int block2[4][4];
	for (int y = 0; y < 4; ++y) {   
		for (int x = 0 ; x < 4; ++x) {
			block2[x][4 - y - 1] = block[shape][y][x];
		}
	}

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			block[shape][y][x] = block2[y][x];
		}
	}


}

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

bool drawBlock(int x, int y, int shape) { //블럭 대입

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
		while (false == bGameOver) { // 블럭 하나가 한칸씩 떨어짐 (조건: 게임오버)

			printBoard();

			render(x, y, shape); //지 정된 좌표에 대한 블럭출력하기

								 //★블럭한칸 지우기

			if (_kbhit()) { //키입력 받기
				char a;
				a = _getch();

				switch (a) {
				case LEFT:
					if (false == canNotMove(x - 1, y, shape)) { 
						x--; 
						render(x, y, shape); 
					}
					break;

				case RIGHT:

					if (false == canNotMove(x + 1, y, shape)) {

						x++;
						render(x, y, shape);
					}
					break;

					
				case UP:
					rotateBlock(shape);
					render(x,y, shape);
					break;
					
				default:
					break;
					}
					continue;
				}

				Sleep(200);

				y++; // 값 +

				if (canNotMove(x, y, shape)) { //내려갈 수 있는지 체크
					drawBlock(x, y, shape);
					y--;
					if (y == 0)
						bGameOver = true;
					break;
				}
			}



		//---이후 진행상황---//
		
		/*

		기믹 : 새로운 게임의 특성 

		체크는 drawBlcok이후
		하나의 줄에대한 사이즈 width 

		지우는 for 문은 아래로 부터 읽기 (한줄에 0이 없는가)
		4줄만 체크해도 됨.
		다 체크 한 후


		여러가지 

		한줄 체크하고 

		블럭 다시 대입

		랜더는 한쿨마다 체크중
		board <-b 

		*/
		}

		getchar();
		getchar();
		return 0;

	}
