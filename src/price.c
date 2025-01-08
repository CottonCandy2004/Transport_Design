#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "auth.h"
#include "fileio.h"
#include "lookup.h"
#include <string.h>
#include "station.h"
#include "train.h"
#include <stdbool.h>

int countprice(vector *stations, const char *start, const char *end, PathInfo *path_info, vector *train, int trainidx)
{
    int s, dist = 0;
    int i = 0;
    int j = 0;
    struct train *train1;
    train1 = (struct train *)vector_get(train, trainidx);
    s = train1->timetable.size;
    for (; i < s; i++)
    {
        struct schedule *s1 = (struct train *)vector_get(&train1->timetable, i);
        if (strcmp(s1->station, start) == 0)
            break;
    }

    for (; j < s; j++)
    {
        struct schedule *s1 = (struct train *)vector_get(&train1->timetable, j);
        if (strcmp(s1->station, end) == 0)
            break;
    }

    for (int k = 0; k < s; k++)
    {
        find_shortest_path(stations, ((struct schedule *)vector_get(&train1->timetable, i + k))->station, ((struct schedule *)vector_get(&train1->timetable, i + k + 1))->station, path_info);
        int start_idx = find_station_index(stations, ((struct schedule *)vector_get(&train1->timetable, i + k))->station);
        int end_idx = find_station_index(stations, ((struct schedule *)vector_get(&train1->timetable, i + k + 1))->station);
        dist = dist + traverse_path(stations, path_info, start_idx, end_idx, false);
        if ((i + 1 + k) == j)
            break;
    }
    int price = 0.4 * dist;
    return price;
}