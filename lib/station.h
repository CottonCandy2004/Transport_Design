#ifndef __STATION_H__
#define __STATION_H__

#include "struct.h"
#include <stdbool.h>
#include <float.h>

#define MAX_STATIONS 1000

typedef struct {
    double dist[MAX_STATIONS];
    int prev[MAX_STATIONS];
    int visited[MAX_STATIONS];
} PathInfo;

int find_station_index(vector* stations, const char* station_name);
void find_shortest_path(vector* stations, const char* start, const char* end, PathInfo* path_info);
double traverse_path(vector* stations, const PathInfo* path_info, int start_idx, int end_idx, bool printable);

#endif