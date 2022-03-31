//구조체 연습

//5마리 고양이
//모든 고양이 모으면 종료
//중복 발생 가능

//고양이 구조체 
//이름 나이 성격 키우기난이도 

#include <stdio.h>
#include <time.h>

typedef struct {
    char* name;
    int age;
    char* character;
    int level;
}CAT;

int collection[5] = { 0 };
CAT cats[5];

void initCats();  //고양이 정보 초기화
void printCat(int selected);  //뽑은 고양이 정보 출력
void printCollection();  //가지고 있는 고양이 이름들 출력
int checkCollection();  //모든 고양이를 가지고 있는지 확인



int main(void) {

    srand(time(NULL));

    initCats();

    while (1) {
        printf("아무키나 눌러주세요. \n");
        getchar();

        int selected = rand() % 5;  //0~4까지 랜덤 숫자
        printCat(selected);  //고양이 뽑기 
        collection[selected] = 1;  //뽑은 고양이 처리
        printCollection(); //가지고 있는 고양이 목록 출력

        if (checkCollection() == 1) {  //모든 고양이 모으면 종료
            printf("모든 고양이를 모으셨습니다.");
            return 0;
        }
    }

    return 0;
}

void initCats() {
    cats[0].name = "검둥이";
    cats[0].age = 1;
    cats[0].character = "온순";
    cats[0].level = 2;

    cats[1].name = "흰둥이";
    cats[1].age = 2;
    cats[1].character = "사나움";
    cats[1].level = 4;

    cats[2].name = "먹보";
    cats[2].age = 3;
    cats[2].character = "뚱";
    cats[2].level = 1;

    cats[3].name = "나비";
    cats[3].age = 4;
    cats[3].character = "멍";
    cats[3].level = 5;

    cats[4].name = "딸기";
    cats[4].age = 5;
    cats[4].character = "졸림";
    cats[4].level = 3;
}

void printCat(int selected) {

    printf("\n%s 등장!!!\n", cats[selected].name);
    printf("나이 : %d\n", cats[selected].age);
    printf("특징 : %s\n", cats[selected].character);
    printf("레벨 : ");

    for (int i = 0; i < cats[selected].level; i++) {
        printf("%s", "☆");
    }

    printf("\n\n");

}

void printCollection() {

    printf("모은 고양이 목록 : \n");

    for (int i = 0; i < 5; i++) {
        if (collection[i] == 1) {
            printf("%s ", cats[i].name);
        }
    }
    printf("\n\n");

}

int checkCollection() {

    for (int i = 0; i < 5; i++) {
        if (collection[i] == 0) {
            return 0;
        }
    }

    return 1;
}