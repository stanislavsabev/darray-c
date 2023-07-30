#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "darray.h"
#include "float_darray.h"

void print_v(int* v) {
    /* iterator over the vector using "iterator" style */
    if (v) {
        int* it;
        int i = 0;
        for (it = darr_begin(v); it != darr_end(v); ++it) {
            printf("v[%d] = %d\n", i, *it);
            ++i;
        }
    }
}

int main1(int argc, char* argv[]) {
    /* this is the variable that will store the array, you can have
     * a vector of any type! For example, you may write float *v = NULL,
     * and you'd have a vector of floats :-). NULL will have a size
     * and capacity of 0. Additionally, vector_begin and vector_end will
     * return NULL on a NULL vector. Alternatively, for clarity of writing
     * you can use the darr_vector_type macro to define a vector of a
     * given type.
     */

    (void)argc;
    (void)argv;

    /* add some elements to the back */
    darr_type(int) v = NULL;
    darr_push_back(v, 10);
    darr_push_back(v, 20);
    darr_push_back(v, 30);
    darr_push_back(v, 40);
    print_v(v);

    /* remove an element by specifying an array subscript */
    darr_remove(v, 2, NULL);
    print_v(v);

    /* remove an element from the back */
    int dest = 0;
    darr_pop_back(v, &dest);
    printf("dest at : %p, value %d\n", &dest, dest);

    /* print out some stats about the vector */
    printf("pointer : %p\n", (void*)v);
    printf("capacity: %zu\n", darr_capacity(v));
    printf("size    : %zu\n", darr_size(v));

    print_v(v);

    /* well, we don't have destructors, so let's clean things up */
    darr_free(v);

    return 0;
}

void print_fv(float** v) {
    /* iterator over the vector using "iterator" style */
    if (v) {
        float** it;
        int i = 0;
        for (it = darr_begin(v); it != darr_end(v); ++it) {
            printf("v[%d] = %f\n", i, **it);
            ++i;
        }
    }
}

int main(int argc, char* argv[]) {
    /* this is the variable that will store the array, you can have
     * a vector of any type! For example, you may write float *v = NULL,
     * and you'd have a vector of floats :-). NULL will have a size
     * and capacity of 0. Additionally, vector_begin and vector_end will
     * return NULL on a NULL vector. Alternatively, for clarity of writing
     * you can use the darr_vector_type macro to define a vector of a
     * given type.
     */

    (void)argc;
    (void)argv;

    /* add some elements to the back */
    darr_type(float*) v = NULL;
    printf("capacity: %zu\n", darr_capacity(v));
    printf("size    : %zu\n", darr_size(v));

    float* a = malloc(sizeof(float));
    float* b = malloc(sizeof(float));
    float* c = malloc(sizeof(float));
    float* d = malloc(sizeof(float));

    *a = 10;
    *b = 20;
    *c = 30;
    *d = 40;

    darr_push_back(v, a);
    darr_push_back(v, b);
    darr_push_back(v, c);
    darr_push_back(v, d);
    print_fv(v);

    float f = 0;
    float* dest = &f;

    /* remove an element by specifying an array subscript */
    darr_remove(v, 2, NULL);
    print_fv(v);

    /* remove an element from the back */
    darr_pop_back(v, &dest);
    printf("dest at : %p, value %f\n", &dest, *dest);

    float** back = darr_back(v);

    /* print out some stats about the vector */
    printf("pointer : %p\n", (void*)v);
    printf("capacity: %zu\n", darr_capacity(v));
    printf("size    : %zu\n", darr_size(v));
    printf("back    : %f\n", **back);
    darr_capacity(v);
    print_fv(v);

    /* well, we don't have destructors, so let's clean things up */
    darr_free(v);

    return 0;
}

// int main_2(int argc, char *argv[]) {

//     /* this is the variable that will store the array, you can have
//      * a vector of any type! For example, you may write float *v = NULL,
//      * and you'd have a vector of floats :-). NULL will have a size
//      * and capacity of 0. Additionally, vector_begin and vector_end will
//      * return NULL on a NULL vector. Alternatively, for clarity of
//      writing
//      * you can use the darr_vector_type macro to define a vector of a
//      * given type.
//      */

//     (void)argc;
//     (void)argv;

//     /* add some elements to the back */
//     darr_vector_type(float) v = NULL;
//     darr_push_back(v, 10 + 5);
//     darr_push_back(v, 20);
//     darr_push_back(v, 30);
//     darr_push_back(v, 40);

//     // /* remove an element by specifying an array subscript */
//     // darr_remove(v, 2);

//     // /* remove an element from the back */
//     // darr_pop_back(v, NULL);

//     // /* print out some stats about the vector */
//     // printf("pointer : %p\n", (void *)v);
//     // printf("capacity: %zu\n", darr_capacity(v));
//     // printf("size    : %zu\n", darr_size(v));

//     // /* iterator over the vector using "iterator" style */
//     // if (v) {
//     //     int *it;
//     //     int i = 0;
//     //     for (it = darr_begin(v); it != darr_end(v); ++it) {
//     //         printf("v[%d] = %d\n", i, *it);
//     //         ++i;
//     //     }
//     // }

//     // /* iterator over the vector standard indexing too! */
//     // if (v) {
//     //     size_t i;
//     //     for (i = 0; i < darr_size(v); ++i) {
//     //         printf("v[%zu] = %d\n", i, v[i]);
//     //     }
//     // }

//     /* well, we don't have destructors, so let's clean things up */
//     darr_free(v);

//     return 0;
// }