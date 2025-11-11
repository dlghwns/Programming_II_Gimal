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
    int x = 35, y = 5;
    char id[100], pw[100];
    int idx;
    char c;

    // 화면 그리기
    gotoxy(x, y++);
    printf("┌──────────────────────────────────────────┐");
    for (int i = 0; i < 18; i++) {
        gotoxy(x, y++);
        printf("│                                          │");
    }
    gotoxy(x, y++);
    printf("└──────────────────────────────────────────┘");

    gotoxy(x + 2, 23); printf("돌아가기");
    gotoxy(x + 16, 6);  printf("☆  로그인 ☆");

    gotoxy(x + 5, 11); printf("아이디 : ");
    gotoxy(x + 5, 14); printf("비밀번호 : ");

    // 아이디 입력
    disable_mouse_input();
    gotoxy(x + 14, 11);
    idx = 0;
    while ((c = _getch()) != '\r') {
        if (c == '\b' && idx > 0) { idx--; printf("\b \b"); }
        else if (idx < 99 && c != '\b') { id[idx++] = c; putchar(c); }
    }
    id[idx] = '\0';

    // 비밀번호 입력
    gotoxy(x + 16, 14);
    idx = 0;
    while ((c = _getch()) != '\r') {
        if (c == '\b' && idx > 0) { idx--; printf("\b \b"); }
        else if (idx < 99 && c != '\b') { pw[idx++] = c; putchar('*'); }
    }
    pw[idx] = '\0';

    check_login(id, pw);

    // 돌아가기 버튼 감지
    enable_mouse_input();
    INPUT_RECORD rec;
    DWORD read;
    while (1) {
        ReadConsoleInput(hInput, &rec, 1, &read);
        if (rec.EventType == MOUSE_EVENT &&
            rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            COORD pos = rec.Event.MouseEvent.dwMousePosition;
            if ((pos.X >= x + 2 && pos.X <= x + 10) && (pos.Y == 23)) {
                show_menu();
                break;
            }
        }
    }
}



void register_menu()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    disable_mouse_input();

    int x = 35, y = 5;
    char id[100], id_c[100], pw[100];
    char c;
    int idx;

    while (1) {  // 재시도 루프 시작
        CLS;

        // 화면 그리기
        gotoxy(x, y++);
        printf("┌──────────────────────────────────────────┐");
        for (int i = 0; i < 18; i++) {
            gotoxy(x, y++);
            printf("│                                          │");
        }
        gotoxy(x, y++);
        printf("└──────────────────────────────────────────┘");
        gotoxy(x + 2, 23); printf("돌아가기");
        gotoxy(x + 16, 6); printf("☆  회원가입 ☆");

        gotoxy(x + 5, 11); printf("아이디 : ");
        gotoxy(x + 5, 14); printf("아이디 확인 : ");
        gotoxy(x + 5, 17); printf("비밀번호 : ");

        // 아이디 입력
        idx = 0;
        gotoxy(x + 14, 11);
        while ((c = _getch()) != '\r') {
            if (c == '\b' && idx > 0) { idx--; printf("\b \b"); }
            else if (idx < 99 && c != '\b') { id[idx++] = c; putchar(c); }
        }
        id[idx] = '\0';

        // 아이디 확인 입력
        idx = 0;
        gotoxy(x + 19, 14);
        while ((c = _getch()) != '\r') {
            if (c == '\b' && idx > 0) { idx--; printf("\b \b"); }
            else if (idx < 99 && c != '\b') { id_c[idx++] = c; putchar(c); }
        }
        id_c[idx] = '\0';

        // 비밀번호 입력
        idx = 0;
        gotoxy(x + 16, 17);
        while ((c = _getch()) != '\r') {
            if (c == '\b' && idx > 0) { idx--; printf("\b \b"); }
            else if (idx < 99 && c != '\b') { pw[idx++] = c; putchar('*'); }
        }
        pw[idx] = '\0';

        // 아이디 확인
        if (strcmp(id, id_c) != 0) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            gotoxy(x + 9, 20); printf("아이디가 일치하지 않습니다.");
            gotoxy(x + 13, 21); printf("다시 시도해주세요.");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            PAUSE;

            y = 5;  // 화면 초기 y 좌표 재설정
            continue;  // 재귀 대신 루프 반복
        }

        // 일치하면 등록 처리 후 종료
        check_register(id, pw);
        break;
    }
}




void check_login(char id[], char pw[])
{
    gotoxy(10, 100);
    printf("%s %s", id, pw);
}


void check_register(char id[], char pw[])
{
    gotoxy(10, 100);
    printf("%s %s", id, pw);
}   