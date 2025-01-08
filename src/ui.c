#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "ui_terminal.h"
#include "ui.h"
#include <windows.h>  // 添加头文件

void flush(char *notice, char **arr, int length, int *choice)
{
    system("cls");
    SetConsoleOutputCP(65001);  // 添加这行
    fflush(stdout);  // 添加这行

    SetColor(15, 0);
    printf("欢迎使用全国铁路网络售票系统\nWelcome to the National Railway Network Ticketing System\n\n%s\n", notice);
    for (int i = 0; i < length; i++)
    {
        if (i == *choice)
        {
            SetColor(0, 15);
            printf("%s\n", arr[i]);
            SetColor(15, 0);
        }
        else
        {
            printf("%s\n", arr[i]);
        }
    }
}

void result_attach(char *result, int *result_colour, char *notice, char **arr, int length, int *choice)
{
    flush(notice, arr, length, choice);
    SetColor(*result_colour, 0);
    printf("\n%s\n", result);
}

int ui_re_choice(char *notice, char **arr, int length, char *result, int result_colour)
{
    HideConsoleCursor();
    int choice = 0, satus = 0;
    while (1)
    {
        result_attach(result, &result_colour, notice, arr, length, &choice);
        orginize_input(&choice, &satus, &length);
        if (satus == 1)
        {
            return choice;
        }
    }
}

void orginize_input(int *choice, int *satus, const int *length)
{
    int key = getch();
    if (key == 224)
    {
        switch (getch())
        {
        case 72:
            (*choice)--;
            if (*choice < 0)
            {
                printf("\a");
                *choice = 0;
            }
            break;
        case 80:
            (*choice)++;
            if (*choice > (*length) - 1)
            {
                printf("\a");
                *choice = (*length) - 1;
            }
            break;
        default:
            printf("\a");
            break;
        }
    }
    else
    {
        switch (key)
        {
        case 'w':
            (*choice)--;
            if (*choice < 0)
            {
                printf("\a");
                *choice = 0;
            }
            break;
        case 's':
            (*choice)++;
            if (*choice > (*length) - 1)
            {
                printf("\a");
                *choice = (*length) - 1;
            }
            break;
        default:
            if (key == '\r')
            {
                *satus = 1;
            }
            else
            {
                printf("\a");
            }
            break;
        }
    }
}

int ui_choice(char *notice, char **arr, int length)
{
    SetConsoleOutputCP(65001);  // 添加这行
    HideConsoleCursor();
    int choice = 0, satus = 0;
    while (1)
    {
        fflush(stdin);
        flush(notice, arr, length, &choice);
        orginize_input(&choice, &satus, &length);
        if (satus == 1)
        {
            system("cls");
            return choice;
        }
    }
}