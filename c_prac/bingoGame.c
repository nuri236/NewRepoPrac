//���� ���߱�

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define COL 5
#define ROW 5

void initArray(int(*array)[COL]);
void suffleArray();
int getEmptyposition();
int convertPointX(int x);
int convertPointY(int y);
void printArray(int(*array)[COL]);
int getNumber();
int checkBingo();
int checkBingo_col();
int checkBingo_row();
int checkBingo_dig_1();
int checkBingo_dig_2();

int numArray[COL][ROW];
int checkArray[COL][ROW];

int main()
{
	int bingoCounter = 0;

	srand(time(NULL));
	initArray(numArray);
	initArray(checkArray);
	suffleArray();
	printArray(numArray);

	while (1) {
		getNumber();	//���ڸ� �Է¹޾Ƽ� ǥ���ϰ� ��ȯ
		printArray(numArray);
		bingoCounter = checkBingo();

		if (bingoCounter > 4) {

			break;
		}
	}

	printf("[�����մϴ�.]\n");
	return 0;
}

//�迭 �ʱ�ȭ �Լ�
void initArray(int(*array)[COL])
{
	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			array[i][j] = -1;
		}
	}
}

void suffleArray()
{
	int num = 1;

	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			int randPosition = getEmptyposition();
			int x = convertPointX(randPosition);
			int y = convertPointY(randPosition);

			numArray[x][y] = num;
			num++;
		}
	}

}

int getEmptyposition()
{

	while (true)
	{
		int randPosition = rand() % 25;	//0~24
		int x = convertPointX(randPosition);
		int y = convertPointY(randPosition);

		if (numArray[x][y] == -1) {
			return randPosition;
		}
	}
}

int convertPointX(int x)
{
	return x / COL;
}

int convertPointY(int y)
{
	return y % ROW;
}

void printArray(int(*array)[COL])
{
	printf("\n");

	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			if (checkArray[i][j] == -1)
				printf("%4d", array[i][j]);
			else
				printf("%4c", '*');
		}
		printf("\n");
	}
	printf("\n");
}

int getNumber()
{
	int num;

	while (1) {
		printf("[���ڸ� �Է��ϼ���. (1~25)] : ");
		scanf("%d", &num);	// 1~25
		int x, y;

		//�Էµ� ���ڰ� ������ ����� ��
		if (num < 1 || num > 25) {
			printf("\n[�߸��� ������ �����Դϴ�.]\n");
			continue;
		}

		//�Էµ� ���ڿ� ���� ���ڸ� ���� �迭�� ��ǥ ã��
		for (int i = 0; i < COL; i++) {
			for (int j = 0; j < ROW; j++) {
				if (numArray[i][j] == num) {
					x = i;
					y = j;
				}
			}
		}

		//�̹� �Է��� ���ڿ��� ��
		if (checkArray[x][y] == 0) {
			printf("[�̹� �Էµ� �����Դϴ�.]\n");
			continue;
		}

		checkArray[x][y] = 0;

		return num;
	}
}

int checkBingo()
{
	int bingoCounter = 0;

	bingoCounter += checkBingo_col();
	bingoCounter += checkBingo_row();
	bingoCounter += checkBingo_dig_1();
	bingoCounter += checkBingo_dig_2();

	printf("*******************\n");
	printf("******%d ����******\n", bingoCounter);
	printf("*******************\n\n");

	return bingoCounter;
}

int checkBingo_col()
{
	int bingo = false;
	int bingoCounter = 0;

	for (int i = 0; i < COL; i++) {

		bingo = true;

		for (int j = 0; j < ROW; j++) {
			if (checkArray[i][j] != 0) {
				bingo = false;
			}
		}

		if (bingo == true)
			bingoCounter++;
	}

	return bingoCounter;
}

int checkBingo_row()
{
	int bingo = false;
	int bingoCounter = 0;

	for (int j = 0; j < ROW; j++) {

		bingo = true;

		for (int i = 0; i < COL; i++) {
			if (checkArray[i][j] != 0) {
				bingo = false;
			}
		}

		if (bingo == true)
			bingoCounter++;
	}

	return bingoCounter;
}

int checkBingo_dig_1()
{
	int bingo = true;

	for (int i = 0; i < COL; i++) {
		if (checkArray[i][i] != 0)
			bingo = false;
	}

	return bingo;
}

int checkBingo_dig_2()
{
	int bingo = true;

	for (int i = 0; i < COL; i++) {
		if (checkArray[i][(4 - i)] != 0)
			bingo = false;
	}

	return bingo;
}