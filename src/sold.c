#include "sold.h"
#include "ui_terminal.h"
#include "struct.h"
#include "stdbool.h"
#include "ui.h"
#include "price.h"
#include "station.h"
#include "lookup.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <wchar.h>  // 添加这行在开头

#define TICKETS 100

void listing_trains_init(struct listing_trains* it)
{
    vector_init(&it->trains, sizeof(struct train));
}

void listing_trains_free(struct listing_trains* it)
{
    vector_free(&it->trains);
    free(it->trains_text);
}

int calc_tickets(vector* train, int train_index, vector* stations, const char* start, const char* end)
{
    struct train* t = (struct train*)vector_get(train, train_index);
    int tickets_left = TICKETS;
    int min = TICKETS;
    bool startcalc = false;
    for (int i = 0; i < t->timetable.size; i++)
    {
        int* calc = (int*)vector_get(&t->tickets, i);
        tickets_left -= *calc;
        if (strcmp(((struct schedule*)vector_get(&t->timetable, i))->station, start) == 0)
        {
            min = tickets_left;
            startcalc = true;
        }
        if (startcalc)
        {
            if (min > tickets_left)
            {
                min = tickets_left;
            }
        }
        if (strcmp(((struct schedule*)vector_get(&t->timetable, i))->station, end) == 0)
        {
            return min;
        }
    }
    return 0;
}


struct listing_trains* listing_trains(vector* train, vector* stations, const char* start, const char* end)
{
    struct listing_trains* it = malloc(sizeof(struct listing_trains));
    listing_trains_init(it);
    it->trains_text = malloc(100 * sizeof(char*));
    int start_index = find_station_index(stations, start);
    int end_index = find_station_index(stations, end);
    if (start_index == -1 || end_index == -1)
    {
        printf("错误：找不到起点或终点站：%s -> %s\n", start, end);
        it->num = 0;
        return it;
    }
    struct city_ststion* start_station = (struct city_ststion*)vector_get(stations, start_index);
    struct city_ststion* end_station = (struct city_ststion*)vector_get(stations, end_index);
    int num = 0;
    for (int i = 0; i < start_station->departure.size; i++)
    {
        struct timetable* start_time = (struct timetable*)vector_get(&start_station->departure, i);
        for (int j = 0; j < end_station->arrival.size; j++)
        {
            struct timetable* end_time = (struct timetable*)vector_get(&end_station->arrival, j);
            if (start_time->trains_num == end_time->trains_num && start_time->time.hour * 60 + start_time->time.minute < end_time->time.hour * 60 + end_time->time.minute)
            {
                struct train* t = (struct train*)vector_get(train, start_time->trains_num);
                int tickets = calc_tickets(train, start_time->trains_num, stations, start, end);
                if (tickets >= 0)
                {
                    vector_push_back(&it->trains, t);
                    char* text = malloc(200 * sizeof(char));
                    int travel_time = end_time->time.hour * 60 + end_time->time.minute - start_time->time.hour * 60 - start_time->time.minute;
                    struct time travel = {travel_time / 60, travel_time % 60};
                    PathInfo path_info;
                    int price = countprice(stations, start, end, &path_info, train, start_time->trains_num);
                    sprintf(text, "%s %02d:%02d —— %s（%02d小时%02d分钟）——> %s %02d:%02d ￥%d （剩余%d张票）", start, start_time->time.hour, start_time->time.minute, t->name, travel.hour, travel.minute, end, end_time->time.hour, end_time->time.minute, price, tickets);
                    it->trains_text[num] = text;
                    printf("%s\n", it->trains_text[num]);
                    num++;
                }
            }
        }
    }
    it->num = num;
    return it;
}

void sold_menu(vector* train, vector* stations)
{
    system("cls");
    ShowConsoleCursor();
    SetConsoleCP(65001);
    printf("请输入起始站：\n");
    char start[40];
    scanf("%s", start);
    printf("请输入终点站：\n");
    char end[40];
    scanf("%s", end);
    struct listing_trains* lt = listing_trains(train, stations, start, end);
    if (lt->num == 0)
    {
        printf("未找到从 %s 到 %s 的直达列车。\n", start, end);
        system("pause");
        return;
    }
    char* notice = "请选择要购买的车次：";
    char** choice = malloc((lt->num + 1) * sizeof(char*));
    memcpy(choice, lt->trains_text, lt->num * sizeof(char*));
    choice[lt->num] = "返回";
    int ch = ui_choice(notice, choice, lt->num + 1);
    if (ch == lt->num)
    {
        return;
    }
    struct train* t = (struct train*)vector_get(&lt->trains, ch);
    int tickets = calc_tickets(train, t->number, stations, start, end);
    if (tickets == 0)
    {
        printf("错误：票已售完\n");
        system("pause");
        return;
    }
    printf("请输入购买票数：\n");
    int buy;
    scanf("%d", &buy);
    if (buy > tickets)
    {
        printf("错误：票数不足\n");
        system("pause");
        return;
    }
    system("cls");
    printf("购买信息：\n");
    printf("车次：%s\n", t->name);
    printf("起始站：%s\n", start);
    struct time starttm, endtm;
    int startidx = -1, endidx = -1;
    for (int i = 0; i < t->timetable.size; i++)
    {
        struct schedule* s = (struct schedule*)vector_get(&t->timetable, i);
        if (strcmp(s->station, start) == 0)
        {
            memccpy(&starttm, &s->departure, 1, sizeof(struct time));
            startidx = i;
            continue;
        }
        if (strcmp(s->station, end) == 0)
        {
            memccpy(&endtm, &s->arrival, 1, sizeof(struct time));
            endidx = i;
            break;
        }
    }
    printf("出发时间：");
    print_time(starttm);
    printf("\n");
    printf("到达时间：");
    print_time(endtm);
    printf("\n");
    printf("终点站：%s\n", end);
    printf("票数：%d\n\n", buy);
    PathInfo path_info;
    int price = countprice(stations, start, end, &path_info, train, t->number);
    int* p = (int*)vector_get(&t->tickets, startidx);
    int* q = (int*)vector_get(&t->tickets, endidx);
    *q -= buy;
    *p += buy;
    SetColor(10, 0);
    printf("购买成功\n");
    SetColor(7, 0);
    system("pause");
}