#ifndef __AUTH_H__
#define __AUTH_H__
#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"
#include "ui_terminal.h"
#include <conio.h>
#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

char *input_password();

int auth()
{
    char *title = " /$$$$$$$            /$$ /$$                                  \n| $$__  $$          |__/| $$                                  \n| $$  \\ $$  /$$$$$$  /$$| $$ /$$  /$$  /$$  /$$$$$$  /$$   /$$\n| $$$$$$$/ |____  $$| $$| $$| $$ | $$ | $$ |____  $$| $$  | $$\n| $$__  $$  /$$$$$$$| $$| $$| $$ | $$ | $$  /$$$$$$$| $$  | $$\n| $$  \\ $$ /$$__  $$| $$| $$| $$ | $$ | $$ /$$__  $$| $$  | $$\n| $$  | $$|  $$$$$$$| $$| $$|  $$$$$/$$$$/|  $$$$$$$|  $$$$$$$\n|__/  |__/ \\_______/|__/|__/ \\_____/\\___/  \\_______/ \\____  $$\n                                                     /$$  | $$\n                                                    |  $$$$$$/\n                                                     \\______/ \n";
    FILE *fp;
    fp = fopen("../data/key.dat", "r");
    while (DEBUG_MODE != 1)
    {
        if (fp == NULL)
        {
            fp = fopen("../data/key.dat", "w");
            if (fp == NULL)
            {
                system("cls");
                printf("%s", title);
                SetColor(4, 0);
                printf("磁盘读写错误，请检查程序是否有相应目录的读写权限！\n");
                SetColor(15, 0);
                system("pause");
                return -1;
            }
            while (1)
            {
                system("cls");
                printf("%s", title);
                printf("请设置密钥（不应超过128位）：\n");
                char *password = input_password();
                if (strlen(password) > 128)
                {
                    printf("\n密钥长度不能超过128位！\n");
                    Sleep(1000);
                    continue;
                }
                else
                {
                    char *sha = summonsha(password);
                    fwrite(sha, sizeof(char), strlen(sha), fp);
                    system("cls");
                    printf("%s", title);
                    printf("密钥设置成功！\n");
                    Sleep(1000);
                    fclose(fp);
                    free(sha);
                    return 200;
                }
            }
        }
        else
        {
            system("cls");
            printf("%s", title);
            char *key = (char *)malloc(sizeof(char) * 65);
            memset(key, 0, 65);
            fread(key, sizeof(char), 64, fp);
            if (feof(fp))
            {
                fclose(fp);
                fp = NULL;
                continue;
            }
            fclose(fp);
            printf("请输入密钥：\n");
            char *password = input_password();
            char *sha = summonsha(password);
            if (strcmp(sha, key) == 0)
            {
                free(sha);
                free(key);
                return 200;
            }
            else
            {
                free(sha);
                free(key);
                return -2;
            }
        }
    }
    fclose(fp);
    return 200;
}

char *input_password()
{
    char *password = (char *)malloc(sizeof(char) * 129);
    memset(password, 0, 129);
    int length = 0;
    char buff;
    while (1)
    {
        buff = _getch();
        if (buff == '\r')
        {
            if (length == 0)
            {
                printf("\a");
                continue;
            }
            password[length] = '\0';
            break;
        }
        else if (buff == '\b')
        {
            if (length > 0)
            {
                length--;
                printf("\b \b");
            }
            else
            {
                printf("\a");
            }
        }
        else
        {
            password[length] = buff;
            length++;
            printf("*");
        }
    }
    return password;
}

#endif