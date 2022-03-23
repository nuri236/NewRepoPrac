//������ �迭 ����
//ī�� ���߱�

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define col 4	
#define low 5	
//ī�� ���� (4*5)
//ī�� ���� 0~19
//����������
//����������
//����������
//����������

void initCardArray();				//ī�� ���� �迭 -1���� �ʱ�ȭ
void initCardNames();				//ī�� �̸� �迭 �ʱ�ȭ
void shuffleCade();				//�������� ī�� �̸��� ī�� ������ ����
int getEmptyposition();				//�迭�� ��Ұ� �ʱ�ȭ�� ���¸� ������ ������ ����, �ƴϸ� 0 ��ȯ
int conv_position_x(int position);		//ī�� ������ �������� �� ������ ��ȯ
int conv_position_y(int position);		//ī�� ������ �������� �� ������ ��ȯ
void printCards();				//�׽�Ʈ�� ���� ���
void printQuestion();				//�÷��̾ ���� ���� ���
int foundAllCard();				//��� ī�尡 ���������� 0, �ƴϸ� 1 ��ȯ


int arrayCard[col][low];	//ī�� ���� �迭
int checkCard[col][low];	//������ ī�� Ȯ�ο�, ���� ī�� 1, ������ ī�� 0
const char* strCard[10];	//ī�� �̸� ���� ���ڿ� �迭

int main() {

	srand(time(NULL));

	initCardArray();
	initCardNames();
	shuffleCade();

	int failCounter = 0;	//����Ƚ�� ī��Ʈ, �������� ��ȯ

	printf("\n=====================�׽�Ʈ��=======================\n");
	printCards();
	printf("====================================================\n");


	while (true) {
		int select1 = 0;	//ó�� �Է¹��� ��
		int select2 = 0;	//���� �Է¹��� ��

		printQuestion();

		printf("ù��° ī�� ���� : ");
		scanf_s("%d", &select1);
		printf("�ι�° ī�� ���� : ");
		scanf_s("%d", &select2);

		if (select1 == select2)
			continue;

		//�Է¹��� ���� ��, ���� ��ȯ
		int firstSelect_x = conv_position_x(select1);
		int firstSelect_y = conv_position_y(select1);

		int secondSelect_x = conv_position_x(select2);
		int secondSelect_y = conv_position_y(select2);

		if (
			(checkCard[firstSelect_x][firstSelect_y] == 0
				&& checkCard[secondSelect_x][secondSelect_y] == 0)
			//������ ī����� ������ ���� �����̰�,
			&&
			(arrayCard[firstSelect_x][firstSelect_y] == arrayCard[secondSelect_x][secondSelect_y])
			//�� ���빰�� ������
			)
		{
			printf("collect %s \n", strCard[arrayCard[firstSelect_x][firstSelect_y]]);
			checkCard[firstSelect_x][firstSelect_y] = 1;
			checkCard[secondSelect_x][secondSelect_y] = 1;
		}
		else {
			printf("wrong\n");
			printf("%d %s \n", select1, strCard[arrayCard[firstSelect_x][firstSelect_y]]);
			printf("%d %s \n", select2, strCard[arrayCard[secondSelect_x][secondSelect_y]]);

			failCounter++;
		}

		if (foundAllCard()) {
			printf("finish, %d time\n", failCounter);
			return 0;
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

			arrayCard[x][y] = i;
		}
	}
}

int getEmptyposition() {

	while (true)
	{
		int randPosition = rand() % 20;	//0~19
		int x = conv_position_x(randPosition);
		int y = conv_position_y(randPosition);

		if (arrayCard[x][y] == -1) {

			return randPosition;
		}
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
			printf("%10s", strCard[arrayCard[i][j]]);

		}
		printf("\n");
	}
}

void printQuestion() {

	int seq = 0;

	printf("\n====================================================\n");
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < low; j++) {

			if (checkCard[i][j] != 0) {
				printf("%10s", strCard[arrayCard[i][j]]);
			}
			else {
				printf("%10d", seq);
			}
			seq++;
		}
		printf("\n");
	}
	printf("====================================================\n");
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