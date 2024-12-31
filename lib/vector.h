#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <string.h>
#include "struct.h"

#define VECTOR_INIT_CAPACITY 4

typedef struct {
    void* data;
    int size;
    int capacity;
    size_t element_size;
} vector;

// 基本操作函数
void vector_init(vector* v, size_t element_size);
void vector_free(vector* v);
void vector_push_back(vector* v, void* element);
void vector_pop_back(vector* v);
int vector_size(vector* v);
void* vector_get(vector* v, int index);

// 特化函数声明
void vector_init_schedule(vector* v);
void vector_push_back_schedule(vector* v, struct schedule* element);
struct schedule* vector_get_schedule(vector* v, int index);

void vector_init_timetable(vector* v);
void vector_push_back_timetable(vector* v, struct timetable* element);
struct timetable* vector_get_timetable(vector* v, int index);

// 基本操作函数实现
void vector_init(vector* v, size_t element_size) {
    v->data = malloc(VECTOR_INIT_CAPACITY * element_size);
    v->size = 0;
    v->capacity = VECTOR_INIT_CAPACITY;
    v->element_size = element_size;
}

void vector_free(vector* v) {
    free(v->data);
    v->size = 0;
    v->capacity = 0;
}

void vector_push_back(vector* v, void* element) {
    if (v->size >= v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * v->element_size);
    }
    memcpy((char*)v->data + v->size * v->element_size, element, v->element_size);
    v->size++;
}

void vector_pop_back(vector* v) {
    if (v->size > 0) {
        v->size--;
    }
}

int vector_size(vector* v) {
    return v->size;
}

void* vector_get(vector* v, int index) {
    if (index >= 0 && index < v->size) {
        return (char*)v->data + index * v->element_size;
    }
    return NULL;
}

// schedule特化实现
void vector_init_schedule(vector* v) {
    vector_init(v, sizeof(struct schedule));
}

void vector_push_back_schedule(vector* v, struct schedule* element) {
    vector_push_back(v, element);
}

struct schedule* vector_get_schedule(vector* v, int index) {
    return (struct schedule*)vector_get(v, index);
}

// timetable特化实现
void vector_init_timetable(vector* v) {
    vector_init(v, sizeof(struct timetable));
}

void vector_push_back_timetable(vector* v, struct timetable* element) {
    vector_push_back(v, element);
}

struct timetable* vector_get_timetable(vector* v, int index) {
    return (struct timetable*)vector_get(v, index);
}

#endif