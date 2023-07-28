#include <stdio.h>
#include <assert.h>

#include "darray.h"


void print_arr(const DArray* arr){
    for (size_t i = 0; i < arr->size; i++)
    {
        int* p;
        if((p = da_get(arr, i)) != NULL){
            printf("%zu: %d\n", i, *p);
        }
    }
}


int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    DArray arr = da_create();
    printf("Arr %p, has size %zu and capacity %zu\n", &arr, da_size(&arr), da_capacity(&arr));
    da_push_back(&arr, 5);
    da_push_back(&arr, 1);
    da_push_back(&arr, 7);
    // print_arr(&arr);
    
    size_t ndx = 2;
    int* a = da_get(&arr, ndx);
    printf("Index %zu, value %d\n", ndx, *a);
    da_set(&arr, 2, ndx);
    a = da_get(&arr, ndx);
    printf("Index %zu, new value %d\n", ndx, *a);
    printf("Arr %p, has size %zu and capacity %zu\n", &arr, da_size(&arr), da_capacity(&arr));
    // print_arr(&arr);
    da_clear(&arr);
    printf("After clear\nArr %p, has size %zu and capacity %zu\n", &arr, da_size(&arr), da_capacity(&arr));
    
    da_destroy(&arr);
    assert(arr.data == NULL); 
    return 0;
}
