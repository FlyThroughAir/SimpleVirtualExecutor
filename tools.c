/**
 * file: tools.c
 * author: fyzbc
 * date: 2017��5��2��
 *
 */
#include "tools.h"




/** \brief ����ĵ�һ������һ��Ϊջ���ڶ�������Ϊջ��Ԫ��
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
            printf("[showOpData]�����������ʵ��");
            exit(-1);
    }
    return NULL;
}

/** \brief ����ĵ�һ������һ��Ϊջ���ڶ�������Ϊջ��Ԫ��
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
            printf("[showTpData]�����������ʵ��");
            exit(-1);
            break;
    }
    return NULL;
}

/** \brief ����ĵ�һ������һ��Ϊջ���ڶ�������Ϊջ��Ԫ��
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

/** \brief ��01�ַ����ļ�
 *
 * \param �ļ���
 * \param �ö�άָ�뷵���ļ�����
 * \return �������ļ�����
 *
 */
int readFile(char* fileName,char** contentBuf){
	int  nLen = 0;
	FILE * fp = fopen(fileName, "r");
	if (fp == NULL) {//�����ļ�ʧ�����˳�
		puts("file not found��");
	}
	fseek(fp, 0, SEEK_END);
	nLen = ftell(fp);  //�õ���ǰָ��λ��, �����ļ��ĳ���
	rewind(fp);    //�ļ�ָ��ָ����ļ�ͷλ��
	*contentBuf = (char*)malloc(sizeof(char)*(nLen+1));
	if (!contentBuf)
	{
		perror("�ڴ治��!\n");
		exit(0);
	}
	//��ȡ�ļ�����//��ȡ�ĳ��Ⱥ�Դ�ļ������п����г��룬�����Զ����� nLen
	nLen = fread(*contentBuf, sizeof(char), nLen, fp);
	(*contentBuf)[nLen] = '\0'; //����ַ�����β��־
	fclose(fp);  //�ر��ļ�
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
	if (fp == NULL) {//�����ļ�ʧ�����˳�
		puts("file not found!");
	}
	while (!feof(fp))
	{
		char element = getc(fp);
		printf("%2x", element);
	}
	fclose(fp);
}




/** \brief ���ַ���ת��������.������ַ�����Ҫ����.
 *
 * \param S[] ��Ҫת�����ַ���
 * \return ����
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


/** \brief ���ٿռ��ȡ�Ӵ�
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




/** \brief ��ת�ַ���
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
