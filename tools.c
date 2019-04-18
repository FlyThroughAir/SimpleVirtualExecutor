/**
 * file: tools.c
 * author: fyzbc
 * date: 2017年5月2日
 *
 */
#include "tools.h"




/** \brief 传入的第一个参数一般为栈，第二个参数为栈内元素
 *
 * \param
 * \param
 * \return
 *
 */

void* showOpData(void* obj1,void* obj2){

    DataType data = (DataType)obj2;
//    printf("msg:%s\n",data->msg);
//    printf("value:%d\n",data->value);
//    printf("type:%d\n",data->type);
    switch(data->value)
    {
        case MOV:
            printf("MOV\n");
            break;
        case CAL:
            printf("CAL\n");
            break;
        case POP:
            printf("POP\n");
            break;
        case RET:
            printf("RET\n");

            break;
        case ADD:
            printf("ADD\n");

            break;
        case AND:
            printf("AND\n");

            break;
        case NOT:
            printf("NOT\n");

            break;
        case EQU:
            printf("EQU\n");

            break;
        default :
            printf("[showOpData]输入有误，请核实！");
            exit(-1);
    }
    return NULL;
}

/** \brief 传入的第一个参数一般为栈，第二个参数为栈内元素
 *
 * \param
 * \param
 * \return
 *
 */
void* showTpData(void* obj1,void* obj2){
    DataType data = (DataType)obj2;
//    printf("msg:%s\n",data->msg);

    switch(data->value)
    {
        case V_VALUE:
            printf("the value!\n");
            break;

        case V_REG:
            printf("the address of register!\n");
            break;

        case V_STACK:
            printf("the address of stack!\n");
            break;

        case V_PV:
            printf("the pointer!\n");
            break;
        default:
            printf("[showTpData]输入有误，请核实！");
            exit(-1);
            break;
    }
    return NULL;
}

/** \brief 传入的第一个参数一般为栈，第二个参数为栈内元素
 *
 * \param
 * \param
 * \return
 *
 */
void* showVlData(void* obj1,void* obj2){
    DataType data = (DataType)obj2;
//    printf("msg:%s\n",data->msg);
//    printf("type:%d\n",data->type);
    printf("value:%d\n",data->value);
    return NULL;
}

/** \brief 读01字符串文件
 *
 * \param 文件名
 * \param 用二维指针返回文件内容
 * \return 读到的文件长度
 *
 */
int readFile(char* fileName,char** contentBuf){
	int  nLen = 0;
	FILE * fp = fopen(fileName, "r");
	if (fp == NULL) {//若打开文件失败则退出
		puts("file not found！");
	}
	fseek(fp, 0, SEEK_END);
	nLen = ftell(fp);  //得到当前指针位置, 即是文件的长度
	rewind(fp);    //文件指针恢复到文件头位置
	*contentBuf = (char*)malloc(sizeof(char)*(nLen+1));
	if (!contentBuf)
	{
		perror("内存不够!\n");
		exit(0);
	}
	//读取文件内容//读取的长度和源文件长度有可能有出入，这里自动调整 nLen
	nLen = fread(*contentBuf, sizeof(char), nLen, fp);
	(*contentBuf)[nLen] = '\0'; //添加字符串结尾标志
	fclose(fp);  //关闭文件
	return nLen;
}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void readBinaryFile(char fileName[])
{
	FILE * fp = fopen(fileName, "rb");
	if (fp == NULL) {//若打开文件失败则退出
		puts("file not found!");
	}
	while (!feof(fp))
	{
		char element = getc(fp);
		printf("%2x", element);
	}
	fclose(fp);
}




/** \brief 将字符串转换成整数.传入的字符串需要倒叙.
 *
 * \param S[] 需要转换的字符串
 * \return 整数
 *
 */

int StrToInt(char s[])
{


    int i = 0;
    int slen = strlen(s);
//    printf("string is %s\n",s);
    int sum = 0;
    double dMidRes;
    int iMidRes;
    for (i;i<slen;i++)
    {
//        printf("i is %d\n",i);
        dMidRes = pow(2,i);
//        printf("dMidRes is %d\n",dMidRes);
        iMidRes = (int)dMidRes;
//        printf("iMidRes is %d\n",iMidRes);
        sum += (s[i]-48)*iMidRes;
//        printf("s[%d] is %d\n",i,s[i]);

    }
//    printf("sum is %d\n",sum);
    return sum;
}


/** \brief 开辟空间获取子串
 *
 * \param
 * \param
 * \return
 *
 */

char* getSubString(char a_str[], int start, int len)
{
    char *thisData = (char*)malloc(sizeof(char)*(len+1));
    int i,j;
    for (i = 0, j=start;i<len,j<(start+len);i++,j++){
        thisData[i] = a_str[j];
    }
    thisData[len] = '\0';
    return thisData;
}




/** \brief 反转字符串
 *
 * \param
 * \param
 * \return
 *
 */

char* reverseCode(char str[])
{
    int c,j,i;
    for(i = 0, j = strlen(str) - 1; i < j; i++, j--)
    {
        c=str[i];
        str[i]=str[j];
        str[j]=c;
    }
    return str;
}
