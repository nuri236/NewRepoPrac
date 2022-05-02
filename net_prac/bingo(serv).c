//네트워크 연습
//빙고 게임
//리눅스 기반

//서버측
//클라이언트와 연결되면 빙고 게임 시작
//클라이언트에게 번호 받으면 빙고판 수정
//사용자에게 번호 입력 받아서 빙고판 수정, 클라이언트로 전송
//5 빙고 완성하면 종료

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define Q_SIZE 5  //클라이언트 연결 요청 대기 큐의 크기 
#define BUF_SIZE 1024  //한 번에 전송할 데이터 최대 길이 
#define COL 5	//빙고판 가로행
#define ROW 5	//빙고판 세로열
#define true 1	
#define false 0

void error_handling(char* message);
void initArray(int(*array)[COL]);	//빙고판 초기화 함수
void suffleArray();	//빙고판 랜덤하게 섞는 함수
int getEmptyposition();	//빙고판 중 입력되지 않은 자리 반환하는 함수
int convertPointX(int x);	//받은 숫자가 몇 행인지 반환하는 함수
int convertPointY(int y);	//받은 숫자가 몇 열인지 반환하는 함수
void printArray(int(*array)[COL]);	//빙고판 출력 함수
int getNumber();	//사용자에게 번호를 입력받아 빙고판을 수정하는 함수
void findNumber(int num);	//상대방에게 번호를 받아 빙고판을 수정하는 함수
int checkBingo();	//총 빙고수 반환 함수
int checkBingo_col();	//가로 빙고 반환수 함수
int checkBingo_row();	//세로 빙고 반환수 함수
int checkBingo_dig_1();	//대각선 빙고 함수(역슬래시 \)
int checkBingo_dig_2();	//대각선 빙고 함수(슬래시 /)
int isCompleated(int bingoCounter, int sock, char* message);	//5 빙고가 완성됐는지 확인하는 함수

int numArray[COL][ROW];	//숫자가 입력되는 빙고판
int checkArray[COL][ROW];	//번호 선택 여부 확인용 배열

int main(int argc, char* argv[]) {

	int serv_sock;  //서버 파일 디스크립터
	int clnt_sock;  //클라이언트 파일 디스크립터
	char message[BUF_SIZE];

	struct sockaddr_in serv_addr;  //서버 주소 정보
	struct sockaddr_in clnt_addr;  //클라이언트 주소 정보
	socklen_t clnt_addr_size;  //클라이언트 주소 정보의 크기

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

	//서버 소켓과 주소 정보 연결, 성공시 0, 실패시 -1
	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("bind() error");
	}

	//연결 요청 대기 상태, 성공시 0, 실패시 -1
	if (listen(serv_sock, Q_SIZE) == -1) {
		error_handling("listen() error");
	}

	clnt_addr_size = sizeof(clnt_addr);

	for (int i = 0; i < Q_SIZE; i++) {
		//연결 요청 수락, 데이터 전송용 소켓 생성, 성공시 파일 디스크립터, 실패시 -1
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

		if (clnt_sock == -1) {
			error_handling("accept() error");
		}
		else {
			printf("Connected clinent %d \n", i + 1);
		}


		//빙고 시작

		int bingoCounter = 0;	//빙고 개수 
		int num;	//선택할 번호

		srand((unsigned int)(time(NULL) + 1));
		initArray(numArray);	//빙고판 초기화
		initArray(checkArray);	//선택한 번호 확인용 배열 초기화
		suffleArray();	//빙고판 랜덤하게 설정
		printArray(numArray);	//빙고판 출력

		while (1) {

			read(clnt_sock, message, sizeof(message));  //서버로부터 데이터 전송받아서 message에 저장

			//클라이언트가 난 끝났다 신호하면 종료
			//아니면 빙고판 수정
			if (message[0] == '0') {
				printf("****** 상대방 5 빙고 완성 ******\n");
				printf("************ 종료 **************\n");
				break;
			}
			else if (message[0] == 'q') {
				printf("****** 상대방 탈주 ******\n");
				printf("************ 종료 **************\n");
				break;
			}
			else {
				num = (int)message[0];
				findNumber(num);
			}


			printArray(numArray);
			bingoCounter = checkBingo();	//빙고 개수 

			//5 빙고 완성시 종료 
			if (isCompleated(bingoCounter, clnt_sock, message) == 1)
				break;

			num = getNumber(); //빙고판에 넣을 숫자 입력

			//긴급 종료
			if (num == -1) {
				printf("긴급 종료");
				message[0] = 'q';
				write(clnt_sock, message, clnt_addr_size);
				return 0;
			}


			printArray(numArray);
			bingoCounter = checkBingo();

			//5 빙고 완성시 종료 
			//아니면 입력한 번호 클라이언트에게 전송
			if (isCompleated(bingoCounter, clnt_sock, message) == 1)
				break;
			else {
				message[0] = (char)num;
				message[1] = '\0';
				write(clnt_sock, message, clnt_addr_size);
			}

		}

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

//빙고판 초기화 함수
void initArray(int(*array)[COL])
{
	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			array[i][j] = -1;
		}
	}
}

