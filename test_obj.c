#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack_obj.h"

int_obj_t * obj_new(int data)
{
    int_obj_t *o = malloc(sizeof(int_obj_t));
    if (!o) {
        return o;
    }
    
    o->data = data;
    
    return o;
}

void * obj_clone(void *obj)
{
    return obj_new(((int_obj_t *) obj)->data);
}

void obj_free(void *obj)
{
    free(obj);
}

int main(void)
{
    stack_t *s = stack_new((stack_params_t){
        .clone = obj_clone, 
        .free = obj_free
    });
    
    int data[] = {3, 4, 5, 6};
    int_obj_t *temp;
    for (size_t i = 0; i < 4; i++) {
        temp = obj_new(data[i]);
        if (!stack_push(s, temp)) {
            perror("Failed to push data\n");
            obj_free(temp);
            goto FREE;
        }
        
        temp = stack_peek(s);
        if (temp->data != data[i]) {
            fprintf(stderr, "Wrong data: %d\n", temp->data);
            obj_free(temp);
            goto FREE;
        }
        obj_free(temp);
    }
    
    int data1[] = {6, 5, 4, 3};
    for (size_t i = 0; i < 4; i++) {
        temp = stack_pop(s);
        if (temp->data != data1[i]) {
            fprintf(stderr, "Wrong data: %d\n", temp->data);
            obj_free(temp);
            goto FREE;
        }
        obj_free(temp);
    }

FREE:
    stack_free(s);
    
    return 0;
}