#include<iostream>
#include<windows.h>

using namespace std;

#define BOARD_X 20 
#define BOARD_Y 20
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

void ioSetCursorPosition(int x, int y) { // Ŀ����ġ

	COORD pos = { 2*x, y }; //��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

void ioHideCursor() { //Ŀ������

	CONSOLE_CURSOR_INFO cur_info;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);
	cur_info.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);
}

void clearBoard() { //���� �ʱ�ȭ

	ioSetCursorPosition(0, 0);
	for (int i = 0; i < BOARD_Y; i++) {
		for (int j = 0; j < BOARD_X; j++) {
			cout << "��"; 
		}
		cout << "\n";
	}
	ioSetCursorPosition(0, 0);
}

void printBoard() { // ���� �� ����

	ioSetCursorPosition(0, 0);
	for (int y = 0; y < BOARD_Y; y++) {
		for (int x = 0; x < BOARD_X; ++x) {
			if (board[y][x] == 1) {
				cout << "��";
			}
			else
				cout << "��";
		}
		cout << "\n";
	}
}

void render(int x, int y) { //�� ���

	for (int i = 0; i < 4; i++) {
		ioSetCursorPosition(x, y+i); 
		for (int j = 0; j < 4; j++) {

			if (block[4][i][j] == 1) {
				cout << "��";
			}
			else 
				cout<< "��";
		}
		cout << "\n";
	}
}

bool checkBlock(int x, int y) { //��üũ 

	bool check = false;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (board[y + i][x + j] == 1 && block[0][i][j] == 1) {
				check = true;
				break;
			}
		}
		if (true == check) break;
	}
	if (false == check) return false;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[y - 1 + i][x + j] |= block[0][i][j];
		}
	}
	return true;
}

int main() {

	ioHideCursor();

	for (int i = 0; i < BOARD_X; i++) { // ���� ���
		board[BOARD_Y -1 ][i] = 1;
	}
	for (int i = 0; i < BOARD_Y; i++) { // ���� ���
		board[i][0] = board[i][BOARD_X - 1] = 1;
	}

	bool bGameOver = false;

	while (false == bGameOver) { // ��� �ݺ�
		int x = 8; //1. �ʱ���ġ
		int y = 0;
		while (false == bGameOver) { //2.���ӿ��� ���Ǳ��� �ݺ�
			printBoard(); //3. �������
			render(x, y); //4. �����
			Sleep(100);
			y++; // 5. y��ǥ�� +
			if (checkBlock(x, y)) { //6. ������ �� �ִ��� üũ 
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