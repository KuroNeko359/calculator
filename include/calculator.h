//
// Created by KuroNeko359 on 2025/10/14.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H
#include <stdbool.h>

enum operator {
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    DIVIDE = '/'
};

/**
 * Input a postfix express, calculating its value.
 * @param str Input a postfix expression.
 */
void calculate(char * str);

bool is_operand(char str);

bool is_operator(char str);

char *parse_string(char *str);

#endif //CALCULATOR_CALCULATOR_H