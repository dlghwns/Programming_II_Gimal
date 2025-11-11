#include <windows.h>

void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



void printclickpos() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD rec;
    DWORD read;

    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

    ReadConsoleInput(hInput, &rec, 1, &read);

    if (rec.EventType == MOUSE_EVENT) {
        if (rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            COORD pos = rec.Event.MouseEvent.dwMousePosition;
            gotoxy(10, 90);  printf("X: %d, Y: %d", pos.X, pos.Y);
        }
    }
}



// 마우스 모드 끄기
void disable_mouse_input()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~ENABLE_MOUSE_INPUT); // 마우스 입력 끔
}

// 마우스 모드 켜기
void enable_mouse_input()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode | ENABLE_MOUSE_INPUT); // 마우스 입력 켬
}