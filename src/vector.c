#include "vector.h"
#include <stdlib.h>
#include <string.h>

// 基本操作函数实现
void vector_init(struct vector* v, size_t element_size) {
    v->data = malloc(VECTOR_INIT_CAPACITY * element_size);
    if (v->data == NULL) {
        return;
    }
    v->size = 0;
    v->capacity = VECTOR_INIT_CAPACITY;
    v->element_size = element_size;

    v->free = vector_free;
    v->push_back = vector_push_back;
    v->pop_back = vector_pop_back;
    v->get_size = vector_size;
    v->get = vector_get;
}

void vector_free(struct vector* v) {
    if (v && v->data) {
        free(v->data);
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;
    }
}

void vector_push_back(struct vector* v, void* element) {
    if (!v || !element) return;
    
    if (v->size >= v->capacity) {
        v->capacity *= 2;
        void* new_data = realloc(v->data, v->capacity * v->element_size);
        if (new_data == NULL) {
            return;
        }
        v->data = new_data;
    }
    memcpy((char*)v->data + v->size * v->element_size, element, v->element_size);
    v->size++;
}

void vector_pop_back(struct vector* v) {
    if (v->size > 0) {
        v->size--;
    }
}

int vector_size(struct vector* v) {
    return v->size;
}

void* vector_get(struct vector* v, int index) {
    if (index >= 0 && index < v->size) {
        return (char*)v->data + index * v->element_size;
    }
    return NULL;
}