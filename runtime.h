/**
 * file: runtime.h
 * author: fyzbc
 * date: 2017��5��2��
 *
 */

#ifndef _RUNTIME
#define _RUNTIME

#include "zstack.h"
#include "tools.h"


/*------------����Ĵ���---------------*/
struct RegistersStruct{

    
    int reg[8]; // �Ĵ�����

    int ip; // ָ��ζ���ƫ�ơ�
    int bp; // ���ݶζ���ƫ�ơ�

    int sp; // ��ջָ��
    int si; // Դ��ַ
    int di; // Ŀ�ı�ַ
    int flag;// ��־�Ĵ���

};

typedef struct RegistersStruct Registers;
typedef struct RegistersStruct* LpRegisters;

/*---------------end-----------------*/

// ����ʱ���ݽṹ
struct RunTimeStruct{

    // �����
    Stack* codeStack;
    // ���ݶ�
    Stack* dataStack;
    // �Ĵ�����
    LpRegisters lpRegisters;

};

typedef struct RunTimeStruct RunTime;
typedef struct RunTimeStruct* LpRunTime;



/** \brief ��ȡָ���Ĵ�����ֵ
 *
 * \param
 * \param
 * \return
 *
 */
int readRegister(LpRegisters lpRegisters, int address);

/** \brief ��ָ���Ĵ�������ֵ
 *
 * \param
 * \param
 * \return
 *
 */
int writeRegister(LpRegisters lpRegisters,int address, int value);


/** \brief ��ʼ������ʱ����
 *
 * \param codeStack �����
 * \param dataStack ���ݶ�
 * \param lpRegister �Ĵ�����
 * \return ���ɳɹ�������ʱ����
 *
 */
LpRunTime initRunTime(Stack* codeStack, Stack* dataStack,LpRegisters lpRegisters);


/** \brief ���ڴ��ж�ȡ����
 *
 * \param lpRunTime ����ʱ����
 * \param order ��Ҫȡ�����ݵ�ջ��ַ
 * \return
 *
 */
int readValueFromStack(LpStack dataStack,int order);

/** \brief ������ջ�ж�ȡ����
 *
 * \param lpRunTime ����ʱ����
 * \param order ��Ҫȡ�����ݵ�ջ��ַ
 * \return
 *
 */
void writeValueToStack(LpStack dataStack, int order, DataType data);


/*
���濪ʼ��ʽ�Ľ���
*/

/*-------------------���濪ʼ��ʽִ��----------------------*/

/** \brief �õ����ݡ�
 *      ǰ������Ϊ������typeָʾ���Ѿ���ջ�е�����
 *
  * \param lpRunTime ����ʱ����
 * \param type ��������
 * \param value ����ֵ
 * \return ���ػ�ȡ������
 *
 */
int getDataByOperator(LpRunTime lpRunTime,int type,int value);


/** \brief ���ò�������
 *
 * \param ����ʱ����
 * \param ��������Ϊ������͵�������������ʱ��Ϊ int* ����
 * \return ���ز������
 *
 */
void setDataByOperator(LpRunTime lpRunTime, int type, int address, int value);



/** \brief ������ջ����
 *
 * \param
 * \param
 * \return
 *
 */
int runOneCommand(LpRunTime lpRunTime,int ret);


/**_______________________________________________*/


/* ����Ϊ����ĺ���ʵ�� */
int movFunction(LpRunTime lpRunTime);
/* �ӷ����� */
int addFunction(LpRunTime lpRunTime);
/* ��ջ */
int popFunction(LpRunTime lpRunTime);



#endif // RUNTIME
