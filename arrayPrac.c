#include <stdio.h>
#include <time.h>



//������ �迭 ����
//ī�� ���߱�

#define cow 4
#define low 5

void initCardArray();	//�迭 -1���� �ʱ�ȭ
void initCardNames();	
void shuffleCade();		
int getEmptyposition();	//�迭 �� �ʱ�ȭ�� ���� ��ȯ
int conv_position_x(int position);
int conv_position_y(int position);
void printCards();
void printQuestion();


int arrayCard[cow][low];
char cardNames[(cow * low)];

void main() {

	srand(time(NULL));

	initCardArray();
	initCard();

	shuffleCade();

	int fallCounter = 0;

	whlile(true) {
		int firstChoice=0;
		int secoundChoice = 0;

		printCards();
		printQuestion();

		printf("ī�带 �� �� ���� : ");
		scanf_s("%d %d", &firstChoice, &secoundChoice);
		if (firstChoice == secoundChoice)
			continue;
	}
}

void initCardArray() {

	for (int i = 0, i < col, i++) {
		for (int j = 0, j < low, j++) {
			arraycard[i][j] = -1;
		}
	}
}

void initCardNames() {

	cardNames[0] = "���̽�";
	cardNames[1] = "��";
	cardNames[2] = "��";
	cardNames[3] = "ŷ";
	cardNames[4] = "��Ŀ";

	cardNames[5] = "��Ʈ";
	cardNames[6] = "�����̽�";
	cardNames[7] = "Ŭ�ι�";
	cardNames[8] = "���̾�";
	cardNames[9] = "����";

}

void shuffleCade() {

	for (int i = 0, i < 10, i++) {
		for (int j = 0, j < 2, j++) {
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


}

void printQuestion() {


}

