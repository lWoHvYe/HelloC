#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "string.h"

int a, b;

int main(int argc, const char *argv[]) {
    // insert code here...
    printf("Hello, World!\n");

    a = b + 1;
    __asm__ volatile  ("":: :"memory"); // Compiler Barrier

//    smp_mb();
    b = 0;
    int *c = &a;

    bool flag = true;

    printf(" a is %d\n", *c);
    printf("addr a is %p\n", c);
    printf("addr c is %p\n", &c);
    printf("flag is %d\n", flag);

    printf(" %f\n", sqrt(1001));

    char str[30] = "2030300 This is test";
    char *ptr;
    long ret;

    ret = strtol(str, &ptr, 10);
    printf("数字是 %6ld% 7.2f\n", ret, (float) ret);
    printf("字符串部分是 |%s|\n", ptr);
    printf("str value %s\n", str);

    char *firstName = "Wang";
    char *lastName = "Hongyan";
    char *name = malloc(strlen(firstName) + strlen(lastName));
    strcpy(name, firstName);
    strcat(name, lastName);
    printf(" strcpy + strcat: %s\n", name);

//    char *name = (char *) malloc(strlen(firstName) + strlen(lastName));
    sprintf(name, "%s %s", firstName, lastName);
    printf("sprintf : %s\n", name);

    printf("value in name (the addr of str) is : %p\n", name);
    printf("addr name is : %p\n", &name);

    return 0;
}
