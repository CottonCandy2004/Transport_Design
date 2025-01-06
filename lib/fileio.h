#ifndef __FILEIO_H__
#define __FILEIO_H__

#include "struct.h"
#include "vector.h"

#define MAX_LINE_LENGTH 1024

void trim_newline(char* str);
int find_or_add_station(vector* stations, const char* station_name);
void add_station_link(struct city_ststion* from_station, struct city_ststion* to_station, double distance);
void read_route(FILE* file, vector* stations);
void read_routes_file(const char* filename, vector* all_stations);

#endif
