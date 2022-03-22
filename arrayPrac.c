#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




//������ �迭 ����
//ī�� ���߱�

#define col 4
#define low 5
#define totalNum col * low

void initCardArray();	//�迭 -1���� �ʱ�ȭ
void initCardNames();
void shuffleCade();
int getEmptyposition();	//�迭 �� �ʱ�ȭ�� ���� ��ȯ
int conv_position_x(int position);
int conv_position_y(int position);
void printCards();
void printQuestion();
int foundAllCard();


int arrayCard[col][low];	//ī�� ����
int checkCard[col][low];	//������ ī�� 
const char* strCard[10];

int main() {

	srand(time(NULL));

	initCardArray();
	initCardNames();

	shuffleCade();

	int failCounter = 0;

	while (true) {
		int select1 = 0;
		int select2 = 0;

		printCards();
		printQuestion();

		printf("ī�带 �� �� ���� : ");
		scanf_s("%d %d", &select1, &select2);
		if (select1 == select2)
			continue;

		int firstSelect_x = conv_position_x(select1);
		int firstSelect_y = conv_position_y(select1);

		int secondSelect_x = conv_position_x(select2);
		int secondSelect_y = conv_position_y(select2);

		if ((checkCard[firstSelect_x][firstSelect_y] == 0
			&& checkCard[secondSelect_x][secondSelect_y] == 0)

			&&

			(arrayCard[firstSelect_x][firstSelect_y] == 0
				&& arrayCard[secondSelect_x][secondSelect_y] == 0)

			)
		{
			printf("collect %c \n", arrayCard[firstSelect_x][firstSelect_y]);
			checkCard[firstSelect_x][firstSelect_y] = 1;
			checkCard[secondSelect_x][secondSelect_y] = 1;
		}
		else {
			printf("wrong\n");
			printf("%d %c \n", strCard[firstSelect_x][firstSelect_y], arrayCard[firstSelect_x][firstSelect_y]);
			printf("%d %c \n", strCard[secondSelect_x][secondSelect_y], arrayCard[secondSelect_x][secondSelect_y]);

			failCounter++;
		}

		if (foundAllCard()) {
			printf("finish, %d time\n", failCounter);
		}
	}
}

void initCardArray() {

	for (int i = 0; i < col; i++) {
		for (int j = 0; j < low; j++) {
			arrayCard[i][j] = -1;
		}
	}
}

void initCardNames() {

	strCard[0] = "���̽�";
	strCard[1] = "��";
	strCard[2] = "��";
	strCard[3] = "ŷ";
	strCard[4] = "��Ŀ";

	strCard[5] = "��Ʈ";
	strCard[6] = "�����̽�";
	strCard[7] = "Ŭ�ι�";
	strCard[8] = "���̾�";
	strCard[9] = "����";

}

void shuffleCade() {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			int position = getEmptyposition();
			int x = conv_position_x(position);
			int y = conv_position_y(position);

		}
	}
}

int getEmptyposition() {

	while (true)
	{
		int randPosition = rand() % 20;	//0~19
		int x = conv_position_x(randPosition);
		int y = conv_position_y(randPosition);

		if (arrayCard[x][y] == -1)
			return randPosition;
	}
	return 0;
}

int conv_position_x(int x) {

	return x / low;
}

int conv_position_y(int y) {

	return y % low;
}

void printCards() {

	for (int i = 0; i < col; i++) {
		for (int j = 0; j < low; j++) {
			printf("%8s", strCard[arrayCard[i][j]]);

		}
		printf("\n");
	}
	printf("\n");
}

void printQuestion() {

	int seq = 0;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < low; j++) {

			if (checkCard[i][j] != 0) {
				printf("%8s", strCard[arrayCard[i][j]]);
			}
			else {
				printf("%8d", seq++);
			}
		}
		printf("\n");
	}
}

int foundAllCard() {

	for (int i = 0; i < col; i++) {
		for (int j = 0; j < low; j++) {

			if (checkCard[i][j] == 0) {
				return 0;
			}
		}
	}

	return 1;
}