/**
 * file: zstack.h
 * author: fyzbc
 * date: 2017��5��2��
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


/*--------------�������������ݻ��߽ṹ��-----------------------*/

struct Data{
    /* �������Ϣ��Դ��Ϣ�� */
    char* msg; // Դ��Ϣ��

    /* �����루����ָʾ�ƣ� */
    int value; // �洢����ֵ

    /* ���ͣ������ĸ�ջ��أ� */
    int type; // 0��ʾ��������1��ʾ����ָʾ����2��ʾֵ

    /* ����ָ�룬ָ��һ�������еĺ������߿ա�
        �����Data����Ϊ������
        ��ôִ�иú��������д�����䣬���򣬺��Ըò�����
     */
    void* (*readFun)(void*,void*); //void*���Ժܷ����ת����������ָ�����͡�
    void* (*writeFun)(void*,void*); //һ�㵥Ŀ���߶�Ŀ���������Ҫд������
    void* (*lookFun)(void*,void*);
};



/*-----------ʵ��һ��˳��ջ------------------------*/
// ����ջ�洢����������
typedef struct Data DataElem;
typedef struct Data* DataType;



//Sequence Stack ʵ��˳��ջ��ʹ��������ʵ��
struct stack
{
    DataType* data;
    int top;
    int maxsize;
};


typedef struct stack Stack;
typedef struct stack* LpStack;
// ��ʼ��ջ
Stack* init(int maxsize);
// �ж�ջ�Ƿ�Ϊ��
bool Empty(Stack* s);
// �ж�ջ�Ƿ�������
bool full(Stack* s);
// ��ջ
void Push(Stack* s,DataType element);
// ��ջ
DataType Pop(Stack* s);
// ȡջ��Ԫ��
DataType Top(Stack* s);
// ���ӣ���ȡջ��Ԫ��
DataType Hook(Stack* s,int order);
// ���ӣ���Ԫ���͵�ջ��ָ��λ�ã�����д
void Stick(Stack* s,int order,DataType element);
// ����ջ
void Destroy(Stack* s);
// ����ջ
void travelStack(Stack* s);
/*---------------end----------------------*/




#endif
