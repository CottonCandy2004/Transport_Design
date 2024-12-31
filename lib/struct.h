#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int* tickets;
    
    struct schedule* timetable;
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
    unsigned int distance;
    struct city_ststion* station;
    struct linked_list* next;
};

struct city_ststion
{
    int station_id;
    char name[50];
    int trains_num;
    struct timetable* arrival;
    struct timetable* departure;
    struct linked_list* linked_stations;

    void (*free)(struct city_ststion* it);
};

void train_init(struct train* it, int tickets_num)
{
    it->tickets_num = tickets_num;
    it->tickets = (int*)malloc(sizeof(int) * tickets_num);
    memset(it->tickets, 0, sizeof(int) * tickets_num);
    it->timetable = (struct schedule*)malloc(sizeof(struct schedule) * tickets_num);
    it->free = train_free;
}

void train_free(struct train* it)
{
    free(it->tickets);
    free(it->timetable);
}

void city_station_init(struct city_ststion* it)
{
    it->arrival = (struct timetable*)malloc(sizeof(struct timetable));
    it->departure = (struct timetable*)malloc(sizeof(struct timetable));
    it->linked_stations = NULL;
    it->free = city_station_free;
}

void city_station_free(struct city_ststion* it)
{
    free(it->arrival);
    free(it->departure);
}

#endif