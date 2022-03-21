#include <stdio.h>
#include <time.h>



//다차원 배열 연습
//카드 맞추기

#define cow 4
#define low 5

void initCardArray();	//배열 -1으로 초기화
void initCardNames();	
void shuffleCade();		
int getEmptyposition();	//배열 중 초기화인 상태 반환
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

		printf("카드를 두 장 선택 : ");
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

	cardNames[0] = "에이스";
	cardNames[1] = "잭";
	cardNames[2] = "퀸";
	cardNames[3] = "킹";
	cardNames[4] = "조커";

	cardNames[5] = "하트";
	cardNames[6] = "스페이스";
	cardNames[7] = "클로버";
	cardNames[8] = "다이아";
	cardNames[9] = "숫자";

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

