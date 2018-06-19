#include<iostream>
#include<windows.h>
#include<cstdlib> //����
#include<conio.h> //Ű�Է�

using namespace std;

#define BOARD_X 20 
#define BOARD_Y 20
#define LEFT 75
#define RIGHT 77
#define UP 72
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

void rotateBlock( int shape ) { // ����� ���� �ٲٴ� ���·� ���-45 block[0][y][x]
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

int main() {

	ioHideCursor();

	for (int i = 0; i < BOARD_X; i++) { // ���� ���
		board[BOARD_Y - 1][i] = 1;
	}
	for (int i = 0; i < BOARD_Y; i++) { // ���� ���
		board[i][0] = board[i][BOARD_X - 1] = 1;
	}

	bool bGameOver = false;

	while (false == bGameOver) { // ��� �ݺ�
		int x = 8; // �ʱ���ġ
		int y = 0;
		int shape = rand() % 7; //���� �� ����
		while (false == bGameOver) { // �� �ϳ��� ��ĭ�� ������ (����: ���ӿ���)

			printBoard();

			render(x, y, shape); //�� ���� ��ǥ�� ���� ������ϱ�

								 //�ں���ĭ �����

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

				y++; // �� +

				if (canNotMove(x, y, shape)) { //������ �� �ִ��� üũ
					drawBlock(x, y, shape);
					y--;
					if (y == 0)
						bGameOver = true;
					break;
				}
			}



		//---���� �����Ȳ---//
		
		/*

		��� : ���ο� ������ Ư�� 

		üũ�� drawBlcok����
		�ϳ��� �ٿ����� ������ width 

		����� for ���� �Ʒ��� ���� �б� (���ٿ� 0�� ���°�)
		4�ٸ� üũ�ص� ��.
		�� üũ �� ��


		�������� 

		���� üũ�ϰ� 

		�� �ٽ� ����

		������ ���𸶴� üũ��
		board <-b 

		*/
		}

		getchar();
		getchar();
		return 0;

	}
