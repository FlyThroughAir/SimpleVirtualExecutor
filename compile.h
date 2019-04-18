/**
 * file: compile.h
 * author: fyzbc
 * date: 2017��5��2��
 *
 */
#ifndef _COMPILE
#define _COMPILE

#include "zstack.h"
#include "tools.h"

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

int encodeInstrution(char *sType, int iType, char *data, int point, int operatorCount, Stack* stack);
/** \brief �ж�ָ�����ͣ�������ָ���ƶ�λ��
 *
 * \param sType ָ���01��
 * \param iType ָ�������ֵ
 * \param data ����01��
 * \param point ��ǰ��Ҫ�Ӹ�λ��ʼ��01��
 * \return ���ظ���ָ��01����ռ��λ��
 */

int readInstruction(char *sType, int iType, char *data, int point,Stack* programStack);
/** \brief ���ص�ַ���͵ĳ���
 *
 * \param
 * \param
 * \return codePoint���ͣ����ص�ַ���͵ĳ���
 *
 */
int readAddressType(char *sType, int iType, char *data, int point,Stack* stack);

/** \brief ����01��
 *
 * \param data ȫ��01��
 * \param dataLen ȫ���ַ����ĳ���
 * \return ��
 *
 */

bool decodeThisCode(char data[], int dataLen,Stack* programStack);

/** \brief �����ݽ�����ջ
 *
 * \param
 * \param
 * \return
 *
 */

int DataToStack(Stack* programStack,char* buf,int len);



#endif // COMPILE
