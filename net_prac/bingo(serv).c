//��Ʈ��ũ ����
//���� ����
//������ ���

//������
//Ŭ���̾�Ʈ�� ����Ǹ� ���� ���� ����
//Ŭ���̾�Ʈ���� ��ȣ ������ ������ ����
//����ڿ��� ��ȣ �Է� �޾Ƽ� ������ ����, Ŭ���̾�Ʈ�� ����
//5 ���� �ϼ��ϸ� ����

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define Q_SIZE 5  //Ŭ���̾�Ʈ ���� ��û ��� ť�� ũ�� 
#define BUF_SIZE 1024  //�� ���� ������ ������ �ִ� ���� 
#define COL 5	//������ ������
#define ROW 5	//������ ���ο�
#define true 1	
#define false 0

void error_handling(char* message);
void initArray(int(*array)[COL]);	//������ �ʱ�ȭ �Լ�
void suffleArray();	//������ �����ϰ� ���� �Լ�
int getEmptyposition();	//������ �� �Էµ��� ���� �ڸ� ��ȯ�ϴ� �Լ�
int convertPointX(int x);	//���� ���ڰ� �� ������ ��ȯ�ϴ� �Լ�
int convertPointY(int y);	//���� ���ڰ� �� ������ ��ȯ�ϴ� �Լ�
void printArray(int(*array)[COL]);	//������ ��� �Լ�
int getNumber();	//����ڿ��� ��ȣ�� �Է¹޾� �������� �����ϴ� �Լ�
void findNumber(int num);	//���濡�� ��ȣ�� �޾� �������� �����ϴ� �Լ�
int checkBingo();	//�� ����� ��ȯ �Լ�
int checkBingo_col();	//���� ���� ��ȯ�� �Լ�
int checkBingo_row();	//���� ���� ��ȯ�� �Լ�
int checkBingo_dig_1();	//�밢�� ���� �Լ�(�������� \)
int checkBingo_dig_2();	//�밢�� ���� �Լ�(������ /)
int isCompleated(int bingoCounter, int sock, char* message);	//5 ���� �ϼ��ƴ��� Ȯ���ϴ� �Լ�

int numArray[COL][ROW];	//���ڰ� �ԷµǴ� ������
int checkArray[COL][ROW];	//��ȣ ���� ���� Ȯ�ο� �迭

int main(int argc, char* argv[]) {

	int serv_sock;  //���� ���� ��ũ����
	int clnt_sock;  //Ŭ���̾�Ʈ ���� ��ũ����
	char message[BUF_SIZE];

	struct sockaddr_in serv_addr;  //���� �ּ� ����
	struct sockaddr_in clnt_addr;  //Ŭ���̾�Ʈ �ּ� ����
	socklen_t clnt_addr_size;  //Ŭ���̾�Ʈ �ּ� ������ ũ��

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

	//���� ���ϰ� �ּ� ���� ����, ������ 0, ���н� -1
	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handling("bind() error");
	}

	//���� ��û ��� ����, ������ 0, ���н� -1
	if (listen(serv_sock, Q_SIZE) == -1) {
		error_handling("listen() error");
	}

	clnt_addr_size = sizeof(clnt_addr);

	for (int i = 0; i < Q_SIZE; i++) {
		//���� ��û ����, ������ ���ۿ� ���� ����, ������ ���� ��ũ����, ���н� -1
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

		if (clnt_sock == -1) {
			error_handling("accept() error");
		}
		else {
			printf("Connected clinent %d \n", i + 1);
		}


		//���� ����

		int bingoCounter = 0;	//���� ���� 
		int num;	//������ ��ȣ

		srand((unsigned int)(time(NULL) + 1));
		initArray(numArray);	//������ �ʱ�ȭ
		initArray(checkArray);	//������ ��ȣ Ȯ�ο� �迭 �ʱ�ȭ
		suffleArray();	//������ �����ϰ� ����
		printArray(numArray);	//������ ���

		while (1) {

			read(clnt_sock, message, sizeof(message));  //�����κ��� ������ ���۹޾Ƽ� message�� ����

			//Ŭ���̾�Ʈ�� �� ������ ��ȣ�ϸ� ����
			//�ƴϸ� ������ ����
			if (message[0] == '0') {
				printf("****** ���� 5 ���� �ϼ� ******\n");
				printf("************ ���� **************\n");
				break;
			}
			else if (message[0] == 'q') {
				printf("****** ���� Ż�� ******\n");
				printf("************ ���� **************\n");
				break;
			}
			else {
				num = (int)message[0];
				findNumber(num);
			}


			printArray(numArray);
			bingoCounter = checkBingo();	//���� ���� 

			//5 ���� �ϼ��� ���� 
			if (isCompleated(bingoCounter, clnt_sock, message) == 1)
				break;

			num = getNumber(); //�����ǿ� ���� ���� �Է�

			//��� ����
			if (num == -1) {
				printf("��� ����");
				message[0] = 'q';
				write(clnt_sock, message, clnt_addr_size);
				return 0;
			}


			printArray(numArray);
			bingoCounter = checkBingo();

			//5 ���� �ϼ��� ���� 
			//�ƴϸ� �Է��� ��ȣ Ŭ���̾�Ʈ���� ����
			if (isCompleated(bingoCounter, clnt_sock, message) == 1)
				break;
			else {
				message[0] = (char)num;
				message[1] = '\0';
				write(clnt_sock, message, clnt_addr_size);
			}

		}

		close(clnt_sock);  //������ ���ۿ� ���� ����
	}

	close(serv_sock);  //���� ���� ����

	return 0;
}

