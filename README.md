# Dynamic array in C

An implementation of type safe, dynamic array in C.

It is using extra padding in the front as storage for meta-data about capacity and size.

The user is given a pointer to first element of the `data`.

## Usage:

```c
#include <stdio.h>

#include "darray.h"

void print_arr(int* arr);

int main(int argc, char* argv[]) {

    (void)argc;
    (void)argv;

    // add some elements
    darr_type(int) arr = NULL;
    darr_append(arr, 10);
    darr_append(arr, 20);
    darr_append(arr, 30);
    darr_append(arr, 40);
    print_arr(arr);

    // accessing elements is same as with normal array
    printf("arr[2] is: %d\n", arr[2]);
    
    // remove an element at index
    size_t i = 2;
    darr_remove(arr, i, NULL);
    print_arr(arr);

    // pop element from the back
    int dest = 0;
    darr_pop_back(arr, &dest);
    printf("popped value %d at %p\n", dest, &dest);
    
    // print out some stats
    printf("pointer   : %p\n", (void*)arr);
    printf("capacity  : %zu\n", darr_capacity(arr));
    printf("size      : %zu\n", darr_len(arr));
    printf("last elem : %d \n\n", *darr_back(arr));

    // free the memory (frees the meta data too)
    darr_free(arr);
    return 0;
}

void print_arr(int* arr) {
    /* iterator over the vector using "iterator" style */
    if (arr) {
        int* it;
        int i = 0;
        for (it = darr_begin(arr); it != darr_end(arr); ++it) {
            printf("arr[%d] = %d\n", i, *it);
            ++i;
        }
    }
}

```


## Credit to
https://github.com/eteran/c-vector - used as original source


