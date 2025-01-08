#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *summonsha(char *str_)
{
    FILE *fp, *buff;
    buff = fopen("sha", "w");
    fwrite(str_, 1, strlen(str_), buff);
    fclose(buff);
    fp = popen("certutil.exe -hashfile sha sha256", "r");
    char *buffer = (char *)malloc(1024);
    char *q=buffer;
    memset(buffer, 0, 1024);
    while (!feof(fp))
    fread(q++, 1, 1, fp);
    pclose(fp);
    char *p = strstr(buffer, "CertUtil");
    p--;
    *p='\0';
    p-=64;
    system("del sha");
    char *sha = (char *)malloc(65);
    strcpy(sha, p);
    free(buffer);
    return sha;
}