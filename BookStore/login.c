#include <stdio.h>
#include <Windows.h>
#define CLS system("cls");

void login_menu()
{
	while (1)
	{
		int choice = 0;
		CLS


		printf("1. 로그인\n");
		printf("2. 회원가입\n");
		printf("3. 회원 탈퇴\n");
		printf("선택 : ");
		scanf_s("%d", &choice);

		if (choice == 1)
		{
			printf("로그인 선택\n");
			// 로그인 함수 호출
			break;
		}
		else if (choice == 2)
		{
			printf("회원가입 선택\n");
			// 회원가입 함수 호출
			break;
		}
		else if (choice == 3)
		{
			printf("회원 탈퇴\n");
			break;
		}
		else
		{
			continue;
		}
	}
	exit(0);
}


void login_delete_user()
{
	CLS


	char user_id[20] = "";
	char user_pw[20] = "";
	char combine[100] = "";
	int found = 0;

	printf("(exit입력시 돌아가기)\n ");
	printf("삭제 할 아이디 : ");
	scanf_s("%s", user_id, sizeof(user_id));
	if (strcmp(user_id, "exit") == 0)
	{
		login_menu();
	}

	printf("비밀번호 : ");
	scanf_s("%s", user_pw, sizeof(user_pw));
	sprintf(combine, "%s_%s", user_id, user_pw);


	
	
}