void error_handling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

//������ �ʱ�ȭ �Լ�
void initArray(int(*array)[COL])
{
	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			array[i][j] = -1;
		}
	}
}

//������ �����ϰ� ���� �Լ�
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

//������ �� �Էµ��� ���� �ڸ� ��ȯ�ϴ� �Լ�
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

//���� ���ڰ� �� ������ ��ȯ�ϴ� �Լ�
int convertPointX(int x)
{
	return x / COL;
}

//���� ���ڰ� �� ������ ��ȯ�ϴ� �Լ�
int convertPointY(int y)
{
	return y % ROW;
}

//������ ��� �Լ�
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

//����ڿ��� ��ȣ�� �Է¹޾� �������� �����ϴ� �Լ�
int getNumber()
{
	int num;
	int x, y;

	while (1) {

		printf("[(1 ~ 25) ���ڸ� �Է��ϼ���. (0 : ����)] : ");
		scanf("%d", &num);	// 1~25

		//��� ���Ḧ ���� ��ȯ
		if (num == 0)
			return -1;


		//�Էµ� ���ڰ� ������ ����� ��
		if (num < 1 || num > 25) {
			printf("\n[�߸��� ������ �����Դϴ�.]\n");
			continue;
		}

		//�Էµ� ���ڿ� ���� ���ڸ� ���� �迭�� ��ǥ ã��
		for (int i = 0; i < COL; i++) {
			for (int j = 0; j < ROW; j++) {
				if (numArray[i][j] == num) {
					x = i;
					y = j;
				}
			}
		}

		//�̹� �Է��� ���ڿ��� ��
		if (checkArray[x][y] == 0) {
			printf("[�̹� �Էµ� �����Դϴ�.]\n");
			getNumber();
		}

		checkArray[x][y] = 0;

		return num;
	}
}

//���濡�� ��ȣ�� �޾� �������� �����ϴ� �Լ�
void findNumber(int num)
{
	int x, y;

	printf("[���� ���� ] : %d\n", num);

	//�Էµ� ���ڿ� ���� ���ڸ� ���� �迭�� ��ǥ ã��
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

//�� ����� ��ȯ �Լ�
int checkBingo()
{
	int bingoCounter = 0;

	bingoCounter += checkBingo_col();
	bingoCounter += checkBingo_row();
	bingoCounter += checkBingo_dig_1();
	bingoCounter += checkBingo_dig_2();

	printf("[%d ����]\n\n", bingoCounter);

	return bingoCounter;
}

//���� ���� ��ȯ�� �Լ�
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

//���� ���� ��ȯ�� �Լ�
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

//�밢�� ���� �Լ�(�������� \)
int checkBingo_dig_1()
{
	int bingo = true;

	for (int i = 0; i < COL; i++) {
		if (checkArray[i][i] != 0)
			bingo = false;
	}

	return bingo;
}

//�밢�� ���� �Լ�(������ /)
int checkBingo_dig_2()
{
	int bingo = true;

	for (int i = 0; i < COL; i++) {
		if (checkArray[i][(4 - i)] != 0)
			bingo = false;
	}

	return bingo;
}

//5 ���� �ϼ��ƴ��� Ȯ���ϴ� �Լ�
int isCompleated(int bingoCounter, int sock, char* message)
{

	//5 ���� �ϼ��� Ŭ���̾�Ʈ�� �� ������ ��ȣ �����ϰ� ����
	if (bingoCounter > 4) {
		message[0] = '0';
		message[1] = '\0';

		write(sock, message, strlen(message));
		printf("******** 5 ���� �ϼ� **********\n");
		printf("************ ���� **************\n");
		return 1;
	}
	else
		return 0;
}