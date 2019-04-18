/**
 * file: runtime.c
 * author: fyzbc
 * date: 2017��5��2��
 *
 */
#include "runtime.h"




/** \brief ��ȡָ���Ĵ�����ֵ
 *
 * \param lpRegisters �Ĵ�����
 * \param address �Ĵ�����ַ
 * \return
 *
 */
int readRegister(LpRegisters lpRegisters, int address){
    if(address<0||address>7){
        printf("[runtime.readRegister],��������������:%d!\n",address);
        exit(-1);
    }
    return lpRegisters->reg[address];
}


/** \brief ��ָ���Ĵ�������ֵ
 *
 * \param lpRegisters �Ĵ�����
 * \param address �Ĵ�����ַ
 * \param value Ҫд���ֵ
 * \return
 *
 */
int writeRegister(LpRegisters lpRegisters,int address, int value){
    if(address<0||address>7){
        printf("[runtime.readRegister],��������������:%d!\n",address);
        exit(-1);
    }
    lpRegisters->reg[address] = value;
    return 0;
}


/** \brief ��ʼ������ʱջ
 *
 * \param codeStack �����
 * \param dataStack ���ݶ�
 * \param lpRegisters �Ĵ�����
 * \return ����ʱ����
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

/** \brief ������ջ�ж�ȡ����
 *
 * \param lpRunTime ����ջ
 * \param address ��Ҫȡ�����ݵ�ջ��ַ
 * \return
 *
 */
int readValueFromStack(LpStack dataStack,int address){
    return Hook(dataStack,address)->value;
}

/** \brief �����ݷ���ջ��
 *
 * \param dataStack ����ջ
 * \param address ��Ҫȡ�����ݵ�ջ��ַ
 * \param data ��Ҫ����ջ�е�����
 * \return
 *
 */
void writeValueToStack(LpStack dataStack, int address, DataType data){
    Stick(dataStack,address,data);
}


/** \brief ��ջ�еõ����ݡ�
 *      ǰ������Ϊ������typeָʾ���Ѿ���ջ�е�����
 *
  * \param lpRunTime ����ʱ����
 * \param type ��������
 * \param value ����ֵ
 * \return ���ػ�ȡ������
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
        printf("[runtime.getDataByOperator]wrong input��");
        exit(-1);
        break;
    }
    return tmpValue;
}


/** \brief ���ò�������
 *
 * \param ����ʱ����
 * \param ��������Ϊ������͵�������������ʱ��Ϊ int* ����
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
        // ����������ľ������ͣ�ͳһ��Ϊ���ݴ洢����
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
        printf("[runtime.getDataByOperator]wrong input��");
        exit(-1);
        break;
    }
    return tmpValue;
}


/** \brief ������ջ����
 *
 * \param lpRunTime ����ʱ����
 * \param ret �����ķ���ֵ����runtime�е�����Ϊretʱ��ֱ�ӷ��ظò�����
 * \return ��������ʱ������
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



/**____________________�����������ж�������___________________________*/
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