//빙고판 랜덤하게 섞는 함수
void suffleArray()
{
	int num = 1;

	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			int randPosition = getEmptyposition();
			int x = convertPointX(randPosition);
			int y = convertPointY(randPosition);

			numArray[x][y] = num;
			num++;
		}
	}

}

//빙고판 중 입력되지 않은 자리 반환하는 함수
int getEmptyposition()
{

	while (true)
	{
		int randPosition = rand() % 25;	//0~24
		int x = convertPointX(randPosition);
		int y = convertPointY(randPosition);

		if (numArray[x][y] == -1) {
			return randPosition;
		}
	}
}

//받은 숫자가 몇 행인지 반환하는 함수
int convertPointX(int x)
{
	return x / COL;
}

//받은 숫자가 몇 열인지 반환하는 함수
int convertPointY(int y)
{
	return y % ROW;
}

//빙고판 출력 함수
void printArray(int(*array)[COL])
{
	printf("\n");

	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			if (checkArray[i][j] == -1)
				printf("%4d", array[i][j]);
			else
				printf("%4c", '*');
		}
		printf("\n");
	}
	printf("\n");
}

//사용자에게 번호를 입력받아 빙고판을 수정하는 함수
int getNumber()
{
	int num;
	int x, y;

	while (1) {

		printf("[(1 ~ 25) 숫자를 입력하세요. (0 : 종료)] : ");
		scanf("%d", &num);	// 1~25

		//긴급 종료를 위한 반환
		if (num == 0)
			return -1;


		//입력된 숫자가 범위를 벗어났을 때
		if (num < 1 || num > 25) {
			printf("\n[잘못된 범위의 숫자입니다.]\n");
			continue;
		}

		//입력된 숫자와 같은 숫자를 가진 배열의 좌표 찾기
		for (int i = 0; i < COL; i++) {
			for (int j = 0; j < ROW; j++) {
				if (numArray[i][j] == num) {
					x = i;
					y = j;
				}
			}
		}

		//이미 입력한 숫자였을 때
		if (checkArray[x][y] == 0) {
			printf("[이미 입력된 숫자입니다.]\n");
			getNumber();
		}

		checkArray[x][y] = 0;

		return num;
	}
}

//상대방에게 번호를 받아 빙고판을 수정하는 함수
void findNumber(int num)
{
	int x, y;

	printf("[상대방 선택 ] : %d\n", num);

	//입력된 숫자와 같은 숫자를 가진 배열의 좌표 찾기
	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			if (numArray[i][j] == num) {
				x = i;
				y = j;
			}
		}
	}

	checkArray[x][y] = 0;
}

//총 빙고수 반환 함수
int checkBingo()
{
	int bingoCounter = 0;

	bingoCounter += checkBingo_col();
	bingoCounter += checkBingo_row();
	bingoCounter += checkBingo_dig_1();
	bingoCounter += checkBingo_dig_2();

	printf("[%d 빙고]\n\n", bingoCounter);

	return bingoCounter;
}

//가로 빙고 반환수 함수
int checkBingo_col()
{
	int bingo = false;
	int bingoCounter = 0;

	for (int i = 0; i < COL; i++) {

		bingo = true;

		for (int j = 0; j < ROW; j++) {
			if (checkArray[i][j] != 0) {
				bingo = false;
			}
		}

		if (bingo == true)
			bingoCounter++;
	}

	return bingoCounter;
}

//세로 빙고 반환수 함수
int checkBingo_row()
{
	int bingo = false;
	int bingoCounter = 0;

	for (int j = 0; j < ROW; j++) {

		bingo = true;

		for (int i = 0; i < COL; i++) {
			if (checkArray[i][j] != 0) {
				bingo = false;
			}
		}

		if (bingo == true)
			bingoCounter++;
	}

	return bingoCounter;
}

//대각선 빙고 함수(역슬래시 \)
int checkBingo_dig_1()
{
	int bingo = true;

	for (int i = 0; i < COL; i++) {
		if (checkArray[i][i] != 0)
			bingo = false;
	}

	return bingo;
}

//대각선 빙고 함수(슬래시 /)
int checkBingo_dig_2()
{
	int bingo = true;

	for (int i = 0; i < COL; i++) {
		if (checkArray[i][(4 - i)] != 0)
			bingo = false;
	}

	return bingo;
}

//5 빙고가 완성됐는지 확인하는 함수
int isCompleated(int bingoCounter, int sock, char* message)
{

	//5 빙고 완성시 클라이언트로 난 끝났다 신호 전송하고 종료
	if (bingoCounter > 4) {
		message[0] = '0';
		message[1] = '\0';

		write(sock, message, strlen(message));
		printf("******** 5 빙고 완성 **********\n");
		printf("************ 종료 **************\n");
		return 1;
	}
	else
		return 0;
}