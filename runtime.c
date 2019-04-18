/**
 * file: runtime.c
 * author: fyzbc
 * date: 2017年5月2日
 *
 */
#include "runtime.h"




/** \brief 获取指定寄存器的值
 *
 * \param lpRegisters 寄存器组
 * \param address 寄存器地址
 * \return
 *
 */
int readRegister(LpRegisters lpRegisters, int address){
    if(address<0||address>7){
        printf("[runtime.readRegister],输入数据有问题:%d!\n",address);
        exit(-1);
    }
    return lpRegisters->reg[address];
}


/** \brief 给指定寄存器设置值
 *
 * \param lpRegisters 寄存器组
 * \param address 寄存器地址
 * \param value 要写入的值
 * \return
 *
 */
int writeRegister(LpRegisters lpRegisters,int address, int value){
    if(address<0||address>7){
        printf("[runtime.readRegister],输入数据有问题:%d!\n",address);
        exit(-1);
    }
    lpRegisters->reg[address] = value;
    return 0;
}


/** \brief 初始化运行时栈
 *
 * \param codeStack 代码段
 * \param dataStack 数据段
 * \param lpRegisters 寄存器组
 * \return 运行时环境
 *
 */
LpRunTime initRunTime(Stack* codeStack, Stack* dataStack, LpRegisters lpRegisters){
    LpRunTime lpRunTime = (LpRunTime)malloc(sizeof(RunTime));
    if(lpRunTime==NULL){
            printf("without enough memory!");
            exit(-1);
    }
    lpRunTime->codeStack = codeStack;
    lpRunTime->dataStack = dataStack;
    lpRunTime->lpRegisters = lpRegisters;
    return lpRunTime;
}

/** \brief 从数据栈中读取数据
 *
 * \param lpRunTime 数据栈
 * \param address 需要取得数据的栈地址
 * \return
 *
 */
int readValueFromStack(LpStack dataStack,int address){
    return Hook(dataStack,address)->value;
}

/** \brief 将数据放入栈中
 *
 * \param dataStack 数据栈
 * \param address 需要取得数据的栈地址
 * \param data 需要放入栈中的数据
 * \return
 *
 */
void writeValueToStack(LpStack dataStack, int address, DataType data){
    Stick(dataStack,address,data);
}


/** \brief 从栈中得到数据。
 *      前置条件为，必须type指示符已经从栈中弹出。
 *
  * \param lpRunTime 运行时环境
 * \param type 操作类型
 * \param value 操作值
 * \return 返回获取的数据
 *
 */
int getDataByOperator(LpRunTime lpRunTime,int type,int value){
//    Stack* cStack = lpRunTime->codeStack;
    Stack* dStack = lpRunTime->dataStack;
    LpRegisters lpRegisters = lpRunTime->lpRegisters;
    int tmpValue = 0;
//    int type = Pop(cStack)->value;
//    int value = Pop(cStack)->value;
    switch(type){
    case V_VALUE:
        tmpValue = value;
        break;
    case V_REG:
        tmpValue = readRegister(lpRegisters,value);
        break;
    case V_STACK:
        tmpValue = readValueFromStack(dStack,value);
        break;
    case V_PV:
        tmpValue = readValueFromStack(dStack,value);
        tmpValue = readValueFromStack(dStack,tmpValue);
        break;
    default:
        printf("[runtime.getDataByOperator]wrong input！");
        exit(-1);
        break;
    }
    return tmpValue;
}


/** \brief 设置操作数据
 *
 * \param 运行时环境
 * \param 保留它成为别的类型的能力，现在暂时定为 int* 类型
 *
 */
