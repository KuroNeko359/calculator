//
// Created by KuroNeko359 on 2025/10/14.
//

#ifndef CALCULATOR_DYNAMIC_STACK_H
#define CALCULATOR_DYNAMIC_STACK_H
#define DYNAMIC_STATCH_ELEM_TYPE int
#include <stdbool.h>

typedef struct dynamic_list_node {
    struct dynamic_list_node *next;
    DYNAMIC_STATCH_ELEM_TYPE data;
} dynamic_list_node;

typedef struct {
    dynamic_list_node *top;
    int length;
} dynamic_stack;

dynamic_stack *dynamic_stack_init();

bool dynamic_stack_push(dynamic_stack *stack,DYNAMIC_STATCH_ELEM_TYPE data);

bool dynamic_stack_is_empty(dynamic_stack *stack);

DYNAMIC_STATCH_ELEM_TYPE dynamic_stack_pop(dynamic_stack *stack);

DYNAMIC_STATCH_ELEM_TYPE dynamic_stack_get_top(dynamic_stack *stack);

#endif //CSAPP_DYNAMIC_STACK_H
