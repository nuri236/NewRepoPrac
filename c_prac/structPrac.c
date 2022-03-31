//����ü ����

//5���� �����
//��� ����� ������ ����
//�ߺ� �߻� ����

//����� ����ü 
//�̸� ���� ���� Ű��Ⳮ�̵� 

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

void initCats();  //����� ���� �ʱ�ȭ
void printCat(int selected);  //���� ����� ���� ���
void printCollection();  //������ �ִ� ����� �̸��� ���
int checkCollection();  //��� ����̸� ������ �ִ��� Ȯ��



int main(void) {

    srand(time(NULL));

    initCats();

    while (1) {
        printf("�ƹ�Ű�� �����ּ���. \n");
        getchar();

        int selected = rand() % 5;  //0~4���� ���� ����
        printCat(selected);  //����� �̱� 
        collection[selected] = 1;  //���� ����� ó��
        printCollection(); //������ �ִ� ����� ��� ���

        if (checkCollection() == 1) {  //��� ����� ������ ����
            printf("��� ����̸� �����̽��ϴ�.");
            return 0;
        }
    }

    return 0;
}

void initCats() {
    cats[0].name = "�˵���";
    cats[0].age = 1;
    cats[0].character = "�¼�";
    cats[0].level = 2;

    cats[1].name = "�����";
    cats[1].age = 2;
    cats[1].character = "�糪��";
    cats[1].level = 4;

    cats[2].name = "�Ժ�";
    cats[2].age = 3;
    cats[2].character = "��";
    cats[2].level = 1;

    cats[3].name = "����";
    cats[3].age = 4;
    cats[3].character = "��";
    cats[3].level = 5;

    cats[4].name = "����";
    cats[4].age = 5;
    cats[4].character = "����";
    cats[4].level = 3;
}

void printCat(int selected) {

    printf("\n%s ����!!!\n", cats[selected].name);
    printf("���� : %d\n", cats[selected].age);
    printf("Ư¡ : %s\n", cats[selected].character);
    printf("���� : ");

    for (int i = 0; i < cats[selected].level; i++) {
        printf("%s", "��");
    }

    printf("\n\n");

}

void printCollection() {

    printf("���� ����� ��� : \n");

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