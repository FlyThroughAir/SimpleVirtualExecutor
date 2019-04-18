/**
 * file: compile.h
 * author: fyzbc
 * date: 2017年5月2日
 *
 */
#ifndef _COMPILE
#define _COMPILE

#include "zstack.h"
#include "tools.h"

/** \brief 解析指令
 *
 * \param sType 指令的01码
 * \param iType 指令的整型值
 * \param data 所有01码
 * \param point 当前需要从该位开始读01码
 * \param operatorCount 该指令是几元的
 * \return 返回除操作码外该条指令的位数
 *
 */

int encodeInstrution(char *sType, int iType, char *data, int point, int operatorCount, Stack* stack);
/** \brief 判断指令类型，并返回指针移动位数
 *
 * \param sType 指令的01码
 * \param iType 指令的整型值
 * \param data 所有01码
 * \param point 当前需要从该位开始读01码
 * \return 返回该条指令01码所占的位数
 */

int readInstruction(char *sType, int iType, char *data, int point,Stack* programStack);
/** \brief 返回地址类型的长度
 *
 * \param
 * \param
 * \return codePoint整型，返回地址类型的长度
 *
 */
int readAddressType(char *sType, int iType, char *data, int point,Stack* stack);

/** \brief 解析01码
 *
 * \param data 全部01码
 * \param dataLen 全部字符串的长度
 * \return 无
 *
 */

bool decodeThisCode(char data[], int dataLen,Stack* programStack);

/** \brief 将数据进行入栈
 *
 * \param
 * \param
 * \return
 *
 */

int DataToStack(Stack* programStack,char* buf,int len);



#endif // COMPILE
