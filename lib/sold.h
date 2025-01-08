#ifndef __SOLD_H__
#define __SOLD_H__

#include "vector.h"
struct listing_trains
{
    int num;
    vector trains;
    char **trains_text;
};

void listing_trains_init(struct listing_trains* it);
void listing_trains_free(struct listing_trains* it);
int calc_tickets(vector* train, int train_index, vector* stations, const char* start, const char* end);
struct listing_trains* listing_trains(vector* train, vector* stations, const char* start, const char* end);
void sold_menu(vector* train, vector* stations);
#endif