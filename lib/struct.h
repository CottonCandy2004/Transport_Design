#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

struct time
{
    int hour;
    int minute;
};

struct schedule
{
    char station[50];
    struct time arrival;
    struct time departure;
};

struct train
{
    char name[50];
    int number;

    int tickets_num;
    vector tickets;
    vector timetable;
    void (*free)(struct train* it);
};

struct timetable
{
    int trains_num;
    struct time time;
};

struct linked_list
{
    int station_id;
    double distance;
    struct city_ststion* station;
    struct linked_list* next;
};

struct city_ststion
{
    int station_id;
    char name[50];
    int trains_num;
    vector arrival;
    vector departure;
    struct linked_list* linked_stations;

    void (*free)(struct city_ststion* it);
};

void train_init(struct train* it);
void train_free(struct train* it);

void city_station_init(struct city_ststion* it);
void city_station_free(struct city_ststion* it);

void train_init(struct train* it)
{
    vector_init(&it->tickets, sizeof(int));
    vector_init(&it->timetable, sizeof(struct schedule));
    it->free = train_free;
}

void train_free(struct train* it)
{
    vector_free(&it->tickets);
    vector_free(&it->timetable);
}

void city_station_init(struct city_ststion* it)
{
    vector_init(&it->arrival, sizeof(struct timetable));
    vector_init(&it->departure, sizeof(struct timetable));
    it->linked_stations = NULL;
    it->free = city_station_free;
}

void city_station_free(struct city_ststion* it)
{
    vector_free(&it->arrival);
    vector_free(&it->departure);
}

#endif