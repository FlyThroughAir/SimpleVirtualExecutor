/**
 * file: main.c
 * author: fyzbc
 * date: 2017��5��2��
 *
 */

#include "main.h"


//typedef enum Registers{
//	A, B, C, D, E, F, SP, PC, SF, ZF,
//	NUM_OF_REGISTERS
//} Registers;


/**
 * ִ����
 */
int execute(LpRunTime lpRunTime){
    Stack* stack = lpRunTime->codeStack;
    int ret = 0;
    while(!Empty(stack))
    {
        // ����һ������
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
	// ������ջ
	DataToStack(codeStack,buf,len);
	//travelStack(codeStack);

    // ��ʼ������ʱ����
    lpRunTime = initRunTime(codeStack,dataStack,lpRegisters);
    //travelStack(lpRunTime->codeStack);
    int ret = execute(lpRunTime);
    printf("%d",ret);
    return 0;
}
