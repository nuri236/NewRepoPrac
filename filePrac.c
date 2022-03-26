//파일 입출력 연습

//파일에 데이터 저장, 불러오기
//fputs, fgets

//비밀번호 입력받음
//맞는 경우, 비밀 일기 읽어와서 보기 & 추가 작성
//틀린 경우, 경고 메세지 & 종료

//비밀번호 asdfasdf

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>


#define MAX 10000

int main(void) {

    char line[MAX];  //파일에서 가져온 내용 저장
    char contents[MAX];  //파일에 저장할 내용 저장
    char password[20];  //비밀번호 입력
    char c; //비밀번호 마스킹용(*)

    printf("[비밀일기 시작]\n[비밀번호를 입력하세요 : ");

    int i = 0;
    while (1) {
        c = _getch();   //한 글자씩 읽기
        if (c == 13) {  //Enter(13) 입력 -> 입력 종료
            password[i] = '\0'; //\0 : 문자열 끝
            break;
        }
        else {
            printf("*");    //입력되는 숫자 대신 * 표시
            password[i] = c;
        }
        i++;
    }
    printf("]\n");

    printf("[비밀번호 확인중]\n");
    if (strcmp(password, "asdfasdf") == 0) {  //비밀번호 일치
        printf("[비밀번호 확인 완료]\n");

        const char* fileName = "c:\\secret_diary.txt";
        //로컬디스크 c에 접근할 권한 없으면 실행 안됨 -> 관리자 권한으로 실행

        FILE* file = fopen(fileName, "a+b");
        //a+ : 파일이 없으면 생성, 있으면 append
        //w : 쓰기 모드       r : 읽기 모드         a : 추가 모드
        //+ : 읽기, 쓰기 둘 다 
        //b : 바이너리 모드   t : 텍스트 모드

        if (file == NULL) {
            printf("[파일 열기 실패]\n");
            return 1;
        }

        while (fgets(line, MAX, file) != NULL) {
            printf("%s \n", line);
        }

        printf("[추가 내용 입력 (종료시 'exit' 입력)]\n\n");

        while (1) {
            scanf("%[^\n]", contents);  //줄바꿈(\n) 나올 때까지 읽어들임(한 문장)
            getchar();  //Flush 처리 (\n)

            if (strcmp(contents, "exit") == 0) {
                printf("\n[입력을 종료합니다.] \n\n");
                break;
            }

            fputs(contents, file);
            fputs("\n", file);  //getchar()로 \n 처리했으므로 추가
        }
        fclose(file);
    }
    else {  //비밀번호 불일치
        printf("[비밀번호 틀림]\n");
    }

    return 0;
}
