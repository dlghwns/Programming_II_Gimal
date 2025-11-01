#define _CRT_SECURE_NO_WARNINGS
#include "login.h"
#include <stdio.h>
#include <Windows.h>

void check_file();


int main()
{
    char user_id[20] = "";
	check_file();


	return 0;
}



void check_file()    // 순서1
{
    FILE* fp = fopen("userdata.txt", "r"); // 읽기 모드로 열기 시도
    if (fp == NULL) {
        fp = fopen("userdata.txt", "w");
        return;
    }

    else {
        fclose(fp);
        return;
    }

}


