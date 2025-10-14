//
// Created by KuroNeko359 on 2025/10/14.
//
#include <stdlib.h>
#include "dynamic_stack.h"

#include <stdio.h>


dynamic_stack *dynamic_stack_init() {
    dynamic_stack *stack = malloc(sizeof(dynamic_stack));
    stack->top = NULL;
    stack->length = 0;
    return stack;
}

bool dynamic_stack_push(dynamic_stack *stack,DYNAMIC_STATCH_ELEM_TYPE data) {
    dynamic_list_node *node = malloc(sizeof(dynamic_list_node));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->length++;
    return true;
}

bool dynamic_stack_is_empty(dynamic_stack *stack) {
    return stack->top == NULL;
}

DYNAMIC_STATCH_ELEM_TYPE dynamic_stack_pop(dynamic_stack *stack) {
    if (dynamic_stack_is_empty(stack)) {
        printf("dynamic_stack_pop:Stack is empty.");
        exit(-1);
    }
    DYNAMIC_STATCH_ELEM_TYPE top_data = stack->top->data;
    if (stack->top->next == NULL) {
        stack->top = NULL;
        return top_data;
    }
    stack->top = stack->top->next;
    return top_data;
}

DYNAMIC_STATCH_ELEM_TYPE dynamic_stack_get_top(dynamic_stack *stack) {
    if (dynamic_stack_is_empty(stack)) {
        printf("dynamic_stack_get_top:Stack is empty.");
        exit(-1);
    }
    return (stack->top)->data;
}
