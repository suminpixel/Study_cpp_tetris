#include<iostream>
#include<windows.h>

using namespace std;

#define BOARD_X 10
#define BOARD_Y 20


int board[BOARD_Y][BOARD_X];
//7개 4,4 배열
int block[7][4][4] = {
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{ 0,0,0,0 },
{ 0,1,1,0 },
{ 0,1,1,0 },
{ 0,0,0,0 }
	},
	{
		{ 0,0,0,0 },
{ 0,1,1,0 },
{ 0,1,1,0 },
{ 0,0,0,0 }
	},
	{
		{ 0,0,0,0 },
{ 0,1,1,0 },
{ 0,1,1,0 },
{ 0,0,0,0 }
	},
	{
		{ 0,0,0,0 },
{ 0,1,1,0 },
{ 0,1,1,0 },
{ 0,0,0,0 }
	},
	{
		{ 0,0,0,0 },
{ 0,1,1,0 },
{ 0.1,1,0 },
{ 0,0,0,0 }
	},
	{
		{ 0,0,0,0 },
{ 0,1,1,0 },
{ 0,1,1,0 },
{ 0,0,0,0 }
	}
};


void ioSetCursorPosition(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void clearBoard() {
	ioSetCursorPosition(0, 0);
	for (int i = 0; i < BOARD_Y; ++i)
	{
		for (int j = 0; j < BOARD_X; ++j) {
			cout << "  "; //cout[i][j];
		}
		cout << "\n";
	}
	ioSetCursorPosition(0, 0);
}


void printBoard() {
	ioSetCursorPosition(0, 0);
	for (int y = 0; y < BOARD_Y; ++y) {
		for (int x = 0; x < BOARD_X; ++x) {
			if (board[y][x] == 1) {
				cout << "■";
			}
			else
				cout << "  ";
		}
		cout << '\n';
	}

}



void render(int x, int y) { // 첫번째 블럭 출력

	ioSetCursorPosition(x, y);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			if (block[0][i][j] == 1) {
				cout << "■";
			}
			else
				cout << "  ";
		}
		cout << '\n';
	}

}

bool checkBlock(int x, int y) {
	bool check = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; ++j) {

			if (board[y + i][x + j] == 1 && block[0][i][j] == 1) {

				check = true;
				break;

			}
			if (check == true)
				break;

		}

	}
	if (check == false)
		return false;

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {

			board[y - 1 + i][x] == block[0][i][i];

		}
	}
	return true;

}
int main() {

	for (int i = 0; i < BOARD_X; i++) {
		board[BOARD_Y - 1][i] = 1;
	}


	while (true) {
		int x = 5;
		int y = 0; // 셋포지션
		while (true) { // 한블럭이 내려올 때 까지

		// x와 y의 값이 변한다
		// y는 아래로 x는 입력값
		// board를 그린다
			printBoard();
			// 그림을 보여준다.
			render(x, y);
			Sleep(600);
			// 체크체크
			clearBoard();

			y++;
			if (checkBlock(x, y)) {
				y--;
				break;
			}


			//for (int i = 0; i < BOARD_Y; i++) {
			//	for (int j = 0; j < BOARD_X; j++){

			//		//특정 좌표의 블럭의 x,y값 = 보드의 값 // 1로 같을때 충돌 
			//		if

			//	}

			//}



	// 보드에 기록한다.




	// 화면을 지운다.

		//printBoard();
		//Sleep(300);
		//clearBoard();

		}
	}



	getchar();
	getchar();
	return 0;
}