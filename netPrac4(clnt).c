//네트워크 프로그래밍 연습
//데이터 전송 연습
//리눅스 기반

//클라이언트측
//서버에 점수(국, 영, 수) 전송, 등급 받아서 출력

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024  //한 번에 전송할 데이터 최대 길이 

void error_handling(char* message);

int main(int argc, char* argv[]) {

    int sock;  //클라이언트 소켓의 파일 디스크립터 저장
    char* class[3] = { "국어", "영어", "수학" };  //과목 이름 배열

    struct sockaddr_in serv_addr;  //서버 주소 정보
    char message[BUF_SIZE];  //전달받은 데이터 저장
    int str_len;  //전달받을 데이터 길이 저장

    if (argc != 3) {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);  //프로그램 실행시 IP 주소, PORT 번호 없으면 출력
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);  //클라이언트 소켓 생성, 성공시 파일 디스크립터, 실패시 -1
    if (sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));  //주소 정보 구조체 0으로 초기화
    serv_addr.sin_family = AF_INET;  //주소체계 저장
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  //IP 정보 저장, 서버 컴퓨터의 IP
    serv_addr.sin_port = htons(atoi(argv[2]));  //PORT 번호 저장, 서버 컴퓨터의 PORT

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {  //서버 소켓과 주소 정보 연결, 성공시 0, 실패시 -1
        error_handling("connect() error");
    }
    else {
        printf("Connected...\n");  //서버와 연결 후 대기중
    }

    for (int i; i < 3; i++) {  //과목별 점수 입력
        printf("%s 점수 : ", class[i]);
        fgets(message, BUF_SIZE, stdin);

        write(sock, message, strlen(message));  //서버로 점수 전송
    }

    str_len = read(sock, message, sizeof(message));  //서버로부터 등급 수신, 문자열 길이 반환
    printf("등급 : %s ", message);

    close(sock);  //클라이언트 소켓 제거

    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}