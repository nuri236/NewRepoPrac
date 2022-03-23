//다차원 배열 연습
//카드 맞추기

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define col 4	
#define low 5	
//카드 지도 (4*5)
//카드 범위 0~19
//ㅁㅁㅁㅁㅁ
//ㅁㅁㅁㅁㅁ
//ㅁㅁㅁㅁㅁ
//ㅁㅁㅁㅁㅁ

void initCardArray();				//카드 지도 배열 -1으로 초기화
void initCardNames();				//카드 이름 배열 초기화
void shuffleCade();				//랜덤으로 카드 이름을 카드 지도와 연결
int getEmptyposition();				//배열의 요소가 초기화된 상태면 범위내 랜덤한 정수, 아니면 0 반환
int conv_position_x(int position);		//카드 지도의 정수값을 몇 행인지 반환
int conv_position_y(int position);		//카드 지도의 정수값을 몇 열인지 반환
void printCards();				//테스트용 정답 출력
void printQuestion();				//플레이어가 보는 문제 출력
int foundAllCard();				//모든 카드가 맞춰졌으면 0, 아니면 1 반환


int arrayCard[col][low];	//카드 지도 배열
int checkCard[col][low];	//뒤집힌 카드 확인용, 맞춘 카드 1, 못맞춘 카드 0
const char* strCard[10];	//카드 이름 넣을 문자열 배열

int main() {

	srand(time(NULL));

	initCardArray();
	initCardNames();
	shuffleCade();

	int failCounter = 0;	//실패횟수 카운트, 마지막에 반환

	printf("\n=====================테스트용=======================\n");
	printCards();
	printf("====================================================\n");


	while (true) {
		int select1 = 0;	//처음 입력받을 수
		int select2 = 0;	//다음 입력받을 수

		printQuestion();

		printf("첫번째 카드 선택 : ");
		scanf_s("%d", &select1);
		printf("두번째 카드 선택 : ");
		scanf_s("%d", &select2);

		if (select1 == select2)
			continue;

		//입력받은 수를 행, 열로 변환
		int firstSelect_x = conv_position_x(select1);
		int firstSelect_y = conv_position_y(select1);

		int secondSelect_x = conv_position_x(select2);
		int secondSelect_y = conv_position_y(select2);

		if (
			(checkCard[firstSelect_x][firstSelect_y] == 0
				&& checkCard[secondSelect_x][secondSelect_y] == 0)
			//선택한 카드들이 맞추지 않은 상태이고,
			&&
			(arrayCard[firstSelect_x][firstSelect_y] == arrayCard[secondSelect_x][secondSelect_y])
			//두 내용물이 같으면
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

	strCard[0] = "에이스";
	strCard[1] = "잭";
	strCard[2] = "퀸";
	strCard[3] = "킹";
	strCard[4] = "조커";

	strCard[5] = "하트";
	strCard[6] = "스페이스";
	strCard[7] = "클로버";
	strCard[8] = "다이아";
	strCard[9] = "숫자";

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