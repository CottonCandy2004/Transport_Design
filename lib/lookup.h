#ifndef __LOOKUP_H__
#define __LOOKUP_H__

#include "vector.h"
#include "struct.h"

void print_time(struct time t);
void station_timetable(struct city_ststion* station, vector* trains);
void train_timetable(struct train* train);
void find_direct_trains(vector* stations, vector* trains, const char* start, const char* end);
void lookup_menu(vector* stations, vector* trains);
#endif