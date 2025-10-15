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

int calculate_number(int num1, int num2, enum operator operator) {
    switch (operator) {
        case PLUS: return num1 + num2;
        case MINUS: return num1 - num2;
        case MULTIPLY: return num1 * num2;
        case DIVIDE: {
            if (num2 == 0) {
                printf("Error: div0");
                exit(EXIT_FAILURE);
            }
            return num1 / num2;
        };
    }
}

int fast_pow(int base, int exponent) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return result;
}

int parse_char2int(char c) {
    if (!is_operand(c)) return 0;
    return c - '0';
}

// TODO The bug that return 0
int parse_string2int(char *str, int start, int end) {
    int number = 0;
    int m = 0;
    for (int i = end; i >= start; i--) {
        number += parse_char2int(str[i]) * fast_pow(10, m);
        m++;
    }
    return number;
}

int calculate(char *str) {
    printf("calculating:                %s\n",str);
    dynamic_stack *result_stack = dynamic_stack_init();
    printf("%s\n", parse_string(str));
    char *parsed_string = parse_string(str);
    printf("calculating postfix:        %s\n",parsed_string);
    int last_space = -1;
    for (int i = 0; i < strlen(parsed_string)-1; i++) {
        printf("resloving %c\n",parsed_string[i]);
        if (parsed_string[i] == ' ') {

            int number = parse_string2int(parsed_string,
                                          last_space + 1, i - 1);
            last_space = i;
            dynamic_stack_push(result_stack, number);
            printf("It is operand %d, put into stack.\n",number);
        }
        if (is_operator(parsed_string[i])) {
            printf("It is operator, calculating from stack.\n");
            int num1 = dynamic_stack_pop(result_stack);
            int num2 = dynamic_stack_pop(result_stack);
            dynamic_stack_push(
                result_stack,
                calculate_number(num1, num2, parsed_string[i]
                ));
            printf("It is operator, calculating from stack, result:%d.\n",calculate_number(num1, num2, parsed_string[i]
            ));
        }
    }
    return result_stack->top->data;
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
        if (str[i] == '(') {
            dynamic_stack_push(stack, str[i]);
            continue;
        }
        if (str[i] == ')') {
            while (!is_bracket(dynamic_stack_get_top(stack))) {
                new_str[index++] = dynamic_stack_pop(stack);
                new_str[index++] = ' ';
            }
            continue;
        }

        if (is_operand(str[i])) {
            while (is_operand(str[i])) {
                new_str[index++] = str[i];
                i++;
            }
            new_str[index++] = ' ';
            i--;
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
                        new_str[index++] = ' ';
                    }
                    if (!dynamic_stack_is_empty(stack)) {
                        top_elem = dynamic_stack_get_top(stack);
                    } else {
                        break;
                    }
                }
                dynamic_stack_push(stack, str[i]);
            }
            continue;
        }
    }

    while (!dynamic_stack_is_empty(stack)) {
        char pop = dynamic_stack_pop(stack);
        if (!is_bracket(pop)) {
            new_str[index++] = pop;
            new_str[index++] = ' ';
        };
    }
    new_str[index] = '\0';
    return new_str;
}
