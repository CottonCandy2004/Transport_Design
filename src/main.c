#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "auth.h"

int main()
{
    SetConsoleOutputCP(65001);
    system("cls");
    int status = auth();
    while (status != 200)
    {
        if (status == -2)
        {
            SetColor(4, 0);
            printf(" X\n密码错误，请重新输入\n");
            Sleep(1000);
            SetColor(15, 0);
        }
        if (status == -1)
            return 0;
        status = auth();
    }
    char *notice1 = "请选择您的操作：";
    char *choice[3] = {"1. 售票", "2.", "3. 退出系统"};
    int result_colour = 0;
    while (1)
    {
        int ch = ui_choice(notice1, choice, 3);
        switch(ch)
        {
        case 0:

            break;
        case 1:

            break;
        case 2:
            exit(0);
        }
    }
    system("pause");
    return 0;
    system("pause");    
    return 0;
}