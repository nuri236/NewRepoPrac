//��Ʈ��ũ ���α׷��� ���� 1
//Ŭ���̾�Ʈ ȭ�� ����
//�л��� �����

#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <string.h>  
#include <stdlib.h> 
#include <Windows.h>

#define MAX_AGE 130	//�Է� ���� �ִ� ���� 130
#define MIN_AGE 0	//�Է� ���� �ּ� ���� 0

typedef struct node {
	struct node* next;

	char name[10];	//�̸� ����
	char phone[20];	//����ó ����
	int age;		//���� ����
	char gender;	//���� ����
}node;

//�޴� ��� �Լ� 
int printMenu() {
	int num;	//������ ��ȣ ����

	printf("\n[�޴�]\n");
	printf("(1) ���� �Ż� ���� �Է�\n");
	printf("(2) ��ü �Ż� ���� ���\n");
	printf("(3) ���� �Ż� ���� ��ȸ\n");
	printf("(4) ���� �Ż� ���� ����\n");
	printf("(5) ���α׷� ����\n");
	printf("��ȣ ���� : ");
	scanf("%d", &num);

	return num;
}

//���� �Ż� ���� �Է� �Լ�
void insertPersonalInformation(node** head)
{
	printf("[���� �Ż� ���� �Է�]\n");

	// �� ��� ���� �� �ʱ�ȭ
	node* newNode = (node*)malloc(sizeof(node));
	newNode->next = NULL;

	//������ �Է�
	printf("�̸� : ");
	scanf("%s", &newNode->name);
	printf("����ó(000-0000-0000) : ");
	scanf("%s", newNode->phone);

	do
	{
		printf("����(M/F) : ");
		char gender;
		scanf(" %c", &gender);
		if (gender == 'M' || gender == 'F') {
			newNode->gender = gender;
			break;
		}
		else
			printf("[�߸��� �Է��Դϴ�.]\n");
	} while (TRUE);

	do
	{
		printf("���� : ");
		int age;
		scanf("%d", &age);
		if (age < MAX_AGE && age > MIN_AGE) {
			newNode->age = age;
			break;
		}
		else
			printf("[�߸��� �Է��Դϴ�.]\n");
	} while (TRUE);

	//ù ����� ��� ��� ��尡 ����
	if (*head == NULL) {
		*head = newNode;
	}
	//ù ��尡 �ƴ� ���, ������ ��� �ڿ� ����
	else {
		node* temp = (node*)malloc(sizeof(node));
		temp = *head;

		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
}

//��ü �Ż� ���� ��� �Լ�
void printallinformation(node** head) {
	int numT = 0;						//�ο��� Ȯ�� ����
	int numF = 0, numM = 0;				//���� �ο��� ����
	int ageY = MAX_AGE + 1, ageO = MIN_AGE - 1;		//������, �ְ�� ����

	node* curr = (node*)malloc(sizeof(node));
	curr = *head;

	if (curr == NULL) {
		printf("[�Էµ� ������ �����ϴ�.] \n");
		return;
	}

	printf("[��ü �Ż� ���� ���]\n");
	printf("%-10s %-20s %-6s %-6s\n", "�̸�", "����ó", "����", "����");
	printf("-------------------------------------------------\n");

	// �����Ͱ� null�� �ƴ� ������ ��� �ݺ�
	while (curr != NULL)
	{
		numT += 1;
		if (curr->gender == 'F')
			numF += 1;
		if (curr->age > ageO)
			ageO = curr->age;
		if (curr->age < ageY)
			ageY = curr->age;

		printf("%-10s ", curr->name);
		printf("%-20s ", curr->phone);
		printf("%-6c ", curr->gender);
		printf("%-6d", curr->age);
		printf("\n");

		// �����Ϳ� ���� ����� �ּ� ����
		curr = curr->next;
	}
	printf("\n[��Ÿ ����]\n");
	printf("�� �ο� : %d\n", numT);
	printf("���� : %d\n", numM = numT - numF);
	printf("���� : %d\n", numF);
	printf("�ְ�� : %d\n", ageO);
	printf("������ : %d\n", ageY);
}

//���� �Ż� ���� ���� �Լ�
void deletePersonalInformation(node** head) {
	char name[10];		//������ �̸� ����
	char YorN;		//���� ���� Ȯ�� ����
	int count = 0;		//������ �̸��� �ִ��� Ȯ���� ����

	node* curr = (node*)malloc(sizeof(node));
	curr = *head;

	//����� ��尡 ���� ��� ��ȯ
	if (curr == NULL) {
		printf("[�Էµ� ������ �����ϴ�.] \n");
		return;
	}
	//����� ��尡 ���� ��� ����
	else {

		//������ �̸� �Է� ����
		printf("[���� �Ż� ���� ����]\n");
		printf("������ �̸� �Է� : ");
		scanf("%s", &name);

		while (TRUE) {

			//�Է¹��� �̸��� ���� ��尡 ������ ���� ���� ����
			if (strcmp(name, curr->name) == 0) {
				count += 1;

				printf("\n�̸�: %-10s", curr->name);
				printf("\n����ó : %-20s", curr->phone);
				printf("\n���� : %-6c", curr->gender);
				printf("\n���� : %-6d", curr->age);
				printf("\n�����Ͻðڽ��ϱ�? (Y/N) : ");

				//YorN �Է¹ޱ�
				do {
					YorN;
					scanf(" %c", &YorN);

					if (YorN == 'Y' || YorN == 'N') {
						break;
					}
					else {
						printf("\n[�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.]\n");
					}
				} while (TRUE);

				//������ ������ ���
				if (YorN == 'Y') {

					//ù ��带 ������ ���
					if ((*head) == curr) {
						(*head) = curr->next;
						curr = (*head);

						printf("\n[������ �Ϸ�Ǿ����ϴ�.]\n\n");
						continue;

					}
					//�ι�° �̻��� ��带 ������ ���
					else {
						node* pre = (node*)malloc(sizeof(node));
						pre = *head;

						//pre ����� next �����Ͱ� curr�� ����
						while (pre->next != curr) {
							pre = pre->next;
						}

						pre->next = curr->next;
						curr = pre;

						printf("\n[������ �Ϸ�Ǿ����ϴ�.]\n\n");
					}
				}
				//������ ����� ���, �״�� �н�
				else if (YorN == 'N') {
					printf("\n[������ ��ҵǾ����ϴ�.]\n");
				}
			}

			//���� ����� ���� ��尡 NULL�̸� ����, �ƴϸ� �ݺ�
			if (curr->next == NULL) {

				if (count == 0) {
					printf("\n[%s�� ������ �����ϴ�.]\n", name);

				}

				printf("\n[������ �����մϴ�.]\n");
				return;
			}
			else { curr = curr->next; }
		}
	}
}

//���� �Ż� ���� ��ȸ �Լ�
void searchPersonalInformation(node** head) {
	char name[10];	//������ �̸� ����
	int count = 0;	//���� ���� Ȯ�� ����

	node* curr = (node*)malloc(sizeof(node));
	curr = *head;

	printf("\n[���� �Ż� ���� ��ȸ]\n");
	printf("��ȸ�� �̸� : ");
	scanf("%s", name);

	printf("\n[���� �Ż� ���� ���]\n");
	printf("\n%-10s %-20s %-6s %-6s \n", "�̸�", "����ó", "����", "����");
	printf("-------------------------------------------------\n");

	// �����Ͱ� null�� �ƴ� ������ ��� �ݺ�
	while (curr != NULL)
	{
		//��ǥ�� ã���� ���
		if (strcmp(curr->name, name) == 0) {
			printf("%-10s ", curr->name);
			printf("%-20s ", curr->phone);
			printf("%-6c ", curr->gender);
			printf("%-6d\n", curr->age);

			count += 1;
		}
		curr = curr->next;
	}

	//��ǥ�� ã�� ������ �� ���
	if (count == 0) {
		printf("\n[%s�� ������ �����ϴ�.]\n", name);
	}

	return;
}

int main() {

	node* head = NULL;	//��� ��� �ʱ�ȭ

	while (TRUE) {
		int num = printMenu();	//�޴� ��� �Լ�
		system("clear");		//ȭ�� �ʱ�ȭ

		switch (num) {
		case 1:
			//(1) ���ý�, ���� �Ż� ���� �Է�
			insertPersonalInformation(&head);
			break;
		case 2:
			//(2) ���ý�,��ü �Ż� ���� ��� 
			printallinformation(&head);
			break;
		case 3:
			//(3) ���ý�,���� �Ż� ���� ��ȸ 
			searchPersonalInformation(&head);
			break;
		case 4:
			//(4) ���ý�,���� �Ż� ���� ���� 
			deletePersonalInformation(&head);
			break;
		case 5:
			//(5) ���ý�, ���α׷� ����
			printf("[���α׷� ����]\n");
			return 0;
		}
	}
	return 0;
}