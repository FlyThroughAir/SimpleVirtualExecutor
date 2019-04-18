/**
 * file: tools.h
 * author: fyzbc
 * date: 2017��5��2��
 *
 */

#ifndef _TOOLS
#define _TOOLS
#include <stdio.h>
#include "zstack.h"

#define STACK_LENGTH 1024
/**
* ���弸Ŀ�����
*/
#define EYES_ZERO   0
#define EYES_ONE    1
#define EYES_TWO    2


/**
Ԥ�����������ָʾ����
*/
#define MOV 0 //000 ˫Ŀ
#define CAL 1 //001 ˫Ŀ
#define POP 2 //010 ��Ŀ �Ӵ���ջ�е���
#define RET 3 //011 ��Ļ
#define ADD 4 //100 ˫Ŀ
#define AND 5 //101 ˫Ŀ
#define NOT 6 //110 ��Ŀ
#define EQU 7 //111 ��Ŀ

/*----------�����ַ����-----------*/
#define V_VALUE 0  //00 ֵ
#define V_REG   1  //01 �Ĵ�����ַ
#define V_STACK 2  //10 ջ��ַ��Ϊֵ
#define V_PV    3  //11 ջ�ϵ�ַ�ڵ�ֵΪһ��ջ��ַ��


// ���岻ͬ��ַ���ͳ����Լ�ָʾ��������
#define V_TYPE_LEN  2  //00 ֵ
#define V_VALUE_LEN 8  //00 ֵ
#define V_REG_LEN   3  //01 �Ĵ�����ַ
#define V_STACK_LEN 7  //10 ջ��ַ��Ϊֵ
#define V_PV_LEN    7  //11 ջ�ϵ�ַ�ڵ�ֵΪһ��ջ��ַ��


// �������������
#define TYPE_OP 0 // ������
#define TYPE_TP 1 // ����
#define TYPE_VL 2 // ֵ

/*--------------�˴����幤��----------------------*/




// ��ȡ�ļ��ļ��������ض�������ݳ��ȡ�
int readFile(char* fileName,char** contentBuf);

// ���������ļ�
void readBinaryFile(char fileName[]);


/** \brief ���ַ���ת��������.������ַ�����Ҫ����.
 *
 * \param S[] ��Ҫת�����ַ���
 * \return ����
 *
 */

int StrToInt(char s[]);

/** \brief ���ٿռ��ȡ�Ӵ�
 *
 * \param
 * \param
 * \return
 *
 */

char* getSubString(char a_str[], int start, int len);

/** \brief ��ת�ַ���
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
