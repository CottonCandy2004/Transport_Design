#ifndef __STATION_H__
#define __STATION_H__

#include "struct.h"
#include <float.h>

#define MAX_STATIONS 1000

typedef struct {
    double dist[MAX_STATIONS];
    int prev[MAX_STATIONS];
    int visited[MAX_STATIONS];
} PathInfo;

// 在站点数组中查找站点索引
int find_station_index(vector* stations, const char* station_name) {
    for (int i = 0; i < stations->size; i++) {
        struct city_ststion* station = (struct city_ststion*)vector_get(stations, i);
        if (strcmp(station->name, station_name) == 0) {
            return i;
        }
    }
    return -1;
}

// Dijkstra最短路径算法
void find_shortest_path(vector* stations, const char* start, const char* end, PathInfo* path_info) {
    int start_idx = find_station_index(stations, start);
    int end_idx = find_station_index(stations, end);
    
    if (start_idx == -1 || end_idx == -1) {
        printf("找不到起点或终点站：%s -> %s\n", start, end);
        return;
    }

    for (int i = 0; i < stations->size; i++) {
        path_info->dist[i] = DBL_MAX;
        path_info->prev[i] = -1;
        path_info->visited[i] = 0;
    }
    path_info->dist[start_idx] = 0;

    for (int count = 0; count < stations->size; count++) {
        double min_dist = DBL_MAX;
        int min_idx = -1;
        
        for (int i = 0; i < stations->size; i++) {
            if (!path_info->visited[i] && path_info->dist[i] < min_dist) {
                min_dist = path_info->dist[i];
                min_idx = i;
            }
        }
        
        if (min_idx == -1) break;
        
        path_info->visited[min_idx] = 1;

        struct city_ststion* current = (struct city_ststion*)vector_get(stations, min_idx);
        struct linked_list* adj = current->linked_stations;
        
        while (adj) {
            if (adj->station_id >= 0 && adj->station_id < stations->size) {
                if (!path_info->visited[adj->station_id]) {
                    double new_dist = path_info->dist[min_idx] + adj->distance;
                    if (new_dist < path_info->dist[adj->station_id]) {
                        path_info->dist[adj->station_id] = new_dist;
                        path_info->prev[adj->station_id] = min_idx;
                    }
                }
            }
            adj = adj->next;
        }
    }
}

// 遍历最短路径并返回总距离
double traverse_path(vector* stations, const PathInfo* path_info, int start_idx, int end_idx) {
    if (start_idx == -1 || end_idx == -1 || path_info->prev[end_idx] == -1) {
        return -1;
    }

    int path[MAX_STATIONS];
    int path_len = 0;
    int curr_idx = end_idx;

    while (curr_idx != -1) {
        path[path_len++] = curr_idx;
        curr_idx = path_info->prev[curr_idx];
    }
    
    printf("路径: ");
    for (int i = path_len - 1; i >= 0; i--) {
        struct city_ststion* curr_station = 
            (struct city_ststion*)vector_get(stations, path[i]);
        printf("%s", curr_station->name);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
    
    return path_info->dist[end_idx];
}

#endif