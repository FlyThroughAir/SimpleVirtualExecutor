/**
 * file: tools.h
 * author: fyzbc
 * date: 2017年5月2日
 *
 */

#ifndef _TOOLS
#define _TOOLS
#include <stdio.h>
#include "zstack.h"

#define STACK_LENGTH 1024
/**
* 定义几目运算符
*/
#define EYES_ZERO   0
#define EYES_ONE    1
#define EYES_TWO    2


/**
预定义操作符合指示类型
*/
#define MOV 0 //000 双目
#define CAL 1 //001 双目
#define POP 2 //010 单目 从代码栈中弹出
#define RET 3 //011 弹幕
#define ADD 4 //100 双目
#define AND 5 //101 双目
#define NOT 6 //110 单目
#define EQU 7 //111 单目

/*----------定义地址类型-----------*/
#define V_VALUE 0  //00 值
#define V_REG   1  //01 寄存器地址
#define V_STACK 2  //10 栈地址内为值
#define V_PV    3  //11 栈上地址内的值为一个栈地址。


// 定义不同地址类型长度以及指示符本身长度
#define V_TYPE_LEN  2  //00 值
#define V_VALUE_LEN 8  //00 值
#define V_REG_LEN   3  //01 寄存器地址
#define V_STACK_LEN 7  //10 栈地址内为值
#define V_PV_LEN    7  //11 栈上地址内的值为一个栈地址。


// 定义操作符代号
#define TYPE_OP 0 // 操作符
#define TYPE_TP 1 // 类型
#define TYPE_VL 2 // 值

/*--------------此处定义工具----------------------*/




// 读取文件文件，并返回读入的数据长度。
int readFile(char* fileName,char** contentBuf);

// 读二进制文件
void readBinaryFile(char fileName[]);


/** \brief 将字符串转换成整数.传入的字符串需要倒叙.
 *
 * \param S[] 需要转换的字符串
 * \return 整数
 *
 */

int StrToInt(char s[]);

/** \brief 开辟空间获取子串
 *
 * \param
 * \param
 * \return
 *
 */

char* getSubString(char a_str[], int start, int len);

/** \brief 反转字符串
 *
 * \param
 * \param
 * \return
 *
 */
char* reverseCode(char str[]);


void* showOpData(void* obj1,void* obj2);
void* showTpData(void* obj1,void* obj2);
void* showVlData(void* obj1,void* obj2);


#endif
