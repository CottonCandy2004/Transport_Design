#include <stdio.h>
#include "lookup.h"
#include "struct.h"
#include "station.h"
#include "ui.h"
#include "train.h"
#include <stdlib.h>
#include <string.h>
#include "ui_terminal.h"

void print_time(struct time t) {
    if (t.hour == -1) {
        printf("--:--");
    } else {
        printf("%02d:%02d", t.hour, t.minute);
    }
}
void station_timetable(struct city_ststion* station, vector* trains)
{
    if (station == NULL) return;
    printf("\n站点 %s 的时刻表：\n车次\t到达\t出发\n ", station->name);
    for (int i = 0; i < station->arrival.size; i++) {
        struct timetable* arrt = (struct timetable*)vector_get(&station->arrival, i);
        struct train* t = find_train(trains, arrt->trains_num);
        struct timetable* dept = (struct timetable*)vector_get(&station->departure, i);
        printf("%s\t", t->name);
        print_time(arrt->time);
        printf("\t");
        print_time(dept->time);
        printf("\n");
    }
}

void train_timetable(struct train* train)
{
    if (train == NULL) return;
    printf("\n列车 %s 的时刻表：\n", train->name);
    for (int i = 0; i < train->timetable.size; i++) {
        struct schedule* sch = get_train_schedule(train, i);
        printf("%s\t", sch->station);
        print_time(sch->arrival);
        printf("\t");
        print_time(sch->departure);
        printf("\n");
    }
}

// 查找直达列车
void find_direct_trains(vector* stations, vector* trains, const char* start, const char* end) {
    int start_idx = find_station_index(stations, start);
    int end_idx = find_station_index(stations, end);
    printf("从 %s 到 %s 的列车搜索结果如下：\n", start, end);
    if (start_idx == -1 || end_idx == -1) {
        printf("ERR: 找不到起点或终点站：%s -> %s\n", start, end);
        return;
    }

    struct city_ststion* start_station = (struct city_ststion*)vector_get(stations, start_idx);
    struct city_ststion* end_station = (struct city_ststion*)vector_get(stations, end_idx);
    
    int found = 0;
    
    for (int i = 0; i < start_station->departure.size; i++) {
        struct timetable* start_time = (struct timetable*)vector_get(&start_station->departure, i);
        
        for (int j = 0; j < end_station->arrival.size; j++) {
            struct timetable* end_time = (struct timetable*)vector_get(&end_station->arrival, j);
            
            if (start_time->trains_num == end_time->trains_num && start_time->time.hour*60+start_time->time.minute < end_time->time.hour*60+end_time->time.minute) {
                found = 1;
                printf("%s %02d:%02d --%s--> %s %02d:%02d\n", start, start_time->time.hour, start_time->time.minute, ((struct train*)trains->get(trains, start_time->trains_num))->name, end, end_time->time.hour, end_time->time.minute, end);
            }
        }
    }
    
    if (!found) {
        printf("未找到从 %s 到 %s 的直达列车。\n", start, end);
    }
}

void lookup_menu(vector* stations, vector* trains)
{
    bool return_flag = false;
    char *notice = "请选择查询的内容";
    char *choice[4] = {"1. 查询站点时刻表", "2. 查询列车时刻表", "3. 查询直达列车", "4. 返回"};
    while (1)
    {
        system("cls");
        int ch = ui_choice(notice, choice, 4);
        system("cls");
        ShowConsoleCursor();
        switch(ch)
        {
        case 0:
            printf("请输入您要查询的站点：\n");
            char station_name[10];
            scanf("%s", station_name);
            station_timetable((struct city_ststion*)vector_get(stations, find_station_index(stations, station_name)), trains);
            system("pause");
            break;
        case 1:
            printf("请输入您要查询的列车号：\n");
            char train_num[10];
            scanf("%s", &train_num);
            train_timetable(find_train(trains, find_train_index(trains, train_num)));
            system("pause");
            break;
        case 2:
            printf("请输入您要查询的起始站：\n");
            char start[10];
            scanf("%s", &start);
            printf("请输入您要查询的终点站：\n");
            char end[10];
            scanf("%s", &end);
            find_direct_trains(stations, trains, start, end);
            system("pause");
            break;
        case 3:
            return_flag = true;
            break;
        }
        if (return_flag)
        {
            break;
        }
    }
}