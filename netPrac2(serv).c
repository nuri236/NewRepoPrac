//��Ʈ��ũ ���α׷��� ����
//������ ���

//������
//Ŭ���̾�Ʈ�� ��û�� ������ "Hello World!" ���

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define Q_SIZE 5  //Ŭ���̾�Ʈ ���� ��û ��� ť�� ũ�� 

void error_handling(char* message);

int main(int argc, char* argv[]) {

    int serv_sock;  //���� ������ ���� ��ũ���� ����(Ŭ���̾�Ʈ ���ϰ� �����)
    int clnt_sock;  //accept()�� ��������� ������ ���� ��ũ���� ����(������ �ۼ��ſ�)

    struct sockaddr_in serv_addr;  //���� �ּ� ����
    struct sockaddr_in clnt_addr;  //Ŭ���̾�Ʈ �ּ� ����
    socklen_t clnt_addr_size;  //Ŭ���̾�Ʈ �ּ� ������ ũ��(accept()�� ����° �μ��� �������� �ƴ϶� �ּҰ��� �䱸)

    char message[] = "Hello World!";

    if (argc != 2) {
        printf("Usage : %s <PORT>\n", argv[0]);  //���α׷� ����� ��Ʈ���� ������ ���
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);  //���� ���� ����, ������ ���� ��ũ����, ���н� -1
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));  //�ּ� ���� ����ü 0���� �ʱ�ȭ
    serv_addr.sin_family = AF_INET;  //�ּ�ü�� ����
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //IP ���� ����, INADDR_ANY == �����ϴ� ��ǻ���� IP
    serv_addr.sin_port = htons(atoi(argv[1]));  //PORT ��ȣ ����

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {  //���� ���ϰ� �ּ� ���� ����, ������ 0, ���н� -1
        error_handling("bind() error");
    }

    if (listen(serv_sock, Q_SIZE) == -1) {  //���� ��û ��� ����, ������ 0, ���н� -1
        error_handling("listen() error");
    }

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);  //���� ��û ����, ������ ���ۿ� ���� ����, ������ ���� ��ũ����, ���н� -1
    if (clnt_sock == -1) {
        error_handling("listen() error");
    }

    write(clnt_sock, message, sizeof(message));  //Ŭ���̾�Ʈ�� ������ ����
    close(clnt_sock);  //������ ���ۿ� ���� ����
    close(serv_sock);  //���� ���� ����

    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


