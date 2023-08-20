#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "loan.h"
#include "concurrent.h"

int a, b;

char *strConcat(const char *firstName, const char *lastName, char **pName);

void foo(char **, char ***);

void copy_string(char *, char *);

int main(int argc, const char *argv[]) {
    // insert code here...
    printf("Hello, World!\n");

    a = b + 1;
    __asm__ volatile  ("":: :"memory"); // Compiler Barrier

//    smp_mb();
    b = 0;
    int *c = &a; // 将a的addr放到c中，&a获取a的addr，这里的*表示指针变量

    bool flag = true;

    printf(" a is %d | %d\n", *c, a); //*c 输出c中地址处的内容，间接寻址，这里的*表示该指针变量所指向的变量，即a
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

    char str1[5], str2[5], str3[5];
    printf("please begin input\n");
    // scanf函数中的输入项如果是字符数组名，不要再加地址符号 &，另因为系统把空格字符作为输入字符串之间的分隔符，所以若输入的内容中包含空格，要使用多个数组接收，
    // 而这里却可能出现些问题（比如每个由空格分隔的字符串输入的长度要<str.length，需要再看看）
    scanf("%s%s%s", str1, str2, str3);
    printf("%s %s %s\n", str1, str2, str3);

    void (*pCopy)(char *, char *);
    pCopy = copy_string;

    char *orStr = "I am a teacher.";
    char ovStr[] = "I am a lonely student."; // 这里不能是指针变量，因为字符指针变量指向的字符串·常量·中的内容是不可以被取代的
    printf("%s\n", ovStr);
    (*pCopy)(orStr, ovStr); // 可以 char *p = ovStr，然后这里传p。然后这里指向函数的指针pCopy，调用时用 pCopy和 *pCopy都可以
    printf("%s\n", ovStr);

    // region str concat 字符串拼接
    char *firstName = "Wang";
    char *lastName = "Hongyan";
    // it is worth mentioning that the new operator is not part of C.
    // To allocate memory in the heap in a C program, you use a more primitive mechanism: a call to a function called malloc,
    // which takes one argument, the number of bytes to allocate, and returns a pointer of type void* to a newly allocated chunk of that many bytes.
    char *name = malloc((strlen(firstName) + strlen(lastName)) << 1); // 这里加不加 char *的强转都可以
    strConcat(firstName, lastName, &name); // 因为入参是name的addr，所以这里不赋值也可以；name = strConcat()

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

    test_demo();

    return 0;
}

// 注意下面两个方法中的参数name、nameAddr与调用方虽然重名，但不一样，确切说是调用方的addr，所以会多个*，调用时传的也是&
// 在程序中通过变量名引用变量的值，所以输出时输出的也即是变量的值了
char *strConcat(const char *firstName, const char *lastName, char **pName) { // pName是指向指针变量name的指针变量，所以使用时加了*
    strcpy((*pName), firstName); // 先把 firstName copy 到 name
    strcat((*pName), " ");
    strcat((*pName), lastName); // 再把 lastName 追加 到 name
    printf(" strcpy + strcat: %s\n", (*pName));

//    char *name = (char *) malloc(strlen(firstName) + strlen(lastName));
    sprintf((*pName), "%s %s", firstName, lastName); // 发送格式化输出到 name 指定的字符串
    printf("sprintf : %s\n", (*pName));
    // 关于str 的 addr，实际上是str中第一个字符的addr，输出时会自动访问下一个，直到 '\0'
    printf("value in name (the addr of str) is : %p\n", (*pName)); // 输出name中存的val，也是个addr
    printf("addr of name is : %p\n", pName); // 输出name的addr

    return (*pName);
}

// 抽取函数后，下面一些更清晰了，尤其是加了括号之后
void foo(char **pName, char ***pNameAddr) { // name是char*, nameAddr是char**，入参分别为 &name和&nameAddr，所以使用时会加一个*
    // ignored:下面这些还是有点复杂的，指针也有类型，不同类型产生了不同的结果，下面说的都是原类型，传入前的类型
    // 0402: 看了教材后，比较清晰了，定义指针变量时必须指定其 基类型，即此指针变量指向的变量的类型。之前把指针单纯看成地址了（漏掉了基类型），所以有了下面的尝试
    // ignored:这个就是name的addr，这里的类型对下面影响较大，当前long *时能正常，因为编辑器是64位的，但这里用char **更合理，因为name是char *
    (*pNameAddr) = pName; // 自动Extract Function，这里是 &pName，显然是不对的，应该是pName，表示调用方中`name`的addr
    // ignored:拿的就是name中存的addr，若nameAddr为char *这里为2位，short *这里为4位，int *这里为8位, long *这里为12位（这里都是16进制，要再乘以4才是实际的位数）
    // 当nameAddr是 char **时，这里用char *就理所当然了。这里str 的 addr 同样是其第一个字符的addr
    char *nna = *(*pNameAddr); // name 中的val，即addr of str
    printf("addr of name / val in nameAddr: %p | %p\n", pName, (*pNameAddr)); // 输出`name`的addr，addr of name
    printf("addr of str / val in name: %p | %p\n", nna, *(*pNameAddr)); // 输出`name`中存的val，也是个addr，addr of str
    printf("val of str: %s | %s\n", nna, *(*pNameAddr)); // 输出`name`指向的变量的val, str
}

void copy_string(char *from, char *to) {
    while ((*to++ = *from++));
//    for (; (*to++ = *from++););
}