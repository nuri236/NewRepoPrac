//네트워크 프로그래밍 연습 1
//클라이언트 화면 구성
//학생부 만들기

#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <string.h>  
#include <stdlib.h> 
#include <Windows.h>

#define MAX_AGE 130	//입력 가능 최대 나이 130
#define MIN_AGE 0	//입력 가능 최소 나이 0

typedef struct node {
	struct node* next;

	char name[10];	//이름 변수
	char phone[20];	//연락처 변수
	int age;		//나이 변수
	char gender;	//성별 변수
}node;

//메뉴 출력 함수 
int printMenu() {
	int num;	//선택할 번호 변수

	printf("\n[메뉴]\n");
	printf("(1) 개별 신상 정보 입력\n");
	printf("(2) 전체 신상 정보 출력\n");
	printf("(3) 개별 신상 정보 조회\n");
	printf("(4) 개별 신상 정보 삭제\n");
	printf("(5) 프로그램 종료\n");
	printf("번호 선택 : ");
	scanf("%d", &num);

	return num;
}

//개별 신상 정보 입력 함수
void insertPersonalInformation(node** head)
{
	printf("[개별 신상 정보 입력]\n");

	// 새 노드 생성 및 초기화
	node* newNode = (node*)malloc(sizeof(node));
	newNode->next = NULL;

	//데이터 입력
	printf("이름 : ");
	scanf("%s", &newNode->name);
	printf("연락처(000-0000-0000) : ");
	scanf("%s", newNode->phone);

	do
	{
		printf("성별(M/F) : ");
		char gender;
		scanf(" %c", &gender);
		if (gender == 'M' || gender == 'F') {
			newNode->gender = gender;
			break;
		}
		else
			printf("[잘못된 입력입니다.]\n");
	} while (TRUE);

	do
	{
		printf("나이 : ");
		int age;
		scanf("%d", &age);
		if (age < MAX_AGE && age > MIN_AGE) {
			newNode->age = age;
			break;
		}
		else
			printf("[잘못된 입력입니다.]\n");
	} while (TRUE);

	//첫 노드일 경우 헤드 노드가 참조
	if (*head == NULL) {
		*head = newNode;
	}
	//첫 노드가 아닌 경우, 마지막 노드 뒤에 삽입
	else {
		node* temp = (node*)malloc(sizeof(node));
		temp = *head;

		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
}

//전체 신상 정보 출력 함수
void printallinformation(node** head) {
	int numT = 0;						//인원수 확인 변수
	int numF = 0, numM = 0;				//성별 인원수 변수
	int ageY = MAX_AGE + 1, ageO = MIN_AGE - 1;		//최저령, 최고령 변수

	node* curr = (node*)malloc(sizeof(node));
	curr = *head;

	if (curr == NULL) {
		printf("[입력된 정보가 없습니다.] \n");
		return;
	}

	printf("[전체 신상 정보 출력]\n");
	printf("%-10s %-20s %-6s %-6s\n", "이름", "연락처", "성별", "나이");
	printf("-------------------------------------------------\n");

	// 포인터가 null이 아닐 때까지 계속 반복
	while (curr != NULL)
	{
		numT += 1;
		if (curr->gender == 'F')
			numF += 1;
		if (curr->age > ageO)
			ageO = curr->age;
		if (curr->age < ageY)
			ageY = curr->age;

		printf("%-10s ", curr->name);
		printf("%-20s ", curr->phone);
		printf("%-6c ", curr->gender);
		printf("%-6d", curr->age);
		printf("\n");

		// 포인터에 다음 노드의 주소 저장
		curr = curr->next;
	}
	printf("\n[기타 정보]\n");
	printf("총 인원 : %d\n", numT);
	printf("남성 : %d\n", numM = numT - numF);
	printf("여성 : %d\n", numF);
	printf("최고령 : %d\n", ageO);
	printf("최저령 : %d\n", ageY);
}

//개별 신상 정보 삭제 함수
void deletePersonalInformation(node** head) {
	char name[10];		//삭제할 이름 변수
	char YorN;		//삭제 여부 확인 변수
	int count = 0;		//삭제할 이름이 있는지 확인할 변수

	node* curr = (node*)malloc(sizeof(node));
	curr = *head;

	//저장된 노드가 없을 경우 반환
	if (curr == NULL) {
		printf("[입력된 정보가 없습니다.] \n");
		return;
	}
	//저장된 노드가 있을 경우 진행
	else {

		//삭제할 이름 입력 받음
		printf("[개별 신상 정보 삭제]\n");
		printf("삭제할 이름 입력 : ");
		scanf("%s", &name);

		while (TRUE) {

			//입력받은 이름과 같은 노드가 있으면 삭제 여부 선택
			if (strcmp(name, curr->name) == 0) {
				count += 1;

				printf("\n이름: %-10s", curr->name);
				printf("\n연락처 : %-20s", curr->phone);
				printf("\n성별 : %-6c", curr->gender);
				printf("\n나이 : %-6d", curr->age);
				printf("\n삭제하시겠습니까? (Y/N) : ");

				//YorN 입력받기
				do {
					YorN;
					scanf(" %c", &YorN);

					if (YorN == 'Y' || YorN == 'N') {
						break;
					}
					else {
						printf("\n[잘못된 입력입니다. 다시 입력해주세요.]\n");
					}
				} while (TRUE);

				//삭제를 선택한 경우
				if (YorN == 'Y') {

					//첫 노드를 삭제할 경우
					if ((*head) == curr) {
						(*head) = curr->next;
						curr = (*head);

						printf("\n[삭제가 완료되었습니다.]\n\n");
						continue;

					}
					//두번째 이상의 노드를 삭제할 경우
					else {
						node* pre = (node*)malloc(sizeof(node));
						pre = *head;

						//pre 노드의 next 포인터가 curr을 참조
						while (pre->next != curr) {
							pre = pre->next;
						}

						pre->next = curr->next;
						curr = pre;

						printf("\n[삭제가 완료되었습니다.]\n\n");
					}
				}
				//삭제를 취소한 경우, 그대로 패스
				else if (YorN == 'N') {
					printf("\n[삭제가 취소되었습니다.]\n");
				}
			}

			//현재 노드의 다음 노드가 NULL이면 종료, 아니면 반복
			if (curr->next == NULL) {

				if (count == 0) {
					printf("\n[%s의 정보가 없습니다.]\n", name);

				}

				printf("\n[삭제를 종료합니다.]\n");
				return;
			}
			else { curr = curr->next; }
		}
	}
}

//개별 신상 정보 조회 함수
void searchPersonalInformation(node** head) {
	char name[10];	//삭제할 이름 변수
	int count = 0;	//삭제 여부 확인 변수

	node* curr = (node*)malloc(sizeof(node));
	curr = *head;

	printf("\n[개별 신상 정보 조회]\n");
	printf("조회할 이름 : ");
	scanf("%s", name);

	printf("\n[개별 신상 정보 출력]\n");
	printf("\n%-10s %-20s %-6s %-6s \n", "이름", "연락처", "성별", "나이");
	printf("-------------------------------------------------\n");

	// 포인터가 null이 아닐 때까지 계속 반복
	while (curr != NULL)
	{
		//목표를 찾으면 출력
		if (strcmp(curr->name, name) == 0) {
			printf("%-10s ", curr->name);
			printf("%-20s ", curr->phone);
			printf("%-6c ", curr->gender);
			printf("%-6d\n", curr->age);

			count += 1;
		}
		curr = curr->next;
	}

	//목표를 찾지 못했을 때 출력
	if (count == 0) {
		printf("\n[%s의 정보가 없습니다.]\n", name);
	}

	return;
}

int main() {

	node* head = NULL;	//헤드 노드 초기화

	while (TRUE) {
		int num = printMenu();	//메뉴 출력 함수
		system("clear");		//화면 초기화

		switch (num) {
		case 1:
			//(1) 선택시, 개별 신상 정보 입력
			insertPersonalInformation(&head);
			break;
		case 2:
			//(2) 선택시,전체 신상 정보 출력 
			printallinformation(&head);
			break;
		case 3:
			//(3) 선택시,개별 신상 정보 조회 
			searchPersonalInformation(&head);
			break;
		case 4:
			//(4) 선택시,개별 신상 정보 삭제 
			deletePersonalInformation(&head);
			break;
		case 5:
			//(5) 선택시, 프로그램 종료
			printf("[프로그램 종료]\n");
			return 0;
		}
	}
	return 0;
}