//
// Created by KuroNeko359 on 2025/10/14.
//
#include "calculator.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_stack.h"

enum bracket bracket_parse_char(char str) {
    switch (str) {
        case '(': return LEFT_PARENTHESIS;
        case ')': return RIGHT_PARENTHESIS;
        case '[': return LEFT_SQUARE_BRACKET;
        case ']': return RIGHT_SQUARE_BRACKET;
        case '{': return LEFT_CURLY_BRACKET;
        case '}': return RIGHT_CURLY_BRACKET;
        default: return INVALID_BRACKET;
    }
}

bool bracket_is_match(enum bracket left_bracket, enum bracket right_bracket) {
    return (left_bracket + 3 == right_bracket);
}


bool bracket_match(char *str) {
    dynamic_stack *stack = dynamic_stack_init();
    for (int i1 = 0; i1 < strlen(str); i1++) {
        enum bracket recent_bracket = bracket_parse_char(str[i1]);
        if (recent_bracket == 6) continue;
        if (recent_bracket < 3) {
            dynamic_stack_push(stack, recent_bracket);
        } else if (recent_bracket >= 3 && recent_bracket < 6) {
            if (dynamic_stack_is_empty(stack)) {
                return false;
            }
            if (bracket_is_match(dynamic_stack_get_top(stack),
                                 recent_bracket)) {
                dynamic_stack_pop(stack);
            }
        }
    }
    return dynamic_stack_is_empty(stack);
}

char calculate_elem(char num1, char num2, enum operator operator) {
    num1 = num1 - '0';
    num2 = num2 - '0';
    switch (operator) {
        case PLUS: return num1 + num2 + '0';
        case MINUS: return num1 - num2 + '0';
        case MULTIPLY: return num1 * num2 + '0';
        case DIVIDE: {
            if (num2 == 0) {
                printf("Error: div0");
                exit(EXIT_FAILURE);
            }
            return num1 / num2 + '0';
        };
    }
}

int calculate(char *str) {
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
    return stack->top->data;
}


bool is_operand(char str) {
    return str >= 48 && str <= 57;
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
    // Check syntax error.
    // Bracket it not appear in pairs.
    if (!bracket_match(str)) {
        printf("Syntax error.");
        exit(-2);
    }
    // TODO There are a operator (except -) before a number.
    if (true) {
    }
    dynamic_stack *stack = dynamic_stack_init();
    char *new_str = malloc((strlen(str) + 1) * 10 * sizeof(char));
    int index = 0;
    for (int i = 0; i < strlen(str); i++) {
        printf("%s\n", new_str);
        if (str[i] == '(') {
            dynamic_stack_push(stack, str[i]);
            continue;
        }
        if (str[i] == ')') {
            while (!is_bracket(dynamic_stack_get_top(stack))) {
                new_str[index++] = dynamic_stack_pop(stack);
            }
            continue;
        }
        if (is_operand(str[i])) {
            new_str[index++] = str[i];
            continue;
        }
        if (is_operator(str[i])) {
            if (dynamic_stack_is_empty(stack) ||
                is_bracket(dynamic_stack_get_top(stack))) {
                dynamic_stack_push(stack, str[i]);
            } else {
                char top_elem = dynamic_stack_get_top(stack);
                while (!dynamic_stack_is_empty(stack) &&
                       get_priority(top_elem) >= get_priority(str[i])) {
                    if (!is_bracket(dynamic_stack_get_top(stack))) {
                        new_str[index++] = dynamic_stack_pop(stack);
                    }
                    if (!dynamic_stack_is_empty(stack)) {
                        top_elem = dynamic_stack_get_top(stack);
                    } else {
                        break;
                    }
                }
                dynamic_stack_push(stack, str[i]);
            }
        }
    }

    while (!dynamic_stack_is_empty(stack)) {
        char pop = dynamic_stack_pop(stack);
        if (!is_bracket(pop)) new_str[index++] = pop;
    }
    new_str[index] = '\0';
    return new_str;
}
