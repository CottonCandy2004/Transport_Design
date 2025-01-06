#ifndef __STRUCT_H__
#define __STRUCT_H__

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



#endif