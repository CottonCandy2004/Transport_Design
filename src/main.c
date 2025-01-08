#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "auth.h"
#include "fileio.h"
#include "lookup.h"
#include "sold.h"
#include <windows.h>
#include "ui_terminal.h"

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
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
    vector allstations;
    vector_init(&allstations, sizeof(struct city_ststion));
    read_routes_file("../data/Citys.rawdat", &allstations);
    vector trains;
    vector_init(&trains, sizeof(struct train));
    read_trains_file("../data/Trains.rawdat", &trains, &allstations);
    char *notice1 = "请选择您的操作：";
    char *choice[3] = {"1. 查询", "2.售票", "3. 退出系统"};
    int result_colour = 0;
    while (1)
    {
        int ch = ui_choice(notice1, choice, 3);
        switch(ch)
        {
        case 0:
            lookup_menu(&allstations, &trains);
            break;
        case 1:
            sold_menu(&trains, &allstations);
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