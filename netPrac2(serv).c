//네트워크 프로그래밍 연습
//리눅스 기반

//서버측
//클라이언트의 요청을 받으면 "Hello World!" 출력

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define Q_SIZE 5  //클라이언트 연결 요청 대기 큐의 크기 

void error_handling(char* message);

int main(int argc, char* argv[]) {

    int serv_sock;  //서버 소켓의 파일 디스크립터 저장(클라이언트 소켓과 연결용)
    int clnt_sock;  //accept()로 만들어지는 소켓의 파일 디스크립터 저장(데이터 송수신용)

    struct sockaddr_in serv_addr;  //서버 주소 정보
    struct sockaddr_in clnt_addr;  //클라이언트 주소 정보
    socklen_t clnt_addr_size;  //클라이언트 주소 정보의 크기(accept()의 세번째 인수로 정수값이 아니라 주소값을 요구)

    char message[] = "Hello World!";

    if (argc != 2) {
        printf("Usage : %s <PORT>\n", argv[0]);  //프로그램 실행시 포트값이 없으면 출력
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);  //서버 소켓 생성, 성공시 파일 디스크립터, 실패시 -1
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));  //주소 정보 구조체 0으로 초기화
    serv_addr.sin_family = AF_INET;  //주소체계 저장
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //IP 정보 저장, INADDR_ANY == 실행하는 컴퓨터의 IP
    serv_addr.sin_port = htons(atoi(argv[1]));  //PORT 번호 저장

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {  //서버 소켓과 주소 정보 연결, 성공시 0, 실패시 -1
        error_handling("bind() error");
    }

    if (listen(serv_sock, Q_SIZE) == -1) {  //연결 요청 대기 상태, 성공시 0, 실패시 -1
        error_handling("listen() error");
    }

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);  //연결 요청 수락, 데이터 전송용 소켓 생성, 성공시 파일 디스크립터, 실패시 -1
    if (clnt_sock == -1) {
        error_handling("listen() error");
    }

    write(clnt_sock, message, sizeof(message));  //클라이언트로 데이터 전송
    close(clnt_sock);  //데이터 전송용 소켓 제거
    close(serv_sock);  //서버 소켓 제거

    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


