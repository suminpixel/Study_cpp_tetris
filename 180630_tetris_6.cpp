#include<iostream>
#include<windows.h>
#include<cstdlib> //����
#include<conio.h> //Ű�Է�
#include<stdio.h>

using namespace std;

#define BOARD_X 10 
#define BOARD_Y 20
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
//#define SPACE 32 //��Ϻ�ȯ

int board[BOARD_Y][BOARD_X]; // ���� ����

int block[7][4][4] = { //������ �� ���¼���
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

void rotateBlock(int shape) { // ����� ���� �ٲٴ� ���·� ���-45 block[0][y][x]
	int block2[4][4];
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			block2[x][4 - y - 1] = block[shape][y][x];
		}
	}

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			block[shape][y][x] = block2[y][x];
		}
	}


}

void ioSetCursorPosition(int x, int y) { // Ŀ����ġ �б�

	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

void ioHideCursor() { //Ŀ������

	CONSOLE_CURSOR_INFO cur_info;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);
	cur_info.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);
}

void printBoard() { // ���� �� ����

	ioSetCursorPosition(0, 0);
	for (int y = 0; y < BOARD_Y; y++) {
		for (int x = 0; x < BOARD_X; ++x) {
			if (board[y][x] == 1) {
				cout << "��";
			}
			else
				cout << "  ";
		}
		cout << "\n";
	}
}

void render(int x, int y, int shape) { //�� ���

	for (int i = 0; i < 4; i++) {
		ioSetCursorPosition(x, y + i); //Ŀ���� �������� ��Ƽ� 4x4��ŭ �������
		for (int j = 0; j < 4; j++) {

			if (block[shape][i][j] == 1) {
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shape+1);
				cout << "��";
			}
			else
				cout << "��";
		}
		cout << "\n";
	}
}

bool canNotMove(int x, int y, int shape) { //�� �浹 üũ 

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

bool drawBlock(int x, int y, int shape) { //�� ����

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[y - 1 + i][x + j] |= block[shape][i][j];

		}
	}
	
	return true;
}

bool arrangeBlock(int i) {

	for (int k = 0; k < BOARD_Y - 1; ++k) {
		for (int j = 1; j < BOARD_X - 1; j++) {
			board[i-k][j] = board[i - k-1][j];
		}
	}

	printBoard();
	return true;
}

bool sweepBlock(int y, int * sweepScore) {

	bool sweepSwitch = true;

	for (int i = BOARD_Y - 2; i > 1; i--) {
		for (int j = 1; j < BOARD_X; j++) {

			if (board[i][j] == 0) {
				sweepSwitch = false;
				break;
			}
			else
				sweepSwitch = true;
		}

		if (sweepSwitch == true) {
			for (int k = 1; k < BOARD_X-1; ++k) {
				board[i][k] = 0;
			}
			
			arrangeBlock(i);
			i = i + 1;
			(*sweepScore)++;

			sweepSwitch = false;
		}

	}

	return sweepScore;
}


//=========================================================main========================================================//

int main() {
	char userName[20];
	int sweepScore = 0;
	int dropCount = 0;

	// OOBE
	bool nameInput = false;
	while (nameInput != true) {
		cout << "\n Username? = ";
		cin >> userName;
		nameInput = true;
	}
	Sleep(400);

	// �������
	for (int i = 0; i < BOARD_X; i++) { // ���� ���
		board[BOARD_Y - 1][i] = 1;
	}
	for (int i = 0; i < BOARD_Y; i++) { // ���� ���
		board[i][0] = board[i][BOARD_X - 1] = 1;
	}


	// ���ӽ���
	bool bGameOver = false;
	ioHideCursor();
	while (false == bGameOver) { // ��� �ݺ�


		int x = 4; // �ʱ���ġ
		int y = 0;
		int shape = rand() % 7; //���� �� ����
		dropCount++;

		while (false == bGameOver) { // �� �ϳ��� ��ĭ�� ������ (����: ���ӿ���)

			printBoard();

			render(x, y, shape); //�� ���� ��ǥ�� ���� ������ϱ�

			if (_kbhit()) { //Ű�Է� �ޱ�
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

				case DOWN:

					if (false == canNotMove(x, y + 1, shape)) {

						y++;
						render(x, y, shape);
					}
					break;

				case UP:
					rotateBlock(shape);
					render(x, y, shape);
					break;

				default:
					break;
				}
				continue;
			}

			Sleep(300);

			y++; // �� +

			if (canNotMove(x, y, shape)) { //������ �� �ִ��� üũ

				drawBlock(x, y, shape);

				sweepBlock(y, &sweepScore);	// ��

				ioSetCursorPosition(1, 26);
				cout << "Score :" << sweepScore*100;

				y--;

				if (y == 0)
					bGameOver = true;
				break;
			}

			// �������

			ioSetCursorPosition(1, 22);
			cout << "Username : " << userName;
			
			ioSetCursorPosition(1, 24);
			cout << "Drop:" << dropCount;

		}


	}

	getchar();
	getchar();
	return 0;

}