void setDataByOperator(LpRunTime lpRunTime, int type, int address, int value){
//    Stack* cStack = lpRunTime->codeStack;
    DataType dataType = NULL;
    Stack* dStack = lpRunTime->dataStack;
    LpRegisters lpRegisters = lpRunTime->lpRegisters;
    int tmpValue = 0;
//    int type = Pop(cStack)->value;
//    int value = Pop(cStack)->value;
    switch(type){
    case V_REG:
        writeRegister(lpRegisters,address,value);
        break;
    case V_PV:
        // 这里无需关心具体类型，统一作为数据存储即可
    case V_STACK:
        dataType = (DataType)malloc(sizeof(DataElem));
        if(dataType==NULL){
            printf("[runtime.setDataByOperator]without enough memory!");
            exit(-1);
        }
        dataType->msg = NULL;
        dataType->type = TYPE_TP;
        dataType->value = value;
        writeValueToStack(dStack, address, dataType);
        break;
    default:
        printf("[runtime.getDataByOperator]wrong input！");
        exit(-1);
        break;
    }
    return tmpValue;
}


/** \brief 函数出栈运行
 *
 * \param lpRunTime 运行时环境
 * \param ret 函数的返回值，当runtime中的命令为ret时，直接返回该参数。
 * \return 返回运行时环境。
 *
 */
int runOneCommand(LpRunTime lpRunTime,int ret){

    Stack* cStack = lpRunTime->codeStack;
    Stack* dStack = lpRunTime->dataStack;
    LpRegisters lpRegisters = lpRunTime->lpRegisters;


    DataType dataType = Pop(cStack);
    int iType = dataType->value;
    switch(iType){
        case MOV:
            //printf("MOV\n");
            ret = movFunction(lpRunTime);
            break;
        case CAL:
            break;
        case POP:
            //printf("POP\n");
            ret = popFunction(lpRunTime);
            break;
        case RET:
            return ret;
        case ADD:
            //printf("ADD\n");
            ret = addFunction(lpRunTime);
            break;
        case AND:

            break;
        case NOT:

            break;
        case EQU:

            break;
        default :
            printf("[runtime.runOneCommand]please check your input!\n");
            exit(-1);
    }

}



/**____________________操作函数（中断向量）___________________________*/
// mov 1 to 0
int movFunction(LpRunTime lpRunTime){

    Stack* cStack = lpRunTime->codeStack;
    Stack* dStack = lpRunTime->dataStack;
    LpRegisters lpRegisters = lpRunTime->lpRegisters;

    int t1 = Pop(cStack)->value;
    int v1 = Pop(cStack)->value;
    int t2 = Pop(cStack)->value;
    int v2 = Pop(cStack)->value;

    //printf("MOV FROM:%d to %d\n",t2,v2);
    v2 = getDataByOperator(lpRunTime,t2,v2);
    //printf("MOV_RET:%d\n",v2);
    setDataByOperator(lpRunTime,t1,v1,v2);

    //v2 = getDataByOperator(lpRunTime,t2,v2);
    return v2;
}


// add 0 to 1
int addFunction(LpRunTime lpRunTime){

    Stack* cStack = lpRunTime->codeStack;
    Stack* dStack = lpRunTime->dataStack;
    LpRegisters lpRegisters = lpRunTime->lpRegisters;

    int tmp;
    int t1 = Pop(cStack)->value;
    int v1 = Pop(cStack)->value;
    int t2 = Pop(cStack)->value;
    int v2 = Pop(cStack)->value;

    //printf("ADD TO:%d to %d\n",t2,v2);

    v1 = getDataByOperator(lpRunTime,t1,v1);
    tmp = getDataByOperator(lpRunTime,t2,v2);
    v1 = v1+tmp;
    setDataByOperator(lpRunTime,t2,v2,v1);

    //printf("RET:%d\n",getDataByOperator(lpRunTime,t2,v2));

    //v2 = getDataByOperator(lpRunTime,t2,v2);
    return v2;
}


// pop 0 to 1
int popFunction(LpRunTime lpRunTime){

    Stack* cStack = lpRunTime->codeStack;
    Stack* dStack = lpRunTime->dataStack;
    LpRegisters lpRegisters = lpRunTime->lpRegisters;

    int t1 = Pop(cStack)->value;
    int v1 = Pop(cStack)->value;

    //printf("POP:%d\n",v1);
    v1 = getDataByOperator(lpRunTime,t1,v1);

    //printf("POP:%d\n",v1);

    //v2 = getDataByOperator(lpRunTime,t2,v2);
    return v1;
}




