#include <stdio.h>
#include "calculator.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        calculate(argv);
    }
    else if (argc <= 1) {
        char *str1[100];
        printf("calculate>");
        scanf("%s",&str1);
        // printf("Postfix:%s\n",new_str);
        printf("result:%d\n",calculate(str1));
    }
    return 0;
}