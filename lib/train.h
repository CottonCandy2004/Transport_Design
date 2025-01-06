#ifndef __TRAIN_H__
#define __TRAIN_H__

#include "struct.h"

// 解析时间字符串为time结构
void parse_time(const char* time_str, struct time* t);

// 向站点添加时刻表信息
void add_station_schedule(struct city_ststion* station, int train_number, 
                         struct time* arrival, struct time* departure);

// 向vector中添加火车信息
void add_train(vector* trains, const char* name, int number);

// 根据火车编号查找火车
struct train* find_train(vector* trains, int number);

#endif
