#include <stdio.h>
#include <Windows.h>
#include "fun.h"
#include "main.h"

void user_menu(char id[])
{
	system("cls");
	

	int x = 1;
	int y = 2;
	
	gotoxy(x, y); 
	printf("┌"); for (int i = 0; i <= 90; i++) { printf("─"); }; printf("┐");          //1번줄	
	gotoxy(x, y + 1);  printf("│ %s님", id); gotoxy(93, y + 1); printf("│");			  //2번줄
	gotoxy(x, y + 2); printf("├"); for (int i = 0; i <= 90; i++) { printf("─"); } printf("┤");  //3번줄.
	y = 5;
	for (int i = 0; i < 18; i++) {
		gotoxy(x, y++);
		printf("│											     │");
	}

	system("pause>nul");
}