#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "loan.h"

int a, b;

char *strConcat(const char *firstName, const char *lastName, char **name);

void foo(char **name, char ***nameAddr);

int main(int argc, const char *argv[]) {
    // insert code here...
    printf("Hello, World!\n");

    a = b + 1;
    __asm__ volatile  ("":: :"memory"); // Compiler Barrier

//    smp_mb();
    b = 0;
    int *c = &a; // 将a的addr放到c中，&a获取a的addr

    bool flag = true;

    printf(" a is %d | %d\n", *c, a); //*c 输出c中地址处的内容，间接寻址
    printf("addr a is %p | %p\n", c, &a); // 输出c中的内容，即a的addr
    printf("addr c is %p\n", &c); // 输出c自身的addr
    printf("flag is %d\n", flag);

    printf(" %f\n", sqrt(1001)); // 开方
    printf(" %0.0f\n", pow(2., 10.)); // 乘方

    char str[30] = "2030300 This is test";
    char *ptr;
    long ret;

    ret = strtol(str, &ptr, 10); // strtol 将str根据base转成长整形，base指定了进制
    printf("数字是 %6ld% 7.2f\n", ret, (float) ret); // 对ret格式化输出
    printf("字符串部分是 |%s |%s |\n", ptr, *&ptr); // 输出字符串部分 输出里填ptr 和 *&ptr结果一样，库本身有做处理
    printf("str value %s ｜str addr is %p | %p\n", str, str, &str); // 当指定输出指针时，对string类型，str与&str是一样的


    // region str concat 字符串拼接
    char *firstName = "Wang";
    char *lastName = "Hongyan";
    // it is worth mentioning that the new operator is not part of C.
    // To allocate memory in the heap in a C program, you use a more primitive mechanism: a call to a function called malloc,
    // which takes one argument, the number of bytes to allocate, and returns a pointer of type void* to a newly allocated chunk of that many bytes.
    char *name = malloc((strlen(firstName) + strlen(lastName)) << 1); // 这里加不加 char *的强转都可以
    name = strConcat(firstName, lastName, &name); // 因为入参是name的addr，所以这里不赋值也可以

    char **nameAddr;
    foo(&name, &nameAddr);

    // If p is a pointer that was given to you using malloc, then statement
    //      free(p);
    // gives the memory pointed to by p back to the heap manager.
    free(name);

    // Local variable 'name' may point to deallocated memory
    printf("after free %p | %p | %s\n", nameAddr, name, name);

    printf("%lu %lu %lu %lu\n", sizeof(char), sizeof(short), sizeof(int), sizeof(long)); // 1/2/4/8
    // endregion

    loan_business();

    return 0;
}

// 注意下面两个方法中的参数name、nameAddr与调用方虽然重名，但不一样，确切说是调用方的addr，所以会多个*，调用时传的也是&
char *strConcat(const char *firstName, const char *lastName, char **name) {
    strcpy((*name), firstName); // 先把 firstName copy 到 name
    strcat((*name), " ");
    strcat((*name), lastName); // 再把 lastName 追加 到 name
    printf(" strcpy + strcat: %s\n", (*name));

//    char *name = (char *) malloc(strlen(firstName) + strlen(lastName));
    sprintf((*name), "%s %s", firstName, lastName); // 发送格式化输出到 name 指定的字符串
    printf("sprintf : %s\n", (*name));

    printf("value in name (the addr of str) is : %p\n", (*name)); // 输出name中存的val，也是个addr
    printf("addr name is : %p\n", name); // 输出name的addr

    return (*name);
}

// 抽取函数后，下面一些更清晰了，尤其是加了括号之后
void foo(char **name, char ***nameAddr) {
    // 下面这些还是有点复杂的，指针也有类型，不同类型产生了不同的结果，下面说的都是原类型，传入前的类型
    // 这个就是name的addr，这里的类型对下面影响较大，当前long *时能正常，因为编辑器是64位的，这里用char **更合理，因为name是char *
    (*nameAddr) = name; // 自动Extract Function，这里是 &name，显然是不对的，应该是name
    // 拿的就是name中存的addr，用char *比long *更合理，若nameAddr为char *这里为2位，short *这里为4位，int *这里为8位, long *这里为12位（这里都是16进制，要再乘以4才是实际的位数）
    // 当nameAddr是 char **时，这里用char *就理所当然了
    char *nna = *(*nameAddr); // 这里的类型好像并不影响结果
    printf("addr of nameAddr %p\n", (*nameAddr)); // 输出name的addr
    printf("val in nameAddr %p | %p\n", nna, *(*nameAddr)); // 输出name中存的val，也是个addr
    printf("val %s | %s\n", nna, *(*nameAddr)); // 输出str
}