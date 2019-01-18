#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack_int.h"

int main(void)
{
    stack_t *s = stack_new((stack_params_t){
        .clone = NULL, 
        .free = NULL
    });
    
    int data[] = {3, 4, 5, 6};
    int temp;
    for (size_t i = 0; i < 4; i++) {
        if (!stack_push(s, data[i])) {
            perror("Failed to push data\n");
            goto FREE;
        }
        
        temp = stack_peek(s);
        if (temp != data[i]) {
            fprintf(stderr, "Wrong data: %d\n", temp);
            goto FREE;
        }
    }
    
    int data1[] = {6, 5, 4, 3};
    for (size_t i = 0; i < 4; i++) {
        temp = stack_pop(s);
        if (temp != data1[i]) {
            fprintf(stderr, "Wrong data: %d\n", temp);
            goto FREE;
        }
    }

FREE:
    stack_free(s);
    
    return 0;
}