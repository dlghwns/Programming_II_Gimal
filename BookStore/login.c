#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "fun.h"
#include "main.h"

#define CLS system("cls")

void login_menu()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    int x = 35, y = 5;
    char id[100];
	char pw[100];
    int idx = 0;
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

    gotoxy(x + 5, 11);
    printf("아이디 : ");
    gotoxy(x + 5, 14);
    printf("비밀번호 : ");

    gotoxy(x + 14, 11);
    //아이디 입력받기======================================================================
	disable_mouse_input();
    while ((c = _getch()) != '\r') {  // Enter 입력 시 종료
        if (c == '\b') {  // Backspace 처리
            if (idx > 0) {
                idx--;
                printf("\b \b");  // 콘솔에서 지우기
            }
        }
        else if (idx < 99) {
            id[idx++] = c;
            putchar(c);  // 화면에 바로 표시
        }
    }
    id[idx] = '\0';


	//비밀번호 입력받기======================================================================
    gotoxy(x + 16, 14);
    idx = 0;
    while ((c = _getch()) != '\r') {
        if (c == '\b') {
            if (idx > 0) {
                idx--;
                printf("\b \b");
            }
        }
        else if (idx < 99) {
            pw[idx++] = c;
            putchar('*'); // 화면에는 *로 표시
        }
    }
    pw[idx] = '\0';







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
