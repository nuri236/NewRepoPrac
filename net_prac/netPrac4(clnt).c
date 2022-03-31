//��Ʈ��ũ ���α׷��� ����
//������ ���� ����
//������ ���

//Ŭ���̾�Ʈ��
//������ ����(��, ��, ��) ����, ��� �޾Ƽ� ���

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024  //�� ���� ������ ������ �ִ� ���� 

void error_handling(char* message);

int main(int argc, char* argv[]) {

    int sock;  //Ŭ���̾�Ʈ ������ ���� ��ũ���� ����
    char* class[3] = { "����", "����", "����" };  //���� �̸� �迭

    struct sockaddr_in serv_addr;  //���� �ּ� ����
    char message[BUF_SIZE];  //���޹��� ������ ����
    int str_len;  //���޹��� ������ ���� ����

    if (argc != 3) {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);  //���α׷� ����� IP �ּ�, PORT ��ȣ ������ ���
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);  //Ŭ���̾�Ʈ ���� ����, ������ ���� ��ũ����, ���н� -1
    if (sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));  //�ּ� ���� ����ü 0���� �ʱ�ȭ
    serv_addr.sin_family = AF_INET;  //�ּ�ü�� ����
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  //IP ���� ����, ���� ��ǻ���� IP
    serv_addr.sin_port = htons(atoi(argv[2]));  //PORT ��ȣ ����, ���� ��ǻ���� PORT

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {  //���� ���ϰ� �ּ� ���� ����, ������ 0, ���н� -1
        error_handling("connect() error");
    }
    else {
        printf("Connected...\n");  //������ ���� �� �����
    }

    for (int i; i < 3; i++) {  //���� ���� �Է�
        printf("%s ���� : ", class[i]);
        fgets(message, BUF_SIZE, stdin);

        write(sock, message, strlen(message));  //������ ���� ����
    }

    str_len = read(sock, message, sizeof(message));  //�����κ��� ��� ����, ���ڿ� ���� ��ȯ
    printf("��� : %s ", message);

    close(sock);  //Ŭ���̾�Ʈ ���� ����

    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}