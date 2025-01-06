#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <stddef.h>

#define VECTOR_INIT_CAPACITY 4

typedef struct vector {
    void* data;
    int size;
    int capacity;
    size_t element_size;

    void (*free)(struct vector* v);
    void (*push_back)(struct vector* v, void* element);
    void (*pop_back)(struct vector* v);
    int (*get_size)(struct vector* v);
    void* (*get)(struct vector* v, int index);
} vector;

// 基本操作函数声明
void vector_init(struct vector* v, size_t element_size);
void vector_free(struct vector* v);
void vector_push_back(struct vector* v, void* element);
void vector_pop_back(struct vector* v);
int vector_size(struct vector* v);
void* vector_get(struct vector* v, int index);

#endif