#include "train.h"
#include <stdlib.h>
#include <string.h>

void parse_time(const char* time_str, struct time* t) {
    int time_value = atoi(time_str);
    if (time_value == -1) {
        t->hour = -1;
        t->minute = -1;
    } else {
        t->hour = time_value / 60;
        t->minute = time_value % 60;
    }
}

void add_station_schedule(struct city_ststion* station, int train_number,
                         struct time* arrival, struct time* departure) {
    struct timetable arr_time = {train_number, *arrival};
    struct timetable dep_time = {train_number, *departure};
    
    if (arrival->hour != -1) {
        vector_push_back(&station->arrival, &arr_time);
    }
    if (departure->hour != -1) {
        vector_push_back(&station->departure, &dep_time);
    }
    station->trains_num++;
}

void add_train(vector* trains, const char* name, int number, int station_num) {
    struct train new_train;
    train_init(&new_train);
    strcpy(new_train.name, name);
    new_train.number = number;
    new_train.tickets_num = 600;
    vector tickets;
    vector_init(&tickets, sizeof(int));
    for (int i = 0; i < station_num; i++) {
        vector_push_back(&tickets, 0);
    }
    vector_push_back(trains, &new_train);
}

struct train* find_train(vector* trains, int number) {
    for (int i = 0; i < trains->size; i++) {
        struct train* t = (struct train*)vector_get(trains, i);
        if (t->number == number) {
            return t;
        }
    }
    return NULL;
}
