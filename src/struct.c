#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 初始化火车结构体
void train_init(struct train* it)
{
    vector_init(&it->tickets, sizeof(int));
    vector_init(&it->timetable, sizeof(struct schedule));
    it->free = train_free;
}

// 释放火车结构体
void train_free(struct train* it)
{
    vector_free(&it->tickets);
    vector_free(&it->timetable);
}

// 初始化城市站点结构体
void city_station_init(struct city_ststion* it)
{
    vector_init(&it->arrival, sizeof(struct timetable));
    vector_init(&it->departure, sizeof(struct timetable));
    it->linked_stations = NULL;
    it->free = city_station_free;
}

// 释放城市站点结构体
void city_station_free(struct city_ststion* it)
{
    vector_free(&it->arrival);
    vector_free(&it->departure);
}