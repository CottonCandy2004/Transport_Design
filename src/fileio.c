#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"
#include "train.h"

// 去掉字符串末尾的换行符
void trim_newline(char* str) {
    int len = strlen(str);
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
        len--;
    }
}

// 在站点数组中查找站点索引
int find_or_add_station(vector* stations, const char* station_name) {
    for (int i = 0; i < stations->size; i++) {
        struct city_ststion* station = (struct city_ststion*)vector_get(stations, i);
        if (strcmp(station->name, station_name) == 0) {
            return i;
        }
    }
    
    struct city_ststion station;
    city_station_init(&station);
    station.station_id = stations->size;
    strcpy(station.name, station_name);
    station.trains_num = 0;
    station.linked_stations = NULL;
    vector_push_back(stations, &station);
    return stations->size - 1;
}

// 添加站点之间的连接
void add_station_link(struct city_ststion* from_station, struct city_ststion* to_station, double distance) {
    struct linked_list* new_link = (struct linked_list*)malloc(sizeof(struct linked_list));
    new_link->station_id = to_station->station_id;
    new_link->distance = distance > 0 ? distance : -distance;    
    new_link->station = to_station;
    new_link->next = NULL;
    if (from_station->linked_stations == NULL) {
        from_station->linked_stations = new_link;
    } else {
        new_link->next = from_station->linked_stations;
        from_station->linked_stations = new_link;
    }
}

// 读取一条路线
void read_route(FILE* file, vector* stations) {
    char line[MAX_LINE_LENGTH];
    if (!fgets(line, MAX_LINE_LENGTH, file)) return;
    
    trim_newline(line);
    char* route_name = strtok(line, ",");
    int station_count = atoi(strtok(NULL, ","));
    printf("%s: %d站\n", route_name, station_count);
    int prev_station_idx = -1;
    double prev_distance = 0;
    
    for (int i = 0; i < station_count; i++) {
        if (!fgets(line, MAX_LINE_LENGTH, file)) break;
        
        trim_newline(line);
        char* station_name = strtok(line, ",");
        double current_distance = atof(strtok(NULL, ","));
        
        int current_station_idx = find_or_add_station(stations, station_name);
        
        if (prev_station_idx != -1) {
            struct city_ststion* prev_station = (struct city_ststion*)vector_get(stations, prev_station_idx);
            struct city_ststion* curr_station = (struct city_ststion*)vector_get(stations, current_station_idx);
            
            double segment_distance = current_distance - prev_distance;
            
            add_station_link(prev_station, curr_station, segment_distance);
            add_station_link(curr_station, prev_station, segment_distance);
        }
        
        prev_station_idx = current_station_idx;
        prev_distance = current_distance;
    }
}

// 读取路线文件
void read_routes_file(const char* filename, vector* all_stations) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开文件: %s\n", filename);
        return;
    }

    while (!feof(file)) {
        read_route(file, all_stations);
    }
    
    printf("成功读取了 %d 个站点\n", all_stations->size);
    fclose(file);
}

// 读取火车信息
void read_trains_file(const char* filename, vector* trains, vector* stations) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("无法打开文件: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        trim_newline(line);
        char* train_name = strtok(line, ",");
        int train_number = trains->size;
        int station_num = 0;
        add_train(trains, train_name, train_number, station_num);
        struct train* current_train = (struct train*)vector_get(trains, train_number);
        while (1) {
            char* station_name = strtok(NULL, ",");
            if (!station_name) break;
            
            char* arrival_str = strtok(NULL, ",");
            char* departure_str = strtok(NULL, ",");
            
            if (!arrival_str || !departure_str) break;
            station_num++;
            int station_idx = find_or_add_station(stations, station_name);
            if (station_idx != -1) {
                struct city_ststion* station = 
                    (struct city_ststion*)vector_get(stations, station_idx);
                
                struct time arrival, departure;
                parse_time(arrival_str, &arrival);
                parse_time(departure_str, &departure);
                add_station_schedule(station, train_number, &arrival, &departure);
                add_train_schedule(current_train, station_name, arrival, departure);
            }
        }
        current_train->tickets_num = station_num;
        for (int i = 0; i < station_num; i++) {
            int buff = 0;
            vector_push_back(&current_train->tickets, &buff);
        }
    }

    fclose(file);
    printf("成功读取了 %d 趟列车信息\n", trains->size);
}