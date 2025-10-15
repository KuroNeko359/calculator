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

enum bracket {
    LEFT_PARENTHESIS,
    LEFT_SQUARE_BRACKET,
    LEFT_CURLY_BRACKET,
    RIGHT_PARENTHESIS,
    RIGHT_SQUARE_BRACKET,
    RIGHT_CURLY_BRACKET,
    INVALID_BRACKET
};

enum bracket bracket_parse_char(char str);

bool bracket_is_match(enum bracket left_bracket, enum bracket right_bracket);

bool bracket_match(char *str1);

/**
 * Input a postfix express, calculating its value.
 * @param str Input a postfix expression.
 */
int calculate(char * str);

bool is_operand(char str);

bool is_operator(char str);

char *parse_string(char *str);

int parse_string2int(char *str, int start, int end);

#endif //CALCULATOR_CALCULATOR_H