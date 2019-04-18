/**
 * file: runtime.h
 * author: fyzbc
 * date: 2017年5月2日
 *
 */

#ifndef _RUNTIME
#define _RUNTIME

#include "zstack.h"
#include "tools.h"


/*------------定义寄存器---------------*/
struct RegistersStruct{

    
    int reg[8]; // 寄存器组

    int ip; // 指令段段内偏移。
    int bp; // 数据段段内偏移。

    int sp; // 堆栈指针
    int si; // 源变址
    int di; // 目的变址
    int flag;// 标志寄存器

};

typedef struct RegistersStruct Registers;
typedef struct RegistersStruct* LpRegisters;

/*---------------end-----------------*/

// 运行时数据结构
struct RunTimeStruct{

    // 代码段
    Stack* codeStack;
    // 数据段
    Stack* dataStack;
    // 寄存器组
    LpRegisters lpRegisters;

};

typedef struct RunTimeStruct RunTime;
typedef struct RunTimeStruct* LpRunTime;



/** \brief 获取指定寄存器的值
 *
 * \param
 * \param
 * \return
 *
 */
int readRegister(LpRegisters lpRegisters, int address);

/** \brief 给指定寄存器设置值
 *
 * \param
 * \param
 * \return
 *
 */
int writeRegister(LpRegisters lpRegisters,int address, int value);


/** \brief 初始化运行时工具
 *
 * \param codeStack 代码段
 * \param dataStack 数据段
 * \param lpRegister 寄存器组
 * \return 构成成功的运行时环境
 *
 */
LpRunTime initRunTime(Stack* codeStack, Stack* dataStack,LpRegisters lpRegisters);


/** \brief 从内存中读取数据
 *
 * \param lpRunTime 运行时环境
 * \param order 需要取得数据的栈地址
 * \return
 *
 */
int readValueFromStack(LpStack dataStack,int order);

/** \brief 从数据栈中读取数据
 *
 * \param lpRunTime 运行时环境
 * \param order 需要取得数据的栈地址
 * \return
 *
 */
void writeValueToStack(LpStack dataStack, int order, DataType data);


/*
下面开始正式的解析
*/

/*-------------------下面开始正式执行----------------------*/

/** \brief 得到数据。
 *      前置条件为，必须type指示符已经从栈中弹出。
 *
  * \param lpRunTime 运行时环境
 * \param type 操作类型
 * \param value 操作值
 * \return 返回获取的数据
 *
 */
int getDataByOperator(LpRunTime lpRunTime,int type,int value);


/** \brief 设置操作数据
 *
 * \param 运行时环境
 * \param 保留它成为别的类型的能力，现在暂时定为 int* 类型
 * \return 返回操作结果
 *
 */
void setDataByOperator(LpRunTime lpRunTime, int type, int address, int value);



/** \brief 函数出栈运行
 *
 * \param
 * \param
 * \return
 *
 */
int runOneCommand(LpRunTime lpRunTime,int ret);


/**_______________________________________________*/


/* 以下为具体的函数实现 */
int movFunction(LpRunTime lpRunTime);
/* 加法运算 */
int addFunction(LpRunTime lpRunTime);
/* 出栈 */
int popFunction(LpRunTime lpRunTime);



#endif // RUNTIME
