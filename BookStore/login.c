#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "fun.h"
#include "main.h"
#include "user_menu.h"

#define CLS system("cls")
#define PAUSE system("pause>nul")
int check_login(char id[], char pw[]);



void login_menu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    disable_mouse_input();

    int x = 35, y;
    char id[100], pw[100];
    int step;
    int idx_id, idx_pw;
    char c;

    while (1)  // 로그인 반복 루프
    {
        CLS;  // 화면 지우기
        y = 5;
        step = 0;
        idx_id = idx_pw = 0;
        memset(id, 0, sizeof(id));
        memset(pw, 0, sizeof(pw));

        // 화면 그리기
        gotoxy(x, y++); printf("┌──────────────────────────────────────────┐");
        for (int i = 0; i < 18; i++) { gotoxy(x, y++); printf("│                                          │"); }
        gotoxy(x, y++); printf("└──────────────────────────────────────────┘");
        gotoxy(x + 2, 23); printf("돌아가기");
        gotoxy(x + 16, 6); printf("☆  로그인 ☆");
        gotoxy(x + 5, 11); printf("아이디 : ");
        gotoxy(x + 5, 14); printf("비밀번호 : ");

        gotoxy(x + 14, 11);

        // 입력 처리
        while (step < 2)
        {
            enable_mouse_input();
            if (_kbhit())
            {
                c = _getch();
                if (c == '\r') { step++; if (step == 1) gotoxy(x + 16, 14); }
                else if (c == '\b') {
                    if (step == 0 && idx_id > 0) { idx_id--; printf("\b \b"); }
                    else if (step == 1 && idx_pw > 0) { idx_pw--; printf("\b \b"); }
                }
                else if (c != '\b') {
                    if (step == 0 && idx_id < 99) { id[idx_id++] = c; putchar(c); }
                    else if (step == 1 && idx_pw < 99) { pw[idx_pw++] = c; putchar('*'); }
                }
            }

            // 돌아가기 버튼 처리 (마우스)
            INPUT_RECORD rec; DWORD read;
            if (PeekConsoleInput(hInput, &rec, 1, &read) && read > 0) {
                ReadConsoleInput(hInput, &rec, 1, &read);
                if (rec.EventType == MOUSE_EVENT &&
                    rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    COORD pos = rec.Event.MouseEvent.dwMousePosition;
                    if (pos.X >= x + 2 && pos.X <= x + 10 && pos.Y == 23) {
                        show_menu();
                        return;
                    }
                }
            }
            Sleep(1);
        }

        id[idx_id] = '\0';
        pw[idx_pw] = '\0';

        int result = check_login(id, pw);

        if (result == 0)
        {
            int x = 35, y = 5;
            gotoxy(x, y++); printf("┌──────────────────────────────────────────┐");
            for (int i = 0; i < 18; i++) { gotoxy(x, y++); printf("│                                          │"); }
            gotoxy(x, y++); printf("└──────────────────────────────────────────┘");
            gotoxy(x + 16, 6); printf("☆  로그인 ☆");
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            gotoxy(x + 14, 12); printf("%s님 환영합니다!!", id);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            user_menu(id);
            return;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            gotoxy(x + 10, 18);
            if (result == 1) printf("존재하지 않는 아이디입니다.");
            else if (result == 2) printf("비밀번호가 틀렸습니다.");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            PAUSE;
            // 루프 반복 -> 화면 지우고 다시 로그인 시도
        }
    }
}




int check_login(char id[], char pw[])
{
    char path[MAX_PATH];
    sprintf(path, "%s\\SW_BOOKSTORE\\userdata.txt", getenv("APPDATA"));

    FILE* fp = fopen(path, "r");
    if (!fp) {
        printf("파일을 열 수 없습니다.\n");
        PAUSE;
        exit(100);
    }

    char line[256];
    int id_found = 0;

    while (fgets(line, sizeof(line), fp)) {
        char file_id[100], file_pw[100];
        int money;

        if (sscanf(line, "%99s %99s %d", file_id, file_pw, &money) == 3) {
            if (strcmp(id, file_id) == 0) {
                id_found = 1; // ID 존재
                if (strcmp(pw, file_pw) == 0) {
                    fclose(fp);
                    return 0;  // 로그인 성공
                }
                else {
                    fclose(fp);
                    return 2;  // 비밀번호 틀림
                }
            }
        }
    }

    fclose(fp);
    if (!id_found)
        return 1; // ID 없음

    return 3; // 그 외 (예상치 못한 경우)
}
