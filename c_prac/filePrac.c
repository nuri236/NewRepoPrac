//���� ����� ����

//���Ͽ� ������ ����, �ҷ�����
//fputs, fgets

//��й�ȣ �Է¹���
//�´� ���, ��� �ϱ� �о�ͼ� ���� & �߰� �ۼ�
//Ʋ�� ���, ��� �޼��� & ����

//��й�ȣ asdfasdf

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>


#define MAX 10000

int main(void) {

    char line[MAX];  //���Ͽ��� ������ ���� ����
    char contents[MAX];  //���Ͽ� ������ ���� ����
    char password[20];  //��й�ȣ �Է�
    char c; //��й�ȣ ����ŷ��(*)

    printf("[����ϱ� ����]\n[��й�ȣ�� �Է��ϼ��� : ");

    int i = 0;
    while (1) {
        c = _getch();   //�� ���ھ� �б�
        if (c == 13) {  //Enter(13) �Է� -> �Է� ����
            password[i] = '\0'; //\0 : ���ڿ� ��
            break;
        }
        else {
            printf("*");    //�ԷµǴ� ���� ��� * ǥ��
            password[i] = c;
        }
        i++;
    }
    printf("]\n");

    printf("[��й�ȣ Ȯ����]\n");
    if (strcmp(password, "asdfasdf") == 0) {  //��й�ȣ ��ġ
        printf("[��й�ȣ Ȯ�� �Ϸ�]\n");

        const char* fileName = "c:\\secret_diary.txt";
        //���õ�ũ c�� ������ ���� ������ ���� �ȵ� -> ������ �������� ����

        FILE* file = fopen(fileName, "a+b");
        //a+ : ������ ������ ����, ������ append
        //w : ���� ���       r : �б� ���         a : �߰� ���
        //+ : �б�, ���� �� �� 
        //b : ���̳ʸ� ���   t : �ؽ�Ʈ ���

        if (file == NULL) {
            printf("[���� ���� ����]\n");
            return 1;
        }

        while (fgets(line, MAX, file) != NULL) {
            printf("%s \n", line);
        }

        printf("[�߰� ���� �Է� (����� 'exit' �Է�)]\n\n");

        while (1) {
            scanf("%[^\n]", contents);  //�ٹٲ�(\n) ���� ������ �о����(�� ����)
            getchar();  //Flush ó�� (\n)

            if (strcmp(contents, "exit") == 0) {
                printf("\n[�Է��� �����մϴ�.] \n\n");
                break;
            }

            fputs(contents, file);
            fputs("\n", file);  //getchar()�� \n ó�������Ƿ� �߰�
        }
        fclose(file);
    }
    else {  //��й�ȣ ����ġ
        printf("[��й�ȣ Ʋ��]\n");
    }

    return 0;
}
