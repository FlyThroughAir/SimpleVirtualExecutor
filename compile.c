/**
 * file: compile.c
 * author: fyzbc
 * date: 2017��5��2��
 *
 */
#include "compile.h"


/** \brief ����ָ��
 *
 * \param sType ָ���01��
 * \param iType ָ�������ֵ
 * \param data ����01��
 * \param point ��ǰ��Ҫ�Ӹ�λ��ʼ��01��
 * \param operatorCount ��ָ���Ǽ�Ԫ��
 * \return ���س������������ָ���λ��
 *
 */

int encodeInstrution(char *sType, int iType, char *data, int point, int operatorCount, Stack* stack)
{
    int codePoint = 0;
    int addressLen = 0;
    // ѭ��������
    int nowOperatorCount = 0;
    // ��ַ���͵���ʼλ��
    int thisPoint = point + codePoint;
    if (operatorCount != 0)
    {
        while(nowOperatorCount < operatorCount)
        {
            addressLen = readAddressType(sType, iType, data, thisPoint,stack);
            codePoint += addressLen;
            nowOperatorCount++;
            //
            thisPoint += addressLen;
        }
    }
    return codePoint;
}


/** \brief �ж�ָ�����ͣ�������ָ���ƶ�λ��
 *
 * \param sType ָ���01��
 * \param iType ָ�������ֵ
 * \param data ����01��
 * \param point ��ǰ��Ҫ�Ӹ�λ��ʼ��01��
 * \return ���ظ���ָ��01����ռ��λ��
 */

int readInstruction(char *sType, int iType, char *data, int point,Stack* programStack)
{

    Stack* stack  = init(10);
    DataType dataType = (DataType)malloc(sizeof(DataElem));
    dataType->msg = sType;
    dataType->value = iType;
    dataType->type = TYPE_OP;
    Push(stack,dataType);

    // ��λ����,�����������3λ
    int codePoint = 3;
    //printf("point is %d\n",point);
    switch(iType)
    {
    case MOV:
      //  printf("MOV\n");
        codePoint += encodeInstrution(sType,iType, data, point+codePoint,EYES_TWO,stack);
        break;
    case CAL:
      //  printf("CAL\n");
        codePoint += encodeInstrution(sType,iType, data, point+codePoint,EYES_TWO,stack);
        break;
    case POP:
      //  printf("POP\n");
        codePoint += encodeInstrution(sType,iType, data, point+codePoint,EYES_ONE,stack);
        break;
    case RET:
      //  printf("RET\n");
        codePoint += encodeInstrution(sType,iType, data, point+codePoint,EYES_ZERO,stack);
        break;
    case ADD:
      //  printf("ADD\n");
        codePoint += encodeInstrution(sType,iType, data, point+codePoint,EYES_TWO,stack);
        break;
    case AND:
      //  printf("AND\n");
        codePoint += encodeInstrution(sType,iType, data, point+codePoint,EYES_TWO,stack);
        break;
    case NOT:
      //  printf("NOT\n");
        codePoint += encodeInstrution(sType,iType, data, point+codePoint,EYES_ONE,stack);
        break;
    case EQU:
        // printf("EQU\n");
        codePoint += encodeInstrution(sType,iType, data, point+codePoint,EYES_TWO,stack);
        break;
    default :
        printf("[readInstruction]please check input!\n");
        exit(-1);
    }

    // ��������ջ�������ε������ջ
    while(!Empty(stack)){
        DataType dt = Pop(stack);
//        printf("-------------start:%d\n",stack->top);
//        printf("%s\n",dt->msg);
//        printf("%d\n",dt->value);
//        printf("%d\n",dt->type);
//        printf("-------------end:%d\n",stack->top);
        Push(programStack,dt);
    }

    return codePoint;

}

/** \brief ���ص�ַ���͵ĳ���
 *
 * \param
 * \param
 * \return codePoint���ͣ����ص�ַ���͵ĳ���
 *
 */
int readAddressType(char *sType, int iType, char *data, int point,Stack* stack)
{
    char *sAddressType = NULL;
    int iAddressType;
    int codePoint = V_TYPE_LEN;
    char* sValue = NULL;
    int iValue;
//    printf("*********");
    sAddressType = getSubString(data, point, V_TYPE_LEN);
    iAddressType = StrToInt(sAddressType);
//    printf("sAddressType is %s\n", sAddressType);
//    printf("iAddressType is %d\n", iAddressType);

    // ָʾ���뱾������ջ
    DataType dataType = (DataType)malloc(sizeof(DataElem));
    dataType->msg = sAddressType;
    dataType->value = iAddressType;
    dataType->type = TYPE_TP;
    Push(stack,dataType);

    switch(iAddressType)
    {
    case V_VALUE:
        //printf("00\n");
        codePoint+=V_VALUE_LEN;
        break;

    case V_REG:
        //printf("01\n");
        codePoint+=V_REG_LEN;
        break;

    case V_STACK:
        //printf("10\n");
        codePoint+=V_STACK_LEN;
        break;

    case V_PV:
        //printf("11\n");
        codePoint+=V_PV_LEN;
        break;
    default:
        printf("[readAddressType]please check input!");
        exit(-1);
        break;
    }

    sValue = getSubString(data,point+V_TYPE_LEN,codePoint-V_TYPE_LEN);
    iValue = StrToInt(sValue);

    // ֵ�뱾������ջ
    dataType = (DataType)malloc(sizeof(DataElem));
    dataType->msg = sValue;
    dataType->value = iValue;
    dataType->type = TYPE_VL;
    Push(stack,dataType);

    //printf("codePoint is %d\n",codePoint);
    return codePoint;
}



/** \brief ����01��
 *
 * \param data ȫ��01��
 * \param dataLen ȫ���ַ����ĳ���
 * \return ��
 *
 */

bool decodeThisCode(char data[], int dataLen,Stack* programStack){
    // ����ռ�
//    char *reverseData = (char*)malloc(sizeof(char)*(dataLen+4));
    int point = 8;
    char *instructionCount=NULL;
    int IinstructionCount;
    int lineCount;
    int len = dataLen;
    // ���õ������ݷ�ת
    reverseCode(data);
    printf("data is %s\n",data);
    instructionCount = getSubString(data,0,8);
    //printf("instructionCount is %s\n",instructionCount);
    IinstructionCount = StrToInt(instructionCount);
    printf("IinstructionCount is %d\n",IinstructionCount);
    lineCount = IinstructionCount;
    //printf("dataLen is %d\n",dataLen);
    if (IinstructionCount > 255){
        printf("stack overflow\n");
        return false;
    }
    else{
        while (point < dataLen && lineCount != 0)
        {

            char *sOneInstruction = NULL;
            int iOneInstruction;
            int pointBias;
            sOneInstruction = getSubString(data,point,3);
            iOneInstruction = StrToInt(sOneInstruction);
            // printf("iOneInstruction is %d\n", iOneInstruction);
            // printf("sOneInstruction is %s\n", sOneInstruction);

            pointBias = readInstruction(sOneInstruction, iOneInstruction, data, point, programStack);
            point += pointBias;
            lineCount--;

        }
        if (point!=0){
            printf("finalPoint is %d\n",point);
        }
    }
}

/** \brief �����ݽ�����ջ
 *
 * \param
 * \param
 * \return
 *
 */

int DataToStack(Stack* programStack,char* buf,int len){
    decodeThisCode(buf,len,programStack);
}
