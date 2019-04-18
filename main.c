/**
 * file: main.c
 * author: fyzbc
 * date: 2017年5月2日
 *
 */

#include "main.h"


//typedef enum Registers{
//	A, B, C, D, E, F, SP, PC, SF, ZF,
//	NUM_OF_REGISTERS
//} Registers;


/**
 * 执行器
 */
int execute(LpRunTime lpRunTime){
    Stack* stack = lpRunTime->codeStack;
    int ret = 0;
    while(!Empty(stack))
    {
        // 运行一个命令
        ret = runOneCommand(lpRunTime,ret);
    }
    return ret;
}

int main() {
    char* buf=NULL;
	char* substring = NULL;

	Stack* codeStack = init(STACK_LENGTH);
	Stack* dataStack = init(STACK_LENGTH);
	LpRegisters lpRegisters = (LpRegisters)malloc(sizeof(Registers));
    LpRunTime lpRunTime = NULL;

	int len = readFile("data.txt",&buf);
	// 代码入栈
	DataToStack(codeStack,buf,len);
	//travelStack(codeStack);

    // 初始化运行时环境
    lpRunTime = initRunTime(codeStack,dataStack,lpRegisters);
    //travelStack(lpRunTime->codeStack);
    int ret = execute(lpRunTime);
    printf("%d",ret);
    return 0;
}
