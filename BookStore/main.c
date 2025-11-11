#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "fun.h"
#include "login.h"
#include "register.h"

#define CLS system("cls")
#define PAUSE system("pause>nul")


void check_file();
void show_menu();
int check_menu_click(COORD pos);


    
int main(void) {
	check_file();
    show_menu();
    return 0;
}

void check_file() {
    char folder[MAX_PATH];
    char file[MAX_PATH];

    char* appdata = getenv("APPDATA");
    if (!appdata) return;  // APPDATA 환경변수 없으면 종료

    sprintf(folder, "%s\\SW_BOOKSTORE", appdata);

    // 폴더가 없으면 생성
    if (GetFileAttributesA(folder) == INVALID_FILE_ATTRIBUTES) {
        if (!CreateDirectoryA(folder, NULL)) {
            printf("폴더 생성 실패, 오류코드: %lu\n", GetLastError());
            return;
        }
    }

    // 파일 경로 생성
    sprintf(file, "%s\\userdata.txt", folder);

    // 파일 없으면 생성
    FILE* fp = fopen(file, "a");
    if (fp) fclose(fp);
}

void show_menu() {
    CLS;
    int x = 35, y = 5;

    gotoxy(x, y++);
    printf("┌──────────────────────────────────────────┐");
    for (int i = 0; i < 18; i++) {
        gotoxy(x, y++);
        printf("│                                          │");
    }
    gotoxy(x, y++);
    printf("└──────────────────────────────────────────┘");

    gotoxy(x + 15, 6);  printf("☆  서원 문고 ☆");
    gotoxy(x + 12, 10); printf("1. 로그인     (Login)");
    gotoxy(x + 12, 14); printf("2. 회원가입   (Sign Up)");
    gotoxy(x + 12, 18); printf("3. 종료       (Exit)");


    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD rec;
    DWORD read;
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);




    while (1) {
        ReadConsoleInput(hInput, &rec, 1, &read);

        if (rec.EventType == MOUSE_EVENT) {
            if (rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                COORD pos = rec.Event.MouseEvent.dwMousePosition;
                if (check_menu_click(pos)) break;
            }
        }

    }
}

int check_menu_click(COORD pos) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    if ((pos.X >= 46 && pos.X <= 68) && (pos.Y >= 9 && pos.Y <= 10)) {
        gotoxy(47, 10);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("1. 로그인     (Login)");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        Sleep(170);

        login_menu();
        return 1;
    }
    else if ((pos.X >= 46 && pos.X <= 68) && (pos.Y >= 13 && pos.Y <= 14)) {
        gotoxy(47, 14);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("2. 회원가입   (Sign Up)");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        Sleep(170);
        register_menu();
        return 1;
    }
    else if ((pos.X >= 46 && pos.X <= 68) && (pos.Y >= 17 && pos.Y <= 18)) {
        gotoxy(47, 18);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("3. 종료       (Exit)");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        exit(0);
    }
    else {
		return 0;
    }
}
