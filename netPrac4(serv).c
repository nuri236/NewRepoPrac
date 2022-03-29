//네트워크 프로그래밍 연습
//데이터 전송 연습
//리눅스 기반

//서버측
//클라이언트에게 점수(국, 영, 수) 받으면, 등급으로 계산 후 전송

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define Q_SIZE 5  //클라이언트 연결 요청 대기 큐의 크기 
#define BUF_SIZE 1024  //한 번에 전송할 데이터 최대 길이 

void error_handling(char* message);
char calculateGrade(int* score);  //과목 점수 배열을 받아서 등급으로 반환

int main(int argc, char* argv[]) {

    int serv_sock;  //서버 소켓의 파일 디스크립터 저장(클라이언트 소켓과 연결용)
    int clnt_sock;  //accept()로 만들어지는 소켓의 파일 디스크립터 저장(데이터 송수신용)
    char message[BUF_SIZE];
    int score[3];  //클라이언트에서 받은 점수를 담을 배열

    struct sockaddr_in serv_addr;  //서버 주소 정보
    struct sockaddr_in clnt_addr;  //클라이언트 주소 정보
    socklen_t clnt_addr_size;  //클라이언트 주소 정보의 크기(accept()의 세번째 인수로 정수값이 아니라 주소값을 요구)

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

    for (int i = 0; i < Q_SIZE; i++) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);  //연결 요청 수락, 데이터 전송용 소켓 생성, 성공시 파일 디스크립터, 실패시 -1

        if (clnt_sock == -1) {
            error_handling("accept() error");
        }
        else {
            printf("Connected clinent %d \n", i + 1);
        }

        for (int j = 0; j < 3; j++) {
            if ((clnt_addr_size = read(clnt_sock, message, BUF_SIZE)) != 0) {
                score[j] = atoi(message);  //클라이언트에서 받은 문자열 점수를 정수형으로 변환, 저장
            }
            else {
                printf("read() error");
            }
        }

        message[0] = calculateGrade(score);  //점수로 등급을 산출 후 반환
        message[1] = '\0';

        write(clnt_sock, message, clnt_addr_size);  //클라이언트로 등급 전송

        close(clnt_sock);  //데이터 전송용 소켓 제거
    }

    close(serv_sock);  //서버 소켓 제거

    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

char calculateGrade(int* score)
{
    int average;  //점수들의 평균을 저장할 변수
    char grade;  //산출한 등급 저장

    average = (score[0] + score[1] + score[2]) / 3;  //세 점수들의 평균

    if (average >= 90)  //평균 점수에 따라 학점 계산
        grade = 'A';
    else if (average >= 80)
        grade = 'B';
    else if (average >= 70)
        grade = 'C';
    else if (average >= 60)
        grade = 'D';
    else
        grade = 'F';

    return grade;
}