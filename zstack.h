/**
 * file: zstack.h
 * author: fyzbc
 * date: 2017年5月2日
 *
 */

#ifndef _ZSTACK
#define _ZSTACK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "tools.h"


/*--------------定义其他的数据或者结构体-----------------------*/

struct Data{
    /* 读入的信息（源信息） */
    char* msg; // 源信息码

    /* 定义码（操作指示灯） */
    int value; // 存储着数值

    /* 类型（和入哪个栈相关） */
    int type; // 0表示操作符，1表示类型指示符，2表示值

    /* 函数指针，指向一个可运行的函数或者空。
        如果该Data解析为操作，
        那么执行该函数，运行此条语句，否则，忽略该参数。
     */
    void* (*readFun)(void*,void*); //void*可以很方便的转换成其他的指针类型。
    void* (*writeFun)(void*,void*); //一般单目或者二目运算符都需要写操作。
    void* (*lookFun)(void*,void*);
};



/*-----------实现一个顺序栈------------------------*/
// 定义栈存储的数据类型
typedef struct Data DataElem;
typedef struct Data* DataType;



//Sequence Stack 实现顺序栈，使用数组来实现
struct stack
{
    DataType* data;
    int top;
    int maxsize;
};


typedef struct stack Stack;
typedef struct stack* LpStack;
// 初始化栈
Stack* init(int maxsize);
// 判断栈是否为空
bool Empty(Stack* s);
// 判断栈是否已满了
bool full(Stack* s);
// 入栈
void Push(Stack* s,DataType element);
// 出栈
DataType Pop(Stack* s);
// 取栈顶元素
DataType Top(Stack* s);
// 钩子，钩取栈中元素
DataType Hook(Stack* s,int order);
// 棍子，将元素送到栈中指定位置，覆盖写
void Stick(Stack* s,int order,DataType element);
// 销毁栈
void Destroy(Stack* s);
// 遍历栈
void travelStack(Stack* s);
/*---------------end----------------------*/




#endif
