#ifndef __DARRAY_H__
#define __DARRAY_H__

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <errno.h>

#define DEFAULT_CAPACITY 8
#define DEFAULT_GROW_RATE 2


typedef struct
{
    size_t capacity;
    size_t size;
    int* data;
} DArray;



static int _ensure_capacity(DArray* arr){
    if(arr->size < arr->capacity){
        return 0;
    }

    size_t new_capacity = arr->capacity * DEFAULT_GROW_RATE;
    arr->data = realloc(arr->data, new_capacity * sizeof(int));
    if(arr->data == NULL){
        return 1;
    }
    arr->capacity = new_capacity;
    return 0;
}


DArray da_create(){

    DArray arr;
    
    arr.data = (int*)calloc(DEFAULT_CAPACITY * sizeof(int), sizeof(int));
    if (arr.data == NULL)
    {
        fprintf(stderr, "da_create error %d\n", errno);
        exit(1);
    }

    arr.capacity = DEFAULT_CAPACITY;
    arr.size = 0;
    return arr;
}


void da_destroy(DArray* arr){
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}


int da_push_back(DArray* arr, int value){
    if(!_ensure_capacity(arr)){
        return 1;
    }
    int* p = arr->data + arr->size++;
    *p = value;
    return 0;
}

int* da_get(const DArray* arr, size_t index){
    if(index > arr->size - 1){
        fprintf(stderr, "da_get invalid index %zu\n", index);
        return NULL;
    }
    return &arr->data[index];
}


int da_set(DArray* arr, int value, size_t index){
    if(index > arr->size - 1){
        fprintf(stderr, "da_set invalid index %zu\n", index);
        return -1;
    }

    arr->data[index] = value;
    return 0;
}

void da_clear(DArray* arr){
    arr->size = 0;
    return;
}

size_t da_size(const DArray* arr){
    return arr->size;
}


size_t da_capacity(const DArray* arr){
    return arr->capacity;
}

#endif // __DARRAY_H__
