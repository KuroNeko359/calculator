//
// Created by KuroNeko359 on 2025/10/14.
//
#include "calculator.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_stack.h"

char calculate_elem(char num1, char num2, enum operator operator) {
    switch (operator) {
        case PLUS: return num1 + num2;
        case MINUS: return num1 - num2;
        case MULTIPLY: return num1 * num2;
        case DIVIDE: return num1 / num2;
    }
}

void calculate(char *str) {
    dynamic_stack *stack = dynamic_stack_init();

    for (int i = 0; i < strlen(str); i++) {
        if (is_operand(str[i])) {
            dynamic_stack_push(stack, str[i]);
        } else if (is_operator(str[i])) {
            char num1 = dynamic_stack_pop(stack);
            char num2 = dynamic_stack_pop(stack);
            dynamic_stack_push(stack, calculate_elem(num1, num2, str[i]));
        }
    }
}


bool is_operand(char str) {
    return !is_operator(str);
}

bool is_bracket(char str) {
    return str == '(' || str == ')';
}


bool is_operator(char str) {
    switch (str) {
        case PLUS:
        case MINUS:
        case MULTIPLY:
        case DIVIDE:
            return true;
        default:
            return false;
    }
}

int get_priority(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default: return 0;
    }
}

char *parse_string(char *str) {
    dynamic_stack *operator_stack = dynamic_stack_init();
    int len = strlen(str);
    char *new_str = malloc((len + 1) * sizeof(char));
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (is_operand(str[i])) {
            new_str[index] = str[i];
            index++;
            printf("%s\n", new_str);
        } else if (is_bracket(str[i])) {
            if (str[i] == '(') {
                printf("str[i] == '('");
                dynamic_stack_push(operator_stack, str[i]);
            } else if (str[i] == ')') {
                printf("str[i] == ')'");
                while (dynamic_stack_get_top(operator_stack) != '(') {
                    new_str[index++] = dynamic_stack_pop(operator_stack);
                }
            }
        } else if (is_operator(str[i])) {
            if (dynamic_stack_is_empty(operator_stack))
                dynamic_stack_push(operator_stack, str[i]);
            char top = dynamic_stack_get_top(operator_stack);
            if (get_priority(top) < get_priority(str[i])) {
                new_str[index++] = str[i + 1];
                new_str[index++] = str[i++];
                new_str[index++] = dynamic_stack_pop(operator_stack);
            }
            printf("%s\n", new_str);
        }
    }
    while (!dynamic_stack_is_empty(operator_stack)) {
        new_str[index++] = dynamic_stack_pop(operator_stack);
    }
    new_str[index] = '\0';
    return new_str;
}
