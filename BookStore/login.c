#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "fun.h"
#include "main.h"

#define CLS system("cls")
#define PAUSE system("pause>nul")
void check_login(char id[], char pw[]);
void check_register(char id[], char pw[]);



void login_menu()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    disable_mouse_input();

    int x = 35, y = 5;
    char id[100] = { 0 }, pw[100] = { 0 };
    int step = 0;   // 0 = ID 입력, 1 = PW 입력
    int idx = 0;
    char c;

    CLS;

    // 화면 그리기
    gotoxy(x, y++); printf("┌──────────────────────────────────────────┐");
    for (int i = 0; i < 18; i++) { gotoxy(x, y++); printf("│                                          │"); }
    gotoxy(x, y++); printf("└──────────────────────────────────────────┘");
    gotoxy(x + 2, 23); printf("돌아가기");
    gotoxy(x + 16, 6); printf("☆  로그인 ☆");
    gotoxy(x + 5, 11); printf("아이디 : ");
    gotoxy(x + 5, 14); printf("비밀번호 : ");

    gotoxy(x + 14, 11);

    enable_mouse_input();
    INPUT_RECORD rec;
    DWORD read;

    while (1) {
        // 키보드 처리
        if (_kbhit()) {
            c = _getch();
            if (c == '\r') {  // Enter
                if (step == 0) { step = 1; idx = 0; gotoxy(x + 16, 14); }
                else break; // 비밀번호 입력 완료
            }
            else if (c == '\b' && idx > 0) { idx--; printf("\b \b"); }
            else if (idx < 99 && c != '\b') {
                if (step == 0) { id[idx++] = c; putchar(c); }
                else { pw[idx++] = c; putchar('*'); }
            }
        }

        // 마우스 처리
        if (PeekConsoleInput(hInput, &rec, 1, &read) && read > 0) {
            ReadConsoleInput(hInput, &rec, 1, &read);
            if (rec.EventType == MOUSE_EVENT &&
                rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                COORD pos = rec.Event.MouseEvent.dwMousePosition;
                if ((pos.X >= x + 2 && pos.X <= x + 10) && (pos.Y == 23)) {
                    show_menu();  // 돌아가기
                    return;
                }
            }
        }

        Sleep(1); // CPU 과부하 방지
    }

    id[idx] = '\0';
    pw[idx] = '\0';
    check_login(id, pw);
}

void register_menu()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    disable_mouse_input();

    int x = 35, y = 5;
    char id[100] = { 0 }, id_c[100] = { 0 }, pw[100] = { 0 };
    int step = 0; // 0=ID,1=ID확인,2=PW
    int idx = 0;
    char c;

    CLS;

    // 화면 그리기
    gotoxy(x, y++); printf("┌──────────────────────────────────────────┐");
    for (int i = 0; i < 18; i++) { gotoxy(x, y++); printf("│                                          │"); }
    gotoxy(x, y++); printf("└──────────────────────────────────────────┘");
    gotoxy(x + 2, 23); printf("돌아가기");
    gotoxy(x + 16, 6); printf("☆  회원가입 ☆");
    gotoxy(x + 5, 11); printf("아이디 : ");
    gotoxy(x + 5, 14); printf("아이디 확인 : ");
    gotoxy(x + 5, 17); printf("비밀번호 : ");

    gotoxy(x + 14, 11);

    enable_mouse_input();
    INPUT_RECORD rec;
    DWORD read;

    while (1) {
        // 키보드 처리
        if (_kbhit()) {
            c = _getch();
            if (c == '\r') {  // Enter
                if (step == 0) { step = 1; idx = 0; gotoxy(x + 19, 14); }
                else if (step == 1) { step = 2; idx = 0; gotoxy(x + 16, 17); }
                else break; // 비밀번호 입력 완료
            }
            else if (c == '\b' && idx > 0) { idx--; printf("\b \b"); }
            else if (idx < 99 && c != '\b') {
                if (step == 0) { id[idx++] = c; putchar(c); }
                else if (step == 1) { id_c[idx++] = c; putchar(c); }
                else { pw[idx++] = c; putchar('*'); }
            }
        }

        // 마우스 처리
        if (PeekConsoleInput(hInput, &rec, 1, &read) && read > 0) {
            ReadConsoleInput(hInput, &rec, 1, &read);
            if (rec.EventType == MOUSE_EVENT &&
                rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                COORD pos = rec.Event.MouseEvent.dwMousePosition;
                if ((pos.X >= x + 2 && pos.X <= x + 10) && (pos.Y == 23)) {
                    show_menu();  // 돌아가기
                    return;
                }
            }
        }

        Sleep(1);
    }

    id[idx] = '\0';
    id_c[idx] = '\0';
    pw[idx] = '\0';

    if (strcmp(id, id_c) != 0) {
        gotoxy(x + 9, 20); printf("아이디가 일치하지 않습니다.");
        gotoxy(x + 13, 21); printf("다시 시도해주세요.");
        PAUSE;
        register_menu(); // 재시도
        return;
    }

    check_register(id, pw);
}



void check_login(char id[], char pw[])
{
    char path[MAX_PATH];
    sprintf(path, "%s\\SW_BOOKSTORE\\userdata.txt", getenv("APPDATA"));


	FILE* fp = fopen(path, "r");
    if (!fp) {
        printf("파일을 열 수 없습니다.\n");
        PAUSE;
        exit(100);
    }



    fclose(fp);
    printf("%s %s", id, pw);

}


void check_register(char id[], char pw[])
{

    char path[MAX_PATH];
    sprintf(path, "%s\\SW_BOOKSTORE\\userdata.txt", getenv("APPDATA"));


    FILE* fp = fopen(path, "a");
    if (!fp) {
        printf("파일을 열 수 없습니다.\n");
        PAUSE;
        exit(100);
    }
    else
    {
		int first_money = 100000;
        fprintf(fp, "%s %s %d", id, pw, first_money);


        fclose(fp);
    }




    printf("%s %s", id, pw);
}   